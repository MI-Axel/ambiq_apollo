/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDelay.h
****************************************************************************
*
*     Description:  Time delay in which the delay is specified in samples
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
 * @brief Time delay in which the delay is specified in samples
 */

#ifndef _MOD_DELAY_H
#define _MOD_DELAY_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Delay_maxDelay 0x00000100
#define MASK_Delay_currentDelay 0x00000200
#define MASK_Delay_stateIndex 0x00000400
#define MASK_Delay_stateHeap 0x00000800
#define MASK_Delay_state 0x00001000
#define OFFSET_Delay_maxDelay 0x00000008
#define OFFSET_Delay_currentDelay 0x00000009
#define OFFSET_Delay_stateIndex 0x0000000A
#define OFFSET_Delay_stateHeap 0x0000000B
#define OFFSET_Delay_state 0x0000000C

#define CLASSID_DELAY (CLASS_ID_MODBASE + 0)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDelayInstance
{
    ModuleInstanceDescriptor instance;
    INT32              maxDelay;            // Maximum delay, in samples. The size of the delay buffer is (maxDelay+1)*numChannels.
    INT32              currentDelay;        // Current delay.
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables.
    INT32              stateHeap;           // Heap in which to allocate memory.
    FLOAT32*           state;               // State variable array.
} awe_modDelayInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDelayClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modDelayConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modDelayProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DELAY_H

/**
 * @}
 *
 * End of file.
 */
