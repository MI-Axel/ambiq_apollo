/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModWindow.h
****************************************************************************
*
*     Description:  This module applies different types of windows to the input.
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
 * @brief This module applies different types of windows to the input.
 */

#ifndef _MOD_WINDOW_H
#define _MOD_WINDOW_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Window_startIndex 0x00000100
#define MASK_Window_endIndex 0x00000200
#define MASK_Window_amp 0x00000400
#define MASK_Window_winType 0x00000800
#define MASK_Window_window 0x00001000
#define OFFSET_Window_startIndex 0x00000008
#define OFFSET_Window_endIndex 0x00000009
#define OFFSET_Window_amp 0x0000000A
#define OFFSET_Window_winType 0x0000000B
#define OFFSET_Window_window 0x0000000C

#define CLASSID_WINDOW (CLASS_ID_MODBASE + 1357)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modWindowInstance
{
    ModuleInstanceDescriptor instance;
    INT32              startIndex;          // starting of the window that should be extracted.  The range of the startIndex is 0 to (blockSize-1)
    INT32              endIndex;            // ending of the window that should be extracted.  The range of the endIndex is 0 to (blockSize-1)
    FLOAT32            amp;                 // The peak level of the window
    INT32              winType;             // Type of the window
    FLOAT32*           window;              // Window coefficients
} awe_modWindowInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modWindowClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modWindowConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modWindowProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_WINDOW_H

/**
 * @}
 *
 * End of file.
 */
