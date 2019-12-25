//*****************************************************************************
//
//! @file amu2s.c
//!
//! @brief utility file to stream data from SPI to USB bridge
//!
//!
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2019, Ambiq Micro
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
//
// Third party software included in this distribution is subject to the
// additional license terms as defined in the /docs/licenses directory.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision v2.2.0-7-g63f7c2ba1 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_util.h"
#include <string.h>

#include "amu2s.h"

#include "AWE_bsp_config.h"

static void *g_pAmu2sIOMHandle;

volatile bool amu2s_init_flag = false;

// Buffer for non-blocking transactions
uint32_t DMATCBBuffer[2048];
volatile uint32_t IomStatus;

static uint16_t packet_counter[Amu2s_max_types];          // support 4 types only
static uint16_t buffer_counter[Amu2s_max_types];          // support 4 types only

static uint8_t buffer_pcm[AMU2S_BUFFER_MAX_INSTANCES][AMU2S_PCM_BYTES + AMU2S_BUFFER_OVERHEAD_BYTES];
static uint8_t buffer_spp[AMU2S_BUFFER_MAX_INSTANCES][AMU2S_SPP_BYTES + AMU2S_BUFFER_OVERHEAD_BYTES];
static uint8_t buffer_opus[AMU2S_BUFFER_MAX_INSTANCES][AMU2S_OPUS_BYTES + AMU2S_BUFFER_OVERHEAD_BYTES];

typedef struct amu2s_buffer
{
    uint8_t* buffer;
    uint32_t len;
}amu2s_buffer_t;

static amu2s_buffer_t buffer_array[Amu2s_max_types]  =
{
    {
        .buffer = NULL,
        .len    = 0,
    },
    {
        .buffer = buffer_pcm[0],
        .len    = AMU2S_PCM_BYTES + AMU2S_BUFFER_OVERHEAD_BYTES,
    },
    {
        .buffer = buffer_spp[0],
        .len    = AMU2S_SPP_BYTES + AMU2S_BUFFER_OVERHEAD_BYTES,
    },
    {
        .buffer = buffer_opus[0],
        .len    = AMU2S_OPUS_BYTES + AMU2S_BUFFER_OVERHEAD_BYTES,
    },
};

//*****************************************************************************
//
// Configuration structure for the IO Master.
//
//*****************************************************************************
am_hal_iom_config_t     g_sAmu2sIomCfg =
{
    .eInterfaceMode     = AM_HAL_IOM_SPI_MODE,
    .ui32ClockFreq      = AM_HAL_IOM_8MHZ,
    .eSpiMode           = AM_HAL_IOM_SPI_MODE_0,
    .pNBTxnBuf          = 0,
    .ui32NBTxnBufLength = 0
};

uint8_t amu2s_init(void)
{
    if ( AMU2S_SPI_IOM > AM_REG_IOM_NUM_MODULES )
    {
        return AMU2S_ERROR_IOM_NUM;
    }
    // Set up IOM
    // Initialize the Device
    g_sAmu2sIomCfg.ui32NBTxnBufLength = sizeof(DMATCBBuffer) / 4;
    g_sAmu2sIomCfg.pNBTxnBuf = &DMATCBBuffer[0];
    //
    // Configure the IOM pins.
    //
    am_bsp_iom_pins_enable(AMU2S_SPI_IOM, AM_HAL_IOM_SPI_MODE);

    //
    // Enable fault detection.
    //
#if AM_APOLLO3_MCUCTRL
    am_hal_mcuctrl_control(AM_HAL_MCUCTRL_CONTROL_FAULT_CAPTURE_ENABLE, 0);
#else // AM_APOLLO3_MCUCTRL
    am_hal_mcuctrl_fault_capture_enable();
#endif // AM_APOLLO3_MCUCTRL

    //
    // Initialize the IOM instance.
    // Enable power to the IOM instance.
    // Configure the IOM for Serial operation during initialization.
    // Enable the IOM.
    // HAL Success return is 0
    //
    if (am_hal_iom_initialize(AMU2S_SPI_IOM, &g_pAmu2sIOMHandle) ||
        am_hal_iom_power_ctrl(g_pAmu2sIOMHandle, AM_HAL_SYSCTRL_WAKE, false) ||
        am_hal_iom_configure(g_pAmu2sIOMHandle, &g_sAmu2sIomCfg) ||
        am_hal_iom_enable(g_pAmu2sIOMHandle))
//|| am_hal_iom_interrupt_enable(g_pAmu2sIOMHandle, 0xFF)
    {
        return AMU2S_ERROR_INITIALIZATION;
    }

    NVIC_SetPriority(IOMSTR0_IRQn, 4);
    NVIC_EnableIRQ(IOMSTR0_IRQn);

    // clear buffers and indexes
    for(uint8_t i = 1; i < Amu2s_max_types; i++)
    {
        memset(buffer_array[i].buffer, 0, buffer_array[i].len);
    }
    memset(buffer_counter, 0, sizeof(buffer_counter));
    memset(packet_counter, 0, sizeof(packet_counter));

    // set flag
    amu2s_init_flag = true;

    //
    // Return the status.
    //
    return AMU2S_ERROR_SUCCESS;
}
uint8_t amu2s_deinit(void)
{
    if (am_hal_iom_disable(g_pAmu2sIOMHandle))
    {
        return AMU2S_ERROR_DEINITIALIZATION;
    }

    am_hal_iom_power_ctrl(g_pAmu2sIOMHandle, AM_HAL_SYSCTRL_DEEPSLEEP, false);
    am_hal_iom_uninitialize(&g_pAmu2sIOMHandle);

    amu2s_init_flag = false;

    return AMU2S_ERROR_SUCCESS;
}

void amu2s_write_callback(void* pCallbackCtxt, uint32_t transactionStatus)
{
    uint32_t count = 0;
    count++;
}

void amu2s_send(amu2s_type_e_t type, const void* buf, uint32_t len)
{
    if(amu2s_init_flag == false)
    {
        amu2s_init();
    }

    // sanity check
    // handle buffer index in a 1d fashion to avoid confusion
    uint8_t* buffer = buffer_array[type].buffer + (buffer_counter[type] * buffer_array[type].len);
    if(buffer == NULL)
    {
        return; // generic data, not supported now
    }

    // AMU2S does not allow nest operation
    AM_CRITICAL_BEGIN

    // build header for driver
    buffer[0] = 0x80; // master transfer command
    buffer[1] = 0x00; // sequence number
    buffer[2] = ((len + 8) >> 8U) & 0xFF;
    buffer[3] = (len + 8) & 0xFF;
    buffer[4] = 0x4A; // write request
    buffer[5] = 0x00; // dummy


    buffer[6] = (len) & 0xFF;
    buffer[7] = ((len) >> 8U) & 0xFF;   // length for tlv in amu2s.exe

    buffer[8] = type;
    buffer[9] = 0x00; // dummy

    buffer[10] = packet_counter[type] & 0xFF;
    buffer[11] = packet_counter[type] >> 8U & 0xFF;
    packet_counter[type]++;

    memcpy(&buffer[12], buf, len);
    uint16_t sum = amu2s_get_checksum(buffer, len+12);

    buffer[len+12] = (sum >> 8U ) & 0xFF;
    buffer[len+13] = sum & 0xFF;

//    amu2s_blocking_write(buffer, (len + 14));
    amu2s_nonblocking_write(buffer, (len + 14), amu2s_write_callback, NULL);

    buffer_counter[type]++;
    if(buffer_counter[type] == AMU2S_BUFFER_MAX_INSTANCES)
    {
        buffer_counter[type] = 0;
    }
    AM_CRITICAL_END

}

static uint16_t amu2s_get_checksum(uint8_t* pBuf, uint32_t numBytes)
{
    uint32_t sum = 0x5A;

    for(uint32_t idx = 0; idx < numBytes; idx++)
    {
        sum += pBuf[idx];
    }

    return (uint16_t)sum;
}

static uint8_t amu2s_blocking_write(uint8_t* buf, uint32_t len)
{
    am_hal_iom_transfer_t Transaction;

    Transaction.ui8RepeatCount  = 0;
    Transaction.ui32PauseCondition = 0;
    Transaction.ui32StatusSetClr = 0;

    //
    // Write the command to the device.
    //
    Transaction.eDirection      = AM_HAL_IOM_TX;
    Transaction.ui32InstrLen    = 1;
    Transaction.ui32Instr       = 0x5A;
    Transaction.ui32NumBytes    = len;
    Transaction.pui32TxBuffer   = (uint32_t *)buf;
    Transaction.uPeerInfo.ui32SpiChipSelect = AMU2S_SPI_CS;
    Transaction.bContinue       = false;

    //
    // Start the transaction.
    //
    if (am_hal_iom_blocking_transfer(g_pAmu2sIOMHandle, &Transaction))
    {
        return AMU2S_ERROR_SENDING;
    }

    //
    // Return the status.
    //
    return AMU2S_ERROR_SUCCESS;

}


static uint8_t amu2s_nonblocking_write(uint8_t *pui8TxBuffer, uint32_t ui32NumBytes, am_hal_iom_callback_t pfnCallback,void *pCallbackCtxt)
{
    am_hal_iom_transfer_t         Transaction;

    Transaction.ui8RepeatCount  = 0;
    Transaction.ui32PauseCondition = 0;
    Transaction.ui32StatusSetClr = 0;
    Transaction.ui8Priority     = 1;        // High priority for now.

    //
    // Set up the IOM transaction.
    //
    Transaction.eDirection      = AM_HAL_IOM_TX;
    Transaction.ui32InstrLen    = 1;
    Transaction.ui32Instr       = 0x5A;
    Transaction.ui32NumBytes    = ui32NumBytes;
    Transaction.pui32TxBuffer   = (uint32_t *)pui8TxBuffer;
    Transaction.uPeerInfo.ui32SpiChipSelect = AMU2S_SPI_CS;
    Transaction.bContinue       = false;

    //
    // Add this transaction to the command queue (no callback).
    //
    IomStatus = am_hal_iom_nonblocking_transfer(g_pAmu2sIOMHandle, &Transaction, pfnCallback, pCallbackCtxt);
    if(IomStatus)
    {
        am_util_stdio_printf("%d\n\r", IomStatus);
        return AMU2S_ERROR_SENDING;
    }

    //
    // Return the status.
    //
    return AMU2S_ERROR_SUCCESS;
}

//*****************************************************************************
//
// IOM ISRs.
//
//*****************************************************************************
void am_iomaster0_isr(void)
{
    uint32_t ui32Status;

    if (!am_hal_iom_interrupt_status_get(g_pAmu2sIOMHandle, true, &ui32Status))
    {
        if ( ui32Status )
        {
            am_hal_iom_interrupt_clear(g_pAmu2sIOMHandle, ui32Status);
            am_hal_iom_interrupt_service(g_pAmu2sIOMHandle, ui32Status);
        }
    }
}

//EOF
