/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSecondOrderFilter40SmoothedCascade.h
****************************************************************************
*
*     Description:  Cascade of 40-bit second order filters realized as a single module
*
*     Copyright:	   DSP Concepts, Inc., 2007 - 2015
*                   1800 Wyatt Drive, Suite 14
*                   Sunnyvale, CA 95054
*
***************************************************************************/

/**
 * @addtogroup Modules
 * @{
 */

/**
 * @file
 * @brief Cascade of 40-bit second order filters realized as a single module
 */

#ifndef _MOD_SECONDORDERFILTER40SMOOTHEDCASCADE_H
#define _MOD_SECONDORDERFILTER40SMOOTHEDCASCADE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SecondOrderFilter40SmoothedCascade_numStages 0x00000100
#define MASK_SecondOrderFilter40SmoothedCascade_smoothingTime 0x00000200
#define MASK_SecondOrderFilter40SmoothedCascade_updateActive 0x00000400
#define MASK_SecondOrderFilter40SmoothedCascade_smoothingCoeff 0x00000800
#define MASK_SecondOrderFilter40SmoothedCascade_filterType 0x00001000
#define MASK_SecondOrderFilter40SmoothedCascade_freq 0x00002000
#define MASK_SecondOrderFilter40SmoothedCascade_gain 0x00004000
#define MASK_SecondOrderFilter40SmoothedCascade_Q 0x00008000
#define MASK_SecondOrderFilter40SmoothedCascade_targetCoeffs 0x00010000
#define MASK_SecondOrderFilter40SmoothedCascade_currentCoeffs 0x00020000
#define MASK_SecondOrderFilter40SmoothedCascade_state 0x00040000
#define OFFSET_SecondOrderFilter40SmoothedCascade_numStages 0x00000008
#define OFFSET_SecondOrderFilter40SmoothedCascade_smoothingTime 0x00000009
#define OFFSET_SecondOrderFilter40SmoothedCascade_updateActive 0x0000000A
#define OFFSET_SecondOrderFilter40SmoothedCascade_smoothingCoeff 0x0000000B
#define OFFSET_SecondOrderFilter40SmoothedCascade_filterType 0x0000000C
#define OFFSET_SecondOrderFilter40SmoothedCascade_freq 0x0000000D
#define OFFSET_SecondOrderFilter40SmoothedCascade_gain 0x0000000E
#define OFFSET_SecondOrderFilter40SmoothedCascade_Q 0x0000000F
#define OFFSET_SecondOrderFilter40SmoothedCascade_targetCoeffs 0x00000010
#define OFFSET_SecondOrderFilter40SmoothedCascade_currentCoeffs 0x00000011
#define OFFSET_SecondOrderFilter40SmoothedCascade_state 0x00000012

#define CLASSID_SECONDORDERFILTER40SMOOTHEDCASCADE (CLASS_ID_MODBASE + 5314)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSecondOrderFilter40SmoothedCascadeInstance
{
    ModuleInstanceDescriptor instance;
    int                numStages;           // Number of cascaded stages of the second order filter.
    float              smoothingTime;       // Time constant of the smoothing process
    int                updateActive;        // Specifies whether the filter coefficients are updating (=1) or fixed (=0)
    float              smoothingCoeff;      // Smoothing coefficient.  This is computed based on the smoothingTime, sample rate, and block size of the module
    int*               filterType;          // Selects the type of filter that is implemented by the module: Bypass=0 Gain=1 Butter1stLPF=2 Butter2ndLPF=3 Butter1stHPF=4 Butter2ndHPF=5 Allpass1st=6 Allpass2nd=7 Shelf2ndLow=8 Shelf2ndLowQ=9 Shelf2ndHigh=10 Shelf2ndHighQ=11 PeakEQ=12 Notch=13 Bandpass=14 Bessel1stLPF=15 Bessel1stHPF=16 AsymShelf1stLow=17 AsymShelf1stHigh=18 SymShelf1stLow=19 SymShelf1stHigh=20
    float*             freq;                // Cutoff frequency of the filter
    float*             gain;                // Amount of boost or cut to apply, in decibels (if applicable)
    float*             Q;                   // Specifies the Q of the filter, if applicable
    float*             targetCoeffs;        // Matrix of filter coefficients.  The size of the matrix is 5 x numStages.  Each column contains the variables for a biquad arranged as [b0; b1; b2; a1; a2].
    float*             currentCoeffs;       // Matrix of filter coefficients.  The size of the matrix is 5 x numStages.  Each column contains the variables for a biquad arranged as [b0; b1; b2; a1; a2].
    float*             state;               // State variables.  2*numChannels per section.
} awe_modSecondOrderFilter40SmoothedCascadeInstance;

/* By default the class object is included and this is required for dynamic
 * instantiation.  When doing static code (define AWE_STATIC_CODE) you can save
 * a little bit of memory by eliminating class objects.  However, you lose the
 * ability to change the module status. */

#if (!defined(AWE_NO_CLASS_OBJECTS) || !defined(AWE_STATIC_CODE))
extern const ModClassModule awe_modSecondOrderFilter40SmoothedCascadeClass;
#endif // #ifndef AWE_NO_CLASS_OBJECTS

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modSecondOrderFilter40SmoothedCascadeConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modSecondOrderFilter40SmoothedCascadeProcess(void *pInstance);

UINT32 awe_modSecondOrderFilter40SmoothedCascadeSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SECONDORDERFILTER40SMOOTHEDCASCADE_H

/**
 * @}
 *
 * End of file.
 */
