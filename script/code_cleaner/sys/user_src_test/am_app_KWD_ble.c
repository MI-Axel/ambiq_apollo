//*****************************************************************************
//
//! @file radio_task.c
//!
//! @brief Task to handle radio operation.
//!
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
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************

//*****************************************************************************
//
// Global includes for this project.
//
//*****************************************************************************

//#include "freertos_kwd.h"
#include "usr_include.h"

//*****************************************************************************
//
// WSF standard includes.
//
//*****************************************************************************
#include "wsf_types.h"
#include "wsf_trace.h"
#include "wsf_buf.h"
#include "wsf_timer.h"

//*****************************************************************************
//
// Includes for operating the ExactLE stack.
//
//*****************************************************************************
#include "hci_handler.h"
#include "dm_handler.h"
#include "l2c_handler.h"
#include "att_handler.h"
#include "smp_handler.h"
#include "l2c_api.h"
#include "att_api.h"
#include "smp_api.h"
#include "app_api.h"
#include "hci_core.h"
#include "hci_drv.h"
#include "hci_drv_apollo.h"

#include "am_mcu_apollo.h"
#include "am_util.h"
#include "am_bsp.h"

#include "hci_apollo_config.h"

#include "wsf_msg.h"
//*****************************************************************************
//
// Includes for the ExactLE "fit" profile.
//
//*****************************************************************************
#include "amvos_api.h"
#include "am_app_KWD_AMA.h"
#include "app_ui.h"

#include "am_audio_buffer.h"

//*****************************************************************************
//
// Radio task handle.
//
//*****************************************************************************
TaskHandle_t radio_task_handle;

//*****************************************************************************
//
// Handle for Radio-related events.
//
//*****************************************************************************
EventGroupHandle_t xRadioEventHandle;

//*****************************************************************************
//
// Function prototypes
//
//*****************************************************************************
void exactle_stack_init(void);
void scheduler_timer_init(void);
void update_scheduler_timers(void);
void set_next_wakeup(void);

//*****************************************************************************
//
// Timer configuration macros.
//
//*****************************************************************************
// Configure how to driver WSF Scheduler
#if 1
// Preferred mode to use when using FreeRTOS
#define USE_FREERTOS_TIMER_FOR_WSF
#else    // 1
// These are only test modes.
#ifdef AM_FREERTOS_USE_STIMER_FOR_TICK
#define USE_STIMER_FOR_WSF // Reuse FreeRTOS used STimer for WSF
#else    // defAM_FREERTOS_USE_STIMER_FOR_TICK
#define USE_CTIMER_FOR_WSF
#endif    // defAM_FREERTOS_USE_STIMER_FOR_TICK
#endif    // 1

// Use FreeRTOS timer for WSF Ticks
#ifdef USE_FREERTOS_TIMER_FOR_WSF
#define CLK_TICKS_PER_WSF_TICKS     (WSF_MS_PER_TICK*configTICK_RATE_HZ/1000)
#endif    // defUSE_FREERTOS_TIMER_FOR_WSF

#ifdef USE_CTIMER_FOR_WSF
#define WSF_CTIMER_NUM 	            1
#define CLK_TICKS_PER_WSF_TICKS     (WSF_MS_PER_TICK*512/1000)   // Number of CTIMER counts per WSF tick.

#if WSF_CTIMER_NUM == 0
#define WSF_CTIMER_INT 	AM_HAL_CTIMER_INT_TIMERA0
#elif WSF_CTIMER_NUM == 1
#define WSF_CTIMER_INT 	AM_HAL_CTIMER_INT_TIMERA1
#elif WSF_CTIMER_NUM == 2
#define WSF_CTIMER_INT 	AM_HAL_CTIMER_INT_TIMERA2
#elif WSF_CTIMER_NUM == 3
#define WSF_CTIMER_INT 	AM_HAL_CTIMER_INT_TIMERA3
#endif    // WSF_CTIMER_NUM==0
#endif    // defUSE_CTIMER_FOR_WSF

#ifdef USE_STIMER_FOR_WSF
#define CLK_TICKS_PER_WSF_TICKS     (WSF_MS_PER_TICK*configSTIMER_CLOCK_HZ/1000)   // Number of STIMER counts per WSF tick.
#endif    // defUSE_STIMER_FOR_WSF

//*****************************************************************************
//
// WSF buffer pools.
//
//*****************************************************************************
#define WSF_BUF_POOLS               (4 + 1)

// Important note: the size of g_pui32BufMem should includes both overhead of internal
// buffer management structure, wsfBufPool_t (up to 16 bytes for each pool), and pool
// description (e.g. g_psPoolDescriptors below).

// Memory for the buffer pool
// extra AMOTA_PACKET_SIZE bytes for OTA handling
static uint32_t g_pui32BufMem[(1024 + 768 + 280*6) / sizeof(uint32_t)];

// Default pool descriptor.
static wsfBufPoolDesc_t g_psPoolDescriptors[WSF_BUF_POOLS] =
{
    {  16,  8 },
    {  32,  4 },
    {  64,  6 },
    { 128,  8 },
    { 280,  6 }
//    { 520,  2 },        //517 bytes buffer for 496bytes of MTU
};

wsfHandlerId_t g_bleDataReadyHandlerId;

//*****************************************************************************
//
// Tracking variable for the scheduler timer.
//
//*****************************************************************************
uint32_t g_ui32LastTime = 0;

void radio_timer_handler(void);

// ama event callback example
void vos_ama_event_cback_example(eVosAmaEvent_t evt, void* pMsg);

#if defined (AM_PART_APOLLO2)
void ble_data_ready_handler(wsfEventMask_t event, wsfMsgHdr_t *pMsg)
{
    HciDataReadyISR();
}
#endif    // defined(AM_PART_APOLLO2)

#ifdef USE_CTIMER_FOR_WSF
//*****************************************************************************
//
// Set up a pair of timers to handle the WSF scheduler.
//
//*****************************************************************************
void
scheduler_timer_init(void)
{
    // Enable the LFRC
    am_hal_clkgen_osc_start(AM_HAL_CLKGEN_OSC_LFRC);

    //
    // One of the timers will run in one-shot mode and provide interrupts for
    // scheduled events.
    //
    am_hal_ctimer_clear(WSF_CTIMER_NUM, AM_HAL_CTIMER_TIMERA);
    am_hal_ctimer_config_single(WSF_CTIMER_NUM, AM_HAL_CTIMER_TIMERA,
                                (AM_HAL_CTIMER_INT_ENABLE |
                                 AM_HAL_CTIMER_LFRC_512HZ |
                                 AM_HAL_CTIMER_FN_ONCE));

    //
    // The other timer will run continuously and provide a constant time-base.
    //
    am_hal_ctimer_clear(WSF_CTIMER_NUM, AM_HAL_CTIMER_TIMERB);
    am_hal_ctimer_config_single(WSF_CTIMER_NUM, AM_HAL_CTIMER_TIMERB,
                                (AM_HAL_CTIMER_LFRC_512HZ |
                                 AM_HAL_CTIMER_FN_CONTINUOUS));

    //
    // Start the continuous timer.
    //
    am_hal_ctimer_start(WSF_CTIMER_NUM, AM_HAL_CTIMER_TIMERB);

    //
    // Enable the timer interrupt.
    //
    am_hal_ctimer_int_register(WSF_CTIMER_INT, radio_timer_handler);
    am_hal_interrupt_priority_set(AM_HAL_INTERRUPT_CTIMER, configKERNEL_INTERRUPT_PRIORITY);
    am_hal_ctimer_int_enable(WSF_CTIMER_INT);
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_CTIMER);
}

//*****************************************************************************
//
// Calculate the elapsed time, and update the WSF software timers.
//
//*****************************************************************************
void
update_scheduler_timers(void)
{
    uint32_t ui32CurrentTime, ui32ElapsedTime;

    //
    // Read the continuous timer.
    //
    ui32CurrentTime = am_hal_ctimer_read(WSF_CTIMER_NUM, AM_HAL_CTIMER_TIMERB);

    //
    // Figure out how long it has been since the last time we've read the
    // continuous timer. We should be reading often enough that we'll never
    // have more than one overflow.
    //
    ui32ElapsedTime = ui32CurrentTime - g_ui32LastTime;

    //
    // Check to see if any WSF ticks need to happen.
    //
    if ( (ui32ElapsedTime / CLK_TICKS_PER_WSF_TICKS) > 0 )
    {
        //
        // Update the WSF timers and save the current time as our "last
        // update".
        //
        WsfTimerUpdate(ui32ElapsedTime / CLK_TICKS_PER_WSF_TICKS);

        g_ui32LastTime = ui32CurrentTime;
    }
}

//*****************************************************************************
//
// Set a timer interrupt for the next upcoming scheduler event.
//
//*****************************************************************************
void
set_next_wakeup(void)
{
    bool_t bTimerRunning;
    wsfTimerTicks_t xNextExpiration;

    //
    // Stop and clear the scheduling timer.
    //
    am_hal_ctimer_stop(WSF_CTIMER_NUM, AM_HAL_CTIMER_TIMERA);
    am_hal_ctimer_clear(WSF_CTIMER_NUM, AM_HAL_CTIMER_TIMERA);

    //
    // Check to see when the next timer expiration should happen.
    //
    xNextExpiration = WsfTimerNextExpiration(&bTimerRunning);

    //
    // If there's a pending WSF timer event, set an interrupt to wake us up in
    // time to service it. Otherwise, set an interrupt to wake us up in time to
    // prevent a double-overflow of our continuous timer.
    //
    if ( xNextExpiration )
    {
        am_hal_ctimer_period_set(WSF_CTIMER_NUM, AM_HAL_CTIMER_TIMERA,
                                 xNextExpiration * CLK_TICKS_PER_WSF_TICKS, 0);
    }
    else
    {
        am_hal_ctimer_period_set(WSF_CTIMER_NUM, AM_HAL_CTIMER_TIMERA, 0x8000, 0);
    }

    //
    // Start the scheduling timer.
    //
    am_hal_ctimer_start(WSF_CTIMER_NUM, AM_HAL_CTIMER_TIMERA);
}

//*****************************************************************************
//
// Interrupt handler for the CTIMERs
//
//*****************************************************************************
void
radio_timer_handler(void)
{
    // Signal radio task to run

    WsfTaskSetReady(0,0);

}
#endif    // defUSE_CTIMER_FOR_WSF
#ifdef USE_STIMER_FOR_WSF
//*****************************************************************************
//
// Reuse STIMER to handle the WSF scheduler.
//
//*****************************************************************************
void
scheduler_timer_init(void)
{
    //
    // USe CMPR1 of STIMER for one-shot mode interrupts for
    // scheduled events.
    //
    uint32_t cfgVal;
    /* Stop the Stimer momentarily.  */
    cfgVal = am_hal_stimer_config(AM_HAL_STIMER_CFG_FREEZE);


    //
    // Configure the STIMER->COMPARE_1
    //
    am_hal_stimer_compare_delta_set(1, CLK_TICKS_PER_WSF_TICKS);
    am_hal_stimer_int_enable(AM_HAL_STIMER_INT_COMPAREB);
    am_hal_stimer_config(cfgVal | AM_HAL_STIMER_CFG_COMPARE_B_ENABLE);

    //
    // Enable the timer interrupt in the NVIC, making sure to use the
    // appropriate priority level.
    //
    am_hal_interrupt_priority_set(AM_HAL_INTERRUPT_STIMER_CMPR1, configKERNEL_INTERRUPT_PRIORITY);
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_STIMER_CMPR1);

    //
    // Reuse STIMER to provide a constant time-base.
    //

}

//*****************************************************************************
//
// Calculate the elapsed time, and update the WSF software timers.
//
//*****************************************************************************
void
update_scheduler_timers(void)
{
    uint32_t ui32CurrentTime, ui32ElapsedTime;

    //
    // Read the continuous timer.
    //
    ui32CurrentTime = am_hal_stimer_counter_get();

    //
    // Figure out how long it has been since the last time we've read the
    // continuous timer. We should be reading often enough that we'll never
    // have more than one overflow.
    //
    ui32ElapsedTime = ui32CurrentTime - g_ui32LastTime;

    //
    // Check to see if any WSF ticks need to happen.
    //
    if ( (ui32ElapsedTime / CLK_TICKS_PER_WSF_TICKS) > 0 )
    {
        //
        // Update the WSF timers and save the current time as our "last
        // update".
        //
        WsfTimerUpdate(ui32ElapsedTime / CLK_TICKS_PER_WSF_TICKS);

        g_ui32LastTime = ui32CurrentTime;
    }
}

//*****************************************************************************
//
// Set a timer interrupt for the next upcoming scheduler event.
//
//*****************************************************************************
void
set_next_wakeup(void)
{
    bool_t bTimerRunning;
    wsfTimerTicks_t xNextExpiration;
    uint32_t cfgVal;
    uint32_t ui32Critical;

    //
    // Check to see when the next timer expiration should happen.
    //
    xNextExpiration = WsfTimerNextExpiration(&bTimerRunning);

    //
    // If there's a pending WSF timer event, set an interrupt to wake us up in
    // time to service it. Otherwise, set an interrupt to wake us up in time to
    // prevent a double-overflow of our continuous timer.
    //

    /* Enter a critical section */
    ui32Critical = am_hal_interrupt_master_disable();

    /* Stop the Stimer momentarily.  */
    cfgVal = am_hal_stimer_config(AM_HAL_STIMER_CFG_FREEZE);
    //
    // Configure the STIMER->COMPARE_1
    //
    if ( xNextExpiration )
    {
        am_hal_stimer_compare_delta_set(1, xNextExpiration * CLK_TICKS_PER_WSF_TICKS);
    }
    else
    {
        am_hal_stimer_compare_delta_set(1, 0x80000000);
    }

    /* Exit Critical Section */
    am_hal_interrupt_master_set(ui32Critical);

    am_hal_stimer_int_enable(AM_HAL_STIMER_INT_COMPAREB);
    am_hal_stimer_config(cfgVal);

}

//*****************************************************************************
//
// Interrupt handler for the CTIMERs
//
//*****************************************************************************
void
radio_timer_handler(void)
{
    // Signal radio task to run

    WsfTaskSetReady(0,0);

}
//*****************************************************************************
//
// Interrupt handler for the STIMER module Compare 1.
//
//*****************************************************************************
void
am_stimer_cmpr1_isr(void)
{
    am_hal_stimer_int_clear(AM_HAL_STIMER_INT_COMPAREB);

    //
    // Run handlers for the various possible timer events.
    //
    radio_timer_handler();

}
#endif    // defUSE_STIMER_FOR_WSF
#ifdef USE_FREERTOS_TIMER_FOR_WSF
TimerHandle_t xWsfTimer;
//*****************************************************************************
//
// Callback handler for the FreeRTOS Timer
//
//*****************************************************************************
void
wsf_timer_handler(TimerHandle_t xTimer)
{
    // Signal radio task to run

    WsfTaskSetReady(0,0);

}
//*****************************************************************************
//
// Reuse FreeRTOS TIMER to handle the WSF scheduler.
//
//*****************************************************************************
void
scheduler_timer_init(void)
{
    // Create a FreeRTOS Timer
    xWsfTimer = xTimerCreate("WSF Timer", pdMS_TO_TICKS(WSF_MS_PER_TICK),
            pdFALSE, NULL, wsf_timer_handler);
    configASSERT(xWsfTimer);
}

//*****************************************************************************
//
// Calculate the elapsed time, and update the WSF software timers.
//
//*****************************************************************************
void
update_scheduler_timers(void)
{
    uint32_t ui32CurrentTime, ui32ElapsedTime;

    //
    // Read the continuous timer.
    //
    ui32CurrentTime = xTaskGetTickCount();

    //
    // Figure out how long it has been since the last time we've read the
    // continuous timer. We should be reading often enough that we'll never
    // have more than one overflow.
    //
    ui32ElapsedTime = ui32CurrentTime - g_ui32LastTime;

    //
    // Check to see if any WSF ticks need to happen.
    //
    if ( (ui32ElapsedTime / CLK_TICKS_PER_WSF_TICKS) > 0 )
    {
        //
        // Update the WSF timers and save the current time as our "last
        // update".
        //
        WsfTimerUpdate(ui32ElapsedTime / CLK_TICKS_PER_WSF_TICKS);

        g_ui32LastTime = ui32CurrentTime;
    }
}

//*****************************************************************************
//
// Set a timer interrupt for the next upcoming scheduler event.
//
//*****************************************************************************
void
set_next_wakeup(void)
{
    bool_t bTimerRunning;
    wsfTimerTicks_t xNextExpiration;

    //
    // Check to see when the next timer expiration should happen.
    //
    xNextExpiration = WsfTimerNextExpiration(&bTimerRunning);

    //
    // If there's a pending WSF timer event, set an interrupt to wake us up in
    // time to service it.
    //
    if ( xNextExpiration )
    {
    	//FIXME!!! Priority issue, cause of xTimer task priority is setted to 1.
#if 0
        configASSERT(pdPASS == xTimerChangePeriod( xWsfTimer,
                pdMS_TO_TICKS(xNextExpiration*CLK_TICKS_PER_WSF_TICKS), 100)) ;
#else    // 0
        uint32_t uX = xTimerChangePeriod( xWsfTimer,
                pdMS_TO_TICKS(xNextExpiration*CLK_TICKS_PER_WSF_TICKS), 100);
#endif    // 0

    }
}

#endif    // defUSE_FREERTOS_TIMER_FOR_WSF
//*****************************************************************************
//
// Initialization for the ExactLE stack.
//
//*****************************************************************************
void
exactle_stack_init(void)
{
    wsfHandlerId_t handlerId;
#if defined (AM_PART_APOLLO3)
    uint16_t       wsfBufMemLen;
#endif    // defined(AM_PART_APOLLO3)
    //
    // Set up timers for the WSF scheduler.
    //
    scheduler_timer_init();
    WsfTimerInit();

    //
    // Initialize a buffer pool for WSF dynamic memory needs.
    //
#if defined (AM_PART_APOLLO2)
    WsfBufInit(sizeof(g_pui32BufMem), (uint8_t *)g_pui32BufMem, WSF_BUF_POOLS,
               g_psPoolDescriptors);
#endif    // defined(AM_PART_APOLLO2)

#if defined (AM_PART_APOLLO3)
    wsfBufMemLen = WsfBufInit(sizeof(g_pui32BufMem), (uint8_t *)g_pui32BufMem, WSF_BUF_POOLS,
               g_psPoolDescriptors);

    if (wsfBufMemLen > sizeof(g_pui32BufMem))
    {
        am_util_debug_printf("Memory pool is too small by %d\r\n",
                             wsfBufMemLen - sizeof(g_pui32BufMem));
    }
#endif    // defined(AM_PART_APOLLO3)
    //
    // Initialize the WSF security service.
    //
    SecInit();
    SecAesInit();
    SecCmacInit();
    SecEccInit();

    //
    // Set up callback functions for the various layers of the ExactLE stack.
    //
    handlerId = WsfOsSetNextHandler(HciHandler);
    HciHandlerInit(handlerId);

    handlerId = WsfOsSetNextHandler(DmHandler);
    DmDevVsInit(0);
    DmAdvInit();
    DmConnInit();
    DmConnSlaveInit();
    DmSecInit();
    DmSecLescInit();
    DmPrivInit();
    DmHandlerInit(handlerId);

    handlerId = WsfOsSetNextHandler(L2cSlaveHandler);
    L2cSlaveHandlerInit(handlerId);
    L2cInit();
    L2cSlaveInit();

    handlerId = WsfOsSetNextHandler(AttHandler);
    AttHandlerInit(handlerId);
    AttsInit();
    AttsIndInit();
    AttcInit();

    handlerId = WsfOsSetNextHandler(SmpHandler);
    SmpHandlerInit(handlerId);
    SmprInit();
    SmprScInit();
    HciSetMaxRxAclLen(251);//(500);

    handlerId = WsfOsSetNextHandler(AppHandler);
    AppHandlerInit(handlerId);

#if USE_OUTPUT_AMVOS_AMA
    handlerId = WsfOsSetNextHandler(AmVosHandler);
    AmVosHandlerInit(handlerId);
#endif    // USE_OUTPUT_AMVOS_AMA
#if defined (AM_PART_APOLLO2)
    g_bleDataReadyHandlerId = WsfOsSetNextHandler(ble_data_ready_handler);
#endif    // defined(AM_PART_APOLLO2)

#if defined (AM_PART_APOLLO3)
    handlerId = WsfOsSetNextHandler(HciDrvHandler);
    HciDrvHandlerInit(handlerId);
#endif    // defined(AM_PART_APOLLO3)
}

//*****************************************************************************
//
// Interrupt handler for the CTS pin
//
//*****************************************************************************
void
radio_cts_handler(void)
{
    // Signal radio task to run

    WsfTaskSetReady(0,0);

}


#if 0
void delay(uint32_t ms)
{
  uint32_t uint32Ms = ms;
  while(uint32Ms--);
}
#endif    // 0
//*****************************************************************************
//
// Perform initial setup for the radio task.
//
//*****************************************************************************
void
RadioTaskSetup(void)
{
//    am_util_debug_printf("RadioTask: setup\r\n");

    //
    // Create an event handle for our wake-up events.
    //
    xRadioEventHandle = xEventGroupCreate();

    //
    // Make sure we actually allocated space for the events we need.
    //
    while ( xRadioEventHandle == NULL );

    // Pass event object to WSF scheduler
    wsfOsSetEventObject((void*)xRadioEventHandle);

#if defined (AM_PART_APOLLO2)
    //
    // Enable 32KHz Clockout to EM9304
    //
#if USE_AP2BLUE
    am_hal_gpio_pin_config(24, AM_HAL_PIN_24_CLKOUT);
#endif    // USE_AP2BLUE
#if USE_NICKEL_BOARD
    am_hal_gpio_pin_config(4, AM_HAL_PIN_4_CLKOUT);
#endif    // USE_NICKEL_BOARD

    am_hal_clkgen_osc_start(AM_HAL_CLKGEN_OSC_XT);

    am_util_delay_ms(200); //jjwang
    //delay(800000);
    am_hal_clkgen_clkout_enable(AM_HAL_CLKGEN_CLKOUT_CKSEL_XT);

#endif    // defined(AM_PART_APOLLO2)

//    //
//    // Boot the radio.
//    //
//    HciDrvRadioBoot(0);
}

//*****************************************************************************
//
// Short Description.
//
//*****************************************************************************

QueueHandle_t radioQueue;
QueueHandle_t radioCmdQueue;

// triggers a ble task event to send data
// return true if failed
#if USE_OUTPUT_AMVOS_AMA
bool am_app_KWD_ble_stream_start(void)
{
    sRadioQueue_t bleStreamTrigger;

    //fill audio data header
    bleStreamTrigger.ama_buf[0] = 0x00;

    bleStreamTrigger.len = 0;

    if(xQueueSend(radioQueue, &bleStreamTrigger, 0) == NULL)
    {
        return true;
    }

    WsfTaskSetReady(0,0);
    return false;

}
#endif    // USE_OUTPUT_AMVOS_AMA
sRadioQueue_t gRadioQueue;       // queue element defined globally to avoid using the stack
sRadioCmdQueue_t gRadioCmdQueue;       // queue element defined globally to avoid using the stack

#if USE_OUTPUT_AMVOS_AMA
uint8_t bleAmaSendingBuffer[256];   // sized to fit a max MTU value
bool am_app_Ble_nextdata_check(uint8_t** buf, uint32_t* len)
{
    if(xQueueReceive(radioCmdQueue, &gRadioCmdQueue, 0))
    {
        //
        // check command queue first for higher priority
        //
        *buf = gRadioCmdQueue.cmd_buf;
        *len = gRadioCmdQueue.len;
        return true;
    }
    else if(xQueueReceive(radioQueue, &gRadioQueue, 0))
    {
        if((gRadioQueue.len == 0) && (gRadioQueue.ama_buf[0] == 0x00))
        {
                return false;
        }
        else
        {
#if USE_OUTPUT_AMVOS_AMA
            // use queued data
            *buf = gRadioQueue.ama_buf;
#else    // USE_OUTPUT_AMVOS_AMA
            *buf = gRadioQueue.buf;
#endif    // USE_OUTPUT_AMVOS_AMA
            *len = gRadioQueue.len;
            return true;
        }
    }
    else
    {
        return false;
    }
}
#endif    // USE_OUTPUT_AMVOS_AMA

//*****************************************************************************
//
//! @brief am_kwd_streaming_start - Manual trigger and start voice command streamming.
//! 
//! 
//! 
//! @return None.
//*****************************************************************************
void am_kwd_streaming_start(void)
{
#if USE_WAKE_ON_SOUND
    am_hal_pdm_enable(); // enable the PDM mic interface
#endif    // USE_WAKE_ON_SOUND

    am_app_KWD_reset_detected_flag();
    g_ui8PushTalkFlag = 1;
}

void am_kwd_streaming_provide_speech(void)
{
#if USE_WAKE_ON_SOUND
    am_hal_pdm_enable(); // enable the PDM mic interface
#endif    // USE_WAKE_ON_SOUND

    am_app_KWD_reset_detected_flag();

    g_bEnableWakeWordDetection = false; // provide speech, in conversation mode, don't trigger keyword
    g_ui8ProvideSpeechFlag = 1;
}


//*****************************************************************************
//
//! @brief am_kwd_streaming_stop - Force stop voice command streamming.
//! 
//! 
//! 
//! @return None.
//*****************************************************************************
void am_kwd_streaming_stop(void)
{
    // Note: count variable is used in AWEProcessing() at am_pdm_isr,
    // is it safe to change? or need to handle with mutex?
    // This function will be called by SmartVoice task in VENDOR_L project.
    am_app_KWD_reset_detected_flag();
}

void am_app_ble_hw_init(void)
{
#if defined (AM_PART_APOLLO2)
    am_hal_interrupt_priority_set(AM_HAL_INTERRUPT_GPIO, configKERNEL_INTERRUPT_PRIORITY/*configMAX_SYSCALL_INTERRUPT_PRIORITY*/); //configKERNEL_INTERRUPT_PRIORITY);
#endif    // defined(AM_PART_APOLLO2)

#if defined (AM_PART_APOLLO3)
    NVIC_SetPriority(BLE_IRQn, NVIC_configKERNEL_INTERRUPT_PRIORITY);
#endif    // defined(AM_PART_APOLLO3)

    //
    // Boot the radio.
    //
    HciDrvRadioBoot(0);

#if defined (AM_PART_APOLLO2)
    //
    // Register an interrupt handler for BLE event
    //
    am_hal_gpio_int_register(AM_BSP_GPIO_EM9304_INT, radio_cts_handler);
#endif    // defined(AM_PART_APOLLO2)
}

void am_app_Ble_task(void *pvParameters)
{
#if defined (AM_PART_APOLLO2)
    am_hal_interrupt_priority_set(AM_HAL_INTERRUPT_GPIO, configKERNEL_INTERRUPT_PRIORITY/*configMAX_SYSCALL_INTERRUPT_PRIORITY*/); //configKERNEL_INTERRUPT_PRIORITY);

    //
    // Boot the radio.
    //
    HciDrvRadioBoot(0);

    //
    // Register an interrupt handler for BLE event
    //
    am_hal_gpio_int_register(AM_BSP_GPIO_EM9304_INT, radio_cts_handler);
#endif    // defined(AM_PART_APOLLO2)

#if WSF_TRACE_ENABLED == TRUE
    //
    // Enable ITM
    //
    am_util_debug_printf("Starting wicentric trace:\n\n");
#endif    // WSF_TRACE_ENABLED==TRUE

    //
    // Initialize the main ExactLE stack.
    //
    exactle_stack_init();

#if defined (AM_PART_APOLLO2)
    //
    // Enable BLE data ready interrupt
    //
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_GPIO);
#endif    // defined(AM_PART_APOLLO2)


    radioQueue = xQueueCreate(4, sizeof( sRadioQueue_t ));          //4 * 15ms = 60 ms
    radioCmdQueue = xQueueCreate(16, sizeof( sRadioCmdQueue_t ));
  
    //
    // Start the "AmVos" profile.
    //
#if USE_OUTPUT_AMVOS_AMA
    AmVosStart();
#endif    // USE_OUTPUT_AMVOS_AMA

    am_app_utils_task_queue_element_t QueueElement;

    am_app_KWD_AMA_evt_cback_register(vos_ama_event_cback_example);

    while (1)
    {
        uint8_t* pBuf;
        uint32_t len;
#if USE_OUTPUT_AMVOS_AMA
        // Workaround : TX Version Exchange packet's NTF is not comming from iOS app. [Lewis]
        // iOS app don't need TX Version Exchange packet. (For Android official app, it is mandatory.)
        if(g_ui8VosTxBusy == 0 || g_eAmaStatus == VOS_AMA_INIT)
//        if(g_ui8VosTxBusy == 0)
        {

            uint32_t data_len = am_app_utils_get_ring_buffer_status(&am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED]);
            
            if(am_app_Ble_nextdata_check(&pBuf, &len))
            {
                AmVosBleSend(pBuf, len);
//                AM_APP_LOG_INFO("1\n");
            }
           
            else if(data_len >= BLE_DATA_BUFFER_SIZE) //57) //
            {
              uint32_t enc_len = BLE_DATA_BUFFER_SIZE;//(data_len / 57 )* 57;
              
              AM_CRITICAL_BEGIN_VOS;
              bleAmaSendingBuffer[0] = 0x10;
              bleAmaSendingBuffer[1] = 0x80;  //AMA_TRANSPORT_DATA_TYPE_VOICE
              bleAmaSendingBuffer[2] = enc_len;
              am_audio_buffer_pop(AM_AUDIO_BUFFER_ENCODED, &bleAmaSendingBuffer[3], enc_len);
          
              AM_CRITICAL_END_VOS;          
              AmVosBleSend(bleAmaSendingBuffer, enc_len + 3);
            }
        }
#endif    // USE_OUTPUT_AMVOS_AMA


        //
        // Calculate the elapsed time from our free-running timer, and update
        // the software timers in the WSF scheduler.
        //
        update_scheduler_timers();
        wsfOsDispatcher();

        //
        // Enable an interrupt to wake us up next time we have a scheduled
        // event.
        //
        set_next_wakeup();

        //
        // Check to see if the WSF routines are ready to go to sleep.
        //
        if (wsfOsReadyToSleep())
        {
            //
            // Attempt to shut down the UART. If we can shut it down
            // successfully, we can go to deep sleep. Otherwise, we'll need to
            // stay awake to finish processing the current packet.
            //

            //
            // Wait for an event to be posted to the Radio Event Handle.
            //
#if 0 // VOS_configUSE_BLE
                am_app_utils_task_read(AM_APP_BLE, &QueueElement);
#else    // 0//VOS_configUSE_BLE
                xEventGroupWaitBits(xRadioEventHandle, 1, pdTRUE,
                               pdFALSE, portMAX_DELAY);
#endif    // 0//VOS_configUSE_BLE
        }
    }

}

#if USE_OUTPUT_AMVOS_AMA
bool amvosIsConnected(void)
{
    if(g_AmaConnId == DM_CONN_ID_NONE)
    {
        return false;
    }
    return true;
}
#endif    // USE_OUTPUT_AMVOS_AMA

void vos_ama_event_cback_example(eVosAmaEvent_t evt, void* pMsg)
{
    switch(evt)
    {
        case VOS_AMA_EVT_IDLE:
            AM_APP_LOG_DEBUG("[AMA Callback] VOS_AMA_EVT_IDLE\n");
            break;
        case VOS_AMA_EVT_PROVIDE_SPEECH:
            AM_APP_LOG_DEBUG("[AMA Callback] VOS_AMA_EVT_PROVIDE_SPEECH\n");
            break;
        case VOS_AMA_EVT_STOP_SPEECH:
            AM_APP_LOG_DEBUG("[AMA Callback] VOS_AMA_EVT_STOP_SPEECH\n");
            break;
        case VOS_AMA_EVT_LISTENING:
            AM_APP_LOG_DEBUG("[AMA Callback] VOS_AMA_EVT_LISTENING\n");
            break;
        case VOS_AMA_EVT_GET_DEV_INFO:
            AM_APP_LOG_DEBUG("[AMA Callback] VOS_AMA_EVT_GET_DEV_INFO\n");
            break;
        case VOS_AMA_EVT_GET_CENTRAL_INFO:
            AM_APP_LOG_DEBUG("[AMA Callback] VOS_AMA_EVT_GET_CENTRAL_INFO\n");
            break;
        case VOS_AMA_EVT_GET_STATE:
            amaGetStateRsp_t state;
            amaGetStateRsp_t* pTemp = (amaGetStateRsp_t*)pMsg;
            state.feature = pTemp->feature;
            state.value = pTemp->value;
            AM_APP_LOG_DEBUG("[AMA Callback] VOS_AMA_EVT_GET_STATE\n");
            if(state.feature == 0x203)  // 0x203: App Network State
            {
                if(state.value == 0)
                {
                    AM_APP_LOG_DEBUG("[AMA Callback] Network is in good condition\n");
                }
                else if(state.value == 1)
                {
                    AM_APP_LOG_DEBUG("[AMA Callback] Network is slow\n");
                }
                else if(state.value == 2)
                {
                    AM_APP_LOG_DEBUG("[AMA Callback] Network not available\n");
                }
                else
                {
                    AM_APP_LOG_DEBUG("[AMA Callback] Invailid value: %d\n", state.value);
                }
            }
            break;

        case VOS_AMA_EVT_SYNC_STATE:
            amaSyncStateRsp_t syncState;
            amaSyncStateRsp_t* pSyncTemp = (amaSyncStateRsp_t*)pMsg;
            syncState.feature = pSyncTemp->feature;
            syncState.value = pSyncTemp->value;
            AM_APP_LOG_DEBUG("[AMA Callback] VOS_AMA_EVT_SYNC_STATE\n");
            if(syncState.feature == 0x203)  // 0x203: App Network State
            {
                if(syncState.value == 0)
                {
                    AM_APP_LOG_DEBUG("[AMA Callback] Network is in good condition\n");
                }
                else if(syncState.value == 1)
                {
                    AM_APP_LOG_DEBUG("[AMA Callback] Network is slow\n");
                }
                else if(syncState.value == 2)
                {
                    AM_APP_LOG_DEBUG("[AMA Callback] Network not available\n");
                }
                else
                {
                    AM_APP_LOG_DEBUG("[AMA Callback] Invailid value: %d\n", syncState.value);
                }
            }
            break;
        default:
            break;
    }
}

