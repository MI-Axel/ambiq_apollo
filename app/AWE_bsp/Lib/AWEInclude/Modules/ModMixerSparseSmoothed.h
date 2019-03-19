/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMixerSparseSmoothed.h
****************************************************************************
*
*     Description:  M-input x N-output smoothly varying mixer
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
 * @brief M-input x N-output smoothly varying mixer
 */

#ifndef _MOD_MIXERSPARSESMOOTHED_H
#define _MOD_MIXERSPARSESMOOTHED_H

#include "ModCommon.h"
#include "MathHelper.h"

typedef struct _SparseItem
{
	float *srcPtr;
	float *dstPtr;
	int srcStride;
} SparseItem;
#define MASK_MixerSparseSmoothed_smoothingTime 0x00000100
#define MASK_MixerSparseSmoothed_smoothingCoeff 0x00000200
#define MASK_MixerSparseSmoothed_maxNZC 0x00000400
#define MASK_MixerSparseSmoothed_numIn 0x00000800
#define MASK_MixerSparseSmoothed_gain 0x00001000
#define MASK_MixerSparseSmoothed_currentGain 0x00002000
#define MASK_MixerSparseSmoothed_nonZeroGain 0x00004000
#define MASK_MixerSparseSmoothed_table 0x00008000
#define OFFSET_MixerSparseSmoothed_smoothingTime 0x00000008
#define OFFSET_MixerSparseSmoothed_smoothingCoeff 0x00000009
#define OFFSET_MixerSparseSmoothed_maxNZC 0x0000000A
#define OFFSET_MixerSparseSmoothed_numIn 0x0000000B
#define OFFSET_MixerSparseSmoothed_gain 0x0000000C
#define OFFSET_MixerSparseSmoothed_currentGain 0x0000000D
#define OFFSET_MixerSparseSmoothed_nonZeroGain 0x0000000E
#define OFFSET_MixerSparseSmoothed_table 0x0000000F

#define CLASSID_MIXERSPARSESMOOTHED (CLASS_ID_MODBASE + 2025)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMixerSparseSmoothedInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process, in msec.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient.
    INT32              maxNZC;              // Maximum number of non zero coefficients.
    INT32              numIn;               // Number of input channels.
    FLOAT32*           gain;                // Linear gain.
    FLOAT32*           currentGain;         // Instanteous gain being applied.  This is an internal variable used in the smoothing process
    FLOAT32*           nonZeroGain;         // Instanteous gain being applied.  This is an internal variable used in the smoothing process
    SparseItem *       table;               // Internal data holding data for quick processing
} awe_modMixerSparseSmoothedInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMixerSparseSmoothedClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modMixerSparseSmoothedConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modMixerSparseSmoothedProcess(void *pInstance);

UINT32 awe_modMixerSparseSmoothedSet(void *pInstance, UINT32 mask);
 

void awe_modMixerSparseSmoothedBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_MIXERSPARSESMOOTHED_H

/**
 * @}
 *
 * End of file.
 */
