/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModTableInterpFract32.h
****************************************************************************
*
*     Description:  Fract32 Table driven interpolation module.  Supports linear and spline modes
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
 * @brief Fract32 Table driven interpolation module.  Supports linear and spline modes
 */

#ifndef _MOD_TABLEINTERPFRACT32_H
#define _MOD_TABLEINTERPFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_TableInterpFract32_maxPoints 0x00000100
#define MASK_TableInterpFract32_numPoints 0x00000200
#define MASK_TableInterpFract32_outRange 0x00000400
#define MASK_TableInterpFract32_alerts 0x00000800
#define MASK_TableInterpFract32_order 0x00001000
#define MASK_TableInterpFract32_XY 0x00002000
#define MASK_TableInterpFract32_polyCoeffs 0x00004000
#define OFFSET_TableInterpFract32_maxPoints 0x00000008
#define OFFSET_TableInterpFract32_numPoints 0x00000009
#define OFFSET_TableInterpFract32_outRange 0x0000000A
#define OFFSET_TableInterpFract32_alerts 0x0000000B
#define OFFSET_TableInterpFract32_order 0x0000000C
#define OFFSET_TableInterpFract32_XY 0x0000000D
#define OFFSET_TableInterpFract32_polyCoeffs 0x0000000E

#define CLASSID_TABLEINTERPFRACT32 (CLASS_ID_MODBASE + 211)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modTableInterpFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              maxPoints;           // Maximum number of values in the lookup table. The total table size is [maxPoints 2].
    INT32              numPoints;           // Current number of interpolation values in use.
    INT32              outRange;            // Indicates if coefficients are out of fractional range.
    INT32              alerts;              // Indicates if coefficients are out of fractional range.
    INT32              order;               // Order of the interpolation. This can be either 2 (for linear) or 4 (for pchip).
    fract32*           XY;                  // Lookup table. The first row is the X values and the second row is the Y values.
    fract32*           polyCoeffs;          // Interpolation coefficients returned by the grid control.
} awe_modTableInterpFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modTableInterpFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modTableInterpFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modTableInterpFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_TABLEINTERPFRACT32_H

/**
 * @}
 *
 * End of file.
 */
