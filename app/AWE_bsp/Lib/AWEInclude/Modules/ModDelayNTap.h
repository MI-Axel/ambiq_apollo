/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDelayNTap.h
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

#ifndef _MOD_DELAYNTAP_H
#define _MOD_DELAYNTAP_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DelayNTap_maxDelay 0x00000100
#define MASK_DelayNTap_stateIndex 0x00000200
#define MASK_DelayNTap_stateHeap 0x00000400
#define MASK_DelayNTap_currentDelay 0x00000800
#define MASK_DelayNTap_state 0x00001000
#define OFFSET_DelayNTap_maxDelay 0x00000008
#define OFFSET_DelayNTap_stateIndex 0x00000009
#define OFFSET_DelayNTap_stateHeap 0x0000000A
#define OFFSET_DelayNTap_currentDelay 0x0000000B
#define OFFSET_DelayNTap_state 0x0000000C

#define CLASSID_DELAYNTAP (CLASS_ID_MODBASE + 1256)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDelayNTapInstance
{
    ModuleInstanceDescriptor instance;
    INT32              maxDelay;            // Maximum delay, in samples.
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables.
    INT32              stateHeap;           // Heap in which to allocate memory.
    INT32*             currentDelay;        // Current delay.
    FLOAT32*           state;               // State variable array.
} awe_modDelayNTapInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDelayNTapClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modDelayNTapConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modDelayNTapProcess(void *pInstance);

 

void awe_modDelayNTapBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_DELAYNTAP_H

/**
 * @}
 *
 * End of file.
 */
