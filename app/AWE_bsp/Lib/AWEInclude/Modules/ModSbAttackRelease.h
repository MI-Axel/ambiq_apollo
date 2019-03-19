/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSbAttackRelease.h
****************************************************************************
*
*     Description:  Subband envelope detector array with programmable attack and release times
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
 * @brief Subband envelope detector array with programmable attack and release times
 */

#ifndef _MOD_SBATTACKRELEASE_H
#define _MOD_SBATTACKRELEASE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SbAttackRelease_attackTime 0x00000100
#define MASK_SbAttackRelease_holdTime 0x00000200
#define MASK_SbAttackRelease_releaseTime 0x00000400
#define MASK_SbAttackRelease_attackCoeff 0x00000800
#define MASK_SbAttackRelease_releaseCoeff 0x00001000
#define MASK_SbAttackRelease_holdCount 0x00002000
#define MASK_SbAttackRelease_envState 0x00004000
#define MASK_SbAttackRelease_holdState 0x00008000
#define OFFSET_SbAttackRelease_attackTime 0x00000008
#define OFFSET_SbAttackRelease_holdTime 0x00000009
#define OFFSET_SbAttackRelease_releaseTime 0x0000000A
#define OFFSET_SbAttackRelease_attackCoeff 0x0000000B
#define OFFSET_SbAttackRelease_releaseCoeff 0x0000000C
#define OFFSET_SbAttackRelease_holdCount 0x0000000D
#define OFFSET_SbAttackRelease_envState 0x0000000E
#define OFFSET_SbAttackRelease_holdState 0x0000000F

#define CLASSID_SBATTACKRELEASE (CLASS_ID_MODBASE + 1321)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSbAttackReleaseInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            attackTime;          // Speed at which the detector reacts to increasing levels.
    FLOAT32            holdTime;            // Duration to hold the output constant after the peak has been reached.
    FLOAT32            releaseTime;         // Speed at which the detector reacts to decreasing levels.
    FLOAT32            attackCoeff;         // Internal coefficient realizing the attack time.
    FLOAT32            releaseCoeff;        // Internal coefficient realizing the release time.
    INT32              holdCount;           // Hold time translated to the number of blocks
    FLOAT32*           envState;            // Vector of per-sample states of the envelope detectors
    INT32*             holdState;           // Vector of per-sample states of the envelope detectors
} awe_modSbAttackReleaseInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSbAttackReleaseClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modSbAttackReleaseConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modSbAttackReleaseProcess(void *pInstance);

UINT32 awe_modSbAttackReleaseSet(void *pInstance, UINT32 mask);
 

void awe_modSbAttackReleaseBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_SBATTACKRELEASE_H

/**
 * @}
 *
 * End of file.
 */
