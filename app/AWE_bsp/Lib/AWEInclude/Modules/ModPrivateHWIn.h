/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModPrivateHWIn.h
****************************************************************************
*
*     Description:  Special non-SMP multicore subsystem HW input pins. This requires special BSP code.
*
*     Copyright:    DSP Concepts, Inc, 2007 - 2015
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
 * @brief Special non-SMP multicore subsystem HW input pins. This requires special BSP code.
 */

#ifndef _MOD_PRIVATEHWIN_H
#define _MOD_PRIVATEHWIN_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_PRIVATEHWIN (CLASS_ID_MODBASE + 46)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modPrivateHWInInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modPrivateHWInInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modPrivateHWInClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modPrivateHWInConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_PRIVATEHWIN, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modPrivateHWInProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_PRIVATEHWIN_H

/**
 * @}
 *
 * End of file.
 */
