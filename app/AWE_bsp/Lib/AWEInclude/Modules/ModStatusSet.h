/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModStatusSet.h
****************************************************************************
*
*     Description:  Sets status in other modules
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
 * @brief Sets status in other modules
 */

#ifndef _MOD_STATUSSET_H
#define _MOD_STATUSSET_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_StatusSet_setBehavior 0x00000100
#define MASK_StatusSet_prevStatus 0x00000200
#define MASK_StatusSet_nextStatus 0x00000400
#define MASK_StatusSet_numModules 0x00000800
#define MASK_StatusSet_modIds 0x00001000
#define MASK_StatusSet_modPtr 0x00002000
#define OFFSET_StatusSet_setBehavior 0x00000008
#define OFFSET_StatusSet_prevStatus 0x00000009
#define OFFSET_StatusSet_nextStatus 0x0000000A
#define OFFSET_StatusSet_numModules 0x0000000B
#define OFFSET_StatusSet_modIds 0x0000000C
#define OFFSET_StatusSet_modPtr 0x0000000D

#define CLASSID_STATUSSET (CLASS_ID_MODBASE + 1338)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modStatusSetInstance
{
    ModuleInstanceDescriptor instance;
    INT32              setBehavior;         // Controls the behavior of setting status
    INT32              prevStatus;          // Previous status
    INT32              nextStatus;          // Status value from the input wire.
    INT32              numModules;          // Total number of modules this module controls
    INT32*             modIds;              // Array to hold the object IDs of modules to set
    ModuleInstanceDescriptor **    modPtr;              // Points to the module to set
} awe_modStatusSetInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modStatusSetClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modStatusSetConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modStatusSetProcess(void *pInstance);

UINT32 awe_modStatusSetSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_STATUSSET_H

/**
 * @}
 *
 * End of file.
 */
