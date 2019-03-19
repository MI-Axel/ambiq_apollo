/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDb10Approx.h
****************************************************************************
*
*     Description:  Converts from energy to decibels using a fast approximation
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
 * @brief Converts from energy to decibels using a fast approximation
 */

#ifndef _MOD_DB10APPROX_H
#define _MOD_DB10APPROX_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_DB10APPROX (CLASS_ID_MODBASE + 71)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDb10ApproxInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modDb10ApproxInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDb10ApproxClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modDb10ApproxConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_DB10APPROX, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modDb10ApproxProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DB10APPROX_H

/**
 * @}
 *
 * End of file.
 */
