/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModReciprocal.h
****************************************************************************
*
*     Description:  Computes the reciprocal (1/x) on a sample-by-sample basis
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
 * @brief Computes the reciprocal (1/x) on a sample-by-sample basis
 */

#ifndef _MOD_RECIPROCAL_H
#define _MOD_RECIPROCAL_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_RECIPROCAL (CLASS_ID_MODBASE + 60)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modReciprocalInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modReciprocalInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modReciprocalClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modReciprocalConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_RECIPROCAL, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modReciprocalProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_RECIPROCAL_H

/**
 * @}
 *
 * End of file.
 */
