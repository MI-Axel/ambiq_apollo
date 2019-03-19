/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModModf.h
****************************************************************************
*
*     Description:  Computes the funtion [f,n] = modf(x) using the math library
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
 * @brief Computes the funtion [f,n] = modf(x) using the math library
 */

#ifndef _MOD_MODF_H
#define _MOD_MODF_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_MODF (CLASS_ID_MODBASE + 56)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modModfInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modModfInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modModfClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modModfConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_MODF, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modModfProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MODF_H

/**
 * @}
 *
 * End of file.
 */
