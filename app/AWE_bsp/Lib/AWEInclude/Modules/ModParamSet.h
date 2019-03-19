/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModParamSet.h
****************************************************************************
*
*     Description:  Sets parameters in other modules
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
 * @brief Sets parameters in other modules
 */

#ifndef _MOD_PARAMSET_H
#define _MOD_PARAMSET_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ParamSet_setBehavior 0x00000100
#define MASK_ParamSet_modPtr 0x00000200
#define MASK_ParamSet_varPtr 0x00000400
#define OFFSET_ParamSet_setBehavior 0x00000008
#define OFFSET_ParamSet_modPtr 0x00000009
#define OFFSET_ParamSet_varPtr 0x0000000A

#define CLASSID_PARAMSET (CLASS_ID_MODBASE + 169)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modParamSetInstance
{
    ModuleInstanceDescriptor instance;
    INT32              setBehavior;         // Controls the behavior of the module
    void *             modPtr;              // Points to the module to set
    void *             varPtr;              // Points to the variable to set within the module instance structure
} awe_modParamSetInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modParamSetClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modParamSetConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_PARAMSET, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modParamSetProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_PARAMSET_H

/**
 * @}
 *
 * End of file.
 */
