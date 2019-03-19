/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModWithinRange.h
****************************************************************************
*
*     Description:  Checks if the input signal levels are within a specified upper and lower range.
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
 * @brief Checks if the input signal levels are within a specified upper and lower range.
 */

#ifndef _MOD_WITHINRANGE_H
#define _MOD_WITHINRANGE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_WithinRange_lower 0x00000100
#define MASK_WithinRange_upper 0x00000200
#define MASK_WithinRange_withinRange 0x00000400
#define MASK_WithinRange_outputValue 0x00000800
#define OFFSET_WithinRange_lower 0x00000008
#define OFFSET_WithinRange_upper 0x00000009
#define OFFSET_WithinRange_withinRange 0x0000000A
#define OFFSET_WithinRange_outputValue 0x0000000B

#define CLASSID_WITHINRANGE (CLASS_ID_MODBASE + 41)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modWithinRangeInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            lower;               // Lower edge of the allowable range.
    FLOAT32            upper;               // Upper edge of the allowable range.
    INT32              withinRange;         // Equals 1 if all input samples in the block are within range. Otherwise equals 0.
    INT32              outputValue;         // Specifies the behavior of the output pin.
    
} awe_modWithinRangeInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modWithinRangeClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modWithinRangeConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_WITHINRANGE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modWithinRangeProcess(void *pInstance);

 

void awe_modWithinRangeBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_WITHINRANGE_H

/**
 * @}
 *
 * End of file.
 */
