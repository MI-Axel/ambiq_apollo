/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModAdderInt32.h
****************************************************************************
*
*     Description:  Adds integer signals
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
 * @brief Adds integer signals
 */

#ifndef _MOD_ADDERINT32_H
#define _MOD_ADDERINT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_AdderInt32_oneChannelOutput 0x00000100
#define OFFSET_AdderInt32_oneChannelOutput 0x00000008

#define CLASSID_ADDERINT32 (CLASS_ID_MODBASE + 45)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAdderInt32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              oneChannelOutput;    // Boolean value that determines whether all channels are summed to form a single output.
    
} awe_modAdderInt32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modAdderInt32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modAdderInt32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_ADDERINT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modAdderInt32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_ADDERINT32_H

/**
 * @}
 *
 * End of file.
 */
