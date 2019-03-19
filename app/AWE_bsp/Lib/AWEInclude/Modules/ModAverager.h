/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAverager.h
****************************************************************************
*
*     Description:  Advanced multichannel averager
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
 * @brief Advanced multichannel averager
 */

#ifndef _MOD_AVERAGER_H
#define _MOD_AVERAGER_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Averager_smoothingTime 0x00000100
#define MASK_Averager_smoothingCoeff 0x00000200
#define MASK_Averager_sampleCounter 0x00000400
#define MASK_Averager_switchCount 0x00000800
#define MASK_Averager_stateSize 0x00001000
#define MASK_Averager_state 0x00002000
#define OFFSET_Averager_smoothingTime 0x00000008
#define OFFSET_Averager_smoothingCoeff 0x00000009
#define OFFSET_Averager_sampleCounter 0x0000000A
#define OFFSET_Averager_switchCount 0x0000000B
#define OFFSET_Averager_stateSize 0x0000000C
#define OFFSET_Averager_state 0x0000000D

#define CLASSID_AVERAGER (CLASS_ID_MODBASE + 1216)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAveragerInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    INT32              sampleCounter;       // Number of samples processed since last reset.
    INT32              switchCount;         // When to switch from cumulative to exponential averaging.
    INT32              stateSize;           // Size of the state array derived from input pin.
    FLOAT32*           state;               // Instantaneous average value.
} awe_modAveragerInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAveragerClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modAveragerConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modAveragerProcess(void *pInstance);

UINT32 awe_modAveragerSet(void *pInstance, UINT32 mask);
 

void awe_modAveragerBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_AVERAGER_H

/**
 * @}
 *
 * End of file.
 */
