/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSineGenControlFract32.h
****************************************************************************
*
*     Description:  Sine wave generator with frequency taken from a control pin
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
 * @brief Sine wave generator with frequency taken from a control pin
 */

#ifndef _MOD_SINEGENCONTROLFRACT32_H
#define _MOD_SINEGENCONTROLFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SineGenControlFract32_smoothingTime 0x00000100
#define MASK_SineGenControlFract32_startPhase 0x00000200
#define MASK_SineGenControlFract32_currentFreq 0x00000400
#define MASK_SineGenControlFract32_stateReal 0x00000800
#define MASK_SineGenControlFract32_stateImag 0x00001000
#define MASK_SineGenControlFract32_smoothingCoeff 0x00002000
#define OFFSET_SineGenControlFract32_smoothingTime 0x00000008
#define OFFSET_SineGenControlFract32_startPhase 0x00000009
#define OFFSET_SineGenControlFract32_currentFreq 0x0000000A
#define OFFSET_SineGenControlFract32_stateReal 0x0000000B
#define OFFSET_SineGenControlFract32_stateImag 0x0000000C
#define OFFSET_SineGenControlFract32_smoothingCoeff 0x0000000D

#define CLASSID_SINEGENCONTROLFRACT32 (CLASS_ID_MODBASE + 180)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSineGenControlFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process.
    FLOAT32            startPhase;          // Starting phase of the sine wave
    FLOAT32            currentFreq;         // Internal state variable holding the smoothed frequency
    fract32            stateReal;           // Real part of the complex unity magnitude state variable
    fract32            stateImag;           // Imaginary part of the complex unity magnitude state variable
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    
} awe_modSineGenControlFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSineGenControlFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSineGenControlFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SINEGENCONTROLFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSineGenControlFract32Process(void *pInstance);

UINT32 awe_modSineGenControlFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SINEGENCONTROLFRACT32_H

/**
 * @}
 *
 * End of file.
 */
