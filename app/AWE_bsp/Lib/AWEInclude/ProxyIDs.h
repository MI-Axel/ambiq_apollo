/**
*	@addtogroup Framework
*	@{
*/

/****************************************************************************
 *
 *		Command IDs
 *		-----------
 *
 ****************************************************************************
 *	ProxyIDs.h
 ****************************************************************************
 *
 *	Description:	Message command ID list
 *
 *	Copyright (c) 2007 - 2016 DSP Concepts Inc., All rights reserved.
 *	Owner: DSP Concepts, Inc.
 *
 ***************************************************************************/
#ifndef PROXYIDS_H_INCLUDED
#define PROXYIDS_H_INCLUDED

/**
 * @brief Enumeration of Proxy function IDs.
 */
typedef enum
{
	/** Undefined ID - zero */
	PFID_Undefined,							/* = 0 */

	/** Function ID for awe_fwSetCall(). */
	PFID_SetCall,							/* = 1 */

	/** Function ID for awe_fwGetCall(). */
	PFID_GetCall,							/* = 2 */

	/** Function ID for ClassPin_Constructor(). */
	PFID_ClassPin_Constructor,				/* = 3 */

	/** Function ID for awe_fwGetClassType(). */
	PFID_GetClassType,						/* = 4 */

	/** Function ID for awe_fwGetPinType(). */
	PFID_GetPinType,						/* = 5 */

	/** Function ID for ClassWire_Constructor(). */
	PFID_ClassWire_Constructor,				/* = 6 */

	/** Function ID for BindIOToWire(). */
	PFID_BindIOToWire,						/* = 7 */

	/** Function ID for awe_fwFetchValue(). */
	PFID_FetchValue,						/* = 8 */

	/** Function ID for awe_fwSetValue(). */
	PFID_SetValue,							/* = 9 */

	/** Function ID for awe_fwGetHeapCount(). */
	PFID_GetHeapCount,						/* = 10 */

	/** Function ID for awe_fwGetHeapSize(). */
	PFID_GetHeapSize,						/* = 11 */

	/** Function ID for awe_fwDestroy(). */
	PFID_Destroy,							/* = 12 */

	/** Function ID for awe_fwGetCIModuleCount(). */
	PFID_GetCIModuleCount,					/* = 13 */

	/** Function ID for awe_fwGetCIModuleInfo(). */
	PFID_GetCIModuleInfo,					/* = 14 */

	/** Function ID for ClassModule_Constructor(). */
	PFID_ClassModule_Constructor,			/* = 15 */

	/** Function ID for ClassLayout_Constructor(). */
	PFID_ClassLayout_Constructor,			/* = 16 */

	/** Function ID for awe_fwSetWire(). */
	PFID_SetWire,							/* = 17 */

	/** Function ID for awe_fwGetWire(). */
	PFID_GetWire,							/* = 18 */

	/** Function ID for awe_fwSetModuleState(). */
	PFID_SetModuleState,					/* = 19 */

	/** Function ID for awe_fwGetModuleState(). */
	PFID_GetModuleState,					/* = 20 */

	/** Function ID for awe_fwPumpModule(). */
	PFID_PumpModule,						/* = 21 */

	/** Function ID for ClassLayout_Process(). */
	PFID_ClassLayout_Process,				/* = 22 */

	/** Function ID for awe_fwGetFirstObject(). */
	PFID_GetFirstObject,					/* = 23 */

	/** Function ID for awe_fwGetNextObject(). */
	PFID_GetNextObject,						/* = 24 */

	/** Function ID for awe_fwGetFirstIO(). */
	PFID_GetFirstIO,						/* = 25 */

	/** Function ID for awe_fwGetNextIO(). */
	PFID_GetNextIO,							/* = 26 */

	/** Function ID for StartAudio(). */
	PFID_StartAudio,						/* = 27 */

	/** Function ID for StopAudio(). */
	PFID_StopAudio,							/* = 28 */

	/** Function ID for awe_fwFetchValue(). */
	PFID_FetchValues,						/* = 29 */

	/** Function ID for awe_fwSetValue(). */
	PFID_SetValues,							/* = 30 */

	/** Function ID for awe_fwGetSizeofInt(). */
	PFID_GetSizeofInt,						/* = 31 */

	/** Function ID for awe_GetFirstFile(). */
	PFID_GetFirstFile,						/* = 32 */

	/** Function ID for awe_GetNextFile(). */
	PFID_GetNextFile,						/* = 33 */

	/** Function ID for awe_OpenFile(). */
	PFID_OpenFile,							/* = 34 */

	/** Function ID for awe_ReadFile(). */
	PFID_ReadFile,							/* = 35 */

	/** Function ID for awe_WriteFile(). */
	PFID_WriteFile,							/* = 36 */

	/** Function ID for awe_CloseFile(). */
	PFID_CloseFile,							/* = 37 */

	/** Function ID for awe_DeleteFile(). */
	PFID_DeleteFile,						/* = 38 */

	/** Function ID for awe_ExecuteFile(). */
	PFID_ExecuteFile,						/* = 39 */

	/** Function ID for awe_EraseFlash(). */
	PFID_EraseFlash,						/* = 40 */

	/** Function ID for awe_GetTargetInfo(). */
	PFID_GetTargetInfo,						/* = 41 */

	/** Function ID for awe_GetFileSystemInfo(). */
	PFID_GetFileSystemInfo,					/* = 42 */

	/** Function ID for awe_fwGetProfileValues(). */
	PFID_GetProfileValues,					/* = 43 */

	/** Function ID for awe_FileSystemReset(). */
	PFID_FileSystemReset,					/* = 44 */

	/** Function ID for awe_fwGetNextObject(). */
	PFID_GetObjectByIndex,					/* = 45 */

	/** Function ID for awe_fwGetObjectByID(). */
	PFID_GetObjectByID,						/* = 46 */

	/** Function ID for awe_fwAddModuleToLayout(). */
	PFID_AddModuleToLayout,					/* = 47 */

	/** Function ID for awe_fwSetValue(), awe_fwSetCall(). */
	PFID_SetValueCall,						/* = 48 */

	/** Command ID for update firmware(), awe_fwSetCall(). */
	PFID_UpdateFirmware,					/* = 49 */

	/** Command ID for FlashContent Read(), awe_fwSetCall(). */
	PFID_FlashReadOpen,						/* = 50 */

	/** Command ID for FlashContent Read(), awe_fwSetCall(). */
	PFID_FlashRead,							/* = 51 */

	/* Command ID to Set values at ObjectID and to call Object Set Funtion. */
	PFID_SetObjectValueCall,				/* = 52 */

	/* Command ID to Fetch values at ObjectID. */
	PFID_FetchObjectValueCall,				/* = 53 */

	/* Command ID to tick for deferred execution. */
	PFID_Tick,								/* = 54 */

	/* Enables or disables address translation. */
	PFID_EnableAddressTranslation,			/* = 55 */

	/** Allocate framework heaps. */
	PFID_AllocateHeaps,						/* = 56 */

	/** Destroy framework heaps. */
	PFID_DestroyHeaps,						/* = 57 */

	/** Single message write-pump-read combo. */
	PFID_WritePumpRead,						/* = 58 */

	/** Set an object's ID. */
	PFID_SetID,								/* = 59 */

	/** Function ID for awe_fwSetValue() followed by awe_fwSetCall. */
	PFID_SetValueSetCall,					/* = 60 */

	/** Function ID for awe_fwSetValues() followed by awe_fwSetCall. */
	PFID_SetValuesSetCall,					/* = 61 */

	/** Function ID for awe_GetCall() followed by awe_fwFetchValue(). */
	PFID_GetCallFetchValue,					/* = 62 */

	/** Function ID for awe_GetCall() followed by awe_fwFetchValue(). */
	PFID_GetCallFetchValues,				/* = 63 */

	/** Function ID to get AWE control flags. */
	PFID_GetFlags,							/* = 64 */

	/** Function ID to set AWE control flags. */
	PFID_SetFlags,							/* = 65 */

	/** Function ID to translate a real address to relative. */
	PFID_TranslateToRelative,				/* = 66 */

	/** Function ID to translate a real address to relative. */
	PFID_TranslateToAbsolute,				/* = 67 */

	/** Function ID for awe_fwSetValue(), awe_fwSetCall() with pointer. */
	PFID_P_SetValueCall,					/* = 68 */

	/** Function ID for awe_fwFetchValue() with pointer. */
	PFID_P_FetchValue,						/* = 69 */

	/** Function ID for awe_GetCall() followed by awe_fwFetchValue() with pointer. */
	PFID_P_GetCallFetchValue,				/* = 70 */

	/** Function ID for awe_fwSetValue() with pointer. */
	PFID_P_SetValue,						/* = 71 */

	/** Function ID for awe_fwSetValue() followed by awe_fwSetCall with pointer. */
	PFID_P_SetValueSetCall,					/* = 72 */

	/** Function ID for awe_fwFetchValue() with pointer. */
	PFID_P_FetchValues,						/* = 73 */

	/** Function ID for awe_GetCall() followed by awe_fwFetchValue() with pointer. */
	PFID_P_GetCallFetchValues,				/* = 74 */

	/** Function ID for awe_fwSetValue() with pointer. */
	PFID_P_SetValues,						/* = 75 */

	/** Function ID for awe_fwSetValues() followed by awe_fwSetCall with pointer. */
	PFID_P_SetValuesSetCall,				/* = 76 */

	/** Function ID for awe_fwSetPointer(). */
	PFID_SetPointer,						/* = 77 */

	/** Function ID for awe_fwSetPointer(). */
	PFID_P_SetPointer,						/* = 78 */

	/** Function ID for awe_fwSetPointer(). */
	PFID_P1_SetPointer,						/* = 79 */

	/** Function ID for awe_fwSetPointer(). */
	PFID_P2_SetPointer,						/* = 80 */

	/** Function ID for awe_fwcreateLookupTable(). */
	PFID_CreateLookupTable,					/* = 81 */

	/** Function ID for awe_fwSUpdateLookupTable(). */
	PFID_UpdateLookupTable,					/* = 82 */

	/** Function ID for awe_fwPumpLayout(). */
	PFID_PumpLayout,						/* = 83 */

	/** Function ID for awe_fwDerefPointer(). */
	PFID_DerefPointer,						/* = 84 */

	/** Function ID for awe_fwGetWireType(). */
	PFID_GetWireType,						/* = 85 */

	/** Function ID for awe_fwSetInstanceID(). */
	PFID_SetInstanceID,						/* = 86 */

	/** Function ID for awe_fwGetFlashEraseTime(). */
	PFID_Get_Flash_Erase_Time,				/* = 87 */

	/** Function ID for awe_fwGetQueryFlashEraseComplete(). */
	PFID_Query_Flash_Erase_Complete,		/* = 88 */

	/** Function ID for awe_fwGetBaudRates(). */
	PFID_Query_Supported_Baud_Rates,		/* = 89 */

	/** Function ID for awe_fwSetBaudRate(). */
	PFID_Set_Baud_Rate,						/* = 90 */

	/** Command to forcefully corrupt DMA and lock DSP. */
	PFID_Lock_DSP,							/* = 91 */

	/** Function ID for reboot(). */
	PFID_Reboot_Target,						/* = 92 */

	/** Function ID for awe_fwDestroyAll(). */
	PFID_DestroyAll,						/* = 93 */

	/** Function ID for report first core. */
	PFID_GetFirstCore,						/* = 94 */

	/** Function ID for report next core. */
	PFID_GetNextCore,						/* = 95 */

	/** Function ID for StartAudio(). */
	PFID_StartAudioNonSMP,					/* = 96 */

	/** Function ID for GetCores(). */
	PFID_GetCores,							/* = 97 */

	/** Function ID for awe_fwFetchValue() as float. */
	PFID_FetchValues_float,					/* = 98 */

	/** Function ID for awe_GetCall() as float followed by awe_fwFetchValue(). */
	PFID_GetCallFetchValues_float,			/* = 99 */

	/** Function ID for awe_fwSetValue() as float. */
	PFID_SetValues_float,					/* = 100 */

	/** Function ID for awe_fwSetValues() as float followed by awe_fwSetCall. */
	PFID_SetValuesSetCall_float,			/* = 101 */

	/** Function ID for awe_fwFetchValue() as float. */
	PFID_FetchValue_float,					/* = 102 */

	/** Function ID for awe_GetCall() as float followed by awe_fwFetchValue(). */
	PFID_GetCallFetchValue_float,			/* = 103 */

	/** Function ID for awe_fwSetValue() as float. */
	PFID_SetValue_float,					/* = 104 */

	/** Function ID for awe_fwSetValue() followed by awe_fwSetCall. */
	PFID_SetValueSetCall_float,				/* = 105 */

	/** Function ID for awe_fwSetValue(). */
	PFID_SetValuesPartial,					/* = 106 */

	/** Function ID for awe_fwSetValue() as float. */
	PFID_SetValuesPartial_float,			/* = 107 */

	/** Trigger a pre pump. */
	PFID_PrePump,							/* = 108 */

	/** Function ID for GetCores(). */
	PFID_SetCores,							/* = 109 */


// Wennebostel user messages
	/** Wennebostol set attenuation. */
	PFID_WB_SetSattenuation = 120,			/* = 120 */

	/** Wennebostel get attenuation. */
	PFID_WB_GetSattenuation,				/* = 121 */

	/** Wennebostol set mute. */
	PFID_WB_SetMute,						/* = 122 */

	/**Wennebostol get mute. */
	PFID_WB_GetMute,						/* = 123 */

} tProxyFuncID;



#endif /* !PROXYIDS_H_INCLUDED */

/**
 * @}
 * End of file.
 */


