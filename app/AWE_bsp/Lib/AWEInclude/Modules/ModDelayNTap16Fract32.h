/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDelayNTap16Fract32.h
****************************************************************************
*
*     Description:  Time delay with multiple output taps
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
 * @brief Time delay with multiple output taps
 */

#ifndef _MOD_DELAYNTAP16FRACT32_H
#define _MOD_DELAYNTAP16FRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DelayNTap16Fract32_numTaps 0x00000100
#define MASK_DelayNTap16Fract32_maxDelay 0x00000200
#define MASK_DelayNTap16Fract32_oneOutputPin 0x00000400
#define MASK_DelayNTap16Fract32_stateIndex 0x00000800
#define MASK_DelayNTap16Fract32_stateHeap 0x00001000
#define MASK_DelayNTap16Fract32_currentDelay 0x00002000
#define MASK_DelayNTap16Fract32_state 0x00004000
#define OFFSET_DelayNTap16Fract32_numTaps 0x00000008
#define OFFSET_DelayNTap16Fract32_maxDelay 0x00000009
#define OFFSET_DelayNTap16Fract32_oneOutputPin 0x0000000A
#define OFFSET_DelayNTap16Fract32_stateIndex 0x0000000B
#define OFFSET_DelayNTap16Fract32_stateHeap 0x0000000C
#define OFFSET_DelayNTap16Fract32_currentDelay 0x0000000D
#define OFFSET_DelayNTap16Fract32_state 0x0000000E

#define CLASSID_DELAYNTAP16FRACT32 (CLASS_ID_MODBASE + 1257)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDelayNTap16Fract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              numTaps;             // Number of output taps
    INT32              maxDelay;            // Maximum delay, in samples.
    INT32              oneOutputPin;        // Specifies a single multichannel output pin.
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables.
    INT32              stateHeap;           // Heap in which to allocate memory.
    INT32*             currentDelay;        // Current delay.
    INT32*             state;               // State variable array.
} awe_modDelayNTap16Fract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDelayNTap16Fract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modDelayNTap16Fract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modDelayNTap16Fract32Process(void *pInstance);

 

void awe_modDelayNTap16Fract32Bypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_DELAYNTAP16FRACT32_H

/**
 * @}
 *
 * End of file.
 */
