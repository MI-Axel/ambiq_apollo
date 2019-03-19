/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModWetDry.h
****************************************************************************
*
*     Description:  2-input x 1-output smoothly varying mixer
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
 * @brief 2-input x 1-output smoothly varying mixer
 */

#ifndef _MOD_WETDRY_H
#define _MOD_WETDRY_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_WetDry_mix 0x00000100
#define MASK_WetDry_mixType 0x00000200
#define MASK_WetDry_smoothingTime 0x00000400
#define MASK_WetDry_currentGain1 0x00000800
#define MASK_WetDry_currentGain2 0x00001000
#define MASK_WetDry_smoothingCoeff 0x00002000
#define OFFSET_WetDry_mix 0x00000008
#define OFFSET_WetDry_mixType 0x00000009
#define OFFSET_WetDry_smoothingTime 0x0000000A
#define OFFSET_WetDry_currentGain1 0x0000000B
#define OFFSET_WetDry_currentGain2 0x0000000C
#define OFFSET_WetDry_smoothingCoeff 0x0000000D

#define CLASSID_WETDRY (CLASS_ID_MODBASE + 95)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modWetDryInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            mix;                 // Linear mixing level.
    INT32              mixType;             // Selects the type of mixing that is implemented by the module: ConstantAmplitude=0, ConstantEnergy=1
    FLOAT32            smoothingTime;       // Time constant of the smoothing process, in msec.
    FLOAT32            currentGain1;        // Instanteous gain being applied to input pin1.  This is an internal variable used in the smoothing process
    FLOAT32            currentGain2;        // Instanteous gain being applied to input pin2.  This is an internal variable used in the smoothing process
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    
} awe_modWetDryInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modWetDryClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modWetDryConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_WETDRY, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modWetDryProcess(void *pInstance);

UINT32 awe_modWetDrySet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_WETDRY_H

/**
 * @}
 *
 * End of file.
 */
