/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModFract32ToInt.h
****************************************************************************
*
*     Description:  Fract32 to integer conversion
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
 * @brief Fract32 to integer conversion
 */

#ifndef _MOD_FRACT32TOINT_H
#define _MOD_FRACT32TOINT_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_FRACT32TOINT (CLASS_ID_MODBASE + 2015)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modFract32ToIntInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modFract32ToIntInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modFract32ToIntClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modFract32ToIntConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_FRACT32TOINT, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modFract32ToIntProcess(void *pInstance);

 

void awe_modFract32ToIntBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_FRACT32TOINT_H

/**
 * @}
 *
 * End of file.
 */
