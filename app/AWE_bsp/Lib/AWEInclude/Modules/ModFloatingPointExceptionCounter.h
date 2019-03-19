/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModFloatingPointExceptionCounter.h
****************************************************************************
*
*     Description:  Counts each floating point exception per block in the system
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
 * @brief Counts each floating point exception per block in the system
 */

#ifndef _MOD_FLOATINGPOINTEXCEPTIONCOUNTER_H
#define _MOD_FLOATINGPOINTEXCEPTIONCOUNTER_H

#include "ModCommon.h"
#include "MathHelper.h"
#ifdef __ADSP21000__
#include "sysreg.h"
#include<def21489.h>
#include<Cdef21489.h>
#endif

#define MASK_FloatingPointExceptionCounter_ResetCounter 0x00000100
#define MASK_FloatingPointExceptionCounter_ALUInvalidCnt 0x00000200
#define MASK_FloatingPointExceptionCounter_ALUOverflowCnt 0x00000400
#define MASK_FloatingPointExceptionCounter_ALUUnderflowCnt 0x00000800
#define MASK_FloatingPointExceptionCounter_ALUFixOverflowCnt 0x00001000
#define MASK_FloatingPointExceptionCounter_ALUInvalidCntY 0x00002000
#define MASK_FloatingPointExceptionCounter_ALUOverflowCntY 0x00004000
#define MASK_FloatingPointExceptionCounter_ALUUnderflowCntY 0x00008000
#define MASK_FloatingPointExceptionCounter_ALUFixOverflowCntY 0x00010000
#define MASK_FloatingPointExceptionCounter_MULInvalidCnt 0x00020000
#define MASK_FloatingPointExceptionCounter_MULOverflowCnt 0x00040000
#define MASK_FloatingPointExceptionCounter_MULUnderflowCnt 0x00080000
#define MASK_FloatingPointExceptionCounter_MULFixOverflowCnt 0x00100000
#define MASK_FloatingPointExceptionCounter_MULInvalidCntY 0x00200000
#define MASK_FloatingPointExceptionCounter_MULOverflowCntY 0x00400000
#define MASK_FloatingPointExceptionCounter_MULUnderflowCntY 0x00800000
#define MASK_FloatingPointExceptionCounter_MULFixOverflowCntY 0x01000000
#define OFFSET_FloatingPointExceptionCounter_ResetCounter 0x00000008
#define OFFSET_FloatingPointExceptionCounter_ALUInvalidCnt 0x00000009
#define OFFSET_FloatingPointExceptionCounter_ALUOverflowCnt 0x0000000A
#define OFFSET_FloatingPointExceptionCounter_ALUUnderflowCnt 0x0000000B
#define OFFSET_FloatingPointExceptionCounter_ALUFixOverflowCnt 0x0000000C
#define OFFSET_FloatingPointExceptionCounter_ALUInvalidCntY 0x0000000D
#define OFFSET_FloatingPointExceptionCounter_ALUOverflowCntY 0x0000000E
#define OFFSET_FloatingPointExceptionCounter_ALUUnderflowCntY 0x0000000F
#define OFFSET_FloatingPointExceptionCounter_ALUFixOverflowCntY 0x00000010
#define OFFSET_FloatingPointExceptionCounter_MULInvalidCnt 0x00000011
#define OFFSET_FloatingPointExceptionCounter_MULOverflowCnt 0x00000012
#define OFFSET_FloatingPointExceptionCounter_MULUnderflowCnt 0x00000013
#define OFFSET_FloatingPointExceptionCounter_MULFixOverflowCnt 0x00000014
#define OFFSET_FloatingPointExceptionCounter_MULInvalidCntY 0x00000015
#define OFFSET_FloatingPointExceptionCounter_MULOverflowCntY 0x00000016
#define OFFSET_FloatingPointExceptionCounter_MULUnderflowCntY 0x00000017
#define OFFSET_FloatingPointExceptionCounter_MULFixOverflowCntY 0x00000018

#define CLASSID_FLOATINGPOINTEXCEPTIONCOUNTER (CLASS_ID_MODBASE + 5317)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modFloatingPointExceptionCounterInstance
{
    ModuleInstanceDescriptor instance;
    int                ResetCounter;        // Flag to reset the counters to zero
    int                ALUInvalidCnt;       // Number of ALU floating invalid point operations in the syatem
    int                ALUOverflowCnt;      // Number of ALU floating point operations which generates overflow result in the syatem
    int                ALUUnderflowCnt;     // Number of ALU floating point operations which generates underflow result in the syatem
    int                ALUFixOverflowCnt;   // Number of ALU fixed point operations which generates overflow result in the syatem
    int                ALUInvalidCntY;      // Number of ALU floating invalid point operations in the syatem (Secondary Processing Element)
    int                ALUOverflowCntY;     // Number of ALU floating point operations which generates overflow result in the syatem (Secondary Processing Element)
    int                ALUUnderflowCntY;    // Number of ALU floating point operations which generates underflow result in the syatem (Secondary Processing Element)
    int                ALUFixOverflowCntY;  // Number of ALU fixed point operations which generates overflow result in the syatem (Secondary Processing Element)
    int                MULInvalidCnt;       // Number of Multiplier floating invalid point operations in the syatem
    int                MULOverflowCnt;      // Number of Multiplier floating point operations which generates overflow result in the syatem
    int                MULUnderflowCnt;     // Number of Multiplier floating point operations which generates underflow result in the syatem
    int                MULFixOverflowCnt;   // Number of Multiplier fixed point operations which generates overflow result in the syatem
    int                MULInvalidCntY;      // Number of Multiplier floating invalid point operations in the syatem (Secondary Processing Element)
    int                MULOverflowCntY;     // Number of Multiplier floating point operations which generates overflow result in the syatem (Secondary Processing Element)
    int                MULUnderflowCntY;    // Number of Multiplier floating point operations which generates underflow result in the syatem (Secondary Processing Element)
    int                MULFixOverflowCntY;  // Number of Multiplier fixed point operations which generates overflow result in the syatem (Secondary Processing Element)
    
} awe_modFloatingPointExceptionCounterInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modFloatingPointExceptionCounterClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modFloatingPointExceptionCounterConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_FLOATINGPOINTEXCEPTIONCOUNTER, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modFloatingPointExceptionCounterProcess(void *pInstance);

UINT32 awe_modFloatingPointExceptionCounterSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_FLOATINGPOINTEXCEPTIONCOUNTER_H

/**
 * @}
 *
 * End of file.
 */
