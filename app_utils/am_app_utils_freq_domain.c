/* this file contains frequency domain functions used in applications */

// standard lib including files
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// mcu device including files
#include "am_util.h"

// app layer including files
#include "am_app_utils.h"
#include "am_app_utils_ring_buffer.h"
#include "am_app_utils_freq_domain.h"


static void am_pcm_amplitude_mean_calc(am_app_utils_ring_buffer_t* buff, bool LRswap, uint32_t window_len, float* LR_mean_array)
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

void am_app_utils_microphone_balance(am_app_utils_ring_buffer_t* buff, uint32_t window_len, bool LRswap, uint8_t ref, float thr,  float* scalar)
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


void am_app_utils_fft(int16_t* time_buff, float* freq_buff, uint32_t fft_size)
{
    float f_time_sequence[fft_size*2];
    //
    // Convert the PDM samples to floats, and arrange them in the format
    // required by the FFT function.
    //

    for (uint32_t i = 0; i < fft_size; i++)
    {
        f_time_sequence[2*i] = time_buff[i] / 1.0;
        f_time_sequence[2*i+1] = 0.0;
    }

    //
    // Perform the FFT.
    //
    arm_cfft_f32(&arm_cfft_sR_f32_len1024, f_time_sequence, 0, 1);
    arm_cmplx_mag_f32(f_time_sequence, freq_buff, fft_size);

}

float am_app_utils_thd_calc(uint32_t base_freq_indx, float* freq_magnitude_buff, uint32_t fft_size, uint32_t sample_freq)
{
    float32_t fFrequencyUnits = 0;
    float32_t fBaseFrequency = 0;
    float64_t fMagnitudeSum = 0;
    float32_t fTHDRet = 0;
    uint32_t index = 0;
    uint32_t ui32FreqIndxLimit = 0;

    if(fft_size%2)
        ui32FreqIndxLimit = (fft_size-1)/2 + 1;
    else
        ui32FreqIndxLimit = fft_size/2 + 1;

    if(base_freq_indx > ui32FreqIndxLimit)
    {
        if(DEBUG_VERBOSE)
            am_util_stdio_printf("The target frequency is out of sample frequency limit! \r\n");
        return -1;
    }

    fFrequencyUnits = (float)sample_freq / (float) fft_size;
    fBaseFrequency = base_freq_indx * fFrequencyUnits;
    
    if(DEBUG_VERBOSE)
        am_util_stdio_printf("THD base frequency is %f. \r\n", fBaseFrequency);
    
    for(index=0; index< ui32FreqIndxLimit; index++)
    {
        if(index != base_freq_indx)
            fMagnitudeSum += freq_magnitude_buff[index];
    }
    
    fTHDRet = fMagnitudeSum / freq_magnitude_buff[base_freq_indx];

    return fTHDRet;

}


