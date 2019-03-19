/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModPolynomialFract32.h
****************************************************************************
*
*     Description:  Sample-by-sample polynomial nonlinearity
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
 * @brief Sample-by-sample polynomial nonlinearity
 */

#ifndef _MOD_POLYNOMIALFRACT32_H
#define _MOD_POLYNOMIALFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_PolynomialFract32_numCoeffs 0x00000100
#define MASK_PolynomialFract32_postShift 0x00000200
#define MASK_PolynomialFract32_coeffs 0x00000400
#define MASK_PolynomialFract32_coeffsFract32 0x00000800
#define OFFSET_PolynomialFract32_numCoeffs 0x00000008
#define OFFSET_PolynomialFract32_postShift 0x00000009
#define OFFSET_PolynomialFract32_coeffs 0x0000000A
#define OFFSET_PolynomialFract32_coeffsFract32 0x0000000B

#define CLASSID_POLYNOMIALFRACT32 (CLASS_ID_MODBASE + 168)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modPolynomialFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              numCoeffs;           // Number of coefficients in the polynomial
    INT32              postShift;           // Number of bits to shift
    FLOAT32*           coeffs;              // Coefficient array in descending order. X^(N-1)*C[0] + X^(N-2)*C[1]+ ...
    fract32*           coeffsFract32;       // Coefficient array in descending order. X^(N-1)*C[0] + X^(N-2)*C[1]+ ...
} awe_modPolynomialFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modPolynomialFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modPolynomialFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modPolynomialFract32Process(void *pInstance);

UINT32 awe_modPolynomialFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_POLYNOMIALFRACT32_H

/**
 * @}
 *
 * End of file.
 */
