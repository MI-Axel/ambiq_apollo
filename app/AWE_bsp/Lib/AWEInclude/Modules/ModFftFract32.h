/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModFftFract32.h
****************************************************************************
*
*     Description:  Forward FFT of fractional data
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
 * @brief Forward FFT of fractional data
 */

#ifndef _MOD_FFTFRACT32_H
#define _MOD_FFTFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_FFTFRACT32 (CLASS_ID_MODBASE + 1268)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modFftFract32Instance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modFftFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modFftFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modFftFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_FFTFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modFftFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_FFTFRACT32_H

/**
 * @}
 *
 * End of file.
 */
