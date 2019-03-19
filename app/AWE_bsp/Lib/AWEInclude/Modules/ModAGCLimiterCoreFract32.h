/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAGCLimiterCoreFract32.h
****************************************************************************
*
*     Description:  Soft knee gain computer for use in peak limiters
*
*     Copyright:    DSP Concepts, Inc, 2007 - 2017
*                   1800 Wyatt Drive, Suite 14
*                   Santa Clara, CA 95054
*
***************************************************************************/

/**
 * @addtogroup Modules
 * @{
 */

/**
 * @file
 * @brief Soft knee gain computer for use in peak limiters
 */

#ifndef _MOD_AGCLIMITERCOREFRACT32_H
#define _MOD_AGCLIMITERCOREFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_AGCLimiterCoreFract32_threshold 0x00000100
#define MASK_AGCLimiterCoreFract32_outputGain 0x00000200
#define MASK_AGCLimiterCoreFract32_slope 0x00000400
#define MASK_AGCLimiterCoreFract32_kneeDepth 0x00000800
#define MASK_AGCLimiterCoreFract32_ratio 0x00001000
#define MASK_AGCLimiterCoreFract32_attackTime 0x00002000
#define MASK_AGCLimiterCoreFract32_decayTime 0x00004000
#define MASK_AGCLimiterCoreFract32_sharpnessFactor 0x00008000
#define MASK_AGCLimiterCoreFract32_sharpnessFactorFract32 0x00010000
#define MASK_AGCLimiterCoreFract32_attackCoeff 0x00020000
#define MASK_AGCLimiterCoreFract32_decayCoeff 0x00040000
#define MASK_AGCLimiterCoreFract32_envState 0x00080000
#define MASK_AGCLimiterCoreFract32_currentGain 0x00100000
#define MASK_AGCLimiterCoreFract32_thresholdFract32 0x00200000
#define MASK_AGCLimiterCoreFract32_kneeDepthFract32 0x00400000
#define MASK_AGCLimiterCoreFract32_gainFract32 0x00800000
#define OFFSET_AGCLimiterCoreFract32_threshold 0x00000008
#define OFFSET_AGCLimiterCoreFract32_outputGain 0x00000009
#define OFFSET_AGCLimiterCoreFract32_slope 0x0000000A
#define OFFSET_AGCLimiterCoreFract32_kneeDepth 0x0000000B
#define OFFSET_AGCLimiterCoreFract32_ratio 0x0000000C
#define OFFSET_AGCLimiterCoreFract32_attackTime 0x0000000D
#define OFFSET_AGCLimiterCoreFract32_decayTime 0x0000000E
#define OFFSET_AGCLimiterCoreFract32_sharpnessFactor 0x0000000F
#define OFFSET_AGCLimiterCoreFract32_sharpnessFactorFract32 0x00000010
#define OFFSET_AGCLimiterCoreFract32_attackCoeff 0x00000011
#define OFFSET_AGCLimiterCoreFract32_decayCoeff 0x00000012
#define OFFSET_AGCLimiterCoreFract32_envState 0x00000013
#define OFFSET_AGCLimiterCoreFract32_currentGain 0x00000014
#define OFFSET_AGCLimiterCoreFract32_thresholdFract32 0x00000015
#define OFFSET_AGCLimiterCoreFract32_kneeDepthFract32 0x00000016
#define OFFSET_AGCLimiterCoreFract32_gainFract32 0x00000017

#define CLASSID_AGCLIMITERCOREFRACT32 (CLASS_ID_MODBASE + 130)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAGCLimiterCoreFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            threshold;           // Amplitude level at which the AGC Limiter Core reduces its output gain value
    FLOAT32            outputGain;          // Value used to scale the output of the AGC Limiter Core
    fract32            slope;               // TBD
    FLOAT32            kneeDepth;           // Knee depth controls the sharpness of the transition between no limiting and limiting
    FLOAT32            ratio;               // Slope of the output attenuation when the signal is above threshold - derived from the standard compression ratio parameter by the formula slope = 1.0 - (1.0/ratio)
    FLOAT32            attackTime;          // Envelope detector attack time constant
    FLOAT32            decayTime;           // Envelope detector decay time constant
    FLOAT32            sharpnessFactor;     // TBD
    fract32            sharpnessFactorFract32; // TBD
    fract32            attackCoeff;         // TBD
    fract32            decayCoeff;          // TBD
    fract32            envState;            // TBD
    fract32            currentGain;         // Instanteous gain applied at the end of the block
    fract32            thresholdFract32;    // threshold - in 8.24 "base2 dB"
    fract32            kneeDepthFract32;    // kneeDepth - in 8.24 "base2 dB"
    fract32            gainFract32;         // outputGain - in 8.24 "base2 dB"
    
} awe_modAGCLimiterCoreFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAGCLimiterCoreFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modAGCLimiterCoreFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_AGCLIMITERCOREFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modAGCLimiterCoreFract32Process(void *pInstance);

UINT32 awe_modAGCLimiterCoreFract32Set(void *pInstance, UINT32 mask);
 

void awe_modAGCLimiterCoreFract32Bypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_AGCLIMITERCOREFRACT32_H

/**
 * @}
 *
 * End of file.
 */
