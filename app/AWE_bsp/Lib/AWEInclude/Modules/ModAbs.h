/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAbs.h
****************************************************************************
*
*     Description:  Absolute value
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
 * @brief Absolute value
 */

#ifndef _MOD_ABS_H
#define _MOD_ABS_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_ABS (CLASS_ID_MODBASE + 43)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAbsInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modAbsInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAbsClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modAbsConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_ABS, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modAbsProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_ABS_H

/**
 * @}
 *
 * End of file.
 */
