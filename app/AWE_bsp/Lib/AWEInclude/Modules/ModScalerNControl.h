/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModScalerNControl.h
****************************************************************************
*
*     Description:  Smooth scaler with independent gain per channel with gain (in linear units) is taken from an input pin
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
 * @brief Smooth scaler with independent gain per channel with gain (in linear units) is taken from an input pin
 */

#ifndef _MOD_SCALERNCONTROL_H
#define _MOD_SCALERNCONTROL_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ScalerNControl_smoothingTime 0x00000100
#define MASK_ScalerNControl_smoothingCoeff 0x00000200
#define MASK_ScalerNControl_currentGain 0x00000400
#define OFFSET_ScalerNControl_smoothingTime 0x00000008
#define OFFSET_ScalerNControl_smoothingCoeff 0x00000009
#define OFFSET_ScalerNControl_currentGain 0x0000000A

#define CLASSID_SCALERNCONTROL (CLASS_ID_MODBASE + 219)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modScalerNControlInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    FLOAT32            smoothingCoeff;      // Smoothing coefficient
    FLOAT32*           currentGain;         // Array of instantaneous linear gains, one per channel.
} awe_modScalerNControlInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modScalerNControlClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modScalerNControlConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modScalerNControlProcess(void *pInstance);

UINT32 awe_modScalerNControlSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SCALERNCONTROL_H

/**
 * @}
 *
 * End of file.
 */
