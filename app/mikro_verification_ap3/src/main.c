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

/*project header files*/
#include "am_app_mic_verif_config.h"
#include "am_app_mic_verif_board_setup.h"
#include "am_app_mic_verif_isr.h"

#include <arm_math.h>

/* app utils include file */
#include "am_app_utils.h"


#if AM_APP_MIC_CALIBRATION
#include "am_mikro_calibration.h"
uint8_t g_ui8MicCalStatus = 0;    
uint8_t g_ui8MicCalFlag = 0;
float g_pfMicScalar[2] = {1, 1};
uint32_t g_ui32WindowLen = AVERAGE_WINDOW_LENGTH;
uint32_t g_ui32SampleNum = 0;
#endif // AM_APP_MIC_CALIBRATION

#if AM_APP_MIC_THD
#include "am_mikro_thd.h"
#define THD_FFT_SIZE                1024
#define THD_FFT_BYTES               (THD_FFT_SIZE * 2)

uint8_t g_ui8MicThdStatus = 0;    
uint8_t g_ui8MicThdFlag = 0;
uint32_t g_ui32THDDataBuffer[THD_FFT_SIZE];
float g_fTHDTimeDomain[THD_FFT_SIZE*2];
float g_fTHDFrequencyDomain[THD_FFT_SIZE*2];
float g_fTHDMagnitudes[THD_FFT_SIZE];
float g_fFrequencyUnits = 0;
float g_fTHDResult = 0;
uint8_t g_ui8THDTestStartFlag = 1;              // 1: test start; 0: test stop.

#endif // AM_APP_MIC_THD

// sharing variables in whole procedures
volatile uint8_t g_ui8PcmDataReadyFlag = 0;

int main(void)
{
    am_app_mic_verif_sys_init();
#if configUSE_SYSVIEW
    SEGGER_SYSVIEW_Conf(); // initialize SystemView
    SEGGER_SYSVIEW_Start(); // start SystemView
    SEGGER_SYSVIEW_OnIdle();          /* Tells SystemView that System is currently in "Idle"*/
#endif // configUSE_SYSVIEW

    //
    // Print the banner.
    //
    DebugLog("Microphone verification procedure is ready!\r\n\n");

    while (1)
    {

        /* breathing LED */
        if (g_ui32TimerCount >=1000)
        {
            g_ui32TimerCount = 0;
            am_devices_led_toggle(am_bsp_psLEDs, 0);
        }
#if AM_APP_MIC_CALIBRATION
        if(g_ui8MicCalStatus == 1)
        {
            DebugLog("Enter into microphone calibration status.\n\r");

            am_util_delay_ms(2000);

            g_ui8MicCalFlag = 1;

            while(g_ui8PcmDataReadyFlag == 0);
            if(g_ui8PcmDataReadyFlag == 1)
            {
                am_audio_mikro_balance(&am_sys_ring_buffers[AM_APP_RINGBUFF_PCM], g_ui32WindowLen, 
                                        true, 1, 30, g_pfMicScalar);
                g_ui8MicCalStatus = 0;
                
                g_ui8PcmDataReadyFlag = 0;

                g_ui8MicCalFlag = 0;
                
                g_ui32SampleNum = 0;

                am_devices_led_off(am_bsp_psLEDs, 1);

                DebugLog("Exit from microphone calibration status.\n\n\r");
            }
        
        }
#endif // AM_AEP_MIKRO_CALIBRATION

#if AM_APP_MIC_THD
        
//        if(g_ui8THDTestStartFlag == 1)
//        {
//            g_ui8THDTestStartFlag = 0;
//            am_pcm_fft(g_in16TestInput_2KHZ_SR16K, g_fTHDMagnitudes, THD_FFT_SIZE);
//            g_fTHDResult = am_thd_calc(128, g_fTHDMagnitudes, THD_FFT_SIZE, 16000);
//
//            am_util_stdio_printf("THD result: %0.6f.\r\n", g_fTHDResult);
//        }

#endif // AM_AEP_MIKRO_THD_CALC

//
// Board key interface for different procedure switch
//

        if((g_sysKeyValue == AM_APP_KEY_0) && (g_ui8ButtonPushedFlag == 1))
        {
            g_sysKeyValue = AM_APP_KEY_NONE;
            g_ui8ButtonPushedFlag = 0;

#if AM_APP_MIC_CALIBRATION
            if(g_ui8MicCalStatus == 1)
            {
                g_ui8MicCalStatus = 0;
            }
            else if(g_ui8MicCalStatus == 0)
            {
                g_ui8MicCalStatus = 1;
                am_devices_led_on(am_bsp_psLEDs, 1);
            }
#endif // AM_APP_MIC_CALIBRATION

        }

        if((g_sysKeyValue == AM_APP_KEY_1) && (g_ui8ButtonPushedFlag == 1))
        {
            g_sysKeyValue = AM_APP_KEY_NONE;
            g_ui8ButtonPushedFlag = 0;
#if AM_APP_MIC_THD
            if(g_ui8MicThdStatus == 1)
            {
                g_ui8MicThdStatus = 0;
            }
            else if(g_ui8MicThdStatus == 0)
            {
                g_ui8MicThdStatus = 1;
                am_devices_led_on(am_bsp_psLEDs, 2);
            }
#endif // AM_APP_MIC_THD

        }



    //
    // Go to Deep Sleep.
    //
//        am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_DEEP);

//        am_hal_interrupt_master_enable();
    }

}
