/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBlockConcatenate.h
****************************************************************************
*
*     Description:  Concatenates two or more blocks of data
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
 * @brief Concatenates two or more blocks of data
 */

#ifndef _MOD_BLOCKCONCATENATE_H
#define _MOD_BLOCKCONCATENATE_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_BLOCKCONCATENATE (CLASS_ID_MODBASE + 1221)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBlockConcatenateInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modBlockConcatenateInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBlockConcatenateClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modBlockConcatenateConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_BLOCKCONCATENATE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modBlockConcatenateProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BLOCKCONCATENATE_H

/**
 * @}
 *
 * End of file.
 */
