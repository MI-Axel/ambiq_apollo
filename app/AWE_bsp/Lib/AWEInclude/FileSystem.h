/*******************************************************************************
*
*               Audio Framework
*               ---------------
*
********************************************************************************
*     FileSystem.h
********************************************************************************
*
*     Description:  Prototypes of AudioWeaver File System
*
*     Copyright:    (c) 2007 - 2016 DSP Concepts Inc., All rights reserved.
*                   1800 Wyatt Drive, Suite 14
*                   Sunnyvale, CA 95054
*
*******************************************************************************/
#ifndef _FILESYSTEM_H
#define _FILESYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "PlatformAPI.h"
#include "Errors.h"
       
#if defined(__ADSP21000__) || defined(__ADSPBLACKFIN__)
#pragma default_section(CODE, "awe_fw_slowcode")
#pragma default_section(ALLDATA, "awe_fw_slowanydata")
#pragma default_section(SWITCH, "awe_fw_slowanydata")
#endif

// Definitions for file attribute byte
#define LOAD_IMAGE				0x01
#define STARTUP_FILE			0x02
#define DATA_FILE				0x04	// Any file of type "Other"
#define COMPILED_SCRIPT			0x08
#define COMMAND_SCRIPT			0x10
#define PRESET_SCRIPT			0x20
#define COMPILED_PRESET_SCRIPT	0x28
#define LOADER_FILE				0x40
#define FILE_DELETED			0x80

#define ALLOCATION_BLOCKSIZE_DWORDS 16
#define MAX_FILENAME_LENGTH 55
#define MAX_FILENAME_LENGTH_IN_DWORDS 14

#ifndef DIRECTORY_ENTRY_DEFINED
#define DIRECTORY_ENTRY_DEFINED

/**
 * @brief Flash file system directory entry data structure.
 *
 * All structure elements are 4 byte words to accommodate SHARC processors
 *
 * File Info UINT32 layout
 *
 * Attribute bits | File Data CRC | Block Offset to Data 
 * -------------- | ------------- | --------------------
 * 1 byte         | 1 byte        |  2 bytes
 * 
 * | bit 31.................................................................................bit 0 | 
 *
 *
 * Attribute              | Value 
 * ---------------------- | -----
 * LOAD_IMAGE			  | 0x01
 * STARTUP_FILE			  | 0x02
 * DATA_FILE		      | 0x04
 * COMPILED_SCRIPT	      | 0x08
 * COMMAND_SCRIPT	      |	0x10
 * PRESET_SCRIPT	      |	0x20
 * COMPILED_PRESET_SCRIPT |	0x28
 * LOADER_FILE			  | 0x40
 * FILE_DELETED			  | 0x80
 *
 */
 
// The layout for nFileInfo field in a file directory entry is:
// ---------------------------------------------------------
// | Attribute bits | File Data CRC | Block Offset to Data |
// ---------------------------------------------------------
// | 1 byte			| 1 byte		| 2 bytes			   |
// ---------------------------------------------------------
// | bit 31...........................................bit 0|
// ---------------------------------------------------------

// Note that the file name must fit in one allocation block
// This inherently limits the file name to 55 bytes plus zero terminator byte (56 bytes)
typedef struct _DIRECTORY_ENTRY
{
	UINT32 nFileInfo;
	UINT32 nDataDWordCnt;
    UINT32 nFilename[MAX_FILENAME_LENGTH_IN_DWORDS];
} DIRECTORY_ENTRY, *PDIRECTORY_ENTRY;
#endif

// File system global state variables
extern PDIRECTORY_ENTRY g_pCurrentDirEntry;

// Count of number of files
extern INT32 g_nFileCnt;

extern BOOL g_bProcessingCommandFile;
extern BOOL g_bProcessingStartupCommandFile;

extern INT32 g_nCurrentDataOffset;

extern UINT32 g_nAllocBlockSizeInDWords;
extern UINT32 g_nAllocBlockSizeInBytes;
extern INT32  g_nFileCnt;
extern UINT32 g_nFileDirectoryFlashAddr;
extern UINT32 g_nStartOfFileDataFlashAddr;

extern UINT32 g_nFlashBlockSize;
extern INT32 g_nFileCnt;
extern UINT32 * g_pFileData;

extern DIRECTORY_ENTRY FileDir[];
extern UINT32 *FileData;

//-----------------------------------------------------------------------------
// METHOD:	awe_fwGetFileAttribute
// PURPOSE: Get the file attribute byte for the indicated file entry
//-----------------------------------------------------------------------------
UINT8 awe_fwGetFileAttribute(PDIRECTORY_ENTRY pDirectoryEntry);


//-----------------------------------------------------------------------------
// METHOD:	awe_fwResetFileSystem
// PURPOSE: Reset the file system
//-----------------------------------------------------------------------------
INT32 awe_fwResetFileSystem(void);


//-----------------------------------------------------------------------------
// METHOD:	awe_fwGetFirstFile
// PURPOSE: Get the first file directory entry
//-----------------------------------------------------------------------------
INT32 awe_fwGetFirstFile(PDIRECTORY_ENTRY * pDirEntry);


//-----------------------------------------------------------------------------
// METHOD:	awe_fwGetNextFile
// PURPOSE: Get the next file directory entry
//-----------------------------------------------------------------------------
INT32 awe_fwGetNextFile(PDIRECTORY_ENTRY * pDirEntry);


//-----------------------------------------------------------------------------
// METHOD:	awe_fwExecuteFile
// PURPOSE: Execute compiled file saved in the flash file system
//-----------------------------------------------------------------------------
INT32 awe_fwExecuteFile(AWEInstance *pAWE, UINT32 *mFilename);


//-----------------------------------------------------------------------------
// METHOD:	awe_fwOpenFile
// PURPOSE: Open a file for read or write
//-----------------------------------------------------------------------------
INT32 awe_fwOpenFile(UINT32 nFileAttribute, UINT32 * pFileNameInDWords, UINT32 * nFileLenInDWords);


//-----------------------------------------------------------------------------
// METHOD:	awe_fwCloseFile
// PURPOSE: Close an open file
//-----------------------------------------------------------------------------
INT32 awe_fwCloseFile(void);


//-----------------------------------------------------------------------------
// METHOD:	awe_fwReadFile
// PURPOSE: Read words from file
//-----------------------------------------------------------------------------
INT32 awe_fwReadFile(UINT32 nWordsToRead, UINT32 * pBuffer, UINT32 * pDWordsRead);


//-----------------------------------------------------------------------------
// METHOD:	awe_fwWriteFile
// PURPOSE: Write words to file
//-----------------------------------------------------------------------------
INT32 awe_fwWriteFile(UINT32 nWordsToWrite, UINT32 * pBuffer, UINT32 * pDWordsWritten);


//-----------------------------------------------------------------------------
// METHOD:	awe_fwFindFile
// PURPOSE: Find the directory entry for the named file
//-----------------------------------------------------------------------------
PDIRECTORY_ENTRY awe_fwFindFile(UINT32 * pFileNameInDWords);


//-----------------------------------------------------------------------------
// METHOD:  awe_fwDeleteFile
// PURPOSE: Marks the file deleted
//-----------------------------------------------------------------------------
INT32 awe_fwDeleteFile(UINT32 * pFileNameInDWords);


//-----------------------------------------------------------------------------
// METHOD:	awe_fwReadFileMem
// PURPOSE: Reads the memory at offset from starting address
//-----------------------------------------------------------------------------
INT32 awe_fwReadFileMem(UINT32 nStartingAddress, UINT32 nOffsetInDWords, UINT32 nWordsToRead, UINT32 * pBuffer);


//-----------------------------------------------------------------------------
// METHOD:	awe_fwGetFileMemStartingAddress
// PURPOSE: Looks up the given file starting memory address and length in DWords
//-----------------------------------------------------------------------------
INT32 awe_fwGetFileMemStartingAddress(UINT32 * pFileNameInDWords, UINT32 * nStartingAddress, UINT32 * nFileLenInDWords);


// Flash specific
INT32 awe_pltGetFlashEraseTime(void);
INT32 awe_fwEraseFlash(void);

#ifdef	__cplusplus
}
#endif


#endif	// _FILESYSTEM_H
