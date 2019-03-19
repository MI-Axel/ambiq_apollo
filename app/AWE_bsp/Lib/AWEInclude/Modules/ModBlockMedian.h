/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBlockMedian.h
****************************************************************************
*
*     Description:  N-Channel Block median
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
 * @brief N-Channel Block median
 */

#ifndef _MOD_BLOCKMEDIAN_H
#define _MOD_BLOCKMEDIAN_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_BLOCKMEDIAN (CLASS_ID_MODBASE + 1225)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBlockMedianInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modBlockMedianInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBlockMedianClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modBlockMedianConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_BLOCKMEDIAN, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modBlockMedianProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BLOCKMEDIAN_H

/**
 * @}
 *
 * End of file.
 */
