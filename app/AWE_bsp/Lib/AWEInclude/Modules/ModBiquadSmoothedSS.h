/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBiquadSmoothedSS.h
****************************************************************************
*
*     Description:  2nd order smoothly updating IIR filter with State Space implementation
*
*     Copyright:    DSP Concepts, Inc, 2007 - 2015
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
 * @brief 2nd order smoothly updating IIR filter with State Space implementation
 */

#ifndef _MOD_BIQUADSMOOTHEDSS_H
#define _MOD_BIQUADSMOOTHEDSS_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_BiquadSmoothedSS_updateActive 0x00000100
#define MASK_BiquadSmoothedSS_smoothingTime 0x00000200
#define MASK_BiquadSmoothedSS_smoothingCoeff 0x00000400
#define MASK_BiquadSmoothedSS_coeffs 0x00000800
#define MASK_BiquadSmoothedSS_targetCoeffs 0x00001000
#define MASK_BiquadSmoothedSS_currentCoeffs 0x00002000
#define MASK_BiquadSmoothedSS_state 0x00004000
#define OFFSET_BiquadSmoothedSS_updateActive 0x00000008
#define OFFSET_BiquadSmoothedSS_smoothingTime 0x00000009
#define OFFSET_BiquadSmoothedSS_smoothingCoeff 0x0000000A
#define OFFSET_BiquadSmoothedSS_coeffs 0x0000000B
#define OFFSET_BiquadSmoothedSS_targetCoeffs 0x0000000C
#define OFFSET_BiquadSmoothedSS_currentCoeffs 0x0000000D
#define OFFSET_BiquadSmoothedSS_state 0x0000000E

#define CLASSID_BIQUADSMOOTHEDSS (CLASS_ID_MODBASE + 3205)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBiquadSmoothedSSInstance
{
    ModuleInstanceDescriptor instance;
    int                updateActive;        // Specifies whether the filter coefficients are updating (=1) or fixed (=0).
    float              smoothingTime;       // Time constant of the smoothing process.
    float              smoothingCoeff;      // Smoothing coefficient. This is computed based on the smoothingTime, sample rate, and block size of the module.
    float*             coeffs;              // Biquad filter coefficients arranged as [b0; b1; b2; a1; a2].
    float*             targetCoeffs;        // Array of filter target coefficients. The size of the array is 5 and contains the variables for a biquad arranged as [Fb; Gaa; Gab; K; Fa].
    float*             currentCoeffs;       // Array of filter current coefficients. The size of the array is 5 and contains the variables for a biquad arranged as [Fb; Gaa; Gab; K; Fa].
    float*             state;               // State variables. 2 per channel.
} awe_modBiquadSmoothedSSInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBiquadSmoothedSSClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modBiquadSmoothedSSConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modBiquadSmoothedSSProcess(void *pInstance);

UINT32 awe_modBiquadSmoothedSSSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BIQUADSMOOTHEDSS_H

/**
 * @}
 *
 * End of file.
 */
