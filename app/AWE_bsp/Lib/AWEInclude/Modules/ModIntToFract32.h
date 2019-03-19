/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModIntToFract32.h
****************************************************************************
*
*     Description:  Integer to fract32 conversion
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
 * @brief Integer to fract32 conversion
 */

#ifndef _MOD_INTTOFRACT32_H
#define _MOD_INTTOFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_INTTOFRACT32 (CLASS_ID_MODBASE + 2018)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modIntToFract32Instance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modIntToFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modIntToFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modIntToFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_INTTOFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modIntToFract32Process(void *pInstance);

 

void awe_modIntToFract32Bypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_INTTOFRACT32_H

/**
 * @}
 *
 * End of file.
 */
