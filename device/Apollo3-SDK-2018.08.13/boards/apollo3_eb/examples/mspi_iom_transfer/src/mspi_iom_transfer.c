//*****************************************************************************
//
//! @file mspi_iom_xfer.c
//!
//! @brief Example demonstrating the hardware assisted MSPI to IOM transfer
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2018, Ambiq Micro
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
// This is part of revision v1.2.12-830-g39ebe7dbe of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_devices_mspi_flash.h"
#include "am_util.h"

#if FIREBALL_CARD
//
// The Fireball device card multiplexes various devices including each of an SPI
// and I2C FRAM. The Fireball device driver controls access to these devices.
// If the Fireball card is not used, FRAM devices can be connected directly
// to appropriate GPIO pins.
//
#include "am_devices_fireball.h"
#endif // FIREBALL_CARD

//*****************************************************************************
// Customize the following for the test
//*****************************************************************************
// Control the example execution
#define FRAM_IOM_MODULE         1
#define NUM_INERATIONS          32
// #define MSPI_FLASH_SERIAL // Configures flash in serial mode (default is quad)
// Enables Verification of the FRAM data after it has been written to
//#define VERIFY_DATA
// Control the size of the block of data to be transferred from Flash to FRAM
#define BLOCK_SIZE              128*1024 // FRAM device is limited to 128K in size
#define CPU_SLEEP_GPIO          29       // GPIO used to track CPU in sleep on logic analyzer
#define DEFAULT_TIMEOUT         10000
#define ENABLE_LOGGING

// Select the FRAM Device
#define FRAM_DEVICE_MB85RS1MT     1     // SPI Fram (Fireball)
//#define FRAM_DEVICE_MB85RC64TA    1     // I2C Fram (Fireball)
//#define FRAM_DEVICE_MB85RS64V     1     // SPI Fram
//#define FRAM_DEVICE_MB85RC256V    1     // I2C Fram
//*****************************************************************************
//*****************************************************************************

#if (FRAM_DEVICE_MB85RS1MT == 1)
#include "am_devices_mb85rs1mt.h"
#define FRAM_DEVICE_ID          AM_DEVICES_MB85RS1MT_ID
#define FRAM_IOM_MODE           AM_HAL_IOM_SPI_MODE
#elif (FRAM_DEVICE_MB85RC256V == 1)
#include "am_devices_mb85rc256v.h"
#define FRAM_DEVICE_ID          AM_DEVICES_MB85RC256V_ID
#define FRAM_IOM_MODE           AM_HAL_IOM_I2C_MODE
#elif (FRAM_DEVICE_MB85RS64V == 1)
#include "am_devices_mb85rs64v.h"
#define FRAM_DEVICE_ID          AM_DEVICES_MB85RS64V_ID
#define FRAM_IOM_MODE           AM_HAL_IOM_SPI_MODE
#elif (FRAM_DEVICE_MB85RC64TA == 1)
#include "am_devices_mb85rc256v.h"
#define FRAM_DEVICE_ID          AM_DEVICES_MB85RC64TA_ID
#define FRAM_IOM_MODE           AM_HAL_IOM_I2C_MODE
#else
#error "Unknown FRAM Device"
#endif

// Size of temporary buffer being used
#define TEMP_BUFFER_SIZE        ((AM_HAL_IOM_MAX_TXNSIZE_SPI + 256) & 0xFFFFFF00)
// Size of SPI Transaction
#define SPI_TXN_SIZE            ((AM_HAL_IOM_MAX_TXNSIZE_SPI) & 0xFFFFFF00)

// Helper Macros to map the ISR based on the IOM being used
#define IOM_INTERRUPT1(n)       AM_HAL_INTERRUPT_IOMASTER ## n
#define IOM_INTERRUPT(n)        IOM_INTERRUPT1(n)
#if AM_CMSIS_REGS
#define FRAM_IOM_IRQn           ((IRQn_Type)(IOMSTR0_IRQn + FRAM_IOM_MODULE))
#else // AM_CMSIS_REGS
#define FRAM_IOM_INTERRUPT      IOM_INTERRUPT(FRAM_IOM_MODULE)
#endif // AM_CMSIS_REGS

//
// Take over the interrupt handler for whichever IOM we're using.
//
#define fram_iom_isr                                                          \
    am_iom_isr1(FRAM_IOM_MODULE)
#define am_iom_isr1(n)                                                        \
    am_iom_isr(n)
#define am_iom_isr(n)                                                         \
    am_iomaster ## n ## _isr

// Friendlier names for the bit masks
#if AM_CMSIS_REGS
#define AM_REG_IOM_CQFLAGS_CQFLAGS_MSPI1START   (_VAL2FLD(IOM0_CQPAUSEEN_CQPEN, IOM0_CQPAUSEEN_CQPEN_SWFLAGEN1))
#define AM_REG_IOM_CQFLAGS_CQFLAGS_MSPI0START   (_VAL2FLD(IOM0_CQPAUSEEN_CQPEN, IOM0_CQPAUSEEN_CQPEN_SWFLAGEN0))

#define IOM_SIGNAL_MSPI_BUFFER0       (AM_REG_IOM_CQFLAGS_CQFLAGS_MSPI0START << 8)
#define IOM_SIGNAL_MSPI_BUFFER1       (AM_REG_IOM_CQFLAGS_CQFLAGS_MSPI1START << 8)
#define MSPI_SIGNAL_IOM_BUFFER0       (MSPI_CQFLAGS_CQFLAGS_SWFLAG0 << 8)
#define MSPI_SIGNAL_IOM_BUFFER1       (MSPI_CQFLAGS_CQFLAGS_SWFLAG1 << 8)

#define IOM_WAIT_FOR_MSPI_BUFFER0     (_VAL2FLD(IOM0_CQPAUSEEN_CQPEN, IOM0_CQPAUSEEN_CQPEN_MSPI0XNOREN))
#define IOM_WAIT_FOR_MSPI_BUFFER1     (_VAL2FLD(IOM0_CQPAUSEEN_CQPEN, IOM0_CQPAUSEEN_CQPEN_MSPI1XNOREN))
#define MSPI_WAIT_FOR_IOM_BUFFER0     (_VAL2FLD(MSPI_CQFLAGS_CQFLAGS, MSPI_CQFLAGS_CQFLAGS_IOM0READY))
#define MSPI_WAIT_FOR_IOM_BUFFER1     (_VAL2FLD(MSPI_CQFLAGS_CQFLAGS, MSPI_CQFLAGS_CQFLAGS_IOM1READY))
#else // AM_CMSIS_REGS
#define AM_REG_IOM_CQFLAGS_CQFLAGS_MSPI1START   AM_REG_IOM_CQPAUSEEN_CQPEN_SWFLAGEN1
#define AM_REG_IOM_CQFLAGS_CQFLAGS_MSPI0START   AM_REG_IOM_CQPAUSEEN_CQPEN_SWFLAGEN0

#define IOM_SIGNAL_MSPI_BUFFER0       (AM_REG_IOM_CQFLAGS_CQFLAGS_MSPI0START << 8)
#define IOM_SIGNAL_MSPI_BUFFER1       (AM_REG_IOM_CQFLAGS_CQFLAGS_MSPI1START << 8)
#define MSPI_SIGNAL_IOM_BUFFER0       (AM_REG_MSPI_CQFLAGS_CQFLAGS_IOM0START << 8)
#define MSPI_SIGNAL_IOM_BUFFER1       (AM_REG_MSPI_CQFLAGS_CQFLAGS_IOM1START << 8)

#define IOM_WAIT_FOR_MSPI_BUFFER0     (AM_REG_IOM_CQPAUSEEN_CQPEN_MSPI0XNOREN)
#define IOM_WAIT_FOR_MSPI_BUFFER1     (AM_REG_IOM_CQPAUSEEN_CQPEN_MSPI1XNOREN)
#define MSPI_WAIT_FOR_IOM_BUFFER0     (AM_REG_MSPI_CQFLAGS_CQFLAGS_IOM0READY)
#define MSPI_WAIT_FOR_IOM_BUFFER1     (AM_REG_MSPI_CQFLAGS_CQFLAGS_IOM1READY)
#endif // AM_CMSIS_REGS


#ifdef ENABLE_LOGGING
#define DEBUG_PRINT am_util_stdio_printf
#else
#define DEBUG_PRINT(...)
#endif
//
// Typedef - to encapsulate device driver functions
//
typedef struct
{
    uint8_t  devName[20];
    uint32_t (*fram_init)(uint32_t ui32Module, am_hal_iom_config_t *psIOMSettings, void **ppIomHandle);
    uint32_t (*fram_term)(uint32_t ui32Module);

    uint32_t (*fram_read_id)(uint32_t *pDeviceID);

    uint32_t (*fram_blocking_write)(uint8_t *ui8TxBuffer,
                             uint32_t ui32WriteAddress,
                             uint32_t ui32NumBytes);

    uint32_t (*fram_nonblocking_write)(uint8_t *ui8TxBuffer,
                                uint32_t ui32WriteAddress,
                                uint32_t ui32NumBytes,
                                am_hal_iom_callback_t pfnCallback,
                                void *pCallbackCtxt);

    uint32_t (*fram_nonblocking_write_adv)(uint8_t *ui8TxBuffer,
                                uint32_t ui32WriteAddress,
                                uint32_t ui32NumBytes,
                                uint32_t ui32PauseCondition,
                                uint32_t ui32StatusSetClr,
                                am_hal_iom_callback_t pfnCallback,
                                void *pCallbackCtxt);

    uint32_t (*fram_blocking_read)(uint8_t *pui8RxBuffer,
                            uint32_t ui32ReadAddress,
                            uint32_t ui32NumBytes);

    uint32_t (*fram_nonblocking_read)(uint8_t *pui8RxBuffer,
                                                      uint32_t ui32ReadAddress,
                                                      uint32_t ui32NumBytes,
                                                      am_hal_iom_callback_t pfnCallback,
                                                      void *pCallbackCtxt);
    uint32_t (*fram_command_send)(uint32_t ui32Cmd);
    am_devices_fireball_control_e fram_fireball_control;
} fram_device_func_t;

// Globals
// Buffer for non-blocking transactions for IOM - Needs to be big enough to accomodate
// all the transactions
uint32_t        g_IomQBuffer[3072];
// Buffer for non-blocking transactions for MSPI - Needs to be big enough to accomodate
// all the transactions
uint32_t        g_MspiQBuffer[2560];
// Temp Buffer in SRAM to read Flash data to, and write FRAM data from
uint32_t        g_TempBuf[2][TEMP_BUFFER_SIZE / 4];

void            *g_MSPIHdl;
void            *g_IOMHandle;
volatile bool   g_bDone = false;

const am_hal_mspi_dev_config_t      MSPI_Flash_Serial_CE0_MSPIConfig =
{
    .eSpiMode             = AM_HAL_MSPI_SPI_MODE_0,
    .eClockFreq           = AM_HAL_MSPI_CLK_24MHZ,
    .ui8TurnAround        = 3,
    .eAddrCfg             = AM_HAL_MSPI_ADDR_3_BYTE,
    .eInstrCfg            = AM_HAL_MSPI_INSTR_1_BYTE,
    .eDeviceConfig        = AM_HAL_MSPI_FLASH_SERIAL_CE0,
    .bSeparateIO          = true,
    .bSendInstr           = true,
    .bSendAddr            = true,
    .bTurnaround          = true,
    .ui8ReadInstr         = AM_DEVICES_MSPI_FLASH_FAST_READ,
    .ui8WriteInstr        = AM_DEVICES_MSPI_FLASH_PAGE_PROGRAM,
    .ui32TCBSize          = (sizeof(g_MspiQBuffer) / sizeof(uint32_t)),
    .pTCB                 = g_MspiQBuffer,
    .scramblingStartAddr  = 0,
    .scramblingEndAddr    = 0,
};

const am_hal_mspi_dev_config_t      MSPI_Flash_Quad_CE0_MSPIConfig =
{
  .eSpiMode             = AM_HAL_MSPI_SPI_MODE_0,
  .eClockFreq           = AM_HAL_MSPI_CLK_24MHZ,
#if defined(MICRON_N25Q256A)
  .ui8TurnAround        = 3,
#elif defined (CYPRESS_S25FS064S)
  .ui8TurnAround        = 5,
#endif
  .eAddrCfg             = AM_HAL_MSPI_ADDR_3_BYTE,
  .eInstrCfg            = AM_HAL_MSPI_INSTR_1_BYTE,
  .eDeviceConfig        = AM_HAL_MSPI_FLASH_QUAD_CE0,
  .bSeparateIO          = false,
  .bSendInstr           = true,
  .bSendAddr            = true,
  .bTurnaround          = true,
#if defined(MICRON_N25Q256A)
  .ui8ReadInstr         = AM_DEVICES_MSPI_FLASH_FAST_READ,
#elif defined (CYPRESS_S25FS064S)
  .ui8ReadInstr         = AM_DEVICES_MSPI_FLASH_QUAD_IO_READ,
#endif          // TODO - Flag an error if another part.
  .ui8WriteInstr        = AM_DEVICES_MSPI_FLASH_PAGE_PROGRAM,
  .ui32TCBSize          = (sizeof(g_MspiQBuffer) / sizeof(uint32_t)),
  .pTCB                 = g_MspiQBuffer,
  .scramblingStartAddr  = 0,
  .scramblingEndAddr    = 0,
};

am_hal_iom_config_t     g_sIomCfg =
{
    .eInterfaceMode       = FRAM_IOM_MODE,
    .ui32ClockFreq        = AM_HAL_IOM_24MHZ,
    .ui32NBTxnBufLength   = sizeof(g_IomQBuffer) / 4,
    .pNBTxnBuf            = g_IomQBuffer,
};

fram_device_func_t fram_func =
{
#if (FRAM_DEVICE_MB85RS1MT == 1)
    // Fireball installed SPI FRAM device
    .devName = "SPI FRAM MB85RS1MT",
    .fram_init = am_devices_mb85rs1mt_init,
    .fram_term = am_devices_mb85rs1mt_term,
    .fram_read_id = am_devices_mb85rs1mt_read_id,
    .fram_blocking_write = am_devices_mb85rs1mt_blocking_write,
    .fram_nonblocking_write = am_devices_mb85rs1mt_nonblocking_write,
    .fram_nonblocking_write_adv = am_devices_mb85rs1mt_nonblocking_write_adv,
    .fram_blocking_read = am_devices_mb85rs1mt_blocking_read,
    .fram_nonblocking_read = am_devices_mb85rs1mt_nonblocking_read,
    .fram_command_send = am_devices_mb85rs1mt_command_send,
#if FIREBALL_CARD
    .fram_fireball_control = AM_DEVICES_FIREBALL_STATE_SPI_FRAM,
#else
    .fram_fireball_control = 0,
#endif
#elif (FRAM_DEVICE_MB85RC256V == 1)
    .devName = "I2C FRAM MB85RC256V",
    .fram_init = am_devices_mb85rc256v_init,
    .fram_term = am_devices_mb85rc256v_term,
    .fram_read_id = am_devices_mb85rc256v_read_id,
    .fram_blocking_write = am_devices_mb85rc256v_blocking_write,
    .fram_nonblocking_write = am_devices_mb85rc256v_nonblocking_write,
    .fram_nonblocking_write_adv = am_devices_mb85rc256v_nonblocking_write_adv,
    .fram_blocking_read = am_devices_mb85rc256v_blocking_read,
    .fram_nonblocking_read = am_devices_mb85rc256v_nonblocking_read,
    .fram_command_send = am_devices_mb85rc256v_command_send,
    .fram_fireball_control = 0,
#elif (FRAM_DEVICE_MB85RS64V == 1)
    .devName = "SPI FRAM MB85RS64V",
    .fram_init = am_devices_mb85rs64v_init,
    .fram_term = am_devices_mb85rs64v_term,
    .fram_read_id = am_devices_mb85rs64v_read_id,
    .fram_blocking_write = am_devices_mb85rs64v_blocking_write,
    .fram_nonblocking_write = am_devices_mb85rs64v_nonblocking_write,
    .fram_nonblocking_write_adv = am_devices_mb85rs64v_nonblocking_write_adv,
    .fram_blocking_read = am_devices_mb85rs64v_blocking_read,
    .fram_nonblocking_read = am_devices_mb85rs64v_nonblocking_read,
    .fram_command_send = am_devices_mb85rs64v_command_send,
    .fram_fireball_control = 0,
#elif (FRAM_DEVICE_MB85RC64TA == 1)
    // Fireball installed I2C FRAM device
    .devName = "I2C FRAM MB85RC64TA",
    .fram_init = am_devices_mb85rc256v_init,
    .fram_term = am_devices_mb85rc256v_term,
    .fram_read_id = am_devices_mb85rc256v_read_id,
    .fram_blocking_write = am_devices_mb85rc256v_blocking_write,
    .fram_nonblocking_write = am_devices_mb85rc256v_nonblocking_write,
    .fram_nonblocking_write_adv = am_devices_mb85rc256v_nonblocking_write_adv,
    .fram_blocking_read = am_devices_mb85rc256v_blocking_read,
    .fram_nonblocking_read = am_devices_mb85rc256v_nonblocking_read,
    .fram_command_send = am_devices_mb85rc256v_command_send,
#if FIREBALL_CARD
    .fram_fireball_control = AM_DEVICES_FIREBALL_STATE_I2C_FRAM,
#else
    .fram_fireball_control = 0,
#endif
#else
#error "Unknown FRAM Device"
#endif
};

//*****************************************************************************
//
// IOM ISRs.
//
//*****************************************************************************
//
//! Take over default ISR. (Queue mode service)
//
void fram_iom_isr(void)
{
    uint32_t ui32Status;

    if (!am_hal_iom_interrupt_status_get(g_IOMHandle, true, &ui32Status))
    {
        if ( ui32Status )
        {
            am_hal_iom_interrupt_clear(g_IOMHandle, ui32Status);
            am_hal_iom_interrupt_service(g_IOMHandle, ui32Status);
        }
    }
}

int
fram_init(void)
{
    uint32_t ui32Status;
    uint32_t ui32DeviceId;

    // Set up IOM
    // Initialize the Device

#if FIREBALL_CARD
    uint32_t ui32Ret, ui32ID;

#if 1
    //
    // Get Fireball ID and Rev info.
    //
    ui32Ret = am_devices_fireball_control(AM_DEVICES_FIREBALL_STATE_ID_GET, &ui32ID);
    if ( ui32Ret != 0 )
    {
        DEBUG_PRINT("FAIL: am_devices_fireball_control(%d) returned 0x%X.\n",
                             AM_DEVICES_FIREBALL_STATE_ID_GET, ui32Ret);
        return -1;
    }
    else if ( ui32ID == FIREBALL_ID )
    {
        DEBUG_PRINT("Fireball found, ID is 0x%X.\n", ui32ID);
    }
    else
    {
        DEBUG_PRINT("Unknown device returned ID as 0x%X.\n", ui32ID);
    }

    ui32Ret = am_devices_fireball_control(AM_DEVICES_FIREBALL_STATE_VER_GET, &ui32ID);
    if ( ui32Ret != 0 )
    {
        DEBUG_PRINT("FAIL: am_devices_fireball_control(%d) returned 0x%X.\n",
                             AM_DEVICES_FIREBALL_STATE_VER_GET, ui32Ret);
        return -1;
    }
    else
    {
        DEBUG_PRINT("Fireball Version is 0x%X.\n", ui32ID);
    }
#endif

    if ( fram_func.fram_fireball_control != 0 )
    {
        ui32Ret = am_devices_fireball_control(fram_func.fram_fireball_control, 0);
        if ( ui32Ret != 0 )
        {
            DEBUG_PRINT("FAIL: am_devices_fireball_control(%d) returned 0x%X.\n",
                                 fram_func.fram_fireball_control, ui32Ret);
            return -1;
        }
    }
#endif // FIREBALL_CARD

    ui32Status = fram_func.fram_init(FRAM_IOM_MODULE, &g_sIomCfg, &g_IOMHandle);
    if (0 == ui32Status)
    {
        ui32Status = fram_func.fram_read_id(&ui32DeviceId);

        if ((ui32Status  != 0) || (ui32DeviceId != FRAM_DEVICE_ID))
        {
            return -1;
        }
        DEBUG_PRINT("%s Found\n", fram_func.devName);
    }
    else
    {
        return -1;
    }
    //
    // Enable the IOM interrupt in the NVIC.
    //
#if AM_CMSIS_REGS
    NVIC_EnableIRQ(FRAM_IOM_IRQn);
#else // AM_CMSIS_REGS
    am_hal_interrupt_enable(FRAM_IOM_INTERRUPT);
#endif // AM_CMSIS_REGS
    return 0;
}

int
fram_deinit(void)
{
    uint32_t ui32Status;

    //
    // Disable the IOM interrupt in the NVIC.
    //
#if AM_CMSIS_REGS
    NVIC_DisableIRQ(FRAM_IOM_IRQn);
#else // AM_CMSIS_REGS
    am_hal_interrupt_disable(FRAM_IOM_INTERRUPT);
#endif // AM_CMSIS_REGS

    // Set up IOM
    // Initialize the Device

    ui32Status = fram_func.fram_term(FRAM_IOM_MODULE);
    if (0 != ui32Status)
    {
        DEBUG_PRINT("Failed to terminate FRAM device\n");
        return -1;
    }
    return 0;
}

int
mspi_flash_init(const am_hal_mspi_dev_config_t *mspiFlashConfig)
{

    uint32_t      ui32Status;
#if FIREBALL_CARD // Set the fireball card for MSPI
    //
    // Set the MUX for the Flash Device
    //
    uint32_t ui32Ret, ui32ID;

#if 1
    //
    // Get Fireball ID and Rev info.
    //
    ui32Ret = am_devices_fireball_control(AM_DEVICES_FIREBALL_STATE_ID_GET, &ui32ID);
    if ( ui32Ret != 0 )
    {
        DEBUG_PRINT("FAIL: am_devices_fireball_control(%d) returned 0x%X.\n",
                             AM_DEVICES_FIREBALL_STATE_ID_GET, ui32Ret);
        return -1;
    }
    else if ( ui32ID == FIREBALL_ID )
    {
        DEBUG_PRINT("Fireball found, ID is 0x%X.\n", ui32ID);
    }
    else
    {
        DEBUG_PRINT("Unknown device returned ID as 0x%X.\n", ui32ID);
    }

    ui32Ret = am_devices_fireball_control(AM_DEVICES_FIREBALL_STATE_VER_GET, &ui32ID);
    if ( ui32Ret != 0 )
    {
        DEBUG_PRINT("FAIL: am_devices_fireball_control(%d) returned 0x%X.\n",
                             AM_DEVICES_FIREBALL_STATE_VER_GET, ui32Ret);
        return -1;
    }
    else
    {
        DEBUG_PRINT("Fireball Version is 0x%X.\n", ui32ID);
    }
#endif

    ui32Ret = am_devices_fireball_control(AM_DEVICES_FIREBALL_STATE_TWIN_QUAD_CE0_CE1, 0);
    if ( ui32Ret != 0 )
    {
        DEBUG_PRINT("FAIL: am_devices_fireball_control(%d) returned 0x%X.\n",
                             AM_DEVICES_FIREBALL_STATE_TWIN_QUAD_CE0_CE1, ui32Ret);
        return -1;
    }
#endif // FIREBALL_CARD

    //
    // Configure the MSPI and Flash Device.
    //
    ui32Status = am_devices_mspi_flash_init((am_hal_mspi_dev_config_t *)&MSPI_Flash_Quad_CE0_MSPIConfig, &g_MSPIHdl);
    if (AM_DEVICES_MSPI_FLASH_STATUS_SUCCESS != ui32Status)
    {
        DEBUG_PRINT("Failed to configure the MSPI and Flash Device correctly!\n");
        return -1;
    }

    //
    // Read the MSPI Device ID.
    //
    ui32Status = am_devices_mspi_flash_id();
    if (AM_DEVICES_MSPI_FLASH_STATUS_SUCCESS != ui32Status)
    {
        DEBUG_PRINT("Failed to read Flash Device ID!\n");
        return -1;
    }
    //
    // Make sure we aren't in XIP mode.
    //
    ui32Status = am_devices_mspi_flash_disable_xip();
    if (AM_DEVICES_MSPI_FLASH_STATUS_SUCCESS != ui32Status)
    {
        DEBUG_PRINT("Failed to disable XIP mode in the MSPI!\n");
        return -1;
    }
    return 0;
}

int
init_mspi_flash_data(void)
{
    uint32_t      ui32Status;

    // Initialize the flash (128K == SPI FRAM size) with the pattern data
    DEBUG_PRINT("Initiating mass erase Flash Device!\n");
    ui32Status = am_devices_mspi_flash_mass_erase();
    if (AM_DEVICES_MSPI_FLASH_STATUS_SUCCESS != ui32Status)
    {
        DEBUG_PRINT("Failed to mass erase Flash Device!\n");
        return -1;
    }
    DEBUG_PRINT("mass erase Flash Device Done!\n");
    DEBUG_PRINT("Writing a known pattern to flash!\n");
    for (uint32_t address = 0; address < BLOCK_SIZE; address += TEMP_BUFFER_SIZE)
    {
        //
        // Generate data into the Sector Buffer
        //
        for (uint32_t i = 0; i < TEMP_BUFFER_SIZE / 4; i++)
        {
            g_TempBuf[0][i] = address + i*4;
        }

        //
        // Write the TX buffer into the target sector.
        //
        ui32Status = am_devices_mspi_flash_write((uint8_t *)g_TempBuf[0], address, TEMP_BUFFER_SIZE);
        if (AM_DEVICES_MSPI_FLASH_STATUS_SUCCESS != ui32Status)
        {
            DEBUG_PRINT("Failed to write buffer to Flash Device!\n");
            return -1;
        }
        //
        // Read the data back into the RX buffer.
        //
        ui32Status = am_devices_mspi_flash_read((uint8_t *)g_TempBuf[1], address, TEMP_BUFFER_SIZE, true);
        if (AM_DEVICES_MSPI_FLASH_STATUS_SUCCESS != ui32Status)
        {
            DEBUG_PRINT("Failed to read buffer to Flash Device!\n");
        }

        //
        // Compare the buffers
        //
        for (uint32_t i = 0; i < TEMP_BUFFER_SIZE / 4; i++)
        {
            if (g_TempBuf[1][i] != g_TempBuf[0][i])
            {
                DEBUG_PRINT("TX and RX buffers failed to compare!\n");
                return -1;
            }
        }
    }
    return 0;
}

void
flash_read_complete(void *pCallbackCtxt, uint32_t transactionStatus)
{
    if (transactionStatus != AM_HAL_STATUS_SUCCESS)
    {
        DEBUG_PRINT("\nFlash Read Failed 0x%x\n", transactionStatus);
    }
    else
    {
        DEBUG_PRINT("\nFlash Read Done 0x%x\n", transactionStatus);
    }
}

void
fram_write_complete(void *pCallbackCtxt, uint32_t transactionStatus)
{
    if (transactionStatus != AM_HAL_STATUS_SUCCESS)
    {
        DEBUG_PRINT("\nFRAM Write Failed 0x%x\n", transactionStatus);
    }
    else
    {
        DEBUG_PRINT("\nFRAM Write Done 0x%x\n", transactionStatus);
        g_bDone = true;
    }
}


int
initiate_mspi_iom_xfer(void)
{
    uint32_t      ui32Status = 0;
    uint32_t u32Arg;

    // Clear flags
    u32Arg = 0x00FF0000;  // clear all flags

    am_hal_mspi_control(g_MSPIHdl, AM_HAL_MSPI_REQ_FLAG_SETCLR, &u32Arg);
    am_hal_iom_control(g_IOMHandle, AM_HAL_IOM_REQ_FLAG_SETCLR, &u32Arg);
    // Link MSPI and IOM
    u32Arg = FRAM_IOM_MODULE;
    am_hal_mspi_control(g_MSPIHdl, AM_HAL_MSPI_REQ_LINK_IOM, &u32Arg);

    DEBUG_PRINT("\nInitiating MSP -> IOM Transfer\n");
    // Queue up FRAM Writes and Flash Reads
    for (uint32_t address = 0, bufIdx = 0; address < BLOCK_SIZE; address += SPI_TXN_SIZE)
    {
        uint32_t bufOdd = bufIdx % 2;
        ui32Status = am_devices_mspi_flash_read_adv((uint8_t *)g_TempBuf[bufOdd], address,
                                       (((address + SPI_TXN_SIZE) >= BLOCK_SIZE) ? (BLOCK_SIZE - address) : SPI_TXN_SIZE),
                                       (bufOdd ? MSPI_WAIT_FOR_IOM_BUFFER1 : MSPI_WAIT_FOR_IOM_BUFFER0),
                                       (bufOdd ? MSPI_SIGNAL_IOM_BUFFER1 : MSPI_SIGNAL_IOM_BUFFER0),
                                       (((address + SPI_TXN_SIZE) >= BLOCK_SIZE) ? flash_read_complete : 0),
                                       0);
        if (ui32Status)
        {
            DEBUG_PRINT("\nFailed to queue up MSPI Read transaction\n");
            break;
        }
        ui32Status = fram_func.fram_nonblocking_write_adv((uint8_t *)g_TempBuf[bufOdd], address,
                                       (((address + SPI_TXN_SIZE) >= BLOCK_SIZE) ? (BLOCK_SIZE - address) : SPI_TXN_SIZE),
                                       (bufOdd ? IOM_WAIT_FOR_MSPI_BUFFER1 : IOM_WAIT_FOR_MSPI_BUFFER0),
                                       (bufOdd ? IOM_SIGNAL_MSPI_BUFFER1 : IOM_SIGNAL_MSPI_BUFFER0),
                                       (((address + SPI_TXN_SIZE) >= BLOCK_SIZE) ? fram_write_complete : 0),
                                       0);
        bufIdx++;
        if (ui32Status)
        {
            DEBUG_PRINT("\nFailed to queue up SPI Write transaction\n");
             break;
        }
    }
    return ui32Status;
}

#if 0
bool g_bFramWriteComplete = 0;
void
fram_write_complete(void *pCallbackCtxt, uint32_t transactionStatus)
{
    if (transactionStatus != AM_HAL_STATUS_SUCCESS)
    {
        DEBUG_PRINT("\nFRAM Write Failed 0x%x\n", transactionStatus);
    }
    else
    {
        g_bFramWriteComplete = true;
    }
}

int
init_fram_data(void)
{
    uint32_t      ui32Status;
#if 0
    // Set the FRAM in write mode
    // Send the WRITE ENABLE command to enable writing.
    //
    if (am_devices_mb85rs1mt_command_send(AM_DEVICES_MB85RS1MT_WRITE_ENABLE))
    {
        return AM_DEVICES_MB85RS1MT_STATUS_ERROR;
    }
#endif

    // Verify FRAM data
    for (uint32_t address = 0; address < (BLOCK_SIZE); address += SPI_TXN_SIZE)
    {
        uint32_t numBytes = (((address + SPI_TXN_SIZE) >= BLOCK_SIZE) ? (BLOCK_SIZE - address) : SPI_TXN_SIZE);
        //
        // Generate data into the Sector Buffer
        //
        for (uint32_t i = 0; i < numBytes/4; i++)
        {
            g_TempBuf[0][i] = address + i*4;
        }

        g_bFramWriteComplete = 0;
        //
        // Write the TX buffer into the target sector.
        //
        DEBUG_PRINT("Writing %d Bytes to Address 0x%x\n", address);
        ui32Status = fram_func.fram_nonblocking_write_adv((uint8_t *)g_TempBuf[0], address, numBytes,
                                       0,
                                       0,
                                       fram_write_complete,
                                       0);
        if (ui32Status)
        {
            DEBUG_PRINT("Failed to write FRAM!\n");
             return -1;
        }
        while (!g_bFramWriteComplete);
    }
    // Wait for writes to finish
    for (uint32_t address = 0; address < (BLOCK_SIZE); address += SPI_TXN_SIZE)
    {
        uint32_t numBytes = (((address + SPI_TXN_SIZE) >= BLOCK_SIZE) ? (BLOCK_SIZE - address) : SPI_TXN_SIZE);
        //
        // Read the data back into the RX buffer.
        //
        DEBUG_PRINT("Read %d Bytes from Address 0x%x\n", numBytes, address);
        // Initiate read of a block of data from FRAM
        ui32Status = fram_func.fram_blocking_read((uint8_t *)&g_TempBuf[1], address, numBytes);

        if (0 != ui32Status)
        {
            DEBUG_PRINT("Failed to read FRAM!\n");
            return -1;
        }

        //
        // Compare the buffers
        //
        DEBUG_PRINT("Comparing the TX and RX Buffers\n");
        for (uint32_t i = 0; i < numBytes/4; i++)
        {
            if (g_TempBuf[1][i] != (address + i*4))
            {
                DEBUG_PRINT("TX and RX buffers failed to compare!\n");
                return -1;
            }
        }
    }
    return 0;
}
#endif


#ifdef VERIFY_DATA
int
verify_fram_data(void)
{
    uint32_t      ui32Status;

    // Verify FRAM data
    for (uint32_t address = 0; address < (BLOCK_SIZE); address += SPI_TXN_SIZE)
    {
        uint32_t numBytes = (((address + SPI_TXN_SIZE) >= BLOCK_SIZE) ? (BLOCK_SIZE - address) : SPI_TXN_SIZE);
        //
        // Read the data back into the RX buffer.
        //
        // Initiate read of a block of data from FRAM
        ui32Status = fram_func.fram_blocking_read((uint8_t *)&g_TempBuf[1], address, numBytes);

        if (0 != ui32Status)
        {
            DEBUG_PRINT("Failed to read FRAM!\n");
            return -1;
        }

        //
        // Compare the buffers
        //
        for (uint32_t i = 0; i < numBytes / 4; i++)
        {
            if (g_TempBuf[1][i] != address + i*4)
            {
                DEBUG_PRINT("TX and RX buffers failed to compare!\n");
                return -1;
            }
        }
    }
    DEBUG_PRINT("FRAM data matches the expectation\n");
    return 0;
}
#endif

//*****************************************************************************
//
// MSPI Example Main.
//
//*****************************************************************************
int
main(void)
{
    uint32_t      ui32Status;
    int iRet;
    uint32_t      numIter = 0;
    const am_hal_mspi_dev_config_t *mspiFlashCfg =
#ifdef MSPI_FLASH_SERIAL
            &MSPI_Flash_Serial_CE0_MSPIConfig;
#else
            &MSPI_Flash_Quad_CE0_MSPIConfig;
#endif

    //
    // Set the clock frequency.
    //
    am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_SYSCLK_MAX, 0);

    //
    // Set the default cache configuration
    //
    //am_hal_cachectrl_config(&am_hal_cachectrl_defaults);
    //am_hal_cachectrl_enable();

    //
    // Configure the board for low power operation.
    //
    am_bsp_low_power_init();

#ifdef ENABLE_LOGGING
#if 0
    //
    // Initialize the printf interface for UART output.
    //
    am_bsp_uart_printf_enable();
#else
    //
    // Initialize the ITM printf interface.
    //
    am_bsp_itm_printf_enable();
#endif
    //
    // Print the banner.
    //
    am_util_stdio_terminal_clear();
#endif

#ifdef CPU_SLEEP_GPIO
    // GPIO used to track the CPU sleeping
    am_hal_gpio_state_write(CPU_SLEEP_GPIO, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_pinconfig(CPU_SLEEP_GPIO, g_AM_HAL_GPIO_OUTPUT);
#endif

    // Initialize the MSPI Flash
    iRet = mspi_flash_init(mspiFlashCfg);
    if (iRet)
    {
        DEBUG_PRINT("Unable to initialize MSPI Flash\n");
        while(1);
    }
    // Initialize the IOM FRAM
    iRet = fram_init();
    if (iRet)
    {
        DEBUG_PRINT("Unable to initialize FRAM\n");
        while(1);
    }

#if 0
    // Initialize FRAM Data
    iRet = init_fram_data();
    if (iRet)
    {
        DEBUG_PRINT("Unable to initialize FRAM data\n");
        while(1);
    }
#endif

    // Initialize Flash Data
    iRet = init_mspi_flash_data();
    if (iRet)
    {
        DEBUG_PRINT("Unable to initialize MSPI Flash data\n");
        while(1);
    }

    am_hal_interrupt_master_enable();

    iRet = initiate_mspi_iom_xfer();
    if (iRet)
    {
        DEBUG_PRINT("Unable to initiate MSPI IOM transfer\n");
        while(1);
    }
    numIter++;

    DEBUG_PRINT("Getting into Wait Loop\n");

    //
    // Loop forever.
    //
    while(1)
    {
        //
        // Disable interrupt while we decide whether we're going to sleep.
        //
        uint32_t ui32IntStatus = am_hal_interrupt_master_disable();

        if (!g_bDone)
        {
#ifdef CPU_SLEEP_GPIO
            am_hal_gpio_state_write(CPU_SLEEP_GPIO, AM_HAL_GPIO_OUTPUT_SET);
            am_hal_sysctrl_sleep(true);
            am_hal_gpio_state_write(CPU_SLEEP_GPIO, AM_HAL_GPIO_OUTPUT_CLEAR);
#else
            am_hal_sysctrl_sleep(true);
#endif // CPU_SLEEP_GPIO

            //
            // Enable interrupts
            //
            am_hal_interrupt_master_set(ui32IntStatus);
        }
        else if (g_bDone)
        {
            //
            // Enable interrupts
            //
            am_hal_interrupt_master_set(ui32IntStatus);
            g_bDone = false;
#ifdef VERIFY_DATA
            if (verify_fram_data())
            {
                DEBUG_PRINT("Verify data failed!\n");
                break;
            }
#endif
            if (numIter++ < NUM_INERATIONS)
            {
                iRet = initiate_mspi_iom_xfer();
                if (iRet)
                {
                    DEBUG_PRINT("Unable to initiate MSPI IOM transfer\n");
                    while(1);
                }
            }
            else
            {
                break;
            }
        }
    }

    //
    // Clean up the FRAM before exit.
    //
    iRet = fram_deinit();
    if (iRet)
    {
        DEBUG_PRINT("Unable to terminate FRAM\n");
    }

    //
    // Clean up the MSPI before exit.
    //
    ui32Status = am_devices_mspi_flash_deinit((am_hal_mspi_dev_config_t *)mspiFlashCfg);
    if (AM_DEVICES_MSPI_FLASH_STATUS_SUCCESS != ui32Status)
    {
        DEBUG_PRINT("Failed to shutdown the MSPI and Flash Device!\n");
    }

    //
    //  End banner.
    //
    DEBUG_PRINT("Apollo3 MSPI-IOM Transfer Example Complete\n");

    //
    // Loop forever while sleeping.
    //
    while (1)
    {
        //
        // Go to Deep Sleep.
        //
        am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_DEEP);
    }
}
