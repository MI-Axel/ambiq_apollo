/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSbDerivative.h
****************************************************************************
*
*     Description:  Subband derivative
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
 * @brief Subband derivative
 */

#ifndef _MOD_SBDERIVATIVE_H
#define _MOD_SBDERIVATIVE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SbDerivative_gain 0x00000100
#define MASK_SbDerivative_lastValue 0x00000200
#define OFFSET_SbDerivative_gain 0x00000008
#define OFFSET_SbDerivative_lastValue 0x00000009

#define CLASSID_SBDERIVATIVE (CLASS_ID_MODBASE + 1324)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSbDerivativeInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            gain;                // Additional gain.
    FLOAT32*           lastValue;           // Previous value x[n-1].
} awe_modSbDerivativeInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSbDerivativeClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modSbDerivativeConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modSbDerivativeProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SBDERIVATIVE_H

/**
 * @}
 *
 * End of file.
 */
