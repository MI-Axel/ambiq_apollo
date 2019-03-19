/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModLogicCompareConst.h
****************************************************************************
*
*     Description:  Compares the value at the input pin against a stored value
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
 * @brief Compares the value at the input pin against a stored value
 */

#ifndef _MOD_LOGICCOMPARECONST_H
#define _MOD_LOGICCOMPARECONST_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_LogicCompareConst_compareType 0x00000100
#define MASK_LogicCompareConst_constValue 0x00000200
#define OFFSET_LogicCompareConst_compareType 0x00000008
#define OFFSET_LogicCompareConst_constValue 0x00000009

#define CLASSID_LOGICCOMPARECONST (CLASS_ID_MODBASE + 39)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modLogicCompareConstInstance
{
    ModuleInstanceDescriptor instance;
    INT32              compareType;         // Selects the type of comparison that is implemented by the module: Equal=0 NotEqual=1 lessThan=2 LessOrEqual=3 greaterThan=4 GreaterOrEqual=5
    FLOAT32            constValue;          // Selects value against to compare against.  In linear units.
    
} awe_modLogicCompareConstInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modLogicCompareConstClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modLogicCompareConstConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_LOGICCOMPARECONST, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modLogicCompareConstProcess(void *pInstance);

 

void awe_modLogicCompareConstBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_LOGICCOMPARECONST_H

/**
 * @}
 *
 * End of file.
 */
