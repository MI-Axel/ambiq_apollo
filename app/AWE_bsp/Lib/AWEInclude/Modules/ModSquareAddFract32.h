/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModSquareAddFract32.h
****************************************************************************
*
*     Description:  Squares all inputs and then sums them together.
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
 * @brief Squares all inputs and then sums them together.
 */

#ifndef _MOD_SQUAREADDFRACT32_H
#define _MOD_SQUAREADDFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_SquareAddFract32_oneChannelOutput 0x00000100
#define OFFSET_SquareAddFract32_oneChannelOutput 0x00000008

#define CLASSID_SQUAREADDFRACT32 (CLASS_ID_MODBASE + 200)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modSquareAddFract32Instance
{
    ModuleInstanceDescriptor instance;
    INT32              oneChannelOutput;    // Boolean value that determines whether all channels are summed to form a single output
    
} awe_modSquareAddFract32Instance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modSquareAddFract32Class;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modSquareAddFract32Constructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SQUAREADDFRACT32, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modSquareAddFract32Process(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SQUAREADDFRACT32_H

/**
 * @}
 *
 * End of file.
 */
