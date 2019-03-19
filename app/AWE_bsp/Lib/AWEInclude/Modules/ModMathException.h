/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMathException.h
****************************************************************************
*
*     Description:  Eliminates NaN and Inf from data
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
 * @brief Eliminates NaN and Inf from data
 */

#ifndef _MOD_MATHEXCEPTION_H
#define _MOD_MATHEXCEPTION_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MathException_nanCount 0x00000100
#define MASK_MathException_infCount 0x00000200
#define MASK_MathException_replacementValue 0x00000400
#define OFFSET_MathException_nanCount 0x00000008
#define OFFSET_MathException_infCount 0x00000009
#define OFFSET_MathException_replacementValue 0x0000000A

#define CLASSID_MATHEXCEPTION (CLASS_ID_MODBASE + 1295)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMathExceptionInstance
{
    ModuleInstanceDescriptor instance;
    INT32              nanCount;            // Number of NaNs encountered
    INT32              infCount;            // Number of Infs encountered
    FLOAT32            replacementValue;    // NaN and Inf values are replaced with this number.
    
} awe_modMathExceptionInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMathExceptionClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modMathExceptionConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_MATHEXCEPTION, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modMathExceptionProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MATHEXCEPTION_H

/**
 * @}
 *
 * End of file.
 */
