/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModConsecutiveCountInt.h
****************************************************************************
*
*     Description:  Counts repeated input values
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
 * @brief Counts repeated input values
 */

#ifndef _MOD_CONSECUTIVECOUNTINT_H
#define _MOD_CONSECUTIVECOUNTINT_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ConsecutiveCountInt_value 0x00000100
#define MASK_ConsecutiveCountInt_count 0x00000200
#define OFFSET_ConsecutiveCountInt_value 0x00000008
#define OFFSET_ConsecutiveCountInt_count 0x00000009

#define CLASSID_CONSECUTIVECOUNTINT (CLASS_ID_MODBASE + 1242)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modConsecutiveCountIntInstance
{
    ModuleInstanceDescriptor instance;
    INT32              value;               // Equals the last input sample
    UINT32             count;               // Number of consecutive times that the last input sample was seen
    
} awe_modConsecutiveCountIntInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modConsecutiveCountIntClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modConsecutiveCountIntConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_CONSECUTIVECOUNTINT, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modConsecutiveCountIntProcess(void *pInstance);

 

void awe_modConsecutiveCountIntBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_CONSECUTIVECOUNTINT_H

/**
 * @}
 *
 * End of file.
 */
