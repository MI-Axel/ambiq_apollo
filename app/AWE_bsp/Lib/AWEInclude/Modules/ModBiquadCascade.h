/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBiquadCascade.h
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

#ifndef _MOD_BIQUADCASCADE_H
#define _MOD_BIQUADCASCADE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_BiquadCascade_numStages 0x00000100
#define MASK_BiquadCascade_coeffs 0x00000200
#define MASK_BiquadCascade_state 0x00000400
#define OFFSET_BiquadCascade_numStages 0x00000008
#define OFFSET_BiquadCascade_coeffs 0x00000009
#define OFFSET_BiquadCascade_state 0x0000000A

#define CLASSID_BIQUADCASCADE (CLASS_ID_MODBASE + 11)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBiquadCascadeInstance
{
    ModuleInstanceDescriptor instance;
    INT32              numStages;           // Number of stages in the filter. The filter order = 2*numStages.
    FLOAT32*           coeffs;              // Matrix of filter coefficients. The size of the matrix is 5 x numStages. Each column contains the variables for a biquad arranged as [b0; b1; b2; a1; a2].
    FLOAT32*           state;               // State variables. 2 per channel.
} awe_modBiquadCascadeInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBiquadCascadeClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modBiquadCascadeConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modBiquadCascadeProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BIQUADCASCADE_H

/**
 * @}
 *
 * End of file.
 */
