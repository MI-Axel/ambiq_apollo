/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModCounter.h
****************************************************************************
*
*     Description:  Counter module with optional wrap around
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
 * @brief Counter module with optional wrap around
 */

#ifndef _MOD_COUNTER_H
#define _MOD_COUNTER_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Counter_incTime 0x00000100
#define MASK_Counter_wrap 0x00000200
#define MASK_Counter_count 0x00000400
#define MASK_Counter_sampleCounter 0x00000800
#define MASK_Counter_sampleCounterPeriod 0x00001000
#define OFFSET_Counter_incTime 0x00000008
#define OFFSET_Counter_wrap 0x00000009
#define OFFSET_Counter_count 0x0000000A
#define OFFSET_Counter_sampleCounter 0x0000000B
#define OFFSET_Counter_sampleCounterPeriod 0x0000000C

#define CLASSID_COUNTER (CLASS_ID_MODBASE + 92)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modCounterInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            incTime;             // Time in msec to wait between increments
    UINT32             wrap;                // Counting is performed modulo this value
    UINT32             count;               // Current counter value
    UINT32             sampleCounter;       // Internal variable used to maintain time
    UINT32             sampleCounterPeriod; // Number of samples corresponding to incTime
    
} awe_modCounterInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modCounterClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modCounterConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_COUNTER, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modCounterProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_COUNTER_H

/**
 * @}
 *
 * End of file.
 */
