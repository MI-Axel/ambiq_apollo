/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModScalerV2.h
****************************************************************************
*
*     Description:  General purpose scaler with a single gain
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
 * @brief General purpose scaler with a single gain
 */

#ifndef _MOD_SCALERV2_H
#define _MOD_SCALERV2_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ScalerV2_gain 0x00000100
#define MASK_ScalerV2_smoothingTime 0x00000200
#define MASK_ScalerV2_isDB 0x00000400
#define MASK_ScalerV2_targetGain 0x00000800
#define MASK_ScalerV2_currentGain 0x00001000
#define MASK_ScalerV2_smoothingCoeff 0x00002000
#define OFFSET_ScalerV2_gain 0x00000008
#define OFFSET_ScalerV2_smoothingTime 0x00000009
#define OFFSET_ScalerV2_isDB 0x0000000A
#define OFFSET_ScalerV2_targetGain 0x0000000B
#define OFFSET_ScalerV2_currentGain 0x0000000C
#define OFFSET_ScalerV2_smoothingCoeff 0x0000000D

#define CLASSID_SCALERV2 (CLASS_ID_MODBASE + 19)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modScalerV2Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            gain;                // Gain in either linear or dB units.
    FLOAT32            smoothingTime;       // Time constant of the smoothing process (0 = unsmoothed).
    INT32              isDB;                // Selects between linear (=0) and dB (=1) operation
    FLOAT32            targetGain;          // Target gain in linear units.
    FLOAT32            currentGain;         // Instantaneous gain applied by the module.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    
} awe_modScalerV2Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modScalerV2Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modScalerV2Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SCALERV2, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modScalerV2Process(void *pInstance);

UINT32 awe_modScalerV2Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SCALERV2_H

/**
 * @}
 *
 * End of file.
 */
