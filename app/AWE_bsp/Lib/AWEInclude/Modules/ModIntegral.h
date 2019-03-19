/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModIntegral.h
****************************************************************************
*
*     Description:  Discrete-time running-sum integral
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
 * @brief Discrete-time running-sum integral
 */

#ifndef _MOD_INTEGRAL_H
#define _MOD_INTEGRAL_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Integral_gain 0x00000100
#define MASK_Integral_cumSum 0x00000200
#define OFFSET_Integral_gain 0x00000008
#define OFFSET_Integral_cumSum 0x00000009

#define CLASSID_INTEGRAL (CLASS_ID_MODBASE + 1290)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modIntegralInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            gain;                // Additional gain.
    FLOAT32*           cumSum;              // Running sum of input samples since last reset.
} awe_modIntegralInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modIntegralClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modIntegralConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modIntegralProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_INTEGRAL_H

/**
 * @}
 *
 * End of file.
 */
