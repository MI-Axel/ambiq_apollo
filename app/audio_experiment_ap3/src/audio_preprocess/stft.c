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
    uint32_t i = 0;
    uint32_t k = 0;
    uint32_t syn_audio_len = 0;
    uint32_t coinciden_len = 0;
    // array length concludes real and image
    float32_t input_dummy_buff[Sf->ui16FftLen];
    syn_audio_len = Sf->ui16FftLen + (syn_frame-1) * Sf->ui16HopSize;
    coinciden_len = Sf->ui16FftLen - Sf->ui16HopSize;
    float32_t ifft_result[Sf->ui16FftLen];
    float32_t window_sum[syn_audio_len];
    float32_t syn_audio_buff[syn_audio_len];
    memset(window_sum, 0, syn_audio_len*sizeof(float32_t));
    memset(syn_audio_buff, 0, syn_audio_len*sizeof(float32_t));

    for(i=0; i<syn_frame; i++)
    {
        memcpy(input_dummy_buff, &input_buff[i*Sf->ui16FftLen], Sf->ui16FftLen*sizeof(float32_t));    
        arm_rfft_fast_f32(Sf->p_armfft, input_dummy_buff, ifft_result, 1);
        for(k=0; k<Sf->ui16FftLen; k++)
        {
//            if ((ifft_result[k] < 0.01) && (ifft_result[k] > -0.01))
//            {
//                ifft_result[k] = 0;
//            }
            syn_audio_buff[k+i*Sf->ui16HopSize] += ifft_result[k]*Sf->pfWindowBuffer[k];
            window_sum[k+i*Sf->ui16HopSize]  += Sf->pfWindowBuffer[k]*Sf->pfWindowBuffer[k]; 
        }
        memset(input_dummy_buff, 0, Sf->ui16FftLen*sizeof(float32_t));
        if(0)
        {
            for(uint32_t indx =0; indx<Sf->ui16FftLen; indx++)
            {
                  DebugLogFloat(ifft_result[indx]);
//                  DebugLogFloat(window_sum[indx]);
                  DebugLog(" ");
//                DebugLog(", ");
                  if((indx+1)%8==0)
                      DebugLog("\n\r");
            }

        }

    }
        if(0)
        {
//            for(uint32_t indx =0; indx<syn_audio_len; indx++)
//            {
////                  DebugLogFloat(ifft_result[indx]);
//                  DebugLogFloat(syn_audio_buff[indx]);
//                  DebugLog(" ");
////                DebugLog(", ");
//                  if((indx+1)%8==0)
//                      DebugLog("\n\r");
//            }
            for(uint32_t indx =0; indx<syn_audio_len; indx++)
            {
                  DebugLogFloat(ifft_result[indx]);
//                  DebugLogFloat(window_sum[indx]);
                  DebugLog(" ");
//                DebugLog(", ");
                  if((indx+1)%8==0)
                      DebugLog("\n\r");
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
//            DebugLogUInt32(i);
        }
        output_pcm[i-coinciden_len] = (int16_t)syn_audio_buff[i];
//        output_pcm[i] = (int16_t)syn_audio_buff[i];
    }
       
}


