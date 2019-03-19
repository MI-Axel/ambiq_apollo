/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModLPF1Control.h
****************************************************************************
*
*     Description:  Time varying 1st order LPF controlled using an input pin.
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
 * @brief Time varying 1st order LPF controlled using an input pin.
 */

#ifndef _MOD_LPF1CONTROL_H
#define _MOD_LPF1CONTROL_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_LPF1Control_smoothingTime 0x00000100
#define MASK_LPF1Control_smoothingCoeff 0x00000200
#define MASK_LPF1Control_currentA1 0x00000400
#define MASK_LPF1Control_state 0x00000800
#define OFFSET_LPF1Control_smoothingTime 0x00000008
#define OFFSET_LPF1Control_smoothingCoeff 0x00000009
#define OFFSET_LPF1Control_currentA1 0x0000000A
#define OFFSET_LPF1Control_state 0x0000000B

#define CLASSID_LPF1CONTROL (CLASS_ID_MODBASE + 1294)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modLPF1ControlInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    FLOAT32            smoothingCoeff;      // Smoothing coefficient
    FLOAT32            currentA1;           // Instantaneous a1 filter coefficient
    FLOAT32*           state;               // State variables.  2 per channel
} awe_modLPF1ControlInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modLPF1ControlClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modLPF1ControlConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modLPF1ControlProcess(void *pInstance);

UINT32 awe_modLPF1ControlSet(void *pInstance, UINT32 mask);
 

void awe_modLPF1ControlBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_LPF1CONTROL_H

/**
 * @}
 *
 * End of file.
 */
