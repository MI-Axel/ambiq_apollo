/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSCNRv1.h
****************************************************************************
*
*     Description:  DSP Concepts proprietary Single-Channel Noise Reducer.  Version 1.
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
 * @brief DSP Concepts proprietary Single-Channel Noise Reducer.  Version 1.
 */

#ifndef _MOD_SCNRV1_H
#define _MOD_SCNRV1_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SCNRv1_minGaindB 0x00000100
#define MASK_SCNRv1_noiseAdjust 0x00000200
#define MASK_SCNRv1_minGain 0x00000400
#define MASK_SCNRv1_attackTime 0x00000800
#define MASK_SCNRv1_attackCoeff 0x00001000
#define MASK_SCNRv1_freq1 0x00002000
#define MASK_SCNRv1_b0_1 0x00004000
#define MASK_SCNRv1_b1_1 0x00008000
#define MASK_SCNRv1_a1_1 0x00010000
#define MASK_SCNRv1_freq2 0x00020000
#define MASK_SCNRv1_b0_2 0x00040000
#define MASK_SCNRv1_b1_2 0x00080000
#define MASK_SCNRv1_a1_2 0x00100000
#define MASK_SCNRv1_ppriorTimeConst 0x00200000
#define MASK_SCNRv1_ppriorEta 0x00400000
#define MASK_SCNRv1_pxState 0x00800000
#define MASK_SCNRv1_pshatState 0x01000000
#define MASK_SCNRv1_gainState 0x02000000
#define MASK_SCNRv1_pnEnvState 0x04000000
#define MASK_SCNRv1_prevPsHat 0x08000000
#define OFFSET_SCNRv1_minGaindB 0x00000008
#define OFFSET_SCNRv1_noiseAdjust 0x00000009
#define OFFSET_SCNRv1_minGain 0x0000000A
#define OFFSET_SCNRv1_attackTime 0x0000000B
#define OFFSET_SCNRv1_attackCoeff 0x0000000C
#define OFFSET_SCNRv1_freq1 0x0000000D
#define OFFSET_SCNRv1_b0_1 0x0000000E
#define OFFSET_SCNRv1_b1_1 0x0000000F
#define OFFSET_SCNRv1_a1_1 0x00000010
#define OFFSET_SCNRv1_freq2 0x00000011
#define OFFSET_SCNRv1_b0_2 0x00000012
#define OFFSET_SCNRv1_b1_2 0x00000013
#define OFFSET_SCNRv1_a1_2 0x00000014
#define OFFSET_SCNRv1_ppriorTimeConst 0x00000015
#define OFFSET_SCNRv1_ppriorEta 0x00000016
#define OFFSET_SCNRv1_pxState 0x00000017
#define OFFSET_SCNRv1_pshatState 0x00000018
#define OFFSET_SCNRv1_gainState 0x00000019
#define OFFSET_SCNRv1_pnEnvState 0x0000001A
#define OFFSET_SCNRv1_prevPsHat 0x0000001B

#define CLASSID_SCNRV1 (CLASS_ID_MODBASE + 15300)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSCNRv1Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            minGaindB;           // the minimum gain to be applied in dB
    FLOAT32            noiseAdjust;         // noise level adjustment.
    FLOAT32            minGain;             // the minimum gain to be applied in linear.
    FLOAT32            attackTime;          // Internal coefficient realizing the attack time.
    FLOAT32            attackCoeff;         // Internal coefficient realizing the attack time.
    FLOAT32            freq1;               // Internal coefficient realizing the attack time.
    FLOAT32            b0_1;                // Desired first numerator coefficient.
    FLOAT32            b1_1;                // Desired second numerator coefficient.
    FLOAT32            a1_1;                // Desired second denominator coefficient.
    FLOAT32            freq2;               // Internal coefficient realizing the attack time.
    FLOAT32            b0_2;                // Desired first numerator coefficient.
    FLOAT32            b1_2;                // Desired second numerator coefficient.
    FLOAT32            a1_2;                // Desired second denominator coefficient.
    FLOAT32            ppriorTimeConst;     // Internal coefficient realizing the attack time.
    FLOAT32            ppriorEta;           // Internal coefficient realizing the attack time.
    FLOAT32*           pxState;             // Sb smoothing state for Px computation.
    FLOAT32*           pshatState;          // Sb smoothing state for Ps_hat computation.
    FLOAT32*           gainState;           // Sb smoothing state for gain computation.
    FLOAT32*           pnEnvState;          // Attack release env state for Pn computation.
    FLOAT32*           prevPsHat;           // Feedback memory.
} awe_modSCNRv1Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSCNRv1Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modSCNRv1Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modSCNRv1Process(void *pInstance);

UINT32 awe_modSCNRv1Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SCNRV1_H

/**
 * @}
 *
 * End of file.
 */
