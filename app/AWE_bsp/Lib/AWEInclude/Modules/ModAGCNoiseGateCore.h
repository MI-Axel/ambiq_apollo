/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAGCNoiseGateCore.h
****************************************************************************
*
*     Description:  Gain computer used to realize noise gates
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
 * @brief Gain computer used to realize noise gates
 */

#ifndef _MOD_AGCNOISEGATECORE_H
#define _MOD_AGCNOISEGATECORE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_AGCNoiseGateCore_threshold 0x00000100
#define MASK_AGCNoiseGateCore_delta 0x00000200
#define MASK_AGCNoiseGateCore_attackTime 0x00000400
#define MASK_AGCNoiseGateCore_releaseTime 0x00000800
#define MASK_AGCNoiseGateCore_crossfadeTime 0x00001000
#define MASK_AGCNoiseGateCore_isMuted 0x00002000
#define MASK_AGCNoiseGateCore_lowerThreshold 0x00004000
#define MASK_AGCNoiseGateCore_upperThreshold 0x00008000
#define MASK_AGCNoiseGateCore_attackCoeffBlock 0x00010000
#define MASK_AGCNoiseGateCore_releaseCoeffBlock 0x00020000
#define MASK_AGCNoiseGateCore_smoothingCoeffOutput 0x00040000
#define MASK_AGCNoiseGateCore_targetGain 0x00080000
#define MASK_AGCNoiseGateCore_currentGain 0x00100000
#define MASK_AGCNoiseGateCore_energy 0x00200000
#define MASK_AGCNoiseGateCore_oneOverNumSamples 0x00400000
#define OFFSET_AGCNoiseGateCore_threshold 0x00000008
#define OFFSET_AGCNoiseGateCore_delta 0x00000009
#define OFFSET_AGCNoiseGateCore_attackTime 0x0000000A
#define OFFSET_AGCNoiseGateCore_releaseTime 0x0000000B
#define OFFSET_AGCNoiseGateCore_crossfadeTime 0x0000000C
#define OFFSET_AGCNoiseGateCore_isMuted 0x0000000D
#define OFFSET_AGCNoiseGateCore_lowerThreshold 0x0000000E
#define OFFSET_AGCNoiseGateCore_upperThreshold 0x0000000F
#define OFFSET_AGCNoiseGateCore_attackCoeffBlock 0x00000010
#define OFFSET_AGCNoiseGateCore_releaseCoeffBlock 0x00000011
#define OFFSET_AGCNoiseGateCore_smoothingCoeffOutput 0x00000012
#define OFFSET_AGCNoiseGateCore_targetGain 0x00000013
#define OFFSET_AGCNoiseGateCore_currentGain 0x00000014
#define OFFSET_AGCNoiseGateCore_energy 0x00000015
#define OFFSET_AGCNoiseGateCore_oneOverNumSamples 0x00000016

#define CLASSID_AGCNOISEGATECORE (CLASS_ID_MODBASE + 3)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAGCNoiseGateCoreInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            threshold;           // Activation threshold of the noise gate, in decibels. When the RMS gain dips below (threshold-delta), the output gain will be ramped to zero (-inf dB).
    FLOAT32            delta;               // Hysterisis width of the noise gate, in decibels. When the RMS gain dips below the dB value of (threshold-delta), the output gain will be ramped to zero (-inf dB). The output gain will return to 0 dB when the input RMS value rises above (threshold+delta).
    FLOAT32            attackTime;          // Attack time of the noise gate. This controls the RMS smoothing interval when the input is increasing in volume, and the time constant of the smoothly updating gain
    FLOAT32            releaseTime;         // Decay time of the noise gate. This controls the RMS smoothing interval when the input is decreasing in volume, and the time constant of the smoothly updating gain
    FLOAT32            crossfadeTime;       // Response time of the noise gate. This controls the time constant of the smoothly updating output gain
    INT32              isMuted;             // Boolean that determines whether the output is muted (isMuted=1) or active (isMuted=0).
    FLOAT32            lowerThreshold;      // Lower activation threshold of the noise gate, in linear units. Computed as undb10f(threshold-delta).
    FLOAT32            upperThreshold;      // Upper activation threshold of the noise gate, in linear units. Computed as undb10f(threshold-delta).
    FLOAT32            attackCoeffBlock;    // Block-by-block smoothing coefficient for the attack portion of the RMS measurement. Set via smoothingTime.
    FLOAT32            releaseCoeffBlock;   // Block-by-block smoothing coefficient for the release portion of the RMS measurement. Set via smoothingTime.
    FLOAT32            smoothingCoeffOutput; // Sample-by-sample smoothing coefficient for the output gain adjustment. Set via crossfadeTime.
    FLOAT32            targetGain;          // Target gain of the smoothing operation.
    FLOAT32            currentGain;         // Instanteous gain of the smoothing operation.
    FLOAT32            energy;              // Smoothed energy measurement.
    FLOAT32            oneOverNumSamples;   // 1 divided by the number of samples in the input pin. Used internally by the algorithm in order to save a divide operation.
    
} awe_modAGCNoiseGateCoreInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAGCNoiseGateCoreClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modAGCNoiseGateCoreConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_AGCNOISEGATECORE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modAGCNoiseGateCoreProcess(void *pInstance);

UINT32 awe_modAGCNoiseGateCoreSet(void *pInstance, UINT32 mask);
 

void awe_modAGCNoiseGateCoreBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_AGCNOISEGATECORE_H

/**
 * @}
 *
 * End of file.
 */
