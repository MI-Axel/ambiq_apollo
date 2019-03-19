/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBiquadCascadeHP.h
****************************************************************************
*
*     Description:  Cascade of second order Biquad filters with high precision implementation
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
 * @brief Cascade of second order Biquad filters with high precision implementation
 */

#ifndef _MOD_BIQUADCASCADEHP_H
#define _MOD_BIQUADCASCADEHP_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_BiquadCascadeHP_numStages 0x00000100
#define MASK_BiquadCascadeHP_coeffs 0x00000200
#define MASK_BiquadCascadeHP_targetCoeffs 0x00000400
#define MASK_BiquadCascadeHP_state 0x00000800
#define OFFSET_BiquadCascadeHP_numStages 0x00000008
#define OFFSET_BiquadCascadeHP_coeffs 0x00000009
#define OFFSET_BiquadCascadeHP_targetCoeffs 0x0000000A
#define OFFSET_BiquadCascadeHP_state 0x0000000B

#define CLASSID_BIQUADCASCADEHP (CLASS_ID_MODBASE + 1217)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBiquadCascadeHPInstance
{
    ModuleInstanceDescriptor instance;
    INT32              numStages;           // Number of stages in the filter. The filter order = 2*numStages.
    FLOAT32*           coeffs;              // Matrix of filter coefficients. The size of the matrix is 5 x numStages. Each column contains the variables for a biquad arranged as [b0; b1; b2; a1; a2].
    FLOAT32*           targetCoeffs;        // Matrix of filter coefficients in the High Precision format. The size of the matrix is 5 x numStages. Each column contains the variables for a biquad arranged as [Fb; Gaa; Gab; K; Fa].
    FLOAT32*           state;               // State variables. 2 per channel.
} awe_modBiquadCascadeHPInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBiquadCascadeHPClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modBiquadCascadeHPConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modBiquadCascadeHPProcess(void *pInstance);

UINT32 awe_modBiquadCascadeHPSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BIQUADCASCADEHP_H

/**
 * @}
 *
 * End of file.
 */
