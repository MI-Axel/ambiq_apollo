/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModFifoOut.h
****************************************************************************
*
*     Description:  Second half of the FIFO module
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
 * @brief Second half of the FIFO module
 */

#ifndef _MOD_FIFOOUT_H
#define _MOD_FIFOOUT_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "ModFifoIn.h"

#define MASK_FifoOut_fifoInPtr 0x00000100
#define OFFSET_FifoOut_fifoInPtr 0x00000008

#define CLASSID_FIFOOUT (CLASS_ID_MODBASE + 1363)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modFifoOutInstance
{
    ModuleInstanceDescriptor instance;
    
    void *             fifoInPtr;           // Points to the fifo_in_module.m instance
} awe_modFifoOutInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modFifoOutClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modFifoOutConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_FIFOOUT, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modFifoOutProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_FIFOOUT_H

/**
 * @}
 *
 * End of file.
 */
