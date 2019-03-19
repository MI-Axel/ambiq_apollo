/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModScalerNV2.h
****************************************************************************
*
*     Description:  General purpose scaler with separate gains per channel
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
 * @brief General purpose scaler with separate gains per channel
 */

#ifndef _MOD_SCALERNV2_H
#define _MOD_SCALERNV2_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ScalerNV2_masterGain 0x00000100
#define MASK_ScalerNV2_smoothingTime 0x00000200
#define MASK_ScalerNV2_isDB 0x00000400
#define MASK_ScalerNV2_smoothingCoeff 0x00000800
#define MASK_ScalerNV2_trimGain 0x00001000
#define MASK_ScalerNV2_targetGain 0x00002000
#define MASK_ScalerNV2_currentGain 0x00004000
#define OFFSET_ScalerNV2_masterGain 0x00000008
#define OFFSET_ScalerNV2_smoothingTime 0x00000009
#define OFFSET_ScalerNV2_isDB 0x0000000A
#define OFFSET_ScalerNV2_smoothingCoeff 0x0000000B
#define OFFSET_ScalerNV2_trimGain 0x0000000C
#define OFFSET_ScalerNV2_targetGain 0x0000000D
#define OFFSET_ScalerNV2_currentGain 0x0000000E

#define CLASSID_SCALERNV2 (CLASS_ID_MODBASE + 20)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modScalerNV2Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            masterGain;          // Overall gain to apply.
    FLOAT32            smoothingTime;       // Time constant of the smoothing process (0 = unsmoothed).
    INT32              isDB;                // Selects between linear (=0) and dB (=1) operation
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    FLOAT32*           trimGain;            // Array of trim gains, one per channel
    FLOAT32*           targetGain;          // Computed target gains in linear units
    FLOAT32*           currentGain;         // Instanteous gains.  These ramp towards targetGain
} awe_modScalerNV2Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modScalerNV2Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modScalerNV2Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modScalerNV2Process(void *pInstance);

UINT32 awe_modScalerNV2Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SCALERNV2_H

/**
 * @}
 *
 * End of file.
 */
