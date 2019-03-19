/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMuteSync.h
****************************************************************************
*
*     Description:  Smooth mute with synchronous requests
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
 * @brief Smooth mute with synchronous requests
 */

#ifndef _MOD_MUTESYNC_H
#define _MOD_MUTESYNC_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MuteSync_isMuted 0x00000100
#define MASK_MuteSync_asyncCommand 0x00000200
#define MASK_MuteSync_syncCommand 0x00000400
#define MASK_MuteSync_muteTime 0x00000800
#define MASK_MuteSync_unmuteTime 0x00001000
#define MASK_MuteSync_compatSync 0x00002000
#define MASK_MuteSync_muteState 0x00004000
#define MASK_MuteSync_currentGain 0x00008000
#define MASK_MuteSync_muteRotateI 0x00010000
#define MASK_MuteSync_syncState 0x00020000
#define MASK_MuteSync_muteSamples 0x00040000
#define MASK_MuteSync_unmuteSamples 0x00080000
#define MASK_MuteSync_muteRotateR 0x00100000
#define MASK_MuteSync_unmuteRotateR 0x00200000
#define MASK_MuteSync_unmuteRotateI 0x00400000
#define MASK_MuteSync_phasorR 0x00800000
#define MASK_MuteSync_phasorI 0x01000000
#define MASK_MuteSync_sampleTime 0x02000000
#define OFFSET_MuteSync_isMuted 0x00000008
#define OFFSET_MuteSync_asyncCommand 0x00000009
#define OFFSET_MuteSync_syncCommand 0x0000000A
#define OFFSET_MuteSync_muteTime 0x0000000B
#define OFFSET_MuteSync_unmuteTime 0x0000000C
#define OFFSET_MuteSync_compatSync 0x0000000D
#define OFFSET_MuteSync_muteState 0x0000000E
#define OFFSET_MuteSync_currentGain 0x0000000F
#define OFFSET_MuteSync_muteRotateI 0x00000010
#define OFFSET_MuteSync_syncState 0x00000011
#define OFFSET_MuteSync_muteSamples 0x00000012
#define OFFSET_MuteSync_unmuteSamples 0x00000013
#define OFFSET_MuteSync_muteRotateR 0x00000014
#define OFFSET_MuteSync_unmuteRotateR 0x00000015
#define OFFSET_MuteSync_unmuteRotateI 0x00000016
#define OFFSET_MuteSync_phasorR 0x00000017
#define OFFSET_MuteSync_phasorI 0x00000018
#define OFFSET_MuteSync_sampleTime 0x00000019

#define CLASSID_MUTESYNC (CLASS_ID_MODBASE + 1299)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMuteSyncInstance
{
    ModuleInstanceDescriptor instance;
    INT32              isMuted;             // Boolean for target gain: 1 means silence
    INT32              asyncCommand;        // Start changing the gain without waiting for completion: 1=unmute, 2=mute
    INT32              syncCommand;         // Change the gain and return only when finished: 1=unmute, 2=mute
    FLOAT32            muteTime;            // Muting time in msec
    FLOAT32            unmuteTime;          // Unmuting time in msec
    INT32              compatSync;          // When true, isMuted compatibility is synchronous
    INT32              muteState;           // Current muting action: 0=not set, 1=unmuted, 2=muted, 3=unmute changing, 4=mute changing
    FLOAT32            currentGain;         // Gain being applied to start of next sample block
    FLOAT32            muteRotateI;         // Imaginary part of multiplier to rotate phasor while muting
    INT32              syncState;           // Active synchronous target state
    INT32              muteSamples;         // Muting time in samples
    INT32              unmuteSamples;       // Unmuting time in samples
    FLOAT32            muteRotateR;         // Real part of multiplier to rotate phasor while muting
    FLOAT32            unmuteRotateR;       // Real part of multiplier to rotate phasor while unmuting
    FLOAT32            unmuteRotateI;       // Imaginary  part of multiplier to rotate phasor while unmuting
    FLOAT32            phasorR;             // Real part of complex  phasor used to compute cosine
    FLOAT32            phasorI;             // Imaginary part of complex phasor used to compute cosine
    INT32              sampleTime;          // Counts samples  since the start of the active mute or unmute operation
    
} awe_modMuteSyncInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMuteSyncClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modMuteSyncConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_MUTESYNC, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modMuteSyncProcess(void *pInstance);

UINT32 awe_modMuteSyncSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MUTESYNC_H

/**
 * @}
 *
 * End of file.
 */
