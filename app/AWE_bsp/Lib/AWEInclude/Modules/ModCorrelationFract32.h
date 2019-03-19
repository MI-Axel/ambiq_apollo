/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModCorrelationFract32.h
****************************************************************************
*
*     Description:  Computes the zero-lag cross correlation
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
 * @brief Computes the zero-lag cross correlation
 */

#ifndef _MOD_CORRELATIONFRACT32_H
#define _MOD_CORRELATIONFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_CorrelationFract32_norm 0x00000100
#define OFFSET_CorrelationFract32_norm 0x00000008

#define CLASSID_CORRELATIONFRACT32 (CLASS_ID_MODBASE + 1245)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modCorrelationFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              norm;                // Type of norm: L1_norm=1, L2_norm=2
    
} awe_modCorrelationFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modCorrelationFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modCorrelationFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_CORRELATIONFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modCorrelationFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_CORRELATIONFRACT32_H

/**
 * @}
 *
 * End of file.
 */
