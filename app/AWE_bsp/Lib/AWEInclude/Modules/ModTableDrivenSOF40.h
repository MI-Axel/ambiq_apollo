/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModTableDrivenSOF40.h
****************************************************************************
*
*     Description:  Table driven second order filter module
*
*     Copyright:	   DSP Concepts, Inc., 2007 - 2015
*                   1800 Wyatt Drive, Suite 14
*                   Sunnyvale, CA 95054
*
***************************************************************************/

/**
 * @addtogroup Modules
 * @{
 */

/**
 * @file
 * @brief Table driven second order filter module
 */

#ifndef _MOD_TABLEDRIVENSOF40_H
#define _MOD_TABLEDRIVENSOF40_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModSecondOrderFilterSmoothed40.h"

#define MASK_TableDrivenSOF40_tableSize 0x00000100
#define MASK_TableDrivenSOF40_setting 0x00000200
#define MASK_TableDrivenSOF40_table 0x00000400
#define OFFSET_TableDrivenSOF40_tableSize 0x00000008
#define OFFSET_TableDrivenSOF40_setting 0x00000009
#define OFFSET_TableDrivenSOF40_table 0x0000000A

#define CLASSID_TABLEDRIVENSOF40 (CLASS_ID_MODBASE + 5311)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modTableDrivenSOF40Instance
{
    ModuleInstanceDescriptor instance;
    int                tableSize;           // Number of entries in the table
    int                setting;             // Control setting
    float*             table;               // Table of design parameters and selection depends on setting parameter
        awe_modSecondOrderFilterSmoothed40Instance    *filt;               // General 2nd order filter designer with 40-bit processing and smoothing
} awe_modTableDrivenSOF40Instance;

/* By default the class object is included and this is required for dynamic
 * instantiation.  When doing static code (define AWE_STATIC_CODE) you can save
 * a little bit of memory by eliminating class objects.  However, you lose the
 * ability to change the module status. */

#if (!defined(AWE_NO_CLASS_OBJECTS) || !defined(AWE_STATIC_CODE))
extern const ModClassModule awe_modTableDrivenSOF40Class;
#endif // #ifndef AWE_NO_CLASS_OBJECTS

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modTableDrivenSOF40Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modTableDrivenSOF40Process(void *pInstance);

UINT32 awe_modTableDrivenSOF40Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_TABLEDRIVENSOF40_H

/**
 * @}
 *
 * End of file.
 */
