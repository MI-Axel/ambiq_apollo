#ifndef __OPTIONAL_FEATURES__
#define __OPTIONAL_FEATURES__

#if (HAS_FLASH_FILESYSTEM == 0)

#include "FileSystem.h"

BOOL             awe_pltInitFlashFileSystem   (void){return FAILURE;}
INT32            awe_pltGetFlashEraseTime(void){return 0;}   

INT32            GetNextCommand          (UINT32 * nTotalDWordsRead){(void)nTotalDWordsRead;return E_COMMAND_NOT_IMPLEMENTED;}	
INT32            GetFileSystemInfo       (FileSystemInfo *pFileSystemInfo){(void)pFileSystemInfo;return E_COMMAND_NOT_IMPLEMENTED;}

INT32            awe_fwResetFileSystem   (void)  {return E_COMMAND_NOT_IMPLEMENTED; }	
INT32            awe_fwGetFirstFile      (PDIRECTORY_ENTRY * pDirEntry) {(void)pDirEntry;	return E_COMMAND_NOT_IMPLEMENTED; }	
INT32            awe_fwGetNextFile       (PDIRECTORY_ENTRY * pDirEntry)  {(void)pDirEntry; return E_COMMAND_NOT_IMPLEMENTED; }	
INT32            awe_fwOpenFile          (UINT32 nFileAttribute, UINT32 * pFileNameInDWords, UINT32 * nFileLenInDWords){(void)nFileAttribute;(void)pFileNameInDWords;(void)nFileLenInDWords; return E_COMMAND_NOT_IMPLEMENTED;}
INT32            awe_fwWriteFile         (UINT32 nWordsToWrite, UINT32 * pBuffer, UINT32 * pDWordsWritten){(void)nWordsToWrite;(void)pBuffer;(void)pDWordsWritten;return E_COMMAND_NOT_IMPLEMENTED;}	
INT32            awe_fwReadFile          (UINT32 nWordsToRead, UINT32 * pBuffer, UINT32 * pDWordsRead){(void)nWordsToRead;(void)pBuffer;(void)pDWordsRead;return E_COMMAND_NOT_IMPLEMENTED;}	
INT32            awe_fwCloseFile         (void){return E_COMMAND_NOT_IMPLEMENTED;}	
INT32            awe_fwDeleteFile        (UINT32 * pFileNameInDWords){(void)pFileNameInDWords;return E_COMMAND_NOT_IMPLEMENTED;}	
PDIRECTORY_ENTRY awe_fwFindFile          (UINT32 * pFileNameInDWords){(void)pFileNameInDWords;return NULL;}	
INT32            awe_fwExecuteFile       (AWEInstance *pAWE, UINT32 * pFileNameInDWords){(void)pAWE;(void)pFileNameInDWords;return E_COMMAND_NOT_IMPLEMENTED;}
UINT8            awe_fwGetFileAttribute  (PDIRECTORY_ENTRY pDirectoryEntry){(void)pDirectoryEntry;return 0;}	
INT32            awe_fwEraseFlash        (void){return E_COMMAND_NOT_IMPLEMENTED;}	
INT32            awe_fwReadFileMem       (UINT32 nStartingAddress, UINT32 nOffsetInDWords, UINT32 nWordsToRead, UINT32 * pBuffer){(void)nStartingAddress;(void)nOffsetInDWords;(void)nWordsToRead;(void)pBuffer;return E_COMMAND_NOT_IMPLEMENTED;}   
INT32            awe_fwGetFileMemStartingAddress  (UINT32 * pFileNameInDWords, UINT32 * nStartingAddress, UINT32 * nFileLenInDWords){(void)pFileNameInDWords;(void)nStartingAddress;(void)nFileLenInDWords;return E_COMMAND_NOT_IMPLEMENTED;}   

#endif //HAS_FLASH_FILESYSTEM

#endif //__OPTIONAL_FEATURES__
