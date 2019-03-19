/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModPrivateHWOut.h
****************************************************************************
*
*     Description:  Special non-SMP multicore subsystem HW output pins. This requires special BSP code.
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
 * @brief Special non-SMP multicore subsystem HW output pins. This requires special BSP code.
 */

#ifndef _MOD_PRIVATEHWOUT_H
#define _MOD_PRIVATEHWOUT_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_PRIVATEHWOUT (CLASS_ID_MODBASE + 47)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modPrivateHWOutInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modPrivateHWOutInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modPrivateHWOutClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modPrivateHWOutConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_PRIVATEHWOUT, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modPrivateHWOutProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_PRIVATEHWOUT_H

/**
 * @}
 *
 * End of file.
 */
