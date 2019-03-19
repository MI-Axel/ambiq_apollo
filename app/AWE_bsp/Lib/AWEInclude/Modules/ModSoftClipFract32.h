/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSoftClipFract32.h
****************************************************************************
*
*     Description:  Fract32 Soft clip in Fract32
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
 * @brief Fract32 Soft clip in Fract32
 */

#ifndef _MOD_SOFTCLIPFRACT32_H
#define _MOD_SOFTCLIPFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SoftClipFract32_threshold 0x00000100
#define MASK_SoftClipFract32_guardbit 0x00000200
#define MASK_SoftClipFract32_th 0x00000400
#define MASK_SoftClipFract32_lastIn 0x00000800
#define MASK_SoftClipFract32_lastOut 0x00001000
#define MASK_SoftClipFract32_currentGain 0x00002000
#define OFFSET_SoftClipFract32_threshold 0x00000008
#define OFFSET_SoftClipFract32_guardbit 0x00000009
#define OFFSET_SoftClipFract32_th 0x0000000A
#define OFFSET_SoftClipFract32_lastIn 0x0000000B
#define OFFSET_SoftClipFract32_lastOut 0x0000000C
#define OFFSET_SoftClipFract32_currentGain 0x0000000D

#define CLASSID_SOFTCLIPFRACT32 (CLASS_ID_MODBASE + 204)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSoftClipFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            threshold;           // Transition point between linear response and knee.
    INT32              guardbit;            // number of guard bits at the clipper output
    fract32            th;                  // Threshold in linear scale
    fract32*           lastIn;              // Array of last input sample, one per channel.
    fract32*           lastOut;             // Array of last output sample, one per channel.
    FLOAT32*           currentGain;         // Array of soft clipper gain, one per channel.
} awe_modSoftClipFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSoftClipFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modSoftClipFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modSoftClipFract32Process(void *pInstance);

UINT32 awe_modSoftClipFract32Set(void *pInstance, UINT32 mask);
 
UINT32 awe_modSoftClipFract32Get(void *pInstance, UINT32 mask);



#ifdef __cplusplus
}
#endif


#endif // _MOD_SOFTCLIPFRACT32_H

/**
 * @}
 *
 * End of file.
 */
