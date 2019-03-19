/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModLogicAny.h
****************************************************************************
*
*     Description:  Check if the input block has any non-zero values
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
 * @brief Check if the input block has any non-zero values
 */

#ifndef _MOD_LOGICANY_H
#define _MOD_LOGICANY_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_LogicAny_result 0x00000100
#define OFFSET_LogicAny_result 0x00000008

#define CLASSID_LOGICANY (CLASS_ID_MODBASE + 36)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modLogicAnyInstance
{
    ModuleInstanceDescriptor instance;
    INT32              result;              // Equals 0 if all input values in the block are 0.  Otherwise equals 1.
    
} awe_modLogicAnyInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modLogicAnyClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modLogicAnyConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_LOGICANY, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modLogicAnyProcess(void *pInstance);

 

void awe_modLogicAnyBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_LOGICANY_H

/**
 * @}
 *
 * End of file.
 */
