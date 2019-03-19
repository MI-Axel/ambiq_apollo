/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModTypeConversion.h
****************************************************************************
*
*     Description:  Converts between numeric data types
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
 * @brief Converts between numeric data types
 */

#ifndef _MOD_TYPECONVERSION_H
#define _MOD_TYPECONVERSION_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_TypeConversion_inputType 0x00000100
#define MASK_TypeConversion_outputType 0x00000200
#define OFFSET_TypeConversion_inputType 0x00000008
#define OFFSET_TypeConversion_outputType 0x00000009

#define CLASSID_TYPECONVERSION (CLASS_ID_MODBASE + 102)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modTypeConversionInstance
{
    ModuleInstanceDescriptor instance;
    INT32              inputType;           // Specifies the dataType of the input
    INT32              outputType;          // Specifies the dataType of the output
    
} awe_modTypeConversionInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modTypeConversionClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modTypeConversionConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_TYPECONVERSION, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modTypeConversionProcess(void *pInstance);

 

void awe_modTypeConversionBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_TYPECONVERSION_H

/**
 * @}
 *
 * End of file.
 */
