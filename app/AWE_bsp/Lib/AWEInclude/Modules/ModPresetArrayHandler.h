/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModPresetArrayHandler.h
****************************************************************************
*
*     Description:  Updates module array from different preset tables.
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
 * @brief Updates module array from different preset tables.
 */

#ifndef _MOD_PRESETARRAYHANDLER_H
#define _MOD_PRESETARRAYHANDLER_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_PresetArrayHandler_numArrays 0x00000100
#define MASK_PresetArrayHandler_numRows 0x00000200
#define MASK_PresetArrayHandler_numCols 0x00000400
#define MASK_PresetArrayHandler_operation 0x00000800
#define MASK_PresetArrayHandler_initialFlag 0x00001000
#define MASK_PresetArrayHandler_presetsArray 0x00002000
#define MASK_PresetArrayHandler_modPtr 0x00004000
#define MASK_PresetArrayHandler_varPtr 0x00008000
#define OFFSET_PresetArrayHandler_numArrays 0x00000008
#define OFFSET_PresetArrayHandler_numRows 0x00000009
#define OFFSET_PresetArrayHandler_numCols 0x0000000A
#define OFFSET_PresetArrayHandler_operation 0x0000000B
#define OFFSET_PresetArrayHandler_initialFlag 0x0000000C
#define OFFSET_PresetArrayHandler_presetsArray 0x0000000D
#define OFFSET_PresetArrayHandler_modPtr 0x0000000E
#define OFFSET_PresetArrayHandler_varPtr 0x0000000F

#define CLASSID_PRESETARRAYHANDLER (CLASS_ID_MODBASE + 1373)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modPresetArrayHandlerInstance
{
    ModuleInstanceDescriptor instance;
    INT32              numArrays;           // number of presets.
    INT32              numRows;             // the number of vectors.
    INT32              numCols;             // the size of each vector.
    INT32              operation;           // math operation on presets. 0 - multiplication and 1 - addition.
    INT32              initialFlag;         // boolean flag which handles initial setup.
    FLOAT32*           presetsArray;        // 3-D presets array table.
    void *             modPtr;              // Points to the module to set.
    void *             varPtr;              // Points to the variable to set within the module instance structure.
} awe_modPresetArrayHandlerInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modPresetArrayHandlerClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modPresetArrayHandlerConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modPresetArrayHandlerProcess(void *pInstance);

UINT32 awe_modPresetArrayHandlerSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_PRESETARRAYHANDLER_H

/**
 * @}
 *
 * End of file.
 */
