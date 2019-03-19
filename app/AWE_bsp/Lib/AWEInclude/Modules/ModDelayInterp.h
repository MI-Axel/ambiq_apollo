/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDelayInterp.h
****************************************************************************
*
*     Description:  Modulated time delay using linear or cubic interpolation
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
 * @brief Modulated time delay using linear or cubic interpolation
 */

#ifndef _MOD_DELAYINTERP_H
#define _MOD_DELAYINTERP_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DelayInterp_maxDelay 0x00000100
#define MASK_DelayInterp_interpType 0x00000200
#define MASK_DelayInterp_currentDelay 0x00000400
#define MASK_DelayInterp_modDepth 0x00000800
#define MASK_DelayInterp_stateIndex 0x00001000
#define MASK_DelayInterp_stateHeap 0x00002000
#define MASK_DelayInterp_state 0x00004000
#define OFFSET_DelayInterp_maxDelay 0x00000008
#define OFFSET_DelayInterp_interpType 0x00000009
#define OFFSET_DelayInterp_currentDelay 0x0000000A
#define OFFSET_DelayInterp_modDepth 0x0000000B
#define OFFSET_DelayInterp_stateIndex 0x0000000C
#define OFFSET_DelayInterp_stateHeap 0x0000000D
#define OFFSET_DelayInterp_state 0x0000000E

#define CLASSID_DELAYINTERP (CLASS_ID_MODBASE + 1250)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDelayInterpInstance
{
    ModuleInstanceDescriptor instance;
    INT32              maxDelay;            // Maximum delay that can be realized, in samples.  The size of the delay buffer (maxDelay+1)*numChannels
    INT32              interpType;          // Interpolation type. 0 - Linear, 1 - Cubic
    FLOAT32            currentDelay;        // Current delay
    FLOAT32            modDepth;            // Maximum depth, in samples, of the modulation signal
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables
    INT32              stateHeap;           // Heap in which to allocate memory
    FLOAT32*           state;               // State variable array
} awe_modDelayInterpInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDelayInterpClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modDelayInterpConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modDelayInterpProcess(void *pInstance);

 

void awe_modDelayInterpBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_DELAYINTERP_H

/**
 * @}
 *
 * End of file.
 */
