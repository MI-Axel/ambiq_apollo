/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBiquadLoading.h
****************************************************************************
*
*     Description:  Simulates loading of biquad filters
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
 * @brief Simulates loading of biquad filters
 */

#ifndef _MOD_BIQUADLOADING_H
#define _MOD_BIQUADLOADING_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModBiquadCascade.h"

#define MASK_BiquadLoading_maxStages 0x00000100
#define MASK_BiquadLoading_numStages 0x00000200
#define OFFSET_BiquadLoading_maxStages 0x00000008
#define OFFSET_BiquadLoading_numStages 0x00000009

#define CLASSID_BIQUADLOADING (CLASS_ID_MODBASE + 1219)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBiquadLoadingInstance
{
    ModuleInstanceDescriptor instance;
    INT32              maxStages;           // Maximum Biquad stages that can be run
    INT32              numStages;           // Number of Biquad stages currently running
        awe_modBiquadCascadeInstance    *filt;               // Cascade of second order Biquad filters
} awe_modBiquadLoadingInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBiquadLoadingClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modBiquadLoadingConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modBiquadLoadingProcess(void *pInstance);

UINT32 awe_modBiquadLoadingSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BIQUADLOADING_H

/**
 * @}
 *
 * End of file.
 */
