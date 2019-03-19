/****************************************************************************
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     ModFileSink.h
****************************************************************************
*
*     Description:  Copies the data at the input pin and writes it in an CSV file
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
 * @brief Copies the data at the input pin and writes it in an CSV file
 */

#ifndef _MOD_FILESINK_H
#define _MOD_FILESINK_H

#include "ModCommon.h"
#include "MathHelper.h"
#include "stdio.h"
#include "string.h"

#define MASK_FileSink_fullFileSize 0x00000100
#define MASK_FileSink_initialize 0x00000200
#define MASK_FileSink_FullFileName 0x00000400
#define MASK_FileSink_OutputFormatString 0x00000800
#define MASK_FileSink_DataType 0x00001000
#define MASK_FileSink_filePtr 0x00002000
#define OFFSET_FileSink_fullFileSize 0x00000008
#define OFFSET_FileSink_initialize 0x00000009
#define OFFSET_FileSink_FullFileName 0x0000000A
#define OFFSET_FileSink_OutputFormatString 0x0000000B
#define OFFSET_FileSink_DataType 0x0000000C
#define OFFSET_FileSink_filePtr 0x0000000D

#define CLASSID_FILESINK (CLASS_ID_MODBASE + 1270)

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Overall instance class
// ----------------------------------------------------------------------

typedef struct _awe_modFileSinkInstance
{
    ModuleInstanceDescriptor instance;
    INT32              fullFileSize;        // Size of the array to hold the full file path of the output .csv file
    INT32              initialize;          // Flag which controls initial configurations
    INT32*             FullFileName;        // Complete file path of the output .csv file to be written data
    INT32*             OutputFormatString;  // Format of the output data to be written to .csv file
    INT32*             DataType;            // Data type of the input pin
    FILE *             filePtr;             // File pointer of the output .csv file
} awe_modFileSinkInstance;

#if !defined(NOREDEF)
extern const ModClassModule awe_modFileSinkClass;
#endif // #if !defined(NOREDEF)

/* Dynamic instantiation is used by default.  When building for static
** code, define AWE_STATIC_CODE to eliminate the constructor function. */

#ifndef AWE_STATIC_CODE
ModInstanceDescriptor * awe_modFileSinkConstructor(INT32 * FW_RESTRICT retVal, UINT32 nIO, WireInstance ** FW_RESTRICT pWires, size_t argCount, const Sample * FW_RESTRICT args);
#endif // #ifndef AWE_STATIC_CODE


void awe_modFileSinkProcess(void *pInstance);

UINT32 awe_modFileSinkSet(void *pInstance, UINT32 mask);
 



#ifdef __cplusplus
}
#endif


#endif // _MOD_FILESINK_H

/**
 * @}
 *
 * End of file.
 */
