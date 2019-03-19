/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModPolynomial.h
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

#ifndef _MOD_POLYNOMIAL_H
#define _MOD_POLYNOMIAL_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Polynomial_numCoeffs 0x00000100
#define MASK_Polynomial_coeffs 0x00000200
#define OFFSET_Polynomial_numCoeffs 0x00000008
#define OFFSET_Polynomial_coeffs 0x00000009

#define CLASSID_POLYNOMIAL (CLASS_ID_MODBASE + 79)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modPolynomialInstance
{
    ModuleInstanceDescriptor instance;
    INT32              numCoeffs;           // Number of coefficients in the polynomial.
    FLOAT32*           coeffs;              // Coefficient array in descending order. X^(N-1)*C[0] + X^(N-2)*C[1]+ ...
} awe_modPolynomialInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modPolynomialClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modPolynomialConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modPolynomialProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_POLYNOMIAL_H

/**
 * @}
 *
 * End of file.
 */
