/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModInvertN.h
****************************************************************************
*
*     Description:  Phase invert module
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
 * @brief Phase invert module
 */

#ifndef _MOD_INVERTN_H
#define _MOD_INVERTN_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_InvertN_numControls 0x00000100
#define MASK_InvertN_smoothingTime 0x00000200
#define MASK_InvertN_smoothingCoeff 0x00000400
#define MASK_InvertN_isInverted 0x00000800
#define MASK_InvertN_currentGain 0x00001000
#define MASK_InvertN_gain 0x00002000
#define OFFSET_InvertN_numControls 0x00000008
#define OFFSET_InvertN_smoothingTime 0x00000009
#define OFFSET_InvertN_smoothingCoeff 0x0000000A
#define OFFSET_InvertN_isInverted 0x0000000B
#define OFFSET_InvertN_currentGain 0x0000000C
#define OFFSET_InvertN_gain 0x0000000D

#define CLASSID_INVERTN (CLASS_ID_MODBASE + 1291)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modInvertNInstance
{
    ModuleInstanceDescriptor instance;
    INT32              numControls;         // Number of individual invert controls
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    INT32*             isInverted;          // Boolean that specifies whether the signal is inverted (=1) or not (=0). One per each pin.
    FLOAT32*           currentGain;         // Instantaneous gain applied by the module.  This is also the starting gain of the module.
    FLOAT32*           gain;                // Target gain.
} awe_modInvertNInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modInvertNClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modInvertNConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modInvertNProcess(void *pInstance);

UINT32 awe_modInvertNSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_INVERTN_H

/**
 * @}
 *
 * End of file.
 */
