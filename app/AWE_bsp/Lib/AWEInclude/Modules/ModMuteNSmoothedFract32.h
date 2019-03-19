/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMuteNSmoothedFract32.h
****************************************************************************
*
*     Description:  Multichannel mute module
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
 * @brief Multichannel mute module
 */

#ifndef _MOD_MUTENSMOOTHEDFRACT32_H
#define _MOD_MUTENSMOOTHEDFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MuteNSmoothedFract32_smoothingTime 0x00000100
#define MASK_MuteNSmoothedFract32_smoothingCoeff 0x00000200
#define MASK_MuteNSmoothedFract32_isMuted 0x00000400
#define MASK_MuteNSmoothedFract32_currentGain 0x00000800
#define MASK_MuteNSmoothedFract32_gain 0x00001000
#define OFFSET_MuteNSmoothedFract32_smoothingTime 0x00000008
#define OFFSET_MuteNSmoothedFract32_smoothingCoeff 0x00000009
#define OFFSET_MuteNSmoothedFract32_isMuted 0x0000000A
#define OFFSET_MuteNSmoothedFract32_currentGain 0x0000000B
#define OFFSET_MuteNSmoothedFract32_gain 0x0000000C

#define CLASSID_MUTENSMOOTHEDFRACT32 (CLASS_ID_MODBASE + 163)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMuteNSmoothedFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    fract32            smoothingCoeff;      // Smoothing coefficient.
    INT32*             isMuted;             // Boolean that controls muting/unmuting.  One per channel.
    fract32*           currentGain;         // Instantaneous gain applied by the module.  This is also the starting gain of the module.
    fract32*           gain;                // Target gain.
} awe_modMuteNSmoothedFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMuteNSmoothedFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modMuteNSmoothedFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modMuteNSmoothedFract32Process(void *pInstance);

UINT32 awe_modMuteNSmoothedFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MUTENSMOOTHEDFRACT32_H

/**
 * @}
 *
 * End of file.
 */
