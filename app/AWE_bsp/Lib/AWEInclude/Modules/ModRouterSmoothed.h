/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModRouterSmoothed.h
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

#ifndef _MOD_ROUTERSMOOTHED_H
#define _MOD_ROUTERSMOOTHED_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_RouterSmoothed_smoothingTime 0x00000100
#define MASK_RouterSmoothed_smoothingCoeff 0x00000200
#define MASK_RouterSmoothed_channelIndex 0x00000400
#define MASK_RouterSmoothed_currentChannelIndex 0x00000800
#define MASK_RouterSmoothed_currentGain 0x00001000
#define OFFSET_RouterSmoothed_smoothingTime 0x00000008
#define OFFSET_RouterSmoothed_smoothingCoeff 0x00000009
#define OFFSET_RouterSmoothed_channelIndex 0x0000000A
#define OFFSET_RouterSmoothed_currentChannelIndex 0x0000000B
#define OFFSET_RouterSmoothed_currentGain 0x0000000C

#define CLASSID_ROUTERSMOOTHED (CLASS_ID_MODBASE + 101)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modRouterSmoothedInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    INT32*             channelIndex;        // Specifies input to output channel routing. Each item in the array corresponds to an output pin and contains two packed values: input pin number in the high 16 bits; input channel number in the low 16 bits.
    INT32*             currentChannelIndex; // Similar to the channelIndex, but specifies the current routing for each channel.
    FLOAT32*           currentGain;         // Instantaneous gain for each output channel.
} awe_modRouterSmoothedInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modRouterSmoothedClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modRouterSmoothedConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modRouterSmoothedProcess(void *pInstance);

UINT32 awe_modRouterSmoothedSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_ROUTERSMOOTHED_H

/**
 * @}
 *
 * End of file.
 */
