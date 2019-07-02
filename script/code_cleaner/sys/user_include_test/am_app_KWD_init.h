//*****************************************************************************
//
//! @file am_app_KWD_init.h
//!
//! @brief the header file of KWD system initialization functions
//!
//*****************************************************************************

//*****************************************************************************
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

#ifndef AM_APP_KWD_INIT
#define AM_APP_KWD_INIT

#include "am_app_KWD_board_config.h"
#include "am_app_utils.h"
#include "am_app_KWD_rtt_recorder.h"
#include "sbc.h"

#if USE_OUTPUT_AMVOS_AMA
#include "accessories.pb.h"
#endif    // USE_OUTPUT_AMVOS_AMA

#if VOS_MAYA_BOARD
#define HEART_BEAT_PERIOD               pdMS_TO_TICKS(3000)
#else    // VOS_MAYA_BOARD
#define HEART_BEAT_PERIOD               pdMS_TO_TICKS(1000)
#endif    // VOS_MAYA_BOARD

#define RTT_RECORDER_RUNNING            pdMS_TO_TICKS(300)

#define KWD_TIME_OUT                    pdMS_TO_TICKS(AUDIO_POSTBUFF_TIME_MS)

#define GSENSOR_PERIOD                  pdMS_TO_TICKS(2000) 

#define LONG_PRESS_TIMER_PERIOD_MS     100
#define LONG_PRESS_EFFECTIVE_MS        4000

//*****************************************************************************
//
// App ring buffer list structure typedefs
//
//*****************************************************************************
// this enum list contains all app related ring buffers between AM_APP_RINGBUFF_NONE and AM_APP_RINGBUFF_MAX
// where each index corresponds to a ring buffer
typedef enum
{
    AM_APP_RINGBUFF_NONE = 0, // The enum must begin with this value as named.
    AM_APP_RINGBUFF_PCM,
#if VOS_configUSE_RTT_RECORDER
    AM_APP_RINGBUFF_RTT_STREAM,
#endif    // VOS_configUSE_RTT_RECORDER
    AM_APP_RINGBUFF_TEST,
    AM_APP_RINGBUFF_MAX // The enum must end with this value as named.
} am_app_utils_ring_buffer_enum_t;



#if VOS_configUSE_BLE
    extern sbc_t g_BluezSBCInstance;
    extern uint8_t g_BleDataBuffer[BLE_DATA_BUFFER_SIZE];
#if USE_OUTPUT_AMVOS_AMA
    extern DeviceInformation g_amaDeviceInformation; 
#endif    // USE_OUTPUT_AMVOS_AMA
#endif    // VOS_configUSE_BLE

extern uint8_t g_ui8KwdDetectedFlag;
extern uint8_t g_ui8ButtonDownFlag;                    // 1: the button is pushed down; 0: no button is pushed.
extern uint8_t g_ui8PushTalkFlag;
extern uint8_t g_ui8ProvideSpeechFlag;

extern volatile uint32_t count;

#if VOS_configUSE_RTT_RECORDER
    extern uint8_t g_ui8RTTStartFlag;             
    extern uint32_t g_ui32RTTSendBytes;
#endif    // VOS_configUSE_RTT_RECORDER

extern uint16_t g_ui16WOSActiveFlag;
extern am_app_utils_ring_buffer_t am_KWD_ring_buffers[];

extern void am_app_KWD_sys_init(void);
extern void am_app_KWD_reset_detected_flag();
extern void am_app_KWD_board_init(void);
extern void am_app_KWD_WOS_pdm_enable(void);
extern void am_app_KWD_WOS_pdm_disable(void);
extern void PDMInit(void);
extern void PDMDeInit(void);

#endif    // ndefAM_APP_KWD_INIT
