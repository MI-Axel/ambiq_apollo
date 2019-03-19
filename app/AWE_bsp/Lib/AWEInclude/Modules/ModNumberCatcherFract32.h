/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*  ModNumberCatcherFract32.h
****************************************************************************
*
*         Description:  Number catcher for fract32 data
*
*         Copyright:	DSP Concepts, Inc., 2007 - 2012
*                       568 E. Weddell Drive, Suite 3
*                       Sunnyvale, CA 94089
*
***************************************************************************/

/**
 * @addtogroup Modules
 * @{
 */

/**
 * @file
 * @brief Number catcher for fract32 data
 */

#ifndef _MOD_NUMBERCATCHERFRACT32_H
#define _MOD_NUMBERCATCHERFRACT32_H

#include "ModCommon.h"
#include "MathHelper.h"

#define MASK_NumberCatcherFract32_maxSaturation 0x00000100
#define MASK_NumberCatcherFract32_numSaturation 0x00000200
#define MASK_NumberCatcherFract32_bucketA 0x00000400
#define MASK_NumberCatcherFract32_bucketB 0x00000800
#define MASK_NumberCatcherFract32_countA 0x00001000
#define MASK_NumberCatcherFract32_countB 0x00002000
#define OFFSET_NumberCatcherFract32_maxSaturation 0x00000008
#define OFFSET_NumberCatcherFract32_numSaturation 0x00000009
#define OFFSET_NumberCatcherFract32_bucketA 0x0000000A
#define OFFSET_NumberCatcherFract32_bucketB 0x0000000B
#define OFFSET_NumberCatcherFract32_countA 0x0000000C
#define OFFSET_NumberCatcherFract32_countB 0x0000000D

#define CLASSID_NUMBERCATCHERFRACT32 (CLASS_ID_MODBASE + 5116)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modNumberCatcherFract32Instance
{
    ModuleInstanceDescriptor instance;
    unsigned int       maxSaturation;       // Maximum saturation count
    unsigned int       numSaturation;       // Current saturation count
    fract32            bucketA;             // Bucket A holds one of the two most frequent numbers
    fract32            bucketB;             // Bucket B holds one of the two most frequent numbers
    unsigned int       countA;              // Count A counts the occurence of one of the two most frequent numbers
    unsigned int       countB;              // Count B counts the occurence of one of the two most frequent numbers
    
} awe_modNumberCatcherFract32Instance;

/* By default the class object is included and this is required for dynamic
 * instantiation.  When doing static code (define AWE_STATIC_CODE) you can save
 * a little bit of memory by eliminating class objects.  However, you lose the
 * ability to change the module status. */

#if (!defined(AWE_NO_CLASS_OBJECTS) || !defined(AWE_STATIC_CODE))
extern const ModClassModule awe_modNumberCatcherFract32Class;
#endif // #ifndef AWE_NO_CLASS_OBJECTS

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modNumberCatcherFract32Constructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modNumberCatcherFract32Process(void *pInstance);

#ifndef AWE_NO_SETGET_FUNCTIONS
UINT32 awe_modNumberCatcherFract32Set(void *pInstance, UINT32 mask);
#endif
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_NUMBERCATCHERFRACT32_H

/**
 * @}
 *
 * End of file.
 */
