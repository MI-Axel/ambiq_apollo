/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDb10.h
****************************************************************************
*
*     Description:  Converts from energy to decibels
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
 * @brief Converts from energy to decibels
 */

#ifndef _MOD_DB10_H
#define _MOD_DB10_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_DB10 (CLASS_ID_MODBASE + 70)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDb10Instance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modDb10Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDb10Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modDb10Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_DB10, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modDb10Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DB10_H

/**
 * @}
 *
 * End of file.
 */
