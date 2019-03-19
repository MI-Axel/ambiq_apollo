/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModWindowFract32.h
****************************************************************************
*
*     Description:  Applies a time domain window
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
 * @brief Applies a time domain window
 */

#ifndef _MOD_WINDOWFRACT32_H
#define _MOD_WINDOWFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_WindowFract32_winLen 0x00000100
#define MASK_WindowFract32_postShift 0x00000200
#define MASK_WindowFract32_window 0x00000400
#define MASK_WindowFract32_windowFract32 0x00000800
#define OFFSET_WindowFract32_winLen 0x00000008
#define OFFSET_WindowFract32_postShift 0x00000009
#define OFFSET_WindowFract32_window 0x0000000A
#define OFFSET_WindowFract32_windowFract32 0x0000000B

#define CLASSID_WINDOWFRACT32 (CLASS_ID_MODBASE + 1356)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modWindowFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              winLen;              // Length of the window
    INT32              postShift;           // Number of bits to shift
    FLOAT32*           window;              // Window coefficients
    fract32*           windowFract32;       // Window coefficients in fractional representation
} awe_modWindowFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modWindowFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modWindowFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modWindowFract32Process(void *pInstance);

UINT32 awe_modWindowFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_WINDOWFRACT32_H

/**
 * @}
 *
 * End of file.
 */
