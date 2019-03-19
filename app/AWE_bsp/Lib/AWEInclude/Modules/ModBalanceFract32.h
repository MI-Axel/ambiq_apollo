/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBalanceFract32.h
****************************************************************************
*
*     Description:  Smooth Stereo Balance Module
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
 * @brief Smooth Stereo Balance Module
 */

#ifndef _MOD_BALANCEFRACT32_H
#define _MOD_BALANCEFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_BalanceFract32_balance 0x00000100
#define MASK_BalanceFract32_smoothingTime 0x00000200
#define MASK_BalanceFract32_currentGainLFract32 0x00000400
#define MASK_BalanceFract32_currentGainRFract32 0x00000800
#define MASK_BalanceFract32_smoothingCoeff 0x00001000
#define MASK_BalanceFract32_gainLFract32 0x00002000
#define MASK_BalanceFract32_gainRFract32 0x00004000
#define OFFSET_BalanceFract32_balance 0x00000008
#define OFFSET_BalanceFract32_smoothingTime 0x00000009
#define OFFSET_BalanceFract32_currentGainLFract32 0x0000000A
#define OFFSET_BalanceFract32_currentGainRFract32 0x0000000B
#define OFFSET_BalanceFract32_smoothingCoeff 0x0000000C
#define OFFSET_BalanceFract32_gainLFract32 0x0000000D
#define OFFSET_BalanceFract32_gainRFract32 0x0000000E

#define CLASSID_BALANCEFRACT32 (CLASS_ID_MODBASE + 136)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBalanceFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            balance;             // Left/Right Balance
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    fract32            currentGainLFract32; // Instantaneous gain applied to left channel.  This is also the starting gain of the left channel.
    fract32            currentGainRFract32; // Instantaneous gain applied to right channel.  This is also the starting gain of the right channel.
    fract32            smoothingCoeff;      // Smoothing coefficient
    fract32            gainLFract32;        // Target gain left channel
    fract32            gainRFract32;        // Target gain right channel
    
} awe_modBalanceFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBalanceFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modBalanceFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_BALANCEFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modBalanceFract32Process(void *pInstance);

UINT32 awe_modBalanceFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BALANCEFRACT32_H

/**
 * @}
 *
 * End of file.
 */
