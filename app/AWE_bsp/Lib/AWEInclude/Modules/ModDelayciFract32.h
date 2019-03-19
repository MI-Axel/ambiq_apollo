/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDelayciFract32.h
****************************************************************************
*
*     Description:  Cubic interpolated time delay Fractional version
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
 * @brief Cubic interpolated time delay Fractional version
 */

#ifndef _MOD_DELAYCIFRACT32_H
#define _MOD_DELAYCIFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DelayciFract32_maxDelay 0x00000100
#define MASK_DelayciFract32_currentDelay 0x00000200
#define MASK_DelayciFract32_currentDelayFract32 0x00000400
#define MASK_DelayciFract32_modDepth 0x00000800
#define MASK_DelayciFract32_modDepthFract32 0x00001000
#define MASK_DelayciFract32_postShift 0x00002000
#define MASK_DelayciFract32_stateIndex 0x00004000
#define MASK_DelayciFract32_stateHeap 0x00008000
#define MASK_DelayciFract32_state 0x00010000
#define OFFSET_DelayciFract32_maxDelay 0x00000008
#define OFFSET_DelayciFract32_currentDelay 0x00000009
#define OFFSET_DelayciFract32_currentDelayFract32 0x0000000A
#define OFFSET_DelayciFract32_modDepth 0x0000000B
#define OFFSET_DelayciFract32_modDepthFract32 0x0000000C
#define OFFSET_DelayciFract32_postShift 0x0000000D
#define OFFSET_DelayciFract32_stateIndex 0x0000000E
#define OFFSET_DelayciFract32_stateHeap 0x0000000F
#define OFFSET_DelayciFract32_state 0x00000010

#define CLASSID_DELAYCIFRACT32 (CLASS_ID_MODBASE + 1255)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDelayciFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              maxDelay;            // Maximum delay that can be realized, in samples.  The size of the delay buffer (maxDelay+1)*numChannels
    FLOAT32            currentDelay;        // Current delay
    fract32            currentDelayFract32; // Current delay in Fract32 format
    FLOAT32            modDepth;            // Maximum depth, in samples, of the modulation signal
    fract32            modDepthFract32;     // Maximum depth, in samples, of the modulation signal
    INT32              postShift;           // Number of bits to shift
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables
    INT32              stateHeap;           // Heap in which to allocate memory
    fract32*           state;               // State variable array
} awe_modDelayciFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDelayciFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modDelayciFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modDelayciFract32Process(void *pInstance);

UINT32 awe_modDelayciFract32Set(void *pInstance, UINT32 mask);
 

void awe_modDelayciFract32Bypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_DELAYCIFRACT32_H

/**
 * @}
 *
 * End of file.
 */
