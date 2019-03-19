/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModRawStreamingSource.h
****************************************************************************
*
*     Description:  Reads raw data from a streaming buffer module
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
 * @brief Reads raw data from a streaming buffer module
 */

#ifndef _MOD_RAWSTREAMINGSOURCE_H
#define _MOD_RAWSTREAMINGSOURCE_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_RawStreamingSource_underflowCount 0x00000100
#define MASK_RawStreamingSource_streamingObjectID 0x00000200
#define MASK_RawStreamingSource_streamingObjectPtr 0x00000400
#define OFFSET_RawStreamingSource_underflowCount 0x00000008
#define OFFSET_RawStreamingSource_streamingObjectID 0x00000009
#define OFFSET_RawStreamingSource_streamingObjectPtr 0x0000000A

#define CLASSID_RAWSTREAMINGSOURCE (CLASS_ID_MODBASE + 2034)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modRawStreamingSourceInstance
{
    ModuleInstanceDescriptor instance;
    INT32              underflowCount;      // Number of output samples that could not be serviced.
    INT32              streamingObjectID;   // Object ID of the upstream module
    void *             streamingObjectPtr;  // Points to the upstream module
} awe_modRawStreamingSourceInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modRawStreamingSourceClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
// This points the constructor for this class to the base constructor
#define awe_modRawStreamingSourceConstructor(ARG1, ARG2, ARG3, ARG4, ARG5) ClassModule_Constructor(CLASSID_RAWSTREAMINGSOURCE, ARG1, ARG2, ARG3, ARG4, ARG5)
#endif // #ifndef AWE_STATIC_CODE


void awe_modRawStreamingSourceProcess(void *pInstance);

 



#ifdef __cplusplus
}
#endif


#endif // _MOD_RAWSTREAMINGSOURCE_H

/**
 * @}
 *
 * End of file.
 */
