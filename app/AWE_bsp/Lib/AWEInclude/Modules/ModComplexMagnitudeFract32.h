/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModComplexMagnitudeFract32.h
****************************************************************************
*
*     Description:  calculates the magnitude of a complex signal
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
 * @brief calculates the magnitude of a complex signal
 */

#ifndef _MOD_COMPLEXMAGNITUDEFRACT32_H
#define _MOD_COMPLEXMAGNITUDEFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_COMPLEXMAGNITUDEFRACT32 (CLASS_ID_MODBASE + 1234)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modComplexMagnitudeFract32Instance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modComplexMagnitudeFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modComplexMagnitudeFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modComplexMagnitudeFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_COMPLEXMAGNITUDEFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modComplexMagnitudeFract32Process(void *pInstance);

 

void awe_modComplexMagnitudeFract32Bypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_COMPLEXMAGNITUDEFRACT32_H

/**
 * @}
 *
 * End of file.
 */
