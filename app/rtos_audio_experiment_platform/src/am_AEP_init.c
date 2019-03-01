//*****************************************************************************
//
// FreeRTOS include files.
//
//*****************************************************************************
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "queue.h"
#include "timers.h"

#include "am_app_utils_task.h"
#include "am_app_utils_rtt_recorder.h"

#include "am_AEP_config.h"
#include "am_AEP_init.h"
#include "am_AEP_task.h"
#include "am_AEP_board_setup.h"
#include "am_opus.h"

//******************************************************************************
// AEP ring buffers
//*****************************************************************************
uint8_t g_pui8Test_RingBuff[100];

#if configUSE_PDM_DATA
uint8_t g_pui8PCM_RingBuff[PCM_FRAME_SIZE*PCM_DATA_BYTES*PCM_PUSH_OVER];
#endif // configUSE_PDM_DATA
am_app_utils_ring_buffer_t am_AEP_ring_buffers[AM_AEP_RINGBUFF_MAX];

am_app_utils_ringbuff_setup_t g_AEP_RingBuffSetup[] = 
{
#if configUSE_PDM_DATA
    {AM_AEP_RINGBUFF_PDM, g_pui8PCM_RingBuff, PCM_FRAME_SIZE*PCM_DATA_BYTES*PCM_PUSH_OVER},
#endif // configUSE_PDM_DATA
    
    {AM_AEP_RINGBUFF_TEST, g_pui8Test_RingBuff, 100}

};

//*****************************************************************************
//
// AEP tasks list and setup array
//
//*****************************************************************************

am_app_utils_task_t am_AEP_tasks[AM_AEP_TASK_MAX];
am_app_utils_task_setup_t g_AEP_TaskSetup[] = 
{
    {AM_AEP_TASK_LED, &am_AEP_led_task, "led_indicator", 128, NULL, 1, 4},

#if configUSE_STDIO_PRINTF
    {AM_AEP_TASK_STDIO, &am_AEP_stdIO_task, "print_on_rtt_swo", 1024, NULL, 5, 16},  // a high priority task to print
#endif // configUSE_STDIO_PRINTF   

#if configUSE_AUDIO_CODEC
    {AM_AEP_TASK_CODEC, &am_AEP_codec_task, "codec_encoder", 12*1024, NULL, 2, 16},
#endif // configUSE_AUDIO_CODEC

    {AM_AEP_TASK_BUTTON, &am_AEP_button_task, "button_responser", 1024, NULL, 3, 16}

};

//*****************************************************************************
//
// KWD application tasks list. User needs to keep this lists name unchaged.
//
//*****************************************************************************

TimerHandle_t am_AEP_timers[AM_AEP_TIMER_MAX];
//*****************************************************************************
//
// AEP application timers configuration
//
//*****************************************************************************
am_app_utils_timer_setup_t g_AEP_TimerSetup[] =
{
    {AM_AEP_TIMER_HEART_BEAT, "HeartBeat", HEART_BEAT_PERIOD,  pdTRUE, &am_AEP_timer_heart_beat_callback}

};

//
// AEP Global variables  
//
uint8_t g_ui8DebounceFlag = 0;

#if configUSE_RTT_LOGGER
uint8_t g_rttRecorderBuff[RTT_BUFFER_LENGTH];
volatile uint8_t g_ui8RttRecordFlag = 0; 
#endif // configUSE_RTT_LOGGER

void am_AEP_init(void)
{
    uint32_t buffCount = 0;
    uint32_t taskCount = 0;
    uint32_t taskSetupCount = 0;
    uint32_t timerSetupCount = 0;

    uint32_t byteSize = 0;

    am_AEP_board_setup();
#if configUSE_RTT_LOGGER
    am_app_utils_rtt_init(g_rttRecorderBuff, RTT_BUFFER_LENGTH);
#endif // configUSE_RTT_LOGGER

    //
    // global data structure initialization
    //
    buffCount = getListCount(g_AEP_RingBuffSetup);
    am_app_utils_ring_buffer_init_all(am_AEP_ring_buffers, g_AEP_RingBuffSetup, buffCount);
    //
    // create application tasks 
    //
    taskCount = getListCount(am_AEP_tasks);
    taskSetupCount = getListCount(g_AEP_TaskSetup);
    timerSetupCount = getListCount(g_AEP_TimerSetup);


    am_app_utils_task_init(am_AEP_tasks, taskCount);
    am_app_utils_task_create_all_tasks(g_AEP_TaskSetup, am_AEP_tasks, taskSetupCount);
    am_app_utils_timer_create_all_timers(g_AEP_TimerSetup, am_AEP_timers, timerSetupCount);
#if configUSE_AUDIO_CODEC
    byteSize = xPortGetFreeHeapSize();
    am_util_stdio_printf("There are %d bytes free heap left.", byteSize);
    am_opus_encoder_init(g_opusEnc);
    am_util_stdio_printf("There are %d bytes free heap left after encoder.", byteSize);
#endif // configUSE_AUDIO_CODEC
    // Enable system heart beat LED
    xTimerStart(am_AEP_timers[AM_AEP_TIMER_HEART_BEAT], 0);    

}

