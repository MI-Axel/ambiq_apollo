/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModButtons21489EZKIT.h
****************************************************************************
*
*     Description:  Interfaces to the buttons on the 21489 EZ-KIT
*
*     Copyright:	   DSP Concepts, Inc., 2007 - 2015
*                   1800 Wyatt Drive, Suite 14
*                   Sunnyvale, CA 95054
*
***************************************************************************/

/**
 * @addtogroup Modules
 * @{
 */

/**
 * @file
 * @brief Interfaces to the buttons on the 21489 EZ-KIT
 */

#ifndef _MOD_BUTTONS21489EZKIT_H
#define _MOD_BUTTONS21489EZKIT_H

#include "ModCommon.h"
#include "MathHelper.h"


#define CLASSID_BUTTONS21489EZKIT (CLASS_ID_MODBASE + 5318)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modButtons21489EZKITInstance
{
    ModuleInstanceDescriptor instance;
    
    
} awe_modButtons21489EZKITInstance;

/* By default the class object is included and this is required for dynamic
 * instantiation.  When doing static code (define AWE_STATIC_CODE) you can save
 * a little bit of memory by eliminating class objects.  However, you lose the
 * ability to change the module status. */

#if (!defined(AWE_NO_CLASS_OBJECTS) || !defined(AWE_STATIC_CODE))
extern const ModClassModule awe_modButtons21489EZKITClass;
#endif // #ifndef AWE_NO_CLASS_OBJECTS

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modButtons21489EZKITConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modButtons21489EZKITProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BUTTONS21489EZKIT_H

/**
 * @}
 *
 * End of file.
 */
