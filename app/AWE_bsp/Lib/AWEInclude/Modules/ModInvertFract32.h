/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModInvertFract32.h
****************************************************************************
*
*     Description:  Phase invert module
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
 * @brief Phase invert module
 */

#ifndef _MOD_INVERTFRACT32_H
#define _MOD_INVERTFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_InvertFract32_isInverted 0x00000100
#define MASK_InvertFract32_smoothingTime 0x00000200
#define MASK_InvertFract32_currentGain 0x00000400
#define MASK_InvertFract32_smoothingCoeff 0x00000800
#define MASK_InvertFract32_currentGainFract32 0x00001000
#define MASK_InvertFract32_smoothingCoeffFract32 0x00002000
#define OFFSET_InvertFract32_isInverted 0x00000008
#define OFFSET_InvertFract32_smoothingTime 0x00000009
#define OFFSET_InvertFract32_currentGain 0x0000000A
#define OFFSET_InvertFract32_smoothingCoeff 0x0000000B
#define OFFSET_InvertFract32_currentGainFract32 0x0000000C
#define OFFSET_InvertFract32_smoothingCoeffFract32 0x0000000D

#define CLASSID_INVERTFRACT32 (CLASS_ID_MODBASE + 145)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modInvertFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              isInverted;          // Boolean that specifies whether the signal is inverted (=1) or not (=0)
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    FLOAT32            currentGain;         // Instantaneous gain applied by the module.  This is also the starting gain of the module.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient
    fract32            currentGainFract32;  // Instantaneous gain applied by the module.  This is also the starting gain of the module.
    fract32            smoothingCoeffFract32; // Smoothing coefficient
    
} awe_modInvertFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modInvertFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modInvertFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_INVERTFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modInvertFract32Process(void *pInstance);

UINT32 awe_modInvertFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_INVERTFRACT32_H

/**
 * @}
 *
 * End of file.
 */
