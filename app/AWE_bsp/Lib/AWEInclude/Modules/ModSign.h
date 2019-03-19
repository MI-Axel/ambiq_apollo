/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSign.h
****************************************************************************
*
*     Description:  Computes the sign (-1, 0, or +1) of a floating-point value
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
 * @brief Computes the sign (-1, 0, or +1) of a floating-point value
 */

#ifndef _MOD_SIGN_H
#define _MOD_SIGN_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_SIGN (CLASS_ID_MODBASE + 62)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSignInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modSignInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSignClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSignConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SIGN, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSignProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SIGN_H

/**
 * @}
 *
 * End of file.
 */
