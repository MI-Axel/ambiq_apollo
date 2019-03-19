/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBiquadSmoothedFract32.h
****************************************************************************
*
*     Description:  2nd order smoothly updating IIR filter
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
 * @brief 2nd order smoothly updating IIR filter
 */

#ifndef _MOD_BIQUADSMOOTHEDFRACT32_H
#define _MOD_BIQUADSMOOTHEDFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_BiquadSmoothedFract32_updateActive 0x00000100
#define MASK_BiquadSmoothedFract32_smoothingTime 0x00000200
#define MASK_BiquadSmoothedFract32_smoothingCoeff 0x00000400
#define MASK_BiquadSmoothedFract32_postShift 0x00000800
#define MASK_BiquadSmoothedFract32_currentPostShift 0x00001000
#define MASK_BiquadSmoothedFract32_coeffs 0x00002000
#define MASK_BiquadSmoothedFract32_coeffsFract32 0x00004000
#define MASK_BiquadSmoothedFract32_current_coeffsFract32 0x00008000
#define MASK_BiquadSmoothedFract32_state 0x00010000
#define OFFSET_BiquadSmoothedFract32_updateActive 0x00000008
#define OFFSET_BiquadSmoothedFract32_smoothingTime 0x00000009
#define OFFSET_BiquadSmoothedFract32_smoothingCoeff 0x0000000A
#define OFFSET_BiquadSmoothedFract32_postShift 0x0000000B
#define OFFSET_BiquadSmoothedFract32_currentPostShift 0x0000000C
#define OFFSET_BiquadSmoothedFract32_coeffs 0x0000000D
#define OFFSET_BiquadSmoothedFract32_coeffsFract32 0x0000000E
#define OFFSET_BiquadSmoothedFract32_current_coeffsFract32 0x0000000F
#define OFFSET_BiquadSmoothedFract32_state 0x00000010

#define CLASSID_BIQUADSMOOTHEDFRACT32 (CLASS_ID_MODBASE + 134)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBiquadSmoothedFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              updateActive;        // Specifies whether the filter coefficients are updating (=1) or fixed (=0)
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    fract32            smoothingCoeff;      // Smoothing coefficient.  This is computed based on the smoothingTime, sample rate, and block size of the module
    INT32              postShift;           // Number of bits to shift
    INT32              currentPostShift;    // Current post shift
    FLOAT32*           coeffs;              // Desired coefficients
    fract32*           coeffsFract32;       // Desired coefficients in fract32
    fract32*           current_coeffsFract32; // Instantaneous coefficients
    fract32*           state;               // State variables.  4 per channel.
} awe_modBiquadSmoothedFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBiquadSmoothedFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modBiquadSmoothedFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modBiquadSmoothedFract32Process(void *pInstance);

UINT32 awe_modBiquadSmoothedFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BIQUADSMOOTHEDFRACT32_H

/**
 * @}
 *
 * End of file.
 */
