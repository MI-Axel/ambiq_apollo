/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAllpassDelayci.h
****************************************************************************
*
*     Description:  High order allpass structure with fractional time delays
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
 * @brief High order allpass structure with fractional time delays
 */

#ifndef _MOD_ALLPASSDELAYCI_H
#define _MOD_ALLPASSDELAYCI_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_AllpassDelayci_maxDelay 0x00000100
#define MASK_AllpassDelayci_currentDelay 0x00000200
#define MASK_AllpassDelayci_modDepth 0x00000400
#define MASK_AllpassDelayci_coef 0x00000800
#define MASK_AllpassDelayci_stateIndex 0x00001000
#define MASK_AllpassDelayci_state 0x00002000
#define OFFSET_AllpassDelayci_maxDelay 0x00000008
#define OFFSET_AllpassDelayci_currentDelay 0x00000009
#define OFFSET_AllpassDelayci_modDepth 0x0000000A
#define OFFSET_AllpassDelayci_coef 0x0000000B
#define OFFSET_AllpassDelayci_stateIndex 0x0000000C
#define OFFSET_AllpassDelayci_state 0x0000000D

#define CLASSID_ALLPASSDELAYCI (CLASS_ID_MODBASE + 1210)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAllpassDelayciInstance
{
    ModuleInstanceDescriptor instance;
    INT32              maxDelay;            // Maximum delay that can be realized, in samples.  The size of the delay buffer (maxDelay+1)*numChannels
    FLOAT32            currentDelay;        // Current delay, in samples. This can be a non-integer number of samples.
    FLOAT32            modDepth;            // Maximum depth, in samples, of the modulation signal
    FLOAT32            coef;                // Feedback/-feedforward coefficient for the allpass delay.
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables
    FLOAT32*           state;               // State variable array
} awe_modAllpassDelayciInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAllpassDelayciClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modAllpassDelayciConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modAllpassDelayciProcess(void *pInstance);

 

void awe_modAllpassDelayciBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_ALLPASSDELAYCI_H

/**
 * @}
 *
 * End of file.
 */
