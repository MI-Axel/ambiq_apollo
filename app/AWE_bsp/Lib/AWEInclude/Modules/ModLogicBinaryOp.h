/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModLogicBinaryOp.h
****************************************************************************
*
*     Description:  Performs logical operations on binary signals
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
 * @brief Performs logical operations on binary signals
 */

#ifndef _MOD_LOGICBINARYOP_H
#define _MOD_LOGICBINARYOP_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_LogicBinaryOp_opType 0x00000100
#define MASK_LogicBinaryOp_oneChannelOutput 0x00000200
#define OFFSET_LogicBinaryOp_opType 0x00000008
#define OFFSET_LogicBinaryOp_oneChannelOutput 0x00000009

#define CLASSID_LOGICBINARYOP (CLASS_ID_MODBASE + 37)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modLogicBinaryOpInstance
{
    ModuleInstanceDescriptor instance;
    INT32              opType;              // AND=0, OR=1, XOR=2.  Selects the type of binary operations that is performed.
    INT32              oneChannelOutput;    // Boolean value that determines whether all channels are operated on to form a single output.
    
} awe_modLogicBinaryOpInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modLogicBinaryOpClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modLogicBinaryOpConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_LOGICBINARYOP, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modLogicBinaryOpProcess(void *pInstance);

 

void awe_modLogicBinaryOpBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_LOGICBINARYOP_H

/**
 * @}
 *
 * End of file.
 */
