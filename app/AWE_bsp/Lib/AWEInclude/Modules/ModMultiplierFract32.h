/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMultiplierFract32.h
****************************************************************************
*
*     Description:  Multi-input multiplier
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
 * @brief Multi-input multiplier
 */

#ifndef _MOD_MULTIPLIERFRACT32_H
#define _MOD_MULTIPLIERFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MultiplierFract32_oneChannelOutput 0x00000100
#define OFFSET_MultiplierFract32_oneChannelOutput 0x00000008

#define CLASSID_MULTIPLIERFRACT32 (CLASS_ID_MODBASE + 160)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMultiplierFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              oneChannelOutput;    // Boolean value that determines whether all channels are summed to form a single output
    
} awe_modMultiplierFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMultiplierFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modMultiplierFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_MULTIPLIERFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modMultiplierFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MULTIPLIERFRACT32_H

/**
 * @}
 *
 * End of file.
 */
