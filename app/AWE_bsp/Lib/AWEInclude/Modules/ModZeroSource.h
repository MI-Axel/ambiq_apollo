/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModZeroSource.h
****************************************************************************
*
*     Description:  Outputs a constant value of zero
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
 * @brief Outputs a constant value of zero
 */

#ifndef _MOD_ZEROSOURCE_H
#define _MOD_ZEROSOURCE_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_ZEROSOURCE (CLASS_ID_MODBASE + 116)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modZeroSourceInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modZeroSourceInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modZeroSourceClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modZeroSourceConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_ZEROSOURCE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modZeroSourceProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_ZEROSOURCE_H

/**
 * @}
 *
 * End of file.
 */
