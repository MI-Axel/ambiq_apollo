/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*  ModAtan2uiApprox.h
****************************************************************************
*
*         Description:  Compute an approximation to the unit interval-valued arctan function, atan2(y, x) / 2pi
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
 * @brief Compute an approximation to the unit interval-valued arctan function, atan2(y, x) / 2pi
 */

#ifndef _MOD_ATAN2UIAPPROX_H
#define _MOD_ATAN2UIAPPROX_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Atan2uiApprox_method 0x00000100
#define OFFSET_Atan2uiApprox_method 0x00000008

#define CLASSID_ATAN2UIAPPROX (CLASS_ID_MODBASE + 5027)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modAtan2uiApproxInstance
{
    ModuleInstanceDescriptor instance;
    int                method;              // Selects the interpolation method: 0=nearest, 1=linear
    
} awe_modAtan2uiApproxInstance;

/* By default the class object is included and this is required for dynamic
 * instantiation.  When doing static code (define AWE_STATIC_CODE) you can save
 * a little bit of memory by eliminating class objects.  However, you lose the
 * ability to change the module status. */

#if !defined(NOREDEF)
extern const ModClassModule awe_modAtan2uiApproxClass;
#endif // #ifndef AWE_NO_CLASS_OBJECTS

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modAtan2uiApproxConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_ATAN2UIAPPROX, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modAtan2uiApproxProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_ATAN2UIAPPROX_H

/**
 * @}
 *
 * End of file.
 */
