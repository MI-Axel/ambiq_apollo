#ifndef STFT_H
#define STFT_H

#include <stdint.h>
#include <arm_math.h>

#include "config.h"
#include "am_app_utils_syscall.h"

typedef struct
{
    uint16_t ui16FftLen;
    uint16_t ui16HopSize;
    uint16_t ui16SynFrames;
    float* pfWindowBuffer;
    arm_rfft_fast_instance_f32 arm_rfft;
}am_app_stft_instance_f32;


extern void stft_init_f32(am_app_stft_instance_f32* Sf, uint16_t fft_len, uint16_t hop, uint16_t roll_frames, const float* window_buff);
extern void stft_window_apply_f32(int16_t* input_signal, float* windowed_signal, am_app_stft_instance_f32* Sf);
extern void stft_f32(am_app_stft_instance_f32* Sf, float32_t* input, float32_t* stft_output);
extern void istft_f32(am_app_stft_instance_f32* Sf, uint32_t syn_frame, float* input_buff, int16_t* output_pcm);
#endif
