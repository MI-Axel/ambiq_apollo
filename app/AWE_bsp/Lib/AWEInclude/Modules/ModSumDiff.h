/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSumDiff.h
****************************************************************************
*
*     Description:  Computes the sum and difference of two signals
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
 * @brief Computes the sum and difference of two signals
 */

#ifndef _MOD_SUMDIFF_H
#define _MOD_SUMDIFF_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_SUMDIFF (CLASS_ID_MODBASE + 68)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSumDiffInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modSumDiffInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSumDiffClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSumDiffConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SUMDIFF, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSumDiffProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SUMDIFF_H

/**
 * @}
 *
 * End of file.
 */
