/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSoftClip.h
****************************************************************************
*
*     Description:  Soft clip in float32
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
 * @brief Soft clip in float32
 */

#ifndef _MOD_SOFTCLIP_H
#define _MOD_SOFTCLIP_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SoftClip_threshold 0x00000100
#define MASK_SoftClip_th 0x00000200
#define MASK_SoftClip_lastIn 0x00000400
#define MASK_SoftClip_lastOut 0x00000800
#define MASK_SoftClip_currentGain 0x00001000
#define OFFSET_SoftClip_threshold 0x00000008
#define OFFSET_SoftClip_th 0x00000009
#define OFFSET_SoftClip_lastIn 0x0000000A
#define OFFSET_SoftClip_lastOut 0x0000000B
#define OFFSET_SoftClip_currentGain 0x0000000C

#define CLASSID_SOFTCLIP (CLASS_ID_MODBASE + 80)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSoftClipInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            threshold;           // Transition point between linear response and knee.
    FLOAT32            th;                  // Threshold in linear scale
    FLOAT32*           lastIn;              // Array of last input sample, one per channel.
    FLOAT32*           lastOut;             // Array of last output sample, one per channel.
    FLOAT32*           currentGain;         // Array of soft clipper gain, one per channel.
} awe_modSoftClipInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSoftClipClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modSoftClipConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modSoftClipProcess(void *pInstance);

UINT32 awe_modSoftClipSet(void *pInstance, UINT32 mask);
 
UINT32 awe_modSoftClipGet(void *pInstance, UINT32 mask);



#ifdef __cplusplus
}
#endif


#endif // _MOD_SOFTCLIP_H

/**
 * @}
 *
 * End of file.
 */
