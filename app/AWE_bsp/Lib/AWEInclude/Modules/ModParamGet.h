/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModParamGet.h
****************************************************************************
*
*     Description:  Gets parameters in other modules
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
 * @brief Gets parameters in other modules
 */

#ifndef _MOD_PARAMGET_H
#define _MOD_PARAMGET_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ParamGet_modPtr 0x00000100
#define MASK_ParamGet_varPtr 0x00000200
#define OFFSET_ParamGet_modPtr 0x00000008
#define OFFSET_ParamGet_varPtr 0x00000009

#define CLASSID_PARAMGET (CLASS_ID_MODBASE + 170)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modParamGetInstance
{
    ModuleInstanceDescriptor instance;
    
    void *             modPtr;              // Points to the module to get
    void *             varPtr;              // Points to the variable to get within the module instance structure
} awe_modParamGetInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modParamGetClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modParamGetConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_PARAMGET, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modParamGetProcess(void *pInstance);

UINT32 awe_modParamGetSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_PARAMGET_H

/**
 * @}
 *
 * End of file.
 */
