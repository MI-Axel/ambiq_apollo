/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModProbe.h
****************************************************************************
*
*     Description:  Probe module with input and output and an internal buffer
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
 * @brief Probe module with input and output and an internal buffer
 */

#ifndef _MOD_PROBE_H
#define _MOD_PROBE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define DATA_UNCHANGED 0
#define COPY_FROM_WIRE_TO_BUFFER 1
#define COPY_FROM_BUFFER_TO_WIRE 2
#define MASK_Probe_operationType 0x00000100
#define MASK_Probe_value 0x00000200
#define OFFSET_Probe_operationType 0x00000008
#define OFFSET_Probe_value 0x00000009

#define CLASSID_PROBE (CLASS_ID_MODBASE + 2033)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modProbeInstance
{
    ModuleInstanceDescriptor instance;
    INT32              operationType;       // Selects the type of operation that is implemented by the module: DATA_UNCHANGED=0, WIRE_TO_BUFFER=1, BUFFER_TO_WIRE=2
    FLOAT32*           value;               // Array of interleaved audio data.
} awe_modProbeInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modProbeClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modProbeConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modProbeProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_PROBE_H

/**
 * @}
 *
 * End of file.
 */
