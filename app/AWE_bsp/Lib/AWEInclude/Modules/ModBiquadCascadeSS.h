/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBiquadCascadeSS.h
****************************************************************************
*
*     Description:  Cascade of second order Biquad filters with State space implementation
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
 * @brief Cascade of second order Biquad filters with State space implementation
 */

#ifndef _MOD_BIQUADCASCADESS_H
#define _MOD_BIQUADCASCADESS_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_BiquadCascadeSS_numStages 0x00000100
#define MASK_BiquadCascadeSS_coeffs 0x00000200
#define MASK_BiquadCascadeSS_targetCoeffs 0x00000400
#define MASK_BiquadCascadeSS_state 0x00000800
#define OFFSET_BiquadCascadeSS_numStages 0x00000008
#define OFFSET_BiquadCascadeSS_coeffs 0x00000009
#define OFFSET_BiquadCascadeSS_targetCoeffs 0x0000000A
#define OFFSET_BiquadCascadeSS_state 0x0000000B

#define CLASSID_BIQUADCASCADESS (CLASS_ID_MODBASE + 3203)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBiquadCascadeSSInstance
{
    ModuleInstanceDescriptor instance;
    int                numStages;           // Number of stages in the filter. The filter order = 2*numStages.
    float*             coeffs;              // Matrix of filter coefficients. The size of the matrix is 5 x numStages. Each column contains the variables for a biquad arranged as [b0; b1; b2; a1; a2].
    float*             targetCoeffs;        // Matrix of filter coefficients in the State Space format. The size of the matrix is 5 x numStages. Each column contains the variables for a biquad arranged as [Fb; Gaa; Gab; K; Fa].
    float*             state;               // State variables. 2 per channel.
} awe_modBiquadCascadeSSInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBiquadCascadeSSClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modBiquadCascadeSSConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modBiquadCascadeSSProcess(void *pInstance);

UINT32 awe_modBiquadCascadeSSSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BIQUADCASCADESS_H

/**
 * @}
 *
 * End of file.
 */
