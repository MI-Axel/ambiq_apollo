/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModVolumeControlHP.h
****************************************************************************
*
*     Description:  Volume control with Fletcher-Munson loudness compensation using High Precision implementation
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
 * @brief Volume control with Fletcher-Munson loudness compensation using High Precision implementation
 */

#ifndef _MOD_VOLUMECONTROLHP_H
#define _MOD_VOLUMECONTROLHP_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModBiquadSmoothedHP.h"

#define MASK_VolumeControlHP_gain 0x00000100
#define MASK_VolumeControlHP_centerFreq 0x00000200
#define MASK_VolumeControlHP_c2 0x00000400
#define MASK_VolumeControlHP_c1 0x00000800
#define MASK_VolumeControlHP_c0 0x00001000
#define MASK_VolumeControlHP_b0_LPF 0x00002000
#define MASK_VolumeControlHP_b1_LPF 0x00004000
#define MASK_VolumeControlHP_b2_LPF 0x00008000
#define MASK_VolumeControlHP_a1 0x00010000
#define MASK_VolumeControlHP_a2 0x00020000
#define OFFSET_VolumeControlHP_gain 0x00000008
#define OFFSET_VolumeControlHP_centerFreq 0x00000009
#define OFFSET_VolumeControlHP_c2 0x0000000A
#define OFFSET_VolumeControlHP_c1 0x0000000B
#define OFFSET_VolumeControlHP_c0 0x0000000C
#define OFFSET_VolumeControlHP_b0_LPF 0x0000000D
#define OFFSET_VolumeControlHP_b1_LPF 0x0000000E
#define OFFSET_VolumeControlHP_b2_LPF 0x0000000F
#define OFFSET_VolumeControlHP_a1 0x00000010
#define OFFSET_VolumeControlHP_a2 0x00000011

#define CLASSID_VOLUMECONTROLHP (CLASS_ID_MODBASE + 1352)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modVolumeControlHPInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            gain;                // Gain through the volume control, in dB.
    FLOAT32            centerFreq;          // Center frequency of the low frequency resonance, in Hz.
    FLOAT32            c2;                  // X^2 coefficient.
    FLOAT32            c1;                  // X^1 coefficient.
    FLOAT32            c0;                  // X^0 coefficient.
    FLOAT32            b0_LPF;              // First numerator coefficient.
    FLOAT32            b1_LPF;              // Second numerator coefficient.
    FLOAT32            b2_LPF;              // Third numerator coefficient.
    FLOAT32            a1;                  // First denominator coefficient.
    FLOAT32            a2;                  // Second denominator coefficient.
        awe_modBiquadSmoothedHPInstance    *mixerFilt;          // 2nd order smoothly updating IIR filter with high precision implementation
} awe_modVolumeControlHPInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modVolumeControlHPClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modVolumeControlHPConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modVolumeControlHPProcess(void *pInstance);

UINT32 awe_modVolumeControlHPSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_VOLUMECONTROLHP_H

/**
 * @}
 *
 * End of file.
 */
