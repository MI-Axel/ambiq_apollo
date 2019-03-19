/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModTimeOut.h
****************************************************************************
*
*     Description:  General purpose time out module with configurable timeout in seconds
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
 * @brief General purpose time out module with configurable timeout in seconds
 */

#ifndef _MOD_TIMEOUT_H
#define _MOD_TIMEOUT_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_TimeOut_timeOut 0x00000100
#define MASK_TimeOut_timeOutBehaviour 0x00000200
#define MASK_TimeOut_outputLevel 0x00000400
#define MASK_TimeOut_currentGain 0x00000800
#define MASK_TimeOut_gain 0x00001000
#define MASK_TimeOut_sineFreq 0x00002000
#define MASK_TimeOut_sineTableSize 0x00004000
#define MASK_TimeOut_sineTableIndx 0x00008000
#define MASK_TimeOut_currentBlockCount 0x00010000
#define MASK_TimeOut_blockCounterCount 0x00020000
#define MASK_TimeOut_smoothingTime 0x00040000
#define MASK_TimeOut_smoothingCoeff 0x00080000
#define MASK_TimeOut_sineTable 0x00100000
#define OFFSET_TimeOut_timeOut 0x00000008
#define OFFSET_TimeOut_timeOutBehaviour 0x00000009
#define OFFSET_TimeOut_outputLevel 0x0000000A
#define OFFSET_TimeOut_currentGain 0x0000000B
#define OFFSET_TimeOut_gain 0x0000000C
#define OFFSET_TimeOut_sineFreq 0x0000000D
#define OFFSET_TimeOut_sineTableSize 0x0000000E
#define OFFSET_TimeOut_sineTableIndx 0x0000000F
#define OFFSET_TimeOut_currentBlockCount 0x00000010
#define OFFSET_TimeOut_blockCounterCount 0x00000011
#define OFFSET_TimeOut_smoothingTime 0x00000012
#define OFFSET_TimeOut_smoothingCoeff 0x00000013
#define OFFSET_TimeOut_sineTable 0x00000014

#define CLASSID_TIMEOUT (CLASS_ID_MODBASE + 1346)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modTimeOutInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            timeOut;             // Timeout value in seconds. Module waits these many seconds and applies timeout based on timeOutBehaviour.
    INT32              timeOutBehaviour;    // Selects the timeout behaviour: MuteTheOutput=0 ReduceTheOutputLevel=1 PlaySineTone=2
    FLOAT32            outputLevel;         // Output level after timeout in dB.
    FLOAT32            currentGain;         // Instantaneous gain applied by the module. This is also the starting gain of the module.
    FLOAT32            gain;                // Target gain in linear units.
    FLOAT32            sineFreq;            // Sine tone frequency in Hz.
    INT32              sineTableSize;       // Sine table length.
    INT32              sineTableIndx;       // Sine table read index.
    INT32              currentBlockCount;   // Blocks counter.
    INT32              blockCounterCount;   // Number of blocks to wait before timeout occures.
    FLOAT32            smoothingTime;       // Time constant of the smoothing process.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    FLOAT32*           sineTable;           // Pre-computed Sine tone table.
} awe_modTimeOutInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modTimeOutClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modTimeOutConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modTimeOutProcess(void *pInstance);

UINT32 awe_modTimeOutSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_TIMEOUT_H

/**
 * @}
 *
 * End of file.
 */
