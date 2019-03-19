/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDownwardExpanderCoreFract32.h
****************************************************************************
*
*     Description:  Gain computer used to realize a downward expander (or noise gate)
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
 * @brief Gain computer used to realize a downward expander (or noise gate)
 */

#ifndef _MOD_DOWNWARDEXPANDERCOREFRACT32_H
#define _MOD_DOWNWARDEXPANDERCOREFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DownwardExpanderCoreFract32_threshold 0x00000100
#define MASK_DownwardExpanderCoreFract32_ratio 0x00000200
#define MASK_DownwardExpanderCoreFract32_kneeDepth 0x00000400
#define MASK_DownwardExpanderCoreFract32_attackTime 0x00000800
#define MASK_DownwardExpanderCoreFract32_decayTime 0x00001000
#define MASK_DownwardExpanderCoreFract32_currentGain 0x00002000
#define MASK_DownwardExpanderCoreFract32_thresholdFract32 0x00004000
#define MASK_DownwardExpanderCoreFract32_ratioMinusOneNegate 0x00008000
#define MASK_DownwardExpanderCoreFract32_kneeDepthFract32 0x00010000
#define MASK_DownwardExpanderCoreFract32_oneOverKneeDepthFract32 0x00020000
#define MASK_DownwardExpanderCoreFract32_attackCoeff 0x00040000
#define MASK_DownwardExpanderCoreFract32_decayCoeff 0x00080000
#define MASK_DownwardExpanderCoreFract32_envState 0x00100000
#define MASK_DownwardExpanderCoreFract32_kneePoly 0x00200000
#define OFFSET_DownwardExpanderCoreFract32_threshold 0x00000008
#define OFFSET_DownwardExpanderCoreFract32_ratio 0x00000009
#define OFFSET_DownwardExpanderCoreFract32_kneeDepth 0x0000000A
#define OFFSET_DownwardExpanderCoreFract32_attackTime 0x0000000B
#define OFFSET_DownwardExpanderCoreFract32_decayTime 0x0000000C
#define OFFSET_DownwardExpanderCoreFract32_currentGain 0x0000000D
#define OFFSET_DownwardExpanderCoreFract32_thresholdFract32 0x0000000E
#define OFFSET_DownwardExpanderCoreFract32_ratioMinusOneNegate 0x0000000F
#define OFFSET_DownwardExpanderCoreFract32_kneeDepthFract32 0x00000010
#define OFFSET_DownwardExpanderCoreFract32_oneOverKneeDepthFract32 0x00000011
#define OFFSET_DownwardExpanderCoreFract32_attackCoeff 0x00000012
#define OFFSET_DownwardExpanderCoreFract32_decayCoeff 0x00000013
#define OFFSET_DownwardExpanderCoreFract32_envState 0x00000014
#define OFFSET_DownwardExpanderCoreFract32_kneePoly 0x00000015

#define CLASSID_DOWNWARDEXPANDERCOREFRACT32 (CLASS_ID_MODBASE + 1262)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDownwardExpanderCoreFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            threshold;           // Below this level the module reduces gain
    FLOAT32            ratio;               // Slope of the gain curve when the signal is below the threshold
    FLOAT32            kneeDepth;           // Knee depth controls the sharpness of the transition between expanding and not expanding
    FLOAT32            attackTime;          // Envelope detector attack time constant
    FLOAT32            decayTime;           // Envelope detector decay time constant
    fract32            currentGain;         // Instantaneous gain computed by the block
    fract32            thresholdFract32;    // threshold - in 8.24 "base2 dB"
    fract32            ratioMinusOneNegate; // -(ratio - 1) - in 8.24 "base2 dB"
    fract32            kneeDepthFract32;    // kneeDepth - in 8.24 "base2 dB"
    fract32            oneOverKneeDepthFract32; // 1/kneeDepth - in 1.31 "base2 dB"
    fract32            attackCoeff;         // Internal derived variable which implements the attackTime
    fract32            decayCoeff;          // Internal derived variable which implements the decayTime
    fract32            envState;            // Holds the instantaneous state of the envelope detector
    fract32*           kneePoly;            // Derived variable for interpolating the soft knee
} awe_modDownwardExpanderCoreFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDownwardExpanderCoreFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modDownwardExpanderCoreFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modDownwardExpanderCoreFract32Process(void *pInstance);

UINT32 awe_modDownwardExpanderCoreFract32Set(void *pInstance, UINT32 mask);
 

void awe_modDownwardExpanderCoreFract32Bypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_DOWNWARDEXPANDERCOREFRACT32_H

/**
 * @}
 *
 * End of file.
 */
