//*****************************************************************************
//
//! @file hci_drv_apollo3.c
//!
//! @brief HCI driver interface.
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

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "am_mcu_apollo.h"
#include "am_util.h"
#include "hci_drv_apollo3.h"
#include "hci_drv_internal.h"
#include "FreeRTOSConfig.h"

//*****************************************************************************
//
// Global variables.
//
//*****************************************************************************

// BLE module handle
void *BLE;

// Buffers for reading/writing data.
#define HCI_DRV_MAX_TX_PACKET           256
#define HCI_DRV_MAX_RX_PACKET           256

DECL_STATIC uint8_t g_pui32ReadBuffer[HCI_DRV_MAX_RX_PACKET];
DECL_STATIC uint8_t g_pui8WriteBuffer[HCI_DRV_MAX_TX_PACKET];
DECL_STATIC UINT16  g_pui8WriteBuffer_len;

//fixme: set the BLE MAC address to a special value
uint8_t g_BLEMacAddress[6] = {0x01,0x02,0x03,0x04,0x05,0x06};

//*****************************************************************************
//
// Error Checking Function.
//
//*****************************************************************************
#ifndef NO_ERRORS

volatile uint32_t g_ui32FailingStatus = 0;

#define ERROR_CHECK(expr)                                                     \
    g_ui32FailingStatus = (expr);                                             \
    if (g_ui32FailingStatus != AM_HAL_STATUS_SUCCESS)                         \
    {                                                                         \
        while (1);                                                            \
    }

#else

#define ERROR_CHECK(expr)

#endif

#if AM_CMSIS_REGS

#define BLE_IRQ_CHECK()             (BLEIF->BSTATUS_b.BLEIRQ)

#else // AM_CMSIS_REGS

#define BLE_IRQ_CHECK()             (AM_BFR(BLEIF, BSTATUS, BLEIRQ))

#endif // AM_CMSIS_REGS


//*****************************************************************************
//
// Forward declarations.
//
//*****************************************************************************

void hci_spi_bt_shutdown (void);

#ifdef BT_SPI

#include "am_util.h"
#include "hci_apollo_config.h"

#ifndef HCI_APOLLO_MAC
#define HCI_APOLLO_MAC                  {0x01, 0x00, 0x00, 0xEE, 0xF3, 0x0C}
#endif

#ifndef HCI_APOLLO_USE_CHIPID_FOR_MAC
#define HCI_APOLLO_USE_CHIPID_FOR_MAC   true
#endif

DECL_STATIC BT_THREAD_RETURN_TYPE hci_spi_read_task (BT_THREAD_ARGS args);


/* ----------------------------------------- External Global Variables */
void hci_transport_enqueue (UCHAR * data, UINT16 datalen);

/* ----------------------------------------- Exported Global Variables */


/* ----------------------------------------- Static Global Variables */

/* SPI Read Task State */
DECL_STATIC UCHAR hci_spi_state;
/* SPI Read Task Synchronization */
BT_DEFINE_MUTEX (hci_spi_mutex)
BT_DEFINE_COND (hci_spi_cond)

/* ----------------------------------------- Functions */

/** HCI-SPI Initialization */
void hci_spi_init (void)
{
    BT_thread_type tid;

    BT_MUTEX_INIT_VOID (hci_spi_mutex, TRANSPORT);
    BT_COND_INIT_VOID(hci_spi_cond, TRANSPORT);

    /* Initialize SPI State */
    hci_spi_state = 0x0;

    /* Create a thread to receive data From Serial PORT and BUFFER it */
    if (0 != BT_thread_create(&tid, NULL, hci_spi_read_task, NULL))
    {
        HCI_SPI_ERR(
        "[HCI-SPI] Could NOT Create SPI Read Thread\n");

        return;
    }


    HCI_SPI_TRC(
    "[HCI-SPI] SPI Power On Initialization Complete\n");

    return;
}

/** HCI-SPI Bluetooth-ON Initialization */
void hci_spi_bt_init(void)
{
    //
    hci_spi_lock (hci_spi_mutex);
    hci_spi_state = 0x1;
    hci_spi_signal (hci_spi_cond);
    hci_spi_unlock (hci_spi_mutex);


#if !defined(AM_DEBUG_BLE_TIMING) && defined(ELLISYS_HCI_LOG_SUPPORT)
    am_hal_gpio_pincfg_t pincfg = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    pincfg.uFuncSel = 6;
    am_hal_gpio_pinconfig(30, pincfg);
    am_hal_gpio_pinconfig(31, pincfg);
    am_hal_gpio_pinconfig(32, pincfg);
    pincfg.uFuncSel = 4;
    am_hal_gpio_pinconfig(33, pincfg);
    pincfg.uFuncSel = 7;
    am_hal_gpio_pinconfig(35, pincfg);
#endif

#ifdef AM_DEBUG_BLE_TIMING
    //
    // Enable debug pins.
    //
    // 30.6 - SCLK
    // 31.6 - MISO
    // 32.6 - MOSI
    // 33.4 - CSN
    // 35.7 - SPI_STATUS
    //
#if AM_APOLLO3_GPIO
    am_hal_gpio_pincfg_t pincfg = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    pincfg.uFuncSel = 6;
    am_hal_gpio_pinconfig(30, pincfg);
    am_hal_gpio_pinconfig(31, pincfg);
    am_hal_gpio_pinconfig(32, pincfg);
    pincfg.uFuncSel = 4;
    am_hal_gpio_pinconfig(33, pincfg);
    pincfg.uFuncSel = 7;
    am_hal_gpio_pinconfig(35, pincfg);
    pincfg.uFuncSel = 1;
    am_hal_gpio_pinconfig(41, pincfg);

    am_hal_debug_gpio_pinconfig(BLE_DEBUG_TRACE_08);

#else
    am_hal_gpio_pin_config(30, AM_HAL_GPIO_FUNC(6));
    am_hal_gpio_pin_config(31, AM_HAL_GPIO_FUNC(6));
    am_hal_gpio_pin_config(32, AM_HAL_GPIO_FUNC(6));
    am_hal_gpio_pin_config(33, AM_HAL_GPIO_FUNC(4));
    am_hal_gpio_pin_config(35, AM_HAL_GPIO_FUNC(7));
#endif // AM_APOLLO3_GPIO
#endif // AM_DEBUG_BLE_TIMING

    //
    // This pin is also used to generate BLE interrupts in the current
    // implementation.
    //
    // 41.1 - BLE IRQ
    //
    //am_hal_gpio_pin_config(41, AM_HAL_GPIO_FUNC(1));


#if AM_CMSIS_REGS
    NVIC_SetPriority(BLE_IRQn, NVIC_configMAX_SYSCALL_INTERRUPT_PRIORITY);
#else // AM_CMSIS_REGS
    am_hal_interrupt_priority_set(AM_HAL_INTERRUPT_BLE, configMAX_SYSCALL_INTERRUPT_PRIORITY);
#endif // AM_CMSIS_REGS

ResetBLE:

    //
    // Configure and enable the BLE interface.
    //
    ERROR_CHECK(am_hal_ble_initialize(0, &BLE));
    ERROR_CHECK(am_hal_ble_power_control(BLE, AM_HAL_BLE_POWER_ACTIVE));

    am_hal_ble_config_t sBleConfig =
    {
#if AM_CMSIS_REGS
        // Clock divider of 8.
        (_VAL2FLD(BLEIF_CLKCFG_FSEL, BLEIF_CLKCFG_FSEL_HFRC_DIV8)   |
         _VAL2FLD(BLEIF_CLKCFG_IOCLKEN, 1)                          |
         _VAL2FLD(BLEIF_CLKCFG_CLK32KEN, 1)),
#else // AM_CMSIS_REGS
        // Clock divider of 8.
        (AM_REG_BLEIF_CLKCFG_FSEL_HFRC_DIV8 |
         AM_REG_BLEIF_CLKCFG_IOCLKEN(1) |
         AM_REG_BLEIF_CLKCFG_CLK32KEN(1)),
#endif // AM_CMSIS_REGS

        // Read threshold of 16.
        0x10,

        // Write threshold of 16.
        0x10,
    };

    ERROR_CHECK(am_hal_ble_config(BLE, &sBleConfig));

    /*delay 1s for 32768Hz clock stability*/
    am_util_delay_ms(1000);

    // Set default trim data before apply patch  // for test
    am_hal_ble_default_trim_set_ramcode(BLE);

    //
    // Apply any necessary patches here.
    //
    //
    // To apply a new patch:
    // 1. Update the /mcu/apollo3/hal/am_hal_ble_patch.c
    // 2. Rebuild the /mcu/apollo3/hal projects.
    // 3. Uncomment the next line and rebuild this project.
    ERROR_CHECK(am_hal_ble_default_patch_apply(BLE));

    //
    // Signal to the BLE core that patching is complete.
    //
    ERROR_CHECK(am_hal_ble_patch_complete(BLE));

    // Check whether BLE controller can detect 32768Hz clock is stable.
    if (am_hal_ble_check_32k_clock(BLE) == AM_HAL_STATUS_FAIL)
    {
        hci_spi_bt_shutdown();
        am_util_delay_ms(1000);
        goto ResetBLE;
    }

    //
    // Enable interrupts for the BLE module.
    //
#if AM_CMSIS_REGS
    am_hal_ble_int_clear(BLE, (BLEIF_INTEN_CMDCMP_Msk   |
                               BLEIF_INTEN_BLECIRQ_Msk  |
                               BLEIF_INTEN_DCMP_Msk));

    am_hal_ble_int_enable(BLE, (BLEIF_INTEN_CMDCMP_Msk  |
                                BLEIF_INTEN_BLECIRQ_Msk |
                                BLEIF_INTEN_DCMP_Msk));
#else // AM_CMSIS_REGS
    am_hal_ble_int_clear(BLE, (AM_REG_BLEIF_INTEN_CMDCMP_M |
                               AM_REG_BLEIF_INTEN_BLECIRQ_M |
                               AM_REG_BLEIF_INTEN_DCMP_M));

    am_hal_ble_int_enable(BLE, (AM_REG_BLEIF_INTEN_CMDCMP_M |
                                AM_REG_BLEIF_INTEN_BLECIRQ_M |
                                AM_REG_BLEIF_INTEN_DCMP_M));
#endif // AM_CMSIS_REGS

#if AM_CMSIS_REGS
    NVIC_EnableIRQ(BLE_IRQn);
#else // AM_CMSIS_REGS
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_BLE);
#endif // AM_CMSIS_REGS

	// heartbeat timer

    return;
}


/** HCI-SPI Bluetooth-OFF Shutdown */
void hci_spi_bt_shutdown (void)
{
#if AM_CMSIS_REGS
    NVIC_DisableIRQ(BLE_IRQn);
#else // AM_CMSIS_REGS
    am_hal_interrupt_disable(AM_HAL_INTERRUPT_BLE);
#endif // AM_CMSIS_REGS

    ERROR_CHECK(am_hal_ble_power_control(BLE, AM_HAL_BLE_POWER_OFF));

#if AM_CMSIS_REGS
    while( PWRCTRL->DEVPWREN_b.PWRBLEL );
#else // AM_CMSIS_REGS
    while ( AM_BFM(PWRCTRL, DEVPWREN, PWRBLEL) );
#endif // AM_CMSIS_REGS

    ERROR_CHECK(am_hal_ble_deinitialize(BLE));

   /* Signal SPI Read Task */
    hci_spi_lock (hci_spi_mutex);
    hci_spi_state = 0x0;
    hci_spi_unlock (hci_spi_mutex);
}


//*****************************************************************************
//
//
// This handler can perform HCI reads or writes, and keeps the actions in the
// correct order.
//
//*****************************************************************************

void
HciDrvReadWriteHandler(uint8_t hci_type, uint8_t * hci_sendbuf, uint32_t hci_sendbuf_len)
{
    uint32_t ui32ErrorStatus;

    am_hal_debug_gpio_set(BLE_DEBUG_TRACE_01);

    //
    // Loop indefinitely, checking to see if there are still tranfsers we need
    // to complete.
    //
    while (1)
    {
        //
        // Figure out what kind of transfer the BLE core will accept.
        //
        if ( BLE_IRQ_CHECK() )
        {
            am_hal_debug_gpio_set(BLE_DEBUG_TRACE_02);

            //
            // Is the BLE core asking for a read? If so, do that now.
            //
            uint32_t ui32NumBytes = 0;
            ui32ErrorStatus = am_hal_ble_blocking_hci_read(BLE, (uint32_t*)g_pui32ReadBuffer, &ui32NumBytes);

            if (ui32NumBytes > HCI_DRV_MAX_RX_PACKET)
            {
                am_util_debug_printf("ERROR: Trying to receive an HCI packet larger than the hci driver buffer size (needs %d bytes of space).",
                                     ui32NumBytes);
                while (1);
            }


            if ( ui32ErrorStatus == AM_HAL_STATUS_SUCCESS)
            {
                //
                // If the read succeeded, we need to wait for the IRQ signal to
                // go back down. If we don't we might inadvertently try to read
                // the same packet twice.
                //
                while ( BLE_IRQ_CHECK() );

                //
                // Pass the data along to the stack. The stack should be able
                // to read as much data as we send it.  If it can't, we need to
                // know that.
                //

                hci_transport_enqueue ((uint8_t *)g_pui32ReadBuffer, (UINT16)ui32NumBytes);

            }
            else
            {
                //
                // If the read didn't succeed for some physical reason, we need
                // to know. We shouldn't get failures here. We checked the IRQ
                // signal before calling the read function, and this driver
                // only contains a single call to the blocking read function,
                // so there shouldn't be any physical reason for the read to
                // fail.
                //
                am_util_debug_printf("HCI READ failed with status %d. Try recording with a logic analyzer to catch the error.\n",
                                     ui32ErrorStatus);
                while (1);
            }

            am_hal_debug_gpio_clear(BLE_DEBUG_TRACE_02);

        }
        else
        {
            //
            // If we don't have anything to read, we can start checking to see
            // if we have things to write.
            //
            if (hci_sendbuf == NULL)
            {
                //
                // If not, we're done!
                //
                break;
            }
            else
            {
                //
                // If we do have something to write, just pop a single item
                // from the queue and send it.
                //
                am_hal_debug_gpio_set(BLE_DEBUG_TRACE_07);

                ui32ErrorStatus = am_hal_ble_blocking_hci_write(BLE,
                                                                hci_type,
                                                                (uint32_t *)hci_sendbuf,
                                                                hci_sendbuf_len);


                if (ui32ErrorStatus == AM_HAL_STATUS_SUCCESS)
                {
                    // mark it so that we can exit in next loop.
                    hci_sendbuf = NULL;
                }

                am_hal_debug_gpio_clear(BLE_DEBUG_TRACE_07);
            }
        }

    }

    am_hal_debug_gpio_clear(BLE_DEBUG_TRACE_01);
}

/** HCI-SPI Read Task */
DECL_STATIC BT_THREAD_RETURN_TYPE hci_spi_read_task (BT_THREAD_ARGS args)
{
    BT_LOOP_FOREVER()
    {
        hci_spi_lock (hci_spi_mutex);

        if ( 0x1 == hci_spi_state)
        {
            HCI_SPI_TRC(
            "[HCI-SPI] SPI Read Task: Waiting to Service ..\n");

            hci_spi_wait (hci_spi_cond, hci_spi_mutex);

            HCI_SPI_TRC(
            "[HCI-SPI] SPI Read Task: Ready to Service ..\n");

            HciDrvReadWriteHandler(0, NULL, 0);
        }

        hci_spi_unlock (hci_spi_mutex);
    }

    return API_SUCCESS;
}

/** HCI-SPI Send Data */
API_RESULT hci_spi_send_data
           (UCHAR type, UCHAR * buf, UINT16 length, UCHAR flag)
{
    // HCI command is sent as a complete packet from Mindtree stack
    if(type == HCI_COMMAND_PACKET) {
        hci_spi_lock (hci_spi_mutex);

        HciDrvReadWriteHandler(type, buf, length);

#ifdef AM_CUSTOM_BDADDR

        uint16_t opcode;
        hci_unpack_2_byte_param(&opcode, buf);

        if (HCI_RESET_OPCODE == opcode) {

            am_hal_mcuctrl_device_t sDevice;
            am_hal_mcuctrl_info_get(AM_HAL_MCUCTRL_INFO_DEVICEID, &sDevice);

            g_BLEMacAddress[0] = sDevice.ui32ChipID0;
            g_BLEMacAddress[1] = sDevice.ui32ChipID0 >> 8;
            g_BLEMacAddress[2] = sDevice.ui32ChipID0 >> 16;

            HciVsA3_SetBDAddr(g_BLEMacAddress);
        }
#endif
        hci_spi_unlock (hci_spi_mutex);
    }
    else {
        // HCI ACL packet is sent in at least three fragments
        if(flag == 1) {
            // beginning of HCI packet header
            BT_mem_copy(g_pui8WriteBuffer, buf, length);
            g_pui8WriteBuffer_len = length;
        }
        else {
            // L2CAP header and payload are sent seperately
            BT_mem_copy(g_pui8WriteBuffer + g_pui8WriteBuffer_len, buf, length);
            g_pui8WriteBuffer_len += length;
        }

        // Check if a complete HCI ACL packet is received.
        if ((g_pui8WriteBuffer_len - 4) < (g_pui8WriteBuffer[2] + (g_pui8WriteBuffer[3] << 8))) {
            return API_SUCCESS;
        }

        hci_spi_lock (hci_spi_mutex);

        HciDrvReadWriteHandler(type, g_pui8WriteBuffer, g_pui8WriteBuffer_len);

        hci_spi_unlock (hci_spi_mutex);

    }

    return API_SUCCESS;
}

//*****************************************************************************
//
// Interrupt handler for BLE
//
//*****************************************************************************
void
am_ble_isr(void)
{

    BaseType_t xHigherPriorityTaskWoken;

    xHigherPriorityTaskWoken = pdFALSE;

    uint32_t ui32Status = am_hal_ble_int_status(BLE, true);

    am_hal_ble_int_clear(BLE, ui32Status);

    // Send an event to the HCI Read Task.
    //
    xSemaphoreGiveFromISR(hci_spi_cond,&xHigherPriorityTaskWoken);

    //
    // If the GPS task is higher-priority than the context we're currently
    // running from, we should yield now and run the radio task.
    //
    if (xHigherPriorityTaskWoken != pdFAIL)
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }

}

/*************************************************************************************************/
/*!
 *  \fn     HciVsA3_SetRfPowerLevelEx
 *
 *  \brief  Vendor-specific command for settting Radio transmit power level
 *          for Nationz.
 *
 *  \param  txPowerlevel    valid range from 0 to 15 in decimal.
 *
 *  \return true when success, otherwise false
 */
/*************************************************************************************************/
bool HciVsA3_SetRfPowerLevelEx(txPowerLevel_t txPowerlevel)
{
    // make sure it's 8 bit
    uint8_t set_tx_power[3];

    set_tx_power[0] = set_tx_power[1] = 0;
    set_tx_power[2] = txPowerlevel;

    if ( txPowerlevel < TX_POWER_LEVEL_INVALID )
    {
        BT_hci_vendor_specific_command(0xFC3B, &set_tx_power[0], sizeof(set_tx_power));
        return true;
    }
    else
    {
        return false;
    }
}

/*************************************************************************************************/
/*!
 *  \fn     HciVsA3_SetBDAddr
 *
 *  \brief  Vendor-specific command for setting Bluetooth device address.
 *
 *  \param  pointer to supplied BD address.
 *
 *  \return true when success, otherwise false
 */
/*************************************************************************************************/
void HciVsA3_SetBDAddr(uint8_t *bd_addr)
{
    BT_hci_vendor_specific_command(0xFC32, &bd_addr[0], 6);
}

#endif /* BT_SPI */
