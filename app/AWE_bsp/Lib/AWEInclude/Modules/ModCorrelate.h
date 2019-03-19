/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModCorrelate.h
****************************************************************************
*
*     Description:  Cross correlation function
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
 * @brief Cross correlation function
 */

#ifndef _MOD_CORRELATE_H
#define _MOD_CORRELATE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Correlate_shape 0x00000100
#define MASK_Correlate_skip 0x00000200
#define MASK_Correlate_olen 0x00000400
#define OFFSET_Correlate_shape 0x00000008
#define OFFSET_Correlate_skip 0x00000009
#define OFFSET_Correlate_olen 0x0000000A

#define CLASSID_CORRELATE (CLASS_ID_MODBASE + 1244)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modCorrelateInstance
{
    ModuleInstanceDescriptor instance;
    INT32              shape;               // Shape of subset to calculate
    INT32              skip;                // Number of samples of full cross correlation to skip at output
    INT32              olen;                // Length of output
    
} awe_modCorrelateInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modCorrelateClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modCorrelateConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_CORRELATE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modCorrelateProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_CORRELATE_H

/**
 * @}
 *
 * End of file.
 */
