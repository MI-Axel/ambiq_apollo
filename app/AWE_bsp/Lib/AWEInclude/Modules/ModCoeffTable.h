/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModCoeffTable.h
****************************************************************************
*
*     Description:  Sets filter coefficients in other modules
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
 * @brief Sets filter coefficients in other modules
 */

#ifndef _MOD_COEFFTABLE_H
#define _MOD_COEFFTABLE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_CoeffTable_index 0x00000100
#define MASK_CoeffTable_numRows 0x00000200
#define MASK_CoeffTable_numCols 0x00000400
#define MASK_CoeffTable_setBehavior 0x00000800
#define MASK_CoeffTable_coeff 0x00001000
#define MASK_CoeffTable_modPtr 0x00002000
#define MASK_CoeffTable_varPtr 0x00004000
#define OFFSET_CoeffTable_index 0x00000008
#define OFFSET_CoeffTable_numRows 0x00000009
#define OFFSET_CoeffTable_numCols 0x0000000A
#define OFFSET_CoeffTable_setBehavior 0x0000000B
#define OFFSET_CoeffTable_coeff 0x0000000C
#define OFFSET_CoeffTable_modPtr 0x0000000D
#define OFFSET_CoeffTable_varPtr 0x0000000E

#define CLASSID_COEFFTABLE (CLASS_ID_MODBASE + 1231)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modCoeffTableInstance
{
    ModuleInstanceDescriptor instance;
    INT32              index;               // current index to coeff table
    INT32              numRows;             // the size of each vector
    INT32              numCols;             // the number of vectors
    INT32              setBehavior;         // Controls the behavior of the module
    FLOAT32*           coeff;               // 2-D coeff table.
    void *             modPtr;              // Points to the module to set
    void *             varPtr;              // Points to the variable to set within the module instance structure
} awe_modCoeffTableInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modCoeffTableClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modCoeffTableConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modCoeffTableProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_COEFFTABLE_H

/**
 * @}
 *
 * End of file.
 */
