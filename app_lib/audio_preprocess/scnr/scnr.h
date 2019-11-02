#ifndef SCNR_H
#define SCNR_H

#include <stdint.h>
#include <math.h>
#include "arm_math.h"
#include "am_app_utils_syscall.h"
#include "config.h"


typedef struct
{
    uint32_t ui32FftLen;
    uint32_t ui32BinNum;
    float32_t fdB_reduc;
    uint32_t ui32LookbackFrames;
    float32_t fBeta;
    float32_t fAlpha;
    float32_t fGmin;

    float32_t* fp_prev;
    float32_t* fp_sn;
    float32_t* fp_n;
}am_app_scnr_instance_f32;

extern void scnr_init(am_app_scnr_instance_f32* scnr, uint32_t nfft, float32_t db_reduc, uint32_t lookback, float32_t beta, float32_t alpha);

extern void scnr_process(am_app_scnr_instance_f32* scnr, float32_t* roll_buff_mag, float32_t* roll_buff_cmplx);

#endif
