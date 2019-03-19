/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDateTime.h
****************************************************************************
*
*     Description:  Records the build date and time in two const variables
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
 * @brief Records the build date and time in two const variables
 */

#ifndef _MOD_DATETIME_H
#define _MOD_DATETIME_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DateTime_date 0x00000100
#define MASK_DateTime_time 0x00000200
#define MASK_DateTime_version 0x00000400
#define OFFSET_DateTime_date 0x00000008
#define OFFSET_DateTime_time 0x00000009
#define OFFSET_DateTime_version 0x0000000A

#define CLASSID_DATETIME (CLASS_ID_MODBASE + 1247)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDateTimeInstance
{
    ModuleInstanceDescriptor instance;
    INT32              date;                // Current date in YYMMDD format.
    INT32              time;                // Current time in HHMMSS format.
    INT32              version;             // Current version of the system.
    
} awe_modDateTimeInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDateTimeClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modDateTimeConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_DATETIME, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modDateTimeProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DATETIME_H

/**
 * @}
 *
 * End of file.
 */
