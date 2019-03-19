/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModApplyPreset.h
****************************************************************************
*
*     Description:  Applies the selected preset, PSBNAME, on the target from Flash
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
 * @brief Applies the selected preset, PSBNAME, on the target from Flash
 */

#ifndef _MOD_APPLYPRESET_H
#define _MOD_APPLYPRESET_H

#include "ModCommon.h"
#include "MathHelper.h"
#if defined(__ADSP21000__) || defined(__ADSPBLACKFIN__)
#include "FileSystem.h"
#endif

#define MASK_ApplyPreset_tiggerState 0x00000100
#define MASK_ApplyPreset_PresetName 0x00000200
#define OFFSET_ApplyPreset_tiggerState 0x00000008
#define OFFSET_ApplyPreset_PresetName 0x00000009

#define CLASSID_APPLYPRESET (CLASS_ID_MODBASE + 2001)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modApplyPresetInstance
{
    ModuleInstanceDescriptor instance;
    INT32              tiggerState;         // State variable which holds trigger input state
    INT32*             PresetName;          // Name of the preset to apply on the target
} awe_modApplyPresetInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modApplyPresetClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modApplyPresetConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modApplyPresetProcess(void *pInstance);

UINT32 awe_modApplyPresetSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_APPLYPRESET_H

/**
 * @}
 *
 * End of file.
 */
