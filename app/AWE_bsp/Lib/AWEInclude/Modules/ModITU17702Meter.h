/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*  ModITU17702Meter.h
****************************************************************************
*
*         Description:  Loudness meter following the ITU 1770-2 standard
*
*         Copyright:	DSP Concepts, Inc., 2007 - 2012
*                       568 E. Weddell Drive, Suite 3
*                       Sunnyvale, CA 94089
*
***************************************************************************/

/**
 * @addtogroup Modules
 * @{
 */

/**
 * @file
 * @brief Loudness meter following the ITU 1770-2 standard
 */

#ifndef _MOD_ITU17702METER_H
#define _MOD_ITU17702METER_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ITU17702Meter_loudnessMode 0x00000100
#define MASK_ITU17702Meter_momentaryPeriod 0x00000200
#define MASK_ITU17702Meter_overlapBlocks 0x00000400
#define MASK_ITU17702Meter_STIntTime 0x00000800
#define MASK_ITU17702Meter_enableGating 0x00001000
#define MASK_ITU17702Meter_safetyGateLevel 0x00002000
#define MASK_ITU17702Meter_relativeGateLevel 0x00004000
#define MASK_ITU17702Meter_isReadyMomentary 0x00008000
#define MASK_ITU17702Meter_isReadyST 0x00010000
#define MASK_ITU17702Meter_pauseST 0x00020000
#define MASK_ITU17702Meter_resetST 0x00040000
#define MASK_ITU17702Meter_isReadyInf 0x00080000
#define MASK_ITU17702Meter_pauseInf 0x00100000
#define MASK_ITU17702Meter_resetInf 0x00200000
#define MASK_ITU17702Meter_isReadyLR 0x00400000
#define MASK_ITU17702Meter_pauseLR 0x00800000
#define MASK_ITU17702Meter_resetLR 0x01000000
#define MASK_ITU17702Meter_momentaryLoudness 0x02000000
#define MASK_ITU17702Meter_STLoudness 0x04000000
#define MASK_ITU17702Meter_infLoudness 0x08000000
#define MASK_ITU17702Meter_loudnessRange 0x10000000
#define MASK_ITU17702Meter_relativeGateLin 0x20000000
#define MASK_ITU17702Meter_safetyGateLin 0x40000000
#define MASK_ITU17702Meter_numSamplesReceived 0x80000000
#define MASK_ITU17702Meter_numSTBlocksProcessed 0x80000000
#define MASK_ITU17702Meter_numInfBlocksProcessed 0x80000000
#define MASK_ITU17702Meter_STStateLength 0x80000000
#define MASK_ITU17702Meter_numSTBlocksPerSec 0x80000000
#define MASK_ITU17702Meter_numSamplesPerMeasure 0x80000000
#define MASK_ITU17702Meter_energySum 0x80000000
#define MASK_ITU17702Meter_tauST 0x80000000
#define MASK_ITU17702Meter_tauInf 0x80000000
#define MASK_ITU17702Meter_STStateIndex 0x80000000
#define MASK_ITU17702Meter_last4 0x80000000
#define MASK_ITU17702Meter_STState 0x80000000
#define MASK_ITU17702Meter_hist 0x80000000
#define MASK_ITU17702Meter_histLR 0x80000000
#define OFFSET_ITU17702Meter_loudnessMode 0x00000008
#define OFFSET_ITU17702Meter_momentaryPeriod 0x00000009
#define OFFSET_ITU17702Meter_overlapBlocks 0x0000000A
#define OFFSET_ITU17702Meter_STIntTime 0x0000000B
#define OFFSET_ITU17702Meter_enableGating 0x0000000C
#define OFFSET_ITU17702Meter_safetyGateLevel 0x0000000D
#define OFFSET_ITU17702Meter_relativeGateLevel 0x0000000E
#define OFFSET_ITU17702Meter_isReadyMomentary 0x0000000F
#define OFFSET_ITU17702Meter_isReadyST 0x00000010
#define OFFSET_ITU17702Meter_pauseST 0x00000011
#define OFFSET_ITU17702Meter_resetST 0x00000012
#define OFFSET_ITU17702Meter_isReadyInf 0x00000013
#define OFFSET_ITU17702Meter_pauseInf 0x00000014
#define OFFSET_ITU17702Meter_resetInf 0x00000015
#define OFFSET_ITU17702Meter_isReadyLR 0x00000016
#define OFFSET_ITU17702Meter_pauseLR 0x00000017
#define OFFSET_ITU17702Meter_resetLR 0x00000018
#define OFFSET_ITU17702Meter_momentaryLoudness 0x00000019
#define OFFSET_ITU17702Meter_STLoudness 0x0000001A
#define OFFSET_ITU17702Meter_infLoudness 0x0000001B
#define OFFSET_ITU17702Meter_loudnessRange 0x0000001C
#define OFFSET_ITU17702Meter_relativeGateLin 0x0000001D
#define OFFSET_ITU17702Meter_safetyGateLin 0x0000001E
#define OFFSET_ITU17702Meter_numSamplesReceived 0x0000001F
#define OFFSET_ITU17702Meter_numSTBlocksProcessed 0x00000020
#define OFFSET_ITU17702Meter_numInfBlocksProcessed 0x00000021
#define OFFSET_ITU17702Meter_STStateLength 0x00000022
#define OFFSET_ITU17702Meter_numSTBlocksPerSec 0x00000023
#define OFFSET_ITU17702Meter_numSamplesPerMeasure 0x00000024
#define OFFSET_ITU17702Meter_energySum 0x00000025
#define OFFSET_ITU17702Meter_tauST 0x00000026
#define OFFSET_ITU17702Meter_tauInf 0x00000027
#define OFFSET_ITU17702Meter_STStateIndex 0x00000028
#define OFFSET_ITU17702Meter_last4 0x00000029
#define OFFSET_ITU17702Meter_STState 0x0000002A
#define OFFSET_ITU17702Meter_hist 0x0000002B
#define OFFSET_ITU17702Meter_histLR 0x0000002C

#define CLASSID_ITU17702METER (CLASS_ID_MODBASE + 5014)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modITU17702MeterInstance
{
    ModuleInstanceDescriptor instance;
    int                loudnessMode;        // Mode of operation for different regional standards
    float              momentaryPeriod;     // Integration period for momentary processesing
    int                overlapBlocks;       // Number of overlapping momentary periods to accumulate for each  block of short term integration
    float              STIntTime;           // Configures the finite time integrator
    int                enableGating;        // Discard blocks less than the gate levels
    float              safetyGateLevel;     // Absolute cutoff in dB below which blocks are discarded
    float              relativeGateLevel;   // Blocks this amount in dB lower than the average loudness are discarded in the second stage
    int                isReadyMomentary;    // Is the first overlap measurement ready (valid)?
    int                isReadyST;           // Is the finite time integrator ready (do we have enough data in the state buffer)?
    int                pauseST;             // Pauses the short term loudness calculation
    int                resetST;             // Resets the short term loudness computation
    int                isReadyInf;          // Is the infinite time integrator ready (do we have at least one sample of data in the buffer?)
    int                pauseInf;            // Pauses the infinite time loudness calculation
    int                resetInf;            // Resets the infinite time loudness computation
    int                isReadyLR;           // Is the loudness range measurement ready?
    int                pauseLR;             // Pauses the loudness range calculation
    int                resetLR;             // Resets the loudness range computation
    float              momentaryLoudness;   // Computed loudness for the last ST block
    float              STLoudness;          // Computed short term loudness over the integration time
    float              infLoudness;         // Computed loudness over all time
    float              loudnessRange;       // Loudness range
    float              relativeGateLin;     // Linear scaling of relative gate level
    float              safetyGateLin;       // Linear scaling of safety gate level
    int                numSamplesReceived;  // Number of samples received for the current momentary block
    int                numSTBlocksProcessed; // Number of momentary blocks processed for ST calculations
    int                numInfBlocksProcessed; // Number of momentary blocks processed for Inf calculations
    int                STStateLength;       // Holds the length of the energy state buffer
    int                numSTBlocksPerSec;   // Number of short term blocks per second
    int                numSamplesPerMeasure; // Number of samples per 100 msec RMS measurement
    float              energySum;           // Used to sum energy in momentary of data
    float              tauST;               // Internal threshold calculated as the first stage of short term processing
    float              tauInf;              // Internal threshold calculated as the first stage of infinite time processing
    int                STStateIndex;        // Points to the oldest variable in the state buffer
    float*             last4;               // Holds samples of the momentary period energy.  Used to compute the overlap blocks for loudness samples
    float*             STState;             // Holds samples of the momentary energy.  Used to compute the short term loudness
    int*               hist;                // Holds the histogram of dB values.  From -100 to 0 dB in 0.1 dB steps
    int*               histLR;              // Holds the histogram of dB values.  From -100 to 0 dB in 0.1 dB steps
} awe_modITU17702MeterInstance;

/* By default the class object is included and this is required for dynamic
 * instantiation.  When doing static code (define AWE_STATIC_CODE) you can save
 * a little bit of memory by eliminating class objects.  However, you lose the
 * ability to change the module status. */

#if !defined(NOREDEF)
extern const ModClassModule awe_modITU17702MeterClass;
#endif // #ifndef AWE_NO_CLASS_OBJECTS

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modITU17702MeterConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modITU17702MeterProcess(void *pInstance);

#ifndef AWE_NO_SETGET_FUNCTIONS
UINT32 awe_modITU17702MeterSet(void *pInstance, UINT32 mask);
#endif
 
#ifndef AWE_NO_SETGET_FUNCTIONS
UINT32 awe_modITU17702MeterGet(void *pInstance, UINT32 mask);
#endif



#ifdef __cplusplus
}
#endif


#endif // _MOD_ITU17702METER_H

/**
 * @}
 *
 * End of file.
 */
