/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModNullSink.h
****************************************************************************
*
*     Description:  Sink module which performs no computation and discards the input
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
 * @brief Sink module which performs no computation and discards the input
 */

#ifndef _MOD_NULLSINK_H
#define _MOD_NULLSINK_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_NULLSINK (CLASS_ID_MODBASE + 108)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modNullSinkInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modNullSinkInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modNullSinkClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modNullSinkConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_NULLSINK, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modNullSinkProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_NULLSINK_H

/**
 * @}
 *
 * End of file.
 */
