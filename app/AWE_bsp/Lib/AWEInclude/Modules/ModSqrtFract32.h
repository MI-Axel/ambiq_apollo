/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSqrtFract32.h
****************************************************************************
*
*     Description:  Computes the square root using Math approximations.
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
 * @brief Computes the square root using Math approximations.
 */

#ifndef _MOD_SQRTFRACT32_H
#define _MOD_SQRTFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_SQRTFRACT32 (CLASS_ID_MODBASE + 207)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSqrtFract32Instance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modSqrtFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSqrtFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSqrtFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SQRTFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSqrtFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SQRTFRACT32_H

/**
 * @}
 *
 * End of file.
 */
