/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModIfftFract32.h
****************************************************************************
*
*     Description:  Inverse FFT of real data on fixed point
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
 * @brief Inverse FFT of real data on fixed point
 */

#ifndef _MOD_IFFTFRACT32_H
#define _MOD_IFFTFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_IfftFract32_onebyBlockSize 0x00000100
#define OFFSET_IfftFract32_onebyBlockSize 0x00000008

#define CLASSID_IFFTFRACT32 (CLASS_ID_MODBASE + 1288)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modIfftFract32Instance
{
    ModuleInstanceDescriptor instance;
    fract32            onebyBlockSize;      // value of 1/BlockSize in fractional value
    
} awe_modIfftFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modIfftFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modIfftFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_IFFTFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modIfftFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_IFFTFRACT32_H

/**
 * @}
 *
 * End of file.
 */
