/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDelayMsec.h
****************************************************************************
*
*     Description:  Time delay in which the delay is specified in milliseconds
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
 * @brief Time delay in which the delay is specified in milliseconds
 */

#ifndef _MOD_DELAYMSEC_H
#define _MOD_DELAYMSEC_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModDelay.h"

#define MASK_DelayMsec_maxDelayTime 0x00000100
#define MASK_DelayMsec_currentDelayTime 0x00000200
#define MASK_DelayMsec_stateHeap 0x00000400
#define OFFSET_DelayMsec_maxDelayTime 0x00000008
#define OFFSET_DelayMsec_currentDelayTime 0x00000009
#define OFFSET_DelayMsec_stateHeap 0x0000000A

#define CLASSID_DELAYMSEC (CLASS_ID_MODBASE + 1)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDelayMsecInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            maxDelayTime;        // Maximum delay, in milliseconds.
    FLOAT32            currentDelayTime;    // Current delay.
    INT32              stateHeap;           // Heap in which to allocate state buffer memory.
        awe_modDelayInstance    *delay;              // Time delay in which the delay is specified in samples
} awe_modDelayMsecInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDelayMsecClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modDelayMsecConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modDelayMsecProcess(void *pInstance);

UINT32 awe_modDelayMsecSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DELAYMSEC_H

/**
 * @}
 *
 * End of file.
 */
