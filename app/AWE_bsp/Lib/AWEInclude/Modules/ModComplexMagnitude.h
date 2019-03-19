/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModComplexMagnitude.h
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

#ifndef _MOD_COMPLEXMAGNITUDE_H
#define _MOD_COMPLEXMAGNITUDE_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_COMPLEXMAGNITUDE (CLASS_ID_MODBASE + 1235)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modComplexMagnitudeInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modComplexMagnitudeInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modComplexMagnitudeClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modComplexMagnitudeConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_COMPLEXMAGNITUDE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modComplexMagnitudeProcess(void *pInstance);

 

void awe_modComplexMagnitudeBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_COMPLEXMAGNITUDE_H

/**
 * @}
 *
 * End of file.
 */
