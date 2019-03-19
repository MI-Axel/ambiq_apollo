/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModLog2.h
****************************************************************************
*
*     Description:  Computes the log base 2 using the math library
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
 * @brief Computes the log base 2 using the math library
 */

#ifndef _MOD_LOG2_H
#define _MOD_LOG2_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_LOG2 (CLASS_ID_MODBASE + 55)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modLog2Instance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modLog2Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modLog2Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modLog2Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_LOG2, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modLog2Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_LOG2_H

/**
 * @}
 *
 * End of file.
 */
