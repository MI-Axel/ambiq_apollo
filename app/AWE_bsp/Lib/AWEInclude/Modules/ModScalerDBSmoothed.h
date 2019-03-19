/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModScalerDBSmoothed.h
****************************************************************************
*
*     Description:  Gain control with dB units and smoothing
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
 * @brief Gain control with dB units and smoothing
 */

#ifndef _MOD_SCALERDBSMOOTHED_H
#define _MOD_SCALERDBSMOOTHED_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ScalerDBSmoothed_gainDB 0x00000100
#define MASK_ScalerDBSmoothed_currentGain 0x00000200
#define MASK_ScalerDBSmoothed_smoothingTime 0x00000400
#define MASK_ScalerDBSmoothed_smoothingCoeff 0x00000800
#define MASK_ScalerDBSmoothed_gain 0x00001000
#define OFFSET_ScalerDBSmoothed_gainDB 0x00000008
#define OFFSET_ScalerDBSmoothed_currentGain 0x00000009
#define OFFSET_ScalerDBSmoothed_smoothingTime 0x0000000A
#define OFFSET_ScalerDBSmoothed_smoothingCoeff 0x0000000B
#define OFFSET_ScalerDBSmoothed_gain 0x0000000C

#define CLASSID_SCALERDBSMOOTHED (CLASS_ID_MODBASE + 2037)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modScalerDBSmoothedInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            gainDB;              // Gain in dB units.
    FLOAT32            currentGain;         // Instantaneous gain applied by the module. This is also the starting gain of the module.
    FLOAT32            smoothingTime;       // Time constant of the smoothing process.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    FLOAT32            gain;                // Gain in linear units.
    
} awe_modScalerDBSmoothedInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modScalerDBSmoothedClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modScalerDBSmoothedConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SCALERDBSMOOTHED, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modScalerDBSmoothedProcess(void *pInstance);

UINT32 awe_modScalerDBSmoothedSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SCALERDBSMOOTHED_H

/**
 * @}
 *
 * End of file.
 */
