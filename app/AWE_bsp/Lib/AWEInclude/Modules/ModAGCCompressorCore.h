/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAGCCompressorCore.h
****************************************************************************
*
*     Description:  Gain computer used to realize compressors
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
 * @brief Gain computer used to realize compressors
 */

#ifndef _MOD_AGCCOMPRESSORCORE_H
#define _MOD_AGCCOMPRESSORCORE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_AGCCompressorCore_threshold 0x00000100
#define MASK_AGCCompressorCore_gain 0x00000200
#define MASK_AGCCompressorCore_ratio 0x00000400
#define MASK_AGCCompressorCore_attackTime 0x00000800
#define MASK_AGCCompressorCore_attackTimeMin 0x00001000
#define MASK_AGCCompressorCore_decayTime 0x00002000
#define MASK_AGCCompressorCore_decayTimeMin 0x00004000
#define MASK_AGCCompressorCore_currentGain 0x00008000
#define MASK_AGCCompressorCore_slope 0x00010000
#define MASK_AGCCompressorCore_sharpnessFactor 0x00020000
#define MASK_AGCCompressorCore_attackCoeff 0x00040000
#define MASK_AGCCompressorCore_attackCoeffSmoothing 0x00080000
#define MASK_AGCCompressorCore_decayCoeff 0x00100000
#define MASK_AGCCompressorCore_decayCoeffSmoothing 0x00200000
#define MASK_AGCCompressorCore_envState 0x00400000
#define OFFSET_AGCCompressorCore_threshold 0x00000008
#define OFFSET_AGCCompressorCore_gain 0x00000009
#define OFFSET_AGCCompressorCore_ratio 0x0000000A
#define OFFSET_AGCCompressorCore_attackTime 0x0000000B
#define OFFSET_AGCCompressorCore_attackTimeMin 0x0000000C
#define OFFSET_AGCCompressorCore_decayTime 0x0000000D
#define OFFSET_AGCCompressorCore_decayTimeMin 0x0000000E
#define OFFSET_AGCCompressorCore_currentGain 0x0000000F
#define OFFSET_AGCCompressorCore_slope 0x00000010
#define OFFSET_AGCCompressorCore_sharpnessFactor 0x00000011
#define OFFSET_AGCCompressorCore_attackCoeff 0x00000012
#define OFFSET_AGCCompressorCore_attackCoeffSmoothing 0x00000013
#define OFFSET_AGCCompressorCore_decayCoeff 0x00000014
#define OFFSET_AGCCompressorCore_decayCoeffSmoothing 0x00000015
#define OFFSET_AGCCompressorCore_envState 0x00000016

#define CLASSID_AGCCOMPRESSORCORE (CLASS_ID_MODBASE + 1203)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAGCCompressorCoreInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            threshold;           // Amplitude level at which the AGC Limiter Core reduces its output gain value.
    FLOAT32            gain;                // Value used to scale the output of the AGC Limiter Core.
    FLOAT32            ratio;               // Specifies the amount of attenuation (and gain) when above (or below) the threshold.
    FLOAT32            attackTime;          // Envelope detector attack time constant.
    FLOAT32            attackTimeMin;       // Minimum value of the attack time constant.
    FLOAT32            decayTime;           // Envelope detector decay time constant.
    FLOAT32            decayTimeMin;        // Minimum value of the decay time constant.
    FLOAT32            currentGain;         // Instantaneous gain applied at the end of the block.
    FLOAT32            slope;               // Internal parameter which holds the slope of the compression curve.
    FLOAT32            sharpnessFactor;     // Unused variable.  Kept in for legacy support
    FLOAT32            attackCoeff;         // Internal derived coefficient based on the attackTime
    FLOAT32            attackCoeffSmoothing; // Internal derived coefficient based on the attackTimeMin
    FLOAT32            decayCoeff;          // Internal derived coefficient based on decayTime
    FLOAT32            decayCoeffSmoothing; // Internal derived coefficient based on decayTimeMin
    FLOAT32            envState;            // State of the envelope detector one-pole filter - runs at tick rate.
    
} awe_modAGCCompressorCoreInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAGCCompressorCoreClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modAGCCompressorCoreConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_AGCCOMPRESSORCORE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modAGCCompressorCoreProcess(void *pInstance);

UINT32 awe_modAGCCompressorCoreSet(void *pInstance, UINT32 mask);
 

void awe_modAGCCompressorCoreBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_AGCCOMPRESSORCORE_H

/**
 * @}
 *
 * End of file.
 */
