/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModGraphicEQBandHP.h
****************************************************************************
*
*     Description:  Single band of a cascade graphic equalizer with high precision implementation
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
 * @brief Single band of a cascade graphic equalizer with high precision implementation
 */

#ifndef _MOD_GRAPHICEQBANDHP_H
#define _MOD_GRAPHICEQBANDHP_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_GraphicEQBandHP_gain 0x00000100
#define MASK_GraphicEQBandHP_lowerEdge 0x00000200
#define MASK_GraphicEQBandHP_upperEdge 0x00000400
#define MASK_GraphicEQBandHP_smoothingTime 0x00000800
#define MASK_GraphicEQBandHP_numStages 0x00001000
#define MASK_GraphicEQBandHP_updateActive 0x00002000
#define MASK_GraphicEQBandHP_smoothingCoeff 0x00004000
#define MASK_GraphicEQBandHP_targetCoeffs 0x00008000
#define MASK_GraphicEQBandHP_currentCoeffs 0x00010000
#define MASK_GraphicEQBandHP_state 0x00020000
#define OFFSET_GraphicEQBandHP_gain 0x00000008
#define OFFSET_GraphicEQBandHP_lowerEdge 0x00000009
#define OFFSET_GraphicEQBandHP_upperEdge 0x0000000A
#define OFFSET_GraphicEQBandHP_smoothingTime 0x0000000B
#define OFFSET_GraphicEQBandHP_numStages 0x0000000C
#define OFFSET_GraphicEQBandHP_updateActive 0x0000000D
#define OFFSET_GraphicEQBandHP_smoothingCoeff 0x0000000E
#define OFFSET_GraphicEQBandHP_targetCoeffs 0x0000000F
#define OFFSET_GraphicEQBandHP_currentCoeffs 0x00000010
#define OFFSET_GraphicEQBandHP_state 0x00000011

#define CLASSID_GRAPHICEQBANDHP (CLASS_ID_MODBASE + 1285)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modGraphicEQBandHPInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            gain;                // Gain in the center of the band, in dB.
    FLOAT32            lowerEdge;           // Lower frequency edge of the band, in Hz.
    FLOAT32            upperEdge;           // Upper frequency edge of the band, in Hz.
    FLOAT32            smoothingTime;       // Time constant of the smoothing process.
    INT32              numStages;           // Number of 2nd order stages in the filter.
    INT32              updateActive;        // Internal control flag which enables currentCoeff updating in process function.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    FLOAT32*           targetCoeffs;        // Target coefficient array. Each column contains the variables for a biquad arranged as [Fb; Gaa; Gab; K; Fa].
    FLOAT32*           currentCoeffs;       // Current coefficient array after smoothing. Each column contains the variables for a biquad arranged as [Fb; Gaa; Gab; K; Fa].
    FLOAT32*           state;               // State variable array with 2 values per stage per channel.
} awe_modGraphicEQBandHPInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modGraphicEQBandHPClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modGraphicEQBandHPConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modGraphicEQBandHPProcess(void *pInstance);

UINT32 awe_modGraphicEQBandHPSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_GRAPHICEQBANDHP_H

/**
 * @}
 *
 * End of file.
 */
