/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModImpulseSource.h
****************************************************************************
*
*     Description:  Source module which periodically outputs an impulse
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
 * @brief Source module which periodically outputs an impulse
 */

#ifndef _MOD_IMPULSESOURCE_H
#define _MOD_IMPULSESOURCE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ImpulseSource_period 0x00000100
#define MASK_ImpulseSource_sampleIndex 0x00000200
#define OFFSET_ImpulseSource_period 0x00000008
#define OFFSET_ImpulseSource_sampleIndex 0x00000009

#define CLASSID_IMPULSESOURCE (CLASS_ID_MODBASE + 2016)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modImpulseSourceInstance
{
    ModuleInstanceDescriptor instance;
    INT32              period;              // Period or rate of the impulse generator.
    INT32              sampleIndex;         // Specifies the index of the next non-zero value.
    
} awe_modImpulseSourceInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modImpulseSourceClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modImpulseSourceConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_IMPULSESOURCE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modImpulseSourceProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_IMPULSESOURCE_H

/**
 * @}
 *
 * End of file.
 */
