/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModRemainder.h
****************************************************************************
*
*     Description:  Remainder of a signal by constant or by other signal on a sample-by-sample basis
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
 * @brief Remainder of a signal by constant or by other signal on a sample-by-sample basis
 */

#ifndef _MOD_REMAINDER_H
#define _MOD_REMAINDER_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Remainder_denominator 0x00000100
#define OFFSET_Remainder_denominator 0x00000008

#define CLASSID_REMAINDER (CLASS_ID_MODBASE + 176)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modRemainderInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            denominator;         // Denominator value. Enabled if DENOMFROMPIN is zero.
    
} awe_modRemainderInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modRemainderClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modRemainderConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_REMAINDER, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modRemainderProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_REMAINDER_H

/**
 * @}
 *
 * End of file.
 */
