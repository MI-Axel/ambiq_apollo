/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModRandiFract32.h
****************************************************************************
*
*     Description:  Low frequency noise generator
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
 * @brief Low frequency noise generator
 */

#ifndef _MOD_RANDIFRACT32_H
#define _MOD_RANDIFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_RandiFract32_freq 0x00000100
#define MASK_RandiFract32_isSmoothed 0x00000200
#define MASK_RandiFract32_slope 0x00000400
#define MASK_RandiFract32_level 0x00000800
#define MASK_RandiFract32_rate 0x00001000
#define MASK_RandiFract32_seed 0x00002000
#define MASK_RandiFract32_fixCurrentSeed 0x00004000
#define MASK_RandiFract32_counter 0x00008000
#define MASK_RandiFract32_oneOverRate 0x00010000
#define OFFSET_RandiFract32_freq 0x00000008
#define OFFSET_RandiFract32_isSmoothed 0x00000009
#define OFFSET_RandiFract32_slope 0x0000000A
#define OFFSET_RandiFract32_level 0x0000000B
#define OFFSET_RandiFract32_rate 0x0000000C
#define OFFSET_RandiFract32_seed 0x0000000D
#define OFFSET_RandiFract32_fixCurrentSeed 0x0000000E
#define OFFSET_RandiFract32_counter 0x0000000F
#define OFFSET_RandiFract32_oneOverRate 0x00000010

#define CLASSID_RANDIFRACT32 (CLASS_ID_MODBASE + 1305)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modRandiFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            freq;                // Rate at which random values are generated.
    INT32              isSmoothed;          // Determines whether the random signal interpolates between random values (isSmoothed=1) or steps between random values (isSmoothed=0).
    fract32            slope;               // Slope value for linear interpolation between random values.
    fract32            level;               // The current value of the random signal.
    INT32              rate;                // Starting value for counter, dependent on freq.
    UINT32             seed;                // State of the random number generator.
    INT32              fixCurrentSeed;      // Whether the prebuild function resets the seed or not. 0 = reset, 1 = no reset.
    INT32              counter;             // Counter value is used in slewing between random values.
    fract32            oneOverRate;         // Used in calculating the slope value.
    
} awe_modRandiFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modRandiFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modRandiFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_RANDIFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modRandiFract32Process(void *pInstance);

UINT32 awe_modRandiFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_RANDIFRACT32_H

/**
 * @}
 *
 * End of file.
 */
