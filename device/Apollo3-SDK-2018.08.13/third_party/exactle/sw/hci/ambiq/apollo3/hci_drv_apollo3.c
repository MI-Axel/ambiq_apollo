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

#include "wsf_types.h"
#include "wsf_timer.h"
#include "bstream.h"
#include "wsf_msg.h"
#include "wsf_cs.h"
#include "hci_drv.h"
#include "hci_drv_apollo.h"
#include "hci_tr_apollo.h"
#include "hci_core.h"
#include "dm_api.h"

#include "am_mcu_apollo.h"
#include "am_util.h"
#include "hci_drv_apollo3.h"

#include <string.h>

//*****************************************************************************
//
// Configurable buffer sizes.
//
//*****************************************************************************
#define NUM_HCI_WRITE_BUFFERS           8
#define HCI_DRV_MAX_TX_PACKET           256
#define HCI_DRV_MAX_RX_PACKET           256

//*****************************************************************************
//
// Configurable error-detection thresholds.
//
//*****************************************************************************
#define HEARTBEAT_TIMEOUT_MS            (10000)   //milli-seconds
#define HCI_DRV_MAX_IRQ_TIMEOUT          100000
#define HCI_DRV_MAX_XTAL_RETRIES         10
#define HCI_DRV_MAX_TX_RETRIES           10000
#define HCI_DRV_MAX_HCI_TRANSACTIONS     10000
#define HCI_DRV_MAX_READ_PACKET          4   // max read in a row at a time

//*****************************************************************************
//
// Structure for holding outgoing HCI packets.
//
//*****************************************************************************
typedef struct
{
    uint32_t ui32Length;
    uint8_t  pui32Data[HCI_DRV_MAX_TX_PACKET];
}
hci_drv_write_t;

//*****************************************************************************
//
// Global variables.
//
//*****************************************************************************

// BLE module handle
void *BLE;

//fixme: set the BLE MAC address to a special value
uint8_t g_BLEMacAddress[6] = {0x01,0x02,0x03,0x04,0x05,0x06};

// Global handle used to send BLE events about the Hci driver layer.
wsfHandlerId_t g_HciDrvHandleID = 0;
wsfTimer_t     g_HeartBeatTimer;

// Buffers for HCI data.
hci_drv_write_t g_psWriteBuffers[NUM_HCI_WRITE_BUFFERS];
am_hal_queue_t g_sWriteQueue;
uint8_t g_pui32ReadBuffer[HCI_DRV_MAX_RX_PACKET];
uint8_t     g_pui32ReadBuffer[HCI_DRV_MAX_RX_PACKET];
uint32_t    g_ui32NumBytes   = 0;
uint32_t    g_consumed_bytes = 0;

// Counters for tracking read data.
volatile uint32_t g_ui32InterruptsSeen = 0;

//*****************************************************************************
//
// Events for the HCI driver interface.
//
//*****************************************************************************
#define BLE_TRANSFER_NEEDED_EVENT                   0x01
#define BLE_HEARTBEAT_EVENT                         0x02

//*****************************************************************************
//
// Error-handling wrapper macro.
//
//*****************************************************************************
#define ERROR_CHECK_VOID(status)                                              \
    if ((status))                                                             \
    {                                                                         \
        error_check(status);                                                  \
        return;                                                               \
    }

#define ERROR_RETURN(status, retval)                                          \
    if ((status))                                                             \
    {                                                                         \
        error_check(status);                                                  \
        return (retval);                                                      \
    }

#define ERROR_RECOVER(status)                                                 \
    if ((status))                                                             \
    {                                                                         \
        am_hal_debug_gpio_toggle(BLE_DEBUG_TRACE_10);                         \
        error_check(status);                                                  \
        HciDrvRadioShutdown();                                                \
        HciDrvRadioBoot(0);                                                   \
        DmDevReset();                                                         \
        return;                                                               \
    }

//*****************************************************************************
//
// Function pointer for redirecting errors
//
//*****************************************************************************
hci_drv_error_handler_t g_hciDrvErrorHandler = 0;
static uint32_t g_ui32FailingStatus = 0;

//*****************************************************************************
//
// By default, errors will be printed. If there is an error handler defined,
// they will be sent there intead.
//
//*****************************************************************************
static void
error_check(uint32_t ui32Status)
{
    //
    // Don't do anything unless there's an error.
    //
    if (ui32Status)
    {
        //
        // Set the global error status. If there's an error handler function,
        // call it. Otherwise, just print the error status and wait.
        //
        g_ui32FailingStatus = ui32Status;

        if (g_hciDrvErrorHandler)
        {
            g_hciDrvErrorHandler(ui32Status);
        }
        else
        {
            am_util_debug_printf("Error detected: 0x%08x\n", g_ui32FailingStatus);
#if AM_CMSIS_REGS
            am_util_debug_printf("BSTATUS: 0x%08x\n", BLEIF->BSTATUS);
#else // AM_CMSIS_REGS
            am_util_debug_printf("BSTATUS: 0x%08x\n", AM_REG(BLEIF, BSTATUS));
#endif // AM_CMSIS_REGS
        }
    }
}

//*****************************************************************************
//
// Other useful macros.
//
//*****************************************************************************
#if AM_CMSIS_REGS

#define BLE_IRQ_CHECK()             (BLEIF->BSTATUS_b.BLEIRQ)

#else // AM_CMSIS_REGS

#define BLE_IRQ_CHECK()             (AM_BFR(BLEIF, BSTATUS, BLEIRQ))

#endif // AM_CMSIS_REGS

// Ellisys HCI SPI tapping support

// #define ELLISYS_HCI_LOG_SUPPORT 1

//*****************************************************************************
//
// Boot the radio.
//
//*****************************************************************************
void
HciDrvRadioBoot(uint32_t ui32Module)
{
    uint32_t ui32NumXtalRetries = 0;

    g_ui32NumBytes     = 0;
    g_consumed_bytes   = 0;
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
    //am_hal_gpio_pinconfig(41, pincfg);
    //am_hal_debug_gpio_pinconfig(BLE_DEBUG_TRACE_08);

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


ResetBLE:

    //
    // Configure and enable the BLE interface.
    //
    ERROR_CHECK_VOID(am_hal_ble_initialize(0, &BLE));
    ERROR_CHECK_VOID(am_hal_ble_power_control(BLE, AM_HAL_BLE_POWER_ACTIVE));

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

    ERROR_CHECK_VOID(am_hal_ble_config(BLE, &sBleConfig));

    /*delay 1s for 32768Hz clock stability*/
    am_util_delay_ms(1000);

    // Download and execute copy patch first.

	ERROR_CHECK_VOID(am_hal_ble_default_copy_patch_apply(BLE));

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
    ERROR_CHECK_VOID(am_hal_ble_default_patch_apply(BLE));

    //
    // Signal to the BLE core that patching is complete.
    //
    ERROR_CHECK_VOID(am_hal_ble_patch_complete(BLE));

    // Check whether BLE controller can detect 32768Hz clock is stable.
    if (am_hal_ble_check_32k_clock(BLE) == AM_HAL_STATUS_FAIL)
    {
        if ( ui32NumXtalRetries < HCI_DRV_MAX_XTAL_RETRIES )
        {
            HciDrvRadioShutdown();
            am_util_delay_ms(1000);
            ui32NumXtalRetries++;
            goto ResetBLE;
        }
        else
        {
            HciDrvRadioShutdown();
            return;
        }
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

    //
    // Initialize a queue to help us keep track of HCI write buffers.
    //
    am_hal_queue_from_array(&g_sWriteQueue, g_psWriteBuffers);

    //
    // Reset the RX interrupt counter.
    //
    g_ui32InterruptsSeen = 0;

    return;
}

//*****************************************************************************
//
// Shut down the BLE core.
//
//*****************************************************************************
void
HciDrvRadioShutdown(void)
{
    WsfTimerStop(&g_HeartBeatTimer);

#if AM_CMSIS_REGS
    NVIC_DisableIRQ(BLE_IRQn);
#else // AM_CMSIS_REGS
    am_hal_interrupt_disable(AM_HAL_INTERRUPT_BLE);
#endif // AM_CMSIS_REGS

    ERROR_CHECK_VOID(am_hal_ble_power_control(BLE, AM_HAL_BLE_POWER_OFF));

#if AM_CMSIS_REGS
    while( PWRCTRL->DEVPWREN_b.PWRBLEL );
#else // AM_CMSIS_REGS
    while ( AM_BFM(PWRCTRL, DEVPWREN, PWRBLEL) );
#endif // AM_CMSIS_REGS

    ERROR_CHECK_VOID(am_hal_ble_deinitialize(BLE));

    g_ui32NumBytes   = 0;
    g_consumed_bytes = 0;
}

//*****************************************************************************
//
// Function used by the BLE stack to send HCI messages to the BLE controller.
//
// Internally, the Cordio BLE stack will allocate memory for an HCI message,
//
//*****************************************************************************
uint16_t
hciDrvWrite(uint8_t type, uint16_t len, uint8_t *pData)
{
    uint8_t *pui8Wptr;
    hci_drv_write_t *psWriteBuffer;


    //
    // Check to see if we still have buffer space.
    //
    if (am_hal_queue_full(&g_sWriteQueue))
    {
        am_util_debug_printf("ERROR: Ran out of HCI transmit queue slots.\n");
        ERROR_RETURN(HCI_DRV_TRANSMIT_QUEUE_FULL, len);
    }

    if (len > (HCI_DRV_MAX_TX_PACKET-1))  // comparison compensates for the type byte at index 0.
    {
        am_util_debug_printf("ERROR: Trying to send an HCI packet larger than the hci driver buffer size (needs %d bytes of space).\n",
                             len);

        ERROR_RETURN(HCI_DRV_TX_PACKET_TOO_LARGE, len);
    }

    //
    // Get a pointer to the next item in the queue.
    //
    psWriteBuffer = am_hal_queue_next_slot(&g_sWriteQueue);

    //
    // Set all of the fields in the hci write structure.
    //
    psWriteBuffer->ui32Length = len + 1;

    pui8Wptr = (uint8_t *) psWriteBuffer->pui32Data;

    *pui8Wptr++ = type;

    for (uint32_t i = 0; i < len; i++)
    {
        pui8Wptr[i] = pData[i];
    }

    //
    // Advance the queue.
    //
    am_hal_queue_item_add(&g_sWriteQueue, 0, 1);

    //
    // Send an event to the BLE transfer handler function.
    //
    WsfSetEvent(g_HciDrvHandleID, BLE_TRANSFER_NEEDED_EVENT);

    // Restart heartbeat timer

    if (type == HCI_CMD_TYPE) {
        WsfTimerStop(&g_HeartBeatTimer);
        WsfTimerStartMs(&g_HeartBeatTimer, HEARTBEAT_TIMEOUT_MS);

#ifdef AM_CUSTOM_BDADDR

        uint16_t opcode;
        BYTES_TO_UINT16(opcode, pData);

        if (HCI_OPCODE_RESET == opcode) {

            extern uint8_t g_BLEMacAddress[6];
            am_hal_mcuctrl_device_t sDevice;
            am_hal_mcuctrl_info_get(AM_HAL_MCUCTRL_INFO_DEVICEID, &sDevice);
            g_BLEMacAddress[0] = sDevice.ui32ChipID0;
            g_BLEMacAddress[1] = sDevice.ui32ChipID0 >> 8;
            g_BLEMacAddress[2] = sDevice.ui32ChipID0 >> 16;

            HciVendorSpecificCmd(0xFC32, 6, g_BLEMacAddress);
        }
#endif

    }

    return len;
}

//*****************************************************************************
//
// Save the handler ID of the HciDrvHandler so we can send it events through
// the WSF task system.
//
// Note: These two lines need to be added to the exactle initialization
// function at the beginning of all Cordio applications:
//
//     handlerId = WsfOsSetNextHandler(HciDrvHandler);
//     HciDrvHandler(handlerId);
//
//*****************************************************************************
void
HciDrvHandlerInit(wsfHandlerId_t handlerId)
{
    g_HciDrvHandleID = handlerId;

    g_HeartBeatTimer.handlerId = handlerId;
    g_HeartBeatTimer.msg.event = BLE_HEARTBEAT_EVENT;
}

//*****************************************************************************
//
// Simple interrupt handler to call
//
// Note: These two lines need to be added to the exactle initialization
// function at the beginning of all Cordio applications:
//
//     handlerId = WsfOsSetNextHandler(HciDrvHandler);
//     HciDrvHandler(handlerId);
//
//*****************************************************************************
void
HciDrvIntService(void)
{
    //
    // Read and clear the interrupt status.
    //
    uint32_t ui32Status = am_hal_ble_int_status(BLE, true);
    am_hal_ble_int_clear(BLE, ui32Status);

    //
    // Advance an event counter to make sure we're keeping track of edges
    // correctly.
    //
    g_ui32InterruptsSeen++;

    //
    // Send an event to get processed in the HCI handler.
    //
    WsfSetEvent(g_HciDrvHandleID, BLE_TRANSFER_NEEDED_EVENT);
}

//*****************************************************************************
//
// Event handler for HCI-related events.
//
// This handler can perform HCI reads or writes, and keeps the actions in the
// correct order.
//
//*****************************************************************************
void
HciDrvHandler(wsfEventMask_t event, wsfMsgHdr_t *pMsg)
{
    uint32_t ui32ErrorStatus, ui32TxRetries;
    uint32_t ui32NumHciTransactions = 0;
    uint32_t read_hci_packet_count = 0;

    if (pMsg->event == BLE_HEARTBEAT_EVENT) {
        HciReadLocalVerInfoCmd();
        WsfTimerStartMs(&g_HeartBeatTimer, HEARTBEAT_TIMEOUT_MS);
        return;
    }

    if (g_ui32NumBytes > g_consumed_bytes)
    {
        g_consumed_bytes += hciTrSerialRxIncoming(g_pui32ReadBuffer + g_consumed_bytes,
                g_ui32NumBytes - g_consumed_bytes);

        if (g_consumed_bytes != g_ui32NumBytes)
        {
            // need to come back again
            WsfSetEvent(g_HciDrvHandleID, BLE_TRANSFER_NEEDED_EVENT);
            // return to make sure received packet is accepted by stack.
            return;
        }

        g_ui32NumBytes   = 0;
        g_consumed_bytes = 0;
    }


    am_hal_debug_gpio_set(BLE_DEBUG_TRACE_01);

    //
    // Loop indefinitely, checking to see if there are still tranfsers we need
    // to complete.
    //
    while (ui32NumHciTransactions++ < HCI_DRV_MAX_HCI_TRANSACTIONS)
    {
        //
        // Figure out what kind of transfer the BLE core will accept.
        //
        if ( BLE_IRQ_CHECK() )
        {
            uint32_t ui32OldInterruptsSeen = g_ui32InterruptsSeen;

            am_hal_debug_gpio_set(BLE_DEBUG_TRACE_02);

            //
            // Is the BLE core asking for a read? If so, do that now.
            //
            g_ui32NumBytes = 0;
            ui32ErrorStatus = am_hal_ble_blocking_hci_read(BLE, (uint32_t*)g_pui32ReadBuffer, &g_ui32NumBytes);

            if (g_ui32NumBytes > HCI_DRV_MAX_RX_PACKET)
            {
                am_util_debug_printf("ERROR: Trying to receive an HCI packet larger than the hci driver buffer size (needs %d bytes of space).",
                                     g_ui32NumBytes);

                ERROR_CHECK_VOID(HCI_DRV_RX_PACKET_TOO_LARGE);
            }


            if ( ui32ErrorStatus == AM_HAL_STATUS_SUCCESS)
            {
                //
                // If the read succeeded, we need to wait for the IRQ signal to
                // go back down. If we don't we might inadvertently try to read
                // the same packet twice.
                //
                uint32_t ui32IRQRetries;
                for (ui32IRQRetries = 0; ui32IRQRetries < HCI_DRV_MAX_IRQ_TIMEOUT; ui32IRQRetries++)
                {
                    if (BLE_IRQ_CHECK() == 0 || g_ui32InterruptsSeen != ui32OldInterruptsSeen)
                    {
                        break;
                    }

                    am_util_delay_us(1);
                }

                if (ui32IRQRetries == HCI_DRV_MAX_IRQ_TIMEOUT)
                {
                    ERROR_RECOVER(HCI_DRV_IRQ_STUCK_HIGH);
                }

                //
                // Pass the data along to the stack. The stack should be able
                // to read as much data as we send it.  If it can't, we need to
                // know that.
                //
                g_consumed_bytes = hciTrSerialRxIncoming(g_pui32ReadBuffer, g_ui32NumBytes);

                if (g_consumed_bytes != g_ui32NumBytes)
                {

                    // need to come back again
                    WsfSetEvent(g_HciDrvHandleID, BLE_TRANSFER_NEEDED_EVENT);
                    // take a break now

                    // worst case disable BLE_IRQ
                    break;
                }

                g_ui32NumBytes   = 0;
                g_consumed_bytes = 0;

                read_hci_packet_count++;
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

                ERROR_RECOVER(ui32ErrorStatus);
            }

            am_hal_debug_gpio_clear(BLE_DEBUG_TRACE_02);

            if (read_hci_packet_count >= HCI_DRV_MAX_READ_PACKET)
            {
                // as long as there is pending packet in the controller to MCU,
                // anyway we will get another interrupt shortly, so we don't need
                // to send BLE_TRANSFER_NEEDED_EVENT to ourself.
                break;
            }

        }
        else
        {
            //
            // If we don't have anything to read, we can start checking to see
            // if we have things to write.
            //
            if (am_hal_queue_empty(&g_sWriteQueue))
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

                hci_drv_write_t *psWriteBuffer = am_hal_queue_peek(&g_sWriteQueue);

                ui32ErrorStatus = am_hal_ble_blocking_hci_write(BLE,
                                                                AM_HAL_BLE_RAW,
                                                                (uint32_t *)psWriteBuffer->pui32Data,
                                                                psWriteBuffer->ui32Length);

                //
                // If we managed to actually send a packet, we can go ahead and
                // advance the queue.
                //
                if (ui32ErrorStatus == AM_HAL_STATUS_SUCCESS)
                {
                    am_hal_queue_item_get(&g_sWriteQueue, 0, 1);
                    ui32TxRetries = 0;
                    // Resetting the cumulative count
                    ui32NumHciTransactions = 0;
                }
                else
                {
                    //
                    // If we fail too many times in a row, we should throw an
                    // error to avoid a lock-up.
                    //
                    ui32TxRetries++;

                    if (ui32TxRetries > HCI_DRV_MAX_TX_RETRIES)
                    {
                        ERROR_RECOVER(HCI_DRV_PACKET_TRANSMIT_FAILED);
                        break;
                    }
                }

                am_hal_debug_gpio_clear(BLE_DEBUG_TRACE_07);
            }
        }
    }

    if (ui32NumHciTransactions == HCI_DRV_MAX_HCI_TRANSACTIONS)
    {
        am_util_debug_printf("ERROR: Maximum number of successive HCI transactions exceeded.\n");
        ERROR_RECOVER(HCI_DRV_TOO_MANY_PACKETS);
    }

    am_hal_debug_gpio_clear(BLE_DEBUG_TRACE_01);
}

//*****************************************************************************
//
// Register an error handler for the HCI driver.
//
//*****************************************************************************
void
HciDrvErrorHandlerSet(hci_drv_error_handler_t pfnErrorHandler)
{
    g_hciDrvErrorHandler = pfnErrorHandler;
}

/*************************************************************************************************/
/*!
 *  \fn     HciVsA3_SetRfPowerLevelEx
 *
 *  \brief  Vendor specific command for settting Radio transmit power level
 *          for Nationz.
 *
 *  \param  txPowerlevel    valid range from 0 to 15 in decimal.
 *
 *  \return true when success, otherwise false
 */
/*************************************************************************************************/
bool_t HciVsA3_SetRfPowerLevelEx(txPowerLevel_t txPowerlevel)
{
    // make sure it's 8 bit
    uint8_t set_tx_power[3];
    set_tx_power[0] = set_tx_power[1] = 0;
    set_tx_power[2] = txPowerlevel;

    if ( txPowerlevel < TX_POWER_LEVEL_INVALID )
    {
        HciVendorSpecificCmd(0xFC3B, sizeof(set_tx_power), set_tx_power);
        return true;
    }
    else
    {
        return false;
    }
}
