/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSubblockStatisticsFract32.h
****************************************************************************
*
*     Description:  Computes statistics at several points in a block of samples
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
 * @brief Computes statistics at several points in a block of samples
 */

#ifndef _MOD_SUBBLOCKSTATISTICSFRACT32_H
#define _MOD_SUBBLOCKSTATISTICSFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SubblockStatisticsFract32_subblockSize 0x00000100
#define MASK_SubblockStatisticsFract32_statisticsType 0x00000200
#define MASK_SubblockStatisticsFract32_nSubblocks 0x00000400
#define OFFSET_SubblockStatisticsFract32_subblockSize 0x00000008
#define OFFSET_SubblockStatisticsFract32_statisticsType 0x00000009
#define OFFSET_SubblockStatisticsFract32_nSubblocks 0x0000000A

#define CLASSID_SUBBLOCKSTATISTICSFRACT32 (CLASS_ID_MODBASE + 1339)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSubblockStatisticsFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              subblockSize;        // Number of samples per subblock to run statistics on.
    INT32              statisticsType;      // Type of statistics calculated.
    INT32              nSubblocks;          // Number of subblocks per input block.
    
} awe_modSubblockStatisticsFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSubblockStatisticsFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSubblockStatisticsFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SUBBLOCKSTATISTICSFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSubblockStatisticsFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SUBBLOCKSTATISTICSFRACT32_H

/**
 * @}
 *
 * End of file.
 */
