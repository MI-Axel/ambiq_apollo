/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModGraphicEQBand.h
****************************************************************************
*
*     Description:  Single band of a cascade graphic equalizer
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
 * @brief Single band of a cascade graphic equalizer
 */

#ifndef _MOD_GRAPHICEQBAND_H
#define _MOD_GRAPHICEQBAND_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_GraphicEQBand_gain 0x00000100
#define MASK_GraphicEQBand_lowerEdge 0x00000200
#define MASK_GraphicEQBand_upperEdge 0x00000400
#define MASK_GraphicEQBand_smoothingTime 0x00000800
#define MASK_GraphicEQBand_numStages 0x00001000
#define MASK_GraphicEQBand_smoothingCoeff 0x00002000
#define MASK_GraphicEQBand_targetCoeffs 0x00004000
#define MASK_GraphicEQBand_currentCoeffs 0x00008000
#define MASK_GraphicEQBand_state 0x00010000
#define OFFSET_GraphicEQBand_gain 0x00000008
#define OFFSET_GraphicEQBand_lowerEdge 0x00000009
#define OFFSET_GraphicEQBand_upperEdge 0x0000000A
#define OFFSET_GraphicEQBand_smoothingTime 0x0000000B
#define OFFSET_GraphicEQBand_numStages 0x0000000C
#define OFFSET_GraphicEQBand_smoothingCoeff 0x0000000D
#define OFFSET_GraphicEQBand_targetCoeffs 0x0000000E
#define OFFSET_GraphicEQBand_currentCoeffs 0x0000000F
#define OFFSET_GraphicEQBand_state 0x00000010

#define CLASSID_GRAPHICEQBAND (CLASS_ID_MODBASE + 16)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modGraphicEQBandInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            gain;                // Gain in the center of the band, in dB.
    FLOAT32            lowerEdge;           // Lower frequency edge of the band, in Hz.
    FLOAT32            upperEdge;           // Upper frequency edge of the band, in Hz.
    FLOAT32            smoothingTime;       // Time constant of the smoothing process.
    INT32              numStages;           // Number of 2nd order stages in the filter.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    FLOAT32*           targetCoeffs;        // Target coefficient array.
    FLOAT32*           currentCoeffs;       // Current coefficient array after smoothing.
    FLOAT32*           state;               // State variable array with 4 values per stage per channel.
} awe_modGraphicEQBandInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modGraphicEQBandClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modGraphicEQBandConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modGraphicEQBandProcess(void *pInstance);

UINT32 awe_modGraphicEQBandSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_GRAPHICEQBAND_H

/**
 * @}
 *
 * End of file.
 */
