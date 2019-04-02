/* this file contains the micro-phone calibration API */

#include "am_mikro_calibration.h"
    
uint8_t g_ui8MicCalStatus = 0;    
uint8_t g_ui8MicCalFlag = 0;
float g_pfMicScalar[2] = {1, 1};
uint32_t g_ui32WindowLen = AVERAGE_WINDOW_LENGTH;
uint32_t g_ui32SampleNum = 0;
volatile uint8_t g_ui8PcmDataReadyFlag = 0;
// dBFS calculation
//float am_audio_DB_calc(void* audio_data, uint32_t data_type, uint32_t window_len)
//{
//    configASSERT(window_len > 0);
//    uint32_t ref_value = 0;
//    float shift_mean = 0;
//
//    ref_value = 2 ^ (data_type-1);
//
//    if(window_len == 1)
//        shift_mean = audio_data[0]
//    else
//        arm_mean_f32((float32_t*)audio_data, window_len, &shift_mean)
//        
//
//
//}

void am_pcm_amplitude_mean_calc(am_app_utils_ring_buffer_t* buff, bool LRswap, uint32_t window_len, float* LR_mean_array)
{
    uint64_t ui64LeftSum = 0;
    uint64_t ui64RightSum = 0;
    uint32_t RegisterValue = 0;
    int16_t LeftPcmValue = 0;
    int16_t RightPcmValue = 0;
    uint32_t indx = 0;
    for(indx=0; indx<window_len; indx++)
    {
        am_app_utils_ring_buffer_pop(buff, &RegisterValue, 4);
        if(LRswap)
        {
            LeftPcmValue = (int16_t)((RegisterValue >> 16) & 0xffff);
            RightPcmValue = (int16_t)(RegisterValue & 0xffff);
        }
        else
        {
            RightPcmValue = (int16_t)((RegisterValue >> 16) & 0xffff);
            LeftPcmValue = (int16_t)(RegisterValue & 0xffff);
        }
        if(LeftPcmValue >= 0)
        {
            ui64LeftSum += LeftPcmValue;
        }
        else
        {
            ui64LeftSum -= LeftPcmValue;
        }
            
        if(RightPcmValue >= 0)
        {
            ui64RightSum += RightPcmValue;
        }
        else
        {
            ui64RightSum -= RightPcmValue;
        }

    }

    LR_mean_array[0] = ui64LeftSum / window_len;
    LR_mean_array[1] = ui64RightSum / window_len;
}

// microphone balance API
// buff: pcm data ring buffer used in system
// ref: which channel data is as reference. 0 means right_chan_data; 1 means left channel data. 
// thr: balance threshold
// data_bit: sample data bit
// window_len: window lenth of the average value 
// scalar[2]: calculated scalar value [left_scalar, right_scalar]

void am_audio_mikro_balance(am_app_utils_ring_buffer_t* buff, uint32_t window_len, bool LRswap, uint8_t ref, float thr,  float* scalar)
{
    float LRmeanArray[2];
    
    am_pcm_amplitude_mean_calc(buff, LRswap, window_len, LRmeanArray);

    am_util_stdio_printf("The left channel mean value: %f and right channel mean value: %f. \r\n", LRmeanArray[0], LRmeanArray[1]);
        
    if(((LRmeanArray[1] - LRmeanArray[0]) >= thr) || ((LRmeanArray[0] - LRmeanArray[1]) >= thr))
    {
        if(ref == 1)
        {
            scalar[0] = LRmeanArray[1] / LRmeanArray[0];
            scalar[1] = 1;
            am_util_stdio_printf("Take right channel as reference. \r\n");
            am_util_stdio_printf("the left scalar: %f and the right scalar: %f. \r\n", scalar[0], scalar[1]);
        }    
        else if(ref == 0)
        {
            scalar[1] = LRmeanArray[1] / LRmeanArray[0];
            scalar[0] = 1;
            am_util_stdio_printf("Take left channel as reference. \r\n");
            am_util_stdio_printf("the left scalar: %f and the right scalar: %f. \r\n", scalar[0], scalar[1]);
        }
    }
}
