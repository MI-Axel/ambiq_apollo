/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDelayInterpFract32.h
****************************************************************************
*
*     Description:  Cubic or Linear interpolated time delay Fractional version
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
 * @brief Cubic or Linear interpolated time delay Fractional version
 */

#ifndef _MOD_DELAYINTERPFRACT32_H
#define _MOD_DELAYINTERPFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DelayInterpFract32_maxDelay 0x00000100
#define MASK_DelayInterpFract32_interpType 0x00000200
#define MASK_DelayInterpFract32_currentDelay 0x00000400
#define MASK_DelayInterpFract32_currentDelayFract32 0x00000800
#define MASK_DelayInterpFract32_modDepth 0x00001000
#define MASK_DelayInterpFract32_modDepthFract32 0x00002000
#define MASK_DelayInterpFract32_postShift 0x00004000
#define MASK_DelayInterpFract32_stateIndex 0x00008000
#define MASK_DelayInterpFract32_stateHeap 0x00010000
#define MASK_DelayInterpFract32_state 0x00020000
#define OFFSET_DelayInterpFract32_maxDelay 0x00000008
#define OFFSET_DelayInterpFract32_interpType 0x00000009
#define OFFSET_DelayInterpFract32_currentDelay 0x0000000A
#define OFFSET_DelayInterpFract32_currentDelayFract32 0x0000000B
#define OFFSET_DelayInterpFract32_modDepth 0x0000000C
#define OFFSET_DelayInterpFract32_modDepthFract32 0x0000000D
#define OFFSET_DelayInterpFract32_postShift 0x0000000E
#define OFFSET_DelayInterpFract32_stateIndex 0x0000000F
#define OFFSET_DelayInterpFract32_stateHeap 0x00000010
#define OFFSET_DelayInterpFract32_state 0x00000011

#define CLASSID_DELAYINTERPFRACT32 (CLASS_ID_MODBASE + 1249)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDelayInterpFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              maxDelay;            // Maximum delay that can be realized, in samples.  The size of the delay buffer (maxDelay+1)*numChannels
    INT32              interpType;          // Interpolation type. 0 - Linear, 1 - Cubic
    FLOAT32            currentDelay;        // Current delay
    fract32            currentDelayFract32; // Current delay in Fract32 format
    FLOAT32            modDepth;            // Maximum depth, in samples, of the modulation signal
    fract32            modDepthFract32;     // Maximum depth, in samples, of the modulation signal
    INT32              postShift;           // Number of bits to shift
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables
    INT32              stateHeap;           // Heap in which to allocate memory
    fract32*           state;               // State variable array
} awe_modDelayInterpFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDelayInterpFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modDelayInterpFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modDelayInterpFract32Process(void *pInstance);

UINT32 awe_modDelayInterpFract32Set(void *pInstance, UINT32 mask);
 

void awe_modDelayInterpFract32Bypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_DELAYINTERPFRACT32_H

/**
 * @}
 *
 * End of file.
 */
