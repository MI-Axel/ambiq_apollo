/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModFloatToInt.h
****************************************************************************
*
*     Description:  Floating-point to integer conversion
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
 * @brief Floating-point to integer conversion
 */

#ifndef _MOD_FLOATTOINT_H
#define _MOD_FLOATTOINT_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_FLOATTOINT (CLASS_ID_MODBASE + 2013)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modFloatToIntInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modFloatToIntInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modFloatToIntClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modFloatToIntConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_FLOATTOINT, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modFloatToIntProcess(void *pInstance);

 

void awe_modFloatToIntBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_FLOATTOINT_H

/**
 * @}
 *
 * End of file.
 */
