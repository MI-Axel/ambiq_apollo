/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMultiplierV2.h
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

#ifndef _MOD_MULTIPLIERV2_H
#define _MOD_MULTIPLIERV2_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MultiplierV2_multMode 0x00000100
#define MASK_MultiplierV2_oneChannelOutput 0x00000200
#define OFFSET_MultiplierV2_multMode 0x00000008
#define OFFSET_MultiplierV2_oneChannelOutput 0x00000009

#define CLASSID_MULTIPLIERV2 (CLASS_ID_MODBASE + 57)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMultiplierV2Instance
{
    ModuleInstanceDescriptor instance;
    INT32              multMode;            // multMode=0 is a multi-input multiplier, multMode=1 is an AGC multiplier
    INT32              oneChannelOutput;    // Boolean value that determines whether all channels are summed to form a single output.
    
} awe_modMultiplierV2Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMultiplierV2Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modMultiplierV2Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_MULTIPLIERV2, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modMultiplierV2Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MULTIPLIERV2_H

/**
 * @}
 *
 * End of file.
 */
