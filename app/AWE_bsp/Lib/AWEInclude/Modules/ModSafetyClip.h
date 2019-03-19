/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSafetyClip.h
****************************************************************************
*
*     Description:  Clips the signal in response to an external signal
*
*     Copyright:    DSP Concepts, Inc, 2007 - 2015
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
 * @brief Clips the signal in response to an external signal
 */

#ifndef _MOD_SAFETYCLIP_H
#define _MOD_SAFETYCLIP_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SafetyClip_clipLevel 0x00000100
#define MASK_SafetyClip_clipTime 0x00000200
#define MASK_SafetyClip_manualTrigger 0x00000400
#define MASK_SafetyClip_isClipping 0x00000800
#define MASK_SafetyClip_clipLevelLinear 0x00001000
#define MASK_SafetyClip_timerPeriod 0x00002000
#define MASK_SafetyClip_timerCount 0x00004000
#define OFFSET_SafetyClip_clipLevel 0x00000008
#define OFFSET_SafetyClip_clipTime 0x00000009
#define OFFSET_SafetyClip_manualTrigger 0x0000000A
#define OFFSET_SafetyClip_isClipping 0x0000000B
#define OFFSET_SafetyClip_clipLevelLinear 0x0000000C
#define OFFSET_SafetyClip_timerPeriod 0x0000000D
#define OFFSET_SafetyClip_timerCount 0x0000000E

#define CLASSID_SAFETYCLIP (CLASS_ID_MODBASE + 1220)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSafetyClipInstance
{
    ModuleInstanceDescriptor instance;
    float              clipLevel;           // Level in dB to which the input will be clipped when clipping is active.
    float              clipTime;            // Time constant in msec which controls how long the signal is clipped for.
    int                manualTrigger;       // Boolean parameter to trigger manually.
    int                isClipping;          // Indicates whether the module is currently clipping.
    float              clipLevelLinear;     // Level in dB at which the input will be attenuated when ducking is active.
    int                timerPeriod;         // The period of timer in terms of number of blocks.
    int                timerCount;          // Instantaneous count of the timer.
    
} awe_modSafetyClipInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSafetyClipClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSafetyClipConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SAFETYCLIP, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSafetyClipProcess(void *pInstance);

UINT32 awe_modSafetyClipSet(void *pInstance, UINT32 mask);
 

void awe_modSafetyClipBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_SAFETYCLIP_H

/**
 * @}
 *
 * End of file.
 */
