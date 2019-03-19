/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModTanh.h
****************************************************************************
*
*     Description:  Computes the function tanh(x) using the math library
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
 * @brief Computes the function tanh(x) using the math library
 */

#ifndef _MOD_TANH_H
#define _MOD_TANH_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_TANH (CLASS_ID_MODBASE + 90)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modTanhInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modTanhInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modTanhClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modTanhConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_TANH, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modTanhProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_TANH_H

/**
 * @}
 *
 * End of file.
 */
