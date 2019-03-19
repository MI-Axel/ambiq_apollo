/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDelayci.h
****************************************************************************
*
*     Description:  Modulated time delay using cubic interpolation
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
 * @brief Modulated time delay using cubic interpolation
 */

#ifndef _MOD_DELAYCI_H
#define _MOD_DELAYCI_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Delayci_maxDelay 0x00000100
#define MASK_Delayci_currentDelay 0x00000200
#define MASK_Delayci_modDepth 0x00000400
#define MASK_Delayci_stateIndex 0x00000800
#define MASK_Delayci_stateHeap 0x00001000
#define MASK_Delayci_state 0x00002000
#define OFFSET_Delayci_maxDelay 0x00000008
#define OFFSET_Delayci_currentDelay 0x00000009
#define OFFSET_Delayci_modDepth 0x0000000A
#define OFFSET_Delayci_stateIndex 0x0000000B
#define OFFSET_Delayci_stateHeap 0x0000000C
#define OFFSET_Delayci_state 0x0000000D

#define CLASSID_DELAYCI (CLASS_ID_MODBASE + 2006)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDelayciInstance
{
    ModuleInstanceDescriptor instance;
    INT32              maxDelay;            // Maximum delay that can be realized, in samples.  The size of the delay buffer (maxDelay+1)*numChannels
    FLOAT32            currentDelay;        // Current delay
    FLOAT32            modDepth;            // Maximum depth, in samples, of the modulation signal
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables
    INT32              stateHeap;           // Heap in which to allocate memory
    FLOAT32*           state;               // State variable array
} awe_modDelayciInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDelayciClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modDelayciConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modDelayciProcess(void *pInstance);

 

void awe_modDelayciBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_DELAYCI_H

/**
 * @}
 *
 * End of file.
 */
