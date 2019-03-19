/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModBlockStatisticsN.h
****************************************************************************
*
*     Description:  Computes statistics per channel on a block-by-block basis
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
 * @brief Computes statistics per channel on a block-by-block basis
 */

#ifndef _MOD_BLOCKSTATISTICSN_H
#define _MOD_BLOCKSTATISTICSN_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_BlockStatisticsN_statisticsType 0x00000100
#define OFFSET_BlockStatisticsN_statisticsType 0x00000008

#define CLASSID_BLOCKSTATISTICSN (CLASS_ID_MODBASE + 1369)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modBlockStatisticsNInstance
{
    ModuleInstanceDescriptor instance;
    INT32              statisticsType;      // Type of statistics calculated.
    
} awe_modBlockStatisticsNInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modBlockStatisticsNClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modBlockStatisticsNConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_BLOCKSTATISTICSN, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modBlockStatisticsNProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_BLOCKSTATISTICSN_H

/**
 * @}
 *
 * End of file.
 */
