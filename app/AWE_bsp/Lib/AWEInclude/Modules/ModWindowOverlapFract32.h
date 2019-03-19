/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModWindowOverlapFract32.h
****************************************************************************
*
*     Description:  Windows the signal and accumlates to an internal buffer
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
 * @brief Windows the signal and accumlates to an internal buffer
 */

#ifndef _MOD_WINDOWOVERLAPFRACT32_H
#define _MOD_WINDOWOVERLAPFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_WindowOverlapFract32_window 0x00000100
#define MASK_WindowOverlapFract32_state 0x00000200
#define OFFSET_WindowOverlapFract32_window 0x00000008
#define OFFSET_WindowOverlapFract32_state 0x00000009

#define CLASSID_WINDOWOVERLAPFRACT32 (CLASS_ID_MODBASE + 1358)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modWindowOverlapFract32Instance
{
    ModuleInstanceDescriptor instance;
    
    fract32*           window;              // Window coefficients
    fract32*           state;               // State variable array
} awe_modWindowOverlapFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modWindowOverlapFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modWindowOverlapFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modWindowOverlapFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_WINDOWOVERLAPFRACT32_H

/**
 * @}
 *
 * End of file.
 */
