/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSlewRateLimiter.h
****************************************************************************
*
*     Description:  Slew rate limiter
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
 * @brief Slew rate limiter
 */

#ifndef _MOD_SLEWRATELIMITER_H
#define _MOD_SLEWRATELIMITER_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SlewRateLimiter_units 0x00000100
#define MASK_SlewRateLimiter_minSlew 0x00000200
#define MASK_SlewRateLimiter_maxSlew 0x00000400
#define MASK_SlewRateLimiter_reset 0x00000800
#define MASK_SlewRateLimiter_minSlewSample 0x00001000
#define MASK_SlewRateLimiter_maxSlewSample 0x00002000
#define MASK_SlewRateLimiter_state 0x00004000
#define OFFSET_SlewRateLimiter_units 0x00000008
#define OFFSET_SlewRateLimiter_minSlew 0x00000009
#define OFFSET_SlewRateLimiter_maxSlew 0x0000000A
#define OFFSET_SlewRateLimiter_reset 0x0000000B
#define OFFSET_SlewRateLimiter_minSlewSample 0x0000000C
#define OFFSET_SlewRateLimiter_maxSlewSample 0x0000000D
#define OFFSET_SlewRateLimiter_state 0x0000000E

#define CLASSID_SLEWRATELIMITER (CLASS_ID_MODBASE + 1335)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSlewRateLimiterInstance
{
    ModuleInstanceDescriptor instance;
    INT32              units;               // Specifies the units for the minSlew and maxSlew variables (0=sample, 1=msec, 2=sec)
    FLOAT32            minSlew;             // Minimum allowed slew rate
    FLOAT32            maxSlew;             // Maximum allowed slew rate
    INT32              reset;               // Forces the output to equal the input
    FLOAT32            minSlewSample;       // Minimum allowed slew rate per sample
    FLOAT32            maxSlewSample;       // Maximum allowed slew rate per sample
    FLOAT32*           state;               // State variables.  One per channel
} awe_modSlewRateLimiterInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSlewRateLimiterClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modSlewRateLimiterConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modSlewRateLimiterProcess(void *pInstance);

UINT32 awe_modSlewRateLimiterSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SLEWRATELIMITER_H

/**
 * @}
 *
 * End of file.
 */
