#ifndef SCNR_H
#define SCNR_H

#include <stdint.h>
#include "arm_math.h"
#include "am_app_utils_syscall.h"

typedef struct
{
    uint16_t ui16FftLen;
    uint16_t ui16BinNum;
    uint16_t ui16dB_reduc;
    uint16_t ui16LookbackFrames;
    uint16_t ui16Beta;
    uint16_t ui16Alpha;
    float32_t fGmin;

    float32_t* fp_prev;
    float32_t* fp_sn;
    float32_t* fp_n;
}am_app_scnr_instance_f32;

#endif
