/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModImpulseMsecSource.h
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

#ifndef _MOD_IMPULSEMSECSOURCE_H
#define _MOD_IMPULSEMSECSOURCE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ImpulseMsecSource_periodMsec 0x00000100
#define MASK_ImpulseMsecSource_period 0x00000200
#define MASK_ImpulseMsecSource_sampleIndex 0x00000400
#define OFFSET_ImpulseMsecSource_periodMsec 0x00000008
#define OFFSET_ImpulseMsecSource_period 0x00000009
#define OFFSET_ImpulseMsecSource_sampleIndex 0x0000000A

#define CLASSID_IMPULSEMSECSOURCE (CLASS_ID_MODBASE + 117)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modImpulseMsecSourceInstance
{
    ModuleInstanceDescriptor instance;
    INT32              periodMsec;          // Period or rate of the impulse generator (in msec).
    INT32              period;              // Period or rate of the impulse generator (in samples).
    INT32              sampleIndex;         // Specifies the index of the next non-zero value.
    
} awe_modImpulseMsecSourceInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modImpulseMsecSourceClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modImpulseMsecSourceConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_IMPULSEMSECSOURCE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modImpulseMsecSourceProcess(void *pInstance);

UINT32 awe_modImpulseMsecSourceSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_IMPULSEMSECSOURCE_H

/**
 * @}
 *
 * End of file.
 */
