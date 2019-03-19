/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModThreeBandToneControl.h
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

#ifndef _MOD_THREEBANDTONECONTROL_H
#define _MOD_THREEBANDTONECONTROL_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ThreeBandToneControl_smoothingTime 0x00000100
#define MASK_ThreeBandToneControl_lowFreq 0x00000200
#define MASK_ThreeBandToneControl_midFreq 0x00000400
#define MASK_ThreeBandToneControl_highFreq 0x00000800
#define MASK_ThreeBandToneControl_lowGain 0x00001000
#define MASK_ThreeBandToneControl_midGain 0x00002000
#define MASK_ThreeBandToneControl_highGain 0x00004000
#define MASK_ThreeBandToneControl_filterUpdateActive 0x00008000
#define MASK_ThreeBandToneControl_smoothingCoeff 0x00010000
#define MASK_ThreeBandToneControl_midTargetGain 0x00020000
#define MASK_ThreeBandToneControl_midCurrentGain 0x00040000
#define MASK_ThreeBandToneControl_midSmoothingCoeff 0x00080000
#define MASK_ThreeBandToneControl_lowerTargetCoeffs 0x00100000
#define MASK_ThreeBandToneControl_lowerCurrentCoeffs 0x00200000
#define MASK_ThreeBandToneControl_lowerState 0x00400000
#define MASK_ThreeBandToneControl_upperTargetCoeffs 0x00800000
#define MASK_ThreeBandToneControl_upperCurrentCoeffs 0x01000000
#define MASK_ThreeBandToneControl_upperState 0x02000000
#define OFFSET_ThreeBandToneControl_smoothingTime 0x00000008
#define OFFSET_ThreeBandToneControl_lowFreq 0x00000009
#define OFFSET_ThreeBandToneControl_midFreq 0x0000000A
#define OFFSET_ThreeBandToneControl_highFreq 0x0000000B
#define OFFSET_ThreeBandToneControl_lowGain 0x0000000C
#define OFFSET_ThreeBandToneControl_midGain 0x0000000D
#define OFFSET_ThreeBandToneControl_highGain 0x0000000E
#define OFFSET_ThreeBandToneControl_filterUpdateActive 0x0000000F
#define OFFSET_ThreeBandToneControl_smoothingCoeff 0x00000010
#define OFFSET_ThreeBandToneControl_midTargetGain 0x00000011
#define OFFSET_ThreeBandToneControl_midCurrentGain 0x00000012
#define OFFSET_ThreeBandToneControl_midSmoothingCoeff 0x00000013
#define OFFSET_ThreeBandToneControl_lowerTargetCoeffs 0x00000014
#define OFFSET_ThreeBandToneControl_lowerCurrentCoeffs 0x00000015
#define OFFSET_ThreeBandToneControl_lowerState 0x00000016
#define OFFSET_ThreeBandToneControl_upperTargetCoeffs 0x00000017
#define OFFSET_ThreeBandToneControl_upperCurrentCoeffs 0x00000018
#define OFFSET_ThreeBandToneControl_upperState 0x00000019

#define CLASSID_THREEBANDTONECONTROL (CLASS_ID_MODBASE + 9)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modThreeBandToneControlInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process.
    FLOAT32            lowFreq;             // Low band center frequency, in Hz.
    FLOAT32            midFreq;             // Mid band center frequency, in Hz.
    FLOAT32            highFreq;            // High band center frequency, in Hz.
    FLOAT32            lowGain;             // Low band gain, in dB.
    FLOAT32            midGain;             // Mid band gain, in dB.
    FLOAT32            highGain;            // High band gain, in dB.
    INT32              filterUpdateActive;  // Boolean that is set when updating coefficients.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient for the filter coefficients.
    FLOAT32            midTargetGain;       // Target gain of the mid frequency gain.
    FLOAT32            midCurrentGain;      // Current gain of the mid frequency gain.
    FLOAT32            midSmoothingCoeff;   // Sample-by-sample smoothing coefficient of the mid frequency gain.
    FLOAT32*           lowerTargetCoeffs;   // Target coefficients for the low frequency shelf.
    FLOAT32*           lowerCurrentCoeffs;  // Current coefficients for the low frequency shelf.
    FLOAT32*           lowerState;          // State variables for the low frequency shelf.
    FLOAT32*           upperTargetCoeffs;   // Target coefficients for the high frequency shelf.
    FLOAT32*           upperCurrentCoeffs;  // Current coefficients for the high frequency shelf.
    FLOAT32*           upperState;          // State variables for the high frequency shelf.
} awe_modThreeBandToneControlInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modThreeBandToneControlClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modThreeBandToneControlConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modThreeBandToneControlProcess(void *pInstance);

UINT32 awe_modThreeBandToneControlSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_THREEBANDTONECONTROL_H

/**
 * @}
 *
 * End of file.
 */
