/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModTwoPieceInterp.h
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

#ifndef _MOD_TWOPIECEINTERP_H
#define _MOD_TWOPIECEINTERP_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_TwoPieceInterp_threshold 0x00000100
#define MASK_TwoPieceInterp_slopeL 0x00000200
#define MASK_TwoPieceInterp_slopeH 0x00000400
#define MASK_TwoPieceInterp_kneeDepth 0x00000800
#define MASK_TwoPieceInterp_polyCoeffs 0x00001000
#define OFFSET_TwoPieceInterp_threshold 0x00000008
#define OFFSET_TwoPieceInterp_slopeL 0x00000009
#define OFFSET_TwoPieceInterp_slopeH 0x0000000A
#define OFFSET_TwoPieceInterp_kneeDepth 0x0000000B
#define OFFSET_TwoPieceInterp_polyCoeffs 0x0000000C

#define CLASSID_TWOPIECEINTERP (CLASS_ID_MODBASE + 2045)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modTwoPieceInterpInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            threshold;           // The point at which two line segments meet
    FLOAT32            slopeL;              // The slope of the line segment on the left hand side
    FLOAT32            slopeH;              // The slope of the line segment on the right hand side
    FLOAT32            kneeDepth;           // Specifies the curvature of the smooth region connecting the two line segments
    FLOAT32*           polyCoeffs;          // Interpolation coefficients returned by the grid control.
} awe_modTwoPieceInterpInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modTwoPieceInterpClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modTwoPieceInterpConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modTwoPieceInterpProcess(void *pInstance);

UINT32 awe_modTwoPieceInterpSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_TWOPIECEINTERP_H

/**
 * @}
 *
 * End of file.
 */
