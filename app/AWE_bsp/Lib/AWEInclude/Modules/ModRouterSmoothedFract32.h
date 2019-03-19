/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModRouterSmoothedFract32.h
****************************************************************************
*
*     Description:  Smoothly varying channel router module
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
 * @brief Smoothly varying channel router module
 */

#ifndef _MOD_ROUTERSMOOTHEDFRACT32_H
#define _MOD_ROUTERSMOOTHEDFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_RouterSmoothedFract32_smoothingTime 0x00000100
#define MASK_RouterSmoothedFract32_smoothingCoeffFract32 0x00000200
#define MASK_RouterSmoothedFract32_channelIndex 0x00000400
#define MASK_RouterSmoothedFract32_currentChannelIndex 0x00000800
#define MASK_RouterSmoothedFract32_currentGain 0x00001000
#define OFFSET_RouterSmoothedFract32_smoothingTime 0x00000008
#define OFFSET_RouterSmoothedFract32_smoothingCoeffFract32 0x00000009
#define OFFSET_RouterSmoothedFract32_channelIndex 0x0000000A
#define OFFSET_RouterSmoothedFract32_currentChannelIndex 0x0000000B
#define OFFSET_RouterSmoothedFract32_currentGain 0x0000000C

#define CLASSID_ROUTERSMOOTHEDFRACT32 (CLASS_ID_MODBASE + 175)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modRouterSmoothedFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    fract32            smoothingCoeffFract32; // Smoothing coefficient
    INT32*             channelIndex;        // Specifies input to output channel routing.  Each item in the array corresponds to an output pin and contains two packed values:  input pin number in the high 16 bits; input channel number in the low 16 bits
    INT32*             currentChannelIndex; // Similar to the channelIndex, but specifies the current routing for each channel
    fract32*           currentGain;         // Instantaneous gain for each output channel
} awe_modRouterSmoothedFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modRouterSmoothedFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modRouterSmoothedFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modRouterSmoothedFract32Process(void *pInstance);

UINT32 awe_modRouterSmoothedFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_ROUTERSMOOTHEDFRACT32_H

/**
 * @}
 *
 * End of file.
 */
