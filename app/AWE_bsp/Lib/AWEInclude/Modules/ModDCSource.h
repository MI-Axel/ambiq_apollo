/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDCSource.h
****************************************************************************
*
*     Description:  Outputs a constant DC value
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
 * @brief Outputs a constant DC value
 */

#ifndef _MOD_DCSOURCE_H
#define _MOD_DCSOURCE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DCSource_value 0x00000100
#define OFFSET_DCSource_value 0x00000008

#define CLASSID_DCSOURCE (CLASS_ID_MODBASE + 2005)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDCSourceInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            value;               // Data Value
    
} awe_modDCSourceInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDCSourceClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modDCSourceConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_DCSOURCE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modDCSourceProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DCSOURCE_H

/**
 * @}
 *
 * End of file.
 */
