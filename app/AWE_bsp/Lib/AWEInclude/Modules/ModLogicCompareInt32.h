/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModLogicCompareInt32.h
****************************************************************************
*
*     Description:  General logical comparison module
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
 * @brief General logical comparison module
 */

#ifndef _MOD_LOGICCOMPAREINT32_H
#define _MOD_LOGICCOMPAREINT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define LOGIC_COMPARE_EQUAL 0
#define LOGIC_COMPARE_NOT_EQUAL 1
#define LOGIC_COMPARE_LESS 2
#define LOGIC_COMPARE_LESS_OR_EQUAL 3
#define LOGIC_COMPARE_GREATER 4
#define LOGIC_COMPARE_GREATER_OR_EQUAL 5
#define MASK_LogicCompareInt32_compareType 0x00000100
#define OFFSET_LogicCompareInt32_compareType 0x00000008

#define CLASSID_LOGICCOMPAREINT32 (CLASS_ID_MODBASE + 150)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modLogicCompareInt32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              compareType;         // Selects the type of comparison that is implemented by the module: EQUAL=0, NOTEQUAL=1, LESSTHAN=2, LESSOREQUAL=3, GREATERTHAN=4, GREATEROREQUAL=5
    
} awe_modLogicCompareInt32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modLogicCompareInt32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modLogicCompareInt32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_LOGICCOMPAREINT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modLogicCompareInt32Process(void *pInstance);

 

void awe_modLogicCompareInt32Bypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_LOGICCOMPAREINT32_H

/**
 * @}
 *
 * End of file.
 */
