/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBiquadCascadeFract32.h
****************************************************************************
*
*     Description:  Cascade of second order Biquad filters
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
 * @brief Cascade of second order Biquad filters
 */

#ifndef _MOD_BIQUADCASCADEFRACT32_H
#define _MOD_BIQUADCASCADEFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_BiquadCascadeFract32_numStages 0x00000100
#define MASK_BiquadCascadeFract32_coeffs 0x00000200
#define MASK_BiquadCascadeFract32_coeffsFract32 0x00000400
#define MASK_BiquadCascadeFract32_state 0x00000800
#define MASK_BiquadCascadeFract32_postShift 0x00001000
#define OFFSET_BiquadCascadeFract32_numStages 0x00000008
#define OFFSET_BiquadCascadeFract32_coeffs 0x00000009
#define OFFSET_BiquadCascadeFract32_coeffsFract32 0x0000000A
#define OFFSET_BiquadCascadeFract32_state 0x0000000B
#define OFFSET_BiquadCascadeFract32_postShift 0x0000000C

#define CLASSID_BIQUADCASCADEFRACT32 (CLASS_ID_MODBASE + 132)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBiquadCascadeFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              numStages;           // Number of stages in the filter.  The filter order = 2 * numStages
    FLOAT32*           coeffs;              // Matrix of filter coefficients.  The size of the matrix is 5 x numStages.  Each column contains the variables for a biquad arranged as [b0; b1; b2; a1; a2].
    fract32*           coeffsFract32;       // Matrix of filter coefficients.  The size of the matrix is 5 x numStages.  Each column contains the variables for a biquad arranged as [b0; b1; b2; a1; a2].
    fract32*           state;               // State variables.  4 per channel.
    INT32*             postShift;           // Number of bits to shift
} awe_modBiquadCascadeFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBiquadCascadeFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modBiquadCascadeFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modBiquadCascadeFract32Process(void *pInstance);

UINT32 awe_modBiquadCascadeFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BIQUADCASCADEFRACT32_H

/**
 * @}
 *
 * End of file.
 */
