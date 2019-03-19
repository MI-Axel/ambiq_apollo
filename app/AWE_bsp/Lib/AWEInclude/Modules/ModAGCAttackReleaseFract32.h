/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAGCAttackReleaseFract32.h
****************************************************************************
*
*     Description:  Multi-channel envelope detector in Fract32 with programmable attack and release times
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
 * @brief Multi-channel envelope detector in Fract32 with programmable attack and release times
 */

#ifndef _MOD_AGCATTACKRELEASEFRACT32_H
#define _MOD_AGCATTACKRELEASEFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_AGCAttackReleaseFract32_attackTime 0x00000100
#define MASK_AGCAttackReleaseFract32_releaseTime 0x00000200
#define MASK_AGCAttackReleaseFract32_attackCoeff 0x00000400
#define MASK_AGCAttackReleaseFract32_releaseCoeff 0x00000800
#define MASK_AGCAttackReleaseFract32_envStates 0x00001000
#define OFFSET_AGCAttackReleaseFract32_attackTime 0x00000008
#define OFFSET_AGCAttackReleaseFract32_releaseTime 0x00000009
#define OFFSET_AGCAttackReleaseFract32_attackCoeff 0x0000000A
#define OFFSET_AGCAttackReleaseFract32_releaseCoeff 0x0000000B
#define OFFSET_AGCAttackReleaseFract32_envStates 0x0000000C

#define CLASSID_AGCATTACKRELEASEFRACT32 (CLASS_ID_MODBASE + 1200)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAGCAttackReleaseFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            attackTime;          // Speed at which the detector reacts to increasing levels.
    FLOAT32            releaseTime;         // Speed at which the detector reacts to decreasing levels.
    fract32            attackCoeff;         // Internal coefficient realizing the attack time.
    fract32            releaseCoeff;        // Internal coefficient realizing the release time.
    fract32*           envStates;           // Vector of sample-by-sample states of the envelope detectors; each column is the state for a channel.
} awe_modAGCAttackReleaseFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAGCAttackReleaseFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modAGCAttackReleaseFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modAGCAttackReleaseFract32Process(void *pInstance);

UINT32 awe_modAGCAttackReleaseFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_AGCATTACKRELEASEFRACT32_H

/**
 * @}
 *
 * End of file.
 */
