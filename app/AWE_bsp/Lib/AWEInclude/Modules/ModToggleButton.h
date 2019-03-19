/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModToggleButton.h
****************************************************************************
*
*     Description:  Converts momentary button signals to toggles
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
 * @brief Converts momentary button signals to toggles
 */

#ifndef _MOD_TOGGLEBUTTON_H
#define _MOD_TOGGLEBUTTON_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ToggleButton_inState 0x00000100
#define MASK_ToggleButton_outState 0x00000200
#define OFFSET_ToggleButton_inState 0x00000008
#define OFFSET_ToggleButton_outState 0x00000009

#define CLASSID_TOGGLEBUTTON (CLASS_ID_MODBASE + 40)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modToggleButtonInstance
{
    ModuleInstanceDescriptor instance;
    INT32              inState;             // Last input to the module
    INT32              outState;            // Last output of the module
    
} awe_modToggleButtonInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modToggleButtonClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modToggleButtonConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_TOGGLEBUTTON, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modToggleButtonProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_TOGGLEBUTTON_H

/**
 * @}
 *
 * End of file.
 */
