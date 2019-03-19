/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModScalerDBSmoothedFract32.h
****************************************************************************
*
*     Description:  Linear multichannel smoothly varying dB scaler
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
 * @brief Linear multichannel smoothly varying dB scaler
 */

#ifndef _MOD_SCALERDBSMOOTHEDFRACT32_H
#define _MOD_SCALERDBSMOOTHEDFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ScalerDBSmoothedFract32_smoothingTime 0x00000100
#define MASK_ScalerDBSmoothedFract32_gainDB 0x00000200
#define MASK_ScalerDBSmoothedFract32_targetGain 0x00000400
#define MASK_ScalerDBSmoothedFract32_currentGain 0x00000800
#define MASK_ScalerDBSmoothedFract32_smoothingCoeff 0x00001000
#define MASK_ScalerDBSmoothedFract32_postShift 0x00002000
#define MASK_ScalerDBSmoothedFract32_twoPowMinusPostShift 0x00004000
#define OFFSET_ScalerDBSmoothedFract32_smoothingTime 0x00000008
#define OFFSET_ScalerDBSmoothedFract32_gainDB 0x00000009
#define OFFSET_ScalerDBSmoothedFract32_targetGain 0x0000000A
#define OFFSET_ScalerDBSmoothedFract32_currentGain 0x0000000B
#define OFFSET_ScalerDBSmoothedFract32_smoothingCoeff 0x0000000C
#define OFFSET_ScalerDBSmoothedFract32_postShift 0x0000000D
#define OFFSET_ScalerDBSmoothedFract32_twoPowMinusPostShift 0x0000000E

#define CLASSID_SCALERDBSMOOTHEDFRACT32 (CLASS_ID_MODBASE + 186)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modScalerDBSmoothedFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    FLOAT32            gainDB;              // Target gain in DB
    fract32            targetGain;          // Desired (or target) of the fractional portion of the overall scaling.  This is also the starting gain of the module.
    fract32            currentGain;         // Instantaneous gain applied by the module.  This is also the starting gain of the module.
    fract32            smoothingCoeff;      // Smoothing coefficient
    INT32              postShift;           // Number of bits to shift after the fractional multiply.  This is based on gain.range.
    FLOAT32            twoPowMinusPostShift; // 2^(-postShift).  Used by to streamline the operation of the set function
    
} awe_modScalerDBSmoothedFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modScalerDBSmoothedFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modScalerDBSmoothedFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SCALERDBSMOOTHEDFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modScalerDBSmoothedFract32Process(void *pInstance);

UINT32 awe_modScalerDBSmoothedFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SCALERDBSMOOTHEDFRACT32_H

/**
 * @}
 *
 * End of file.
 */
