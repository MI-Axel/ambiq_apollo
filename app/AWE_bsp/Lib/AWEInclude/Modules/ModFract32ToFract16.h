/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*  ModFract32ToFract16.h
****************************************************************************
*
*         Description:  Fract32 to Fract16 data type conversion
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
 * @brief Fract32 to Fract16 data type conversion
 */

#ifndef _MOD_FRACT32TOFRACT16_H
#define _MOD_FRACT32TOFRACT16_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_FRACT32TOFRACT16 (CLASS_ID_MODBASE + 3602)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modFract32ToFract16Instance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modFract32ToFract16Instance;

/* By default the class object is included and this is required for dynamic
 * instantiation.  When doing static code (define AWE_STATIC_CODE) you can save
 * a little bit of memory by eliminating class objects.  However, you lose the
 * ability to change the module status. */

#if (!defined(AWE_NO_CLASS_OBJECTS) || !defined(AWE_STATIC_CODE))
extern const ModClassModule awe_modFract32ToFract16Class;
#endif // #ifndef AWE_NO_CLASS_OBJECTS

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modFract32ToFract16Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_FRACT32TOFRACT16, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modFract32ToFract16Process(void *pInstance);

 

void awe_modFract32ToFract16Bypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_FRACT32TOFRACT16_H

/**
 * @}
 *
 * End of file.
 */
