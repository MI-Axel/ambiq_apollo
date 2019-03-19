/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAdder.h
****************************************************************************
*
*     Description:  Multi-input adder
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
 * @brief Multi-input adder
 */

#ifndef _MOD_ADDER_H
#define _MOD_ADDER_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Adder_oneChannelOutput 0x00000100
#define OFFSET_Adder_oneChannelOutput 0x00000008

#define CLASSID_ADDER (CLASS_ID_MODBASE + 44)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAdderInstance
{
    ModuleInstanceDescriptor instance;
    INT32              oneChannelOutput;    // Boolean value that determines whether all channels are summed to form a single output.
    
} awe_modAdderInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAdderClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modAdderConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_ADDER, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modAdderProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_ADDER_H

/**
 * @}
 *
 * End of file.
 */
