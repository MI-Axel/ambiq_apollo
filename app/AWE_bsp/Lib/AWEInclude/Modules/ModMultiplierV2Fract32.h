/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMultiplierV2Fract32.h
****************************************************************************
*
*     Description:  Multi-purpose multiplier
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
 * @brief Multi-purpose multiplier
 */

#ifndef _MOD_MULTIPLIERV2FRACT32_H
#define _MOD_MULTIPLIERV2FRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MultiplierV2Fract32_multMode 0x00000100
#define MASK_MultiplierV2Fract32_oneChannelOutput 0x00000200
#define MASK_MultiplierV2Fract32_postShift 0x00000400
#define OFFSET_MultiplierV2Fract32_multMode 0x00000008
#define OFFSET_MultiplierV2Fract32_oneChannelOutput 0x00000009
#define OFFSET_MultiplierV2Fract32_postShift 0x0000000A

#define CLASSID_MULTIPLIERV2FRACT32 (CLASS_ID_MODBASE + 165)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMultiplierV2Fract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              multMode;            // multMode=0 is a multi-input multiplier, multMode=1 is an AGC multiplier
    INT32              oneChannelOutput;    // Boolean value that determines whether all channels are summed to form a single output.
    INT32              postShift;           // Number of bits to shift
    
} awe_modMultiplierV2Fract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMultiplierV2Fract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modMultiplierV2Fract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_MULTIPLIERV2FRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modMultiplierV2Fract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MULTIPLIERV2FRACT32_H

/**
 * @}
 *
 * End of file.
 */
