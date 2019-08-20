#include <stdbool.h>
#include <stdint.h>
#include "arm_math.h"
#include "arm_const_structs.h"
#include "am_app_utils.h"
#include "stft.h"
#include "board_setup.h"

void stft_init_f32(am_app_stft_instance_f32* Sf, arm_rfft_fast_instance_f32* p_armfft, uint16_t fft_len, uint16_t hop, uint16_t roll_frames, const float* window_buff)
{
    Sf->ui16FftLen = fft_len;
    Sf->ui16HopSize = hop;
    Sf->ui16SynFrames = roll_frames;
    configASSERT((fft_len >= hop));
    Sf->pfWindowBuffer = window_buff;
    Sf->p_armfft = p_armfft;
    arm_rfft_fast_init_f32(Sf->p_armfft, Sf->ui16FftLen);
}

void stft_window_apply_f32(int16_t* input_signal, float* windowed_signal, am_app_stft_instance_f32* Sf)
{
    uint16_t i = 0;
    for(i=0; i < Sf->ui16FftLen; i++)
    {
        windowed_signal[i] = input_signal[i] * Sf->pfWindowBuffer[i];
    }
}

//void stft_buffer_update_f32(float* fft_in_buffer, float* prev_sample, float* new_sample, uint16_t fft_len, uint16_t hop)
//{
//    uint16_t indx = 0;
//    uint16_t copyBytes = 0;
//    configASSERT((fft_len >= hop));
//    // old sample data rolling    
//    for(indx=0; indx<(fft_len-hop); indx++)
//    {
//        fft_in_buffer[2*indx] = prev_sample[indx];
//        fft_in_buffer[2*indx+1] = 0;
//    }
//
//    // new sample data update
//    for(indx=(fft_len-hop); indx<fft_len; indx++)
//    {
//        fft_in_buffer[2*indx] = new_sample[indx-(fft_len-hop)];
//        fft_in_buffer[2*indx+1] = 0;
//    }
//
//    // update the old sample buffer
//    for(indx=2*hop; indx<2*fft_len; indx+=2)
//    {
//        prev_sample[indx/2-hop] = fft_in_buffer[indx];
//    }
//}

void stft_f32(am_app_stft_instance_f32* Sf, float32_t* windowed_sig, float32_t* stft_result)
{
//    float32_t input[Sf->ui16FftLen*2];
//    uint32_t indx = 0;
//    for(indx=0; indx<Sf->ui16FftLen; indx++)
//    {
//        input[indx] = windowed_sig[indx];
//        input[2*indx+1] = 0.0;
//    }

    arm_rfft_fast_f32(Sf->p_armfft, windowed_sig, stft_result, 0);

}

void istft_f32(am_app_stft_instance_f32* Sf, uint32_t syn_frame, float* input_buff, int16_t* output_pcm)
{
    uint32_t indx = 0;
    uint32_t k = 0;
    uint32_t syn_audio_len = 0;
    uint32_t input_audio_len = 0;
    uint32_t rfft_len = Sf->ui16FftLen/2 + 1; 
    float input_dummy_buff[rfft_len];
    input_audio_len = 3 * syn_frame;
    syn_audio_len = Sf->ui16FftLen + (syn_frame-1) * Sf->ui16HopSize;
    float ifft_result[Sf->ui16FftLen];
    float window_sum[syn_audio_len];
    float syn_audio_buff[syn_audio_len];
    for(indx=0; indx<syn_frame; indx++)
    {
        memcpy(input_dummy_buff, &input_buff[indx*rfft_len], rfft_len*sizeof(float32_t));    
        arm_rfft_fast_f32(Sf->p_armfft, input_dummy_buff, ifft_result, 1);
        
        for(k=0; k<Sf->ui16FftLen; k++)
        {
            syn_audio_buff[k+indx*Sf->ui16HopSize] += ifft_result[k]*Sf->pfWindowBuffer[k];
            window_sum[k+indx*Sf->ui16HopSize]  += Sf->pfWindowBuffer[k]*Sf->pfWindowBuffer[k]; 
        }
    }
    //
    // Divide with window sum to re-construct the signal. NOLA needed.
    //
    for(indx=0; indx<syn_audio_len; indx++)
    {
        if(window_sum[indx]!=0)
        {
            syn_audio_buff[indx] = syn_audio_buff[indx]/window_sum[indx];
        }
        output_pcm[indx] = (int16_t)syn_audio_buff[indx];
    }
       
}
