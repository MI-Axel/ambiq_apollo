/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSMixer2x1.h
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

#ifndef _MOD_SMIXER2X1_H
#define _MOD_SMIXER2X1_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SMixer2x1_gain1 0x00000100
#define MASK_SMixer2x1_gain2 0x00000200
#define MASK_SMixer2x1_smoothingTime 0x00000400
#define MASK_SMixer2x1_currentGain1 0x00000800
#define MASK_SMixer2x1_currentGain2 0x00001000
#define MASK_SMixer2x1_smoothingCoeff 0x00002000
#define OFFSET_SMixer2x1_gain1 0x00000008
#define OFFSET_SMixer2x1_gain2 0x00000009
#define OFFSET_SMixer2x1_smoothingTime 0x0000000A
#define OFFSET_SMixer2x1_currentGain1 0x0000000B
#define OFFSET_SMixer2x1_currentGain2 0x0000000C
#define OFFSET_SMixer2x1_smoothingCoeff 0x0000000D

#define CLASSID_SMIXER2X1 (CLASS_ID_MODBASE + 94)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSMixer2x1Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            gain1;               // Desired gain applied to first input channel.
    FLOAT32            gain2;               // Desired gain applied to second input channel.
    FLOAT32            smoothingTime;       // Time constant of the smoothing process.
    FLOAT32            currentGain1;        // Instantaneous gain for the first input channel.
    FLOAT32            currentGain2;        // Instantaneous gain for the second input channel.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    
} awe_modSMixer2x1Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSMixer2x1Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSMixer2x1Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SMIXER2X1, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSMixer2x1Process(void *pInstance);

UINT32 awe_modSMixer2x1Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SMIXER2X1_H

/**
 * @}
 *
 * End of file.
 */
