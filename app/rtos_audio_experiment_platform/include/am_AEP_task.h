#ifndef AM_AEP_TASK_H
#define AM_AEP_TASK_H
//*****************************************************************************
//
// Required built-ins.
//
//*****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//*****************************************************************************
//
// Standard AmbiqSuite includes.
//
//*****************************************************************************
#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_devices.h"
#include "am_util.h"

//*****************************************************************************
//
// FreeRTOS include files.
//
//*****************************************************************************
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "event_groups.h"
#include "queue.h"
//*****************************************************************************

// App utilis include
#include "am_app_utils_task.h"

extern void am_AEP_led_task(void *pvParameters);

extern void am_AEP_button_task(void *pvParameters);

extern void am_AEP_codec_task(void *pvParameters);

extern void am_AEP_timer_heart_beat_callback(TimerHandle_t xTimer);























#endif
