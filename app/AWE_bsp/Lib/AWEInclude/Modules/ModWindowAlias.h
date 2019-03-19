/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModWindowAlias.h
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

#ifndef _MOD_WINDOWALIAS_H
#define _MOD_WINDOWALIAS_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_WindowAlias_winLen 0x00000100
#define MASK_WindowAlias_stateIndex 0x00000200
#define MASK_WindowAlias_numAliasSections 0x00000400
#define MASK_WindowAlias_window 0x00000800
#define MASK_WindowAlias_state 0x00001000
#define OFFSET_WindowAlias_winLen 0x00000008
#define OFFSET_WindowAlias_stateIndex 0x00000009
#define OFFSET_WindowAlias_numAliasSections 0x0000000A
#define OFFSET_WindowAlias_window 0x0000000B
#define OFFSET_WindowAlias_state 0x0000000C

#define CLASSID_WINDOWALIAS (CLASS_ID_MODBASE + 1355)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modWindowAliasInstance
{
    ModuleInstanceDescriptor instance;
    INT32              winLen;              // Length of the window
    INT32              stateIndex;          // Index of the oldest state variable in the array of state variables
    INT32              numAliasSections;    // Number of sections that are aliased to form the output.  Equals WLEN/OLEN
    FLOAT32*           window;              // Window coefficients
    FLOAT32*           state;               // State variable array
} awe_modWindowAliasInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modWindowAliasClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modWindowAliasConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modWindowAliasProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_WINDOWALIAS_H

/**
 * @}
 *
 * End of file.
 */
