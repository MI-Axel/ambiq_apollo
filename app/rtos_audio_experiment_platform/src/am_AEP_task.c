#include "am_AEP_init.h"
#include "am_AEP_task.h"


// AEP led task
void am_AEP_led_task(void *pvParameters)
{
    const TickType_t xDelay500ms = pdMS_TO_TICKS(500);
    const TickType_t xDelay200ms = pdMS_TO_TICKS(200);
    const TickType_t xDelaySwirl = pdMS_TO_TICKS(35);
    am_app_utils_task_queue_element_t QueueElement;
    while(1)
    {
        am_app_utils_task_read(am_AEP_tasks, AM_AEP_TASK_LED, &QueueElement);
       
    }

}

// AEP button task
void am_AEP_button_task(void *pvParameters)
{
    const TickType_t xDelay500ms = pdMS_TO_TICKS(500);
    const TickType_t xDelay200ms = pdMS_TO_TICKS(200);
    const TickType_t xDelaySwirl = pdMS_TO_TICKS(35);
    am_app_utils_task_queue_element_t QueueElement;
    while(1)
    {
        am_app_utils_task_read(am_AEP_tasks, AM_AEP_TASK_BUTTON, &QueueElement);
       
    }

}


//*****************************************************************************
//
// Software timer callback functions
//
//*****************************************************************************
void am_AEP_timer_heart_beat_callback(TimerHandle_t xTimer)
{
    am_devices_led_toggle(am_bsp_psLEDs, 0);
}


