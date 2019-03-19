/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModTriggeredSink.h
****************************************************************************
*
*     Description:  Copies the data at the input pin and stores it in an internal buffer. When triggered, buffer is frozen.
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
 * @brief Copies the data at the input pin and stores it in an internal buffer. When triggered, buffer is frozen.
 */

#ifndef _MOD_TRIGGEREDSINK_H
#define _MOD_TRIGGEREDSINK_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_TriggeredSink_reset 0x00000100
#define MASK_TriggeredSink_ctrl_index 0x00000200
#define MASK_TriggeredSink_manual_trigger 0x00000400
#define MASK_TriggeredSink_value 0x00000800
#define OFFSET_TriggeredSink_reset 0x00000008
#define OFFSET_TriggeredSink_ctrl_index 0x00000009
#define OFFSET_TriggeredSink_manual_trigger 0x0000000A
#define OFFSET_TriggeredSink_value 0x0000000B

#define CLASSID_TRIGGEREDSINK (CLASS_ID_MODBASE + 1347)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modTriggeredSinkInstance
{
    ModuleInstanceDescriptor instance;
    INT32              reset;               // Data will remain latched until reset set to 1.
    INT32              ctrl_index;          // Index of first non-zero element of the ctrl signal. Any non-zero element will trigger a data acquisition.
    INT32              manual_trigger;      // Trigger data acquisition from Matlab
    FLOAT32*           value;               // Captured values.
} awe_modTriggeredSinkInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modTriggeredSinkClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modTriggeredSinkConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modTriggeredSinkProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_TRIGGEREDSINK_H

/**
 * @}
 *
 * End of file.
 */
