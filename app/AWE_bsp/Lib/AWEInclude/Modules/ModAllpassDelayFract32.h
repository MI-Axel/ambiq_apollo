/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAllpassDelayFract32.h
****************************************************************************
*
*     Description:  Sample-based time delay
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
 * @brief Sample-based time delay
 */

#ifndef _MOD_ALLPASSDELAYFRACT32_H
#define _MOD_ALLPASSDELAYFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_AllpassDelayFract32_maxDelay 0x00000100
#define MASK_AllpassDelayFract32_currentDelay 0x00000200
#define MASK_AllpassDelayFract32_coef 0x00000400
#define MASK_AllpassDelayFract32_coefFract32 0x00000800
#define MASK_AllpassDelayFract32_postShift 0x00001000
#define MASK_AllpassDelayFract32_stateIndex 0x00002000
#define MASK_AllpassDelayFract32_state 0x00004000
#define OFFSET_AllpassDelayFract32_maxDelay 0x00000008
#define OFFSET_AllpassDelayFract32_currentDelay 0x00000009
#define OFFSET_AllpassDelayFract32_coef 0x0000000A
#define OFFSET_AllpassDelayFract32_coefFract32 0x0000000B
#define OFFSET_AllpassDelayFract32_postShift 0x0000000C
#define OFFSET_AllpassDelayFract32_stateIndex 0x0000000D
#define OFFSET_AllpassDelayFract32_state 0x0000000E

#define CLASSID_ALLPASSDELAYFRACT32 (CLASS_ID_MODBASE + 1206)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAllpassDelayFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              maxDelay;            // Maximum delay that can be realized, in samples.  The size of the delay buffer (maxDelay+1)*numChannels
    INT32              currentDelay;        // Current delay
    FLOAT32            coef;                // Feedback/-feedforward coefficient for the allpass delay.
    fract32            coefFract32;         // Feedback/-feedforward fractional coefficient for the allpass delay.
    INT32              postShift;           // Number of bits to shift after the fractional multiply.  This is based on gain.range.
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables
    fract32*           state;               // State variable array
} awe_modAllpassDelayFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAllpassDelayFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modAllpassDelayFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modAllpassDelayFract32Process(void *pInstance);

UINT32 awe_modAllpassDelayFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_ALLPASSDELAYFRACT32_H

/**
 * @}
 *
 * End of file.
 */
