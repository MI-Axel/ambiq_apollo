/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAllpassDelay16.h
****************************************************************************
*
*     Description:  High order allpass structure with integer time delays
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
 * @brief High order allpass structure with integer time delays
 */

#ifndef _MOD_ALLPASSDELAY16_H
#define _MOD_ALLPASSDELAY16_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_AllpassDelay16_maxDelay 0x00000100
#define MASK_AllpassDelay16_currentDelay 0x00000200
#define MASK_AllpassDelay16_coef 0x00000400
#define MASK_AllpassDelay16_stateIndex 0x00000800
#define MASK_AllpassDelay16_state 0x00001000
#define OFFSET_AllpassDelay16_maxDelay 0x00000008
#define OFFSET_AllpassDelay16_currentDelay 0x00000009
#define OFFSET_AllpassDelay16_coef 0x0000000A
#define OFFSET_AllpassDelay16_stateIndex 0x0000000B
#define OFFSET_AllpassDelay16_state 0x0000000C

#define CLASSID_ALLPASSDELAY16 (CLASS_ID_MODBASE + 1209)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAllpassDelay16Instance
{
    ModuleInstanceDescriptor instance;
    INT32              maxDelay;            // Maximum delay that can be realized, in samples.  The size of the delay buffer (maxDelay+1)*numChannels
    INT32              currentDelay;        // Current delay
    FLOAT32            coef;                // Feedback/-feedforward coefficient for the allpass delay.
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables
    FLOAT32*           state;               // State variable array
} awe_modAllpassDelay16Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAllpassDelay16Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modAllpassDelay16Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modAllpassDelay16Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_ALLPASSDELAY16_H

/**
 * @}
 *
 * End of file.
 */
