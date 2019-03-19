/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModComplexMagnitudeSquared.h
****************************************************************************
*
*     Description:  calculates the square of the magnitude of a complex signal.
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
 * @brief calculates the square of the magnitude of a complex signal.
 */

#ifndef _MOD_COMPLEXMAGNITUDESQUARED_H
#define _MOD_COMPLEXMAGNITUDESQUARED_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_COMPLEXMAGNITUDESQUARED (CLASS_ID_MODBASE + 1236)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modComplexMagnitudeSquaredInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modComplexMagnitudeSquaredInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modComplexMagnitudeSquaredClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modComplexMagnitudeSquaredConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_COMPLEXMAGNITUDESQUARED, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modComplexMagnitudeSquaredProcess(void *pInstance);

 

void awe_modComplexMagnitudeSquaredBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_COMPLEXMAGNITUDESQUARED_H

/**
 * @}
 *
 * End of file.
 */
