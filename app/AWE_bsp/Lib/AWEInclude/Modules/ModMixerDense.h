/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMixerDense.h
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

#ifndef _MOD_MIXERDENSE_H
#define _MOD_MIXERDENSE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MixerDense_gain 0x00000100
#define OFFSET_MixerDense_gain 0x00000008

#define CLASSID_MIXERDENSE (CLASS_ID_MODBASE + 2021)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMixerDenseInstance
{
    ModuleInstanceDescriptor instance;
    
    FLOAT32*           gain;                // Array of linear gain factors. The size of the array is numIn * numOut.
} awe_modMixerDenseInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMixerDenseClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modMixerDenseConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modMixerDenseProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MIXERDENSE_H

/**
 * @}
 *
 * End of file.
 */
