/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModOverwriteControl.h
****************************************************************************
*
*     Description:  Module which allows to overwrite control data on any channel.
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
 * @brief Module which allows to overwrite control data on any channel.
 */

#ifndef _MOD_OVERWRITECONTROL_H
#define _MOD_OVERWRITECONTROL_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_OverwriteControl_dataType 0x00000100
#define MASK_OverwriteControl_Overwrite 0x00000200
#define MASK_OverwriteControl_Value 0x00000400
#define OFFSET_OverwriteControl_dataType 0x00000008
#define OFFSET_OverwriteControl_Overwrite 0x00000009
#define OFFSET_OverwriteControl_Value 0x0000000A

#define CLASSID_OVERWRITECONTROL (CLASS_ID_MODBASE + 1371)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modOverwriteControlInstance
{
    ModuleInstanceDescriptor instance;
    INT32              dataType;            // Data type of the input/output pin, used internally.
    INT32*             Overwrite;           // Boolean indicates whether to overwrite the output of a channel by the given value.
    FLOAT32*           Value;               // Array of values to be overwritten per channel.
} awe_modOverwriteControlInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modOverwriteControlClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modOverwriteControlConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modOverwriteControlProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_OVERWRITECONTROL_H

/**
 * @}
 *
 * End of file.
 */
