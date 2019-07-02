//*****************************************************************************
//
//! @file am_app_KWD_isr.c
//!
//! @brief ISR functions of KWD application
//!
//! These functions are required by the RTOS for ticking, sleeping, and basic
//! error checking.
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
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
// This is part of revision v1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include "am_audio_buffer.h"
#include "usr_include.h"
#include "hci_api.h"
#include "wsf_os.h"


#if defined (AM_PART_APOLLO3)
extern void *g_sCOMUART;
extern void *PDMHandle;
#endif // #if defined (AM_PART_APOLLO3)

#if VOS_configUSE_PUSH_TO_TALK
extern void push_to_talk_button_process(void);
#endif // VOS_configUSE_PUSH_TO_TALK

#if VOS_configUSE_MUTE_MIC
extern void mute_mic_button_process(void);
extern void mute_mic_long_press_handler(void);
#endif // VOS_configUSE_MUTE_MIC

volatile BOOL g_bUARTPacketReceived = FALSE;

extern wsfHandlerId_t g_bleDataReadyHandlerId;
//*****************************************************************************
//
// Interrupt handler for the CTIMER module.
//
//*****************************************************************************
void
am_ctimer_isr(void)
{
#if VOS_configUSE_SYSVIEWER
    traceISR_ENTER();
#endif
    uint32_t ui32Status;
    //
    // Check the timer interrupt status.
    //
    ui32Status = am_hal_ctimer_int_status_get(false);
    am_hal_ctimer_int_clear(ui32Status);
#if VOS_MAYA_BOARD
    if(ui32Status & BUZZER_PWM_TIMER_INT)
    {
        am_app_util_buzzer_interrupt_routine();
    }
#endif // #if VOS_MAYA_BOARD

    //
    // Run handlers for the various possible timer events.
    //
    am_hal_ctimer_int_service(ui32Status);

#if VOS_configUSE_SYSVIEWER
    traceISR_EXIT();
#endif
}

//*****************************************************************************
//
// Interrupt handler for the GPIO pins.
//
//*****************************************************************************
void
am_gpio_isr(void)
{
    uint64_t ui64Status;

#if defined (AM_PART_APOLLO2)
    //
    // Read and clear the GPIO interrupt status.
    //
    ui64Status = am_hal_gpio_int_status_get(false);
    am_hal_gpio_int_clear(ui64Status);

#if VOS_configUSE_SYSVIEWER 
    traceISR_ENTER();
#endif

#if VOS_configUSE_BLE
    //
    // Check to see if this was a wakeup event falserom the BLE radio.
    //
    if ( ui64Status & AM_HAL_GPIO_BIT(AM_BSP_GPIO_EM9304_INT) )
    {
        //WsfSetEvent(g_bleDataReadyHandlerId, BLE_DATA_READY_EVENT);
        WsfSetEventOnly(g_bleDataReadyHandlerId, BLE_DATA_READY_EVENT);
    }
#endif

#if VOS_configUSE_PUSH_TO_TALK
    if((ui64Status >> CTRL_BUTTON3) & 0x01 )
    {
        push_to_talk_button_process();
    }
#endif // VOS_configUSE_PUSH_TO_TALK

#if VOS_configUSE_MUTE_MIC
    if((ui64Status >> CTRL_BUTTON4) & 0x01 )
    {
        mute_mic_button_process();
    }
#endif // VOS_configUSE_MUTE_MIC

    //
    // Call the individual pin interrupt handlers for any pin that triggered an
    // interrupt.
    //
    am_hal_gpio_int_service(ui64Status);
#endif // #if defined (AM_PART_APOLLO2)

#if defined (AM_PART_APOLLO3)
    //
    // Read and clear the GPIO interrupt status.
    //
    am_hal_gpio_interrupt_status_get(false, &ui64Status);
    am_hal_gpio_interrupt_clear(ui64Status);

#if VOS_MAYA_BOARD

    if((ui64Status >> CTRL_BUTTON3) & 0x01 )
    {
        am_app_logic_button_process();
    }

#endif // VOS_MAYA_BOARD

#if VOS_configUSE_PUSH_TO_TALK
    if((ui64Status >> CTRL_BUTTON2) & 0x01 )
    {
        //am_hal_gpio_interrupt_disable(AM_HAL_GPIO_BIT(CTRL_BUTTON2));
//        am_app_logic_button2_process();
//        am_app_KWD_AMA_tx_ver_exchange_send();
        AppConnClose(1);
        WsfTaskSetReady(0,0);
    }
#endif // VOS_configUSE_PUSH_TO_TALK

#if VOS_configUSE_MUTE_MIC
    if((ui64Status >> CTRL_BUTTON4) & 0x01 )
    {
//        am_app_KWD_AMA_tx_ver_exchange_send();
//        am_app_KWD_AMA_reset_connection_send();
//          AttcMtuReq(1, 247);
        uint8_t buf[4];
        buf[0] = 0;
        buf[1] = 0;
        buf[2] = 0xff;
        buf[3] = 0x00;
        AttsHandleValueNtf(1, 18,4, buf);
        WsfTaskSetReady(0,0);
//        mute_mic_long_press_handler();
    }
#endif // VOS_configUSE_MUTE_MIC

    //
    // Call the individual pin interrupt handlers for any pin that triggered an
    // interrupt.
    //
    am_hal_gpio_interrupt_service(ui64Status);
    #if VOS_configUSE_SYSVIEWER
    traceISR_EXIT();
    #endif
#endif //#if defined (AM_PART_APOLLO3)

}

#if defined (AM_PART_APOLLO3)
//*****************************************************************************
//
// Interrupt handler for BLE
//
//*****************************************************************************
void
am_ble_isr(void)
{
#if VOS_configUSE_SYSVIEWER
    traceISR_ENTER();
#endif
    HciDrvIntService();

    // Signal radio task to run

    WsfTaskSetReady(0, 0);
#if VOS_configUSE_SYSVIEWER
    traceISR_EXIT();
#endif
}
#endif // #if defined (AM_PART_APOLLO3)

//*****************************************************************************
//
// PDM Interrupt Service Routine (ISR)
//
//*****************************************************************************
#if defined (AM_PART_APOLLO2)
void am_pdm_isr(void)
{
    uint32_t ui32Status;
    uint32_t ui32FIFOCount;
    ui32Status = am_hal_pdm_int_status_get(false);
    uint16_t sampleIndex = 0;
    int32_t i32PDMSampleStereo[PCM_FRAME_SIZE];

    #if VOS_configUSE_SYSVIEWER 
        traceISR_ENTER();
    #endif
  //
  // Grab the FIFO depth
  //
    ui32FIFOCount = am_hal_pdm_fifo_depth_read();

  //
  // When Threshold causes ISR, Grab samples from packed FIFO and make sure we don't underflow
  //
    if((ui32Status == AM_HAL_PDM_INT_FIFO) && (ui32FIFOCount >= PCM_FRAME_SIZE))
    {
        for (sampleIndex = 0; sampleIndex < PCM_FRAME_SIZE; sampleIndex ++)
        {
            i32PDMSampleStereo[sampleIndex] = (int32_t)am_hal_pdm_fifo_data_read();
        }
//        am_app_utils_ring_buffer_push(&am_KWD_ring_buffers[AM_APP_RINGBUFF_PCM], i32PDMSampleStereo, PCM_FRAME_SIZE*BYTES_PER_SAMPLE, FALSE);

        am_app_utils_ring_buffer_push(&am_KWD_ring_buffers[AM_APP_RINGBUFF_PCM], i32PDMSampleStereo, PCM_FRAME_SIZE*BYTES_PER_SAMPLE);

        #if (VOS_configUSE_RTT_RECORDER && VOS_configUSE_RECORD_RAW_PCM)
        //
        // Record the raw PCM data and send over RTT
        //
            if(g_ui8RTTStartFlag == 1)
               am_app_KWD_rtt_record((void*)i32PDMSampleStereo, PCM_FRAME_SIZE*BYTES_PER_SAMPLE); 
        #endif
        #if VOS_configUSE_AWE || VOS_configUSE_SENSORY_THF_ONLY
            am_app_utils_task_send_fromISR(AM_APP_ISR_PDM, AM_APP_TASK_AUD_PROCESSING, AM_APP_MESSAGE_LONG, BYTES_PER_SAMPLE*PCM_FRAME_SIZE, &am_KWD_ring_buffers[AM_APP_RINGBUFF_PCM]);
        #endif    
//        configASSERT(bQueueReValue);
    }
    if(ui32Status & (AM_HAL_PDM_INT_UNDFL | AM_HAL_PDM_INT_OVF))
    {
        am_hal_pdm_fifo_flush(); 
        AM_APP_LOG_DEBUG("am_hal_pdm_fifo_flush();\n");
    }
    // Clear PDM Interrupt (write to clear).
    am_hal_pdm_int_clear(AM_HAL_PDM_INT_FIFO | AM_HAL_PDM_INT_UNDFL | AM_HAL_PDM_INT_OVF);

#if VOS_configUSE_SYSVIEWER
    traceISR_EXIT();
#endif
}
#endif // #if defined (AM_PART_APOLLO2)

#if defined (AM_PART_APOLLO3)
void am_pdm_isr(void)
{
    uint32_t ui32Status;
    bool bQueueReValue;

#if VOS_configUSE_SYSVIEWER
    traceISR_ENTER();
#endif

    extern uint32_t g_ui32PDMDataBuffer[PCM_FRAME_SIZE * BYTES_PER_SAMPLE];
    //
    // Read the interrupt status.
    //
    am_hal_pdm_interrupt_status_get(PDMHandle, &ui32Status, true);
    am_hal_pdm_interrupt_clear(PDMHandle, ui32Status);

    //
    // Once our DMA transaction completes, we will disable the PDM and send a
    // flag back down to the main routine. Disabling the PDM is only necessary
    // because this example only implemented a single buffer for storing FFT
    // data. More complex programs could use a system of multiple buffers to
    // allow the CPU to run the FFT in one buffer while the DMA pulls PCM data
    // into another buffer.
    //
    if (ui32Status & AM_HAL_PDM_INT_DCMP)
    {
        // trigger next traction
        PDMn(0)->DMATOTCOUNT = AWE_FRAME_SIZE*4;  // FIFO unit in bytes

//        am_app_utils_ring_buffer_push(&am_KWD_ring_buffers[AM_APP_RINGBUFF_PCM], g_ui32PDMDataBuffer, PCM_FRAME_SIZE*BYTES_PER_SAMPLE);
        am_audio_buffer_push(AM_AUDIO_BUFFER_STEREO, g_ui32PDMDataBuffer, PCM_FRAME_SIZE*BYTES_PER_SAMPLE);
//        bQueueReValue = am_app_utils_task_send_fromISR(AM_APP_ISR_PDM, AM_APP_TASK_AUD_PROCESSING, AM_APP_MESSAGE_LONG, BYTES_PER_SAMPLE*PCM_FRAME_SIZE, &am_KWD_ring_buffers[AM_APP_RINGBUFF_PCM]);
        bQueueReValue = am_app_utils_task_send_fromISR(AM_APP_ISR_PDM, AM_APP_TASK_AUD_PROCESSING, AM_APP_MESSAGE_LONG, BYTES_PER_SAMPLE*PCM_FRAME_SIZE, &am_audio_ring_buffers[AM_AUDIO_BUFFER_STEREO]);
        #if (VOS_configUSE_RTT_RECORDER && VOS_configUSE_RECORD_RAW_PCM)
        //
        // Record the raw PCM data and send over RTT
        //
            if(g_ui8RTTStartFlag == 1)
               am_app_KWD_rtt_record((void*)i32PDMSampleStereo, PCM_FRAME_SIZE*BYTES_PER_SAMPLE); 
        #endif

//        am_util_debug_printf("PDM DCMP interrupt, pick g_ui32PDMDataBuffer[5] = 0x%8x\n", g_ui32PDMDataBuffer[5]);
    }
    else if(ui32Status & (AM_HAL_PDM_INT_UNDFL | AM_HAL_PDM_INT_OVF))
    {
        am_hal_pdm_fifo_flush(PDMHandle);
        AM_APP_LOG_DEBUG("am_hal_pdm_fifo_flush();\n");
    }

    //
    // When Threshold causes ISR, Grab samples from packed FIFO and make sure we don't underflow
    //
#if VOS_configUSE_SYSVIEWER
//    traceISR_EXIT();
#endif

}
#endif // #if defined (AM_PART_APOLLO3)

/*{{{*/
#if (USE_OUTPUT_BUFFER_UART1)
//*****************************************************************************
//
// Interrupt handler for UART1
//
//*****************************************************************************
void
am_uart1_isr(void)
{
#if VOS_configUSE_SYSVIEWER
    traceISR_ENTER();
#endif
    BaseType_t xHigherPriorityTaskWoken;
    uint32_t ui32Status;

    //
    // Read and save the interrupt status, but clear out the status register.
    //
    ui32Status = AM_REGn(UART, 1, MIS);
    AM_REGn(UART, 1, IEC) = ui32Status;

    if (ui32Status & (AM_HAL_UART_INT_RX_TMOUT | AM_HAL_UART_INT_TX | AM_HAL_UART_INT_RX))
    {
        am_hal_uart_service_buffered_timeout_save(UART1_MODULE, ui32Status);
    }
    if (ui32Status & (AM_HAL_UART_INT_RX_TMOUT | AM_HAL_UART_INT_RX))
    {
        g_bUARTPacketReceived = TRUE;
    }
    // set event flag to unblock tasks
//    xEventGroupSetBitsFromISR(xKWDEventHandle, 0x04, &xHigherPriorityTaskWoken);
#if VOS_configUSE_SYSVIEWER
    traceISR_EXIT();
#endif
}
#endif
/*}}}*/

/*{{{*/
//*****************************************************************************
//
// Interrupt handler for UART0
//
//*****************************************************************************
#if defined (AM_PART_APOLLO2)
void
am_uart_isr(void)
{
#if VOS_configUSE_SYSVIEWER
    traceISR_ENTER();
#endif
    uint32_t ui32Status;

    //
    // Read and save the interrupt status, but clear out the status register.
    //
    ui32Status = AM_REGn(UART, 0, MIS);
    AM_REGn(UART, 0, IEC) = ui32Status;

    if (ui32Status & (AM_HAL_UART_INT_RX_TMOUT | AM_HAL_UART_INT_TX | AM_HAL_UART_INT_RX))
    {
        am_hal_uart_service_buffered(UART0_MODULE, ui32Status);
    }
    if (ui32Status & (AM_HAL_UART_INT_RX_TMOUT | AM_HAL_UART_INT_RX))
    {
        g_bUARTPacketReceived = TRUE;
    }
#if VOS_configUSE_AWE_TUNING
    am_app_utils_task_send_fromISR(AM_APP_ISR_UART0, AM_APP_TASK_AWE_TICK,
                                                    AM_APP_MESSAGE_SHORT, EMPTY_MESSAGE, NULL);
#endif

#if VOS_configUSE_SYSVIEWER
    traceISR_EXIT();
#endif
}
#endif // #if defined (AM_PART_APOLLO2)

#if defined (AM_PART_APOLLO3)
void
am_uart_isr(void)
{
#if VOS_configUSE_SYSVIEWER
    traceISR_ENTER();
#endif
    uint32_t ui32Status, ui32Idle;
    am_hal_uart_interrupt_status_get(g_sCOMUART, &ui32Status, true);
    am_hal_uart_interrupt_clear(g_sCOMUART, ui32Status);
    am_hal_uart_interrupt_service(g_sCOMUART, ui32Status, &ui32Idle);

#if VOS_configUSE_AWE_TUNING
    am_app_utils_task_send_fromISR(AM_APP_ISR_UART0, AM_APP_TASK_AWE_TICK,
                                AM_APP_MESSAGE_SHORT, EMPTY_MESSAGE, NULL);
#endif // #if VOS_configUSE_AWE_TUNING
#if VOS_configUSE_SYSVIEWER
    traceISR_EXIT();
#endif
    
}
#endif // #if defined (AM_PART_APOLLO3)
//#endif
/*}}}*/

/*{{{*/
#if USE_OUTPUT_BUFFER_SPI
//*****************************************************************************
//
// Interrupt handler for IOM0
//
//*****************************************************************************
void
am_iomaster0_isr(void)
{
    uint32_t ui32IntStatus;

    //
    // Read and clear the interrupt status.
    //
    ui32IntStatus = am_hal_iom_int_status_get(IOM0, false);
    am_hal_iom_int_clear(IOM0, ui32IntStatus);

    //
    // Service FIFO interrupts as necessary, and call IOM callbacks as
    // transfers are completed.
    //
    am_hal_iom_int_service(IOM0, ui32IntStatus);
}
#endif
/*}}}*/

//*****************************************************************************
//
// Sleep function called from FreeRTOS IDLE task.
// Do necessary application specific Power down operations here
// Return 0 if this function also incorporates the WFI, else return value same
// as idleTime
//
//*****************************************************************************
uint32_t am_freertos_sleep(uint32_t idleTime)
{
//#if USE_OUTPUT_BUFFER_SPI
//    if (am_hal_iom_fifo_full_slots(IOM0 == 0x00))
//    {
//       configure_iom_sleep(0);
//    }
//#endif
//#if USE_OUTPUT_BUFFER_UART0
//    uint32_t TxBuff;
//    uint32_t RxBuff;
//    am_hal_uart_get_status_buffered(0, &RxBuff, &TxBuff);
//    if (TxBuff == 0)
//    {
//        configure_uart_sleep(0);
//    }
//#endif
//#if USE_OUTPUT_BUFFER_UART1
//    uint32_t TxBuff;
//    uint32_t RxBuff;
//    am_hal_uart_get_status_buffered(0, &RxBuff, &TxBuff);
//    if (TxBuff == 0)
//    {
//       configure_uart_sleep(1);
//    }
//#endif
//    am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_NORMAL);
    am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_DEEP);
    return 0;
}

//*****************************************************************************
//
// Recovery function called from FreeRTOS IDLE task, after waking up from Sleep
// Do necessary 'wakeup' operations here, e.g. to power up/enable peripherals etc.
//
//*****************************************************************************
void am_freertos_wakeup(uint32_t idleTime)
{
    return;
}


//*****************************************************************************
//
// FreeRTOS debugging functions.
//
//*****************************************************************************
void
vApplicationMallocFailedHook(void)
{
    //
    // Called if a call to pvPortMalloc() fails because there is insufficient
    // free memory available in the FreeRTOS heap.  pvPortMalloc() is called
    // internally by FreeRTOS API functions that create tasks, queues, software
    // timers, and semaphores.  The size of the FreeRTOS heap is set by the
    // configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h.
    //
    while (1);
}

void
vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    (void) pcTaskName;
    (void) pxTask;

    //
    // Run time stack overflow checking is performed if
    // configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    // function is called if a stack overflow is detected.
    //
    while (1)
    {
        __asm("BKPT #0\n") ; // Break into the debugger
    }
}

