/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDownwardExpanderCore.h
****************************************************************************
*
*     Description:  Gain computer used to realize a downward expander (or noise gate)
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
 * @brief Gain computer used to realize a downward expander (or noise gate)
 */

#ifndef _MOD_DOWNWARDEXPANDERCORE_H
#define _MOD_DOWNWARDEXPANDERCORE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DownwardExpanderCore_threshold 0x00000100
#define MASK_DownwardExpanderCore_ratio 0x00000200
#define MASK_DownwardExpanderCore_kneeDepth 0x00000400
#define MASK_DownwardExpanderCore_attackTime 0x00000800
#define MASK_DownwardExpanderCore_decayTime 0x00001000
#define MASK_DownwardExpanderCore_currentGain 0x00002000
#define MASK_DownwardExpanderCore_attackCoeff 0x00004000
#define MASK_DownwardExpanderCore_decayCoeff 0x00008000
#define MASK_DownwardExpanderCore_envState 0x00010000
#define MASK_DownwardExpanderCore_kneePoly 0x00020000
#define OFFSET_DownwardExpanderCore_threshold 0x00000008
#define OFFSET_DownwardExpanderCore_ratio 0x00000009
#define OFFSET_DownwardExpanderCore_kneeDepth 0x0000000A
#define OFFSET_DownwardExpanderCore_attackTime 0x0000000B
#define OFFSET_DownwardExpanderCore_decayTime 0x0000000C
#define OFFSET_DownwardExpanderCore_currentGain 0x0000000D
#define OFFSET_DownwardExpanderCore_attackCoeff 0x0000000E
#define OFFSET_DownwardExpanderCore_decayCoeff 0x0000000F
#define OFFSET_DownwardExpanderCore_envState 0x00000010
#define OFFSET_DownwardExpanderCore_kneePoly 0x00000011

#define CLASSID_DOWNWARDEXPANDERCORE (CLASS_ID_MODBASE + 1263)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDownwardExpanderCoreInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            threshold;           // Below this level the module reduces gain
    FLOAT32            ratio;               // Slope of the gain curve when the signal is below the threshold
    FLOAT32            kneeDepth;           // Knee depth controls the sharpness of the transition between expanding and not expanding
    FLOAT32            attackTime;          // Envelope detector attack time constant
    FLOAT32            decayTime;           // Envelope detector decay time constant
    FLOAT32            currentGain;         // Instantaneous gain computed by the block
    FLOAT32            attackCoeff;         // Internal derived variable which implements the attackTime
    FLOAT32            decayCoeff;          // Internal derived variable which implements the decayTime
    FLOAT32            envState;            // Holds the instantaneous state of the envelope detector
    FLOAT32*           kneePoly;            // Derived variable for interpolating the soft knee
} awe_modDownwardExpanderCoreInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDownwardExpanderCoreClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modDownwardExpanderCoreConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modDownwardExpanderCoreProcess(void *pInstance);

UINT32 awe_modDownwardExpanderCoreSet(void *pInstance, UINT32 mask);
 

void awe_modDownwardExpanderCoreBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_DOWNWARDEXPANDERCORE_H

/**
 * @}
 *
 * End of file.
 */
