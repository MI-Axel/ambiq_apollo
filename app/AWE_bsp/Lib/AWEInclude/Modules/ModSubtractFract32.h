/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSubtractFract32.h
****************************************************************************
*
*     Description:  Subtracts the last Fract32 input from all other Fract32 inputs
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
 * @brief Subtracts the last Fract32 input from all other Fract32 inputs
 */

#ifndef _MOD_SUBTRACTFRACT32_H
#define _MOD_SUBTRACTFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_SUBTRACTFRACT32 (CLASS_ID_MODBASE + 202)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSubtractFract32Instance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modSubtractFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSubtractFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSubtractFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SUBTRACTFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSubtractFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SUBTRACTFRACT32_H

/**
 * @}
 *
 * End of file.
 */
