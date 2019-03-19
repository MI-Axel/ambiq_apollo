/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSineSmoothedGenFract32.h
****************************************************************************
*
*     Description:  Smoothly varying sine wave generator
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
 * @brief Smoothly varying sine wave generator
 */

#ifndef _MOD_SINESMOOTHEDGENFRACT32_H
#define _MOD_SINESMOOTHEDGENFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SineSmoothedGenFract32_freq 0x00000100
#define MASK_SineSmoothedGenFract32_smoothingTime 0x00000200
#define MASK_SineSmoothedGenFract32_startPhase 0x00000400
#define MASK_SineSmoothedGenFract32_smoothingCoeff 0x00000800
#define MASK_SineSmoothedGenFract32_phase 0x00001000
#define MASK_SineSmoothedGenFract32_phaseIncTarget 0x00002000
#define MASK_SineSmoothedGenFract32_phaseInc 0x00004000
#define OFFSET_SineSmoothedGenFract32_freq 0x00000008
#define OFFSET_SineSmoothedGenFract32_smoothingTime 0x00000009
#define OFFSET_SineSmoothedGenFract32_startPhase 0x0000000A
#define OFFSET_SineSmoothedGenFract32_smoothingCoeff 0x0000000B
#define OFFSET_SineSmoothedGenFract32_phase 0x0000000C
#define OFFSET_SineSmoothedGenFract32_phaseIncTarget 0x0000000D
#define OFFSET_SineSmoothedGenFract32_phaseInc 0x0000000E

#define CLASSID_SINESMOOTHEDGENFRACT32 (CLASS_ID_MODBASE + 196)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSineSmoothedGenFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            freq;                // Target frequency of the sine wave
    FLOAT32            smoothingTime;       // Time constant of the frequency adjustment operation
    FLOAT32            startPhase;          // Starting phase of the sine wave
    fract32            smoothingCoeff;      // Smoothing coefficient
    fract32            phase;               // Instantanteous phase and also starting phase
    fract32            phaseIncTarget;      // Target for the sample to sample phase increment.  Essentially the target frequency
    fract32            phaseInc;            // Instantaneous sample to sample phase increment
    
} awe_modSineSmoothedGenFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSineSmoothedGenFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSineSmoothedGenFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SINESMOOTHEDGENFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSineSmoothedGenFract32Process(void *pInstance);

UINT32 awe_modSineSmoothedGenFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SINESMOOTHEDGENFRACT32_H

/**
 * @}
 *
 * End of file.
 */
