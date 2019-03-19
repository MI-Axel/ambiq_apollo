/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDeMultiplexor.h
****************************************************************************
*
*     Description:  1 to N demultiplexor module without smoothing
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
 * @brief 1 to N demultiplexor module without smoothing
 */

#ifndef _MOD_DEMULTIPLEXOR_H
#define _MOD_DEMULTIPLEXOR_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DeMultiplexor_index 0x00000100
#define OFFSET_DeMultiplexor_index 0x00000008

#define CLASSID_DEMULTIPLEXOR (CLASS_ID_MODBASE + 2008)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDeMultiplexorInstance
{
    ModuleInstanceDescriptor instance;
    INT32              index;               // Specifies which output pin the input has to be routed. The index is zero based.
    
} awe_modDeMultiplexorInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDeMultiplexorClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modDeMultiplexorConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_DEMULTIPLEXOR, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modDeMultiplexorProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DEMULTIPLEXOR_H

/**
 * @}
 *
 * End of file.
 */
