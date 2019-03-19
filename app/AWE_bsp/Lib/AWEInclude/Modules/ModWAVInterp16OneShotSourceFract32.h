/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModWAVInterp16OneShotSourceFract32.h
****************************************************************************
*
*     Description:  Periodic one shot WAV playback with linear interpolation
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
 * @brief Periodic one shot WAV playback with linear interpolation
 */

#ifndef _MOD_WAVINTERP16ONESHOTSOURCEFRACT32_H
#define _MOD_WAVINTERP16ONESHOTSOURCEFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_WAVInterp16OneShotSourceFract32_smoothingTime 0x00000100
#define MASK_WAVInterp16OneShotSourceFract32_circularBufferSize 0x00000200
#define MASK_WAVInterp16OneShotSourceFract32_extensionSize 0x00000400
#define MASK_WAVInterp16OneShotSourceFract32_currentFRatio 0x00000800
#define MASK_WAVInterp16OneShotSourceFract32_smoothingCoeff 0x00001000
#define MASK_WAVInterp16OneShotSourceFract32_fIndex 0x00002000
#define MASK_WAVInterp16OneShotSourceFract32_psObjectID 0x00004000
#define MASK_WAVInterp16OneShotSourceFract32_psObjectPtr 0x00008000
#define OFFSET_WAVInterp16OneShotSourceFract32_smoothingTime 0x00000008
#define OFFSET_WAVInterp16OneShotSourceFract32_circularBufferSize 0x00000009
#define OFFSET_WAVInterp16OneShotSourceFract32_extensionSize 0x0000000A
#define OFFSET_WAVInterp16OneShotSourceFract32_currentFRatio 0x0000000B
#define OFFSET_WAVInterp16OneShotSourceFract32_smoothingCoeff 0x0000000C
#define OFFSET_WAVInterp16OneShotSourceFract32_fIndex 0x0000000D
#define OFFSET_WAVInterp16OneShotSourceFract32_psObjectID 0x0000000E
#define OFFSET_WAVInterp16OneShotSourceFract32_psObjectPtr 0x0000000F

#define CLASSID_WAVINTERP16ONESHOTSOURCEFRACT32 (CLASS_ID_MODBASE + 1353)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modWAVInterp16OneShotSourceFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    INT32              circularBufferSize;  // Size of the upstream circular buffer, in 16-bit words.
    INT32              extensionSize;       // Size of the extension region of the circular buffer,  in 16-bit words
    FLOAT32            currentFRatio;       // Specifies rate at which audio is read from the input buffer
    FLOAT32            smoothingCoeff;      // Smoothing coefficient
    INT32              fIndex;              // 32-bit fractional state index
    INT32              psObjectID;          // Object ID of the upstream PeriodicStreaming module
    ModuleInstanceDescriptor **    psObjectPtr;         // Points to the upstream PeriodicStreaming module
} awe_modWAVInterp16OneShotSourceFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modWAVInterp16OneShotSourceFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modWAVInterp16OneShotSourceFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_WAVINTERP16ONESHOTSOURCEFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modWAVInterp16OneShotSourceFract32Process(void *pInstance);

UINT32 awe_modWAVInterp16OneShotSourceFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_WAVINTERP16ONESHOTSOURCEFRACT32_H

/**
 * @}
 *
 * End of file.
 */
