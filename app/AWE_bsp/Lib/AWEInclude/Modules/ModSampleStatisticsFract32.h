/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSampleStatisticsFract32.h
****************************************************************************
*
*     Description:  Computes sample statistics over multichannel fract32 signals
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
 * @brief Computes sample statistics over multichannel fract32 signals
 */

#ifndef _MOD_SAMPLESTATISTICSFRACT32_H
#define _MOD_SAMPLESTATISTICSFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SampleStatisticsFract32_statisticsType 0x00000100
#define MASK_SampleStatisticsFract32_instantaneousValue 0x00000200
#define OFFSET_SampleStatisticsFract32_statisticsType 0x00000008
#define OFFSET_SampleStatisticsFract32_instantaneousValue 0x00000009

#define CLASSID_SAMPLESTATISTICSFRACT32 (CLASS_ID_MODBASE + 1319)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSampleStatisticsFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              statisticsType;      // Type of statistics calculated: 0=maximum, 1=minimum, 2=maximum absolute value, 3=minimum absolute value.
    fract32            instantaneousValue;  // Instantaneous output value.
    
} awe_modSampleStatisticsFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSampleStatisticsFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSampleStatisticsFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SAMPLESTATISTICSFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSampleStatisticsFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SAMPLESTATISTICSFRACT32_H

/**
 * @}
 *
 * End of file.
 */
