/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModOscillator.h
****************************************************************************
*
*     Description:  Numerically-controlled oscillator
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
 * @brief Numerically-controlled oscillator
 */

#ifndef _MOD_OSCILLATOR_H
#define _MOD_OSCILLATOR_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Oscillator_freqhz 0x00000100
#define MASK_Oscillator_startPhase 0x00000200
#define MASK_Oscillator_freq 0x00000400
#define MASK_Oscillator_phase 0x00000800
#define OFFSET_Oscillator_freqhz 0x00000008
#define OFFSET_Oscillator_startPhase 0x00000009
#define OFFSET_Oscillator_freq 0x0000000A
#define OFFSET_Oscillator_phase 0x0000000B

#define CLASSID_OSCILLATOR (CLASS_ID_MODBASE + 1300)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modOscillatorInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            freqhz;              // Nominal oscillator frequency in Hz
    FLOAT32            startPhase;          // Starting phase oscillator in multiples of pi radians
    FLOAT32            freq;                // Current oscillator frequency
    FLOAT32*           phase;               // Current oscillator phase
} awe_modOscillatorInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modOscillatorClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modOscillatorConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modOscillatorProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_OSCILLATOR_H

/**
 * @}
 *
 * End of file.
 */
