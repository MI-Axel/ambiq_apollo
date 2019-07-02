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

#include "usr_include.h"
#include "am_app_KWD_init.h"

#if USE_OUTPUT_AMVOS_AMA
#include "am_app_KWD_AMA.h"
#endif

#include "am_audio_buffer.h"

#if VOS_configUSE_SENSORY_THF_ONLY || VOS_configUSE_Sensory_THF
#include "SensoryLib.h"
#endif
//*****************************************************************************
//
// KWD application tasks list. User needs to keep this lists name unchaged.
//
//*****************************************************************************

am_app_utils_task_t am_KWD_tasks[AM_APP_MAX_TASK];

#if USE_OUTPUT_AMVOS_AMA
DeviceInformation g_amaDeviceInformation = 
{
    .serial_number  = "11223355",
    .name           = "VoS-AMA-LE",
    .device_type    = "A3U3B4RTI76K2J"  // Ambiq Micro's ID
};

#if VOS_configUSE_MSBC_BLUEZ
uint8_t g_ui8AudioFormat = 3; // 0 = raw, 1 = OPUS_32KBPS, 2 = OPUS_16KBPS, 3 = MSBC
#elif VOS_configUSE_OPTIM_OPUS
uint8_t g_ui8AudioFormat = 1; // 0 = raw, 1 = OPUS_32KBPS, 2 = OPUS_16KBPS, 3 = MSBC
#endif // VOS_configUSE_MSBC_BLUEZ

bool g_config_preroll_enabled = false;
#endif // #if USE_OUTPUT_AMVOS_AMA

bool g_config_opus_enabled = false;

extern void am_app_Ble_task(void *pvParameters);
//*****************************************************************************
//
// KWD application tasks configuration 
//
//*****************************************************************************
static const am_app_utils_task_setup_t g_KWD_TaskSetup[] = 
{
    //
    // fixme: enable the priority settings below to allow preemption to happen
    //
    
    // TASK ID,                     Task function pointer,              Task name string,           Stack,  Cback,  Priority,   Queue size
    {AM_APP_TASK_LED,               &am_app_KWD_led_task,               "key&led",                  128,    NULL,   2,          4},

#if (VOS_configUSE_LOG_UART0 || VOS_configUSE_PRINTF_UART0)
    {AM_APP_TASK_UART0,             &am_app_KWD_uart0_gatekeeper_task,  "uart0_data_print",         1024,   NULL,   2,         16},
#endif

#if VOS_configUSE_STDIO_PRINTF
    {AM_APP_TASK_STDIO,             &am_app_KWD_stdIO_gatekeeper_task,  "print_on_rtt_swo",         1024,   NULL,   2,          16},  // a high priority task to print
#endif    
#if VOS_configUSE_AWE || VOS_configUSE_SENSORY_THF_ONLY
    {AM_APP_TASK_AUD_PROCESSING,    &am_app_KWD_AWE_processing_task,    "AWE_Process_task",         1024,   NULL,   4,          16},
#endif
#if VOS_configUSE_MODEL_INFERENCE
    {AM_APP_TASK_MODEL_INFERENCE,   &am_app_KWD_model_inference_task,   "KWD_model_inference",      1024,   NULL,   3,          8},
#endif    
#if VOS_configUSE_AUDIO_CODEC
    {AM_APP_TASK_CODEC,             &am_app_KWD_codec_task,             "audio_stream_compress",    3072,   NULL,   3,          16},
#endif
#if VOS_configUSE_RTT_RECORDER
    {AM_APP_TASK_RTT_SWITCH,        &am_app_KWD_rtt_switch_task,        "rtt_switch",               128,    NULL,   1,          8},
#endif
#if VOS_configUSE_BLE
    {AM_APP_BLE,                    &am_app_Ble_task,                   "ble_task",                 512,    NULL,   2,          16},
#endif

#if VOS_MAYA_BOARD
  #if VOS_configUSE_BUZZER
    {AM_APP_TASK_BUZZER,            &am_app_KWD_buzzer_task,            "buzzer_task",              64,     NULL,   2,          4},
  #endif
  #if VOS_configUSE_GSENSOR  
    {AM_APP_TASK_GSENSOR,           &am_app_KWD_gsensor_task,           "gsensor_task",             256,    NULL,   1,          4},
  #endif  
    {AM_APP_TASK_LOGIC,             &am_app_KWD_logic_task,             "logic_task",               256,    NULL,   1,          4},
#endif // #if VOS_MAYA_BOARD
    {AM_APP_TASK_AWE_TICK,          &am_app_KWD_AWE_tick_task,          "AWE_tick_function",        512,    NULL,   1,          8}
};

//#if defined (AM_PART_APOLLO2)
//static const am_app_utils_task_setup_t g_KWD_TaskSetup[] = 
//{
//    {AM_APP_TASK_LED,   &am_app_KWD_led_task,    "led_indicator",  128,    NULL,   1,  4},
//
//#if (VOS_configUSE_LOG_UART0 || VOS_configUSE_PRINTF_UART0)
//    {AM_APP_TASK_UART0,   &am_app_KWD_uart0_gatekeeper_task,    "uart0_data_print",  1024, NULL, 2, 16},
//#endif
//
//#if VOS_configUSE_STDIO_PRINTF
//    {AM_APP_TASK_STDIO, &am_app_KWD_stdIO_gatekeeper_task, "print_on_rtt_swo", 1024, NULL, 5, 16},  // a high priority task to print
//#endif    
//#if VOS_configUSE_AWE
//    {AM_APP_TASK_AWE_PROCESSING, &am_app_KWD_AWE_processing_task, "AWE_Process_task", 1024, NULL, 4, 16},
//#endif
//
//#if VOS_configUSE_MODEL_INFERENCE
//    {AM_APP_TASK_MODEL_INFERENCE, &am_app_KWD_model_inference_task, "KWD_model_inference", 1024, NULL, 5, 8},
//#endif
//
//#if VOS_configUSE_AUDIO_CODEC
//    {AM_APP_TASK_CODEC, &am_app_KWD_codec_task, "audio_stream_compress", 1024, NULL, 4, 16},
//#endif
//
//#if VOS_configUSE_BLE
//    {AM_APP_BLE, &am_app_Ble_task, "ble_task", 1024, NULL, 6, 16},
//#endif
//
//#if VOS_configUSE_RTT_RECORDER
//    {AM_APP_TASK_RTT_SWITCH, &am_app_KWD_rtt_switch_task, "rtt_switch", 128, NULL, 1, 8},
//#endif

//    {AM_APP_TASK_AWE_TICK, &am_app_KWD_AWE_tick_task, "AWE_tick_function", 512, NULL, 3, 8}
//};
//#endif

#define KWD_TASK_INIT_COUNT     (sizeof(g_KWD_TaskSetup)/sizeof(am_app_utils_task_setup_t))

//*****************************************************************************
//
// KWD application tasks list. User needs to keep this lists name unchaged.
//
//*****************************************************************************

TimerHandle_t am_KWD_timers[AM_APP_MAX_TIMER];
//*****************************************************************************
//
// KWD application timers configuration
//
//*****************************************************************************
static const am_app_utils_timer_setup_t g_KWD_TimerSetup[] =
{
    {AM_APP_TIMER_HEART_BEAT, "HeartBeat", HEART_BEAT_PERIOD,  pdTRUE, &am_app_KWD_timer_heart_beat_callback},
    {AM_APP_TIMER_KWD_TIME_OUT, "KwdTimeOut", KWD_TIME_OUT, pdFALSE, &am_app_KWD_timer_postbuff_timeout_callback},
#if VOS_configUSE_MUTE_MIC
    {AM_APP_TIMER_LONG_PRESS, "ButtonLongPress", LONG_PRESS_TIMER_PERIOD_MS, pdFALSE, &am_app_KWD_timer_longpress_callback},
#endif // VOS_configUSE_MUTE_MIC
#if VOS_configUSE_GSENSOR   
    {AM_APP_TIMER_GSENSOR_PERIOD, "GsensorTimer", GSENSOR_PERIOD, pdTRUE, &am_app_KWD_timer_gsensor_period_callback}
#endif // VOS_configUSE_GSENSOR
};

#define KWD_TIMER_INIT_COUNT     (sizeof(g_KWD_TimerSetup)/sizeof(am_app_utils_timer_setup_t))

//******************************************************************************
//KWD Global data buffers used by ring buffers
//*****************************************************************************
uint8_t g_PCM_DataFrame[PCM_FRAME_SIZE*PCM_FRAME_PUSH_OVER*BYTES_PER_SAMPLE];   // 1K bytes

#if VOS_configUSE_BLE
    uint8_t g_BleDataBuffer[BLE_DATA_BUFFER_SIZE];      // 114 bytes
#endif

#if (VOS_configUSE_RTT_RECORDER)
    uint8_t g_rttRecorderBuffer[RTT_BUFFER_LENGTH];     // N/A
#endif

    
uint8_t g_TestDataFrame[10];
//******************************************************************************
//KWD Global parameters
//*****************************************************************************
uint8_t g_ui8KwdDetectedFlag = 0;                   // 1: the key word is detected; 0: no key word detected.
uint8_t g_ui8ButtonDownFlag = 0;                    // 1: the button is pushed down; 0: no button is pushed.

uint8_t g_ui8PushTalkFlag = 0;                      // trig for AMA push-to-talk.
uint8_t g_ui8ProvideSpeechFlag = 0;                 // trig for AMA conversation talk.

//volatile uint32_t count = 0;
#if VOS_configUSE_RTT_RECORDER
uint8_t g_ui8RTTStartFlag = 0;                      // 1: the start of RTT recorder; 0: stop recording
uint32_t g_ui32RTTSendBytes = 0;
#endif

//Start pdm >100ms when power-up
uint16_t g_ui16WOSActiveFlag = 20;
//******************************************************************************
//KWD Global codec instance
//*****************************************************************************
#if VOS_configUSE_AUDIO_CODEC
    #if (VOS_configUSE_SBC_BLUEZ || VOS_configUSE_MSBC_BLUEZ)
        sbc_t   g_BluezSBCInstance;
    #endif
#endif

//******************************************************************************
//KWD Global ring buffers
//*****************************************************************************
am_app_utils_ring_buffer_t am_KWD_ring_buffers[AM_APP_RINGBUFF_MAX];

static const am_app_utils_ringbuff_setup_t g_KWD_RingBuffSetup[] = 
{
    {AM_APP_RINGBUFF_PCM, g_PCM_DataFrame, PCM_FRAME_SIZE*PCM_FRAME_PUSH_OVER*BYTES_PER_SAMPLE},

    #if VOS_configUSE_RECORD_CODEC
        {AM_APP_RINGBUFF_RTT_STREAM, g_rttCodecStream, RTT_CODEC_RING_BUFF_LEN},
    #endif
    {AM_APP_RINGBUFF_TEST, g_TestDataFrame, 10}
   
};

#define KWD_RINGBUFF_INIT_COUNT     (sizeof(g_KWD_RingBuffSetup)/sizeof(am_app_utils_ringbuff_setup_t))

//******************************************************************************
//KWD system init function
//*****************************************************************************

void am_app_KWD_sys_init(void)
{
    #if VOS_configUSE_AWE
        uint32_t Pos = 0;

        am_app_KWD_AWE_instance_init();

//#if VOS_configUSE_AWE_TUNING
        UARTMsgInit();
//#endif // VOS_configUSE_AWE_TUNING

        #if VOS_configUSE_QSD
            Q.noiseFloorThreshold = -60;
            Q.snrThreshold = 6;
            dspc_qsd_config(&Q, 16000.0f, AWE_FRAME_SIZE);
        #endif
        awe_fwInit(&g_AWEInstance);
        //awe_fwPacketExecuteArray(&g_AWEInstance, (unsigned int*) InitCommands, InitCommands_Len);
        awe_fwPacketExecuteArray(InitCommands, InitCommands_Len, &Pos);
    #endif

    //
    // audio codec initialization
    //
    #if VOS_configUSE_AUDIO_CODEC
        am_app_KWD_codec_init();
    #endif

    #if (VOS_configUSE_RTT_RECORDER)
        am_app_KWD_rtt_init(g_rttRecorderBuffer, RTT_BUFFER_LENGTH);
    #endif
    
    #if VOS_configUSE_STDIO_PRINTF
        am_app_utils_stdio_printf_init((am_app_utils_stdio_printf_t)am_app_KWD_printf);
        #if VOS_configUSE_PRINTF_SWO
            swo_init_flag = true;
            am_app_itm_printf_enable();
        #endif
    #endif
            
    #if VOS_configUSE_SENSORY_THF_ONLY || VOS_configUSE_Sensory_THF
        errors_t result;
//        SensoryInfo(&isp);
//        printf("Version = %d.%d.%d\n", (isp.version>>20)&0x00000fff, (isp.version>>12)&0x000000ff, isp.version&0x00000fff);
        
        if (result = SensoryInitialize()) {
//            printf("SensoryInitialize returned error 0x%lx\n", result);
            return;
        }
    #endif
        
    g_bEnableWakeWordDetection = true;

#if USE_OUTPUT_AMVOS_AMA
#if VOS_configUSE_PREROLL
    g_config_preroll_enabled = true;    // fixme: temporarily enable preroll on AMA
#else
    g_config_preroll_enabled = false;
#endif // VOS_configUSE_PREROLL
#endif // USE_OUTPUT_AMVOS_AMA

    //
    // global data structure initialization
    //
    am_app_utils_ring_buffer_init_all(am_KWD_ring_buffers, g_KWD_RingBuffSetup, KWD_RINGBUFF_INIT_COUNT);

#if USE_UNIVERSAL_AUDIO_BUFFER
    //
    // init audio buffers
    //
    am_audio_buffer_init();
#endif // USE_UNIVERSAL_AUDIO_BUFFER

    //
    // create application tasks 
    //
    am_app_utils_task_init();
    am_app_utils_task_create_all_tasks(g_KWD_TaskSetup, KWD_TASK_INIT_COUNT);
    
    am_app_utils_timer_create_all_timers(g_KWD_TimerSetup, KWD_TIMER_INIT_COUNT);

    am_app_KWD_board_init();
    // Enable system heart beat LED
    xTimerStart(am_KWD_timers[AM_APP_TIMER_HEART_BEAT], 0);
  #if VOS_configUSE_GSENSOR  
    xTimerStart(am_KWD_timers[AM_APP_TIMER_GSENSOR_PERIOD], 0);
  #endif
}
