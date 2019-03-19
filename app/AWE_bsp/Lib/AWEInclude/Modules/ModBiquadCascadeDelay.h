/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBiquadCascadeDelay.h
****************************************************************************
*
*     Description:  Cascade of 4 second order Biquad filters with additional delay
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
 * @brief Cascade of 4 second order Biquad filters with additional delay
 */

#ifndef _MOD_BIQUADCASCADEDELAY_H
#define _MOD_BIQUADCASCADEDELAY_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_BiquadCascadeDelay_numStages 0x00000100
#define MASK_BiquadCascadeDelay_coeffs 0x00000200
#define MASK_BiquadCascadeDelay_state 0x00000400
#define OFFSET_BiquadCascadeDelay_numStages 0x00000008
#define OFFSET_BiquadCascadeDelay_coeffs 0x00000009
#define OFFSET_BiquadCascadeDelay_state 0x0000000A

#define CLASSID_BIQUADCASCADEDELAY (CLASS_ID_MODBASE + 3300)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBiquadCascadeDelayInstance
{
    ModuleInstanceDescriptor instance;
    int                numStages;           // Number of stages in the filter. The filter order = 8*numStages.
    float*             coeffs;              // Matrix of filter coefficients. The size of the matrix is 20 x numStages.
    float*             state;               // State variables. 13 per channel.
} awe_modBiquadCascadeDelayInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBiquadCascadeDelayClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modBiquadCascadeDelayConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modBiquadCascadeDelayProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BIQUADCASCADEDELAY_H

/**
 * @}
 *
 * End of file.
 */
