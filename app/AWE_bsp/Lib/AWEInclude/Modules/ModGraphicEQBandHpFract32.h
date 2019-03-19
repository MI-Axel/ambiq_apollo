/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModGraphicEQBandHpFract32.h
****************************************************************************
*
*     Description:  Single band of a cascade graphic equalizer with High Precision Biquad fract32 algorithm
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
 * @brief Single band of a cascade graphic equalizer with High Precision Biquad fract32 algorithm
 */

#ifndef _MOD_GRAPHICEQBANDHPFRACT32_H
#define _MOD_GRAPHICEQBANDHPFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_GraphicEQBandHpFract32_gain 0x00000100
#define MASK_GraphicEQBandHpFract32_lowerEdge 0x00000200
#define MASK_GraphicEQBandHpFract32_upperEdge 0x00000400
#define MASK_GraphicEQBandHpFract32_smoothingTime 0x00000800
#define MASK_GraphicEQBandHpFract32_numStages 0x00001000
#define MASK_GraphicEQBandHpFract32_updateActive 0x00002000
#define MASK_GraphicEQBandHpFract32_bShift 0x00004000
#define MASK_GraphicEQBandHpFract32_aShift 0x00008000
#define MASK_GraphicEQBandHpFract32_smoothingCoeff 0x00010000
#define MASK_GraphicEQBandHpFract32_coeffs 0x00020000
#define MASK_GraphicEQBandHpFract32_coeffsFract32 0x00040000
#define MASK_GraphicEQBandHpFract32_currentCoeffsFract32 0x00080000
#define MASK_GraphicEQBandHpFract32_state 0x00100000
#define OFFSET_GraphicEQBandHpFract32_gain 0x00000008
#define OFFSET_GraphicEQBandHpFract32_lowerEdge 0x00000009
#define OFFSET_GraphicEQBandHpFract32_upperEdge 0x0000000A
#define OFFSET_GraphicEQBandHpFract32_smoothingTime 0x0000000B
#define OFFSET_GraphicEQBandHpFract32_numStages 0x0000000C
#define OFFSET_GraphicEQBandHpFract32_updateActive 0x0000000D
#define OFFSET_GraphicEQBandHpFract32_bShift 0x0000000E
#define OFFSET_GraphicEQBandHpFract32_aShift 0x0000000F
#define OFFSET_GraphicEQBandHpFract32_smoothingCoeff 0x00000010
#define OFFSET_GraphicEQBandHpFract32_coeffs 0x00000011
#define OFFSET_GraphicEQBandHpFract32_coeffsFract32 0x00000012
#define OFFSET_GraphicEQBandHpFract32_currentCoeffsFract32 0x00000013
#define OFFSET_GraphicEQBandHpFract32_state 0x00000014

#define CLASSID_GRAPHICEQBANDHPFRACT32 (CLASS_ID_MODBASE + 1284)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modGraphicEQBandHpFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            gain;                // Gain in the center of the band, in dB
    FLOAT32            lowerEdge;           // Lower frequency edge of the band, in Hz
    FLOAT32            upperEdge;           // Upper frequency edge of the band, in Hz
    FLOAT32            smoothingTime;       // Time constant of the smoothing process.
    INT32              numStages;           // Number of 2nd order stages in the filter
    INT32              updateActive;        // Specifies whether the filter coefficients are updating (=1) or fixed (=0).
    INT32              bShift;              // Number of bits to shift of Numerator coefficients
    INT32              aShift;              // Number of bits to shift of Denominator coefficients
    fract32            smoothingCoeff;      // Smoothing coefficient
    FLOAT32*           coeffs;              // Matrix of filter coefficients.  The size of the matrix is 5 x numStages.  Each column contains the variables for a biquad arranged as [b0; b1; b2; a1; a2].
    fract32*           coeffsFract32;       // Matrix of filter coefficients.  The size of the matrix is 5 x numStages.  Each column contains the variables for a biquad arranged as [b0; b1; b2; a1; a2].
    fract32*           currentCoeffsFract32; // Matrix of filter coefficients.  The size of the matrix is 5 x numStages.  Each column contains the variables for a biquad arranged as [b0; b1; b2; a1; a2].
    fract32*           state;               // State variables.  6 per channel.
} awe_modGraphicEQBandHpFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modGraphicEQBandHpFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modGraphicEQBandHpFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modGraphicEQBandHpFract32Process(void *pInstance);

UINT32 awe_modGraphicEQBandHpFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_GRAPHICEQBANDHPFRACT32_H

/**
 * @}
 *
 * End of file.
 */
