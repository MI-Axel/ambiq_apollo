/*******************************************************************************
*
*               Audio Framework
*               ---------------
*
********************************************************************************
*     AWE_Wrapper.h
********************************************************************************
*
*     Description:  AudioWeaver Wrapper Header File
*
*     Copyright:    (c) 2018 DSP Concepts, Inc. All rights reserved.
*                   3235 Kifer Road
*                   Santa Clara, CA 95054
*
*******************************************************************************/
 #ifndef __PLATFORM_H__
 #define __PLATFORM_H__

#include "usb_device.h"
#include "usbd_audio.h"
#include "usbd_desc.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_audio.h"
#include "aweCore.h"
#include "AWECoreUtils.h"
#include "TargetInfo.h"
#include "Errors.h"

#include "dspc_asrc_48000_to_48000_32m_080db.h"

/** Create handle. */
#define CREATE_OBJECT_HANDLE(isArray, isFloat, objectID, index) \
	( ((isArray & 1) << 31) | ((isFloat & 1) << 30) | ((objectID & 0x3FFFF) << 12) | (index & 0xFF) )

#if ENABLE_MIC
    #define INPUT_CHANNEL_COUNT 3
#else
    #define INPUT_CHANNEL_COUNT 2
#endif

#define OUTPUT_CHANNEL_COUNT 2

#define MONO_CHANNEL_COUNT 1
#define STEREO_CHANNEL_COUNT 2

#define TOTAL_BUFFERS 2
#define CHANNEL_BLOCK_SIZE_IN_SAMPLES AUDIO_BLOCK_SIZE
#define STEREO_BLOCK_SIZE_IN_SAMPLES (AUDIO_BLOCK_SIZE * STEREO_CHANNEL_COUNT)
#define PCM_SIZE_IN_BYTES 2

#define USB_PLAYBACK_BLOCKSIZE 48
#define MIC_INPUT_BLOCKSIZE 48
#define CODEC_OUTPUT_BLOCKSIZE AUDIO_BLOCK_SIZE

#define CODEC_BUFFER_SIZE_IN_SAMPLES (STEREO_BLOCK_SIZE_IN_SAMPLES * TOTAL_BUFFERS)
#define PCM_BUFFER_SIZE_IN_SAMPLES (MIC_INPUT_BLOCKSIZE * TOTAL_BUFFERS)

#define USB_BUFFER_SIZE_IN_SAMPLES (USB_PLAYBACK_BLOCKSIZE * STEREO_CHANNEL_COUNT)

#define USB_ASRC_BUFFER_SIZE_IN_SAMPLES DSPC_ASRC_BUFFER_LEN(ASRC_FS_IN_48000, ASRC_FS_OUT_48000, ASRC_PHASELEN_28, USB_PLAYBACK_BLOCKSIZE, CODEC_OUTPUT_BLOCKSIZE, STEREO_CHANNEL_COUNT)

#define USB_STATE_LEN DSPC_ASRC_STATE_LEN(USB_PLAYBACK_BLOCKSIZE, CODEC_OUTPUT_BLOCKSIZE, ASRC_FS_IN_48000, ASRC_PHASELEN_28)

#define HID_EP_BUFFER_SIZE 64

#define CODEC_FREQ 48000

#define AWE_COMMAND_BUFFER_LEN 264

// 48000/1000 * 64/8 = 384 (384 / 8 = 48)
#define PDM_BUFFER_SIZE 384
#define NEW_PDM_SAMPLES 192

#define PCM_SAMPLE_SIZE_IN_BYTES 2
#define PCM_SAMPLE_SIZE_IN_BITS 16

#define MIC_AUDIO_IN_FREQ            48000
#define MIC_AUDIO_IN_BIT_RESOLUTION  16
#define MIC_AUDIO_IN_CHANNEL_NBR     1
#define MIC_AUDIO_IN_VOLUME          64

#define HID_REPORT_PACKET_SIZE 56
#define HID_REPORT_DATA_SIZE 52
#define DATA_SIZE_IN_DWORDS 13

#define MAX_PUMP_COUNT 100

#define DEFAULT_AUDIO_IN_VOLUME 64

#define SMOOTHING_COEFF 894598

#define FAILURE 0
#define SUCCESS 1

#define STRIDE1 1
#define STRIDE2 2
#define CHANNEL1 0
#define CHANNEL2 1
#define CHANNEL3 2

extern INT16 I2SBuffer[CODEC_BUFFER_SIZE_IN_SAMPLES];
extern volatile INT32 nI2SBufferNdx;

extern UINT8 HIDInBuff[HID_EP_BUFFER_SIZE];
extern UINT8 HIDOutBuff[HID_EP_BUFFER_SIZE];

extern UINT32 g_packet_buffer[];

extern INT16 USBBuffer[USB_BUFFER_SIZE_IN_SAMPLES];
extern volatile UINT32 nUSBReadBufferNdx;
extern volatile UINT32 nUSBWriteBufferNdx;

extern volatile BOOL g_bReadyToSend;
extern volatile BOOL g_bPacketReceived;
extern volatile BOOL g_bDeferredProcessingRequired;
extern volatile BOOL g_bPlaying;

extern volatile INT32 g_nReceivedPacketCount;
extern volatile BOOL g_bBlinkLED4ForBoardAlive;

extern volatile UINT32 g_nPumpCount;

extern USBD_HandleTypeDef hUsbDeviceFS;
extern I2S_HandleTypeDef hI2S2;
extern I2S_HandleTypeDef hI2S3;

extern DSPC_ASRC USB_ASRC;

extern AWEInstance g_AWEInstance;

extern void BoardSetup(void);

#define ProcessWriteASRC_IRQHandler CAN1_TX_IRQHandler
#define ProcessWriteASRC_IRQ CAN1_TX_IRQn

#define AudioWeaverPump_IRQHandler1 CAN1_RX0_IRQHandler
#define AudioWeaverPump_IRQ1 CAN1_RX0_IRQn

#define ProcessUSBMsg_IRQHandler CAN1_RX1_IRQHandler
#define ProcessUSBMsg_IRQ CAN1_RX1_IRQn

#define AudioWeaverPump_IRQHandler2 CAN1_SCE_IRQHandler
#define AudioWeaverPump_IRQ2 CAN1_SCE_IRQn

#define OBJECT_FOUND 0

void targetInit(void);
void CoreInit(void);
void BoardInit(void);
void AudioInit(void);
void USBMsgInit(void);

void CheckForUSBPacketReady(void);

INT32 usrAudioStart(void);
INT32 usrAudioStop(void);

void USBSendReply(AWEInstance * pAWE);

void AWEIdleLoop(void);

void I2S2_DMA_Complete_CallBack(void);

void I2S3_DMA_Complete_CallBack(void);

void awe_pltGPIOSetPinDir(UINT32 nPinNo, UINT32 nPinDir);
void awe_pltGPIOSetPin(UINT32 nPinNo, UINT32 nValue);
void awe_pltGPIOTogglePin(UINT32 nPinNo);
void awe_pltGPIOGetPin(UINT32 nPinNo, UINT32 * nValue);

void awe_vecScaleSmoothFract32(
		     fract32 *              src,
		     int                    srcInc,
		     fract32 *              dst,
		     int                    dstInc,
		     fract32 * VEC_RESTRICT currentGainFract,
		     fract32                targetGainFract,
		     int                    postShift,
		     fract32                smoothingCoeff,
		     int                    blockSize);

extern volatile fract32 g_nNewVolGain;

#if (HAS_FLASH_FILESYSTEM == 1)

BOOL usrInitFlashFileSystem(void);
INT32 usrGetFlashEraseTime(void);
BOOL usrReadFlashMemory(UINT32 nFlashAddress, UINT32 * pBuffer, UINT32 nDWordsToRead);
BOOL usrWriteFlashMemory(UINT32 nFlashAddress, UINT32 * pBuffer, UINT32 nDWordsToWrite);
BOOL usrEraseFlashMemorySector(UINT32 nStartingAddress, UINT32 nNumberOfSectors);

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

#endif

#endif
