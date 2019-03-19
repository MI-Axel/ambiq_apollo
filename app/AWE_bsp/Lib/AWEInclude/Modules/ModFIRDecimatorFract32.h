/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModFIRDecimatorFract32.h
****************************************************************************
*
*     Description:  Decimator combining an FIR filter and a downsampler
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
 * @brief Decimator combining an FIR filter and a downsampler
 */

#ifndef _MOD_FIRDECIMATORFRACT32_H
#define _MOD_FIRDECIMATORFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_FIRDecimatorFract32_D 0x00000100
#define MASK_FIRDecimatorFract32_N 0x00000200
#define MASK_FIRDecimatorFract32_stateIndex 0x00000400
#define MASK_FIRDecimatorFract32_stateLen 0x00000800
#define MASK_FIRDecimatorFract32_postShift 0x00001000
#define MASK_FIRDecimatorFract32_coeffs 0x00002000
#define MASK_FIRDecimatorFract32_coeffsFract32 0x00004000
#define MASK_FIRDecimatorFract32_state 0x00008000
#define OFFSET_FIRDecimatorFract32_D 0x00000008
#define OFFSET_FIRDecimatorFract32_N 0x00000009
#define OFFSET_FIRDecimatorFract32_stateIndex 0x0000000A
#define OFFSET_FIRDecimatorFract32_stateLen 0x0000000B
#define OFFSET_FIRDecimatorFract32_postShift 0x0000000C
#define OFFSET_FIRDecimatorFract32_coeffs 0x0000000D
#define OFFSET_FIRDecimatorFract32_coeffsFract32 0x0000000E
#define OFFSET_FIRDecimatorFract32_state 0x0000000F

#define CLASSID_FIRDECIMATORFRACT32 (CLASS_ID_MODBASE + 1271)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modFIRDecimatorFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              D;                   // Downsampling factor
    INT32              N;                   // Length of the filter
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables
    INT32              stateLen;            // Length of the circular buffer used by each channel
    INT32              postShift;           // Number of bits to shift
    FLOAT32*           coeffs;              // Filter coefficient array in normal order
    fract32*           coeffsFract32;       // Filter Fract32 coefficient array in normal order
    fract32*           state;               // State variable array.  The size of the array equals stateLen * numChannels
} awe_modFIRDecimatorFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modFIRDecimatorFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modFIRDecimatorFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modFIRDecimatorFract32Process(void *pInstance);

UINT32 awe_modFIRDecimatorFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_FIRDECIMATORFRACT32_H

/**
 * @}
 *
 * End of file.
 */
