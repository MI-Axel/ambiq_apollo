/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModTwoPieceInterpV2.h
****************************************************************************
*
*     Description:  Two piece interpolation module
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
 * @brief Two piece interpolation module
 */

#ifndef _MOD_TWOPIECEINTERPV2_H
#define _MOD_TWOPIECEINTERPV2_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_TwoPieceInterpV2_threshold 0x00000100
#define MASK_TwoPieceInterpV2_useRatios 0x00000200
#define MASK_TwoPieceInterpV2_slopeL 0x00000400
#define MASK_TwoPieceInterpV2_slopeH 0x00000800
#define MASK_TwoPieceInterpV2_ratioL 0x00001000
#define MASK_TwoPieceInterpV2_ratioH 0x00002000
#define MASK_TwoPieceInterpV2_kneeDepth 0x00004000
#define MASK_TwoPieceInterpV2_polyCoeffs 0x00008000
#define OFFSET_TwoPieceInterpV2_threshold 0x00000008
#define OFFSET_TwoPieceInterpV2_useRatios 0x00000009
#define OFFSET_TwoPieceInterpV2_slopeL 0x0000000A
#define OFFSET_TwoPieceInterpV2_slopeH 0x0000000B
#define OFFSET_TwoPieceInterpV2_ratioL 0x0000000C
#define OFFSET_TwoPieceInterpV2_ratioH 0x0000000D
#define OFFSET_TwoPieceInterpV2_kneeDepth 0x0000000E
#define OFFSET_TwoPieceInterpV2_polyCoeffs 0x0000000F

#define CLASSID_TWOPIECEINTERPV2 (CLASS_ID_MODBASE + 1348)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modTwoPieceInterpV2Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            threshold;           // The point at which two line segments meet
    INT32              useRatios;           // Specifies whether the line segments are specified using their slopes (=0) or ratios (=1)
    FLOAT32            slopeL;              // The slope of the line segment on the left hand side
    FLOAT32            slopeH;              // The slope of the line segment on the right hand side
    FLOAT32            ratioL;              // 1/slope of the line segment on the left hand side
    FLOAT32            ratioH;              // 1/slope of the line segment on the right hand side
    FLOAT32            kneeDepth;           // Specifies the curvature of the smooth region connecting the two line segments
    FLOAT32*           polyCoeffs;          // Interpolation coefficients returned by the grid control.
} awe_modTwoPieceInterpV2Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modTwoPieceInterpV2Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modTwoPieceInterpV2Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modTwoPieceInterpV2Process(void *pInstance);

UINT32 awe_modTwoPieceInterpV2Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_TWOPIECEINTERPV2_H

/**
 * @}
 *
 * End of file.
 */
