/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAGCVariableAttackRelease.h
****************************************************************************
*
*     Description:  Peak follower with variable attack and release rates
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
 * @brief Peak follower with variable attack and release rates
 */

#ifndef _MOD_AGCVARIABLEATTACKRELEASE_H
#define _MOD_AGCVARIABLEATTACKRELEASE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_AGCVariableAttackRelease_attackTimeInitial 0x00000100
#define MASK_AGCVariableAttackRelease_attackTimeFinal 0x00000200
#define MASK_AGCVariableAttackRelease_releaseTimeInitial 0x00000400
#define MASK_AGCVariableAttackRelease_releaseTimeFinal 0x00000800
#define MASK_AGCVariableAttackRelease_attackCoefInitial 0x00001000
#define MASK_AGCVariableAttackRelease_attackCoefFinal 0x00002000
#define MASK_AGCVariableAttackRelease_releaseCoefInitial 0x00004000
#define MASK_AGCVariableAttackRelease_releaseCoefFinal 0x00008000
#define MASK_AGCVariableAttackRelease_attackMode 0x00010000
#define MASK_AGCVariableAttackRelease_state 0x00020000
#define MASK_AGCVariableAttackRelease_startLevel 0x00040000
#define OFFSET_AGCVariableAttackRelease_attackTimeInitial 0x00000008
#define OFFSET_AGCVariableAttackRelease_attackTimeFinal 0x00000009
#define OFFSET_AGCVariableAttackRelease_releaseTimeInitial 0x0000000A
#define OFFSET_AGCVariableAttackRelease_releaseTimeFinal 0x0000000B
#define OFFSET_AGCVariableAttackRelease_attackCoefInitial 0x0000000C
#define OFFSET_AGCVariableAttackRelease_attackCoefFinal 0x0000000D
#define OFFSET_AGCVariableAttackRelease_releaseCoefInitial 0x0000000E
#define OFFSET_AGCVariableAttackRelease_releaseCoefFinal 0x0000000F
#define OFFSET_AGCVariableAttackRelease_attackMode 0x00000010
#define OFFSET_AGCVariableAttackRelease_state 0x00000011
#define OFFSET_AGCVariableAttackRelease_startLevel 0x00000012

#define CLASSID_AGCVARIABLEATTACKRELEASE (CLASS_ID_MODBASE + 1205)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAGCVariableAttackReleaseInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            attackTimeInitial;   // Envelope detector initial attack time constant
    FLOAT32            attackTimeFinal;     // Envelope detector final attack time constant
    FLOAT32            releaseTimeInitial;  // Envelope detector initial release time constant
    FLOAT32            releaseTimeFinal;    // Envelope detector final release time constant
    FLOAT32            attackCoefInitial;   // Computed coefficient used for initial attack
    FLOAT32            attackCoefFinal;     // Computed coefficient used for final attack
    FLOAT32            releaseCoefInitial;  // Computed coefficient used for initial release
    FLOAT32            releaseCoefFinal;    // Computed coefficient used for final release
    INT32              attackMode;          // Internal variable to keep track of the last mode (1 = attack, 0 = release, -1 = not started)
    FLOAT32            state;               // Internal state variable. This is also the instantaneous output value.
    FLOAT32            startLevel;          // Internal state variable to keep track of the initial value of the attack or release phase
    
} awe_modAGCVariableAttackReleaseInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAGCVariableAttackReleaseClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modAGCVariableAttackReleaseConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_AGCVARIABLEATTACKRELEASE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modAGCVariableAttackReleaseProcess(void *pInstance);

UINT32 awe_modAGCVariableAttackReleaseSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_AGCVARIABLEATTACKRELEASE_H

/**
 * @}
 *
 * End of file.
 */
