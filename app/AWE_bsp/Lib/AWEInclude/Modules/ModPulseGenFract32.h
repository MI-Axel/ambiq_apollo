/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModPulseGenFract32.h
****************************************************************************
*
*     Description:  Generates a periodic rectangular pulse
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
 * @brief Generates a periodic rectangular pulse
 */

#ifndef _MOD_PULSEGENFRACT32_H
#define _MOD_PULSEGENFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_PulseGenFract32_period 0x00000100
#define MASK_PulseGenFract32_onTime 0x00000200
#define MASK_PulseGenFract32_isOn 0x00000400
#define MASK_PulseGenFract32_periodSamples 0x00000800
#define MASK_PulseGenFract32_onTimeSamples 0x00001000
#define MASK_PulseGenFract32_count 0x00002000
#define OFFSET_PulseGenFract32_period 0x00000008
#define OFFSET_PulseGenFract32_onTime 0x00000009
#define OFFSET_PulseGenFract32_isOn 0x0000000A
#define OFFSET_PulseGenFract32_periodSamples 0x0000000B
#define OFFSET_PulseGenFract32_onTimeSamples 0x0000000C
#define OFFSET_PulseGenFract32_count 0x0000000D

#define CLASSID_PULSEGENFRACT32 (CLASS_ID_MODBASE + 171)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modPulseGenFract32Instance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            period;              // Total period of the pulse.
    FLOAT32            onTime;              // Duration of the positive portion of the pulse.
    INT32              isOn;                // Boolean that turns the beeping on or off.
    INT32              periodSamples;       // Total period of the pulse in samples.
    INT32              onTimeSamples;       // Duration of the positive period of the pulse in samples.
    INT32              count;               // Sample counter that increments for each value output.
    
} awe_modPulseGenFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modPulseGenFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modPulseGenFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_PULSEGENFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modPulseGenFract32Process(void *pInstance);

UINT32 awe_modPulseGenFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_PULSEGENFRACT32_H

/**
 * @}
 *
 * End of file.
 */
