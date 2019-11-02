#ifndef BEAMFORMING_H
#define BEAMFORMING_H

#include <arm_math.h>
#include "config.h"
//
// Actually, it's a end-fire beamforming instance
// So, it only supports beamforming_ch_num = 2
//
typedef struct
{
    uint32_t beamforming_ch_num;
    uint32_t fft_bin_num;               // fft frequency bins number  (=nfft//2+1)
    const float32_t* beam_weight_L;
    const float32_t* beam_weight_R;

}am_app_beamforming_instance_f32;

extern void beamforming_init_f32(am_app_beamforming_instance_f32* Bf, const float32_t* beam_left_weight, const float32_t* beam_right_weight, uint32_t nfft);
extern void endfire_beamforming(am_app_beamforming_instance_f32* Bf, float32_t* left_ch, float32_t* right_ch, float32_t* out_buff);
#endif // BEAMFORMING_H
