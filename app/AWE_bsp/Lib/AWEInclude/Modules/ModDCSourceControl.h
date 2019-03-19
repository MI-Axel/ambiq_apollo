/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDCSourceControl.h
****************************************************************************
*
*     Description:  Outputs a DC signal at the value of the control signal
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
 * @brief Outputs a DC signal at the value of the control signal
 */

#ifndef _MOD_DCSOURCECONTROL_H
#define _MOD_DCSOURCECONTROL_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DCSourceControl_scaler 0x00000100
#define OFFSET_DCSourceControl_scaler 0x00000008

#define CLASSID_DCSOURCECONTROL (CLASS_ID_MODBASE + 2003)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDCSourceControlInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            scaler;              // The constant which to multipy the input value with
    
} awe_modDCSourceControlInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDCSourceControlClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modDCSourceControlConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_DCSOURCECONTROL, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modDCSourceControlProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DCSOURCECONTROL_H

/**
 * @}
 *
 * End of file.
 */
