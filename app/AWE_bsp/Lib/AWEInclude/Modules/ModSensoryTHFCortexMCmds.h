/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSensoryTHFCortexMCmds.h
****************************************************************************
*
*     Description:  Sensory Voice Command
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
 * @brief Sensory Voice Command
 */

#ifndef _MOD_SENSORYTHFCORTEXMCMDS_H
#define _MOD_SENSORYTHFCORTEXMCMDS_H

#include "ModCommon.h"
#include "MathHelper.h"

 
typedef struct {
    void * pAppStruct;
    volatile const char * szErrorReason;
    volatile INT32 nDelaySampleCnt;
    int state;
    BOOL bInitialized;
    UINT32 nInitializedItemsMask;
} STATIC_VARS;
#define TRIGGER_DELAY 240
#define COMMAND_DELAY 0
enum {STATE_RESTART_TRIGGER, STATE_TRIGGER, STATE_RESTART_COMMAND, STATE_COMMAND};
 
#define MASK_SensoryTHFCortexMCmds_commandWaitTimeout 0x00000100
#define MASK_SensoryTHFCortexMCmds_triggerWordBufferLen 0x00000200
#define MASK_SensoryTHFCortexMCmds_commandWordBufferLen 0x00000400
#define MASK_SensoryTHFCortexMCmds_enableTriggerPhrase 0x00000800
#define MASK_SensoryTHFCortexMCmds_nAPIResult 0x00001000
#define MASK_SensoryTHFCortexMCmds_triggerWordGrammarData 0x00002000
#define MASK_SensoryTHFCortexMCmds_commandWordGrammarData 0x00004000
#define MASK_SensoryTHFCortexMCmds_pGlobals 0x00008000
#define MASK_SensoryTHFCortexMCmds_pAudioFrame 0x00010000
#define MASK_SensoryTHFCortexMCmds_pAudioBuffer 0x00020000
#define OFFSET_SensoryTHFCortexMCmds_commandWaitTimeout 0x00000008
#define OFFSET_SensoryTHFCortexMCmds_triggerWordBufferLen 0x00000009
#define OFFSET_SensoryTHFCortexMCmds_commandWordBufferLen 0x0000000A
#define OFFSET_SensoryTHFCortexMCmds_enableTriggerPhrase 0x0000000B
#define OFFSET_SensoryTHFCortexMCmds_nAPIResult 0x0000000C
#define OFFSET_SensoryTHFCortexMCmds_triggerWordGrammarData 0x0000000D
#define OFFSET_SensoryTHFCortexMCmds_commandWordGrammarData 0x0000000E
#define OFFSET_SensoryTHFCortexMCmds_pGlobals 0x0000000F
#define OFFSET_SensoryTHFCortexMCmds_pAudioFrame 0x00000010
#define OFFSET_SensoryTHFCortexMCmds_pAudioBuffer 0x00000011

#define CLASSID_SENSORYTHFCORTEXMCMDS (CLASS_ID_MODBASE + 30106)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSensoryTHFCortexMCmdsInstance
{
    ModuleInstanceDescriptor instance;
    INT32              commandWaitTimeout;  // Timeout in seconds to look for command after trigger word
    INT32              triggerWordBufferLen; // Count of 16-bit values in the grammar data buffer
    INT32              commandWordBufferLen; // Count of 16-bit values in the grammar data buffer
    INT32              enableTriggerPhrase; // Enable trigger phrase detection
    INT32              nAPIResult;          // Return status for last call into the embedded Sensory API
    INT32*             triggerWordGrammarData; // Trigger word grammar file data
    INT32*             commandWordGrammarData; // Command word grammar file data
    STATIC_VARS *      pGlobals;            // Points to the global variables structure
    fract16 *          pAudioFrame;         // Points to a buffer to hold a fract16 audio frame
    fract16 *          pAudioBuffer;        // Points to a buffer for algorithm processing
} awe_modSensoryTHFCortexMCmdsInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSensoryTHFCortexMCmdsClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modSensoryTHFCortexMCmdsConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modSensoryTHFCortexMCmdsProcess(void *pInstance);

UINT32 awe_modSensoryTHFCortexMCmdsSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SENSORYTHFCORTEXMCMDS_H

/**
 * @}
 *
 * End of file.
 */
