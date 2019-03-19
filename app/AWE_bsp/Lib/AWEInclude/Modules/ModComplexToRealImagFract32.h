/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModComplexToRealImagFract32.h
****************************************************************************
*
*     Description:  Converts a complex signal into separate real and imaginary components
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
 * @brief Converts a complex signal into separate real and imaginary components
 */

#ifndef _MOD_COMPLEXTOREALIMAGFRACT32_H
#define _MOD_COMPLEXTOREALIMAGFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_COMPLEXTOREALIMAGFRACT32 (CLASS_ID_MODBASE + 1240)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modComplexToRealImagFract32Instance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modComplexToRealImagFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modComplexToRealImagFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modComplexToRealImagFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_COMPLEXTOREALIMAGFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modComplexToRealImagFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_COMPLEXTOREALIMAGFRACT32_H

/**
 * @}
 *
 * End of file.
 */
