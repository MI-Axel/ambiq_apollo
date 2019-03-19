/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModPeriodicFunctionGen.h
****************************************************************************
*
*     Description:  General purpose periodic function generator
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
 * @brief General purpose periodic function generator
 */

#ifndef _MOD_PERIODICFUNCTIONGEN_H
#define _MOD_PERIODICFUNCTIONGEN_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_PeriodicFunctionGen_functionType 0x00000100
#define MASK_PeriodicFunctionGen_freq 0x00000200
#define MASK_PeriodicFunctionGen_amplitude 0x00000400
#define MASK_PeriodicFunctionGen_offset 0x00000800
#define MASK_PeriodicFunctionGen_offsetRad 0x00001000
#define MASK_PeriodicFunctionGen_phase 0x00002000
#define MASK_PeriodicFunctionGen_phaseInc 0x00004000
#define MASK_PeriodicFunctionGen_impPeriod 0x00008000
#define MASK_PeriodicFunctionGen_impSampleIndex 0x00010000
#define MASK_PeriodicFunctionGen_triPhase 0x00020000
#define MASK_PeriodicFunctionGen_triPhaseInc 0x00040000
#define MASK_PeriodicFunctionGen_sawPhase 0x00080000
#define MASK_PeriodicFunctionGen_sawPhaseIncrement 0x00100000
#define OFFSET_PeriodicFunctionGen_functionType 0x00000008
#define OFFSET_PeriodicFunctionGen_freq 0x00000009
#define OFFSET_PeriodicFunctionGen_amplitude 0x0000000A
#define OFFSET_PeriodicFunctionGen_offset 0x0000000B
#define OFFSET_PeriodicFunctionGen_offsetRad 0x0000000C
#define OFFSET_PeriodicFunctionGen_phase 0x0000000D
#define OFFSET_PeriodicFunctionGen_phaseInc 0x0000000E
#define OFFSET_PeriodicFunctionGen_impPeriod 0x0000000F
#define OFFSET_PeriodicFunctionGen_impSampleIndex 0x00000010
#define OFFSET_PeriodicFunctionGen_triPhase 0x00000011
#define OFFSET_PeriodicFunctionGen_triPhaseInc 0x00000012
#define OFFSET_PeriodicFunctionGen_sawPhase 0x00000013
#define OFFSET_PeriodicFunctionGen_sawPhaseIncrement 0x00000014

#define CLASSID_PERIODICFUNCTIONGEN (CLASS_ID_MODBASE + 118)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modPeriodicFunctionGenInstance
{
    ModuleInstanceDescriptor instance;
    INT32              functionType;        // Type of the wave form to be generated on output
    FLOAT32            freq;                // Frequency of the function generator output wave.
    FLOAT32            amplitude;           // Amplitude in linear units.
    FLOAT32            offset;              // Starting phase of the function generator output wave.
    FLOAT32            offsetRad;           // Offset in radiuns.
    FLOAT32            phase;               // Instantanteous phase and also starting phase.
    FLOAT32            phaseInc;            // Instantaneous sample to sample phase increment.
    INT32              impPeriod;           // Period or rate of the impulse generator.
    INT32              impSampleIndex;      // Specifies the index of the next non-zero value.
    FLOAT32            triPhase;            // Instantanteous phase and also starting phase.
    FLOAT32            triPhaseInc;         // Instantaneous sample to sample phase increment.
    FLOAT32            sawPhase;            // The stored phase of the sawtooth function.
    FLOAT32            sawPhaseIncrement;   // The amount that the oscillator phase is incremented for each output sample.
    
} awe_modPeriodicFunctionGenInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modPeriodicFunctionGenClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modPeriodicFunctionGenConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_PERIODICFUNCTIONGEN, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modPeriodicFunctionGenProcess(void *pInstance);

UINT32 awe_modPeriodicFunctionGenSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_PERIODICFUNCTIONGEN_H

/**
 * @}
 *
 * End of file.
 */
