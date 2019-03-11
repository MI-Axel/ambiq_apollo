#ifndef STFT_H
#define STFT_H

#include <stdint.h>
#include "am_app_utils_syscall.h"

typedef struct
{
    uint16_t ui16FftLen;
    uint16_t ui16NumChannel;
    uint16_t ui16HopSize;
    bool bValueWindowed;
        
    uint16_t ui16State;
    uint16_t ui16StateOut;

    float* pfFftInBuffer;                // data buffer for STFT
    float* pfPrevSample;
}am_app_stft_instance_f32;


extern void am_app_stft_init_f32(am_app_stft_instance_f32* S, uint16_t fft_len, uint16_t channels, uint16_t hop, bool windowed_value);

#endif
