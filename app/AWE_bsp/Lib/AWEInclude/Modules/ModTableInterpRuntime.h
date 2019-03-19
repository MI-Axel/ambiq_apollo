/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModTableInterpRuntime.h
****************************************************************************
*
*     Description:  Table driven interpolation module with set function.  Supports linear and smooth modes
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
 * @brief Table driven interpolation module with set function.  Supports linear and smooth modes
 */

#ifndef _MOD_TABLEINTERPRUNTIME_H
#define _MOD_TABLEINTERPRUNTIME_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_TableInterpRuntime_maxPoints 0x00000100
#define MASK_TableInterpRuntime_numPoints 0x00000200
#define MASK_TableInterpRuntime_order 0x00000400
#define MASK_TableInterpRuntime_XY 0x00000800
#define MASK_TableInterpRuntime_polyCoeffs 0x00001000
#define OFFSET_TableInterpRuntime_maxPoints 0x00000008
#define OFFSET_TableInterpRuntime_numPoints 0x00000009
#define OFFSET_TableInterpRuntime_order 0x0000000A
#define OFFSET_TableInterpRuntime_XY 0x0000000B
#define OFFSET_TableInterpRuntime_polyCoeffs 0x0000000C

#define CLASSID_TABLEINTERPRUNTIME (CLASS_ID_MODBASE + 2044)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modTableInterpRuntimeInstance
{
    ModuleInstanceDescriptor instance;
    INT32              maxPoints;           // Maximum number of values in the lookup table. The total table size is [maxPoints 2].
    INT32              numPoints;           // Current number of interpolation values in use.
    INT32              order;               // Order of the interpolation. This can be either 2 (for linear) or 4 (for pchip).
    FLOAT32*           XY;                  // Samples of the lookup table. The first row is the x values and the second row is the f(x) values
    FLOAT32*           polyCoeffs;          // Interpolation coefficients returned by the grid control
} awe_modTableInterpRuntimeInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modTableInterpRuntimeClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modTableInterpRuntimeConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modTableInterpRuntimeProcess(void *pInstance);

UINT32 awe_modTableInterpRuntimeSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_TABLEINTERPRUNTIME_H

/**
 * @}
 *
 * End of file.
 */
