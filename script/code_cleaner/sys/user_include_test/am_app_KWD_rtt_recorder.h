//*****************************************************************************
//
//! @file am_app_KWD_rtt_recorder.h
//!
//! @brief the header file of KWD rtt recorder functions
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

#ifndef AM_APP_KWD_RTT_RECORDER
#define AM_APP_KWD_RTT_RECORDER

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

#include "am_app_KWD_board_config.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "queue.h"
#include "SEGGER_RTT.h"
#include "am_app_utils.h"

#include "am_app_KWD_init.h"
#include "am_app_KWD_task.h"
#include "am_app_utils_task.h"

void am_app_KWD_rtt_init(uint8_t* rttBuffer, uint32_t LenBytes);

void am_app_KWD_rtt_record(void* pBuffer, uint32_t NumBytes);

void am_app_KWD_log_print(am_app_utils_task_enum_t senderID, uint32_t message);

void am_app_KWD_printf(uint32_t indx, uint8_t printType);

#endif    // ndefAM_APP_KWD_RTT_RECORDER
