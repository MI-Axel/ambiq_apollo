/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModTableLookup.h
****************************************************************************
*
*     Description:  Evenly spaced table lookup
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
 * @brief Evenly spaced table lookup
 */

#ifndef _MOD_TABLELOOKUP_H
#define _MOD_TABLELOOKUP_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_TableLookup_L 0x00000100
#define MASK_TableLookup_interpolationType 0x00000200
#define MASK_TableLookup_minX 0x00000400
#define MASK_TableLookup_maxX 0x00000800
#define MASK_TableLookup_divisor 0x00001000
#define MASK_TableLookup_table 0x00002000
#define OFFSET_TableLookup_L 0x00000008
#define OFFSET_TableLookup_interpolationType 0x00000009
#define OFFSET_TableLookup_minX 0x0000000A
#define OFFSET_TableLookup_maxX 0x0000000B
#define OFFSET_TableLookup_divisor 0x0000000C
#define OFFSET_TableLookup_table 0x0000000D

#define CLASSID_TABLELOOKUP (CLASS_ID_MODBASE + 209)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modTableLookupInstance
{
    ModuleInstanceDescriptor instance;
    INT32              L;                   // Number of entries in the table.
    INT32              interpolationType;   // Selects the type of interpolation: 0=nearest, 1=linear.
    FLOAT32            minX;                // X value corresponding to the first table entry.
    FLOAT32            maxX;                // X value corresponding to the last table entry.
    FLOAT32            divisor;             // Precomputed constant = (L-1)/(maxX-minX) to eliminate division on the target.
    FLOAT32*           table;               // Table of evenly spaced values.
} awe_modTableLookupInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modTableLookupClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modTableLookupConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modTableLookupProcess(void *pInstance);

UINT32 awe_modTableLookupSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_TABLELOOKUP_H

/**
 * @}
 *
 * End of file.
 */
