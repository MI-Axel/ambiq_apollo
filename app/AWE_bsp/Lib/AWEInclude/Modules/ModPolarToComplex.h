/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModPolarToComplex.h
****************************************************************************
*
*     Description:  converts separate angle and magnitude components into a complex signal
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
 * @brief converts separate angle and magnitude components into a complex signal
 */

#ifndef _MOD_POLARTOCOMPLEX_H
#define _MOD_POLARTOCOMPLEX_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_POLARTOCOMPLEX (CLASS_ID_MODBASE + 1303)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modPolarToComplexInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modPolarToComplexInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modPolarToComplexClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modPolarToComplexConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_POLARTOCOMPLEX, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modPolarToComplexProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_POLARTOCOMPLEX_H

/**
 * @}
 *
 * End of file.
 */
