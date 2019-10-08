#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "am_app_utils.h"
#include "am_app_utils_ring_buffer.h"
#include "audio_preprocessor.h"


void audio_fft_frame_concatenate(int16_t* prev, int16_t* hop_buff, int16_t* ret, uint32_t hop, uint32_t fft_len)
{
    configASSERT(fft_len >= hop);
    configASSERT(2*hop > fft_len)
    memcpy(ret, prev, (fft_len-hop)*sizeof(int16_t));
    memcpy(&ret[fft_len-hop], hop_buff, hop*sizeof(int16_t));
    //
    // update the previous frame
    //
    memcpy(prev, &hop_buff[2*hop-fft_len], (fft_len-hop)*sizeof(int16_t));

//    for(uint32_t indx=0; indx< fft_len; indx++)
//    {
//        ret[indx] = (float) temp_buff[indx];
//    }

}


//
// Endfire Beamforming fuction
// left_ch & right_ch: the output result from rfft_fast. Need to change to complx_multi format 
// fft_bin_num : fft_length/2+1
//
void audio_dual_ch_beamforming(float32_t* left_ch, float32_t* right_ch, float32_t* beam_left_weight, float32_t* beam_right_weight, uint32_t fft_bin_num, float32_t* out_buff)
{
    float32_t left_buff[fft_bin_num*2];
    float32_t right_buff[fft_bin_num*2];
    
    float32_t left_ret[fft_bin_num*2];
    float32_t right_ret[fft_bin_num*2];

    left_buff[0] = left_ch[0];
    left_buff[1] = 0;
    left_buff[fft_bin_num*2-2] = left_ch[1];
    left_buff[fft_bin_num*2-1] = 0;
    memcpy(&left_buff[2], &left_ch[2], (fft_bin_num*2-4)*sizeof(float32_t));
    
    right_buff[0] = right_ch[0];
    right_buff[1] = 0;
    right_buff[fft_bin_num*2-2] = right_ch[1];
    right_buff[fft_bin_num*2-1] = 0;
    memcpy(&right_buff[2], &right_ch[2], (fft_bin_num*2-4)*sizeof(float32_t));
    
    memset(left_ret, 0, sizeof(left_ret));
    memset(right_ret, 0, sizeof(right_ret));

    arm_cmplx_mult_cmplx_f32(left_buff, beam_left_weight, left_ret, fft_bin_num);
    arm_cmplx_mult_cmplx_f32(right_buff, beam_right_weight, right_ret, fft_bin_num);
    
    out_buff[0] = left_ret[0] + right_ret[0];
    out_buff[1] = left_ret[fft_bin_num*2-2] + right_ret[fft_bin_num*2-2];
    for(uint32_t idx=2; idx<fft_bin_num*2-2; idx++)
    {
        out_buff[idx] = left_ret[idx] + right_ret[idx];
    }
}


