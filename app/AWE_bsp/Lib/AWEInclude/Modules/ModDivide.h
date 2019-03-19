/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDivide.h
****************************************************************************
*
*     Description:  Divides two signals on a sample-by-sample basis
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
 * @brief Divides two signals on a sample-by-sample basis
 */

#ifndef _MOD_DIVIDE_H
#define _MOD_DIVIDE_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_DIVIDE (CLASS_ID_MODBASE + 47)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDivideInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modDivideInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDivideClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modDivideConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_DIVIDE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modDivideProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DIVIDE_H

/**
 * @}
 *
 * End of file.
 */
