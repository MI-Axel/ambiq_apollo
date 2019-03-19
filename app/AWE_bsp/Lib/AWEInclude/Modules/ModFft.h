/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModFft.h
****************************************************************************
*
*     Description:  Forward FFT of real data
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
 * @brief Forward FFT of real data
 */

#ifndef _MOD_FFT_H
#define _MOD_FFT_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Fft_hardware_specific_struct_pointer 0x00000100
#define OFFSET_Fft_hardware_specific_struct_pointer 0x00000008

#define CLASSID_FFT (CLASS_ID_MODBASE + 1269)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modFftInstance
{
    ModuleInstanceDescriptor instance;
    
    void *             hardware_specific_struct_pointer; // This may point to a struct that varies based on the target platform
} awe_modFftInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modFftClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modFftConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modFftProcess(void *pInstance);

UINT32 awe_modFftSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_FFT_H

/**
 * @}
 *
 * End of file.
 */
