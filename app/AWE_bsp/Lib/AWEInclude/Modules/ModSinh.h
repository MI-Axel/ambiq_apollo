/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSinh.h
****************************************************************************
*
*     Description:  Computes the function sinh(x) using the math library
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
 * @brief Computes the function sinh(x) using the math library
 */

#ifndef _MOD_SINH_H
#define _MOD_SINH_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_SINH (CLASS_ID_MODBASE + 88)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSinhInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modSinhInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSinhClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSinhConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SINH, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSinhProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SINH_H

/**
 * @}
 *
 * End of file.
 */
