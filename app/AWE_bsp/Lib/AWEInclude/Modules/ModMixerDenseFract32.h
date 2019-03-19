/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMixerDenseFract32.h
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

#ifndef _MOD_MIXERDENSEFRACT32_H
#define _MOD_MIXERDENSEFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MixerDenseFract32_postShift 0x00000100
#define MASK_MixerDenseFract32_gain 0x00000200
#define MASK_MixerDenseFract32_gainFract32 0x00000400
#define OFFSET_MixerDenseFract32_postShift 0x00000008
#define OFFSET_MixerDenseFract32_gain 0x00000009
#define OFFSET_MixerDenseFract32_gainFract32 0x0000000A

#define CLASSID_MIXERDENSEFRACT32 (CLASS_ID_MODBASE + 162)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMixerDenseFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              postShift;           // Number of bits to shift
    FLOAT32*           gain;                // Array of linear gain factors. The size of the array is numIn * numOut.
    fract32*           gainFract32;         // Array of linear gain factors in fractional representation. The size of the array is numIn * numOut.
} awe_modMixerDenseFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMixerDenseFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modMixerDenseFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modMixerDenseFract32Process(void *pInstance);

UINT32 awe_modMixerDenseFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MIXERDENSEFRACT32_H

/**
 * @}
 *
 * End of file.
 */
