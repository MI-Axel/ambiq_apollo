/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAudioWeightingFract32.h
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

#ifndef _MOD_AUDIOWEIGHTINGFRACT32_H
#define _MOD_AUDIOWEIGHTINGFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModBiquadCascadeFract32.h"
#include "ModMuteUnmuteFract32.h"

#define MASK_AudioWeightingFract32_weightingType 0x00000100
#define MASK_AudioWeightingFract32_numStages 0x00000200
#define MASK_AudioWeightingFract32_coeffs 0x00000400
#define OFFSET_AudioWeightingFract32_weightingType 0x00000008
#define OFFSET_AudioWeightingFract32_numStages 0x00000009
#define OFFSET_AudioWeightingFract32_coeffs 0x0000000A

#define CLASSID_AUDIOWEIGHTINGFRACT32 (CLASS_ID_MODBASE + 1213)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAudioWeightingFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              weightingType;       // Selects weighting type
    INT32              numStages;           // Number of stages in the IIR filter
    FLOAT32*           coeffs;              // Array of precomputed filter coefficients for the specified sampling rate
        awe_modBiquadCascadeFract32Instance    *filt;               // Cascade of second order Biquad filters
        awe_modMuteUnmuteFract32Instance    *mute;               // Multichannel smooth mute
} awe_modAudioWeightingFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAudioWeightingFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modAudioWeightingFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modAudioWeightingFract32Process(void *pInstance);

UINT32 awe_modAudioWeightingFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_AUDIOWEIGHTINGFRACT32_H

/**
 * @}
 *
 * End of file.
 */
