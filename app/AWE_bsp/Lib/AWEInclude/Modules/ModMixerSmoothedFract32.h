/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMixerSmoothedFract32.h
****************************************************************************
*
*     Description:  M-input x N-output smoothly varying mixer
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
 * @brief M-input x N-output smoothly varying mixer
 */

#ifndef _MOD_MIXERSMOOTHEDFRACT32_H
#define _MOD_MIXERSMOOTHEDFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MixerSmoothedFract32_smoothingTime 0x00000100
#define MASK_MixerSmoothedFract32_smoothingCoeff 0x00000200
#define MASK_MixerSmoothedFract32_postShift 0x00000400
#define MASK_MixerSmoothedFract32_gain 0x00000800
#define MASK_MixerSmoothedFract32_targetGain 0x00001000
#define MASK_MixerSmoothedFract32_currentGain 0x00002000
#define OFFSET_MixerSmoothedFract32_smoothingTime 0x00000008
#define OFFSET_MixerSmoothedFract32_smoothingCoeff 0x00000009
#define OFFSET_MixerSmoothedFract32_postShift 0x0000000A
#define OFFSET_MixerSmoothedFract32_gain 0x0000000B
#define OFFSET_MixerSmoothedFract32_targetGain 0x0000000C
#define OFFSET_MixerSmoothedFract32_currentGain 0x0000000D

#define CLASSID_MIXERSMOOTHEDFRACT32 (CLASS_ID_MODBASE + 159)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMixerSmoothedFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    fract32            smoothingCoeff;      // Smoothing coefficient
    INT32              postShift;           // Number of bits to shift
    FLOAT32*           gain;                // Linear gain
    fract32*           targetGain;          // Linear gain
    fract32*           currentGain;         // Linear gain
} awe_modMixerSmoothedFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMixerSmoothedFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modMixerSmoothedFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modMixerSmoothedFract32Process(void *pInstance);

UINT32 awe_modMixerSmoothedFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MIXERSMOOTHEDFRACT32_H

/**
 * @}
 *
 * End of file.
 */
