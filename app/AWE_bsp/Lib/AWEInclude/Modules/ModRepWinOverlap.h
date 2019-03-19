/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModRepWinOverlap.h
****************************************************************************
*
*     Description:  Replicates, windows, and overlap adds signals
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
 * @brief Replicates, windows, and overlap adds signals
 */

#ifndef _MOD_REPWINOVERLAP_H
#define _MOD_REPWINOVERLAP_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_RepWinOverlap_winLen 0x00000100
#define MASK_RepWinOverlap_repCount 0x00000200
#define MASK_RepWinOverlap_window 0x00000400
#define MASK_RepWinOverlap_state 0x00000800
#define OFFSET_RepWinOverlap_winLen 0x00000008
#define OFFSET_RepWinOverlap_repCount 0x00000009
#define OFFSET_RepWinOverlap_window 0x0000000A
#define OFFSET_RepWinOverlap_state 0x0000000B

#define CLASSID_REPWINOVERLAP (CLASS_ID_MODBASE + 1310)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modRepWinOverlapInstance
{
    ModuleInstanceDescriptor instance;
    INT32              winLen;              // Length of the window
    INT32              repCount;            // Number of times to replicate the input prior to applying the window
    FLOAT32*           window;              // Window coefficients
    FLOAT32*           state;               // State variable array
} awe_modRepWinOverlapInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modRepWinOverlapClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modRepWinOverlapConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modRepWinOverlapProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_REPWINOVERLAP_H

/**
 * @}
 *
 * End of file.
 */
