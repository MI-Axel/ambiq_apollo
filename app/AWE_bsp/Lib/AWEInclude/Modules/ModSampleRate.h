/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSampleRate.h
****************************************************************************
*
*     Description:  Measures the sample rate of the input signal
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
 * @brief Measures the sample rate of the input signal
 */

#ifndef _MOD_SAMPLERATE_H
#define _MOD_SAMPLERATE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SampleRate_procSpeed 0x00000100
#define MASK_SampleRate_numBlocksToAverage 0x00000200
#define MASK_SampleRate_lastCount 0x00000400
#define MASK_SampleRate_averageDeltaCount 0x00000800
#define MASK_SampleRate_SRArrayLength 0x00001000
#define MASK_SampleRate_initialized 0x00002000
#define MASK_SampleRate_dataValid 0x00004000
#define MASK_SampleRate_measuredSR 0x00008000
#define MASK_SampleRate_prevMeasuredSR 0x00010000
#define MASK_SampleRate_prevPrevMeasuredSR 0x00020000
#define MASK_SampleRate_SROutPin 0x00040000
#define MASK_SampleRate_blockCounter 0x00080000
#define MASK_SampleRate_allowableSR 0x00100000
#define OFFSET_SampleRate_procSpeed 0x00000008
#define OFFSET_SampleRate_numBlocksToAverage 0x00000009
#define OFFSET_SampleRate_lastCount 0x0000000A
#define OFFSET_SampleRate_averageDeltaCount 0x0000000B
#define OFFSET_SampleRate_SRArrayLength 0x0000000C
#define OFFSET_SampleRate_initialized 0x0000000D
#define OFFSET_SampleRate_dataValid 0x0000000E
#define OFFSET_SampleRate_measuredSR 0x0000000F
#define OFFSET_SampleRate_prevMeasuredSR 0x00000010
#define OFFSET_SampleRate_prevPrevMeasuredSR 0x00000011
#define OFFSET_SampleRate_SROutPin 0x00000012
#define OFFSET_SampleRate_blockCounter 0x00000013
#define OFFSET_SampleRate_allowableSR 0x00000014

#define CLASSID_SAMPLERATE (CLASS_ID_MODBASE + 1318)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSampleRateInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            procSpeed;           // Processor clock speed in MHz
    INT32              numBlocksToAverage;  // Number of blocks to process before the sample rate is retured
    INT32              lastCount;           // Holds the last call cycle count
    INT32              averageDeltaCount;   // Holds the average delta count of numBlocksToAverage calls
    INT32              SRArrayLength;       // Number of sample rates that can be estimated
    INT32              initialized;         // Specifies whether the last cycle counter has been initialized
    INT32              dataValid;           // Indicates whether the sample rate measurement is valid
    FLOAT32            measuredSR;          // Readback variable.  Displays the measured sample rate on the inspector
    FLOAT32            prevMeasuredSR;      // Last measured sample rate
    FLOAT32            prevPrevMeasuredSR;  // Previous to last measured sample rate
    INT32              SROutPin;            // Boolean specifies whether module will have output pin
    INT32              blockCounter;        // Counts up to numBlocksToAverage
    FLOAT32*           allowableSR;         // Array of possible sample rates
} awe_modSampleRateInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSampleRateClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modSampleRateConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modSampleRateProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SAMPLERATE_H

/**
 * @}
 *
 * End of file.
 */
