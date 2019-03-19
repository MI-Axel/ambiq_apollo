/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMixerV3Fract32.h
****************************************************************************
*
*     Description:  M-input x N-output mixer
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
 * @brief M-input x N-output mixer
 */

#ifndef _MOD_MIXERV3FRACT32_H
#define _MOD_MIXERV3FRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

typedef struct _SparseItem
{
	fract32 *srcPtr;
	fract32 *dstPtr;
	int srcStride;
} SparseItem;
#define MASK_MixerV3Fract32_maxNonZero 0x00000100
#define MASK_MixerV3Fract32_postShift 0x00000200
#define MASK_MixerV3Fract32_gainScale 0x00000400
#define MASK_MixerV3Fract32_numIn 0x00000800
#define MASK_MixerV3Fract32_gain 0x00001000
#define MASK_MixerV3Fract32_nonZeroGainFract32 0x00002000
#define MASK_MixerV3Fract32_table 0x00004000
#define OFFSET_MixerV3Fract32_maxNonZero 0x00000008
#define OFFSET_MixerV3Fract32_postShift 0x00000009
#define OFFSET_MixerV3Fract32_gainScale 0x0000000A
#define OFFSET_MixerV3Fract32_numIn 0x0000000B
#define OFFSET_MixerV3Fract32_gain 0x0000000C
#define OFFSET_MixerV3Fract32_nonZeroGainFract32 0x0000000D
#define OFFSET_MixerV3Fract32_table 0x0000000E

#define CLASSID_MIXERV3FRACT32 (CLASS_ID_MODBASE + 166)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMixerV3Fract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              maxNonZero;          // Maximum number of non zero coefficients.
    INT32              postShift;           // Number of bits to shift
    FLOAT32            gainScale;           // Scale coefficients based on postShift.
    INT32              numIn;               // Number of input channels.
    FLOAT32*           gain;                // Linear gain.
    fract32*           nonZeroGainFract32;  // Instanteous fract32 gain being applied.
    SparseItem *       table;               // Internal data holding data for quick processing
} awe_modMixerV3Fract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMixerV3Fract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modMixerV3Fract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modMixerV3Fract32Process(void *pInstance);

UINT32 awe_modMixerV3Fract32Set(void *pInstance, UINT32 mask);
 

void awe_modMixerV3Fract32Bypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_MIXERV3FRACT32_H

/**
 * @}
 *
 * End of file.
 */
