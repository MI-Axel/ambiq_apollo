/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMultiplexor.h
****************************************************************************
*
*     Description:  Selects one of N inputs
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
 * @brief Selects one of N inputs
 */

#ifndef _MOD_MULTIPLEXOR_H
#define _MOD_MULTIPLEXOR_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Multiplexor_indexPinFlag 0x00000100
#define MASK_Multiplexor_index 0x00000200
#define OFFSET_Multiplexor_indexPinFlag 0x00000008
#define OFFSET_Multiplexor_index 0x00000009

#define CLASSID_MULTIPLEXOR (CLASS_ID_MODBASE + 103)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMultiplexorInstance
{
    ModuleInstanceDescriptor instance;
    INT32              indexPinFlag;        // Specifies index pin available or not.
    INT32              index;               // Specifies which input pin to route to the output. The index is zero based.
    
} awe_modMultiplexorInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMultiplexorClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modMultiplexorConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_MULTIPLEXOR, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modMultiplexorProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MULTIPLEXOR_H

/**
 * @}
 *
 * End of file.
 */
