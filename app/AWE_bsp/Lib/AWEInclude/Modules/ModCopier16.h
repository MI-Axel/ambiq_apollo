/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*  ModCopier16.h
****************************************************************************
*
*         Description:  Copies input wire to output wire
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
 * @brief Copies input wire to output wire
 */

#ifndef _MOD_COPIER16_H
#define _MOD_COPIER16_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_COPIER16 (CLASS_ID_MODBASE + 3600)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modCopier16Instance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modCopier16Instance;

/* By default the class object is included and this is required for dynamic
 * instantiation.  When doing static code (define AWE_STATIC_CODE) you can save
 * a little bit of memory by eliminating class objects.  However, you lose the
 * ability to change the module status. */

#if (!defined(AWE_NO_CLASS_OBJECTS) || !defined(AWE_STATIC_CODE))
extern const ModClassModule awe_modCopier16Class;
#endif // #ifndef AWE_NO_CLASS_OBJECTS

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modCopier16Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_COPIER16, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modCopier16Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_COPIER16_H

/**
 * @}
 *
 * End of file.
 */
