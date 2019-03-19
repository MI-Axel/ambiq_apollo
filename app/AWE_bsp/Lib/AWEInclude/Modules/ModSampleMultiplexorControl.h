/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSampleMultiplexorControl.h
****************************************************************************
*
*     Description:  N to 1 multiplexor module with a control input operating sample-by-sample
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
 * @brief N to 1 multiplexor module with a control input operating sample-by-sample
 */

#ifndef _MOD_SAMPLEMULTIPLEXORCONTROL_H
#define _MOD_SAMPLEMULTIPLEXORCONTROL_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_SAMPLEMULTIPLEXORCONTROL (CLASS_ID_MODBASE + 1317)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSampleMultiplexorControlInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modSampleMultiplexorControlInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSampleMultiplexorControlClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSampleMultiplexorControlConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SAMPLEMULTIPLEXORCONTROL, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSampleMultiplexorControlProcess(void *pInstance);

 

void awe_modSampleMultiplexorControlBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_SAMPLEMULTIPLEXORCONTROL_H

/**
 * @}
 *
 * End of file.
 */
