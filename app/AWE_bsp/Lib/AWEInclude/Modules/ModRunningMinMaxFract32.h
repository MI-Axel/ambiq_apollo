/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModRunningMinMaxFract32.h
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

#ifndef _MOD_RUNNINGMINMAXFRACT32_H
#define _MOD_RUNNINGMINMAXFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_RunningMinMaxFract32_statisticsType 0x00000100
#define MASK_RunningMinMaxFract32_value 0x00000200
#define MASK_RunningMinMaxFract32_reset 0x00000400
#define OFFSET_RunningMinMaxFract32_statisticsType 0x00000008
#define OFFSET_RunningMinMaxFract32_value 0x00000009
#define OFFSET_RunningMinMaxFract32_reset 0x0000000A

#define CLASSID_RUNNINGMINMAXFRACT32 (CLASS_ID_MODBASE + 1311)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modRunningMinMaxFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              statisticsType;      // Type of statistics needed.
    fract32            value;               // Instantaneous output value.
    INT32              reset;               // Trigger pin to reset monitoring.
    
} awe_modRunningMinMaxFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modRunningMinMaxFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modRunningMinMaxFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_RUNNINGMINMAXFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modRunningMinMaxFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_RUNNINGMINMAXFRACT32_H

/**
 * @}
 *
 * End of file.
 */
