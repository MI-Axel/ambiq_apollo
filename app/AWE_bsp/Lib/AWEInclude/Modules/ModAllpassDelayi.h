/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAllpassDelayi.h
****************************************************************************
*
*     Description:  Interpolated time allpass delay
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
 * @brief Interpolated time allpass delay
 */

#ifndef _MOD_ALLPASSDELAYI_H
#define _MOD_ALLPASSDELAYI_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_AllpassDelayi_maxDelay 0x00000100
#define MASK_AllpassDelayi_currentDelay 0x00000200
#define MASK_AllpassDelayi_modDepth 0x00000400
#define MASK_AllpassDelayi_coef 0x00000800
#define MASK_AllpassDelayi_stateIndex 0x00001000
#define MASK_AllpassDelayi_state 0x00002000
#define OFFSET_AllpassDelayi_maxDelay 0x00000008
#define OFFSET_AllpassDelayi_currentDelay 0x00000009
#define OFFSET_AllpassDelayi_modDepth 0x0000000A
#define OFFSET_AllpassDelayi_coef 0x0000000B
#define OFFSET_AllpassDelayi_stateIndex 0x0000000C
#define OFFSET_AllpassDelayi_state 0x0000000D

#define CLASSID_ALLPASSDELAYI (CLASS_ID_MODBASE + 1211)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAllpassDelayiInstance
{
    ModuleInstanceDescriptor instance;
    INT32              maxDelay;            // Maximum delay that can be realized, in samples.  The size of the delay buffer (maxDelay+1)*numChannels
    FLOAT32            currentDelay;        // Current delay
    FLOAT32            modDepth;            // Maximum depth, in samples, of the modulation signal
    FLOAT32            coef;                // Feedback/-feedforward coefficient for the allpass delay.
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables
    FLOAT32*           state;               // State variable array
} awe_modAllpassDelayiInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAllpassDelayiClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modAllpassDelayiConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modAllpassDelayiProcess(void *pInstance);

 

void awe_modAllpassDelayiBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_ALLPASSDELAYI_H

/**
 * @}
 *
 * End of file.
 */
