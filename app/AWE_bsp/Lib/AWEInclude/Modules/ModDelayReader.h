/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModDelayReader.h
****************************************************************************
*
*     Description:  Reads the data from a delay_state_writer_module with a given delay
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
 * @brief Reads the data from a delay_state_writer_module with a given delay
 */

#ifndef _MOD_DELAYREADER_H
#define _MOD_DELAYREADER_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_DelayReader_maxDelay 0x00000100
#define MASK_DelayReader_currentDelay 0x00000200
#define MASK_DelayReader_interpolationType 0x00000400
#define MASK_DelayReader_dswObjectID 0x00000800
#define MASK_DelayReader_dswObjectPtr 0x00001000
#define OFFSET_DelayReader_maxDelay 0x00000008
#define OFFSET_DelayReader_currentDelay 0x00000009
#define OFFSET_DelayReader_interpolationType 0x0000000A
#define OFFSET_DelayReader_dswObjectID 0x0000000B
#define OFFSET_DelayReader_dswObjectPtr 0x0000000C

#define CLASSID_DELAYREADER (CLASS_ID_MODBASE + 1251)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modDelayReaderInstance
{
    ModuleInstanceDescriptor instance;
    INT32              maxDelay;            // Max Delay of the writer module (per channel)
    FLOAT32            currentDelay;        // Current delay
    INT32              interpolationType;   // Interpolation type - linear, cubic, etc
    INT32              dswObjectID;         // Object ID of the upstream DelayStateWriter module
    void *             dswObjectPtr;        // Points to the upstream DelayStateWriter module
} awe_modDelayReaderInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modDelayReaderClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modDelayReaderConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_DELAYREADER, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modDelayReaderProcess(void *pInstance);

 

void awe_modDelayReaderBypass(void *pInstance);


#ifdef __cplusplus
}
#endif


#endif // _MOD_DELAYREADER_H

/**
 * @}
 *
 * End of file.
 */
