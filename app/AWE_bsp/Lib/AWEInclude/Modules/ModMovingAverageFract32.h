/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMovingAverageFract32.h
****************************************************************************
*
*     Description:  Moving average FIR filter
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
 * @brief Moving average FIR filter
 */

#ifndef _MOD_MOVINGAVERAGEFRACT32_H
#define _MOD_MOVINGAVERAGEFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MovingAverageFract32_maxNumSamples 0x00000100
#define MASK_MovingAverageFract32_numSamples 0x00000200
#define MASK_MovingAverageFract32_stateIndex 0x00000400
#define MASK_MovingAverageFract32_inputGain 0x00000800
#define MASK_MovingAverageFract32_state 0x00001000
#define MASK_MovingAverageFract32_lastOut 0x00002000
#define OFFSET_MovingAverageFract32_maxNumSamples 0x00000008
#define OFFSET_MovingAverageFract32_numSamples 0x00000009
#define OFFSET_MovingAverageFract32_stateIndex 0x0000000A
#define OFFSET_MovingAverageFract32_inputGain 0x0000000B
#define OFFSET_MovingAverageFract32_state 0x0000000C
#define OFFSET_MovingAverageFract32_lastOut 0x0000000D

#define CLASSID_MOVINGAVERAGEFRACT32 (CLASS_ID_MODBASE + 1297)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMovingAverageFract32Instance
{
    ModuleInstanceDescriptor instance;
    int                maxNumSamples;       // Maximum length of the filter
    int                numSamples;          // Current filter length
    int                stateIndex;          // Index of the oldest state variable in the circular array of state variables.
    fract32            inputGain;           // Scale down factor for input samples.  Yields DC gain of 1.0
    fract32*           state;               // State variable array.
    fract32*           lastOut;             // Holds the variable y[n-1] for each channel
} awe_modMovingAverageFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMovingAverageFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modMovingAverageFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modMovingAverageFract32Process(void *pInstance);

UINT32 awe_modMovingAverageFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MOVINGAVERAGEFRACT32_H

/**
 * @}
 *
 * End of file.
 */
