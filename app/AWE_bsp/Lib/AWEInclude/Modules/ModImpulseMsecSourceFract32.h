/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModImpulseMsecSourceFract32.h
****************************************************************************
*
*     Description:  Source module which periodically outputs an impulse.  Time specified in msec.
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
 * @brief Source module which periodically outputs an impulse.  Time specified in msec.
 */

#ifndef _MOD_IMPULSEMSECSOURCEFRACT32_H
#define _MOD_IMPULSEMSECSOURCEFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ImpulseMsecSourceFract32_periodMsec 0x00000100
#define MASK_ImpulseMsecSourceFract32_period 0x00000200
#define MASK_ImpulseMsecSourceFract32_sampleIndex 0x00000400
#define OFFSET_ImpulseMsecSourceFract32_periodMsec 0x00000008
#define OFFSET_ImpulseMsecSourceFract32_period 0x00000009
#define OFFSET_ImpulseMsecSourceFract32_sampleIndex 0x0000000A

#define CLASSID_IMPULSEMSECSOURCEFRACT32 (CLASS_ID_MODBASE + 146)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modImpulseMsecSourceFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              periodMsec;          // Period or rate of the impulse generator (in msec).
    INT32              period;              // Period or rate of the impulse generator (in samples).
    INT32              sampleIndex;         // Specifies the index of the next non-zero value.
    
} awe_modImpulseMsecSourceFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modImpulseMsecSourceFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modImpulseMsecSourceFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_IMPULSEMSECSOURCEFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modImpulseMsecSourceFract32Process(void *pInstance);

UINT32 awe_modImpulseMsecSourceFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_IMPULSEMSECSOURCEFRACT32_H

/**
 * @}
 *
 * End of file.
 */
