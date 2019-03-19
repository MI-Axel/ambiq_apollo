/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModTableLookupIntFloat.h
****************************************************************************
*
*     Description:  Table lookup where the input serves as an index into a lookup table
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
 * @brief Table lookup where the input serves as an index into a lookup table
 */

#ifndef _MOD_TABLELOOKUPINTFLOAT_H
#define _MOD_TABLELOOKUPINTFLOAT_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_TableLookupIntFloat_L 0x00000100
#define MASK_TableLookupIntFloat_table 0x00000200
#define OFFSET_TableLookupIntFloat_L 0x00000008
#define OFFSET_TableLookupIntFloat_table 0x00000009

#define CLASSID_TABLELOOKUPINTFLOAT (CLASS_ID_MODBASE + 1342)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modTableLookupIntFloatInstance
{
    ModuleInstanceDescriptor instance;
    INT32              L;                   // Number of entries in the table
    FLOAT32*           table;               // Table of lookup values
} awe_modTableLookupIntFloatInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modTableLookupIntFloatClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modTableLookupIntFloatConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modTableLookupIntFloatProcess(void *pInstance);

 

void awe_modTableLookupIntFloatBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_TABLELOOKUPINTFLOAT_H

/**
 * @}
 *
 * End of file.
 */
