/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSawtooth.h
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

#ifndef _MOD_SAWTOOTH_H
#define _MOD_SAWTOOTH_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Sawtooth_freq 0x00000100
#define MASK_Sawtooth_phase 0x00000200
#define MASK_Sawtooth_phaseIncrement 0x00000400
#define OFFSET_Sawtooth_freq 0x00000008
#define OFFSET_Sawtooth_phase 0x00000009
#define OFFSET_Sawtooth_phaseIncrement 0x0000000A

#define CLASSID_SAWTOOTH (CLASS_ID_MODBASE + 2035)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSawtoothInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            freq;                // Frequency of the sawtooth generator.
    FLOAT32            phase;               // The stored phase of the sawtooth module.
    FLOAT32            phaseIncrement;      // The amount that the oscillator phase is incremented for each output sample.
    
} awe_modSawtoothInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSawtoothClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSawtoothConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SAWTOOTH, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSawtoothProcess(void *pInstance);

UINT32 awe_modSawtoothSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SAWTOOTH_H

/**
 * @}
 *
 * End of file.
 */
