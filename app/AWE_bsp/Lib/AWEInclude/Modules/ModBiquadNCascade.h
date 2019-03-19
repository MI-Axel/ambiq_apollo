/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBiquadNCascade.h
****************************************************************************
*
*     Description:  Cascade of second order Biquad filters with different coefficients for each channel
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
 * @brief Cascade of second order Biquad filters with different coefficients for each channel
 */

#ifndef _MOD_BIQUADNCASCADE_H
#define _MOD_BIQUADNCASCADE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_BiquadNCascade_numStages 0x00000100
#define MASK_BiquadNCascade_coeffs 0x00000200
#define MASK_BiquadNCascade_state 0x00000400
#define OFFSET_BiquadNCascade_numStages 0x00000008
#define OFFSET_BiquadNCascade_coeffs 0x00000009
#define OFFSET_BiquadNCascade_state 0x0000000A

#define CLASSID_BIQUADNCASCADE (CLASS_ID_MODBASE + 12)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBiquadNCascadeInstance
{
    ModuleInstanceDescriptor instance;
    INT32              numStages;           // Number of stages in the filter. The filter order = 2*numStages.
    FLOAT32*           coeffs;              // Matrix of filter coefficients. The size of the matrix is (5*numStages) x numChannels. Each column contains the variables for a biquad arranged as [b0; b1; b2; a1; a2].
    FLOAT32*           state;               // State variables. 2 per channel.
} awe_modBiquadNCascadeInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBiquadNCascadeClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modBiquadNCascadeConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modBiquadNCascadeProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BIQUADNCASCADE_H

/**
 * @}
 *
 * End of file.
 */
