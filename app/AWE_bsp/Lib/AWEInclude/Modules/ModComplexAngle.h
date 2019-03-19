/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModComplexAngle.h
****************************************************************************
*
*     Description:  Calculates the phase angle of the complex input
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
 * @brief Calculates the phase angle of the complex input
 */

#ifndef _MOD_COMPLEXANGLE_H
#define _MOD_COMPLEXANGLE_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_COMPLEXANGLE (CLASS_ID_MODBASE + 1232)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modComplexAngleInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modComplexAngleInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modComplexAngleClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modComplexAngleConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_COMPLEXANGLE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modComplexAngleProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_COMPLEXANGLE_H

/**
 * @}
 *
 * End of file.
 */
