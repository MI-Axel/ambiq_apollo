/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSOFSmoothedCascadeFract32.h
****************************************************************************
*
*     Description:  General 2nd order filter cascade designer with smoothing
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
 * @brief General 2nd order filter cascade designer with smoothing
 */

#ifndef _MOD_SOFSMOOTHEDCASCADEFRACT32_H
#define _MOD_SOFSMOOTHEDCASCADEFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SOFSmoothedCascadeFract32_numStages 0x00000100
#define MASK_SOFSmoothedCascadeFract32_smoothingTime 0x00000200
#define MASK_SOFSmoothedCascadeFract32_updateActive 0x00000400
#define MASK_SOFSmoothedCascadeFract32_smoothingCoeff 0x00000800
#define MASK_SOFSmoothedCascadeFract32_postShift 0x00001000
#define MASK_SOFSmoothedCascadeFract32_twoPowMinusPostShift 0x00002000
#define MASK_SOFSmoothedCascadeFract32_filterType 0x00004000
#define MASK_SOFSmoothedCascadeFract32_freq 0x00008000
#define MASK_SOFSmoothedCascadeFract32_gain 0x00010000
#define MASK_SOFSmoothedCascadeFract32_Q 0x00020000
#define MASK_SOFSmoothedCascadeFract32_coeffs 0x00040000
#define MASK_SOFSmoothedCascadeFract32_target_coeffsFract32 0x00080000
#define MASK_SOFSmoothedCascadeFract32_current_coeffsFract32 0x00100000
#define MASK_SOFSmoothedCascadeFract32_state 0x00200000
#define OFFSET_SOFSmoothedCascadeFract32_numStages 0x00000008
#define OFFSET_SOFSmoothedCascadeFract32_smoothingTime 0x00000009
#define OFFSET_SOFSmoothedCascadeFract32_updateActive 0x0000000A
#define OFFSET_SOFSmoothedCascadeFract32_smoothingCoeff 0x0000000B
#define OFFSET_SOFSmoothedCascadeFract32_postShift 0x0000000C
#define OFFSET_SOFSmoothedCascadeFract32_twoPowMinusPostShift 0x0000000D
#define OFFSET_SOFSmoothedCascadeFract32_filterType 0x0000000E
#define OFFSET_SOFSmoothedCascadeFract32_freq 0x0000000F
#define OFFSET_SOFSmoothedCascadeFract32_gain 0x00000010
#define OFFSET_SOFSmoothedCascadeFract32_Q 0x00000011
#define OFFSET_SOFSmoothedCascadeFract32_coeffs 0x00000012
#define OFFSET_SOFSmoothedCascadeFract32_target_coeffsFract32 0x00000013
#define OFFSET_SOFSmoothedCascadeFract32_current_coeffsFract32 0x00000014
#define OFFSET_SOFSmoothedCascadeFract32_state 0x00000015

#define CLASSID_SOFSMOOTHEDCASCADEFRACT32 (CLASS_ID_MODBASE + 192)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSOFSmoothedCascadeFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              numStages;           // Number of cascaded stages of the second order filter.
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    INT32              updateActive;        // Specifies whether the filter coefficients are updating (=1) or fixed (=0)
    fract32            smoothingCoeff;      // Smoothing coefficient.  This is computed based on the smoothingTime, sample rate, and block size of the module
    INT32              postShift;           // Number of bits to shift
    FLOAT32            twoPowMinusPostShift; // 2^(-postShift).  Used by to streamline the operation of the set function
    INT32*             filterType;          // Selects the type of filter that is implemented by the module: Bypass=0, Gain=1, Butter1stLPF=2, Butter2ndLPF=3, Butter1stHPF=4, Butter2ndHPF=5, Allpass1st=6, Allpass2nd=7, Shelf2ndLow=8, Shelf2ndLowQ=9, Shelf2ndHigh=10, Shelf2ndHighQ=11, PeakEQ=12, Notch=13, Bandpass=14, Bessel1stLPF=15, Bessel1stHPF=16, AsymShelf1stLow=17, AsymShelf1stHigh=18, SymShelf1stLow=19, SymShelf1stHigh=20, VariableQLPF=21, VariableQHPF=22.
    FLOAT32*           freq;                // Cutoff frequency of the filter
    FLOAT32*           gain;                // Amount of boost or cut to apply, in decibels (if applicable)
    FLOAT32*           Q;                   // Specifies the Q of the filter, if applicable
    FLOAT32*           coeffs;              // coefficients
    fract32*           target_coeffsFract32; // Matrix of filter coefficients.  The size of the matrix is 5 x numStages.  Each column contains the variables for a biquad arranged as [b0; b1; b2; a1; a2].
    fract32*           current_coeffsFract32; // Matrix of filter coefficients.  The size of the matrix is 5 x numStages.  Each column contains the variables for a biquad arranged as [b0; b1; b2; a1; a2].
    fract32*           state;               // State variables. 4 per channel per stage
} awe_modSOFSmoothedCascadeFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSOFSmoothedCascadeFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modSOFSmoothedCascadeFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modSOFSmoothedCascadeFract32Process(void *pInstance);

UINT32 awe_modSOFSmoothedCascadeFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SOFSMOOTHEDCASCADEFRACT32_H

/**
 * @}
 *
 * End of file.
 */
