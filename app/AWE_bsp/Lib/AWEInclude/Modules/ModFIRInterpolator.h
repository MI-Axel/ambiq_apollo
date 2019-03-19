/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModFIRInterpolator.h
****************************************************************************
*
*     Description:  Interpolator combining an upsampler and an FIR filter
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
 * @brief Interpolator combining an upsampler and an FIR filter
 */

#ifndef _MOD_FIRINTERPOLATOR_H
#define _MOD_FIRINTERPOLATOR_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_FIRInterpolator_L 0x00000100
#define MASK_FIRInterpolator_N 0x00000200
#define MASK_FIRInterpolator_polyphaseLen 0x00000400
#define MASK_FIRInterpolator_stateIndex 0x00000800
#define MASK_FIRInterpolator_stateLen 0x00001000
#define MASK_FIRInterpolator_coeffs 0x00002000
#define MASK_FIRInterpolator_state 0x00004000
#define OFFSET_FIRInterpolator_L 0x00000008
#define OFFSET_FIRInterpolator_N 0x00000009
#define OFFSET_FIRInterpolator_polyphaseLen 0x0000000A
#define OFFSET_FIRInterpolator_stateIndex 0x0000000B
#define OFFSET_FIRInterpolator_stateLen 0x0000000C
#define OFFSET_FIRInterpolator_coeffs 0x0000000D
#define OFFSET_FIRInterpolator_state 0x0000000E

#define CLASSID_FIRINTERPOLATOR (CLASS_ID_MODBASE + 1274)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modFIRInterpolatorInstance
{
    ModuleInstanceDescriptor instance;
    INT32              L;                   // Upsampling factor.
    INT32              N;                   // Length of the filter.
    INT32              polyphaseLen;        // Length of each polyphase filter component.
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables.
    INT32              stateLen;            // Length of the circular state buffer.
    FLOAT32*           coeffs;              // Filter coefficient array in normal order.
    FLOAT32*           state;               // State variable array. The size of the array equals stateLen*numChannels.
} awe_modFIRInterpolatorInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modFIRInterpolatorClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modFIRInterpolatorConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modFIRInterpolatorProcess(void *pInstance);

UINT32 awe_modFIRInterpolatorSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_FIRINTERPOLATOR_H

/**
 * @}
 *
 * End of file.
 */
