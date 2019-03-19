/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModRunningStatisticsFract32.h
****************************************************************************
*
*     Description:  Computes long term statistics. Fract32 version.
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
 * @brief Computes long term statistics. Fract32 version.
 */

#ifndef _MOD_RUNNINGSTATISTICSFRACT32_H
#define _MOD_RUNNINGSTATISTICSFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_RunningStatisticsFract32_statisticsType 0x00000100
#define MASK_RunningStatisticsFract32_value 0x00000200
#define MASK_RunningStatisticsFract32_mean 0x00000400
#define MASK_RunningStatisticsFract32_avgEnergy 0x00000800
#define MASK_RunningStatisticsFract32_numBlocksProcessed 0x00001000
#define MASK_RunningStatisticsFract32_reset 0x00002000
#define OFFSET_RunningStatisticsFract32_statisticsType 0x00000008
#define OFFSET_RunningStatisticsFract32_value 0x00000009
#define OFFSET_RunningStatisticsFract32_mean 0x0000000A
#define OFFSET_RunningStatisticsFract32_avgEnergy 0x0000000B
#define OFFSET_RunningStatisticsFract32_numBlocksProcessed 0x0000000C
#define OFFSET_RunningStatisticsFract32_reset 0x0000000D

#define CLASSID_RUNNINGSTATISTICSFRACT32 (CLASS_ID_MODBASE + 1313)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modRunningStatisticsFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              statisticsType;      // Type of statistics needed.
    fract32            value;               // Instantaneous output value.
    fract32            mean;                // Instantaneous mean value.
    fract32            avgEnergy;           // State variable for average energy.
    INT32              numBlocksProcessed;  // Counter for the number of blocks processed.
    INT32              reset;               // Used to identify the first block which is processed.
    
} awe_modRunningStatisticsFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modRunningStatisticsFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modRunningStatisticsFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_RUNNINGSTATISTICSFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modRunningStatisticsFract32Process(void *pInstance);

UINT32 awe_modRunningStatisticsFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_RUNNINGSTATISTICSFRACT32_H

/**
 * @}
 *
 * End of file.
 */
