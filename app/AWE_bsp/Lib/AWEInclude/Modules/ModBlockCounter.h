/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBlockCounter.h
****************************************************************************
*
*     Description:  Incremets internal counter per call and sends the count value on control output pin
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
 * @brief Incremets internal counter per call and sends the count value on control output pin
 */

#ifndef _MOD_BLOCKCOUNTER_H
#define _MOD_BLOCKCOUNTER_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_BlockCounter_counter 0x00000100
#define OFFSET_BlockCounter_counter 0x00000008

#define CLASSID_BLOCKCOUNTER (CLASS_ID_MODBASE + 91)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBlockCounterInstance
{
    ModuleInstanceDescriptor instance;
    INT32              counter;             // Internal counter increments per call.
    
} awe_modBlockCounterInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBlockCounterClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modBlockCounterConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_BLOCKCOUNTER, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modBlockCounterProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BLOCKCOUNTER_H

/**
 * @}
 *
 * End of file.
 */
