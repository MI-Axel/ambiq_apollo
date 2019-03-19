/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModScalerNDBSmoothed.h
****************************************************************************
*
*     Description:  Smoothly varying linear scaler with independent gains in dB units
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
 * @brief Smoothly varying linear scaler with independent gains in dB units
 */

#ifndef _MOD_SCALERNDBSMOOTHED_H
#define _MOD_SCALERNDBSMOOTHED_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ScalerNDBSmoothed_smoothingTime 0x00000100
#define MASK_ScalerNDBSmoothed_smoothingCoeff 0x00000200
#define MASK_ScalerNDBSmoothed_gainDB 0x00000400
#define MASK_ScalerNDBSmoothed_gain 0x00000800
#define MASK_ScalerNDBSmoothed_currentGain 0x00001000
#define OFFSET_ScalerNDBSmoothed_smoothingTime 0x00000008
#define OFFSET_ScalerNDBSmoothed_smoothingCoeff 0x00000009
#define OFFSET_ScalerNDBSmoothed_gainDB 0x0000000A
#define OFFSET_ScalerNDBSmoothed_gain 0x0000000B
#define OFFSET_ScalerNDBSmoothed_currentGain 0x0000000C

#define CLASSID_SCALERNDBSMOOTHED (CLASS_ID_MODBASE + 2040)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modScalerNDBSmoothedInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process, in msec.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    FLOAT32*           gainDB;              // Array of gains, one per channel.  In dB units.
    FLOAT32*           gain;                // Linear equivalent of gainDB.
    FLOAT32*           currentGain;         // Array of instantaneous gains, one per channel, in linear units.
} awe_modScalerNDBSmoothedInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modScalerNDBSmoothedClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modScalerNDBSmoothedConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modScalerNDBSmoothedProcess(void *pInstance);

UINT32 awe_modScalerNDBSmoothedSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SCALERNDBSMOOTHED_H

/**
 * @}
 *
 * End of file.
 */
