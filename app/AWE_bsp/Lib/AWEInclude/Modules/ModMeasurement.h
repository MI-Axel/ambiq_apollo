/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMeasurement.h
****************************************************************************
*
*     Description:  Performs transfer function measurements
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
 * @brief Performs transfer function measurements
 */

#ifndef _MOD_MEASUREMENT_H
#define _MOD_MEASUREMENT_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Measurement_L 0x00000100
#define MASK_Measurement_numReps 0x00000200
#define MASK_Measurement_trigger 0x00000400
#define MASK_Measurement_readIndex 0x00000800
#define MASK_Measurement_stateIndex 0x00001000
#define MASK_Measurement_cnt 0x00002000
#define MASK_Measurement_stimulus 0x00004000
#define MASK_Measurement_response 0x00008000
#define OFFSET_Measurement_L 0x00000008
#define OFFSET_Measurement_numReps 0x00000009
#define OFFSET_Measurement_trigger 0x0000000A
#define OFFSET_Measurement_readIndex 0x0000000B
#define OFFSET_Measurement_stateIndex 0x0000000C
#define OFFSET_Measurement_cnt 0x0000000D
#define OFFSET_Measurement_stimulus 0x0000000E
#define OFFSET_Measurement_response 0x0000000F

#define CLASSID_MEASUREMENT (CLASS_ID_MODBASE + 1296)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMeasurementInstance
{
    ModuleInstanceDescriptor instance;
    INT32              L;                   // Length of the stimulus signal.
    INT32              numReps;             // Number of times to repeat the stimulus and average the result
    INT32              trigger;             // state variable/parameter which the PC sets to trigger the measurement.
    INT32              readIndex;           // Index used for circular reading
    INT32              stateIndex;          // Index used for state
    INT32              cnt;                 // Index used to measure the response
    FLOAT32*           stimulus;            // Column vector of length L holding the stimulus signal
    FLOAT32*           response;            // Holds the time average measured signal
} awe_modMeasurementInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMeasurementClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modMeasurementConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modMeasurementProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MEASUREMENT_H

/**
 * @}
 *
 * End of file.
 */
