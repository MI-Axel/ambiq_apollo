/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModUndb10Approx.h
****************************************************************************
*
*     Description:  Converts from decibels to linear units
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
 * @brief Converts from decibels to linear units
 */

#ifndef _MOD_UNDB10APPROX_H
#define _MOD_UNDB10APPROX_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_UNDB10APPROX (CLASS_ID_MODBASE + 75)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modUndb10ApproxInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modUndb10ApproxInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modUndb10ApproxClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modUndb10ApproxConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_UNDB10APPROX, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modUndb10ApproxProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_UNDB10APPROX_H

/**
 * @}
 *
 * End of file.
 */
