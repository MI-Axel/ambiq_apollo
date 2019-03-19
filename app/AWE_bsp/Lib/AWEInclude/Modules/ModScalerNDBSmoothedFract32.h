/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModScalerNDBSmoothedFract32.h
****************************************************************************
*
*     Description:  Smoothly varying linear Fract32 scaler with independent gains in dB units
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
 * @brief Smoothly varying linear Fract32 scaler with independent gains in dB units
 */

#ifndef _MOD_SCALERNDBSMOOTHEDFRACT32_H
#define _MOD_SCALERNDBSMOOTHEDFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ScalerNDBSmoothedFract32_smoothingTime 0x00000100
#define MASK_ScalerNDBSmoothedFract32_smoothingCoeff 0x00000200
#define MASK_ScalerNDBSmoothedFract32_postShift 0x00000400
#define MASK_ScalerNDBSmoothedFract32_twoPowMinusPostShift 0x00000800
#define MASK_ScalerNDBSmoothedFract32_gainDB 0x00001000
#define MASK_ScalerNDBSmoothedFract32_targetGain 0x00002000
#define MASK_ScalerNDBSmoothedFract32_currentGain 0x00004000
#define OFFSET_ScalerNDBSmoothedFract32_smoothingTime 0x00000008
#define OFFSET_ScalerNDBSmoothedFract32_smoothingCoeff 0x00000009
#define OFFSET_ScalerNDBSmoothedFract32_postShift 0x0000000A
#define OFFSET_ScalerNDBSmoothedFract32_twoPowMinusPostShift 0x0000000B
#define OFFSET_ScalerNDBSmoothedFract32_gainDB 0x0000000C
#define OFFSET_ScalerNDBSmoothedFract32_targetGain 0x0000000D
#define OFFSET_ScalerNDBSmoothedFract32_currentGain 0x0000000E

#define CLASSID_SCALERNDBSMOOTHEDFRACT32 (CLASS_ID_MODBASE + 189)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modScalerNDBSmoothedFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    fract32            smoothingCoeff;      // Smoothing coefficient
    INT32              postShift;           // Number of bits to shift after the fractional multiply.  This is based on gain.range.
    FLOAT32            twoPowMinusPostShift; // 2^(-postShift).  Used by to streamline the operation of the set function
    FLOAT32*           gainDB;              // Array of gains, one per channel
    fract32*           targetGain;          // Array of gains, one per channel
    fract32*           currentGain;         // Array of instantaneous gains, one per channel
} awe_modScalerNDBSmoothedFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modScalerNDBSmoothedFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modScalerNDBSmoothedFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modScalerNDBSmoothedFract32Process(void *pInstance);

UINT32 awe_modScalerNDBSmoothedFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SCALERNDBSMOOTHEDFRACT32_H

/**
 * @}
 *
 * End of file.
 */
