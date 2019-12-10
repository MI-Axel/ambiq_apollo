// ----------------------------------------------------------------------
// DSP Concepts Asynchronous sample rate converter coefficient file.
//
// FSin: 48000
// FSout: 48000
// Interpolation factor M: 32
// Passband frequency edge: 18000 Hz
// Stopband frequency edge: 24000 Hz
// Stopband attenuation: 80.0 dB
// Maximum measured THD and frequency
// Linear interpolation:  -76.3 dB at frequency  15750.00 Hz 
// Cubic interpolation:   -89.6 dB at frequency   7792.97 Hz 
// Length of interpolation filter: 980
// Filter iterations per sample (filter phase): 28
// Fractional fStep = 1.000000
// ----------------------------------------------------------------------
#ifndef _DSPC_ASRC_48000_TO_48000_32M_080DB_H_
#define _DSPC_ASRC_48000_TO_48000_32M_080DB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "dspc_asrc.h"

#define ASRC_PHASELEN_28 28
#define ASRC_FS_IN_48000 48000
#define ASRC_FS_OUT_48000 48000

extern DSPC_ASRC_PROPS DSPC_ASRC_48000_TO_48000_32M_080DB_PROPS;

#ifdef __cplusplus
}
#endif

#endif /* !defined DSPC_ASRC_H_ */
