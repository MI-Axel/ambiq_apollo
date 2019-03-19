/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMultiplexorV2Fract32.h
****************************************************************************
*
*     Description:  General purpose multiplexor
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
 * @brief General purpose multiplexor
 */

#ifndef _MOD_MULTIPLEXORV2FRACT32_H
#define _MOD_MULTIPLEXORV2FRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MultiplexorV2Fract32_index 0x00000100
#define MASK_MultiplexorV2Fract32_smoothingTime 0x00000200
#define MASK_MultiplexorV2Fract32_fadeTime 0x00000400
#define MASK_MultiplexorV2Fract32_isControl 0x00000800
#define MASK_MultiplexorV2Fract32_smoothingCoeffFract32 0x00001000
#define MASK_MultiplexorV2Fract32_oldSrcGainFract32 0x00002000
#define MASK_MultiplexorV2Fract32_newSrcGainFract32 0x00004000
#define MASK_MultiplexorV2Fract32_fadeState 0x00008000
#define MASK_MultiplexorV2Fract32_fadeStateInit 0x00010000
#define MASK_MultiplexorV2Fract32_oldIndex 0x00020000
#define MASK_MultiplexorV2Fract32_newIndex 0x00040000
#define OFFSET_MultiplexorV2Fract32_index 0x00000008
#define OFFSET_MultiplexorV2Fract32_smoothingTime 0x00000009
#define OFFSET_MultiplexorV2Fract32_fadeTime 0x0000000A
#define OFFSET_MultiplexorV2Fract32_isControl 0x0000000B
#define OFFSET_MultiplexorV2Fract32_smoothingCoeffFract32 0x0000000C
#define OFFSET_MultiplexorV2Fract32_oldSrcGainFract32 0x0000000D
#define OFFSET_MultiplexorV2Fract32_newSrcGainFract32 0x0000000E
#define OFFSET_MultiplexorV2Fract32_fadeState 0x0000000F
#define OFFSET_MultiplexorV2Fract32_fadeStateInit 0x00000010
#define OFFSET_MultiplexorV2Fract32_oldIndex 0x00000011
#define OFFSET_MultiplexorV2Fract32_newIndex 0x00000012

#define CLASSID_MULTIPLEXORV2FRACT32 (CLASS_ID_MODBASE + 164)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMultiplexorV2Fract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              index;               // Specifies which input pin to route to the output. The index is zero based.
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    FLOAT32            fadeTime;            // Silence time in crossfade
    INT32              isControl;           // Indicates if the index is controlled by an external signal
    fract32            smoothingCoeffFract32; // Smoothing coefficient
    fract32            oldSrcGainFract32;   // Instanteous gain being applied to the old source.  This is an internal variable used in the smoothing process
    fract32            newSrcGainFract32;   // Instanteous gain being applied to the new source.  This is an internal variable used in the smoothing process
    INT32              fadeState;           // State variable for determining when to transitioning between inputs
    INT32              fadeStateInit;       // Derived from fadeTime, determines number of blocks to wait before switching input pins
    INT32              oldIndex;            // This is index that is currently being used and the module smoothly transitions to index
    INT32              newIndex;            // This is index that is currently being used and the module smoothly transitions to index
    
} awe_modMultiplexorV2Fract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMultiplexorV2Fract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modMultiplexorV2Fract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_MULTIPLEXORV2FRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modMultiplexorV2Fract32Process(void *pInstance);

UINT32 awe_modMultiplexorV2Fract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MULTIPLEXORV2FRACT32_H

/**
 * @}
 *
 * End of file.
 */
