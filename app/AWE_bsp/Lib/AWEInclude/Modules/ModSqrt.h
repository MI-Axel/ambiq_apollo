/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSqrt.h
****************************************************************************
*
*     Description:  Computes the square root
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
 * @brief Computes the square root
 */

#ifndef _MOD_SQRT_H
#define _MOD_SQRT_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_SQRT (CLASS_ID_MODBASE + 63)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSqrtInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modSqrtInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSqrtClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSqrtConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SQRT, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSqrtProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SQRT_H

/**
 * @}
 *
 * End of file.
 */
