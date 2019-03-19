/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAGCLimiterCore.h
****************************************************************************
*
*     Description:  Gain computer used to realize soft-knee peak limiters
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
 * @brief Gain computer used to realize soft-knee peak limiters
 */

#ifndef _MOD_AGCLIMITERCORE_H
#define _MOD_AGCLIMITERCORE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_AGCLimiterCore_threshold 0x00000100
#define MASK_AGCLimiterCore_gain 0x00000200
#define MASK_AGCLimiterCore_slope 0x00000400
#define MASK_AGCLimiterCore_kneeDepth 0x00000800
#define MASK_AGCLimiterCore_ratio 0x00001000
#define MASK_AGCLimiterCore_attackTime 0x00002000
#define MASK_AGCLimiterCore_decayTime 0x00004000
#define MASK_AGCLimiterCore_currentGain 0x00008000
#define MASK_AGCLimiterCore_sharpnessFactor 0x00010000
#define MASK_AGCLimiterCore_attackCoeff 0x00020000
#define MASK_AGCLimiterCore_decayCoeff 0x00040000
#define MASK_AGCLimiterCore_envState 0x00080000
#define OFFSET_AGCLimiterCore_threshold 0x00000008
#define OFFSET_AGCLimiterCore_gain 0x00000009
#define OFFSET_AGCLimiterCore_slope 0x0000000A
#define OFFSET_AGCLimiterCore_kneeDepth 0x0000000B
#define OFFSET_AGCLimiterCore_ratio 0x0000000C
#define OFFSET_AGCLimiterCore_attackTime 0x0000000D
#define OFFSET_AGCLimiterCore_decayTime 0x0000000E
#define OFFSET_AGCLimiterCore_currentGain 0x0000000F
#define OFFSET_AGCLimiterCore_sharpnessFactor 0x00000010
#define OFFSET_AGCLimiterCore_attackCoeff 0x00000011
#define OFFSET_AGCLimiterCore_decayCoeff 0x00000012
#define OFFSET_AGCLimiterCore_envState 0x00000013

#define CLASSID_AGCLIMITERCORE (CLASS_ID_MODBASE + 4)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAGCLimiterCoreInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            threshold;           // Amplitude level at which the AGC Limiter Core reduces its output gain value
    FLOAT32            gain;                // Value used to scale the output of the AGC Limiter Core
    FLOAT32            slope;               // Internal derived variable which holds the slope of the compression curve
    FLOAT32            kneeDepth;           // Knee depth controls the sharpness of the transition between no limiting and limiting
    FLOAT32            ratio;               // Slope of the output attenuation when the signal is above threshold - derived from the standard compression ratio parameter by the formula slope = 1.0 - (1.0/ratio)
    FLOAT32            attackTime;          // Envelope detector attack time constant
    FLOAT32            decayTime;           // Envelope detector decay time constant
    FLOAT32            currentGain;         // Instantaneous gain computed by the block
    FLOAT32            sharpnessFactor;     // Internal derived variable which is used to implement the soft knee
    FLOAT32            attackCoeff;         // Internal derived variable which implements the attackTime
    FLOAT32            decayCoeff;          // Internal derived variable which implements the decayTime
    FLOAT32            envState;            // Holds the instantaneous state of the envelope detector
    
} awe_modAGCLimiterCoreInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAGCLimiterCoreClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modAGCLimiterCoreConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_AGCLIMITERCORE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modAGCLimiterCoreProcess(void *pInstance);

UINT32 awe_modAGCLimiterCoreSet(void *pInstance, UINT32 mask);
 

void awe_modAGCLimiterCoreBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_AGCLIMITERCORE_H

/**
 * @}
 *
 * End of file.
 */
