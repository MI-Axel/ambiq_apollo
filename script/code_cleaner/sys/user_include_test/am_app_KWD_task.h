//*****************************************************************************
//
//! @file am_app_KWD_task.h
//!
//! @brief header file of application tasks
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

#ifndef AM_APP_KWD_TASK_H
#define AM_APP_KWD_TASK_H


#include <string.h>
//*****************************************************************************
//
// FreeRTOS include files.
//
//*****************************************************************************
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "queue.h"
#include "FreeRTOSConfig.h"
#include "am_app_KWD_board_config.h"
#include "am_app_utils_task.h"
#include "am_app_utils_ring_buffer.h"

//*****************************************************************************
//
// App message type list macro definitions
//
//*****************************************************************************
// this enum list contains all app related ring buffers between AM_APP_RINGBUFF_NONE and AM_APP_RINGBUFF_MAX
// where each index corresponds to a ring buffer
typedef enum
{
	AM_APP_MESSAGE_NONE = 0, // The enum must begin with this value as named.
    AM_APP_MESSAGE_SHORT,
    AM_APP_MESSAGE_LONG,
    AM_APP_MESSAGE_STR,
	AM_APP_MESSAGE_MAX // The enum must end with this value as name} am_app_utils_ring_buffer_enum_t;
} am_app_utils_message_type_enum_t;

extern bool swo_init_flag;
extern bool g_bEnableWakeWordDetection;
extern bool g_bAmaIsReady;

// Macro define for some empty message

extern void am_app_KWD_setup_task(void *pvParameters);

extern void am_app_KWD_led_task(void *pvParameters);

extern void am_app_KWD_rtt_switch_task(void *pvParameters);

extern void am_app_KWD_uart0_gatekeeper_task(void *pvParameters);

extern void am_app_KWD_stdIO_gatekeeper_task(void* pvParameters);

extern void am_app_KWD_AWE_processing_task(void *pvParameters);

extern void am_app_KWD_model_inference_task(void *pvParameters);

extern void am_app_KWD_AWE_tick_task(void *pvParameters);

extern void am_app_KWD_buzzer_task(void *pvParameters);
extern void am_app_KWD_gsensor_task(void *pvParameters);
extern void am_app_KWD_logic_task(void *pvParameters);

extern void am_app_KWD_codec_task(void *pvParameters);

extern void am_app_KWD_timer_heart_beat_callback(TimerHandle_t xTimer);
extern void am_app_KWD_timer_postbuff_timeout_callback(TimerHandle_t xTimer);
extern void am_app_KWD_timer_gsensor_period_callback(TimerHandle_t xTimer);
extern void am_app_KWD_timer_longpress_callback(TimerHandle_t xTimer);
#endif    // ndefAM_APP_KWD_TASK_H
