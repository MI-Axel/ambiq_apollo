/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModRebuffer.h
****************************************************************************
*
*     Description:  Overlaps data into larger block sizes. The underlying time base is preserved.
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
 * @brief Overlaps data into larger block sizes. The underlying time base is preserved.
 */

#ifndef _MOD_REBUFFER_H
#define _MOD_REBUFFER_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Rebuffer_outBlockSize 0x00000100
#define MASK_Rebuffer_overlap 0x00000200
#define MASK_Rebuffer_stateIndex 0x00000400
#define MASK_Rebuffer_state 0x00000800
#define OFFSET_Rebuffer_outBlockSize 0x00000008
#define OFFSET_Rebuffer_overlap 0x00000009
#define OFFSET_Rebuffer_stateIndex 0x0000000A
#define OFFSET_Rebuffer_state 0x0000000B

#define CLASSID_REBUFFER (CLASS_ID_MODBASE + 1309)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modRebufferInstance
{
    ModuleInstanceDescriptor instance;
    INT32              outBlockSize;        // Specifies the size of the output block. Positive values indicate a specific block size, in samples. Negative values specify a multiplicative factor between the input and output block sizes.
    INT32              overlap;             // Number of samples of overlap between blocks. Set by the prebuild function.
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables.
    FLOAT32*           state;               // State variable array.
} awe_modRebufferInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modRebufferClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modRebufferConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modRebufferProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_REBUFFER_H

/**
 * @}
 *
 * End of file.
 */
