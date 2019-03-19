/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBiquadSmoothed.h
****************************************************************************
*
*     Description:  2nd order smoothly updating IIR filter
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
 * @brief 2nd order smoothly updating IIR filter
 */

#ifndef _MOD_BIQUADSMOOTHED_H
#define _MOD_BIQUADSMOOTHED_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_BiquadSmoothed_updateActive 0x00000100
#define MASK_BiquadSmoothed_smoothingTime 0x00000200
#define MASK_BiquadSmoothed_b0 0x00000400
#define MASK_BiquadSmoothed_b1 0x00000800
#define MASK_BiquadSmoothed_b2 0x00001000
#define MASK_BiquadSmoothed_a1 0x00002000
#define MASK_BiquadSmoothed_a2 0x00004000
#define MASK_BiquadSmoothed_current_b0 0x00008000
#define MASK_BiquadSmoothed_current_b1 0x00010000
#define MASK_BiquadSmoothed_current_b2 0x00020000
#define MASK_BiquadSmoothed_current_a1 0x00040000
#define MASK_BiquadSmoothed_current_a2 0x00080000
#define MASK_BiquadSmoothed_smoothingCoeff 0x00100000
#define MASK_BiquadSmoothed_state 0x00200000
#define OFFSET_BiquadSmoothed_updateActive 0x00000008
#define OFFSET_BiquadSmoothed_smoothingTime 0x00000009
#define OFFSET_BiquadSmoothed_b0 0x0000000A
#define OFFSET_BiquadSmoothed_b1 0x0000000B
#define OFFSET_BiquadSmoothed_b2 0x0000000C
#define OFFSET_BiquadSmoothed_a1 0x0000000D
#define OFFSET_BiquadSmoothed_a2 0x0000000E
#define OFFSET_BiquadSmoothed_current_b0 0x0000000F
#define OFFSET_BiquadSmoothed_current_b1 0x00000010
#define OFFSET_BiquadSmoothed_current_b2 0x00000011
#define OFFSET_BiquadSmoothed_current_a1 0x00000012
#define OFFSET_BiquadSmoothed_current_a2 0x00000013
#define OFFSET_BiquadSmoothed_smoothingCoeff 0x00000014
#define OFFSET_BiquadSmoothed_state 0x00000015

#define CLASSID_BIQUADSMOOTHED (CLASS_ID_MODBASE + 13)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBiquadSmoothedInstance
{
    ModuleInstanceDescriptor instance;
    INT32              updateActive;        // Specifies whether the filter coefficients are updating (=1) or fixed (=0).
    FLOAT32            smoothingTime;       // Time constant of the smoothing process.
    FLOAT32            b0;                  // Desired first numerator coefficient.
    FLOAT32            b1;                  // Desired second numerator coefficient.
    FLOAT32            b2;                  // Desired third numerator coefficient.
    FLOAT32            a1;                  // Desired second denominator coefficient.
    FLOAT32            a2;                  // Desired third denominator coefficient.
    FLOAT32            current_b0;          // Instantaneous first numerator coefficient.
    FLOAT32            current_b1;          // Instantaneous second numerator coefficient.
    FLOAT32            current_b2;          // Instantaneous third numerator coefficient.
    FLOAT32            current_a1;          // Instantaneous second denominator coefficient.
    FLOAT32            current_a2;          // Instantaneous third denominator coefficient.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient. This is computed based on the smoothingTime, sample rate, and block size of the module.
    FLOAT32*           state;               // State variables. 2 per channel.
} awe_modBiquadSmoothedInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBiquadSmoothedClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modBiquadSmoothedConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modBiquadSmoothedProcess(void *pInstance);

UINT32 awe_modBiquadSmoothedSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BIQUADSMOOTHED_H

/**
 * @}
 *
 * End of file.
 */
