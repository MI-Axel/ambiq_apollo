/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*  ModCexpuiApprox.h
****************************************************************************
*
*         Description:  Compute an approximation to the unit interval complex exponential function, exp(jx/2pi)
*
*         Copyright:	DSP Concepts, Inc., 2007 - 2012
*                       568 E. Weddell Drive, Suite 3
*                       Sunnyvale, CA 94089
*
***************************************************************************/

/**
 * @addtogroup Modules
 * @{
 */

/**
 * @file
 * @brief Compute an approximation to the unit interval complex exponential function, exp(jx/2pi)
 */

#ifndef _MOD_CEXPUIAPPROX_H
#define _MOD_CEXPUIAPPROX_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_CexpuiApprox_method 0x00000100
#define OFFSET_CexpuiApprox_method 0x00000008

#define CLASSID_CEXPUIAPPROX (CLASS_ID_MODBASE + 5025)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modCexpuiApproxInstance
{
    ModuleInstanceDescriptor instance;
    int                method;              // Selects the interpolation method: 0=nearest, 1=linear
    
} awe_modCexpuiApproxInstance;

/* By default the class object is included and this is required for dynamic
 * instantiation.  When doing static code (define AWE_STATIC_CODE) you can save
 * a little bit of memory by eliminating class objects.  However, you lose the
 * ability to change the module status. */

#if !defined(NOREDEF)
extern const ModClassModule awe_modCexpuiApproxClass;
#endif // #ifndef AWE_NO_CLASS_OBJECTS

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modCexpuiApproxConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_CEXPUIAPPROX, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modCexpuiApproxProcess(void *pInstance);

 

void awe_modCexpuiApproxBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_CEXPUIAPPROX_H

/**
 * @}
 *
 * End of file.
 */
