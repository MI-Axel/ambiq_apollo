/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModConvolve.h
****************************************************************************
*
*     Description:  Vector convolution
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
 * @brief Vector convolution
 */

#ifndef _MOD_CONVOLVE_H
#define _MOD_CONVOLVE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Convolve_shape 0x00000100
#define MASK_Convolve_skip 0x00000200
#define MASK_Convolve_olen 0x00000400
#define OFFSET_Convolve_shape 0x00000008
#define OFFSET_Convolve_skip 0x00000009
#define OFFSET_Convolve_olen 0x0000000A

#define CLASSID_CONVOLVE (CLASS_ID_MODBASE + 1243)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modConvolveInstance
{
    ModuleInstanceDescriptor instance;
    INT32              shape;               // Shape of subsection
    INT32              skip;                // Number of samples of full convolution to skip at output
    INT32              olen;                // Length of output
    
} awe_modConvolveInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modConvolveClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modConvolveConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_CONVOLVE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modConvolveProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_CONVOLVE_H

/**
 * @}
 *
 * End of file.
 */
