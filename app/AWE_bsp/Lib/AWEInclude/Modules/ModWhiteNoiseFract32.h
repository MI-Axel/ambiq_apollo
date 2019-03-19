/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModWhiteNoiseFract32.h
****************************************************************************
*
*     Description:  Uniformly distributed white noise generator
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
 * @brief Uniformly distributed white noise generator
 */

#ifndef _MOD_WHITENOISEFRACT32_H
#define _MOD_WHITENOISEFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModRand.h"
#include "ModScalerFract32.h"

#define MASK_WhiteNoiseFract32_range 0x00000100
#define OFFSET_WhiteNoiseFract32_range 0x00000008

#define CLASSID_WHITENOISEFRACT32 (CLASS_ID_MODBASE + 215)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modWhiteNoiseFract32Instance
{
    ModuleInstanceDescriptor instance;
    fract32            range;               // Generated noise will be in the interval [-range +range]
        awe_modRandInstance    *rand;               // Random number generator using a LCG algorithm
        awe_modScalerFract32Instance    *scale;              // Linear multichannel scaler
} awe_modWhiteNoiseFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modWhiteNoiseFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modWhiteNoiseFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modWhiteNoiseFract32Process(void *pInstance);

UINT32 awe_modWhiteNoiseFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_WHITENOISEFRACT32_H

/**
 * @}
 *
 * End of file.
 */
