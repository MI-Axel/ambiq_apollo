/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSquareFract32.h
****************************************************************************
*
*     Description:  Computes the square using the math library.
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
 * @brief Computes the square using the math library.
 */

#ifndef _MOD_SQUAREFRACT32_H
#define _MOD_SQUAREFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_SQUAREFRACT32 (CLASS_ID_MODBASE + 201)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSquareFract32Instance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modSquareFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSquareFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSquareFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SQUAREFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSquareFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SQUAREFRACT32_H

/**
 * @}
 *
 * End of file.
 */
