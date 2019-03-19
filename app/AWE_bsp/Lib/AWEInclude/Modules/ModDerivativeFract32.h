/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDerivativeFract32.h
****************************************************************************
*
*     Description:  Fixed point Discrete-time derivative
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
 * @brief Fixed point Discrete-time derivative
 */

#ifndef _MOD_DERIVATIVEFRACT32_H
#define _MOD_DERIVATIVEFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DerivativeFract32_gain 0x00000100
#define MASK_DerivativeFract32_gainFract32 0x00000200
#define MASK_DerivativeFract32_lastValue 0x00000400
#define OFFSET_DerivativeFract32_gain 0x00000008
#define OFFSET_DerivativeFract32_gainFract32 0x00000009
#define OFFSET_DerivativeFract32_lastValue 0x0000000A

#define CLASSID_DERIVATIVEFRACT32 (CLASS_ID_MODBASE + 1258)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDerivativeFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            gain;                // Additional gain.
    fract32            gainFract32;         // Additional gain.
    fract32*           lastValue;           // Previous value x[n-1].
} awe_modDerivativeFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDerivativeFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modDerivativeFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modDerivativeFract32Process(void *pInstance);

UINT32 awe_modDerivativeFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DERIVATIVEFRACT32_H

/**
 * @}
 *
 * End of file.
 */
