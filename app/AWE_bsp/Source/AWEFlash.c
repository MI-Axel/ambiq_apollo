/*******************************************************************************
*
*               Audio Framework
*               ---------------
*
********************************************************************************
*     AWEFlash.c
********************************************************************************
*
*     Description:  AudioWeaver Flash Memory Interface
*
*
*******************************************************************************/
#include "AWEFlash.h"

/* ----------------------------------------------------------------------
** Initialize the flash file system
** ------------------------------------------------------------------- */

const UINT32 FLASH_MEMORY_SIZE_IN_BYTES = 0x08100000;
const UINT32 FLASH_MEMORY_SIZE_IN_WORDS = 0x08100000 >> 2;
const UINT32 ERASEABLE_BLOCKSIZE = 0x20000;
const UINT32 FILE_SYSTEM_START_OFFSET = 0x08080000;	
const UINT32 FLASH_START_OFFSET = 0x000000;


///-----------------------------------------------------------------------------
/// @name  INT32 awe_pltGetFlashEraseTime(void)
/// @brief Number of seconds to erase flash file system
///
/// @retval  	Number of seconds to erase dflash file system
///-----------------------------------------------------------------------------
INT32 awe_pltGetFlashEraseTime(void)
{
    // This number must be measured for each target
    // Return 0 to prevent AWE_Server from showing the progress bar
    return 0;

}   // End awe_pltGetFlashEraseTime


//-----------------------------------------------------------------------------
// METHOD:  awe_pltInitFlashFileSystem
// PURPOSE: This method is here
//-----------------------------------------------------------------------------
AWE_OPTIMIZE_FOR_SPACE
AWE_FW_SLOW_CODE
BOOL awe_pltInitFlashFileSystem(void)
{
    // Clear the flash register flags 
    __HAL_FLASH_CLEAR_FLAG( (FLASH_FLAG_EOP | \
                             FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | \
                             FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR | FLASH_FLAG_RDERR));
    
	g_filesystem_info.m_FlashDeviceDWords = FLASH_MEMORY_SIZE_IN_WORDS;
    
    return InitFlashFileSystem(FLASH_MEMORY_SIZE_IN_BYTES,
                               ERASEABLE_BLOCKSIZE,
                               FILE_SYSTEM_START_OFFSET);
   
}   // End awe_pltInitFlashFileSystem


//-----------------------------------------------------------------------------
// METHOD:  awe_pltReadFlashMemory
// PURPOSE: Read from flash memory device
//-----------------------------------------------------------------------------
AWE_OPTIMIZE_FOR_SPACE
AWE_FW_SLOW_CODE
BOOL awe_pltReadFlashMemory(UINT32 nFlashAddress, UINT32 * pBuffer, UINT32 nDWordsToRead)
{	
    UINT32 n;
    UINT32 * pSrc = (UINT32 *)nFlashAddress;
    
	for (n = 0; n < nDWordsToRead; n++)
	{
		pBuffer[n] = pSrc[n];
	}	

	return SUCCESS;	

}	// End awe_pltReadFlashMemory


//-----------------------------------------------------------------------------
// METHOD:  awe_pltWriteFlashMemory
// PURPOSE: Write to flash memory device
//-----------------------------------------------------------------------------
AWE_OPTIMIZE_FOR_SPACE
AWE_FW_SLOW_CODE
BOOL awe_pltWriteFlashMemory(UINT32 nFlashAddress, UINT32 * pBuffer, UINT32 nDWordsToWrite)
{ 
	UINT32 n = 0;
		
	// Flash address must be on a 4 byte boundary since writing DWords
	if ( (nFlashAddress & 0x00000003) != 0)
	{
		return FAILURE;
	}
    
    HAL_FLASH_Unlock();

    while (n < nDWordsToWrite)
    {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, nFlashAddress, pBuffer[n]) == HAL_OK)
        { 
            // Read back DWORD that was written
            DWORD nDWord;            
            nDWord = *(PDWORD)nFlashAddress;
            if (nDWord != pBuffer[n])
            {
                return FAILURE;
            }
            
            nFlashAddress = nFlashAddress + 4;
            n++;
        }
        else
        { 
            return FAILURE;
        }
    } 

    HAL_FLASH_Lock();     

	return SUCCESS;

}	// End awe_pltWriteFlashMemory


//-----------------------------------------------------------------------------
// METHOD:  awe_pltEraseFlashMemory4KSector
// PURPOSE: Erase Flash Memory used for Flash File System
//          The flash memory region assigned for the flash file system
//          starts with flash sector 8. These are actually 128K sectors.
//-----------------------------------------------------------------------------
AWE_OPTIMIZE_FOR_SPACE
AWE_FW_SLOW_CODE
BOOL awe_pltEraseFlashMemorySector(UINT32 nStartingAddress, UINT32 nNumberOfSectors)
{   
    FLASH_EraseInitTypeDef EraseInitStruct;
    UINT32 nSector_to_erase = 0;    
    UINT32 SectorError = 0;

    if (nStartingAddress < ADDR_FLASH_SECTOR_7)
    {
        nSector_to_erase = FLASH_SECTOR_6;
    }

    else if (nStartingAddress < ADDR_FLASH_SECTOR_8)
    {
        nSector_to_erase = FLASH_SECTOR_7;
    }
    
    else if (nStartingAddress < ADDR_FLASH_SECTOR_9)
    {
        nSector_to_erase = FLASH_SECTOR_8;
    }
    
    else if (nStartingAddress < ADDR_FLASH_SECTOR_10)
    {
        nSector_to_erase = FLASH_SECTOR_9;
    }
    
    else if (nStartingAddress < ADDR_FLASH_SECTOR_11)
    {
        nSector_to_erase = FLASH_SECTOR_10;
    } 
   
    else if (nStartingAddress < ((uint32_t)0x08100000))
    {
        nSector_to_erase = FLASH_SECTOR_11;
    }    
    
    HAL_FLASH_Unlock();  

    EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
    EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    EraseInitStruct.Sector = nSector_to_erase;
    EraseInitStruct.NbSectors = nNumberOfSectors;
    
    if (HAL_FLASHEx_Erase(&EraseInitStruct, (uint32_t *)&SectorError) != HAL_OK)
    {
        return FAILURE;
    }
    
    __HAL_FLASH_DATA_CACHE_DISABLE();
    __HAL_FLASH_DATA_CACHE_RESET(); 
    __HAL_FLASH_DATA_CACHE_ENABLE();
    
    HAL_FLASH_Lock(); 

	return SUCCESS;
      
}	// End awe_pltEraseFlashMemory4KSector

