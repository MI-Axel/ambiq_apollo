/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAbsFract32.h
****************************************************************************
*
*     Description:  Absolute value of fractional input
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
 * @brief Absolute value of fractional input
 */

#ifndef _MOD_ABSFRACT32_H
#define _MOD_ABSFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_ABSFRACT32 (CLASS_ID_MODBASE + 128)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAbsFract32Instance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modAbsFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAbsFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modAbsFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_ABSFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modAbsFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_ABSFRACT32_H

/**
 * @}
 *
 * End of file.
 */
