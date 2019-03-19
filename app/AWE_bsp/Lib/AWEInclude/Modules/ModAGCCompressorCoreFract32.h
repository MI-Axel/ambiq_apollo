/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAGCCompressorCoreFract32.h
****************************************************************************
*
*     Description:  Gain computer for use in Compressor
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
 * @brief Gain computer for use in Compressor
 */

#ifndef _MOD_AGCCOMPRESSORCOREFRACT32_H
#define _MOD_AGCCOMPRESSORCOREFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_AGCCompressorCoreFract32_threshold 0x00000100
#define MASK_AGCCompressorCoreFract32_gain 0x00000200
#define MASK_AGCCompressorCoreFract32_ratio 0x00000400
#define MASK_AGCCompressorCoreFract32_attackTime 0x00000800
#define MASK_AGCCompressorCoreFract32_attackTimeMin 0x00001000
#define MASK_AGCCompressorCoreFract32_decayTime 0x00002000
#define MASK_AGCCompressorCoreFract32_decayTimeMin 0x00004000
#define MASK_AGCCompressorCoreFract32_currentGain 0x00008000
#define MASK_AGCCompressorCoreFract32_thresholdFract32 0x00010000
#define MASK_AGCCompressorCoreFract32_gainFract32 0x00020000
#define MASK_AGCCompressorCoreFract32_slope 0x00040000
#define MASK_AGCCompressorCoreFract32_sharpnessFactor 0x00080000
#define MASK_AGCCompressorCoreFract32_attackCoeff 0x00100000
#define MASK_AGCCompressorCoreFract32_attackCoeffSmoothing 0x00200000
#define MASK_AGCCompressorCoreFract32_decayCoeff 0x00400000
#define MASK_AGCCompressorCoreFract32_decayCoeffSmoothing 0x00800000
#define MASK_AGCCompressorCoreFract32_envState 0x01000000
#define OFFSET_AGCCompressorCoreFract32_threshold 0x00000008
#define OFFSET_AGCCompressorCoreFract32_gain 0x00000009
#define OFFSET_AGCCompressorCoreFract32_ratio 0x0000000A
#define OFFSET_AGCCompressorCoreFract32_attackTime 0x0000000B
#define OFFSET_AGCCompressorCoreFract32_attackTimeMin 0x0000000C
#define OFFSET_AGCCompressorCoreFract32_decayTime 0x0000000D
#define OFFSET_AGCCompressorCoreFract32_decayTimeMin 0x0000000E
#define OFFSET_AGCCompressorCoreFract32_currentGain 0x0000000F
#define OFFSET_AGCCompressorCoreFract32_thresholdFract32 0x00000010
#define OFFSET_AGCCompressorCoreFract32_gainFract32 0x00000011
#define OFFSET_AGCCompressorCoreFract32_slope 0x00000012
#define OFFSET_AGCCompressorCoreFract32_sharpnessFactor 0x00000013
#define OFFSET_AGCCompressorCoreFract32_attackCoeff 0x00000014
#define OFFSET_AGCCompressorCoreFract32_attackCoeffSmoothing 0x00000015
#define OFFSET_AGCCompressorCoreFract32_decayCoeff 0x00000016
#define OFFSET_AGCCompressorCoreFract32_decayCoeffSmoothing 0x00000017
#define OFFSET_AGCCompressorCoreFract32_envState 0x00000018

#define CLASSID_AGCCOMPRESSORCOREFRACT32 (CLASS_ID_MODBASE + 1202)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAGCCompressorCoreFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            threshold;           // Amplitude level at which the AGC Limiter Core reduces its output gain value.
    FLOAT32            gain;                // Value used to scale the output of the AGC Limiter Core.
    FLOAT32            ratio;               // Slope of the output attenuation when the signal is above threshold - derived from the standard compression ratio parameter by the formula slope = 1.0 - (1.0/ratio).
    FLOAT32            attackTime;          // Envelope detector attack time constant.
    FLOAT32            attackTimeMin;       // Minimum value of the attack time constant.
    FLOAT32            decayTime;           // Envelope detector decay time constant.
    FLOAT32            decayTimeMin;        // Minimum value of the decay time constant.
    fract32            currentGain;         // Instanteous gain applied at the end of the block.
    fract32            thresholdFract32;    // threshold - in 8.24 "base2 dB"
    fract32            gainFract32;         // outputGain - in 8.24 "base2 dB"
    fract32            slope;               // Internal parameter which holds the slope of the compression curve.
    FLOAT32            sharpnessFactor;     // Unused variable.  Kept in for legacy support
    fract32            attackCoeff;         // Internal derived coefficient based on the attackTime
    fract32            attackCoeffSmoothing; // Internal derived coefficient based on the attackTimeMin
    fract32            decayCoeff;          // Internal derived coefficient based on decayTime
    fract32            decayCoeffSmoothing; // Internal derived coefficient based on decayTimeMin
    fract32            envState;            // State of the envelope detector one-pole filter - runs at tick rate.
    
} awe_modAGCCompressorCoreFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAGCCompressorCoreFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modAGCCompressorCoreFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_AGCCOMPRESSORCOREFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modAGCCompressorCoreFract32Process(void *pInstance);

UINT32 awe_modAGCCompressorCoreFract32Set(void *pInstance, UINT32 mask);
 

void awe_modAGCCompressorCoreFract32Bypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_AGCCOMPRESSORCOREFRACT32_H

/**
 * @}
 *
 * End of file.
 */
