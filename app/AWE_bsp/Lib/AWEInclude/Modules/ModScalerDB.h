/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModScalerDB.h
****************************************************************************
*
*     Description:  Gain control with dB units and no smoothing
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
 * @brief Gain control with dB units and no smoothing
 */

#ifndef _MOD_SCALERDB_H
#define _MOD_SCALERDB_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_ScalerDB_gainDB 0x00000100
#define MASK_ScalerDB_gain 0x00000200
#define OFFSET_ScalerDB_gainDB 0x00000008
#define OFFSET_ScalerDB_gain 0x00000009

#define CLASSID_SCALERDB (CLASS_ID_MODBASE + 2036)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modScalerDBInstance
{
    ModuleInstanceDescriptor instance;
    FLOAT32            gainDB;              // Gain in dB.
    FLOAT32            gain;                // Gain in linear units.
    
} awe_modScalerDBInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modScalerDBClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modScalerDBConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_SCALERDB, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modScalerDBProcess(void *pInstance);

UINT32 awe_modScalerDBSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_SCALERDB_H

/**
 * @}
 *
 * End of file.
 */
