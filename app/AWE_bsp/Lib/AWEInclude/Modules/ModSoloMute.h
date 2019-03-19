/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSoloMute.h
****************************************************************************
*
*     Description:  Solo and mute control module
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
 * @brief Solo and mute control module
 */

#ifndef _MOD_SOLOMUTE_H
#define _MOD_SOLOMUTE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SoloMute_numControls 0x00000100
#define MASK_SoloMute_smoothingTime 0x00000200
#define MASK_SoloMute_smoothingCoeff 0x00000400
#define MASK_SoloMute_isSolo 0x00000800
#define MASK_SoloMute_isMuted 0x00001000
#define MASK_SoloMute_currentGain 0x00002000
#define MASK_SoloMute_gain 0x00004000
#define OFFSET_SoloMute_numControls 0x00000008
#define OFFSET_SoloMute_smoothingTime 0x00000009
#define OFFSET_SoloMute_smoothingCoeff 0x0000000A
#define OFFSET_SoloMute_isSolo 0x0000000B
#define OFFSET_SoloMute_isMuted 0x0000000C
#define OFFSET_SoloMute_currentGain 0x0000000D
#define OFFSET_SoloMute_gain 0x0000000E

#define CLASSID_SOLOMUTE (CLASS_ID_MODBASE + 30)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSoloMuteInstance
{
    ModuleInstanceDescriptor instance;
    INT32              numControls;         // Number of individual mute controls
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    INT32*             isSolo;              // Boolean that controls pin solo.  One per each pin.
    INT32*             isMuted;             // Boolean that controls pin muted or unmuted.  One per each pin.
    FLOAT32*           currentGain;         // Instantaneous gain applied by the module.  This is also the starting gain of the module.
    FLOAT32*           gain;                // Target gain.
} awe_modSoloMuteInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSoloMuteClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modSoloMuteConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modSoloMuteProcess(void *pInstance);

UINT32 awe_modSoloMuteSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SOLOMUTE_H

/**
 * @}
 *
 * End of file.
 */
