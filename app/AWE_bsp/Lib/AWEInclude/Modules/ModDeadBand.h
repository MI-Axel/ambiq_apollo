/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDeadBand.h
****************************************************************************
*
*     Description:  Dead band module
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
 * @brief Dead band module
 */

#ifndef _MOD_DEADBAND_H
#define _MOD_DEADBAND_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DeadBand_posDelta 0x00000100
#define MASK_DeadBand_negDelta 0x00000200
#define MASK_DeadBand_reset 0x00000400
#define MASK_DeadBand_state 0x00000800
#define OFFSET_DeadBand_posDelta 0x00000008
#define OFFSET_DeadBand_negDelta 0x00000009
#define OFFSET_DeadBand_reset 0x0000000A
#define OFFSET_DeadBand_state 0x0000000B

#define CLASSID_DEADBAND (CLASS_ID_MODBASE + 1248)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDeadBandInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            posDelta;            // Positive change that needs to occur before the output signal is affected
    FLOAT32            negDelta;            // Negative change that needs to occur before the output signal is affected
    INT32              reset;               // Forces the output to equal the input
    FLOAT32*           state;               // State variables.  One per channel
} awe_modDeadBandInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDeadBandClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modDeadBandConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modDeadBandProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_DEADBAND_H

/**
 * @}
 *
 * End of file.
 */
