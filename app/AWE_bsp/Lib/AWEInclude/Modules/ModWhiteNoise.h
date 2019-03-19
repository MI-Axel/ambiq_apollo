/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModWhiteNoise.h
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

#ifndef _MOD_WHITENOISE_H
#define _MOD_WHITENOISE_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModRand.h"
#include "ModScalerV2.h"
#include "ModTypeConversion.h"

#define MASK_WhiteNoise_range 0x00000100
#define OFFSET_WhiteNoise_range 0x00000008

#define CLASSID_WHITENOISE (CLASS_ID_MODBASE + 124)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modWhiteNoiseInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            range;               // Generated noise will be in the interval [-range +range].
        awe_modRandInstance    *rand;               // Random number generator using a LCG algorithm
        awe_modTypeConversionInstance    *int2flt;            // Converts between numeric data types
        awe_modScalerV2Instance    *scale;              // General purpose scaler with a single gain
} awe_modWhiteNoiseInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modWhiteNoiseClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modWhiteNoiseConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modWhiteNoiseProcess(void *pInstance);

UINT32 awe_modWhiteNoiseSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_WHITENOISE_H

/**
 * @}
 *
 * End of file.
 */
