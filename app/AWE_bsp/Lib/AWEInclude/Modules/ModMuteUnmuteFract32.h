/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMuteUnmuteFract32.h
****************************************************************************
*
*     Description:  Multichannel smooth mute
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
 * @brief Multichannel smooth mute
 */

#ifndef _MOD_MUTEUNMUTEFRACT32_H
#define _MOD_MUTEUNMUTEFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MuteUnmuteFract32_trigger 0x00000100
#define MASK_MuteUnmuteFract32_muteTime 0x00000200
#define MASK_MuteUnmuteFract32_silenceTime 0x00000400
#define MASK_MuteUnmuteFract32_unmuteTime 0x00000800
#define MASK_MuteUnmuteFract32_muteTimeSamples 0x00001000
#define MASK_MuteUnmuteFract32_silenceTimeSamples 0x00002000
#define MASK_MuteUnmuteFract32_unmuteTimeSamples 0x00004000
#define MASK_MuteUnmuteFract32_muteCoeffR 0x00008000
#define MASK_MuteUnmuteFract32_muteCoeffI 0x00010000
#define MASK_MuteUnmuteFract32_unmuteCoeffR 0x00020000
#define MASK_MuteUnmuteFract32_unmuteCoeffI 0x00040000
#define MASK_MuteUnmuteFract32_stateR 0x00080000
#define MASK_MuteUnmuteFract32_stateI 0x00100000
#define MASK_MuteUnmuteFract32_sampleTime 0x00200000
#define OFFSET_MuteUnmuteFract32_trigger 0x00000008
#define OFFSET_MuteUnmuteFract32_muteTime 0x00000009
#define OFFSET_MuteUnmuteFract32_silenceTime 0x0000000A
#define OFFSET_MuteUnmuteFract32_unmuteTime 0x0000000B
#define OFFSET_MuteUnmuteFract32_muteTimeSamples 0x0000000C
#define OFFSET_MuteUnmuteFract32_silenceTimeSamples 0x0000000D
#define OFFSET_MuteUnmuteFract32_unmuteTimeSamples 0x0000000E
#define OFFSET_MuteUnmuteFract32_muteCoeffR 0x0000000F
#define OFFSET_MuteUnmuteFract32_muteCoeffI 0x00000010
#define OFFSET_MuteUnmuteFract32_unmuteCoeffR 0x00000011
#define OFFSET_MuteUnmuteFract32_unmuteCoeffI 0x00000012
#define OFFSET_MuteUnmuteFract32_stateR 0x00000013
#define OFFSET_MuteUnmuteFract32_stateI 0x00000014
#define OFFSET_MuteUnmuteFract32_sampleTime 0x00000015

#define CLASSID_MUTEUNMUTEFRACT32 (CLASS_ID_MODBASE + 155)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMuteUnmuteFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              trigger;             // Begins the muting and unmuting process
    FLOAT32            muteTime;            // Muting time, in msec
    FLOAT32            silenceTime;         // Duration of the silence period, in msec
    FLOAT32            unmuteTime;          // Unmuting time, in msec
    INT32              muteTimeSamples;     // Muting time, in samples
    INT32              silenceTimeSamples;  // Silence time, in samples
    INT32              unmuteTimeSamples;   // Unmuting time, in samples
    fract32            muteCoeffR;          // One of two coefficients used to compute the muting profile
    fract32            muteCoeffI;          // One of two coefficients used to compute the muting profile
    fract32            unmuteCoeffR;        // One of two coefficients used to compute the unmuting profile
    fract32            unmuteCoeffI;        // One of two coefficients used to compute the unmuting profile
    fract32            stateR;              // One of two state variables which control the ramping profile
    fract32            stateI;              // One of two state variables which control the ramping profile
    INT32              sampleTime;          // Counts the samples elapsed in the entire mute/silence/unmute cycle
    
} awe_modMuteUnmuteFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMuteUnmuteFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modMuteUnmuteFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_MUTEUNMUTEFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modMuteUnmuteFract32Process(void *pInstance);

UINT32 awe_modMuteUnmuteFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MUTEUNMUTEFRACT32_H

/**
 * @}
 *
 * End of file.
 */
