/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModLogicCompareConstFract32.h
****************************************************************************
*
*     Description:  Compares fract32 values against a constant parameter value
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
 * @brief Compares fract32 values against a constant parameter value
 */

#ifndef _MOD_LOGICCOMPARECONSTFRACT32_H
#define _MOD_LOGICCOMPARECONSTFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define LOGIC_COMPARE_EQUAL 0
#define LOGIC_COMPARE_NOT_EQUAL 1
#define LOGIC_COMPARE_LESS 2
#define LOGIC_COMPARE_LESS_OR_EQUAL 3
#define LOGIC_COMPARE_GREATER 4
#define LOGIC_COMPARE_GREATER_OR_EQUAL 5
#define MASK_LogicCompareConstFract32_compareType 0x00000100
#define MASK_LogicCompareConstFract32_const_value 0x00000200
#define OFFSET_LogicCompareConstFract32_compareType 0x00000008
#define OFFSET_LogicCompareConstFract32_const_value 0x00000009

#define CLASSID_LOGICCOMPARECONSTFRACT32 (CLASS_ID_MODBASE + 148)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modLogicCompareConstFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              compareType;         // Selects the type of compare that is implemented by the module: Equal=0 NotEqual=1 lessThan=2 LessOrEqual=3 greaterThan=4 GreaterOrEqual=5
    fract32            const_value;         // Selects value against to perform compare operations
    
} awe_modLogicCompareConstFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modLogicCompareConstFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modLogicCompareConstFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_LOGICCOMPARECONSTFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modLogicCompareConstFract32Process(void *pInstance);

 

void awe_modLogicCompareConstFract32Bypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_LOGICCOMPARECONSTFRACT32_H

/**
 * @}
 *
 * End of file.
 */
