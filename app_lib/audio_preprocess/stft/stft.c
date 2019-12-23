#include <stdbool.h>
#include <stdint.h>
#include "arm_math.h"
#include "arm_const_structs.h"
#include "am_app_utils.h"
#include "stft.h"

void stft_init_f32(am_app_stft_instance_f32* Sf, uint16_t fft_len, uint16_t hop, uint16_t roll_frames, const float* window_buff)
{
    Sf->ui16FftLen = fft_len;
    Sf->ui16HopSize = hop;
    Sf->ui16SynFrames = roll_frames;
    configASSERT((fft_len >= hop));
    Sf->pfWindowBuffer = window_buff;
    arm_rfft_fast_init_f32(&(Sf->arm_rfft), Sf->ui16FftLen);
}

void stft_window_apply_f32(int16_t* input_signal, float* windowed_signal, am_app_stft_instance_f32* Sf)
{
    uint16_t i = 0;
    for(i=0; i < Sf->ui16FftLen; i++)
    {
        windowed_signal[i] = input_signal[i] * Sf->pfWindowBuffer[i];
    }
}

//
// STFT function
// input: windowed audio signal
// output: stft complex result of (nfft//2+1) complex pairs (nfft+2 elements) with freq-increasing order
//
void stft_f32(am_app_stft_instance_f32* Sf, float32_t* windowed_sig, float32_t* stft_result)
{
    uint32_t fft_bin_num = Sf->ui16FftLen + 2;
    ALLOC(pf_rfftRet, (Sf->ui16FftLen), float32_t);
    arm_rfft_fast_f32(&(Sf->arm_rfft), windowed_sig, pf_rfftRet, 0);
    //
    // arm rfft return value format is tricky. Needs to be reformed for future use
    //
    stft_result[0] = pf_rfftRet[0];
    stft_result[1] = 0;
    stft_result[fft_bin_num-2] = pf_rfftRet[1];
    stft_result[fft_bin_num-1] = 0;
    memcpy(&stft_result[2], &pf_rfftRet[2], (fft_bin_num-4)*sizeof(float32_t));

}

void istft_f32(am_app_stft_instance_f32* Sf, uint32_t syn_frame, float32_t* input_buff, int16_t* output_pcm)
{
    uint32_t i = 0;
    uint32_t k = 0;
    uint32_t syn_audio_len = 0;
    uint32_t coinciden_len = 0;
    uint32_t cmplx_bins = 0;
    // array length concludes real and image
//    float32_t input_dummy_buff[Sf->ui16FftLen];
    //
    // initialize the internal buffer for calculation
    //
    syn_audio_len = Sf->ui16FftLen + (syn_frame-1) * Sf->ui16HopSize;
    coinciden_len = Sf->ui16FftLen - Sf->ui16HopSize;
// 2 * complex pairs
    cmplx_bins = Sf->ui16FftLen + 2;

    ALLOC(input_reform_buff, Sf->ui16FftLen, float32_t);
    ALLOC(ifft_result, Sf->ui16FftLen, float32_t);
    ALLOC(window_sum, syn_audio_len, float32_t);
    ALLOC(syn_audio_buff, syn_audio_len, float32_t);
    memset(window_sum, 0, syn_audio_len*sizeof(float32_t));
    memset(syn_audio_buff, 0, syn_audio_len*sizeof(float32_t));


    for(i=0; i<syn_frame; i++)
    {
        //
        // need to reform input format to feed arm irfft
        //
        input_reform_buff[0] = input_buff[i*cmplx_bins]; 
        input_reform_buff[1] = input_buff[(i+1)*cmplx_bins-2];
        memcpy(&input_reform_buff[2], &input_buff[i*cmplx_bins+2], (cmplx_bins-4)*sizeof(float32_t));    
        arm_rfft_fast_f32(&(Sf->arm_rfft), input_reform_buff, ifft_result, 1);
        for(k=0; k<Sf->ui16FftLen; k++)
        {
            syn_audio_buff[k+i*Sf->ui16HopSize] += ifft_result[k]*Sf->pfWindowBuffer[k];
            window_sum[k+i*Sf->ui16HopSize]  += Sf->pfWindowBuffer[k]*Sf->pfWindowBuffer[k]; 
        }
    }
    
    //
    // Divide with window sum to re-construct the signal. NOLA needed.
    //
    for(i=coinciden_len; i<Sf->ui16HopSize+coinciden_len; i++)
//    for(i=0; i<syn_audio_len-coinciden_len; i++)
    {

        if(window_sum[i] > 0.000001)
        {
            syn_audio_buff[i] = syn_audio_buff[i]/window_sum[i];
        }
        else
        {
            syn_audio_buff[i] = syn_audio_buff[i]/0.000001;
        }
        output_pcm[i-coinciden_len] = (int16_t)syn_audio_buff[i];
    }
       
}


