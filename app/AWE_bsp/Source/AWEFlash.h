/* ----------------------------------------------------------------------------
 *   Extern functions
 * ------------------------------------------------------------------------- */
#include "TargetProcessor.h"
#include "Framework.h"

#ifndef SUCCESS
#define SUCCESS 1
#endif

#ifndef FAILURE
#define FAILURE 0
#endif

#define FILESYSTEM_TYPE_FLASH 2

#define ADDR_FLASH_SECTOR_0     ((UINT32)0x08000000) // Base @ of Sector 0, 16 Kbytes
#define ADDR_FLASH_SECTOR_1     ((UINT32)0x08004000) // Base @ of Sector 1, 16 Kbytes
#define ADDR_FLASH_SECTOR_2     ((UINT32)0x08008000) // Base @ of Sector 2, 16 Kbytes
#define ADDR_FLASH_SECTOR_3     ((UINT32)0x0800C000) // Base @ of Sector 3, 16 Kbytes
#define ADDR_FLASH_SECTOR_4     ((UINT32)0x08010000) // Base @ of Sector 4, 64 Kbytes
#define ADDR_FLASH_SECTOR_5     ((UINT32)0x08020000) // Base @ of Sector 5, 128 Kbytes
#define ADDR_FLASH_SECTOR_6     ((UINT32)0x08040000) // Base @ of Sector 6, 128 Kbytes
#define ADDR_FLASH_SECTOR_7     ((UINT32)0x08060000) // Base @ of Sector 7, 128 Kbytes
#define ADDR_FLASH_SECTOR_8     ((UINT32)0x08080000) // Base @ of Sector 8, 128 Kbytes
#define ADDR_FLASH_SECTOR_9     ((UINT32)0x080A0000) // Base @ of Sector 9, 128 Kbytes
#define ADDR_FLASH_SECTOR_10    ((UINT32)0x080C0000) // Base @ of Sector 10, 128 Kbytes
#define ADDR_FLASH_SECTOR_11    ((UINT32)0x080E0000) // Base @ of Sector 11, 128 Kbytes

extern const UINT32 FLASH_MEMORY_SIZE_IN_BYTES;
extern const UINT32 FLASH_MEMORY_SIZE_IN_WORDS;
extern const UINT32 ERASEABLE_BLOCKSIZE;
extern const UINT32 FILE_SYSTEM_START_OFFSET;    
extern const UINT32 FLASH_START_OFFSET;

extern BOOL InitFlashFileSystem(UINT32 nFlashMemorySizeBytes,
								UINT32 nEraseableBlockSize,
								UINT32 nFileSystemStartOffset);

BOOL awe_pltInitFlashFileSystem(void);
BOOL awe_pltReadFlashMemory(UINT32 nAddress, UINT32 * pBuffer, UINT32 nDWordsToRead);
BOOL awe_pltWriteFlashMemory(UINT32 nAddress, UINT32 * pBuffer, UINT32 nDWordsToWrite);
BOOL awe_pltEraseFlashMemorySector(UINT32 nStartingAddress, UINT32 nNumberOfSectors);
BOOL awe_pltAllocateBlock(UINT32 nAddress);

extern FileSystemInfo g_filesystem_info;
