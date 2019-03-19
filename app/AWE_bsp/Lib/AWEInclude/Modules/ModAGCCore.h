/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAGCCore.h
****************************************************************************
*
*     Description:  Slowly varying RMS based gain computer
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
 * @brief Slowly varying RMS based gain computer
 */

#ifndef _MOD_AGCCORE_H
#define _MOD_AGCCORE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_AGCCore_targetLevel 0x00000100
#define MASK_AGCCore_maxAttenuation 0x00000200
#define MASK_AGCCore_maxGain 0x00000400
#define MASK_AGCCore_ratio 0x00000800
#define MASK_AGCCore_activationThreshold 0x00001000
#define MASK_AGCCore_smoothingTime 0x00002000
#define MASK_AGCCore_enableRecovery 0x00004000
#define MASK_AGCCore_recoveryRate 0x00008000
#define MASK_AGCCore_currentGain 0x00010000
#define MASK_AGCCore_oneOverSlope 0x00020000
#define MASK_AGCCore_smoothingCoeffSample 0x00040000
#define MASK_AGCCore_smoothingCoeffBlock 0x00080000
#define MASK_AGCCore_recoveryRateUp 0x00100000
#define MASK_AGCCore_recoveryRateDown 0x00200000
#define MASK_AGCCore_targetGain 0x00400000
#define MASK_AGCCore_energy 0x00800000
#define MASK_AGCCore_oneOverNumSamples 0x01000000
#define OFFSET_AGCCore_targetLevel 0x00000008
#define OFFSET_AGCCore_maxAttenuation 0x00000009
#define OFFSET_AGCCore_maxGain 0x0000000A
#define OFFSET_AGCCore_ratio 0x0000000B
#define OFFSET_AGCCore_activationThreshold 0x0000000C
#define OFFSET_AGCCore_smoothingTime 0x0000000D
#define OFFSET_AGCCore_enableRecovery 0x0000000E
#define OFFSET_AGCCore_recoveryRate 0x0000000F
#define OFFSET_AGCCore_currentGain 0x00000010
#define OFFSET_AGCCore_oneOverSlope 0x00000011
#define OFFSET_AGCCore_smoothingCoeffSample 0x00000012
#define OFFSET_AGCCore_smoothingCoeffBlock 0x00000013
#define OFFSET_AGCCore_recoveryRateUp 0x00000014
#define OFFSET_AGCCore_recoveryRateDown 0x00000015
#define OFFSET_AGCCore_targetGain 0x00000016
#define OFFSET_AGCCore_energy 0x00000017
#define OFFSET_AGCCore_oneOverNumSamples 0x00000018

#define CLASSID_AGCCORE (CLASS_ID_MODBASE + 2)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAGCCoreInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            targetLevel;         // Target audio level.
    FLOAT32            maxAttenuation;      // Maximum attenuation of the AGC.
    FLOAT32            maxGain;             // Maximum gain of the AGC.
    FLOAT32            ratio;               // Slope of the output attenuation when the signal is above threshold.
    FLOAT32            activationThreshold; // Activation threshold of the AGC. The AGC stops updating its gain when the instantaneous input level is below this value.
    FLOAT32            smoothingTime;       // Response time of the AGC. This controls the RMS smoothing interval and the time constant of the smoothly updating gain.
    INT32              enableRecovery;      // Boolean which enables the AGC's gain recovery. If enabled, the AGC slows returns 0 dB gain when the input is below the activation threshold.
    FLOAT32            recoveryRate;        // Rate at which the gain is adjusted when the input is below the activation threshold.
    FLOAT32            currentGain;         // Instantaneous gain of the smoothing operation.
    FLOAT32            oneOverSlope;        // Used by the processing function to compute the amount of cut/boost. Equal to 1-1/ratio.
    FLOAT32            smoothingCoeffSample; // Sample-by-sample smoothing coefficient for the output gain adjustment. Set via smoothingTime.
    FLOAT32            smoothingCoeffBlock; // Block-by-block smoothing coefficient for the RMS measurement. Set via smoothingTime.
    FLOAT32            recoveryRateUp;      // Recovery rate coefficient when increasing the gain (it is always >= 1).
    FLOAT32            recoveryRateDown;    // Recovery rate coefficient when decreasing the gain (it is always <= 1).
    FLOAT32            targetGain;          // Target gain of the smoothing operation.
    FLOAT32            energy;              // Smoothed energy measurement.
    FLOAT32            oneOverNumSamples;   // 1 divided by the number of samples in the input pin. Used internally by the algorithm in order to save a divide operation.
    
} awe_modAGCCoreInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAGCCoreClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modAGCCoreConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_AGCCORE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modAGCCoreProcess(void *pInstance);

UINT32 awe_modAGCCoreSet(void *pInstance, UINT32 mask);
 

void awe_modAGCCoreBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_AGCCORE_H

/**
 * @}
 *
 * End of file.
 */
