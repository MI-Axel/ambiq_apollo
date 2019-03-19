/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModTableLookupIntInt.h
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

#ifndef _MOD_TABLELOOKUPINTINT_H
#define _MOD_TABLELOOKUPINTINT_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_TableLookupIntInt_L 0x00000100
#define MASK_TableLookupIntInt_table 0x00000200
#define OFFSET_TableLookupIntInt_L 0x00000008
#define OFFSET_TableLookupIntInt_table 0x00000009

#define CLASSID_TABLELOOKUPINTINT (CLASS_ID_MODBASE + 1343)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modTableLookupIntIntInstance
{
    ModuleInstanceDescriptor instance;
    INT32              L;                   // Number of entries in the table
    INT32*             table;               // Table of lookup values
} awe_modTableLookupIntIntInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modTableLookupIntIntClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modTableLookupIntIntConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modTableLookupIntIntProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_TABLELOOKUPINTINT_H

/**
 * @}
 *
 * End of file.
 */
