/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModLogicAll.h
****************************************************************************
*
*     Description:  Check if the input block has all non-zero values
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
 * @brief Check if the input block has all non-zero values
 */

#ifndef _MOD_LOGICALL_H
#define _MOD_LOGICALL_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_LogicAll_result 0x00000100
#define OFFSET_LogicAll_result 0x00000008

#define CLASSID_LOGICALL (CLASS_ID_MODBASE + 35)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modLogicAllInstance
{
    ModuleInstanceDescriptor instance;
    INT32              result;              // Equals 1 if all input values in the block are non-zero.  Otherwise equals 0.
    
} awe_modLogicAllInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modLogicAllClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modLogicAllConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_LOGICALL, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modLogicAllProcess(void *pInstance);

 

void awe_modLogicAllBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_LOGICALL_H

/**
 * @}
 *
 * End of file.
 */
