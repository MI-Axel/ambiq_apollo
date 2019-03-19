/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMixerSmoothed.h
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

#ifndef _MOD_MIXERSMOOTHED_H
#define _MOD_MIXERSMOOTHED_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MixerSmoothed_smoothingTime 0x00000100
#define MASK_MixerSmoothed_smoothingCoeff 0x00000200
#define MASK_MixerSmoothed_gain 0x00000400
#define MASK_MixerSmoothed_currentGain 0x00000800
#define OFFSET_MixerSmoothed_smoothingTime 0x00000008
#define OFFSET_MixerSmoothed_smoothingCoeff 0x00000009
#define OFFSET_MixerSmoothed_gain 0x0000000A
#define OFFSET_MixerSmoothed_currentGain 0x0000000B

#define CLASSID_MIXERSMOOTHED (CLASS_ID_MODBASE + 2023)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMixerSmoothedInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process, in msec.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    FLOAT32*           gain;                // Linear gain.
    FLOAT32*           currentGain;         // Instanteous gain being applied.  This is an internal variable used in the smoothing process
} awe_modMixerSmoothedInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMixerSmoothedClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modMixerSmoothedConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modMixerSmoothedProcess(void *pInstance);

UINT32 awe_modMixerSmoothedSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MIXERSMOOTHED_H

/**
 * @}
 *
 * End of file.
 */
