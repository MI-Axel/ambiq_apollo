/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModIIRHWAccelrator.h
****************************************************************************
*
*     Description:  IIR filter using the SHARC hardware accelerator
*
*     Copyright:    DSP Concepts, Inc, 2007 - 2015
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
 * @brief IIR filter using the SHARC hardware accelerator
 */

#ifndef _MOD_IIRHWACCELRATOR_H
#define _MOD_IIRHWACCELRATOR_H

#include "ModCommon.h"
#include "MathHelper.h"
#ifdef __ADSP21000__
#include "signal.h"
#include<def21469.h>
#include<Cdef21469.h>
asm("#include<def21469.h>;");
#endif

#define MASK_IIRHWAccelrator_numBiquads 0x00000100
#define MASK_IIRHWAccelrator_ping_pong_flag 0x00000200
#define MASK_IIRHWAccelrator_coeffs 0x00000400
#define MASK_IIRHWAccelrator_out_buf 0x00000800
#define MASK_IIRHWAccelrator_iir_hw_instance_ptr 0x00001000
#define OFFSET_IIRHWAccelrator_numBiquads 0x00000008
#define OFFSET_IIRHWAccelrator_ping_pong_flag 0x00000009
#define OFFSET_IIRHWAccelrator_coeffs 0x0000000A
#define OFFSET_IIRHWAccelrator_out_buf 0x0000000B
#define OFFSET_IIRHWAccelrator_iir_hw_instance_ptr 0x0000000C

#define CLASSID_IIRHWACCELRATOR (CLASS_ID_MODBASE + 5316)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modIIRHWAccelratorInstance
{
    ModuleInstanceDescriptor instance;
#ifdef __ADSP21000__
    int                numBiquads;          // Length of the filter
    int                ping_pong_flag;      // status flag
    float*             coeffs;              // Coefficient array
    float*             out_buf;             // State variable array
    iir_hw_accelrator_t    iir_hw_instance_ptr; // Structure of iir hw instance
#endif
} awe_modIIRHWAccelratorInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modIIRHWAccelratorClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modIIRHWAccelratorConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modIIRHWAccelratorProcess(void *pInstance);

UINT32 awe_modIIRHWAccelratorSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_IIRHWACCELRATOR_H

/**
 * @}
 *
 * End of file.
 */
