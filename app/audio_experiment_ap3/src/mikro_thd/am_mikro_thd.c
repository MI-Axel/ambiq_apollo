/* this file is the source file of the micro-phone THD calculation API */

#include "am_mikro_thd.h"


void am_pcm_fft(int16_t* time_buff, float* freq_buff, uint32_t fft_size)
{
    float f_time_sequence[fft_size*2];
    //
    // Convert the PDM samples to floats, and arrange them in the format
    // required by the FFT function.
    //
#if configUSE_DATA_VERBOSE
//    am_util_stdio_printf("The input data of time domain:\n\r");
#endif // configUSE_DATA_VERBOSE

    for (uint32_t i = 0; i < fft_size; i++)
    {

#if configUSE_DATA_VERBOSE
//        am_util_stdio_printf("%d\n\r", time_buff[i]);
#endif // configUSE_DATA_VERBOSE

        f_time_sequence[2*i] = time_buff[i] / 1.0;
        f_time_sequence[2*i+1] = 0.0;
    }

#if configUSE_DATA_VERBOSE
//        am_util_stdio_printf("END\n\r");
#endif // configUSE_DATA_VERBOSE
    //
    // Perform the FFT.
    //
    arm_cfft_f32(&arm_cfft_sR_f32_len1024, f_time_sequence, 0, 1);
    arm_cmplx_mag_f32(f_time_sequence, freq_buff, fft_size);

#if configUSE_DATA_VERBOSE
//    am_util_stdio_printf("FFT result:\r\n");
    for (uint32_t i = 0; i < fft_size/2; i++)
    {
//            am_util_stdio_printf("%f\n\r", freq_buff[i]);
    }

//     am_util_stdio_printf("END\n\r");
#endif // configUSE_DATA_VERBOSE

}

float am_thd_calc(uint32_t base_freq_indx, float* freq_magnitude_buff, uint32_t fft_size, uint32_t sample_freq)
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
        am_util_stdio_printf("The target frequency is out of sample frequency limit! \r\n");
        return -1;
    }

    fFrequencyUnits = (float)sample_freq / (float) fft_size;
#if configUSE_DATA_VERBOSE
    fBaseFrequency = base_freq_indx * fFrequencyUnits;
    am_util_stdio_printf("THD base frequency is %f. \r\n", fBaseFrequency);
#endif // configUSE_DATA_VERBOSE
    for(index=0; index< ui32FreqIndxLimit; index++)
    {
        if(index != base_freq_indx)
            fMagnitudeSum += freq_magnitude_buff[index];
    }
    
    fTHDRet = fMagnitudeSum / freq_magnitude_buff[base_freq_indx];

    return fTHDRet;

}

