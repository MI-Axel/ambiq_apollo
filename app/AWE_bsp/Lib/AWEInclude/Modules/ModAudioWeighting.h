/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAudioWeighting.h
****************************************************************************
*
*     Description:  Standard audio weighting filters
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
 * @brief Standard audio weighting filters
 */

#ifndef _MOD_AUDIOWEIGHTING_H
#define _MOD_AUDIOWEIGHTING_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModBiquadCascade.h"
#include "ModMuteUnmute.h"

#define MASK_AudioWeighting_weightingType 0x00000100
#define MASK_AudioWeighting_numStages 0x00000200
#define MASK_AudioWeighting_coeffs 0x00000400
#define OFFSET_AudioWeighting_weightingType 0x00000008
#define OFFSET_AudioWeighting_numStages 0x00000009
#define OFFSET_AudioWeighting_coeffs 0x0000000A

#define CLASSID_AUDIOWEIGHTING (CLASS_ID_MODBASE + 1214)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAudioWeightingInstance
{
    ModuleInstanceDescriptor instance;
    INT32              weightingType;       // Selects weighting type
    INT32              numStages;           // Number of stages in the IIR filter
    FLOAT32*           coeffs;              // Array of precomputed filter coefficients for the specified sampling rate
        awe_modBiquadCascadeInstance    *filt;               // Cascade of second order Biquad filters
        awe_modMuteUnmuteInstance    *mute;               // Mutes and unmutes to hide artifacts
} awe_modAudioWeightingInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAudioWeightingClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modAudioWeightingConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modAudioWeightingProcess(void *pInstance);

UINT32 awe_modAudioWeightingSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_AUDIOWEIGHTING_H

/**
 * @}
 *
 * End of file.
 */
