/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAttackDecaySustainRelease.h
****************************************************************************
*
*     Description:  Multi-channel envelope detector with programmable attack time, decay time, sustain level and release time
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
 * @brief Multi-channel envelope detector with programmable attack time, decay time, sustain level and release time
 */

#ifndef _MOD_ATTACKDECAYSUSTAINRELEASE_H
#define _MOD_ATTACKDECAYSUSTAINRELEASE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_AttackDecaySustainRelease_attackTime 0x00000100
#define MASK_AttackDecaySustainRelease_decayTime 0x00000200
#define MASK_AttackDecaySustainRelease_sustainLevel 0x00000400
#define MASK_AttackDecaySustainRelease_releaseTime 0x00000800
#define MASK_AttackDecaySustainRelease_maxLevel 0x00001000
#define MASK_AttackDecaySustainRelease_startAttack 0x00002000
#define MASK_AttackDecaySustainRelease_startRelease 0x00004000
#define MASK_AttackDecaySustainRelease_attackCoeff 0x00008000
#define MASK_AttackDecaySustainRelease_decayCoeff 0x00010000
#define MASK_AttackDecaySustainRelease_releaseCoeff 0x00020000
#define MASK_AttackDecaySustainRelease_adsrState 0x00040000
#define MASK_AttackDecaySustainRelease_envStates 0x00080000
#define OFFSET_AttackDecaySustainRelease_attackTime 0x00000008
#define OFFSET_AttackDecaySustainRelease_decayTime 0x00000009
#define OFFSET_AttackDecaySustainRelease_sustainLevel 0x0000000A
#define OFFSET_AttackDecaySustainRelease_releaseTime 0x0000000B
#define OFFSET_AttackDecaySustainRelease_maxLevel 0x0000000C
#define OFFSET_AttackDecaySustainRelease_startAttack 0x0000000D
#define OFFSET_AttackDecaySustainRelease_startRelease 0x0000000E
#define OFFSET_AttackDecaySustainRelease_attackCoeff 0x0000000F
#define OFFSET_AttackDecaySustainRelease_decayCoeff 0x00000010
#define OFFSET_AttackDecaySustainRelease_releaseCoeff 0x00000011
#define OFFSET_AttackDecaySustainRelease_adsrState 0x00000012
#define OFFSET_AttackDecaySustainRelease_envStates 0x00000013

#define CLASSID_ATTACKDECAYSUSTAINRELEASE (CLASS_ID_MODBASE + 1212)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAttackDecaySustainReleaseInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            attackTime;          // Time taken for initial run-up level from nill peak, beginning when the key is first pressed.
    FLOAT32            decayTime;           // Time taken for the subsequent run down from the attack level to the designated sustain level.
    FLOAT32            sustainLevel;        // Level during the main sequence of the sound duration, until the key is released.
    FLOAT32            releaseTime;         // Time taken for the level to decay from the sustain level to zero after the key is released.
    FLOAT32            maxLevel;            // Maximum level to which attack phase reach from zero to this level.
    INT32              startAttack;         // Flag indicates start of attack phase. This is a trigger control.
    INT32              startRelease;        // Flag indicates start release phase. This is a trigger control.
    FLOAT32            attackCoeff;         // Internal coefficient realizing the attack time.
    FLOAT32            decayCoeff;          // Internal coefficient realizing the decay time.
    FLOAT32            releaseCoeff;        // Internal coefficient realizing the release time.
    INT32              adsrState;           // Internal state to switch between Attack, Decay, Sustain and Release states.
    FLOAT32*           envStates;           // Vector of sample-by-sample states of the envelope detectors; each column is the state for a channel.
} awe_modAttackDecaySustainReleaseInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAttackDecaySustainReleaseClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modAttackDecaySustainReleaseConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modAttackDecaySustainReleaseProcess(void *pInstance);

UINT32 awe_modAttackDecaySustainReleaseSet(void *pInstance, UINT32 mask);
 

void awe_modAttackDecaySustainReleaseBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_ATTACKDECAYSUSTAINRELEASE_H

/**
 * @}
 *
 * End of file.
 */
