/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDb20Fract32.h
****************************************************************************
*
*     Description:  Converts from linear units to decibels using a polynomial approximation
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
 * @brief Converts from linear units to decibels using a polynomial approximation
 */

#ifndef _MOD_DB20FRACT32_H
#define _MOD_DB20FRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_DB20FRACT32 (CLASS_ID_MODBASE + 141)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDb20Fract32Instance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modDb20Fract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDb20Fract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modDb20Fract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_DB20FRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modDb20Fract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DB20FRACT32_H

/**
 * @}
 *
 * End of file.
 */
