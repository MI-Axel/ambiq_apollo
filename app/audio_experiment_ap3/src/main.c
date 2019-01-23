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
/* app utils include file */
//#include "am_app_utils.h"

#if AM_AEP_OPUS_TEST
/* apollo opus include file */
#include "am_opus.h"
#endif /* AM_OPUS_TEST */

#if configUSE_RTT_DATA_OUTPUT
#include "am_app_utils_rtt_recorder.h"
#endif /* USE_RTT_DATA_OUTPUT */

#include <arm_math.h>


int main(void)
{
    am_app_AEP_sys_init(); 
    //
    // Print the banner.
    //
    DebugLog("Starting audio test\r\n\n");


//    am_opus_encoder_init(g_opusEnc);

//    g_opusEncRet = opus_encode(g_opusEnc, g_opusTestData, FRAME_SIZE, g_opusOutputBuff, MAX_PACKET_SIZE);
//    if(g_opusEncRet < 0)
//    {
//        am_util_stdio_printf("encode failed: %s\r\n", opus_strerror(g_opusEncRet));
//    }
//    else
//    {
//        am_util_stdio_printf("encode finished: %d bytes is encoded.\r\n", g_opusEncRet);
//    }

    while (1)
    {
//        am_hal_interrupt_master_disable();

//         if (g_bPDMDataReady) 
//        {
//            g_bPDMDataReady = false;
//            g_numFramesCaptured++;

//            if (g_numFramesCaptured < NUM_FRAMES) 
//            {
//                pdm_data_get();  // Start converting the next set of PCM samples.
//            }

//            else 
//            {
//                g_numFramesCaptured = 0;
//                g_audioRunningFlag = 0;
//                am_hal_pdm_disable(PDMHandle);
//                am_devices_led_off(am_bsp_psLEDs, 0);
//                DebugLog("PDM data recording ends!\r\n");
//            }
//        }

        /* breathing LED */
        if (g_ui32TimerCount >=1000)
        {
            g_ui32TimerCount = 0;
            am_devices_led_toggle(am_bsp_psLEDs, 0);
        
        }
        if(g_sysKeyValue == AM_APP_KEY_0)
        {
            g_sysKeyValue = AM_APP_KEY_NONE;

            if(g_rttRecordingFlag == 1)
            {
                g_rttRecordingFlag = 0;
                am_devices_led_off(am_bsp_psLEDs, 1);
            }
            else if(g_rttRecordingFlag == 0)
            {
                g_rttRecordingFlag = 1;
                am_devices_led_on(am_bsp_psLEDs, 1);
            }
        }
    //
    // Go to Deep Sleep.
    //
//        am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_DEEP);

//        am_hal_interrupt_master_enable();
    }

}
