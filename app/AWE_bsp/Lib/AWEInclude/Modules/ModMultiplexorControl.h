/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModMultiplexorControl.h
****************************************************************************
*
*     Description:  N to 1 multiplexor module with a control input
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
 * @brief N to 1 multiplexor module with a control input
 */

#ifndef _MOD_MULTIPLEXORCONTROL_H
#define _MOD_MULTIPLEXORCONTROL_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_MultiplexorControl_smoothingTime 0x00000100
#define MASK_MultiplexorControl_index 0x00000200
#define MASK_MultiplexorControl_smoothingCoeff 0x00000400
#define MASK_MultiplexorControl_currentIndex 0x00000800
#define MASK_MultiplexorControl_currentGain 0x00001000
#define OFFSET_MultiplexorControl_smoothingTime 0x00000008
#define OFFSET_MultiplexorControl_index 0x00000009
#define OFFSET_MultiplexorControl_smoothingCoeff 0x0000000A
#define OFFSET_MultiplexorControl_currentIndex 0x0000000B
#define OFFSET_MultiplexorControl_currentGain 0x0000000C

#define CLASSID_MULTIPLEXORCONTROL (CLASS_ID_MODBASE + 2026)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modMultiplexorControlInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    INT32              index;               // Value seen on the control pin.  Specifies which input pin to route to the output. The index is zero based.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient
    INT32              currentIndex;        // This is index that is currently being used and the module smoothly transitions to index
    FLOAT32            currentGain;         // Instanteous gain being applied.  This is an internal variable used in the smoothing process
    
} awe_modMultiplexorControlInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modMultiplexorControlClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modMultiplexorControlConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_MULTIPLEXORCONTROL, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modMultiplexorControlProcess(void *pInstance);

UINT32 awe_modMultiplexorControlSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_MULTIPLEXORCONTROL_H

/**
 * @}
 *
 * End of file.
 */
