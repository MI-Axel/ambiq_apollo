/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSMixer2x1Fract32.h
****************************************************************************
*
*     Description:  2-input x 1-output smoothly varying mixer module with linear gains
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
 * @brief 2-input x 1-output smoothly varying mixer module with linear gains
 */

#ifndef _MOD_SMIXER2X1FRACT32_H
#define _MOD_SMIXER2X1FRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SMixer2x1Fract32_gain1 0x00000100
#define MASK_SMixer2x1Fract32_gain2 0x00000200
#define MASK_SMixer2x1Fract32_smoothingTime 0x00000400
#define MASK_SMixer2x1Fract32_targetGain1 0x00000800
#define MASK_SMixer2x1Fract32_currentGain1 0x00001000
#define MASK_SMixer2x1Fract32_targetGain2 0x00002000
#define MASK_SMixer2x1Fract32_currentGain2 0x00004000
#define MASK_SMixer2x1Fract32_smoothingCoeff 0x00008000
#define MASK_SMixer2x1Fract32_postShift 0x00010000
#define MASK_SMixer2x1Fract32_twoPowMinusPostShift 0x00020000
#define OFFSET_SMixer2x1Fract32_gain1 0x00000008
#define OFFSET_SMixer2x1Fract32_gain2 0x00000009
#define OFFSET_SMixer2x1Fract32_smoothingTime 0x0000000A
#define OFFSET_SMixer2x1Fract32_targetGain1 0x0000000B
#define OFFSET_SMixer2x1Fract32_currentGain1 0x0000000C
#define OFFSET_SMixer2x1Fract32_targetGain2 0x0000000D
#define OFFSET_SMixer2x1Fract32_currentGain2 0x0000000E
#define OFFSET_SMixer2x1Fract32_smoothingCoeff 0x0000000F
#define OFFSET_SMixer2x1Fract32_postShift 0x00000010
#define OFFSET_SMixer2x1Fract32_twoPowMinusPostShift 0x00000011

#define CLASSID_SMIXER2X1FRACT32 (CLASS_ID_MODBASE + 198)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSMixer2x1Fract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            gain1;               // Desired gain applied to first input channel
    FLOAT32            gain2;               // Desired gain applied to second input channel
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    fract32            targetGain1;         // Fractional portion of the desired (or target) gain of the first channel
    fract32            currentGain1;        // Fractional portion of the instantaneous gain of the first channel
    fract32            targetGain2;         // Fractional portion of the desired (or target) gain of the second channel
    fract32            currentGain2;        // Fractional portion of the instantaneous gain of the second channel
    fract32            smoothingCoeff;      // Smoothing coefficient
    INT32              postShift;           // Number of bits to shift after the fractional multiply.  This is based on gain.range.
    FLOAT32            twoPowMinusPostShift; // 2^(-postShift).  Used by to streamline the operation of the set function
    
} awe_modSMixer2x1Fract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSMixer2x1Fract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSMixer2x1Fract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SMIXER2X1FRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSMixer2x1Fract32Process(void *pInstance);

UINT32 awe_modSMixer2x1Fract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SMIXER2X1FRACT32_H

/**
 * @}
 *
 * End of file.
 */
