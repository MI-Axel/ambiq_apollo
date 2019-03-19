/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModWindowAliasFract32.h
****************************************************************************
*
*     Description:  Applies a time domain window and optionally aliases the result to a shorter length
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
 * @brief Applies a time domain window and optionally aliases the result to a shorter length
 */

#ifndef _MOD_WINDOWALIASFRACT32_H
#define _MOD_WINDOWALIASFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_WindowAliasFract32_winLen 0x00000100
#define MASK_WindowAliasFract32_stateIndex 0x00000200
#define MASK_WindowAliasFract32_numAliasSections 0x00000400
#define MASK_WindowAliasFract32_postShift 0x00000800
#define MASK_WindowAliasFract32_window 0x00001000
#define MASK_WindowAliasFract32_windowFract32 0x00002000
#define MASK_WindowAliasFract32_state 0x00004000
#define OFFSET_WindowAliasFract32_winLen 0x00000008
#define OFFSET_WindowAliasFract32_stateIndex 0x00000009
#define OFFSET_WindowAliasFract32_numAliasSections 0x0000000A
#define OFFSET_WindowAliasFract32_postShift 0x0000000B
#define OFFSET_WindowAliasFract32_window 0x0000000C
#define OFFSET_WindowAliasFract32_windowFract32 0x0000000D
#define OFFSET_WindowAliasFract32_state 0x0000000E

#define CLASSID_WINDOWALIASFRACT32 (CLASS_ID_MODBASE + 1354)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modWindowAliasFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              winLen;              // Length of the window
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables
    INT32              numAliasSections;    // Number of sections that are aliased to form the output.  Equals WLEN/OLEN
    INT32              postShift;           // Number of bits to shift
    FLOAT32*           window;              // Window coefficients
    fract32*           windowFract32;       // Window coefficients in fractional representation
    fract32*           state;               // State variable array
} awe_modWindowAliasFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modWindowAliasFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modWindowAliasFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modWindowAliasFract32Process(void *pInstance);

UINT32 awe_modWindowAliasFract32Set(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_WINDOWALIASFRACT32_H

/**
 * @}
 *
 * End of file.
 */
