/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDelayNChan.h
****************************************************************************
*
*     Description:  Module with different time delay for each channel specified in samples
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
 * @brief Module with different time delay for each channel specified in samples
 */

#ifndef _MOD_DELAYNCHAN_H
#define _MOD_DELAYNCHAN_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DelayNChan_maxDelay 0x00000100
#define MASK_DelayNChan_stateHeap 0x00000200
#define MASK_DelayNChan_currentDelay 0x00000400
#define MASK_DelayNChan_stateIndex 0x00000800
#define MASK_DelayNChan_state 0x00001000
#define OFFSET_DelayNChan_maxDelay 0x00000008
#define OFFSET_DelayNChan_stateHeap 0x00000009
#define OFFSET_DelayNChan_currentDelay 0x0000000A
#define OFFSET_DelayNChan_stateIndex 0x0000000B
#define OFFSET_DelayNChan_state 0x0000000C

#define CLASSID_DELAYNCHAN (CLASS_ID_MODBASE + 1367)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDelayNChanInstance
{
    ModuleInstanceDescriptor instance;
    INT32              maxDelay;            // Maximum delay, in samples.
    INT32              stateHeap;           // Heap in which to allocate memory.
    INT32*             currentDelay;        // Current delay per channel, in samples.
    INT32*             stateIndex;          // Index of the oldest state variable in the array of state variables.
    FLOAT32*           state;               // State variable array.
} awe_modDelayNChanInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDelayNChanClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modDelayNChanConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modDelayNChanProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DELAYNCHAN_H

/**
 * @}
 *
 * End of file.
 */
