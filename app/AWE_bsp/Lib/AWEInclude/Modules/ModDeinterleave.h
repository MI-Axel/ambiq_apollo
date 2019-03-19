/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDeinterleave.h
****************************************************************************
*
*     Description:  Deinterleaves a multichannel audio signal into separate mono signals
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
 * @brief Deinterleaves a multichannel audio signal into separate mono signals
 */

#ifndef _MOD_DEINTERLEAVE_H
#define _MOD_DEINTERLEAVE_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_DEINTERLEAVE (CLASS_ID_MODBASE + 97)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDeinterleaveInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modDeinterleaveInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDeinterleaveClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modDeinterleaveConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_DEINTERLEAVE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modDeinterleaveProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DEINTERLEAVE_H

/**
 * @}
 *
 * End of file.
 */
