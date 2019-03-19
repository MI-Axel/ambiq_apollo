/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMultiplexorV2.h
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

#ifndef _MOD_MULTIPLEXORV2_H
#define _MOD_MULTIPLEXORV2_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MultiplexorV2_index 0x00000100
#define MASK_MultiplexorV2_smoothingTime 0x00000200
#define MASK_MultiplexorV2_fadeTime 0x00000400
#define MASK_MultiplexorV2_isControl 0x00000800
#define MASK_MultiplexorV2_smoothingCoeff 0x00001000
#define MASK_MultiplexorV2_oldSrcGain 0x00002000
#define MASK_MultiplexorV2_newSrcGain 0x00004000
#define MASK_MultiplexorV2_fadeState 0x00008000
#define MASK_MultiplexorV2_fadeStateInit 0x00010000
#define MASK_MultiplexorV2_oldIndex 0x00020000
#define MASK_MultiplexorV2_newIndex 0x00040000
#define OFFSET_MultiplexorV2_index 0x00000008
#define OFFSET_MultiplexorV2_smoothingTime 0x00000009
#define OFFSET_MultiplexorV2_fadeTime 0x0000000A
#define OFFSET_MultiplexorV2_isControl 0x0000000B
#define OFFSET_MultiplexorV2_smoothingCoeff 0x0000000C
#define OFFSET_MultiplexorV2_oldSrcGain 0x0000000D
#define OFFSET_MultiplexorV2_newSrcGain 0x0000000E
#define OFFSET_MultiplexorV2_fadeState 0x0000000F
#define OFFSET_MultiplexorV2_fadeStateInit 0x00000010
#define OFFSET_MultiplexorV2_oldIndex 0x00000011
#define OFFSET_MultiplexorV2_newIndex 0x00000012

#define CLASSID_MULTIPLEXORV2 (CLASS_ID_MODBASE + 104)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMultiplexorV2Instance
{
    ModuleInstanceDescriptor instance;
    INT32              index;               // Specifies which input pin to route to the output. The index is zero based.
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    FLOAT32            fadeTime;            // Silence time in crossfade
    INT32              isControl;           // Indicates if the index is controlled by an external signal
    FLOAT32            smoothingCoeff;      // Smoothing coefficient
    FLOAT32            oldSrcGain;          // Instanteous gain being applied to the old source.  This is an internal variable used in the smoothing process
    FLOAT32            newSrcGain;          // Instanteous gain being applied to the new source.  This is an internal variable used in the smoothing process
    INT32              fadeState;           // State variable for determining when to transitioning between inputs
    INT32              fadeStateInit;       // Derived from fadeTime, determines number of blocks to wait before switching input pins
    INT32              oldIndex;            // This is the index that is currently being used
    INT32              newIndex;            // This is the index being transitioned to
    
} awe_modMultiplexorV2Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMultiplexorV2Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modMultiplexorV2Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_MULTIPLEXORV2, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modMultiplexorV2Process(void *pInstance);

UINT32 awe_modMultiplexorV2Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MULTIPLEXORV2_H

/**
 * @}
 *
 * End of file.
 */
