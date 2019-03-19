/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMuteSmoothed.h
****************************************************************************
*
*     Description:  Smoothly mutes and unmutes
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
 * @brief Smoothly mutes and unmutes
 */

#ifndef _MOD_MUTESMOOTHED_H
#define _MOD_MUTESMOOTHED_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MuteSmoothed_isMuted 0x00000100
#define MASK_MuteSmoothed_smoothingTime 0x00000200
#define MASK_MuteSmoothed_currentGain 0x00000400
#define MASK_MuteSmoothed_smoothingCoeff 0x00000800
#define MASK_MuteSmoothed_gain 0x00001000
#define OFFSET_MuteSmoothed_isMuted 0x00000008
#define OFFSET_MuteSmoothed_smoothingTime 0x00000009
#define OFFSET_MuteSmoothed_currentGain 0x0000000A
#define OFFSET_MuteSmoothed_smoothingCoeff 0x0000000B
#define OFFSET_MuteSmoothed_gain 0x0000000C

#define CLASSID_MUTESMOOTHED (CLASS_ID_MODBASE + 28)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMuteSmoothedInstance
{
    ModuleInstanceDescriptor instance;
    INT32              isMuted;             // Boolean that controls muting/unmuting.
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    FLOAT32            currentGain;         // Instantaneous gain applied by the module.  This is also the starting gain of the module.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    FLOAT32            gain;                // Target gain.
    
} awe_modMuteSmoothedInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMuteSmoothedClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modMuteSmoothedConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_MUTESMOOTHED, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modMuteSmoothedProcess(void *pInstance);

UINT32 awe_modMuteSmoothedSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MUTESMOOTHED_H

/**
 * @}
 *
 * End of file.
 */
