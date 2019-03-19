/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSineGenFract32.h
****************************************************************************
*
*     Description:  Sine wave generator
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
 * @brief Sine wave generator
 */

#ifndef _MOD_SINEGENFRACT32_H
#define _MOD_SINEGENFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SineGenFract32_freq 0x00000100
#define MASK_SineGenFract32_startPhase 0x00000200
#define MASK_SineGenFract32_stateReal 0x00000400
#define MASK_SineGenFract32_stateImag 0x00000800
#define MASK_SineGenFract32_incReal 0x00001000
#define MASK_SineGenFract32_incImag 0x00002000
#define OFFSET_SineGenFract32_freq 0x00000008
#define OFFSET_SineGenFract32_startPhase 0x00000009
#define OFFSET_SineGenFract32_stateReal 0x0000000A
#define OFFSET_SineGenFract32_stateImag 0x0000000B
#define OFFSET_SineGenFract32_incReal 0x0000000C
#define OFFSET_SineGenFract32_incImag 0x0000000D

#define CLASSID_SINEGENFRACT32 (CLASS_ID_MODBASE + 195)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSineGenFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            freq;                // Target frequency of the sine wave
    FLOAT32            startPhase;          // Starting phase of the sine wave
    fract32            stateReal;           // Real part of the complex unity magnitude state variable
    fract32            stateImag;           // Imaginary part of the complex unity magnitude state variable
    fract32            incReal;             // Real part of the complex unity magnitude multiplier
    fract32            incImag;             // Imaginary part of the complex unity magnitude multiplier
    
} awe_modSineGenFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSineGenFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSineGenFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SINEGENFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSineGenFract32Process(void *pInstance);

UINT32 awe_modSineGenFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SINEGENFRACT32_H

/**
 * @}
 *
 * End of file.
 */
