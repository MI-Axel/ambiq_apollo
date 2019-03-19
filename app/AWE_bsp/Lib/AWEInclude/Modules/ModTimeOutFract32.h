/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModTimeOutFract32.h
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

#ifndef _MOD_TIMEOUTFRACT32_H
#define _MOD_TIMEOUTFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_TimeOutFract32_timeOut 0x00000100
#define MASK_TimeOutFract32_timeOutBehaviour 0x00000200
#define MASK_TimeOutFract32_outputLevel 0x00000400
#define MASK_TimeOutFract32_currentGain 0x00000800
#define MASK_TimeOutFract32_gain 0x00001000
#define MASK_TimeOutFract32_sineFreq 0x00002000
#define MASK_TimeOutFract32_sineTableSize 0x00004000
#define MASK_TimeOutFract32_sineTableIndx 0x00008000
#define MASK_TimeOutFract32_currentBlockCount 0x00010000
#define MASK_TimeOutFract32_blockCounterCount 0x00020000
#define MASK_TimeOutFract32_smoothingTime 0x00040000
#define MASK_TimeOutFract32_smoothingCoeff 0x00080000
#define MASK_TimeOutFract32_postShift 0x00100000
#define MASK_TimeOutFract32_twoPowMinusPostShift 0x00200000
#define MASK_TimeOutFract32_sineTable 0x00400000
#define OFFSET_TimeOutFract32_timeOut 0x00000008
#define OFFSET_TimeOutFract32_timeOutBehaviour 0x00000009
#define OFFSET_TimeOutFract32_outputLevel 0x0000000A
#define OFFSET_TimeOutFract32_currentGain 0x0000000B
#define OFFSET_TimeOutFract32_gain 0x0000000C
#define OFFSET_TimeOutFract32_sineFreq 0x0000000D
#define OFFSET_TimeOutFract32_sineTableSize 0x0000000E
#define OFFSET_TimeOutFract32_sineTableIndx 0x0000000F
#define OFFSET_TimeOutFract32_currentBlockCount 0x00000010
#define OFFSET_TimeOutFract32_blockCounterCount 0x00000011
#define OFFSET_TimeOutFract32_smoothingTime 0x00000012
#define OFFSET_TimeOutFract32_smoothingCoeff 0x00000013
#define OFFSET_TimeOutFract32_postShift 0x00000014
#define OFFSET_TimeOutFract32_twoPowMinusPostShift 0x00000015
#define OFFSET_TimeOutFract32_sineTable 0x00000016

#define CLASSID_TIMEOUTFRACT32 (CLASS_ID_MODBASE + 1345)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modTimeOutFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            timeOut;             // Timeout value in seconds. Module waits these many seconds and applies timeout based on timeOutBehaviour.
    INT32              timeOutBehaviour;    // Selects the timeout behaviour: MuteTheOutput=0 ReduceTheOutputLevel=1 PlaySineTone=2
    FLOAT32            outputLevel;         // Output level after timeout in dB.
    fract32            currentGain;         // Instantaneous gain applied by the module. This is also the starting gain of the module.
    fract32            gain;                // Target gain in linear units.
    FLOAT32            sineFreq;            // Sine tone frequency in Hz.
    INT32              sineTableSize;       // Sine table length.
    INT32              sineTableIndx;       // Sine table read index.
    INT32              currentBlockCount;   // Blocks counter.
    INT32              blockCounterCount;   // Number of blocks to wait before timeout occures.
    FLOAT32            smoothingTime;       // Time constant of the smoothing process.
    fract32            smoothingCoeff;      // Smoothing coefficient.
    INT32              postShift;           // Number of bits to shift after the fractional multiply.  This is based on outputLevel.range.
    FLOAT32            twoPowMinusPostShift; // 2^(-postShift).  Used by to streamline the operation of the set function
    fract32*           sineTable;           // Pre-computed Sine tone table.
} awe_modTimeOutFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modTimeOutFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modTimeOutFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modTimeOutFract32Process(void *pInstance);

UINT32 awe_modTimeOutFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_TIMEOUTFRACT32_H

/**
 * @}
 *
 * End of file.
 */
