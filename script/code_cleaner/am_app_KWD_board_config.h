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

///*******************************************************************************
//*
//*               Board hardware configurtion
//*               ---------------------------
//*
//********************************************************************************
//*     platform.h
//********************************************************************************
//*
//*     Description:  AWE Platform Interface Header File
//*
//*******************************************************************************/

#ifndef AM_APP_KWD_BOARD_CONFIG_H
#define AM_APP_KWD_BOARD_CONFIG_H

//#define VOS_AMA_FW_VER_STRING                     "1.00.11"

// ---------------------------------------
// User Hardware Selection
// ---------------------------------------

/* Select an EVB Board */
#define VOS_COREBOARD_APOLLO2_EVB                            0
#define VOS_COREBOARD_APOLLO2_BLUE_EVB                       0
#define VOS_COREBOARD_APOLLO3_BLUE_EVB                       1
#define VOS_MAYA_BOARD                                       0

// Select Mikro Board(s)used and MikroBUS slots
#define VOS_MIKBRD_VESPER                          0
#define VOS_MIKBRD_ST_MICS                         1

//*******************************************************************************
// System level functional module selection 
//*******************************************************************************

#define VOS_configUSE_SYSVIEWER             0
#define VOS_configUSE_SYS_LOG               0 
#define VOS_configUSE_RTT_RECORDER          0 
#define VOS_configUSE_STDIO_PRINTF          1

#define VOS_configUSE_AWE                   1
#define VOS_configUSE_MODEL_INFERENCE       0

#define VOS_configUSE_SENSORY_THF_ONLY      0

#define VOS_configUSE_BLE                   1 
#define VOS_configUSE_AUDIO_CODEC           1

#if VOS_MAYA_BOARD 
#define VOS_configUSE_GSENSOR               0
#define VOS_configUSE_BUZZER                1
#endif 
//********************************************************************************
// AWE module configuration 
//********************************************************************************
#if VOS_configUSE_AWE
    #define VOS_configUSE_AWE_TUNING            0
    #define VOS_configUSE_QSD                   0
    #define VOS_configUSE_Sensory_THF           1          
    #define VOS_configUSE_WOS                   0                          
    #define VOS_configUSE_PUSH_TO_TALK          1
    #define VOS_configUSE_MUTE_MIC              1 
#endif

//****************************************
// AWE layout configuration selection 
//****************************************
#if VOS_configUSE_Sensory_THF
    #define VOS_configUSE_2CM_FBF_SCNR                      0
    #define VOS_configUSE_2CM_FBF_SCNR_0_5                  0
    #define VOS_configUSE_2CM_FBF_SCNR_0_5_PREROLL          1
#else
    #define VOS_configUSE_2CM_FBF_SCNR_THF_AMA              0
    #define VOS_configUSE_2CM_FBF_SCNR_THF_AMA_25H          0
#endif

//********************************************************************************
// Microphone Balancing Manual Scaler
//********************************************************************************
//#define DMIC_LEFT_SCALER                                (1.0)   // LEFT mic on PDM channel
//#define DMIC_RIGHT_SCALER                               (1.0)   // RIGHT mic on PDM channel, no need to set this

//********************************************************************************
// Audio Codec module configuration 
//********************************************************************************
#if VOS_configUSE_AUDIO_CODEC
    #define VOS_configUSE_SBC_BLUEZ                 0               
    #define VOS_configUSE_MSBC_BLUEZ                0  
    #define VOS_configUSE_OPTIM_OPUS                1
#endif
//********************************************************************************
// BLE module configuration 
//********************************************************************************
#if VOS_configUSE_BLE
    #define VOS_configUSE_PREROLL                   1              

    #define VOS_configUSE_BLE_Measure_Throughput    0
#endif

#if VOS_configUSE_BLE || VOS_configUSE_AUDIO_CODEC
#define USE_UNIVERSAL_AUDIO_BUFFER              1
#endif 

//********************************************************************************
// RTT recorder module configuration 
//********************************************************************************
#if VOS_configUSE_RTT_RECORDER
    #define VOS_configUSE_RECORD_RAW_PCM            0            
    #define VOS_configUSE_RECORD_FULL_FILTER        0 
    #define VOS_configUSE_RECORD_CODEC              0
#endif
//********************************************************************************
// System log module configuration 
//********************************************************************************
#if VOS_configUSE_SYS_LOG
    #define VOS_configUSE_LOG_UART0                 1              
    #define VOS_configUSE_LOG_UART1                 0
#endif

//********************************************************************************
// std IO sub module configuration 
//********************************************************************************
#if VOS_configUSE_STDIO_PRINTF
    #define VOS_configUSE_PRINTF_UART0          	1
    #define VOS_configUSE_PRINTF_RTT                0
    #define VOS_configUSE_PRINTF_SWO                0
#endif

#if VOS_configUSE_WOS
    #define USE_WAKE_ON_SOUND                1
#endif


#endif
