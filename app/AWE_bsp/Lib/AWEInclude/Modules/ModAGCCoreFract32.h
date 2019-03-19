/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAGCCoreFract32.h
****************************************************************************
*
*     Description:  Automatic Gain Control gain calculator module
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
 * @brief Automatic Gain Control gain calculator module
 */

#ifndef _MOD_AGCCOREFRACT32_H
#define _MOD_AGCCOREFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_AGCCoreFract32_targetLevel 0x00000100
#define MASK_AGCCoreFract32_maxAttenuation 0x00000200
#define MASK_AGCCoreFract32_maxGain 0x00000400
#define MASK_AGCCoreFract32_ratio 0x00000800
#define MASK_AGCCoreFract32_activationThreshold 0x00001000
#define MASK_AGCCoreFract32_smoothingTime 0x00002000
#define MASK_AGCCoreFract32_enableRecovery 0x00004000
#define MASK_AGCCoreFract32_recoveryRate 0x00008000
#define MASK_AGCCoreFract32_currentGain 0x00010000
#define MASK_AGCCoreFract32_smoothingCoeffSampleFract32 0x00020000
#define MASK_AGCCoreFract32_smoothingCoeffBlockFract32 0x00040000
#define MASK_AGCCoreFract32_targetGainFract32 0x00080000
#define MASK_AGCCoreFract32_energyFract32 0x00100000
#define MASK_AGCCoreFract32_oneOverNumSamplesFract32 0x00200000
#define MASK_AGCCoreFract32_oneOverSlopeFract32 0x00400000
#define MASK_AGCCoreFract32_oneOverSlope 0x00800000
#define MASK_AGCCoreFract32_smoothingCoeffSample 0x01000000
#define MASK_AGCCoreFract32_smoothingCoeffBlock 0x02000000
#define MASK_AGCCoreFract32_recoveryRateUp 0x04000000
#define MASK_AGCCoreFract32_recoveryRateDown 0x08000000
#define MASK_AGCCoreFract32_targetGain 0x10000000
#define MASK_AGCCoreFract32_energy 0x20000000
#define MASK_AGCCoreFract32_oneOverNumSamples 0x40000000
#define MASK_AGCCoreFract32_targetLevelFract32 0x80000000
#define MASK_AGCCoreFract32_maxGainFract32 0x80000000
#define MASK_AGCCoreFract32_maxAttenuationFract32 0x80000000
#define MASK_AGCCoreFract32_activationThresholdFract32 0x80000000
#define MASK_AGCCoreFract32_recoveryRateUpFract32 0x80000000
#define MASK_AGCCoreFract32_recoveryRateDownFract32 0x80000000
#define MASK_AGCCoreFract32_currentGainFract32 0x80000000
#define OFFSET_AGCCoreFract32_targetLevel 0x00000008
#define OFFSET_AGCCoreFract32_maxAttenuation 0x00000009
#define OFFSET_AGCCoreFract32_maxGain 0x0000000A
#define OFFSET_AGCCoreFract32_ratio 0x0000000B
#define OFFSET_AGCCoreFract32_activationThreshold 0x0000000C
#define OFFSET_AGCCoreFract32_smoothingTime 0x0000000D
#define OFFSET_AGCCoreFract32_enableRecovery 0x0000000E
#define OFFSET_AGCCoreFract32_recoveryRate 0x0000000F
#define OFFSET_AGCCoreFract32_currentGain 0x00000010
#define OFFSET_AGCCoreFract32_smoothingCoeffSampleFract32 0x00000011
#define OFFSET_AGCCoreFract32_smoothingCoeffBlockFract32 0x00000012
#define OFFSET_AGCCoreFract32_targetGainFract32 0x00000013
#define OFFSET_AGCCoreFract32_energyFract32 0x00000014
#define OFFSET_AGCCoreFract32_oneOverNumSamplesFract32 0x00000015
#define OFFSET_AGCCoreFract32_oneOverSlopeFract32 0x00000016
#define OFFSET_AGCCoreFract32_oneOverSlope 0x00000017
#define OFFSET_AGCCoreFract32_smoothingCoeffSample 0x00000018
#define OFFSET_AGCCoreFract32_smoothingCoeffBlock 0x00000019
#define OFFSET_AGCCoreFract32_recoveryRateUp 0x0000001A
#define OFFSET_AGCCoreFract32_recoveryRateDown 0x0000001B
#define OFFSET_AGCCoreFract32_targetGain 0x0000001C
#define OFFSET_AGCCoreFract32_energy 0x0000001D
#define OFFSET_AGCCoreFract32_oneOverNumSamples 0x0000001E
#define OFFSET_AGCCoreFract32_targetLevelFract32 0x0000001F
#define OFFSET_AGCCoreFract32_maxGainFract32 0x00000020
#define OFFSET_AGCCoreFract32_maxAttenuationFract32 0x00000021
#define OFFSET_AGCCoreFract32_activationThresholdFract32 0x00000022
#define OFFSET_AGCCoreFract32_recoveryRateUpFract32 0x00000023
#define OFFSET_AGCCoreFract32_recoveryRateDownFract32 0x00000024
#define OFFSET_AGCCoreFract32_currentGainFract32 0x00000025

#define CLASSID_AGCCOREFRACT32 (CLASS_ID_MODBASE + 1204)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAGCCoreFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            targetLevel;         // Target audio level
    FLOAT32            maxAttenuation;      // Maximum attenuation of the AGC
    FLOAT32            maxGain;             // Maximum gain of the AGC
    FLOAT32            ratio;               // Slope of the output attenuation when the signal is above threshold
    FLOAT32            activationThreshold; // Activation threshold of the AGC.  The AGC stops updating its gain when the instantaneous input level is below this value
    FLOAT32            smoothingTime;       // Response time of the AGC.  This controls the RMS smoothing interval and the time constant of the smoothly updating gain
    INT32              enableRecovery;      // Boolean which enables the AGC's gain recovery.  If enabled, the AGC slows returns 0 dB gain when the input is below the activation threshold
    FLOAT32            recoveryRate;        // Rate at which the gain is adjusted when the input is below the activation threshold
    FLOAT32            currentGain;         // Instantaneous gain of the smoothing operation.
    fract32            smoothingCoeffSampleFract32; // Sample-by-sample smoothing coefficient for the output gain adjustment.  Set via smoothingTime.
    fract32            smoothingCoeffBlockFract32; // Block-by-block smoothing coefficient for the RMS measurement. Set via smoothingTime.
    fract32            targetGainFract32;   // Target gain of the smoothing operation.
    fract32            energyFract32;       // Smoothed energy measurement.
    fract32            oneOverNumSamplesFract32; // 1 divided by the number of samples in the input pin.  Used internally by the algorithm in order to save a divide operation.
    fract32            oneOverSlopeFract32; // Used by the processing function to compute the amount of cut/boost.  Equal to 1-1/ratio.
    FLOAT32            oneOverSlope;        // Used by the processing function to compute the amount of cut/boost.  Equal to 1-1/ratio.
    FLOAT32            smoothingCoeffSample; // Sample-by-sample smoothing coefficient for the output gain adjustment.  Set via smoothingTime.
    FLOAT32            smoothingCoeffBlock; // Block-by-block smoothing coefficient for the RMS measurement. Set via smoothingTime.
    FLOAT32            recoveryRateUp;      // Recovery rate coefficient when increasing the gain (it is always >= 1)
    FLOAT32            recoveryRateDown;    // Recovery rate coefficient when decreasing the gain (it is always <= 1)
    FLOAT32            targetGain;          // Target gain of the smoothing operation.
    FLOAT32            energy;              // Smoothed energy measurement.
    FLOAT32            oneOverNumSamples;   // 1 divided by the number of samples in the input pin.  Used internally by the algorithm in order to save a divide operation.
    fract32            targetLevelFract32;  // Target audio level
    fract32            maxGainFract32;      // Maximum gain of the AGC
    fract32            maxAttenuationFract32; // Maximum attenuation of the AGC
    fract32            activationThresholdFract32; // Activation threshold of the AGC.  The AGC stops updating its gain when the instantaneous input level is below this value
    fract32            recoveryRateUpFract32; // Recovery rate coefficient when increasing the gain (it is always >= 1)
    fract32            recoveryRateDownFract32; // Recovery rate coefficient when decreasing the gain (it is always <= 1)
    fract32            currentGainFract32;  // Instantaneous gain of the smoothing operation.
    
} awe_modAGCCoreFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAGCCoreFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modAGCCoreFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_AGCCOREFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modAGCCoreFract32Process(void *pInstance);

UINT32 awe_modAGCCoreFract32Set(void *pInstance, UINT32 mask);
 
UINT32 awe_modAGCCoreFract32Get(void *pInstance, UINT32 mask);

void awe_modAGCCoreFract32Bypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_AGCCOREFRACT32_H

/**
 * @}
 *
 * End of file.
 */
