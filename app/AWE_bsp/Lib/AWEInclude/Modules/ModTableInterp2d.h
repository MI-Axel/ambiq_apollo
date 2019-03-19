/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModTableInterp2d.h
****************************************************************************
*
*     Description:  Table driven 2d interpolation module.  Currently supports only bilinear interpolation
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
 * @brief Table driven 2d interpolation module.  Currently supports only bilinear interpolation
 */

#ifndef _MOD_TABLEINTERP2D_H
#define _MOD_TABLEINTERP2D_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_TableInterp2d_nPoints 0x00000100
#define MASK_TableInterp2d_table 0x00000200
#define OFFSET_TableInterp2d_nPoints 0x00000008
#define OFFSET_TableInterp2d_table 0x00000009

#define CLASSID_TABLEINTERP2D (CLASS_ID_MODBASE + 1341)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modTableInterp2dInstance
{
    ModuleInstanceDescriptor instance;
    INT32              nPoints;             // Number of points in each dimension of the active interpolation table.
    FLOAT32*           table;               // 2d Interpolation Lookup table
} awe_modTableInterp2dInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modTableInterp2dClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modTableInterp2dConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modTableInterp2dProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_TABLEINTERP2D_H

/**
 * @}
 *
 * End of file.
 */
