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

#if AM_AEP_SCNR_TEST
#include "stft.h"
#endif // AM_AEP_SCNR_TEST

#if AM_AEP_MIKRO_CALIBRATION
#include "am_mikro_calibration.h"
#endif // AM_AEP_MIKRO_CALIBRATION

#if AM_AEP_MIKRO_THD_CALC
#include "am_mikro_thd.h"
#include "am_AEP_local_test_data.h"

#endif // AM_AEP_MIKRO_THD_CALC

#if AM_AEP_AUDIO_BUFFER_TEST
#include "am_audio_buffer.h"
#endif // AM_AEP_AUDIO_BUFFER_TEST

#if AM_AEP_STFT_TEST
#include "stft.h"
#include "am_AEP_local_test_data.h"
#include "hanning_window.h"
#endif // AM_AEP_STFT_TEST

#if AM_AEP_BEAMFORMING_TEST
#include "hanning_window.h"
#include "stft.h"
#include "audio_preprocessor.h"
#include "am_AEP_local_test_data.h"
uint32_t g_ui32DMicDataCollectFlag = 0;

#endif // AM_AEP_BEAMFORMING_TEST

#if AM_AEP_DIGITAL_FILTER_TEST
#include "digital_filter.h"
#include "am_AEP_local_test_data.h"
#endif // AM_AEP_DIGITAL_FILTER_TEST


int main(void)
{
    am_app_AEP_sys_init();
#if configUSE_SYSVIEW
    SEGGER_SYSVIEW_Conf(); // initialize SystemView
    SEGGER_SYSVIEW_Start(); // start SystemView
    SEGGER_SYSVIEW_OnIdle();          /* Tells SystemView that System is currently in "Idle"*/
#endif // configUSE_SYSVIEW

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

#if AM_AEP_STFT_TEST
#define PRINT_PCM_DATA                              0
#define PRINT_STFT_DATA                             1
#define PRINT_MAGNITUDE_DATA                        0
#define PRINT_ISTFT_DATA                            0
#define LOCAL_DATA_TEST                             1

#define AUDIO_PREPROCESS_FFT_SIZE                   128
#define AUDIO_HOP_SIZE                              80
#define AUDIO_ROLLING_FRAMES                        3
#define AUDIO_BUFF_LENGTH                           (AUDIO_PREPROCESS_FFT_SIZE+(AUDIO_ROLLING_FRAMES-1)*AUDIO_HOP_SIZE)
#define AUDIO_STFT_LENGTH                           (AUDIO_PREPROCESS_FFT_SIZE*AUDIO_ROLLING_FRAMES)
int16_t g_pin16PCMDataBuffer[AUDIO_BUFF_LENGTH];
float g_pfWindowedPcmDataBuff[AUDIO_PREPROCESS_FFT_SIZE*AUDIO_ROLLING_FRAMES];
float g_fFftOutBuff[AUDIO_STFT_LENGTH+10];
float g_pfIstftOutBuff[AUDIO_BUFF_LENGTH];
float g_fFftMagnitudes[AUDIO_PREPROCESS_FFT_SIZE];
int16_t g_pin16SynPCMOutput[AUDIO_BUFF_LENGTH];
#endif // AM_AEP_STFT_TEST

#if AM_AEP_DIGITAL_FILTER_TEST
#define LOCAL_DATA_TEST                             1
#define LOCAL_TEST_LENGTH                           1024
high_pass_filterType* PCM_HP_filter; 
PCM_HP_filter = high_pass_filter_create();
#endif // AM_AEP_DIGITAL_FILTER_TEST



    //
    // Print the banner.
    //
    DebugLog("Audio test starts!\r\n\n");

#if AM_AEP_STFT_TEST
    uint32_t indx = 0;
    uint32_t k = 0;
    float fMaxValue;
    uint32_t ui32MaxIndex;
    uint32_t ui32LoudestFrequency;
    uint32_t g_ui32SampleFreq = 16000;
    if(LOCAL_DATA_TEST)
    {
        DebugLog("Using local data to test STFT...\n\r");
        for(indx=0; indx<AUDIO_BUFF_LENGTH;indx++)
        {
            g_pin16PCMDataBuffer[indx] = g_in16TestInput_2KHZ_SR16K[indx]; 
        }
    }
    am_app_stft_instance_f32 Sf;
//
// rfft only calculate one side
//
    arm_rfft_fast_instance_f32 S_arm_fft;

    stft_init_f32(&Sf, &S_arm_fft, AUDIO_PREPROCESS_FFT_SIZE, AUDIO_HOP_SIZE, AUDIO_ROLLING_FRAMES, g_f32HanningWindow);

    for(indx=0; indx<AUDIO_ROLLING_FRAMES; indx++)
    {
        stft_window_apply_f32(&g_pin16PCMDataBuffer[indx*AUDIO_HOP_SIZE], &g_pfWindowedPcmDataBuff[indx*AUDIO_PREPROCESS_FFT_SIZE], &Sf);
        stft_f32(&Sf, &g_pfWindowedPcmDataBuff[indx*AUDIO_PREPROCESS_FFT_SIZE], &g_fFftOutBuff[indx*(AUDIO_PREPROCESS_FFT_SIZE)]);
    }
    if(PRINT_PCM_DATA)
    {
        DebugLog("PCM data as following:\r\n");
        for(k =0; k<AUDIO_PREPROCESS_FFT_SIZE*AUDIO_ROLLING_FRAMES; k++)
        {           
            if((k%4)==0)
                DebugLog("\n\r");
            DebugLogFloat(g_pfWindowedPcmDataBuff[k]);
            DebugLog(", ");
        }
        DebugLog("The End...\n\n\r");
  
    }

    if(PRINT_STFT_DATA)
    {
        DebugLog("STFT result of 1 local frame:\r\n");
        for(indx =0; indx<AUDIO_STFT_LENGTH; indx++)
        {
            if((indx%4)==0)
                DebugLog("\n\r");
            DebugLogFloat(g_fFftOutBuff[indx]);
            DebugLog(", ");
        }
        DebugLog("The End...\n\r");
    }
   istft_f32(&Sf, AUDIO_ROLLING_FRAMES, g_fFftOutBuff, g_pin16SynPCMOutput); 
    if(PRINT_ISTFT_DATA)
    {
        DebugLog("ISTFT result of 1 local frame:\r\n");
        for(indx =0; indx<AUDIO_BUFF_LENGTH; indx++)
        {
            if((indx%4)==0)
                DebugLog("\n\r");
            DebugLogFloat(g_pin16SynPCMOutput[indx]);
            DebugLog(", ");
        }
        DebugLog("The End...\n\r");
    }
    
//    arm_cmplx_mag_f32(Sf.pfStftBuffer, g_fFftMagnitudes, Sf.ui16FftLen);
    //
    // Find the frequency bin with the largest magnitude.
    //
//    arm_max_f32(g_fFftMagnitudes, Sf.ui16FftLen / 2, &fMaxValue, &ui32MaxIndex);

//    ui32LoudestFrequency = (g_ui32SampleFreq * ui32MaxIndex) / Sf.ui16FftLen;

//    am_util_stdio_printf("Loudest frequency: %d        \n\n\r", ui32LoudestFrequency);

//    if(PRINT_MAGNITUDE_DATA)
//    {
//        DebugLog("STFT Magnitude result of 1 local frame:\r\n");
//        for(indx =0; indx<AUDIO_PREPROCESS_FFT_SIZE; indx++)
//        {
//            if((indx%4)==0)
//                DebugLog("\n\r");
//            DebugLogFloat(g_fFftMagnitudes[indx]);
//            DebugLog(", ");
//        }
//        DebugLog("The End...\n\r");
//    }

#endif // AM_AEP_STFT_TEST

#if AM_AEP_DIGITAL_FILTER_TEST
uint32_t indx = 0;
float g_pfDigitalFilterTestInput[LOCAL_TEST_LENGTH];
float g_pfDigitalFilterTestOutput[10+LOCAL_TEST_LENGTH];
int32_t g_in32FilterRet;

if(LOCAL_DATA_TEST)
{
    DebugLog("Using local data to test digital filter...\n\r");

    for(indx=0; indx<LOCAL_TEST_LENGTH;indx++)
    {
        g_pfDigitalFilterTestInput[indx] = g_in16TestInput_2KHZ_SR16K[indx] / 1.0; 
    }
#if configUSE_MEASURE_MIPS
    reset_timer(); //reset timer
    start_timer(); //reset timer
#endif // configUSE_MEASURE_MIPS

    g_in32FilterRet = high_pass_filter_filterBlock(PCM_HP_filter, g_pfDigitalFilterTestInput, 
            g_pfDigitalFilterTestOutput,LOCAL_TEST_LENGTH);

#if configUSE_MEASURE_MIPS
    stop_timer(); //reset timer
    mips_update(); //read number of cycles 
#endif // configUSE_MEASURE_MIPS
//    DebugLog("Digital filter output...\n\r");
//    for(indx =0; indx<LOCAL_TEST_LENGTH+10; indx++)
//    {
//            if((indx%8)==0)
//                DebugLog("\n\r");
//            DebugLogFloat(g_pfDigitalFilterTestOutput[indx]);
//            DebugLog(", ");
//    }
//    DebugLog("The End...\n\r");

}

#endif // AM_AEP_DIGITAL_FILTER_TEST

#if AM_AEP_BEAMFORMING_TEST
#define AUDIO_PREPROCESS_FFT_SIZE                   128
#define AUDIO_HOP_SIZE                              80
#define AUDIO_ROLLING_FRAMES                        3
#define AUDIO_BUFF_LENGTH                           (AUDIO_HOP_SIZE*AUDIO_ROLLING_FRAMES)
#define AUDIO_STFT_LENGTH                           (AUDIO_PREPROCESS_FFT_SIZE*AUDIO_ROLLING_FRAMES)

#define PRINT_PCM_DATA                              0
#define PRINT_STFT_DATA                             0
#define PRINT_ISTFT_DATA                            1

uint32_t indx, k, i, idx;

uint32_t g_pui32AudioProBuff[AUDIO_HOP_SIZE];
int16_t* g_pin16PcmPtr;

int16_t g_pin16LeftChPrev[AUDIO_PREPROCESS_FFT_SIZE-AUDIO_HOP_SIZE]={0};
int16_t g_pin16RightChPrev[AUDIO_PREPROCESS_FFT_SIZE-AUDIO_HOP_SIZE]={0};
int16_t g_pin16LeftChBuff[AUDIO_HOP_SIZE];
int16_t g_pin16RightChBuff[AUDIO_HOP_SIZE];
int16_t g_pin16LeftConcaBuff[AUDIO_PREPROCESS_FFT_SIZE];
float32_t g_pfFftInBuff[AUDIO_PREPROCESS_FFT_SIZE];
float32_t g_pfFftOutBuff[AUDIO_STFT_LENGTH];
float32_t g_pfFftOutCopy[AUDIO_STFT_LENGTH];
int16_t g_pin16SynAudioBuff[AUDIO_BUFF_LENGTH];
float32_t g_pfIfftTest[AUDIO_PREPROCESS_FFT_SIZE];
am_app_stft_instance_f32 Sf;
//
// rfft only calculate one side
//
arm_rfft_fast_instance_f32 S_arm_fft;

stft_init_f32(&Sf, &S_arm_fft, AUDIO_PREPROCESS_FFT_SIZE, AUDIO_HOP_SIZE, AUDIO_ROLLING_FRAMES, g_f32HanningWindow);


am_util_stdio_printf("The virtual keyboard address: 0x%08X\n\r", &g_sysKeyValue);

#endif // AM_AEP_BEAMFORMING_TEST

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

#if AM_AEP_MIKRO_CALIBRATION
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

#if AM_AEP_MIKRO_THD_CALC
        
        if(g_ui8THDTestStartFlag == 1)
        {
            g_ui8THDTestStartFlag = 0;
            am_pcm_fft(g_in16TestInput_2KHZ_SR16K, g_fTHDMagnitudes, THD_FFT_SIZE);
            g_fTHDResult = am_thd_calc(128, g_fTHDMagnitudes, THD_FFT_SIZE, 16000);

            am_util_stdio_printf("THD result: %0.6f.\r\n", g_fTHDResult);
        }

#endif // AM_AEP_MIKRO_THD_CALC

#if AM_AEP_BEAMFORMING_TEST
    if(g_ui32DMicDataCollectFlag == 1)
    {
        DebugLog("Start to record audio in 2 secs...\n\r");

        am_util_delay_ms(2000);

        g_audioRunningFlag = 1;

        while(g_ui8PcmDataReadyFlag == 0);
//
// This part is used to upload microphone data to jupyter notebook
//
//        if(g_ui8PcmDataReadyFlag == 1)
//        {
//            g_audioRunningFlag = 0;
//            g_ui32DMicDataCollectFlag = 0;
//            g_ui8PcmDataReadyFlag = 0;
//            g_ui32AudioFrameSum = 0;
//            am_devices_led_off(am_bsp_psLEDs, 3);
//            DebugLog("Audio recording is terminated and data starts to upload:\n\r");
//
//            while(!am_app_utils_ring_buffer_empty(&am_sys_ring_buffers[AM_APP_RINGBUFF_PCM]))
//            {
//                am_app_utils_ring_buffer_pop(&am_sys_ring_buffers[AM_APP_RINGBUFF_PCM], g_pui32AudioProBuff, AUDIO_BUFF_LENGTH*PCM_DATA_BYTES);
//                g_pin16PcmPtr = g_pui32AudioProBuff;
//                for(uint32_t indx =0; indx<AUDIO_BUFF_LENGTH*2; indx++)
//                {
//                    DebugLogInt16(g_pin16PcmPtr[indx]);
//                    DebugLog(" ");
////                  DebugLog(", ");
//                    if((indx%8)==0)
//                        DebugLog("\n\r");
//
//                }
//            }
//            DebugLog("The end of data transfer...\n\r");
//        }
        if(g_ui8PcmDataReadyFlag ==1)
        {
            g_audioRunningFlag = 0;
            g_ui32DMicDataCollectFlag = 0;
            g_ui8PcmDataReadyFlag = 0;
            g_ui32AudioFrameSum = 0;
            am_devices_led_off(am_bsp_psLEDs, 3);
            DebugLog("Audio recording is terminated and data starts to upload:\n\r");
            while(!am_app_utils_ring_buffer_empty(&am_sys_ring_buffers[AM_APP_RINGBUFF_PCM]))
//            for(uint32_t frame=0; frame<2; frame++)
            {
                for(idx=0; idx<AUDIO_ROLLING_FRAMES; idx++)
                {
                    am_app_utils_ring_buffer_pop(&am_sys_ring_buffers[AM_APP_RINGBUFF_PCM], g_pui32AudioProBuff, AUDIO_HOP_SIZE*PCM_DATA_BYTES);
                    for(k=0; k<AUDIO_HOP_SIZE; k++)
                    {
                        g_pin16LeftChBuff[k] = g_pui32AudioProBuff[k] & 0x0000FFFF; 

//                        g_pin16LeftChBuff[k] = g_in16TestInput_2KHZ_SR16K[k]; 
//                        g_pin16RightChBuff[k] = (g_pui32AudioProBuff[k]>>16) & 0x0000FFFF;
                        if(PRINT_PCM_DATA)
                        {
                            DebugLogInt16(g_pin16LeftChBuff[k]);
                            DebugLog(" ");
//                    DebugLog(", ");
                            if((k+1)%8==0)
                                DebugLog("\n\r");
                        }
                    }
                    audio_fft_frame_concatenate(g_pin16LeftChPrev, g_pin16LeftChBuff, g_pin16LeftConcaBuff, AUDIO_HOP_SIZE, AUDIO_PREPROCESS_FFT_SIZE);

                    stft_window_apply_f32(g_pin16LeftConcaBuff, g_pfFftInBuff, &Sf);
                    stft_f32(&Sf, g_pfFftInBuff, &g_pfFftOutBuff[idx*AUDIO_PREPROCESS_FFT_SIZE]);
//                    for(k=0; k<Sf.ui16FftLen; k++)
//                    {
//                        am_util_stdio_printf("%f, ", g_pfFftOutBuff[k+idx*AUDIO_PREPROCESS_FFT_SIZE]);
//                        if((k+1)%8==0)
//                        {
//                            am_util_stdio_printf("\n\r");
//                        }
//                    }
                  
                    if(PRINT_STFT_DATA)
                    {
                        for(k=0; k<AUDIO_PREPROCESS_FFT_SIZE*AUDIO_ROLLING_FRAMES;k++)
                        {
                            DebugLogFloat(g_pfFftOutBuff[k]);
                            DebugLog(" ");
//                          DebugLog(", ");
                            if((k+1)%8==0)
                                DebugLog("\n\r");
                        }
                    }

                }
//                for(i=0; i < AUDIO_PREPROCESS_FFT_SIZE*AUDIO_ROLLING_FRAMES; i++)
//                {
//                    g_pfFftOutCopy[i] = g_pfFftOutBuff[i];                
//                }
                istft_f32(&Sf, AUDIO_ROLLING_FRAMES, g_pfFftOutBuff, g_pin16SynAudioBuff);
//                for(i=0; i<AUDIO_ROLLING_FRAMES; i++)
//                {
//                    arm_rfft_fast_f32(Sf.p_armfft, &g_pfFftOutBuff[i*Sf.ui16FftLen], g_pfIfftTest, 1);
//                    for(k=0; k<Sf.ui16FftLen; k++)
//                    {
//                        DebugLogFloat(g_pfIfftTest[k]);
////                        DebugLog(" ");
//                        DebugLog(", ");
//                        if((k+1)%8==0)
//                            DebugLog("\n\r");
//                    }
                   

//                }
                if(PRINT_ISTFT_DATA)
                {
                    for(indx =0; indx<AUDIO_BUFF_LENGTH; indx++)
                    {
                        DebugLogInt16(g_pin16SynAudioBuff[indx]);
//                        DebugLogFloat(g_pfIfftTest[indx]);
                        DebugLog(" ");
//                      DebugLog(", ");
                        if((indx+1)%8==0)
                            DebugLog("\n\r");
                    }
                }
            }
            DebugLog("The end of data transfer...\n\r");
        }
    }
#endif // AM_AEP_BEAMFORMING_TEST


        
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

#if AM_AEP_MIKRO_CALIBRATION
            if(g_ui8MicCalStatus == 1)
            {
                g_ui8MicCalStatus = 0;
            }
            else if(g_ui8MicCalStatus == 0)
            {
                g_ui8MicCalStatus = 1;
                am_devices_led_on(am_bsp_psLEDs, 1);
            }
#endif // AM_AEP_MIKRO_CALIBRATION

#if AM_AEP_BEAMFORMING_TEST
    if(g_ui32DMicDataCollectFlag == 0)
    {
        g_ui32DMicDataCollectFlag = 1;
        am_devices_led_on(am_bsp_psLEDs, 3);
    }
#endif // AM_AEP_BEAMFORMING_TEST


        }

    //
    // Go to Deep Sleep.
    //
//        am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_DEEP);

//        am_hal_interrupt_master_enable();
    }

}
