/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModScalerNSmoothed.h
****************************************************************************
*
*     Description:  Smoothly varying linear scaler with independent gains
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
 * @brief Smoothly varying linear scaler with independent gains
 */

#ifndef _MOD_SCALERNSMOOTHED_H
#define _MOD_SCALERNSMOOTHED_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ScalerNSmoothed_smoothingTime 0x00000100
#define MASK_ScalerNSmoothed_smoothingCoeff 0x00000200
#define MASK_ScalerNSmoothed_gain 0x00000400
#define MASK_ScalerNSmoothed_currentGain 0x00000800
#define OFFSET_ScalerNSmoothed_smoothingTime 0x00000008
#define OFFSET_ScalerNSmoothed_smoothingCoeff 0x00000009
#define OFFSET_ScalerNSmoothed_gain 0x0000000A
#define OFFSET_ScalerNSmoothed_currentGain 0x0000000B

#define CLASSID_SCALERNSMOOTHED (CLASS_ID_MODBASE + 2042)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modScalerNSmoothedInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    FLOAT32*           gain;                // Array of gains, one per channel.
    FLOAT32*           currentGain;         // Array of instantaneous gains, one per channel.
} awe_modScalerNSmoothedInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modScalerNSmoothedClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modScalerNSmoothedConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modScalerNSmoothedProcess(void *pInstance);

UINT32 awe_modScalerNSmoothedSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SCALERNSMOOTHED_H

/**
 * @}
 *
 * End of file.
 */
