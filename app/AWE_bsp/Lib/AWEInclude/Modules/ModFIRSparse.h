/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModFIRSparse.h
****************************************************************************
*
*     Description:  Sparse FIR filter in which most coefficients equal zero
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
 * @brief Sparse FIR filter in which most coefficients equal zero
 */

#ifndef _MOD_FIRSPARSE_H
#define _MOD_FIRSPARSE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_FIRSparse_numTaps 0x00000100
#define MASK_FIRSparse_maxDelay 0x00000200
#define MASK_FIRSparse_stateHeap 0x00000400
#define MASK_FIRSparse_stateIndex 0x00000800
#define MASK_FIRSparse_tapDelay 0x00001000
#define MASK_FIRSparse_tapCoeffs 0x00002000
#define MASK_FIRSparse_state 0x00004000
#define OFFSET_FIRSparse_numTaps 0x00000008
#define OFFSET_FIRSparse_maxDelay 0x00000009
#define OFFSET_FIRSparse_stateHeap 0x0000000A
#define OFFSET_FIRSparse_stateIndex 0x0000000B
#define OFFSET_FIRSparse_tapDelay 0x0000000C
#define OFFSET_FIRSparse_tapCoeffs 0x0000000D
#define OFFSET_FIRSparse_state 0x0000000E

#define CLASSID_FIRSPARSE (CLASS_ID_MODBASE + 1277)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modFIRSparseInstance
{
    ModuleInstanceDescriptor instance;
    INT32              numTaps;             // Number of non-zero coefficients (taps) in the filter
    INT32              maxDelay;            // Maximum delay that can be realized, in samples
    INT32              stateHeap;           // Heap in which to allocate memory
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables
    INT32*             tapDelay;            // Current delay per channel
    FLOAT32*           tapCoeffs;           // Coefficient applied to each tap output
    FLOAT32*           state;               // State variable array
} awe_modFIRSparseInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modFIRSparseClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modFIRSparseConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modFIRSparseProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_FIRSPARSE_H

/**
 * @}
 *
 * End of file.
 */
