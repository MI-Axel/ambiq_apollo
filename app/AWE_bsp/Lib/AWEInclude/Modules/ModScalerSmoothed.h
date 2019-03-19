/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModScalerSmoothed.h
****************************************************************************
*
*     Description:  Gain control with linear units and smoothing
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
 * @brief Gain control with linear units and smoothing
 */

#ifndef _MOD_SCALERSMOOTHED_H
#define _MOD_SCALERSMOOTHED_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ScalerSmoothed_gain 0x00000100
#define MASK_ScalerSmoothed_smoothingTime 0x00000200
#define MASK_ScalerSmoothed_currentGain 0x00000400
#define MASK_ScalerSmoothed_smoothingCoeff 0x00000800
#define OFFSET_ScalerSmoothed_gain 0x00000008
#define OFFSET_ScalerSmoothed_smoothingTime 0x00000009
#define OFFSET_ScalerSmoothed_currentGain 0x0000000A
#define OFFSET_ScalerSmoothed_smoothingCoeff 0x0000000B

#define CLASSID_SCALERSMOOTHED (CLASS_ID_MODBASE + 2039)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modScalerSmoothedInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            gain;                // Gain in linear units.
    FLOAT32            smoothingTime;       // Time constant of the smoothing process.
    FLOAT32            currentGain;         // Instantaneous gain applied by the module. This is also the starting gain of the module.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    
} awe_modScalerSmoothedInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modScalerSmoothedClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modScalerSmoothedConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SCALERSMOOTHED, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modScalerSmoothedProcess(void *pInstance);

UINT32 awe_modScalerSmoothedSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SCALERSMOOTHED_H

/**
 * @}
 *
 * End of file.
 */
