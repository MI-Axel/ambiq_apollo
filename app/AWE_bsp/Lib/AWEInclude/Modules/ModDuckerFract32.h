/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDuckerFract32.h
****************************************************************************
*
*     Description:  Duck or reduce the audio level of the input
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
 * @brief Duck or reduce the audio level of the input
 */

#ifndef _MOD_DUCKERFRACT32_H
#define _MOD_DUCKERFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DuckerFract32_duckLevel 0x00000100
#define MASK_DuckerFract32_attackTime 0x00000200
#define MASK_DuckerFract32_holdTime 0x00000400
#define MASK_DuckerFract32_releaseTime 0x00000800
#define MASK_DuckerFract32_manualTrigger 0x00001000
#define MASK_DuckerFract32_duckLevelLinear 0x00002000
#define MASK_DuckerFract32_attackCoeff 0x00004000
#define MASK_DuckerFract32_releaseCoeff 0x00008000
#define MASK_DuckerFract32_timerPeriod 0x00010000
#define MASK_DuckerFract32_timerCount 0x00020000
#define MASK_DuckerFract32_currentGain 0x00040000
#define MASK_DuckerFract32_targetGain 0x00080000
#define MASK_DuckerFract32_smoothingCoeff 0x00100000
#define OFFSET_DuckerFract32_duckLevel 0x00000008
#define OFFSET_DuckerFract32_attackTime 0x00000009
#define OFFSET_DuckerFract32_holdTime 0x0000000A
#define OFFSET_DuckerFract32_releaseTime 0x0000000B
#define OFFSET_DuckerFract32_manualTrigger 0x0000000C
#define OFFSET_DuckerFract32_duckLevelLinear 0x0000000D
#define OFFSET_DuckerFract32_attackCoeff 0x0000000E
#define OFFSET_DuckerFract32_releaseCoeff 0x0000000F
#define OFFSET_DuckerFract32_timerPeriod 0x00000010
#define OFFSET_DuckerFract32_timerCount 0x00000011
#define OFFSET_DuckerFract32_currentGain 0x00000012
#define OFFSET_DuckerFract32_targetGain 0x00000013
#define OFFSET_DuckerFract32_smoothingCoeff 0x00000014

#define CLASSID_DUCKERFRACT32 (CLASS_ID_MODBASE + 1264)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDuckerFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            duckLevel;           // Level in dB at which the input will be attenuated when ducking is active.
    FLOAT32            attackTime;          // Time constant in msec, which controls the ducking process.
    FLOAT32            holdTime;            // Time constant in msec which controls how long the signal is attenuated for.
    FLOAT32            releaseTime;         // Time constant in msec which controls how fast the gain is restored to 1.0.
    INT32              manualTrigger;       // Boolean parameter to trigger manually.
    fract32            duckLevelLinear;     // Level in dB at which the input will be attenuated when ducking is active.
    fract32            attackCoeff;         // Internal coefficient realizing the attack time.
    fract32            releaseCoeff;        // Internal coefficient realizing the release time.
    INT32              timerPeriod;         // The period of timer in terms of number of blocks.
    INT32              timerCount;          // Instantaneous count of the timer.
    fract32            currentGain;         // Instantaneous gain applied by the module.
    fract32            targetGain;          // Target gain applied by the module.
    fract32            smoothingCoeff;      // Internal coefficient realizing the smoothing time.
    
} awe_modDuckerFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDuckerFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modDuckerFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_DUCKERFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modDuckerFract32Process(void *pInstance);

UINT32 awe_modDuckerFract32Set(void *pInstance, UINT32 mask);
 

void awe_modDuckerFract32Bypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_DUCKERFRACT32_H

/**
 * @}
 *
 * End of file.
 */
