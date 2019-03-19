/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModCfftFract32.h
****************************************************************************
*
*     Description:  Forward and inverse FFT of complex data
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
 * @brief Forward and inverse FFT of complex data
 */

#ifndef _MOD_CFFTFRACT32_H
#define _MOD_CFFTFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_CfftFract32_dir 0x00000100
#define MASK_CfftFract32_onebyBlockSize 0x00000200
#define OFFSET_CfftFract32_dir 0x00000008
#define OFFSET_CfftFract32_onebyBlockSize 0x00000009

#define CLASSID_CFFTFRACT32 (CLASS_ID_MODBASE + 1229)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modCfftFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              dir;                 // Transform direction.  Forward = 1. Inverse = -1
    fract32            onebyBlockSize;      // value of 1/BlockSize in fractional value
    
} awe_modCfftFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modCfftFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modCfftFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_CFFTFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modCfftFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_CFFTFRACT32_H

/**
 * @}
 *
 * End of file.
 */
