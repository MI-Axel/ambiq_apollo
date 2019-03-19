/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBiquadV2Fract32.h
****************************************************************************
*
*     Description:  2nd order IIR filter
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
 * @brief 2nd order IIR filter
 */

#ifndef _MOD_BIQUADV2FRACT32_H
#define _MOD_BIQUADV2FRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_BiquadV2Fract32_precisionType 0x00000100
#define MASK_BiquadV2Fract32_updateActive 0x00000200
#define MASK_BiquadV2Fract32_postShift 0x00000400
#define MASK_BiquadV2Fract32_bShift 0x00000800
#define MASK_BiquadV2Fract32_currentBShift 0x00001000
#define MASK_BiquadV2Fract32_aShift 0x00002000
#define MASK_BiquadV2Fract32_currentAShift 0x00004000
#define MASK_BiquadV2Fract32_coeffs 0x00008000
#define MASK_BiquadV2Fract32_coeffsFract32 0x00010000
#define MASK_BiquadV2Fract32_state 0x00020000
#define MASK_BiquadV2Fract32_currentCoeffsFract32 0x00040000
#define OFFSET_BiquadV2Fract32_precisionType 0x00000008
#define OFFSET_BiquadV2Fract32_updateActive 0x00000009
#define OFFSET_BiquadV2Fract32_postShift 0x0000000A
#define OFFSET_BiquadV2Fract32_bShift 0x0000000B
#define OFFSET_BiquadV2Fract32_currentBShift 0x0000000C
#define OFFSET_BiquadV2Fract32_aShift 0x0000000D
#define OFFSET_BiquadV2Fract32_currentAShift 0x0000000E
#define OFFSET_BiquadV2Fract32_coeffs 0x0000000F
#define OFFSET_BiquadV2Fract32_coeffsFract32 0x00000010
#define OFFSET_BiquadV2Fract32_state 0x00000011
#define OFFSET_BiquadV2Fract32_currentCoeffsFract32 0x00000012

#define CLASSID_BIQUADV2FRACT32 (CLASS_ID_MODBASE + 137)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBiquadV2Fract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              precisionType;       // Boolean value that determines whether all channels are summed to form a single output.
    INT32              updateActive;        // Specifies whether the filter coefficients are updating (=1) or fixed (=0).
    INT32              postShift;           // Number of bits to shift
    INT32              bShift;              // Number of bits to shift of Numerator coefficients
    INT32              currentBShift;       // Current post shift of Numerator coefficients
    INT32              aShift;              // Number of bits to shift of Denominator coefficients
    INT32              currentAShift;       // Current post shift of Denominator coefficients
    FLOAT32*           coeffs;              // coefficients
    fract32*           coeffsFract32;       // coefficients in Fract32
    fract32*           state;               // State variables.  6 per channel.
    fract32*           currentCoeffsFract32; // Current coefficients in Fract32
} awe_modBiquadV2Fract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBiquadV2Fract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modBiquadV2Fract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modBiquadV2Fract32Process(void *pInstance);

UINT32 awe_modBiquadV2Fract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BIQUADV2FRACT32_H

/**
 * @}
 *
 * End of file.
 */
