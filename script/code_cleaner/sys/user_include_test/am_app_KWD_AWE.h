//*****************************************************************************
//
//! @file am_app_KWS_AWE.h
//!
//! @brief header file of AWE frame work
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

#ifndef AM_APP_KWS_AWE_H
#define AM_APP_KWS_AWE_H

#include "am_app_KWD_board_config.h"

#if VOS_configUSE_AWE
#include "Errors.h"
#include "Framework.h"
#include "StandardDefs.h"
#include "PlatformTuningHandler.h"
#include "MathHelper.h"
#include "ControlDriver.h"

#if VOS_configUSE_2CM_FBF_SCNR_THF_AMA || VOS_configUSE_2CM_FBF_SCNR_THF_AMA_25H
#include "TargetInfo_AM_2cm_FBF_SCNR_THF_AMA.h"
#include "AM_2cm_FBF_SCNR_AMA_Senv2_ModuleList.h"
#include "AM_2cm_FBF_SCNR_AMA_Senv2_AWB.h"
#endif    // VOS_configUSE_2CM_FBF_SCNR_THF_AMA||VOS_configUSE_2CM_FBF_SCNR_THF_AMA_25H

#if VOS_configUSE_2CM_FBF_SCNR
#include "TargetInfo_AM_2cm_FBF_SCNR.h"
#include "AM_2cm_FBF_SCNR_ModuleList.h"
#include "AM_2cm_FBF_SCNR_AWB.h"
#endif    // VOS_configUSE_2CM_FBF_SCNR

#if VOS_configUSE_2CM_FBF_SCNR_0_5
#include "TargetInfo_AM_2cm_FBF_SCNR_0_5.h"
#include "AM_2cm_FBF_SCNR_0_5_ModuleList.h"
#include "AM_2cm_FBF_SCNR_0_5_AWB.h"
#endif    // VOS_configUSE_2CM_FBF_SCNR_0_5

#if VOS_configUSE_2CM_FBF_SCNR_0_5_PREROLL
#include "TargetInfo_AM_2cm_FBF_SCNR_0_5_preroll_no_scnr.h"
#include "AM_2cm_FBF_SCNR_0_5_preroll_no_scnr_ModuleList.h"
#include "AM_2cm_FBF_SCNR_0_5_preroll_no_scnrAWB.h"
#endif    // VOS_configUSE_2CM_FBF_SCNR_0_5_PREROLL



#include "dspc_qsd.h"
#endif    // VOS_configUSE_AWE

#include "am_app_utils.h"


#define INPUT_CHANNEL_COUNT         2
#define OUTPUT_CHANNEL_COUNT        1

#if VOS_configUSE_AWE
#define MAX_PUMP_COUNT                  100

#define AudioWeaverPump_IRQHandler1 	am_software1_isr
#define AudioWeaverPump_IRQHandler2 	am_software2_isr

extern volatile int32_t in32AudioRunningFlag;

extern volatile BOOL g_bBlinkLED4ForBoardAlive;


extern volatile BOOL g_bReboot;

extern volatile UINT32 g_nPumpCount;

extern AWEInstance g_AWEInstance;

extern volatile BOOL g_bAudioPump1Active;

extern volatile BOOL g_bAudioPump2Active;
#if VOS_configUSE_QSD
extern DSPC_QSD Q;
#endif    // VOS_configUSE_QSD
#endif    // VOS_configUSE_AWE

extern int32_t g_delayedSample;
extern int32_t g_endingSampleCnt;

extern void am_app_KWD_AWE_instance_init();
extern void am_app_KWD_AWE_handler(int32_t *nLRSample);

//*****************************************************************************
// Tuning Driver function declaration
//*****************************************************************************

extern void UARTMsgInit(void);

extern void CheckForUARTPacketReady(void);

extern void UART0SendReply(void);

#endif    // ndefAM_APP_KWS_AWE_H
