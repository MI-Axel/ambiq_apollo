/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModInterleave.h
****************************************************************************
*
*     Description:  Interleaves multiple audio signals
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
 * @brief Interleaves multiple audio signals
 */

#ifndef _MOD_INTERLEAVE_H
#define _MOD_INTERLEAVE_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_INTERLEAVE (CLASS_ID_MODBASE + 98)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modInterleaveInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modInterleaveInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modInterleaveClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modInterleaveConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_INTERLEAVE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modInterleaveProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_INTERLEAVE_H

/**
 * @}
 *
 * End of file.
 */
