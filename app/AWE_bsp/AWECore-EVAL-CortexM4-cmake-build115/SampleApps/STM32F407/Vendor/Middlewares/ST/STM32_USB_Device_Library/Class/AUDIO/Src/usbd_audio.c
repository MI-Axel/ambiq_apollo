/**
  ******************************************************************************
  * @file    usbd_audio.c
  * @author  MCD Application Team
  * @version V2.4.2
  * @date    11-December-2015
  * @brief   This file provides the Audio core functions.
  *
  * @verbatim
  *
  *          ===================================================================
  *                                AUDIO Class  Description
  *          ===================================================================
 *           This driver manages the Audio Class 1.0 following the "USB Device Class Definition for
  *           Audio Devices V1.0 Mar 18, 98".
  *           This driver implements the following aspects of the specification:
  *             - Device descriptor management
  *             - Configuration descriptor management
  *             - Standard AC Interface Descriptor management
  *             - 1 Audio Streaming Interface (with single channel, PCM, Stereo mode)
  *             - 1 Audio Streaming Endpoint
  *             - 1 Audio Terminal Input (1 channel)
  *             - Audio Class-Specific AC Interfaces
  *             - Audio Class-Specific AS Interfaces
  *             - AudioControl Requests: only SET_CUR and GET_CUR requests are supported (for Mute)
  *             - Audio Feature Unit (limited to Mute control)
  *             - Audio Synchronization type: Asynchronous
  *             - Single fixed audio sampling rate (configurable in usbd_conf.h file)
  *          The current audio class version supports the following audio features:
  *             - Pulse Coded Modulation (PCM) format
  *             - sampling rate: 48KHz.
  *             - Bit resolution: 16
  *             - Number of channels: 2
  *             - No volume control
  *             - Mute/Unmute capability
  *             - Asynchronous Endpoints
  *
  * @note     In HS mode and when the DMA is used, all variables and data structures
  *           dealing with the DMA during the transaction process should be 32-bit aligned.
  *
  *
  *  @endverbatim
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "usbd_audio.h"
#include "usbd_desc.h"
#include "usbd_ctlreq.h"
#include "cs43l22.h"
#include "Platform.h"

#include <stdio.h>
#include <math.h>


/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */


/** @defgroup USBD_AUDIO
  * @brief usbd core module
  * @{
  */

/** @defgroup USBD_AUDIO_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */

/** @defgroup USBD_AUDIO_Private_Defines
  * @{
  */

#define DEV_SPK_MAX_VOL		0x0000
#define DEV_SPK_MIN_VOL		0xDB10
#define DEV_SPK_RES_VOL		0x0030
#define DEV_SPK_CUR_VOL		0xFFF0

extern volatile fract32 g_nNewVolGain;

/** @defgroup USBD_AUDIO_Private_Macros
  * @{
  */
#define AUDIO_SAMPLE_FREQ(frq)      (uint8_t)(frq), (uint8_t)((frq >> 8)), (uint8_t)((frq >> 16))

#define AUDIO_PACKET_SZE(frq)          (uint8_t)(((frq * 2 * 2)/1000) & 0xFF), \
                                       (uint8_t)((((frq * 2 * 2)/1000) >> 8) & 0xFF)

/**
  * @}
  */


/** @defgroup USBD_AUDIO_Private_FunctionPrototypes
  * @{
  */


static uint8_t USBD_AUDIO_Init(USBD_HandleTypeDef *pdev,
                              uint8_t cfgidx);

static uint8_t USBD_AUDIO_DeInit(USBD_HandleTypeDef *pdev,
                                uint8_t cfgidx);

static uint8_t USBD_AUDIO_Setup(USBD_HandleTypeDef *pdev,
                               USBD_SetupReqTypedef *req);

static uint8_t *USBD_AUDIO_GetCfgDesc(uint16_t *length);

static uint8_t *USBD_AUDIO_GetDeviceQualifierDesc(uint16_t *length);

static uint8_t USBD_AUDIO_DataIn(USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t USBD_AUDIO_DataOut(USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t USBD_AUDIO_EP0_RxReady(USBD_HandleTypeDef *pdev);

static uint8_t USBD_AUDIO_EP0_TxReady(USBD_HandleTypeDef *pdev);

static uint8_t USBD_AUDIO_SOF(USBD_HandleTypeDef *pdev);

static uint8_t USBD_AUDIO_IsoINIncomplete(USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t USBD_AUDIO_IsoOutIncomplete(USBD_HandleTypeDef *pdev, uint8_t epnum);

static void AUDIO_REQ_GetCurrent(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req);

static void AUDIO_REQ_SetCurrent(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req);


/**
  * @}
  */

/** @defgroup USBD_AUDIO_Private_Variables
  * @{
  */

USBD_AUDIO_HandleTypeDef g_Audio;

USBD_ClassTypeDef USBD_AUDIO =
{
  USBD_AUDIO_Init,
  USBD_AUDIO_DeInit,
  USBD_AUDIO_Setup,
  USBD_AUDIO_EP0_TxReady,
  USBD_AUDIO_EP0_RxReady,
  USBD_AUDIO_DataIn,
  USBD_AUDIO_DataOut,
  USBD_AUDIO_SOF,
  USBD_AUDIO_IsoINIncomplete,
  USBD_AUDIO_IsoOutIncomplete,
  USBD_AUDIO_GetCfgDesc,
  USBD_AUDIO_GetCfgDesc,
  USBD_AUDIO_GetCfgDesc,
  USBD_AUDIO_GetDeviceQualifierDesc
};

// -90.5 dB
int16_t nMinVol = DEV_SPK_MIN_VOL;

// 0 dB
int16_t nMaxVol = DEV_SPK_MAX_VOL;

// 1/256 dB step
int16_t nResVol = DEV_SPK_RES_VOL;

// -22.5 dB
volatile int16_t g_nCurrentVolume = DEV_SPK_CUR_VOL;

extern const uint8_t USBD_AUDIO_CfgDesc[USB_AUDIO_CONFIG_DESC_SIZ];
extern const uint8_t HID_ReportDescriptor[REPORT_DESC_SIZE];
extern const uint8_t USBD_HID_Desc[USB_HID_DESC_SIZE];
extern const uint8_t USBD_AUDIO_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC];

/**
  * @}
  */

/** @defgroup USBD_AUDIO_Private_Functions
  * @{
  */

/**
  * @brief  USBD_AUDIO_Init
  *         Initialize the AUDIO interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t USBD_AUDIO_Init(USBD_HandleTypeDef *pdev,
                               uint8_t cfgidx)
{
    USBD_AUDIO_HandleTypeDef * haudio;

    /* Open EP IN */
    USBD_LL_OpenEP(pdev,
                 HID_IN_EP,
                 USBD_EP_TYPE_INTR,
                 HID_IN_EP_SIZE);


    /* Open EP OUT */
    USBD_LL_OpenEP(pdev,
                 HID_OUT_EP,
                 USBD_EP_TYPE_INTR,
                 HID_OUT_EP_SIZE);

    /* Open EP OUT */
    USBD_LL_OpenEP(pdev,
                 AUDIO_OUT_EP,
                 USBD_EP_TYPE_ISOC,
                 AUDIO_OUT_PACKET_SIZE_BYTES);

    pdev->pClassData = &g_Audio;

    haudio = (USBD_AUDIO_HandleTypeDef *)pdev->pClassData;
    haudio->alt_setting = 0;
    haudio->offset = AUDIO_OFFSET_UNKNOWN;
    haudio->writeNdx = 0;
    haudio->readNdx = 0;
    haudio->rd_enable = 0;
    haudio->buffer = USBBuffer;

    /* Initialize the Audio output Hardware layer */
    if (((USBD_AUDIO_ItfTypeDef *)pdev->pUserData)->Init(USBD_AUDIO_FREQ, AUDIO_DEFAULT_VOLUME, 0) != USBD_OK)
    {
      return USBD_FAIL;
    }

    // Prepare Out endpoint to receive HID Report packets
    USBD_LL_PrepareReceive(pdev,
                           HID_OUT_EP,
                           HIDOutBuff,
                           HID_EP_BUFFER_SIZE);

    // Prepare Out endpoint to receive next audio packet
    USBD_LL_PrepareReceive(pdev,
                           AUDIO_OUT_EP,
                           (PBYTE)haudio->buffer,
                           AUDIO_OUT_PACKET_SIZE_BYTES);

    return USBD_OK;
}

/**
  * @brief  USBD_AUDIO_Init
  *         DeInitialize the AUDIO layer
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t USBD_AUDIO_DeInit(USBD_HandleTypeDef *pdev,
                                 uint8_t cfgidx)
{
    USBD_LL_CloseEP(pdev, HID_IN_EP);
    USBD_LL_CloseEP(pdev, HID_OUT_EP);
    USBD_LL_CloseEP(pdev, AUDIO_OUT_EP);

    ((USBD_AUDIO_ItfTypeDef *)pdev->pUserData)->DeInit(0);

    return USBD_OK;
}

/**
  * @brief  USBD_AUDIO_Setup
  *         Handle the AUDIO specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
static uint8_t USBD_AUDIO_Setup(USBD_HandleTypeDef *pdev,
                                USBD_SetupReqTypedef *req)
{
    USBD_AUDIO_HandleTypeDef * haudio;
    uint16_t len;
    uint8_t *pbuf;
    uint8_t ret = USBD_OK;
    haudio = (USBD_AUDIO_HandleTypeDef*) pdev->pClassData;

    //printf("USBD_AUDIO_Setup: bmRequest = 0x%X, bRequest = 0x%X, wValue = 0x%X, wIndex = 0x%X\n\r", req->bmRequest, req->bRequest, req->wValue, req->wIndex);

    switch (req->bmRequest & USB_REQ_TYPE_MASK)
    {
        case USB_REQ_TYPE_CLASS:

            switch (req->bRequest)
            {
                case AUDIO_REQ_GET_CUR:

                    // Get volume or mute current value
                    AUDIO_REQ_GetCurrent(pdev, req);
                    break;

                case AUDIO_REQ_SET_CUR:

                    AUDIO_REQ_SetCurrent(pdev, req);
                    break;

                case AUDIO_REQ_GET_MIN:

                    USBD_CtlSendData(pdev, (uint8_t *)&nMinVol, sizeof(nMinVol) );
                    break;

                case AUDIO_REQ_GET_MAX:

                    USBD_CtlSendData(pdev, (uint8_t *)&nMaxVol, sizeof(nMaxVol) );
                    break;

                case AUDIO_REQ_GET_RES:

                    USBD_CtlSendData(pdev, (uint8_t *)&nResVol, sizeof(nResVol) );
                    break;

                default:
                    USBD_CtlError(pdev, req);
                    ret = USBD_FAIL;
            }
            break;

        case USB_REQ_TYPE_STANDARD:

            switch (req->bRequest)
            {
                case USB_REQ_GET_DESCRIPTOR:

                    if ( (req->wValue >> 8) == AUDIO_DESCRIPTOR_TYPE)
                    {
                        pbuf = (uint8_t *)USBD_AUDIO_CfgDesc + 18;
                        len = MIN(USB_AUDIO_DESC_SIZ, req->wLength);
                    }
                    else if ( (req->wValue >> 8) == HID_REPORT_DESC_TYPE)
                    {
                        len = MIN(REPORT_DESC_SIZE, req->wLength);
                        pbuf = (UINT8 *)HID_ReportDescriptor;
                    }
                    else if ( (req->wValue >> 8) == HID_DESCRIPTOR_TYPE)
                    {
                        pbuf = (uint8_t *)USBD_HID_Desc;
                        len = MIN(USB_HID_DESC_SIZE, req->wLength);
                    }
                    else
                    {
                    	break;
                    }

                    USBD_CtlSendData(pdev,
                                     pbuf,
                                     len);
                    break;

                case USB_REQ_GET_INTERFACE:

                    USBD_CtlSendData(pdev, (uint8_t *)&(haudio->alt_setting), 1);
                    break;

                case USB_REQ_SET_INTERFACE:

                    if ((uint8_t)(req->wValue) <= USBD_MAX_NUM_INTERFACES)
                    {
                        haudio->alt_setting = (uint8_t)(req->wValue);
                    }
                    else
                    {
                        /* Call the error management function (command will be nacked */
                        USBD_CtlError(pdev, req);
                    }
                    break;

                default:
                    USBD_CtlError(pdev, req);
                    ret = USBD_FAIL;

            }   // End switch

            break;

        default:
            ;

    }   // End switch

    return ret;
}


/**
  * @brief  USBD_AUDIO_GetCfgDesc
  *         return configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t *USBD_AUDIO_GetCfgDesc(uint16_t *length)
{
    *length = sizeof(USBD_AUDIO_CfgDesc);
    return (uint8_t *)USBD_AUDIO_CfgDesc;
}


/**
  * @brief  USBD_AUDIO_EP0_RxReady
  *         handle EP0 Rx Ready event
  * @param  pdev: device instance
  * @retval status
  */
static uint8_t USBD_AUDIO_EP0_RxReady(USBD_HandleTypeDef *pdev)
{
    USBD_AUDIO_HandleTypeDef *haudio;

    haudio = (USBD_AUDIO_HandleTypeDef *)pdev->pClassData;

    if (haudio->control.cmd == AUDIO_REQ_SET_CUR)
    {
        if (haudio->control.unit == AUDIO_OUT_STREAMING_CTRL)
        {
            uint8_t nControlSelector = HIBYTE(pdev->request.wValue);

            if (nControlSelector == AUDIO_CONTROL_MUTE)
            {
                ((USBD_AUDIO_ItfTypeDef *)pdev->pUserData)->MuteCtl(haudio->control.data[0]);
            }
            else if (nControlSelector == AUDIO_CONTROL_VOLUME)
            {
                int16_t  nValue;
                int32_t  nVolume;

                nValue = haudio->control.data[1];
                nValue = (nValue << 8) | haudio->control.data[0];

                nVolume = 100 - (int32_t)floorf(100.0f * (nValue / -9456.0f ) );
                cs43l22_SetVolume(AUDIO_I2C_ADDRESS, (uint8_t)nVolume);
            }

            haudio->control.cmd = 0;
            haudio->control.len = 0;
        }
    }

  return USBD_OK;
}


/**
  * @brief  USBD_AUDIO_EP0_TxReady
  *         handle EP0 TRx Ready event
  * @param  pdev: device instance
  * @retval status
  */
static uint8_t USBD_AUDIO_EP0_TxReady(USBD_HandleTypeDef *pdev)
{
    return USBD_OK;
}
/**
  * @brief  USBD_AUDIO_SOF
  *         handle SOF event
  * @param  pdev: device instance
  * @retval status
  */
static uint8_t USBD_AUDIO_SOF(USBD_HandleTypeDef *pdev)
{
    return USBD_OK;
}


/**
  * @brief  USBD_AUDIO_IsoINIncomplete
  *         handle data ISO IN Incomplete event
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t USBD_AUDIO_IsoINIncomplete(USBD_HandleTypeDef *pdev, uint8_t epnum)
{

  return USBD_OK;
}
/**
  * @brief  USBD_AUDIO_IsoOutIncomplete
  *         handle data ISO OUT Incomplete event
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t USBD_AUDIO_IsoOutIncomplete(USBD_HandleTypeDef *pdev, uint8_t epnum)
{

  return USBD_OK;
}


/**
  * @brief  USBD_AUDIO_DataIn
  *         handle data IN Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t USBD_AUDIO_DataIn(USBD_HandleTypeDef *pdev, uint8_t epnum)
{
    if (g_bReadyToSend)
    {
        NVIC_SetPendingIRQ(ProcessUSBMsg_IRQ);
    }

    return USBD_OK;
}


/**
  * @brief  USBD_AUDIO_DataOut
  *         handle data OUT Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t USBD_AUDIO_DataOut(USBD_HandleTypeDef *pdev, uint8_t epnum)
{
    if (epnum == AUDIO_OUT_EP)
    {
        USBD_AUDIO_HandleTypeDef * haudio = (USBD_AUDIO_HandleTypeDef*)pdev->pClassData;

        // Prepare Out endpoint to receive next audio packet
        USBD_LL_PrepareReceive(pdev,
                               AUDIO_OUT_EP,
                               (PBYTE)&(haudio->buffer[nUSBWriteBufferNdx]),
                               AUDIO_OUT_PACKET_SIZE_BYTES);

        nUSBWriteBufferNdx = (nUSBWriteBufferNdx + NEW_USB_SAMPLES) % AUDIO_BUFFER_SIZE_IN_SAMPLES;

        // Issue software interrupt to place received data into ASRC buffer
        NVIC_SetPendingIRQ(ProcessWriteASRC_IRQ);
    }
    else if (epnum == HID_OUT_EP)
    {
        uint8_t nPayloadByteCount;
        uint32_t nPayloadWordCount;
        uint32_t nBufferEndingNdx;
        static uint32_t s_nPacketBufferNdx = 0;
        static uint32_t s_nPacketLenInDWords = 0;

        // Prepare Out endpoint to receive next HID packet
        USBD_LL_PrepareReceive(pdev,
                               HID_OUT_EP,
                               HIDOutBuff,
                               HID_EP_BUFFER_SIZE);

        nPayloadByteCount = HIDOutBuff[3];

        nPayloadWordCount = nPayloadByteCount >> 2;

        nBufferEndingNdx = s_nPacketBufferNdx + nPayloadWordCount;

        if (nBufferEndingNdx > MAX_COMMAND_BUFFER_LEN)
        {
            s_nPacketBufferNdx = 0;
            return USBD_OK;
        }

        // Copy the data into the AWE packet buffer
        memcpy(&g_packet_buffer[s_nPacketBufferNdx], &HIDOutBuff[4], nPayloadByteCount);

        if (s_nPacketBufferNdx == 0)
        {
            uint32_t * pPacketLen = (uint32_t *)&HIDOutBuff[4];
            s_nPacketLenInDWords = *pPacketLen >> 16;
        }

        s_nPacketBufferNdx += nPayloadWordCount;

        if (s_nPacketBufferNdx >= s_nPacketLenInDWords)
        {
            // Indicate packet is ready.
            g_bPacketReceived = TRUE;

            s_nPacketBufferNdx = 0;
        }
    }

    return USBD_OK;

}   // End USBD_AUDIO_DataOut


/**
  * @brief  AUDIO_Req_GetCurrent
  *         Handles the GET_CUR Audio control request.
  * @param  pdev: instance
  * @param  req: setup class request
  * @retval status
  */
static void AUDIO_REQ_GetCurrent(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req)
{
    USBD_AUDIO_HandleTypeDef *haudio;

    haudio = (USBD_AUDIO_HandleTypeDef*)pdev->pClassData;

    if ( (req->wValue >> 8) == AUDIO_CONTROL_MUTE)
    {
        memset(haudio->control.data, 0, 64);

        // Send the current mute state
        USBD_CtlSendData(pdev,
                        haudio->control.data,
                        req->wLength);
    }
    else
    {
        // Send the current volume
        USBD_CtlSendData(pdev,
                        (uint8_t *)&g_nCurrentVolume,
                        sizeof(g_nCurrentVolume) );
    }
}


/**
  * @brief  AUDIO_Req_SetCurrent
  *         Handles the SET_CUR Audio control request.
  * @param  pdev: instance
  * @param  req: setup class request
  * @retval status
  */
static void AUDIO_REQ_SetCurrent(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req)
{
    USBD_AUDIO_HandleTypeDef *haudio;

    haudio = (USBD_AUDIO_HandleTypeDef*)pdev->pClassData;

    if (req->wLength)
    {
        /* Prepare the reception of the buffer over EP0 */
        USBD_CtlPrepareRx(pdev,
                          haudio->control.data,
                          req->wLength);

        haudio->control.cmd = AUDIO_REQ_SET_CUR;     /* Set the request value */
        haudio->control.len = req->wLength;          /* Set the request data length */
        haudio->control.unit = HIBYTE(req->wIndex);  /* Set the request target unit */
    }

}


/**
* @brief  DeviceQualifierDescriptor
*         return Device Qualifier descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
static uint8_t * USBD_AUDIO_GetDeviceQualifierDesc(uint16_t *length)
{
    *length = sizeof(USBD_AUDIO_DeviceQualifierDesc);

    return (uint8_t *)USBD_AUDIO_DeviceQualifierDesc;
}


/**
* @brief  USBD_AUDIO_RegisterInterface
* @param  fops: Audio interface callback
* @retval status
*/
uint8_t USBD_AUDIO_RegisterInterface(USBD_HandleTypeDef *pdev,
                                     USBD_AUDIO_ItfTypeDef *fops)
{
    if (fops != NULL)
    {
        pdev->pUserData= fops;
    }
    return 0;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
