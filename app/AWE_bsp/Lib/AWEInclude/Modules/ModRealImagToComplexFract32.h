/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModRealImagToComplexFract32.h
****************************************************************************
*
*     Description:  converts separate real and imaginary components into a complex signal
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
 * @brief converts separate real and imaginary components into a complex signal
 */

#ifndef _MOD_REALIMAGTOCOMPLEXFRACT32_H
#define _MOD_REALIMAGTOCOMPLEXFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_REALIMAGTOCOMPLEXFRACT32 (CLASS_ID_MODBASE + 1307)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modRealImagToComplexFract32Instance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modRealImagToComplexFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modRealImagToComplexFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modRealImagToComplexFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_REALIMAGTOCOMPLEXFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modRealImagToComplexFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_REALIMAGTOCOMPLEXFRACT32_H

/**
 * @}
 *
 * End of file.
 */
