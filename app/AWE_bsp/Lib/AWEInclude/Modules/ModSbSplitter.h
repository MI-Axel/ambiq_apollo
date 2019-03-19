/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSbSplitter.h
****************************************************************************
*
*     Description:  Subband splitter module
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
 * @brief Subband splitter module
 */

#ifndef _MOD_SBSPLITTER_H
#define _MOD_SBSPLITTER_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SbSplitter_numOut 0x00000100
#define MASK_SbSplitter_bandEdges 0x00000200
#define MASK_SbSplitter_transitionWidths 0x00000400
#define MASK_SbSplitter_gains 0x00000800
#define OFFSET_SbSplitter_numOut 0x00000008
#define OFFSET_SbSplitter_bandEdges 0x00000009
#define OFFSET_SbSplitter_transitionWidths 0x0000000A
#define OFFSET_SbSplitter_gains 0x0000000B

#define CLASSID_SBSPLITTER (CLASS_ID_MODBASE + 1329)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSbSplitterInstance
{
    ModuleInstanceDescriptor instance;
    INT32              numOut;              // Number of output pins
    FLOAT32*           bandEdges;           // Cutoff frequencies between bands, in Hz
    FLOAT32*           transitionWidths;    // Width of the transition region between bands (Hz or Octave)
    FLOAT32*           gains;               // Internal array of gain factors.  Each column represents a different output.
} awe_modSbSplitterInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSbSplitterClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modSbSplitterConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modSbSplitterProcess(void *pInstance);

UINT32 awe_modSbSplitterSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SBSPLITTER_H

/**
 * @}
 *
 * End of file.
 */
