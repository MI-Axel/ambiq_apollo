//*****************************************************************************
//
//! @file radio_task.h
//!
//! @brief Functions and variables related to the radio task.
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

#ifndef RADIO_TASK_H
#define RADIO_TASK_H

#include "am_app_KWD_board_config.h"
#include "am_app_utils_task.h"
//*****************************************************************************
//
// Radio task handle.
//
//*****************************************************************************
//extern TaskHandle_t radio_task_handle;

extern QueueHandle_t radioQueue;
extern QueueHandle_t radioCmdQueue;
//extern wsfHandlerId_t g_bleDataReadyHandlerId;

#define USE_AP2BLUE 1

#define AMA_TRANSPORT_DATA_TYPE_CMD		0
#define AMA_TRANSPORT_DATA_TYPE_VOICE	1

#if VOS_configUSE_BLE
#define USE_OUTPUT_AMVOS_AMA            1
#endif    // VOS_configUSE_BLE

//#define USE_BLE_OTA                     1

/*! Event types for ble rx data handler */
#define BLE_DATA_READY_EVENT                   0x01      /*! Trigger Rx data path */


typedef struct{
#if USE_OUTPUT_AMVOS_AMA
    uint8_t ama_buf[4]; //dummy
#else    // USE_OUTPUT_AMVOS_AMA
    uint8_t* buf;
#endif    // USE_OUTPUT_AMVOS_AMA
    uint32_t len;
    uint32_t reserved;
}sRadioQueue_t;

typedef struct{
    uint8_t cmd_buf[BLE_COMMAND_BUFFER_SIZE];
    uint32_t len;
}sRadioCmdQueue_t;



typedef enum
{
    AM_BLE_EVENT_DATA,
    AM_BLE_EVENT_DATA1,
    AM_BLE_EVENT_DATA2
}eBleEvent;

//*****************************************************************************
//
// External function definitions.
//
//*****************************************************************************
extern void RadioTaskSetup(void);
extern void am_app_ble_hw_init(void);
extern void RadioTask(void *pvParameters);
extern void radioKwdSendData(uint8_t* buf, uint32_t len);

extern void am_kwd_streaming_start(void);
extern void am_kwd_streaming_stop(void);

#if USE_OUTPUT_AMVOS_AMA
extern uint16_t radio_kwd_data_send(uint8_t* buf, uint32_t len);
#endif    // USE_OUTPUT_AMVOS_AMA

extern bool am_app_KWD_ble_stream_start(void);
extern bool am_app_Ble_nextdata_check(uint8_t** buf, uint32_t* len);

#endif    // ndefRADIO_TASK_H
