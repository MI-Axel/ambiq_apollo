/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMixerSmoothedV2b.h
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

#ifndef _MOD_MIXERSMOOTHEDV2B_H
#define _MOD_MIXERSMOOTHEDV2B_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MixerSmoothedV2b_smoothingTime 0x00000100
#define MASK_MixerSmoothedV2b_smoothingCoeff 0x00000200
#define MASK_MixerSmoothedV2b_numIn 0x00000400
#define MASK_MixerSmoothedV2b_gain 0x00000800
#define MASK_MixerSmoothedV2b_currentGain 0x00001000
#define OFFSET_MixerSmoothedV2b_smoothingTime 0x00000008
#define OFFSET_MixerSmoothedV2b_smoothingCoeff 0x00000009
#define OFFSET_MixerSmoothedV2b_numIn 0x0000000A
#define OFFSET_MixerSmoothedV2b_gain 0x0000000B
#define OFFSET_MixerSmoothedV2b_currentGain 0x0000000C

#define CLASSID_MIXERSMOOTHEDV2B (CLASS_ID_MODBASE + 2024)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMixerSmoothedV2bInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process, in msec.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    INT32              numIn;               // Number of input channels.
    FLOAT32*           gain;                // Linear gain.
    FLOAT32*           currentGain;         // Instanteous gain being applied.  This is an internal variable used in the smoothing process
} awe_modMixerSmoothedV2bInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMixerSmoothedV2bClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modMixerSmoothedV2bConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modMixerSmoothedV2bProcess(void *pInstance);

UINT32 awe_modMixerSmoothedV2bSet(void *pInstance, UINT32 mask);
 

void awe_modMixerSmoothedV2bBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_MIXERSMOOTHEDV2B_H

/**
 * @}
 *
 * End of file.
 */
