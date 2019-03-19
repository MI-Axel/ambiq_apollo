/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModVolumeControlSS.h
****************************************************************************
*
*     Description:  Volume control with Fletcher-Munson loudness compensation using State Space implementation
*
*     Copyright:    DSP Concepts, Inc, 2007 - 2015
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
 * @brief Volume control with Fletcher-Munson loudness compensation using State Space implementation
 */

#ifndef _MOD_VOLUMECONTROLSS_H
#define _MOD_VOLUMECONTROLSS_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModBiquadSmoothedSS.h"

#define MASK_VolumeControlSS_gain 0x00000100
#define MASK_VolumeControlSS_centerFreq 0x00000200
#define MASK_VolumeControlSS_c2 0x00000400
#define MASK_VolumeControlSS_c1 0x00000800
#define MASK_VolumeControlSS_c0 0x00001000
#define MASK_VolumeControlSS_b0_LPF 0x00002000
#define MASK_VolumeControlSS_b1_LPF 0x00004000
#define MASK_VolumeControlSS_b2_LPF 0x00008000
#define MASK_VolumeControlSS_a1 0x00010000
#define MASK_VolumeControlSS_a2 0x00020000
#define OFFSET_VolumeControlSS_gain 0x00000008
#define OFFSET_VolumeControlSS_centerFreq 0x00000009
#define OFFSET_VolumeControlSS_c2 0x0000000A
#define OFFSET_VolumeControlSS_c1 0x0000000B
#define OFFSET_VolumeControlSS_c0 0x0000000C
#define OFFSET_VolumeControlSS_b0_LPF 0x0000000D
#define OFFSET_VolumeControlSS_b1_LPF 0x0000000E
#define OFFSET_VolumeControlSS_b2_LPF 0x0000000F
#define OFFSET_VolumeControlSS_a1 0x00000010
#define OFFSET_VolumeControlSS_a2 0x00000011

#define CLASSID_VOLUMECONTROLSS (CLASS_ID_MODBASE + 3206)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modVolumeControlSSInstance
{
    ModuleInstanceDescriptor instance;
    float              gain;                // Gain through the volume control, in dB.
    float              centerFreq;          // Center frequency of the low frequency resonance, in Hz.
    float              c2;                  // X^2 coefficient.
    float              c1;                  // X^1 coefficient.
    float              c0;                  // X^0 coefficient.
    float              b0_LPF;              // First numerator coefficient.
    float              b1_LPF;              // Second numerator coefficient.
    float              b2_LPF;              // Third numerator coefficient.
    float              a1;                  // First denominator coefficient.
    float              a2;                  // Second denominator coefficient.
        awe_modBiquadSmoothedSSInstance    *mixerFilt;          // 2nd order smoothly updating IIR filter with State Space implementation
} awe_modVolumeControlSSInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modVolumeControlSSClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modVolumeControlSSConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modVolumeControlSSProcess(void *pInstance);

UINT32 awe_modVolumeControlSSSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_VOLUMECONTROLSS_H

/**
 * @}
 *
 * End of file.
 */
