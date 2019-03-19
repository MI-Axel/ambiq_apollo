/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDelayNChanMsec.h
****************************************************************************
*
*     Description:  Module with different time delay for each channel specified in milliseconds
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
 * @brief Module with different time delay for each channel specified in milliseconds
 */

#ifndef _MOD_DELAYNCHANMSEC_H
#define _MOD_DELAYNCHANMSEC_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModDelayNChan.h"

#define MASK_DelayNChanMsec_maxDelayTime 0x00000100
#define MASK_DelayNChanMsec_stateHeap 0x00000200
#define MASK_DelayNChanMsec_maxDelay 0x00000400
#define MASK_DelayNChanMsec_currentDelayTime 0x00000800
#define OFFSET_DelayNChanMsec_maxDelayTime 0x00000008
#define OFFSET_DelayNChanMsec_stateHeap 0x00000009
#define OFFSET_DelayNChanMsec_maxDelay 0x0000000A
#define OFFSET_DelayNChanMsec_currentDelayTime 0x0000000B

#define CLASSID_DELAYNCHANMSEC (CLASS_ID_MODBASE + 1368)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDelayNChanMsecInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            maxDelayTime;        // Maximum delay, in milliseconds.
    INT32              stateHeap;           // Heap in which to allocate memory. Used to pass the value to internal delaynchan module.
    INT32              maxDelay;            // Max delay in samples. Used to pass the value to internal delaynchan module.
    FLOAT32*           currentDelayTime;    // Current delay, in milliseconds.
        awe_modDelayNChanInstance    *delay;              // Module with different time delay for each channel specified in samples
} awe_modDelayNChanMsecInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDelayNChanMsecClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modDelayNChanMsecConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modDelayNChanMsecProcess(void *pInstance);

UINT32 awe_modDelayNChanMsecSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DELAYNCHANMSEC_H

/**
 * @}
 *
 * End of file.
 */
