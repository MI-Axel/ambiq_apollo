/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModCfft.h
****************************************************************************
*
*     Description:  Forward and inverse FFT of complex data
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
 * @brief Forward and inverse FFT of complex data
 */

#ifndef _MOD_CFFT_H
#define _MOD_CFFT_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_Cfft_dir 0x00000100
#define MASK_Cfft_hardware_specific_struct_pointer 0x00000200
#define MASK_Cfft_fft_size_aligned_io_buffer_pointer 0x00000400
#define MASK_Cfft_fft_twiddle_buffer_pointer 0x00000800
#define OFFSET_Cfft_dir 0x00000008
#define OFFSET_Cfft_hardware_specific_struct_pointer 0x00000009
#define OFFSET_Cfft_fft_size_aligned_io_buffer_pointer 0x0000000A
#define OFFSET_Cfft_fft_twiddle_buffer_pointer 0x0000000B

#define CLASSID_CFFT (CLASS_ID_MODBASE + 1230)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modCfftInstance
{
    ModuleInstanceDescriptor instance;
    INT32              dir;                 // Transform direction.  Forward = 1. Inverse = -1
    void *             hardware_specific_struct_pointer; // This may point to a struct that varies based on the target platform
    void *             fft_size_aligned_io_buffer_pointer; // This points to a buffer which is aligned by fft size on SHARC
    void *             fft_twiddle_buffer_pointer; // This points to twiddle buffer on SHARC
} awe_modCfftInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modCfftClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modCfftConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modCfftProcess(void *pInstance);

UINT32 awe_modCfftSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_CFFT_H

/**
 * @}
 *
 * End of file.
 */
