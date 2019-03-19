/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSawtoothFract32.h
****************************************************************************
*
*     Description:  Sawtooth wave generator (no anti-aliasing)
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
 * @brief Sawtooth wave generator (no anti-aliasing)
 */

#ifndef _MOD_SAWTOOTHFRACT32_H
#define _MOD_SAWTOOTHFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SawtoothFract32_freq 0x00000100
#define MASK_SawtoothFract32_phase 0x00000200
#define MASK_SawtoothFract32_phaseIncrement 0x00000400
#define OFFSET_SawtoothFract32_freq 0x00000008
#define OFFSET_SawtoothFract32_phase 0x00000009
#define OFFSET_SawtoothFract32_phaseIncrement 0x0000000A

#define CLASSID_SAWTOOTHFRACT32 (CLASS_ID_MODBASE + 183)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSawtoothFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            freq;                // Frequency of the sawtooth generator.
    fract32            phase;               // The stored phase of the sawtooth module.
    fract32            phaseIncrement;      // The amount that the oscillator phase is incremented for each output sample.
    
} awe_modSawtoothFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSawtoothFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSawtoothFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SAWTOOTHFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSawtoothFract32Process(void *pInstance);

UINT32 awe_modSawtoothFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SAWTOOTHFRACT32_H

/**
 * @}
 *
 * End of file.
 */
