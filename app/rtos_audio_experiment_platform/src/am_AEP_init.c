#include "am_AEP_config.h"
#include "am_AEP_init.h"
#include "am_AEP_task.h"
#include "am_AEP_board_setup.h"

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
#endif    

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
// KWD application timers configuration
//
//*****************************************************************************
am_app_utils_timer_setup_t g_AEP_TimerSetup[] =
{
    {AM_AEP_TIMER_HEART_BEAT, "HeartBeat", HEART_BEAT_PERIOD,  pdTRUE, &am_AEP_timer_heart_beat_callback}
};


void am_AEP_init(void)
{
    uint32_t buffCount = 0;
    uint32_t taskCount = 0;
    uint32_t taskSetupCount = 0;
    uint32_t timerSetupCount = 0;
    
    am_AEP_board_setup();
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

    // Enable system heart beat LED
    xTimerStart(am_AEP_timers[AM_AEP_TIMER_HEART_BEAT], 0);    

}

