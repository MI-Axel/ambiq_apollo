/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModFIRHWAccelerator.h
****************************************************************************
*
*     Description:  FIR filter using the SHARC hardware accelerator
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
 * @brief FIR filter using the SHARC hardware accelerator
 */

#ifndef _MOD_FIRHWACCELERATOR_H
#define _MOD_FIRHWACCELERATOR_H

#include "ModCommon.h"
#include "MathHelper.h"
#ifdef __ADSP21000__
#include "signal.h"
#include<def21469.h>
#include<Cdef21469.h>
#endif

#define MASK_FIRHWAccelerator_totalNumTaps 0x00000100
#define MASK_FIRHWAccelerator_stateSize 0x00000200
#define MASK_FIRHWAccelerator_coeffs 0x00000400
#define MASK_FIRHWAccelerator_state 0x00000800
#define MASK_FIRHWAccelerator_firTcbCh 0x00001000
#define MASK_FIRHWAccelerator_writeIndex 0x00002000
#define MASK_FIRHWAccelerator_numTaps 0x00004000
#define MASK_FIRHWAccelerator_outBuf 0x00008000
#define OFFSET_FIRHWAccelerator_totalNumTaps 0x00000008
#define OFFSET_FIRHWAccelerator_stateSize 0x00000009
#define OFFSET_FIRHWAccelerator_coeffs 0x0000000A
#define OFFSET_FIRHWAccelerator_state 0x0000000B
#define OFFSET_FIRHWAccelerator_firTcbCh 0x0000000C
#define OFFSET_FIRHWAccelerator_writeIndex 0x0000000D
#define OFFSET_FIRHWAccelerator_numTaps 0x0000000E
#define OFFSET_FIRHWAccelerator_outBuf 0x0000000F

#define CLASSID_FIRHWACCELERATOR (CLASS_ID_MODBASE + 5315)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modFIRHWAcceleratorInstance
{
    ModuleInstanceDescriptor instance;
#ifdef __ADSP21000__
    int                totalNumTaps;        // total numTaps of all channels
    int                stateSize;           // total state size
    float*             coeffs;              // Coefficient array
    float*             state;               // State variable array
    int*               firTcbCh;            // TCB structure
    int*               writeIndex;          // TCB structure
    int*               numTaps;             // separate filter size for each channel
    float*             outBuf;              // State variable array
#endif
} awe_modFIRHWAcceleratorInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modFIRHWAcceleratorClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modFIRHWAcceleratorConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modFIRHWAcceleratorProcess(void *pInstance);

UINT32 awe_modFIRHWAcceleratorSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_FIRHWACCELERATOR_H

/**
 * @}
 *
 * End of file.
 */
