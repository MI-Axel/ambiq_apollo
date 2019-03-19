/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModThreeBandToneControlFract32.h
****************************************************************************
*
*     Description:  Three band equalizer
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
 * @brief Three band equalizer
 */

#ifndef _MOD_THREEBANDTONECONTROLFRACT32_H
#define _MOD_THREEBANDTONECONTROLFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ThreeBandToneControlFract32_smoothingTime 0x00000100
#define MASK_ThreeBandToneControlFract32_lowFreq 0x00000200
#define MASK_ThreeBandToneControlFract32_midFreq 0x00000400
#define MASK_ThreeBandToneControlFract32_highFreq 0x00000800
#define MASK_ThreeBandToneControlFract32_lowGain 0x00001000
#define MASK_ThreeBandToneControlFract32_midGain 0x00002000
#define MASK_ThreeBandToneControlFract32_highGain 0x00004000
#define MASK_ThreeBandToneControlFract32_headRoomBits 0x00008000
#define MASK_ThreeBandToneControlFract32_postShift 0x00010000
#define MASK_ThreeBandToneControlFract32_twoPowMinusPostShift 0x00020000
#define MASK_ThreeBandToneControlFract32_filterUpdateActive 0x00040000
#define MASK_ThreeBandToneControlFract32_smoothingCoeff 0x00080000
#define MASK_ThreeBandToneControlFract32_midTargetGain 0x00100000
#define MASK_ThreeBandToneControlFract32_midCurrentGain 0x00200000
#define MASK_ThreeBandToneControlFract32_midSmoothingCoeff 0x00400000
#define MASK_ThreeBandToneControlFract32_lowerTargetCoeffs 0x00800000
#define MASK_ThreeBandToneControlFract32_lowerCurrentCoeffs 0x01000000
#define MASK_ThreeBandToneControlFract32_lowerState 0x02000000
#define MASK_ThreeBandToneControlFract32_upperTargetCoeffs 0x04000000
#define MASK_ThreeBandToneControlFract32_upperCurrentCoeffs 0x08000000
#define MASK_ThreeBandToneControlFract32_upperState 0x10000000
#define OFFSET_ThreeBandToneControlFract32_smoothingTime 0x00000008
#define OFFSET_ThreeBandToneControlFract32_lowFreq 0x00000009
#define OFFSET_ThreeBandToneControlFract32_midFreq 0x0000000A
#define OFFSET_ThreeBandToneControlFract32_highFreq 0x0000000B
#define OFFSET_ThreeBandToneControlFract32_lowGain 0x0000000C
#define OFFSET_ThreeBandToneControlFract32_midGain 0x0000000D
#define OFFSET_ThreeBandToneControlFract32_highGain 0x0000000E
#define OFFSET_ThreeBandToneControlFract32_headRoomBits 0x0000000F
#define OFFSET_ThreeBandToneControlFract32_postShift 0x00000010
#define OFFSET_ThreeBandToneControlFract32_twoPowMinusPostShift 0x00000011
#define OFFSET_ThreeBandToneControlFract32_filterUpdateActive 0x00000012
#define OFFSET_ThreeBandToneControlFract32_smoothingCoeff 0x00000013
#define OFFSET_ThreeBandToneControlFract32_midTargetGain 0x00000014
#define OFFSET_ThreeBandToneControlFract32_midCurrentGain 0x00000015
#define OFFSET_ThreeBandToneControlFract32_midSmoothingCoeff 0x00000016
#define OFFSET_ThreeBandToneControlFract32_lowerTargetCoeffs 0x00000017
#define OFFSET_ThreeBandToneControlFract32_lowerCurrentCoeffs 0x00000018
#define OFFSET_ThreeBandToneControlFract32_lowerState 0x00000019
#define OFFSET_ThreeBandToneControlFract32_upperTargetCoeffs 0x0000001A
#define OFFSET_ThreeBandToneControlFract32_upperCurrentCoeffs 0x0000001B
#define OFFSET_ThreeBandToneControlFract32_upperState 0x0000001C

#define CLASSID_THREEBANDTONECONTROLFRACT32 (CLASS_ID_MODBASE + 210)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modThreeBandToneControlFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    FLOAT32            lowFreq;             // Low band center frequency, in Hz
    FLOAT32            midFreq;             // Mid band center frequency, in Hz
    FLOAT32            highFreq;            // High band center frequency, in Hz
    FLOAT32            lowGain;             // Low band gain, in dB
    FLOAT32            midGain;             // Mid band gain, in dB
    FLOAT32            highGain;            // High band gain, in dB
    INT32              headRoomBits;        // Head room bits. This prevents internal clipping in the filter stages
    INT32              postShift;           // postShift controls the headroom within the fixed-point filtering
    FLOAT32            twoPowMinusPostShift; // Two power -postShift value
    INT32              filterUpdateActive;  // Boolean that is set when updating coefficients
    fract32            smoothingCoeff;      // Smoothing coefficient for the filter coefficients
    fract32            midTargetGain;       // Target gain of the mid frequency gain
    fract32            midCurrentGain;      // Current gain of the mid frequency gain
    fract32            midSmoothingCoeff;   // Sample-by-sample smoothing coefficient of the mid frequency gain
    fract32*           lowerTargetCoeffs;   // Target coefficients for the low frequency shelf
    fract32*           lowerCurrentCoeffs;  // Current coefficients for the low frequency shelf
    fract32*           lowerState;          // State variables for the low frequency shelf
    fract32*           upperTargetCoeffs;   // Target coefficients for the high frequency shelf
    fract32*           upperCurrentCoeffs;  // Current coefficients for the high frequency shelf
    fract32*           upperState;          // State variables for the high frequency shelf
} awe_modThreeBandToneControlFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modThreeBandToneControlFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modThreeBandToneControlFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modThreeBandToneControlFract32Process(void *pInstance);

UINT32 awe_modThreeBandToneControlFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_THREEBANDTONECONTROLFRACT32_H

/**
 * @}
 *
 * End of file.
 */
