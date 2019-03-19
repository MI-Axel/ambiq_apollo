/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModHysteresis.h
****************************************************************************
*
*     Description:  Threshold with hysteresis
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
 * @brief Threshold with hysteresis
 */

#ifndef _MOD_HYSTERESIS_H
#define _MOD_HYSTERESIS_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Hysteresis_upperThreshold 0x00000100
#define MASK_Hysteresis_lowerThreshold 0x00000200
#define MASK_Hysteresis_state 0x00000400
#define OFFSET_Hysteresis_upperThreshold 0x00000008
#define OFFSET_Hysteresis_lowerThreshold 0x00000009
#define OFFSET_Hysteresis_state 0x0000000A

#define CLASSID_HYSTERESIS (CLASS_ID_MODBASE + 1287)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modHysteresisInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            upperThreshold;      // Upper switching threshold
    FLOAT32            lowerThreshold;      // Lower switching threshold
    INT32*             state;               // Current state per chanel
} awe_modHysteresisInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modHysteresisClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modHysteresisConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modHysteresisProcess(void *pInstance);

 

void awe_modHysteresisBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_HYSTERESIS_H

/**
 * @}
 *
 * End of file.
 */
