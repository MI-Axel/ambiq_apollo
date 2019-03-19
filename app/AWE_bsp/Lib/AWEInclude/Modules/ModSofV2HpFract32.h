/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSofV2HpFract32.h
****************************************************************************
*
*     Description:  General 2nd order filter designer with smoothing
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
 * @brief General 2nd order filter designer with smoothing
 */

#ifndef _MOD_SOFV2HPFRACT32_H
#define _MOD_SOFV2HPFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SofV2HpFract32_filterType 0x00000100
#define MASK_SofV2HpFract32_freq 0x00000200
#define MASK_SofV2HpFract32_gain 0x00000400
#define MASK_SofV2HpFract32_Q 0x00000800
#define MASK_SofV2HpFract32_smoothingTime 0x00001000
#define MASK_SofV2HpFract32_updateActive 0x00002000
#define MASK_SofV2HpFract32_smoothingCoeff 0x00004000
#define MASK_SofV2HpFract32_bShift 0x00008000
#define MASK_SofV2HpFract32_aShift 0x00010000
#define MASK_SofV2HpFract32_targetCoeffs 0x00020000
#define MASK_SofV2HpFract32_currentCoeffs 0x00040000
#define MASK_SofV2HpFract32_state 0x00080000
#define OFFSET_SofV2HpFract32_filterType 0x00000008
#define OFFSET_SofV2HpFract32_freq 0x00000009
#define OFFSET_SofV2HpFract32_gain 0x0000000A
#define OFFSET_SofV2HpFract32_Q 0x0000000B
#define OFFSET_SofV2HpFract32_smoothingTime 0x0000000C
#define OFFSET_SofV2HpFract32_updateActive 0x0000000D
#define OFFSET_SofV2HpFract32_smoothingCoeff 0x0000000E
#define OFFSET_SofV2HpFract32_bShift 0x0000000F
#define OFFSET_SofV2HpFract32_aShift 0x00000010
#define OFFSET_SofV2HpFract32_targetCoeffs 0x00000011
#define OFFSET_SofV2HpFract32_currentCoeffs 0x00000012
#define OFFSET_SofV2HpFract32_state 0x00000013

#define CLASSID_SOFV2HPFRACT32 (CLASS_ID_MODBASE + 206)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSofV2HpFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              filterType;          // Selects the type of filter that is implemented by the module: Bypass=0, Gain=1, Butter1stLPF=2, Butter2ndLPF=3, Butter1stHPF=4, Butter2ndHPF=5, Allpass1st=6, Allpass2nd=7, Shelf2ndLow=8, Shelf2ndLowQ=9, Shelf2ndHigh=10, Shelf2ndHighQ=11, PeakEQ=12, Notch=13, Bandpass=14, Bessel1stLPF=15, Bessel1stHPF=16, AsymShelf1stLow=17, AsymShelf1stHigh=18, SymShelf1stLow=19, SymShelf1stHigh=20, VariableQLPF=21, VariableQHPF=22.
    FLOAT32            freq;                // Cutoff frequency of the filter
    FLOAT32            gain;                // Amount of boost or cut to apply, in decibels (if applicable)
    FLOAT32            Q;                   // Specifies the Q of the filter, if applicable
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    INT32              updateActive;        // Specifies whether the filter coefficients are updating (=1) or fixed (=0)
    fract32            smoothingCoeff;      // Smoothing coefficient.  This is computed based on the smoothingTime, sample rate, and block size of the module
    INT32              bShift;              // Number of bits to shift of Numerator coefficients
    INT32              aShift;              // Number of bits to shift of Denominator coefficients
    fract32*           targetCoeffs;        // Target coefficients in Fract32
    fract32*           currentCoeffs;       // Instantaneous coefficients in Fract32
    fract32*           state;               // State variables.  6 per channel.
} awe_modSofV2HpFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSofV2HpFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modSofV2HpFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modSofV2HpFract32Process(void *pInstance);

UINT32 awe_modSofV2HpFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SOFV2HPFRACT32_H

/**
 * @}
 *
 * End of file.
 */
