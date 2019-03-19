/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModCrossFader.h
****************************************************************************
*
*     Description:  Cross fader
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
 * @brief Cross fader
 */

#ifndef _MOD_CROSSFADER_H
#define _MOD_CROSSFADER_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_CrossFader_smoothingTime 0x00000100
#define MASK_CrossFader_mixType 0x00000200
#define MASK_CrossFader_currentGainA 0x00000400
#define MASK_CrossFader_currentGainB 0x00000800
#define MASK_CrossFader_smoothingCoeff 0x00001000
#define OFFSET_CrossFader_smoothingTime 0x00000008
#define OFFSET_CrossFader_mixType 0x00000009
#define OFFSET_CrossFader_currentGainA 0x0000000A
#define OFFSET_CrossFader_currentGainB 0x0000000B
#define OFFSET_CrossFader_smoothingCoeff 0x0000000C

#define CLASSID_CROSSFADER (CLASS_ID_MODBASE + 18)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modCrossFaderInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            smoothingTime;       // Time constant of the smoothing process
    INT32              mixType;             // Selects the type of curve: Linear=0, Energy=1.
    FLOAT32            currentGainA;        // Instantaneous gain applied to channel A.
    FLOAT32            currentGainB;        // Instantaneous gain applied to channel B.
    FLOAT32            smoothingCoeff;      // Smoothing coefficient
    
} awe_modCrossFaderInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modCrossFaderClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modCrossFaderConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_CROSSFADER, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modCrossFaderProcess(void *pInstance);

UINT32 awe_modCrossFaderSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_CROSSFADER_H

/**
 * @}
 *
 * End of file.
 */
