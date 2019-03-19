/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBooleanInvert.h
****************************************************************************
*
*     Description:  Complements (inverts) Boolean data
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
 * @brief Complements (inverts) Boolean data
 */

#ifndef _MOD_BOOLEANINVERT_H
#define _MOD_BOOLEANINVERT_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_BOOLEANINVERT (CLASS_ID_MODBASE + 32)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBooleanInvertInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modBooleanInvertInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBooleanInvertClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modBooleanInvertConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_BOOLEANINVERT, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modBooleanInvertProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BOOLEANINVERT_H

/**
 * @}
 *
 * End of file.
 */
