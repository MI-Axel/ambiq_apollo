/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDownsampler.h
****************************************************************************
*
*     Description:  Downsampler (or decimator) - keeps 1 out of every D samples
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
 * @brief Downsampler (or decimator) - keeps 1 out of every D samples
 */

#ifndef _MOD_DOWNSAMPLER_H
#define _MOD_DOWNSAMPLER_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Downsampler_D 0x00000100
#define OFFSET_Downsampler_D 0x00000008

#define CLASSID_DOWNSAMPLER (CLASS_ID_MODBASE + 1261)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDownsamplerInstance
{
    ModuleInstanceDescriptor instance;
    INT32              D;                   // Decimation factor. 1 out of every D samples is output.
    
} awe_modDownsamplerInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDownsamplerClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modDownsamplerConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_DOWNSAMPLER, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modDownsamplerProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DOWNSAMPLER_H

/**
 * @}
 *
 * End of file.
 */
