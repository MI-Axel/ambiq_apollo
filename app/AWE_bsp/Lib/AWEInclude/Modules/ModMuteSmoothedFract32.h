/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMuteSmoothedFract32.h
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

#ifndef _MOD_MUTESMOOTHEDFRACT32_H
#define _MOD_MUTESMOOTHEDFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MuteSmoothedFract32_isMuted 0x00000100
#define MASK_MuteSmoothedFract32_smoothingTime 0x00000200
#define MASK_MuteSmoothedFract32_currentGain 0x00000400
#define MASK_MuteSmoothedFract32_smoothingCoeffFract32 0x00000800
#define MASK_MuteSmoothedFract32_target_gainFract32 0x00001000
#define OFFSET_MuteSmoothedFract32_isMuted 0x00000008
#define OFFSET_MuteSmoothedFract32_smoothingTime 0x00000009
#define OFFSET_MuteSmoothedFract32_currentGain 0x0000000A
#define OFFSET_MuteSmoothedFract32_smoothingCoeffFract32 0x0000000B
#define OFFSET_MuteSmoothedFract32_target_gainFract32 0x0000000C

#define CLASSID_MUTESMOOTHEDFRACT32 (CLASS_ID_MODBASE + 161)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMuteSmoothedFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              isMuted;             // Target gain factor decider
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    fract32            currentGain;         // Instantaneous gain applied by the module.  This is also the starting gain of the module.
    fract32            smoothingCoeffFract32; // Smoothing coefficient
    fract32            target_gainFract32;  // Target gain
    
} awe_modMuteSmoothedFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMuteSmoothedFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modMuteSmoothedFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_MUTESMOOTHEDFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modMuteSmoothedFract32Process(void *pInstance);

UINT32 awe_modMuteSmoothedFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MUTESMOOTHEDFRACT32_H

/**
 * @}
 *
 * End of file.
 */
