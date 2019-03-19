/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMixerV3.h
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

#ifndef _MOD_MIXERV3_H
#define _MOD_MIXERV3_H

#include "ModCommon.h"
#include "MathHelper.h"

typedef struct _SparseItem
{
	FLOAT32 *srcPtr;
	FLOAT32 *dstPtr;
	int srcStride;
} SparseItem;
#define MASK_MixerV3_maxNonZero 0x00000100
#define MASK_MixerV3_numIn 0x00000200
#define MASK_MixerV3_gain 0x00000400
#define MASK_MixerV3_nonZeroGain 0x00000800
#define MASK_MixerV3_table 0x00001000
#define OFFSET_MixerV3_maxNonZero 0x00000008
#define OFFSET_MixerV3_numIn 0x00000009
#define OFFSET_MixerV3_gain 0x0000000A
#define OFFSET_MixerV3_nonZeroGain 0x0000000B
#define OFFSET_MixerV3_table 0x0000000C

#define CLASSID_MIXERV3 (CLASS_ID_MODBASE + 22)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMixerV3Instance
{
    ModuleInstanceDescriptor instance;
    INT32              maxNonZero;          // Maximum number of non zero coefficients.
    INT32              numIn;               // Number of input channels.
    FLOAT32*           gain;                // Linear gain.
    FLOAT32*           nonZeroGain;         // Instanteous gain being applied.
    SparseItem *       table;               // Internal data holding data for quick processing
} awe_modMixerV3Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMixerV3Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modMixerV3Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modMixerV3Process(void *pInstance);

UINT32 awe_modMixerV3Set(void *pInstance, UINT32 mask);
 

void awe_modMixerV3Bypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_MIXERV3_H

/**
 * @}
 *
 * End of file.
 */
