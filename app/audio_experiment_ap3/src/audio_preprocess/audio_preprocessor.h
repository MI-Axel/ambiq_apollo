#ifndef AUDIO_PREPROCESSOR_H
#define AUDIO_PREPROCESSOR_H
#include <arm_math.h>
#include "stft.h"

#define AUDIO_PREPROCESS_FFT_SIZE                   128
#define AUDIO_HOP_SIZE                              80
#define AUDIO_ROLLING_FRAMES                        3
#define AUDIO_PCM_BYTES                             4
#define AUDIO_BUFF_LENGTH                           (AUDIO_HOP_SIZE*AUDIO_ROLLING_FRAMES)
#define AUDIO_STFT_LENGTH                           (AUDIO_PREPROCESS_FFT_SIZE*AUDIO_ROLLING_FRAMES)

extern void audio_fft_frame_concatenate(int16_t* prev, int16_t* hop_buff, int16_t* ret, uint32_t hop, uint32_t fft_len);

extern void audio_dual_ch_beamforming(float32_t* left_ch, float32_t* right_ch, float32_t* beam_left_weight, float32_t* beam_right_weight, uint32_t fft_bin_num, float32_t* out_buff);

extern am_app_stft_instance_f32 Sf;
//
// rfft only calculate one side
//
extern arm_rfft_fast_instance_f32 S_arm_fft;


















#endif // AUDIO_PREPROCESSOR_H
