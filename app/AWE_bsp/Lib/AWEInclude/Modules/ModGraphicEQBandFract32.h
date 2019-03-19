/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModGraphicEQBandFract32.h
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

#ifndef _MOD_GRAPHICEQBANDFRACT32_H
#define _MOD_GRAPHICEQBANDFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModBiquadCascadeFract32.h"

#define MASK_GraphicEQBandFract32_gain 0x00000100
#define MASK_GraphicEQBandFract32_lowerEdge 0x00000200
#define MASK_GraphicEQBandFract32_upperEdge 0x00000400
#define MASK_GraphicEQBandFract32_numStages 0x00000800
#define OFFSET_GraphicEQBandFract32_gain 0x00000008
#define OFFSET_GraphicEQBandFract32_lowerEdge 0x00000009
#define OFFSET_GraphicEQBandFract32_upperEdge 0x0000000A
#define OFFSET_GraphicEQBandFract32_numStages 0x0000000B

#define CLASSID_GRAPHICEQBANDFRACT32 (CLASS_ID_MODBASE + 143)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modGraphicEQBandFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            gain;                // Gain in the center of the band, in dB
    FLOAT32            lowerEdge;           // Lower frequency edge of the band, in Hz
    FLOAT32            upperEdge;           // Upper frequency edge of the band, in Hz
    INT32              numStages;           // Number of 2nd order stages in the filter
        awe_modBiquadCascadeFract32Instance    *filt;               // Cascade of second order Biquad filters
} awe_modGraphicEQBandFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modGraphicEQBandFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modGraphicEQBandFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modGraphicEQBandFract32Process(void *pInstance);

UINT32 awe_modGraphicEQBandFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_GRAPHICEQBANDFRACT32_H

/**
 * @}
 *
 * End of file.
 */
