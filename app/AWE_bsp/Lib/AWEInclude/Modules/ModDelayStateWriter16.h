/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDelayStateWriter16.h
****************************************************************************
*
*     Description:  Writes data into an internal 16-bit circular state buffer
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
 * @brief Writes data into an internal 16-bit circular state buffer
 */

#ifndef _MOD_DELAYSTATEWRITER16_H
#define _MOD_DELAYSTATEWRITER16_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DelayStateWriter16_maxDelay 0x00000100
#define MASK_DelayStateWriter16_stateLen 0x00000200
#define MASK_DelayStateWriter16_stateIndex 0x00000400
#define MASK_DelayStateWriter16_stateHeap 0x00000800
#define MASK_DelayStateWriter16_state 0x00001000
#define OFFSET_DelayStateWriter16_maxDelay 0x00000008
#define OFFSET_DelayStateWriter16_stateLen 0x00000009
#define OFFSET_DelayStateWriter16_stateIndex 0x0000000A
#define OFFSET_DelayStateWriter16_stateHeap 0x0000000B
#define OFFSET_DelayStateWriter16_state 0x0000000C

#define CLASSID_DELAYSTATEWRITER16 (CLASS_ID_MODBASE + 1253)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDelayStateWriter16Instance
{
    ModuleInstanceDescriptor instance;
    INT32              maxDelay;            // Maximum delay, per channel.
    INT32              stateLen;            // Size of the internal state buffer.
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables.
    INT32              stateHeap;           // Heap in which to allocate memory.
    FLOAT32*           state;               // State variable array.
} awe_modDelayStateWriter16Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDelayStateWriter16Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modDelayStateWriter16Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modDelayStateWriter16Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DELAYSTATEWRITER16_H

/**
 * @}
 *
 * End of file.
 */
