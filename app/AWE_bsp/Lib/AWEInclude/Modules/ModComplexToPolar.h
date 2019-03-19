/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModComplexToPolar.h
****************************************************************************
*
*     Description:  converts the complex signal into polar..
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
 * @brief converts the complex signal into polar..
 */

#ifndef _MOD_COMPLEXTOPOLAR_H
#define _MOD_COMPLEXTOPOLAR_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_COMPLEXTOPOLAR (CLASS_ID_MODBASE + 1239)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modComplexToPolarInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modComplexToPolarInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modComplexToPolarClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modComplexToPolarConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_COMPLEXTOPOLAR, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modComplexToPolarProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_COMPLEXTOPOLAR_H

/**
 * @}
 *
 * End of file.
 */
