/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSineGen.h
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

#ifndef _MOD_SINEGEN_H
#define _MOD_SINEGEN_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SineGen_freq 0x00000100
#define MASK_SineGen_startPhase 0x00000200
#define MASK_SineGen_stateReal 0x00000400
#define MASK_SineGen_stateImag 0x00000800
#define MASK_SineGen_incReal 0x00001000
#define MASK_SineGen_incImag 0x00002000
#define OFFSET_SineGen_freq 0x00000008
#define OFFSET_SineGen_startPhase 0x00000009
#define OFFSET_SineGen_stateReal 0x0000000A
#define OFFSET_SineGen_stateImag 0x0000000B
#define OFFSET_SineGen_incReal 0x0000000C
#define OFFSET_SineGen_incImag 0x0000000D

#define CLASSID_SINEGEN (CLASS_ID_MODBASE + 2043)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSineGenInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            freq;                // Frequency of the sine wave.
    FLOAT32            startPhase;          // Starting phase of the sine wave.
    FLOAT32            stateReal;           // Real part of the complex unity magnitude state variable
    FLOAT32            stateImag;           // Imaginary part of the complex unity magnitude state variable.
    FLOAT32            incReal;             // Real part of the complex unity magnitude multiplier.
    FLOAT32            incImag;             // Imaginary part of the complex unity magnitude multiplier.
    
} awe_modSineGenInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSineGenClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSineGenConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SINEGEN, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSineGenProcess(void *pInstance);

UINT32 awe_modSineGenSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SINEGEN_H

/**
 * @}
 *
 * End of file.
 */
