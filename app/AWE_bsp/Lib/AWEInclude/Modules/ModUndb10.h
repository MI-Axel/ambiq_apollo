/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModUndb10.h
****************************************************************************
*
*     Description:  Converts from decibels to energy
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
 * @brief Converts from decibels to energy
 */

#ifndef _MOD_UNDB10_H
#define _MOD_UNDB10_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_UNDB10 (CLASS_ID_MODBASE + 74)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modUndb10Instance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modUndb10Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modUndb10Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modUndb10Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_UNDB10, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modUndb10Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_UNDB10_H

/**
 * @}
 *
 * End of file.
 */
