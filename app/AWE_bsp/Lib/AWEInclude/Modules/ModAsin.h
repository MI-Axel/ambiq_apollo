/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAsin.h
****************************************************************************
*
*     Description:  Computes the function asin(x) using the math library
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
 * @brief Computes the function asin(x) using the math library
 */

#ifndef _MOD_ASIN_H
#define _MOD_ASIN_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_ASIN (CLASS_ID_MODBASE + 82)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAsinInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modAsinInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAsinClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modAsinConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_ASIN, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modAsinProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_ASIN_H

/**
 * @}
 *
 * End of file.
 */
