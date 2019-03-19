/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModFileStreaming.h
****************************************************************************
*
*     Description:  Streams real-time data from a file to the target
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
 * @brief Streams real-time data from a file to the target
 */

#ifndef _MOD_FILESTREAMING_H
#define _MOD_FILESTREAMING_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_FileStreaming_transferBufferSize 0x00000100
#define MASK_FileStreaming_circularBufferSize 0x00000200
#define MASK_FileStreaming_prefillLevel 0x00000400
#define MASK_FileStreaming_underflowCount 0x00000800
#define MASK_FileStreaming_currentFillLevel 0x00001000
#define MASK_FileStreaming_isReady 0x00002000
#define MASK_FileStreaming_isPrefilling 0x00004000
#define MASK_FileStreaming_asyncStatus 0x00008000
#define MASK_FileStreaming_playbackState 0x00010000
#define MASK_FileStreaming_isNewStream 0x00020000
#define MASK_FileStreaming_fileExtension 0x00040000
#define MASK_FileStreaming_writeIndex 0x00080000
#define MASK_FileStreaming_readIndex 0x00100000
#define MASK_FileStreaming_transferBuffer 0x00200000
#define MASK_FileStreaming_circularBuffer 0x00400000
#define OFFSET_FileStreaming_transferBufferSize 0x00000008
#define OFFSET_FileStreaming_circularBufferSize 0x00000009
#define OFFSET_FileStreaming_prefillLevel 0x0000000A
#define OFFSET_FileStreaming_underflowCount 0x0000000B
#define OFFSET_FileStreaming_currentFillLevel 0x0000000C
#define OFFSET_FileStreaming_isReady 0x0000000D
#define OFFSET_FileStreaming_isPrefilling 0x0000000E
#define OFFSET_FileStreaming_asyncStatus 0x0000000F
#define OFFSET_FileStreaming_playbackState 0x00000010
#define OFFSET_FileStreaming_isNewStream 0x00000011
#define OFFSET_FileStreaming_fileExtension 0x00000012
#define OFFSET_FileStreaming_writeIndex 0x00000013
#define OFFSET_FileStreaming_readIndex 0x00000014
#define OFFSET_FileStreaming_transferBuffer 0x00000015
#define OFFSET_FileStreaming_circularBuffer 0x00000016

#define CLASSID_FILESTREAMING (CLASS_ID_MODBASE + 2011)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modFileStreamingInstance
{
    ModuleInstanceDescriptor instance;
    INT32              transferBufferSize;  // Size of the transfer buffer, in 32-bit words.
    INT32              circularBufferSize;  // Size of the circular buffer, in 32-bit words.
    INT32              prefillLevel;        // Circular buffer fills to this number of words before data is output.
    INT32              underflowCount;      // Number of output words that could not be serviced.
    INT32              currentFillLevel;    // Number of available words in the circular buffer.
    INT32              isReady;             // Boolean that indicates whether the module is ready to output data.
    INT32              isPrefilling;        // Boolean that indicates whether the module is waiting for prefill data. While waiting, the module does not output data.
    INT32              asyncStatus;         // Used to pass asynchronous messages (pause/stop/play) from the PC to the target.
    INT32              playbackState;       // Indicates the current state of the player: FIOS_Stopped, FIOS_Playing, FIOS_Paused. Starts out in FIOS_Stopped.
    INT32              isNewStream;         // Boolean that indicates whether the player has just output the first block of a new file.
    INT32              fileExtension;       // First 4 letters of the file extension, each packed as a byte into the word.
    INT32              writeIndex;          // Index at which to write data into the circular buffer.
    INT32              readIndex;           // Index at which to read data out of the circular buffer.
    INT32*             transferBuffer;      // Data transferred from PC to target DSP via this buffer.
    INT32*             circularBuffer;      // Data transferred from PC to target DSP via this buffer.
} awe_modFileStreamingInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modFileStreamingClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modFileStreamingConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modFileStreamingProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_FILESTREAMING_H

/**
 * @}
 *
 * End of file.
 */
