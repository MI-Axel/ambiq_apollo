/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*  ModSinuiApprox.h
****************************************************************************
*
*         Description:  Computes an approximation to the function sin(x/2pi)
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
 * @brief Computes an approximation to the function sin(x/2pi)
 */

#ifndef _MOD_SINUIAPPROX_H
#define _MOD_SINUIAPPROX_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SinuiApprox_method 0x00000100
#define OFFSET_SinuiApprox_method 0x00000008

#define CLASSID_SINUIAPPROX (CLASS_ID_MODBASE + 5024)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSinuiApproxInstance
{
    ModuleInstanceDescriptor instance;
    int                method;              // Selects the interpolation method: 0=nearest, 1=linear
    
} awe_modSinuiApproxInstance;

/* By default the class object is included and this is required for dynamic
 * instantiation.  When doing static code (define AWE_STATIC_CODE) you can save
 * a little bit of memory by eliminating class objects.  However, you lose the
 * ability to change the module status. */

#if !defined(NOREDEF)
extern const ModClassModule awe_modSinuiApproxClass;
#endif // #ifndef AWE_NO_CLASS_OBJECTS

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSinuiApproxConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SINUIAPPROX, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSinuiApproxProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SINUIAPPROX_H

/**
 * @}
 *
 * End of file.
 */
