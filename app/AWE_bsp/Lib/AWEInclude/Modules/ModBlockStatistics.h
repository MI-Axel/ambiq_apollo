/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBlockStatistics.h
****************************************************************************
*
*     Description:  Computes statistics of a block of samples
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
 * @brief Computes statistics of a block of samples
 */

#ifndef _MOD_BLOCKSTATISTICS_H
#define _MOD_BLOCKSTATISTICS_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_BlockStatistics_statisticsType 0x00000100
#define MASK_BlockStatistics_instantaneousValue 0x00000200
#define OFFSET_BlockStatistics_statisticsType 0x00000008
#define OFFSET_BlockStatistics_instantaneousValue 0x00000009

#define CLASSID_BLOCKSTATISTICS (CLASS_ID_MODBASE + 1227)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBlockStatisticsInstance
{
    ModuleInstanceDescriptor instance;
    INT32              statisticsType;      // Type of statistics calculated.
    FLOAT32            instantaneousValue;  // Instantaneous output value.
    
} awe_modBlockStatisticsInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBlockStatisticsClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modBlockStatisticsConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_BLOCKSTATISTICS, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modBlockStatisticsProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BLOCKSTATISTICS_H

/**
 * @}
 *
 * End of file.
 */
