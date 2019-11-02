//
// Standard Include
//
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
//
// app utils
//
#include "am_app_utils.h"
//
// Procedure config Include
//
#include "beamforming.h"

//
// beamforming instance init function
// nfft: fft length
//
void beamforming_init_f32(am_app_beamforming_instance_f32* Bf, const float32_t* beam_left_weight, const float32_t* beam_right_weight, uint32_t nfft)
{
    Bf->beamforming_ch_num = 2;             // it only supports end fire structure (2 channels) 
    Bf->fft_bin_num = (nfft/2) + 1;
    Bf->beam_weight_L = beam_left_weight;
    Bf->beam_weight_R = beam_right_weight;
}

//
// Endfire Beamforming fuction
// left_ch & right_ch: the output result from rfft_fast. Need to change to complx_multi format 
// fft_bin_num : fft_length/2+1
// output: in normal order; need reformed if feed into arm irfft
void endfire_beamforming(am_app_beamforming_instance_f32* Bf, float32_t* left_ch, float32_t* right_ch, float32_t* out_buff)
{
    float32_t left_ret[Bf->fft_bin_num*2];
    float32_t right_ret[Bf->fft_bin_num*2];
    
    memset(left_ret, 0, sizeof(left_ret));
    memset(right_ret, 0, sizeof(right_ret));

    arm_cmplx_mult_cmplx_f32(left_ch, Bf->beam_weight_L, left_ret, Bf->fft_bin_num);
    arm_cmplx_mult_cmplx_f32(right_ch, Bf->beam_weight_R, right_ret, Bf->fft_bin_num);
    
    for(uint32_t idx=0; idx<Bf->fft_bin_num*2; idx++)
    {
        out_buff[idx] = left_ret[idx] + right_ret[idx];
    }
}


