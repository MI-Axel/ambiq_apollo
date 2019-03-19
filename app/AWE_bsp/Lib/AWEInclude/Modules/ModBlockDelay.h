/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBlockDelay.h
****************************************************************************
*
*     Description:  Delays signals by a multiple of the blockSize
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
 * @brief Delays signals by a multiple of the blockSize
 */

#ifndef _MOD_BLOCKDELAY_H
#define _MOD_BLOCKDELAY_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_BlockDelay_maxBlockDelay 0x00000100
#define MASK_BlockDelay_currentBlockDelay 0x00000200
#define MASK_BlockDelay_stateIndex 0x00000400
#define MASK_BlockDelay_state 0x00000800
#define OFFSET_BlockDelay_maxBlockDelay 0x00000008
#define OFFSET_BlockDelay_currentBlockDelay 0x00000009
#define OFFSET_BlockDelay_stateIndex 0x0000000A
#define OFFSET_BlockDelay_state 0x0000000B

#define CLASSID_BLOCKDELAY (CLASS_ID_MODBASE + 1222)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBlockDelayInstance
{
    ModuleInstanceDescriptor instance;
    INT32              maxBlockDelay;       // Maximum delay that can be realized, in blocks. The size of the delay buffer, (maxDelay+1)*blockSize*numChannels.
    INT32              currentBlockDelay;   // Current block delay.
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables.
    FLOAT32*           state;               // State variable array.
} awe_modBlockDelayInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBlockDelayClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modBlockDelayConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modBlockDelayProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BLOCKDELAY_H

/**
 * @}
 *
 * End of file.
 */
