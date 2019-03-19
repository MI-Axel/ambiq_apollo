/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModRunningMinMax.h
****************************************************************************
*
*     Description:  Computes long term min/max/max abs
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
 * @brief Computes long term min/max/max abs
 */

#ifndef _MOD_RUNNINGMINMAX_H
#define _MOD_RUNNINGMINMAX_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_RunningMinMax_statisticsType 0x00000100
#define MASK_RunningMinMax_value 0x00000200
#define MASK_RunningMinMax_reset 0x00000400
#define OFFSET_RunningMinMax_statisticsType 0x00000008
#define OFFSET_RunningMinMax_value 0x00000009
#define OFFSET_RunningMinMax_reset 0x0000000A

#define CLASSID_RUNNINGMINMAX (CLASS_ID_MODBASE + 1312)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modRunningMinMaxInstance
{
    ModuleInstanceDescriptor instance;
    INT32              statisticsType;      // Type of statistics needed.
    FLOAT32            value;               // Instantaneous output value.
    INT32              reset;               // Trigger pin to reset monitoring.
    
} awe_modRunningMinMaxInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modRunningMinMaxClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modRunningMinMaxConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_RUNNINGMINMAX, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modRunningMinMaxProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_RUNNINGMINMAX_H

/**
 * @}
 *
 * End of file.
 */
