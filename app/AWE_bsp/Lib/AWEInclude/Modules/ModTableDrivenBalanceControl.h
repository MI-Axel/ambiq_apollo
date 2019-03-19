/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModTableDrivenBalanceControl.h
****************************************************************************
*
*     Description:  Table driven balance control
*
*     Copyright:    DSP Concepts, Inc, 2007 - 2015
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
 * @brief Table driven balance control
 */

#ifndef _MOD_TABLEDRIVENBALANCECONTROL_H
#define _MOD_TABLEDRIVENBALANCECONTROL_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModScalerNDBSmoothed.h"

#define MASK_TableDrivenBalanceControl_setting 0x00000100
#define MASK_TableDrivenBalanceControl_tableSize 0x00000200
#define MASK_TableDrivenBalanceControl_chanFlag 0x00000400
#define MASK_TableDrivenBalanceControl_table 0x00000800
#define OFFSET_TableDrivenBalanceControl_setting 0x00000008
#define OFFSET_TableDrivenBalanceControl_tableSize 0x00000009
#define OFFSET_TableDrivenBalanceControl_chanFlag 0x0000000A
#define OFFSET_TableDrivenBalanceControl_table 0x0000000B

#define CLASSID_TABLEDRIVENBALANCECONTROL (CLASS_ID_MODBASE + 1224)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modTableDrivenBalanceControlInstance
{
    ModuleInstanceDescriptor instance;
    int                setting;             // 
    int                tableSize;           // Number of entries in the table
    int*               chanFlag;            // Specifies assignment per channel.  0 = left, 1 = right, 2 = unassigned.
    float*             table;               // Table of design parameteres and selection depends on setting parameter
        awe_modScalerNDBSmoothedInstance    *scalern;            // Smoothly varying linear scaler with independent gains in dB units
} awe_modTableDrivenBalanceControlInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modTableDrivenBalanceControlClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modTableDrivenBalanceControlConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modTableDrivenBalanceControlProcess(void *pInstance);

UINT32 awe_modTableDrivenBalanceControlSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_TABLEDRIVENBALANCECONTROL_H

/**
 * @}
 *
 * End of file.
 */
