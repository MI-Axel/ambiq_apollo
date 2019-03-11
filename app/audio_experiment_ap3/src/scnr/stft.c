#include "arm_math.h"
#include "arm_const_structs.h"
#include "am_app_utils.h"
#include "stft.h"

void am_app_stft_init_f32(am_app_stft_instance_f32* Sf, uint16_t fft_len, uint16_t channels, uint16_t hop, bool windowed_value)
{
    uint16_t bufferLen = 0;
    Sf->ui16FftLen = fft_len;
    Sf->ui16NumChannel = channels;
    Sf->ui16HopSize = hop;
    configASSERT((fft_len >= hop));
    Sf->bValueWindowed = windowed_value;
    bufferLen = fft_len * sizeof(float) * 2;
    Sf->pfFftInBuffer = am_alloc(bufferLen);
    bufferLen = (fft_len-hop) * sizeof(float); 
    Sf->pfPrevSample = am_alloc(bufferLen);
}

void stft_window_apply_f32(float* fft_in_buffer, const float* window_array, uint16_t fft_len)
{
    uint16_t i = 0;
    for(i=0; i<fft_len; i++ )
    {
        fft_in_buffer[i] = fft_in_buffer[i] * window_array[i];    
    }

}

void stft_buffer_update_f32(float* fft_in_buffer, float* prev_sample, float* new_sample, uint16_t fft_len, uint16_t hop)
{
    uint16_t indx = 0;
    uint16_t copyBytes = 0;
    configASSERT((fft_len >= hop));
    // old sample data rolling    
    for(indx=0; indx<(fft_len-hop); indx++)
    {
        fft_in_buffer[2*indx] = prev_sample[indx];
        fft_in_buffer[2*indx+1] = 0;
    }

    // new sample data update
    for(indx=(fft_len-hop); indx<fft_len; indx++)
    {
        fft_in_buffer[2*indx] = new_sample[indx-(fft_len-hop)];
        fft_in_buffer[2*indx+1] = 0;
    }

    // update the old sample buffer
    for(indx=2*hop; indx<2*fft_len; indx+=2)
    {
        prev_sample[indx/2-hop] = fft_in_buffer[indx];
    }
}

void stft_analysis(float* fft_in_buffer, uint16_t fft_len)
{
    const static arm_cfft_instance_f32 *S;
    switch (fft_len) {
    case 16:
       S = &arm_cfft_sR_f32_len16;
       break;
     case 32:
       S = &arm_cfft_sR_f32_len32;
       break;
     case 64:
       S = &arm_cfft_sR_f32_len64;
       break;
     case 128:
       S = &arm_cfft_sR_f32_len128;
       break;
     case 256:
       S = &arm_cfft_sR_f32_len256;
       break;
     case 512:
       S = &arm_cfft_sR_f32_len512;
       break;
     case 1024:
       S = &arm_cfft_sR_f32_len1024;
       break;
     case 2048:
       S = &arm_cfft_sR_f32_len2048;
       break;
     case 4096:
       S = &arm_cfft_sR_f32_len4096;
       break;
   }
    arm_cfft_f32(S, fft_in_buffer, 0, 1);

}
