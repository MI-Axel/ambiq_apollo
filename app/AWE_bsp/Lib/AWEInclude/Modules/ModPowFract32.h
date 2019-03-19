/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModPowFract32.h
****************************************************************************
*
*     Description:  Computes the funtion pow(x, y) using the math library.
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
 * @brief Computes the funtion pow(x, y) using the math library.
 */

#ifndef _MOD_POWFRACT32_H
#define _MOD_POWFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_PowFract32_postShift 0x00000100
#define MASK_PowFract32_log_output 0x00000200
#define MASK_PowFract32_mul_output 0x00000400
#define OFFSET_PowFract32_postShift 0x00000008
#define OFFSET_PowFract32_log_output 0x00000009
#define OFFSET_PowFract32_mul_output 0x0000000A

#define CLASSID_POWFRACT32 (CLASS_ID_MODBASE + 172)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modPowFract32Instance
{
    ModuleInstanceDescriptor instance;
    
    INT32*             postShift;           // Array of number of bits to shift after the fractional multiply.
    fract32*           log_output;          // log10 output array.
    fract32*           mul_output;          // multiplication output array.
} awe_modPowFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modPowFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modPowFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modPowFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_POWFRACT32_H

/**
 * @}
 *
 * End of file.
 */
