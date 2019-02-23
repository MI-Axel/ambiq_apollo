/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

/* This file is the main file of the audio experiment platform. */

#include <stdint.h>

#include "am_bsp.h"
#include "am_mcu_apollo.h"  // Defines AM_CMSIS_REGS
#include "am_util.h"

#include "am_audio_platform_config.h"
#include "board_setup.h"
#include "audio_driver.h"

#include <arm_math.h>

/* app utils include file */
//#include "am_app_utils.h"

#if configUSE_RTT_DATA_OUTPUT
#include "am_app_utils_rtt_recorder.h"
#endif /* USE_RTT_DATA_OUTPUT */

#if configUSE_SYSVIEW
#include "SEGGER_SYSVIEW.h"
#endif

#if AM_AEP_OPUS_TEST
/* apollo opus include file */
#include "am_opus.h"
#endif /* AM_AEP_OPUS_TEST */

#if AM_AEP_MEMCPY_TEST
#include "am_memcpy_ringbuff_test.h"
#endif // AM_AEP_MEMCPY_TEST

#if AM_AEP_ALLOC_FREE_TEST
#include "am_alloc_free_test.h"
#endif // AM_AEP_ALLOC_FREE_TEST

int main(void)
{
    am_app_AEP_sys_init();
#if configUSE_SYSVIEW
    SEGGER_SYSVIEW_Conf(); // initialize SystemView
    SEGGER_SYSVIEW_Start(); // start SystemView
    SEGGER_SYSVIEW_OnIdle();          /* Tells SystemView that System is currently in "Idle"*/
#endif // configUSE_SYSVIEW
    //
    // Print the banner.
    //
    DebugLog("Starting audio test\r\n\n");

#if AM_AEP_MEMCPY_TEST
    uint32_t ui32CpyLen = 37957;
    am_app_utils_ring_buffer_init_all(am_AEP_ring_buffers, g_AEP_RingBuffSetup, g_ui32RingBuffCount);

    am_ringbuff_test();
#endif // AM_AEP_MEMCPY_TEST

#if AM_AEP_ALLOC_FREE_TEST
    am_alloc_free_test();
#endif // AM_AEP_ALLOC_FREE_TEST

#if AM_AEP_OPUS_TEST
    uint8_t g_ui8EncStartFlag = 0;
    uint32_t g_ui32LocalDataIndex = 0;
    uint32_t g_ui32LocalDataFrameNum = sizeof(mono_16b_USP1602) / sizeof(opus_int16);
    uint32_t g_ui32FrameSize = 320;                 // encoder frame size
    uint32_t g_ui32EncOutputBytes = 80;             // FrameSize * 2 bytes / 8 
//    uint32_t g_ui32EncOutputBytes = 40;             // FrameSize * 2 bytes / 16 
    uint32_t g_ui32OutputSumBytes = 0;              // used to summary the output bytes
    
    am_opus_encoder_init(g_opusEnc);

#endif // AM_AEP_OPUS_TEST

    while (1)
    {

        /* breathing LED */
        if (g_ui32TimerCount >=1000)
        {
            g_ui32TimerCount = 0;
            am_devices_led_toggle(am_bsp_psLEDs, 0);
#if AM_AEP_MEMCPY_TEST
            am_ringbuff_test();
#endif // AM_AEP_MEMCPY_TEST
        }

#if AM_AEP_OPUS_TEST

        if((g_ui32LocalDataIndex <= (sizeof(mono_16b_USP1602) - g_ui32FrameSize * sizeof(opus_int16))) && (g_ui8EncStartFlag == 1))
        {
#if configUSE_SYSVIEW            
            SEGGER_SYSVIEW_OnUserStart(10);
#endif // configUSE_SYSVIEW
            g_opusEncRet = opus_encode(g_opusEnc, (opus_int16*)&mono_16b_USP1602[g_ui32LocalDataIndex], g_ui32FrameSize, g_opusOutputBuff, g_ui32EncOutputBytes);

#if configUSE_SYSVIEW
            SEGGER_SYSVIEW_OnUserStop(10);
#endif // configUSE_SYSVIEW

            if(g_opusEncRet < 0)
            {
                am_util_stdio_printf("encode failed: %s\r\n", opus_strerror(g_opusEncRet));
            }
            else
            {
                g_ui32LocalDataIndex += g_ui32FrameSize * sizeof(opus_int16);
                g_ui32OutputSumBytes += g_opusEncRet;
#if configUSE_RTT_DATA_OUTPUT
                if(g_rttRecordingFlag == 1)
                    // Output opus data to rtt buffer
                    am_app_utils_rtt_record(g_opusOutputBuff, g_ui32EncOutputBytes);
#endif // configUSE_RTT_DATA_OUTPUT
                am_util_stdio_printf("encode finished: %d bytes is output.\r\n", g_opusEncRet);
            }
        }
        else if((g_ui32LocalDataIndex > (sizeof(mono_16b_USP1602) - g_ui32FrameSize * sizeof(opus_int16))) && (g_ui8EncStartFlag == 1))
        {
            am_util_stdio_printf("Totally %d bytes are output.\r\n", g_ui32OutputSumBytes);
            DebugLog("Local data are all encoded!\r\n");
            am_devices_led_off(am_bsp_psLEDs, 1);
            g_ui8EncStartFlag = 0;
            g_ui32LocalDataIndex = 0;
            g_ui32OutputSumBytes = 0;
#if configUSE_RTT_DATA_OUTPUT
            g_rttRecordingFlag = 0;
#endif // configUSE_RTT_DATA_OUTPUT
        }

#endif // AM_AEP_OPUS_TEST

#if AM_AEP_MEMCPY_TEST
//        am_memcpy_test(&mono_16b_USP1602[11], &g_pui8MemcpyBuff[1], ui32CpyLen);

//        am_fast_memcpy_test(&mono_16b_USP1602[11], &g_pui8FastMemcpyBuff[1], ui32CpyLen);

//        if(am_memcpy_verify(&mono_16b_USP1602[11], &g_pui8MemcpyBuff[1], ui32CpyLen) && am_memcpy_verify(&mono_16b_USP1602[11], &g_pui8FastMemcpyBuff[1], ui32CpyLen))
//            am_devices_led_on(am_bsp_psLEDs, 2);
//        else
//        {
//            am_devices_led_off(am_bsp_psLEDs, 2);
//            while(1);                           // if error occurs, the code will stuck here
//        }
#endif // AM_AEP_MEMCPY_TEST


//
// Board key interface for debug using
//

        if(g_sysKeyValue == AM_APP_KEY_0)
        {
            g_sysKeyValue = AM_APP_KEY_NONE;

#if configUSE_RTT_DATA_OUTPUT
            if(g_rttRecordingFlag == 1)
            {
                g_rttRecordingFlag = 0;
            }
            else if(g_rttRecordingFlag == 0)
            {
                g_rttRecordingFlag = 1;
            }
#endif // configUSE_RTT_DATA_OUTPUT

#if AM_AEP_OPUS_TEST
            if(g_ui8EncStartFlag == 1)
            {
                g_ui8EncStartFlag = 0;
            }
            else if(g_ui8EncStartFlag == 0)
            {
                g_ui8EncStartFlag = 1;
                am_devices_led_on(am_bsp_psLEDs, 1);
            }

#endif // AM_AEP_OPUS_TEST
        }

    //
    // Go to Deep Sleep.
    //
//        am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_DEEP);

//        am_hal_interrupt_master_enable();
    }

}
