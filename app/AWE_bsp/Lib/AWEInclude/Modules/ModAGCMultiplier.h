/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAGCMultiplier.h
****************************************************************************
*
*     Description:  Mono x N-channel multiplier
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
 * @brief Mono x N-channel multiplier
 */

#ifndef _MOD_AGCMULTIPLIER_H
#define _MOD_AGCMULTIPLIER_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_AGCMULTIPLIER (CLASS_ID_MODBASE + 2000)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAGCMultiplierInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modAGCMultiplierInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAGCMultiplierClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modAGCMultiplierConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_AGCMULTIPLIER, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modAGCMultiplierProcess(void *pInstance);

 

void awe_modAGCMultiplierBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_AGCMULTIPLIER_H

/**
 * @}
 *
 * End of file.
 */
