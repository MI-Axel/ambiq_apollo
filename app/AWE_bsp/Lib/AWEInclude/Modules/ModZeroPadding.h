/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModZeroPadding.h
****************************************************************************
*
*     Description:  Zero padding
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
 * @brief Zero padding
 */

#ifndef _MOD_ZEROPADDING_H
#define _MOD_ZEROPADDING_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_ZEROPADDING (CLASS_ID_MODBASE + 1361)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modZeroPaddingInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modZeroPaddingInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modZeroPaddingClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modZeroPaddingConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_ZEROPADDING, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modZeroPaddingProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_ZEROPADDING_H

/**
 * @}
 *
 * End of file.
 */
