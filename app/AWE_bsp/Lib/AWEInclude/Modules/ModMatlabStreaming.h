/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMatlabStreaming.h
****************************************************************************
*
*     Description:  Streams real-time data from MATLAB to the target
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
 * @brief Streams real-time data from MATLAB to the target
 */

#ifndef _MOD_MATLABSTREAMING_H
#define _MOD_MATLABSTREAMING_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MatlabStreaming_transferBufferSize 0x00000100
#define MASK_MatlabStreaming_circularBufferSize 0x00000200
#define MASK_MatlabStreaming_prefillLevel 0x00000400
#define MASK_MatlabStreaming_underflowCount 0x00000800
#define MASK_MatlabStreaming_currentFillLevel 0x00001000
#define MASK_MatlabStreaming_isReady 0x00002000
#define MASK_MatlabStreaming_isPrefilling 0x00004000
#define MASK_MatlabStreaming_asyncStatus 0x00008000
#define MASK_MatlabStreaming_playbackState 0x00010000
#define MASK_MatlabStreaming_isNewStream 0x00020000
#define MASK_MatlabStreaming_fileExtension 0x00040000
#define MASK_MatlabStreaming_writeIndex 0x00080000
#define MASK_MatlabStreaming_readIndex 0x00100000
#define MASK_MatlabStreaming_transferBuffer 0x00200000
#define MASK_MatlabStreaming_circularBuffer 0x00400000
#define OFFSET_MatlabStreaming_transferBufferSize 0x00000008
#define OFFSET_MatlabStreaming_circularBufferSize 0x00000009
#define OFFSET_MatlabStreaming_prefillLevel 0x0000000A
#define OFFSET_MatlabStreaming_underflowCount 0x0000000B
#define OFFSET_MatlabStreaming_currentFillLevel 0x0000000C
#define OFFSET_MatlabStreaming_isReady 0x0000000D
#define OFFSET_MatlabStreaming_isPrefilling 0x0000000E
#define OFFSET_MatlabStreaming_asyncStatus 0x0000000F
#define OFFSET_MatlabStreaming_playbackState 0x00000010
#define OFFSET_MatlabStreaming_isNewStream 0x00000011
#define OFFSET_MatlabStreaming_fileExtension 0x00000012
#define OFFSET_MatlabStreaming_writeIndex 0x00000013
#define OFFSET_MatlabStreaming_readIndex 0x00000014
#define OFFSET_MatlabStreaming_transferBuffer 0x00000015
#define OFFSET_MatlabStreaming_circularBuffer 0x00000016

#define CLASSID_MATLABSTREAMING (CLASS_ID_MODBASE + 2020)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMatlabStreamingInstance
{
    ModuleInstanceDescriptor instance;
    INT32              transferBufferSize;  // Size of the transfer buffer, in 32-bit words.
    INT32              circularBufferSize;  // Size of the circular buffer, in 32-bit words.
    INT32              prefillLevel;        // Circular buffer fills to this number of words before data is output.
    INT32              underflowCount;      // Number of output samples that could not be serviced.
    INT32              currentFillLevel;    // Number of available data samples in the circular buffer.
    INT32              isReady;             // Boolean that indicates whether the module is ready to output data.
    INT32              isPrefilling;        // Boolean that indicates whether the module is waiting for prefill data. While waiting, the module does not output data.
    INT32              asyncStatus;         // Used to pass asynchronous messages (pause/stop/play) from the PC to the target.
    INT32              playbackState;       // Indicates the current state of the player: FIOS_Stopped, FIOS_Playing, FIOS_Paused. Starts out in FIOS_Stopped.
    INT32              isNewStream;         // Boolean that indicates whether the player has just output the first block of a new file.
    INT32              fileExtension;       // First 4 letters of the file extension each packed as a byte into the word (for commonality with the file_streaming_module.m).
    INT32              writeIndex;          // Index at which to write data into the circular buffer.
    INT32              readIndex;           // Index at which to read data out of the circular buffer.
    INT32*             transferBuffer;      // Data transferred from PC to target DSP via this buffer.
    INT32*             circularBuffer;      // Data transferred from PC to target DSP via this buffer.
} awe_modMatlabStreamingInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMatlabStreamingClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modMatlabStreamingConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modMatlabStreamingProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MATLABSTREAMING_H

/**
 * @}
 *
 * End of file.
 */
