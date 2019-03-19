/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBalance.h
****************************************************************************
*
*     Description:  Left-right balance control
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
 * @brief Left-right balance control
 */

#ifndef _MOD_BALANCE_H
#define _MOD_BALANCE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Balance_balance 0x00000100
#define MASK_Balance_smoothingTime 0x00000200
#define MASK_Balance_currentGainL 0x00000400
#define MASK_Balance_currentGainR 0x00000800
#define MASK_Balance_smoothingCoeff 0x00001000
#define MASK_Balance_gainL 0x00002000
#define MASK_Balance_gainR 0x00004000
#define OFFSET_Balance_balance 0x00000008
#define OFFSET_Balance_smoothingTime 0x00000009
#define OFFSET_Balance_currentGainL 0x0000000A
#define OFFSET_Balance_currentGainR 0x0000000B
#define OFFSET_Balance_smoothingCoeff 0x0000000C
#define OFFSET_Balance_gainL 0x0000000D
#define OFFSET_Balance_gainR 0x0000000E

#define CLASSID_BALANCE (CLASS_ID_MODBASE + 125)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBalanceInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            balance;             // Left/Right Balance.
    FLOAT32            smoothingTime;       // Time constant of the smoothing process.
    FLOAT32            currentGainL;        // Instantaneous gain applied to left channel. This is also the starting gain of the left channel.
    FLOAT32            currentGainR;        // Instantaneous gain applied to right channel. This is also the starting gain of the right channel.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    FLOAT32            gainL;               // Target gain left channel.
    FLOAT32            gainR;               // Target gain right channel.
    
} awe_modBalanceInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBalanceClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modBalanceConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_BALANCE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modBalanceProcess(void *pInstance);

UINT32 awe_modBalanceSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BALANCE_H

/**
 * @}
 *
 * End of file.
 */
