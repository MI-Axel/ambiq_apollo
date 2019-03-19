/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModShiftFract32.h
****************************************************************************
*
*     Description:  Arithmetic shift of integer or fractional data
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
 * @brief Arithmetic shift of integer or fractional data
 */

#ifndef _MOD_SHIFTFRACT32_H
#define _MOD_SHIFTFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ShiftFract32_numBits 0x00000100
#define OFFSET_ShiftFract32_numBits 0x00000008

#define CLASSID_SHIFTFRACT32 (CLASS_ID_MODBASE + 194)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modShiftFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              numBits;             // Integer value that specifies the number of bits to shift the input.
    
} awe_modShiftFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modShiftFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modShiftFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SHIFTFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modShiftFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SHIFTFRACT32_H

/**
 * @}
 *
 * End of file.
 */
