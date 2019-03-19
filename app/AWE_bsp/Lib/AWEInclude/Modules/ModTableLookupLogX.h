/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModTableLookupLogX.h
****************************************************************************
*
*     Description:  Log/Anti-log and Linearly spaced table lookup
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
 * @brief Log/Anti-log and Linearly spaced table lookup
 */

#ifndef _MOD_TABLELOOKUPLOGX_H
#define _MOD_TABLELOOKUPLOGX_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_TableLookupLogX_numPoints 0x00000100
#define MASK_TableLookupLogX_spacingType 0x00000200
#define MASK_TableLookupLogX_interpolationType 0x00000400
#define MASK_TableLookupLogX_minX 0x00000800
#define MASK_TableLookupLogX_maxX 0x00001000
#define MASK_TableLookupLogX_log_minX 0x00002000
#define MASK_TableLookupLogX_log_maxX 0x00004000
#define MASK_TableLookupLogX_logspace_delta 0x00008000
#define MASK_TableLookupLogX_divisor 0x00010000
#define MASK_TableLookupLogX_table 0x00020000
#define OFFSET_TableLookupLogX_numPoints 0x00000008
#define OFFSET_TableLookupLogX_spacingType 0x00000009
#define OFFSET_TableLookupLogX_interpolationType 0x0000000A
#define OFFSET_TableLookupLogX_minX 0x0000000B
#define OFFSET_TableLookupLogX_maxX 0x0000000C
#define OFFSET_TableLookupLogX_log_minX 0x0000000D
#define OFFSET_TableLookupLogX_log_maxX 0x0000000E
#define OFFSET_TableLookupLogX_logspace_delta 0x0000000F
#define OFFSET_TableLookupLogX_divisor 0x00000010
#define OFFSET_TableLookupLogX_table 0x00000011

#define CLASSID_TABLELOOKUPLOGX (CLASS_ID_MODBASE + 1344)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modTableLookupLogXInstance
{
    ModuleInstanceDescriptor instance;
    INT32              numPoints;           // Number of entries in the table.
    INT32              spacingType;         // Selects the input spacig type: 0=Log, 1=Anti-log and 2=Linear.
    INT32              interpolationType;   // Selects the type of interpolation: 0=nearest, 1=linear.
    FLOAT32            minX;                // X value corresponding to the first table entry.
    FLOAT32            maxX;                // X value corresponding to the last table entry.
    FLOAT32            log_minX;            // Log value of the minX parameter.
    FLOAT32            log_maxX;            // Log value of the maxX parameter.
    FLOAT32            logspace_delta;      // Logspace delta for input.
    FLOAT32            divisor;             // Precomputed constant = (NUM_POINTS-1)/(log_maxX - log_minX) to eliminate division on the target.
    FLOAT32*           table;               // Table of evenly spaced values.
} awe_modTableLookupLogXInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modTableLookupLogXClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modTableLookupLogXConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modTableLookupLogXProcess(void *pInstance);

UINT32 awe_modTableLookupLogXSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_TABLELOOKUPLOGX_H

/**
 * @}
 *
 * End of file.
 */
