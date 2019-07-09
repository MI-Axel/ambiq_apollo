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

#if AM_APP_ANALOG_MIC
uint32_t g_ui32AD_Val = 0;
uint32_t g_ui32PCM_RegVal = 0;
uint32_t g_ui32OutSamples = 0;
#endif // AM_APP_ANALOG_MIC

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

#if AM_APP_ANALOG_MIC
        //
        // Check for DMA errors.
        //
        if (g_bADCDMAError)
        {
            am_util_stdio_printf("DMA Error occured\n");
            while(1);
        }

        //
        // Check if the ADC DMA completion interrupt occurred.
        //
        if (g_bADCDMAComplete)
        {
#if 0
            {
                uint32_t        ui32SampleCount;
                am_util_stdio_printf("DMA Complete\n\r");
                ui32SampleCount = ADC_SAMPLE_BUF_SIZE;
                if (AM_HAL_STATUS_SUCCESS != am_hal_adc_samples_read(g_ADCHandle,
                                                                     g_ui32ADCSampleBuffer,
                                                                     &ui32SampleCount,
                                                                     SampleBuffer))
                {
                    am_util_stdio_printf("Error - failed to process samples.\n");
                }
            }
#endif

            //
            // Reset the DMA completion and error flags.
            //
            g_bADCDMAComplete = false;

            //
            // Re-configure the ADC DMA.
            //
            adc_config_dma();

            //
            // Clear the ADC interrupts.
            //
            if (AM_HAL_STATUS_SUCCESS != am_hal_adc_interrupt_clear(g_ADCHandle, 0xFFFFFFFF))
            {
                am_util_stdio_printf("Error - clearing the ADC interrupts failed.\n");
            }

            //
            // Trigger the ADC sampling for the first time manually.
            //
            if (AM_HAL_STATUS_SUCCESS != am_hal_adc_sw_trigger(g_ADCHandle))
            {
                am_util_stdio_printf("Error - triggering the ADC failed.\n");
            }
        }
        
        if((g_bAMicDataReady == true) && (g_bAMicEvalFlag == true) && (g_bPDMDataReady == true))
        {
            am_util_stdio_printf("Get Analog Mic data %d bytes!\n\r", g_ui32AMicDataSumBytes);

            am_util_stdio_printf("Get PDM audio data %d bytes!\n\r", g_ui32PCMDataSumBytes);

            am_util_stdio_printf("Audio data collection ended....");
            
            //
            // zero clear the counter 
            //
            g_ui32AMicDataSumBytes = 0;
            g_ui32PCMDataSumBytes = 0;
        }

        if((g_bPDMDataReady == true) && (g_bAMicDataReady == true))
        {
            am_devices_led_off(am_bsp_psLEDs, 1);
            g_bAMicEvalFlag = false;
            g_bPDMDataReady = false;
            g_bAMicDataReady = false;
            am_util_stdio_printf("Analog Mic data as following: \n\r");
            while(!(am_app_utils_ring_buffer_empty(&am_sys_ring_buffers[AM_APP_RINGBUFF_ANA])))
            {
                uint8_t indx = 0;
                uint32_t ringbuff_ret = 0;
                for(indx=0; indx<16; indx++)
                {
                    ringbuff_ret = am_app_utils_ring_buffer_pop(&am_sys_ring_buffers[AM_APP_RINGBUFF_ANA], &g_ui32AD_Val, 4);
                    if(ringbuff_ret == 4)
                    {    
                        g_ui32OutSamples += 1;
                    }
                    else if(ringbuff_ret ==0)
                    {
                        am_util_stdio_printf("AMic ring buffer is already empty...\n\r");
                        break;
                    }
                    else
                    {
                        am_util_stdio_printf("There're something weired...AMic ring buffer not 4 bytes aligned...\n\r");
                    }
                    //
                    // follow the ADC data format
                    //
                    DebugLogUInt32(g_ui32AD_Val>>6);
                    DebugLog(" ");
                }
                am_util_stdio_printf("\n\r");
            }
            am_util_stdio_printf("Send out ALL AMic data! There're totally %d samples\n\n\r", g_ui32OutSamples); 
            g_ui32OutSamples = 0;
#if 0
            am_util_stdio_printf("PCM data register values as following: \n\r");
            while(!(am_app_utils_ring_buffer_empty(&am_sys_ring_buffers[AM_APP_RINGBUFF_PCM])))
            {
                uint8_t indx = 0;
                uint32_t ringbuff_ret = 0;
                for(indx==0; indx<16; indx++)
                {
                    ringbuff_ret = am_app_utils_ring_buffer_pop(&am_sys_ring_buffers[AM_APP_RINGBUFF_PCM], &g_ui32PCM_RegVal, 4);
                    if(ringbuff_ret == 4)
                    {    
                        g_ui32OutSamples += 1;
                    }
                    else if(ringbuff_ret ==0)
                    {
                        am_util_stdio_printf("DMic ring buffer is already empty...\n\r");
                        break;
                    }
                    else
                    {
                        am_util_stdio_printf("There're something weired...DMic ring buffer not 4 bytes aligned...\n\r");
                    }

                    //
                    // follow the ADC data format
                    //
                    DebugLogUInt32(g_ui32PCM_RegVal);
                    DebugLog(" ");
                }
                am_util_stdio_printf("\n\r");

            }
            am_util_stdio_printf("Send out ALL DMic data! There're totally %d samples\n\r", g_ui32OutSamples); 
            g_ui32OutSamples = 0;
#endif // 0
            am_util_stdio_printf("All data were sended out...\n\n\n\r");
        }
#endif // AM_APP_ANALOG_MIC

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

#if AM_APP_ANALOG_MIC
            if(g_bAMicEvalFlag == false)
            {
                am_util_stdio_printf("Waiting 2 seconds to evaluate AMic and DMic...\r\n");
                am_util_delay_ms(2000);
                am_util_stdio_printf("Start to get audio data...\r\n");
                am_devices_led_on(am_bsp_psLEDs, 1);
                g_bAMicEvalFlag = true;
            }
#endif // AM_APP_ANALOG_MIC

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
