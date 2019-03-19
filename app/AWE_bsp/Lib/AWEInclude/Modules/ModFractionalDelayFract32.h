/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModFractionalDelayFract32.h
****************************************************************************
*
*     Description:  provides fractional delay
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
 * @brief provides fractional delay
 */

#ifndef _MOD_FRACTIONALDELAYFRACT32_H
#define _MOD_FRACTIONALDELAYFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModDelay.h"
#include "ModFIRFract32.h"

#define MASK_FractionalDelayFract32_floatCurrentDelay 0x00000100
#define OFFSET_FractionalDelayFract32_floatCurrentDelay 0x00000008

#define CLASSID_FRACTIONALDELAYFRACT32 (CLASS_ID_MODBASE + 1283)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modFractionalDelayFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            floatCurrentDelay;   // total delay
        awe_modDelayInstance    *ConstantDelay;      // Time delay in which the delay is specified in samples
        awe_modFIRFract32Instance    *FIRmodule;          // FIR fract32 filter
} awe_modFractionalDelayFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modFractionalDelayFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modFractionalDelayFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modFractionalDelayFract32Process(void *pInstance);

UINT32 awe_modFractionalDelayFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_FRACTIONALDELAYFRACT32_H

/**
 * @}
 *
 * End of file.
 */
