/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSineSmoothedGen.h
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

#ifndef _MOD_SINESMOOTHEDGEN_H
#define _MOD_SINESMOOTHEDGEN_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SineSmoothedGen_freq 0x00000100
#define MASK_SineSmoothedGen_smoothingTime 0x00000200
#define MASK_SineSmoothedGen_startPhase 0x00000400
#define MASK_SineSmoothedGen_smoothingCoeff 0x00000800
#define MASK_SineSmoothedGen_phase 0x00001000
#define MASK_SineSmoothedGen_phaseIncTarget 0x00002000
#define MASK_SineSmoothedGen_phaseInc 0x00004000
#define OFFSET_SineSmoothedGen_freq 0x00000008
#define OFFSET_SineSmoothedGen_smoothingTime 0x00000009
#define OFFSET_SineSmoothedGen_startPhase 0x0000000A
#define OFFSET_SineSmoothedGen_smoothingCoeff 0x0000000B
#define OFFSET_SineSmoothedGen_phase 0x0000000C
#define OFFSET_SineSmoothedGen_phaseIncTarget 0x0000000D
#define OFFSET_SineSmoothedGen_phaseInc 0x0000000E

#define CLASSID_SINESMOOTHEDGEN (CLASS_ID_MODBASE + 121)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSineSmoothedGenInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            freq;                // Frequency of the sine wave, in Hz.
    FLOAT32            smoothingTime;       // Time constant of the frequency adjustment operation, in msec.
    FLOAT32            startPhase;          // Starting phase of the sine wave, in degrees.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    FLOAT32            phase;               // Instantanteous phase and also starting phase.
    FLOAT32            phaseIncTarget;      // Target for the sample to sample phase increment. Essentially the target frequency.
    FLOAT32            phaseInc;            // Instantaneous sample to sample phase increment.
    
} awe_modSineSmoothedGenInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSineSmoothedGenClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSineSmoothedGenConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SINESMOOTHEDGEN, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSineSmoothedGenProcess(void *pInstance);

UINT32 awe_modSineSmoothedGenSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SINESMOOTHEDGEN_H

/**
 * @}
 *
 * End of file.
 */
