/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBooleanSink.h
****************************************************************************
*
*     Description:  Sink module holding Boolean data
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
 * @brief Sink module holding Boolean data
 */

#ifndef _MOD_BOOLEANSINK_H
#define _MOD_BOOLEANSINK_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_BooleanSink_value 0x00000100
#define OFFSET_BooleanSink_value 0x00000008

#define CLASSID_BOOLEANSINK (CLASS_ID_MODBASE + 105)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBooleanSinkInstance
{
    ModuleInstanceDescriptor instance;
    
    INT32*             value;               // Boolean array of response to the signals on the wires
} awe_modBooleanSinkInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBooleanSinkClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modBooleanSinkConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modBooleanSinkProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BOOLEANSINK_H

/**
 * @}
 *
 * End of file.
 */
