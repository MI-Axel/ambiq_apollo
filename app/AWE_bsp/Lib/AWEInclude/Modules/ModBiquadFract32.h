/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBiquadFract32.h
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

#ifndef _MOD_BIQUADFRACT32_H
#define _MOD_BIQUADFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_BiquadFract32_updateActive 0x00000100
#define MASK_BiquadFract32_postShift 0x00000200
#define MASK_BiquadFract32_currentPostShift 0x00000400
#define MASK_BiquadFract32_coeffs 0x00000800
#define MASK_BiquadFract32_coeffsFract32 0x00001000
#define MASK_BiquadFract32_state 0x00002000
#define MASK_BiquadFract32_currentCoeffsFract32 0x00004000
#define OFFSET_BiquadFract32_updateActive 0x00000008
#define OFFSET_BiquadFract32_postShift 0x00000009
#define OFFSET_BiquadFract32_currentPostShift 0x0000000A
#define OFFSET_BiquadFract32_coeffs 0x0000000B
#define OFFSET_BiquadFract32_coeffsFract32 0x0000000C
#define OFFSET_BiquadFract32_state 0x0000000D
#define OFFSET_BiquadFract32_currentCoeffsFract32 0x0000000E

#define CLASSID_BIQUADFRACT32 (CLASS_ID_MODBASE + 133)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBiquadFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              updateActive;        // Specifies whether the filter coefficients are updating (=1) or fixed (=0).
    INT32              postShift;           // Number of bits to shift
    INT32              currentPostShift;    // Current post shift
    FLOAT32*           coeffs;              // coefficients
    fract32*           coeffsFract32;       // coefficients in Fract32
    fract32*           state;               // State variables.  4 per channel.
    fract32*           currentCoeffsFract32; // Current coefficients in Fract32
} awe_modBiquadFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBiquadFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modBiquadFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modBiquadFract32Process(void *pInstance);

UINT32 awe_modBiquadFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BIQUADFRACT32_H

/**
 * @}
 *
 * End of file.
 */
