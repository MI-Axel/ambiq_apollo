#ifndef AM_AEP_INIT_H
#define AM_AEP_INIT_H

#include "am_app_utils_task.h"
#include "am_AEP_config.h"

#define HEART_BEAT_PERIOD               pdMS_TO_TICKS(500)

//*****************************************************************************
//
// AEP task index list
//
//*****************************************************************************
// this enum list contains all app related application tasks between AM_TASK_NONE and AM_MAX_TASK
// where each index corresponds to a TASK or ISR.
// Naming convention for a task: AM_TASK_xxx
// Naming convention for an ISR: AM_ISR_xxx
typedef enum
{
	AM_AEP_TASK_NONE = 0, // The enum must begin with this value as named.
    AM_AEP_TASK_LED,
    AM_AEP_TASK_BUTTON,
#if configUSE_STDIO_PRINTF
     AM_AEP_TASK_STDIO,
#endif // configUSE_STDIO_PRINTF

#if configUSE_AUDIO_CODEC
    AM_AEP_TASK_CODEC,    
#endif // configUSE_AUDIO_CODEC
    AM_AEP_ISR_PDM,
    AM_AEP_ISR_GPIO,
    AM_AEP_TASK_MAX // The enum must end with this value as named.
} am_app_utils_task_enum_t;

//*****************************************************************************
//
// AEP timers index list
//
//*****************************************************************************
typedef enum
{
	AM_AEP_TIMER_NONE = 0, // The enum must begin with this value as named.
    AM_AEP_TIMER_HEART_BEAT,
    AM_AEP_TIMER_DEBOUNCE,
    AM_AEP_TIMER_MAX // The enum must end with this value as named.
} am_app_utils_timer_enum_t;

//*****************************************************************************
//
// AEP ring buffer index list
//
//*****************************************************************************
typedef enum
{
    AM_AEP_RINGBUFF_NONE = 0, // The enum must begin with this value as named.
    AM_AEP_RINGBUFF_PDM,
    AM_AEP_RINGBUFF_TEST,
    AM_AEP_RINGBUFF_MAX // The enum must end with this value as named.
} am_app_utils_ring_buffer_enum_t;

extern uint8_t g_ui8DebounceFlag;

extern am_app_utils_task_t am_AEP_tasks[AM_AEP_TASK_MAX];

extern TimerHandle_t am_AEP_timers[AM_AEP_TIMER_MAX];

extern am_app_utils_ring_buffer_t am_AEP_ring_buffers[AM_AEP_RINGBUFF_MAX];

#if configUSE_RTT_LOGGER
extern uint8_t g_rttRecorderBuff[RTT_BUFFER_LENGTH];
extern volatile uint8_t g_ui8RttRecordFlag;
#endif // configUSE_RTT_LOGGER

extern void am_AEP_init(void);























#endif
