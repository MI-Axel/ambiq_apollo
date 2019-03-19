/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMuteNSmoothed.h
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

#ifndef _MOD_MUTENSMOOTHED_H
#define _MOD_MUTENSMOOTHED_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MuteNSmoothed_smoothingTime 0x00000100
#define MASK_MuteNSmoothed_smoothingCoeff 0x00000200
#define MASK_MuteNSmoothed_isMuted 0x00000400
#define MASK_MuteNSmoothed_currentGain 0x00000800
#define MASK_MuteNSmoothed_gain 0x00001000
#define OFFSET_MuteNSmoothed_smoothingTime 0x00000008
#define OFFSET_MuteNSmoothed_smoothingCoeff 0x00000009
#define OFFSET_MuteNSmoothed_isMuted 0x0000000A
#define OFFSET_MuteNSmoothed_currentGain 0x0000000B
#define OFFSET_MuteNSmoothed_gain 0x0000000C

#define CLASSID_MUTENSMOOTHED (CLASS_ID_MODBASE + 27)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMuteNSmoothedInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    INT32*             isMuted;             // Boolean that controls muting/unmuting.  One per channel.
    FLOAT32*           currentGain;         // Instantaneous gain applied by the module.  This is also the starting gain of the module.
    FLOAT32*           gain;                // Target gain.
} awe_modMuteNSmoothedInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMuteNSmoothedClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modMuteNSmoothedConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modMuteNSmoothedProcess(void *pInstance);

UINT32 awe_modMuteNSmoothedSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MUTENSMOOTHED_H

/**
 * @}
 *
 * End of file.
 */
