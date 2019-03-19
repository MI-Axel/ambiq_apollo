/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModFIRSparseReaderFract32.h
****************************************************************************
*
*     Description:  Sparse FIR filter which works together with the DelayStateWriter module
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
 * @brief Sparse FIR filter which works together with the DelayStateWriter module
 */

#ifndef _MOD_FIRSPARSEREADERFRACT32_H
#define _MOD_FIRSPARSEREADERFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_FIRSparseReaderFract32_numTaps 0x00000100
#define MASK_FIRSparseReaderFract32_postShift 0x00000200
#define MASK_FIRSparseReaderFract32_dswObjectID 0x00000400
#define MASK_FIRSparseReaderFract32_tapDelay 0x00000800
#define MASK_FIRSparseReaderFract32_tapDelayTarget 0x00001000
#define MASK_FIRSparseReaderFract32_tapCoeffs 0x00002000
#define MASK_FIRSparseReaderFract32_tapCoeffsFract32 0x00004000
#define MASK_FIRSparseReaderFract32_dswObjectPtr 0x00008000
#define OFFSET_FIRSparseReaderFract32_numTaps 0x00000008
#define OFFSET_FIRSparseReaderFract32_postShift 0x00000009
#define OFFSET_FIRSparseReaderFract32_dswObjectID 0x0000000A
#define OFFSET_FIRSparseReaderFract32_tapDelay 0x0000000B
#define OFFSET_FIRSparseReaderFract32_tapDelayTarget 0x0000000C
#define OFFSET_FIRSparseReaderFract32_tapCoeffs 0x0000000D
#define OFFSET_FIRSparseReaderFract32_tapCoeffsFract32 0x0000000E
#define OFFSET_FIRSparseReaderFract32_dswObjectPtr 0x0000000F

#define CLASSID_FIRSPARSEREADERFRACT32 (CLASS_ID_MODBASE + 1279)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modFIRSparseReaderFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              numTaps;             // Number of non-zero coefficients (taps) in the filter
    INT32              postShift;           // Number of bits to shift
    INT32              dswObjectID;         // Object ID of the upstream DelayStateWriter module
    INT32*             tapDelay;            // Current delay per tap
    INT32*             tapDelayTarget;      // Current delay per tap
    FLOAT32*           tapCoeffs;           // Coefficient applied to each tap output
    fract32*           tapCoeffsFract32;    // Fract32 coefficient applied to each tap output
    void *             dswObjectPtr;        // Points to the upstream DelayStateWriter module
} awe_modFIRSparseReaderFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modFIRSparseReaderFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modFIRSparseReaderFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modFIRSparseReaderFract32Process(void *pInstance);

UINT32 awe_modFIRSparseReaderFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_FIRSPARSEREADERFRACT32_H

/**
 * @}
 *
 * End of file.
 */
