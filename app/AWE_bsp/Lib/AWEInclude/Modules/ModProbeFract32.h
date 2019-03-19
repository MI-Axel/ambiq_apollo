/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModProbeFract32.h
****************************************************************************
*
*     Description:  Source buffer holding 1 wire of data
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
 * @brief Source buffer holding 1 wire of data
 */

#ifndef _MOD_PROBEFRACT32_H
#define _MOD_PROBEFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define DATA_UNCHANGED 0
#define COPY_FROM_WIRE_TO_BUFFER 1
#define COPY_FROM_BUFFER_TO_WIRE 2
#define MASK_ProbeFract32_operationType 0x00000100
#define MASK_ProbeFract32_value 0x00000200
#define OFFSET_ProbeFract32_operationType 0x00000008
#define OFFSET_ProbeFract32_value 0x00000009

#define CLASSID_PROBEFRACT32 (CLASS_ID_MODBASE + 1304)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modProbeFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              operationType;       // Selects the type of operation that is implemented by the module: DATA_UNCHANGED=0 WIRE_TO_BUFFER=1 BUFFER_TO_WIRE=2
    fract32*           value;               // Array of interleaved audio data
} awe_modProbeFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modProbeFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modProbeFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modProbeFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_PROBEFRACT32_H

/**
 * @}
 *
 * End of file.
 */
