/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModExp.h
****************************************************************************
*
*     Description:  Computes the function exp(x) using the math library
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
 * @brief Computes the function exp(x) using the math library
 */

#ifndef _MOD_EXP_H
#define _MOD_EXP_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_EXP (CLASS_ID_MODBASE + 48)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modExpInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modExpInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modExpClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modExpConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_EXP, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modExpProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_EXP_H

/**
 * @}
 *
 * End of file.
 */
