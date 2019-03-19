/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBiquadLoadingFract32.h
****************************************************************************
*
*     Description:  Simulates loading of biquad fract32 filters
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
 * @brief Simulates loading of biquad fract32 filters
 */

#ifndef _MOD_BIQUADLOADINGFRACT32_H
#define _MOD_BIQUADLOADINGFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModBiquadCascadeFract32.h"

#define MASK_BiquadLoadingFract32_maxStages 0x00000100
#define MASK_BiquadLoadingFract32_numStages 0x00000200
#define OFFSET_BiquadLoadingFract32_maxStages 0x00000008
#define OFFSET_BiquadLoadingFract32_numStages 0x00000009

#define CLASSID_BIQUADLOADINGFRACT32 (CLASS_ID_MODBASE + 1218)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBiquadLoadingFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              maxStages;           // Maximum Biquad fract32 stages that can be run
    INT32              numStages;           // Number of Biquad fract32 stages currently running
        awe_modBiquadCascadeFract32Instance    *filt;               // Cascade of second order Biquad filters
} awe_modBiquadLoadingFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBiquadLoadingFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modBiquadLoadingFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modBiquadLoadingFract32Process(void *pInstance);

UINT32 awe_modBiquadLoadingFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BIQUADLOADINGFRACT32_H

/**
 * @}
 *
 * End of file.
 */
