/*******************************************************************************
*
*               USB Descriptors
*               ---------------
*
********************************************************************************
*     USBDescriptors.c
********************************************************************************
*
*     Description:  USB Descriptors for STM Discovery board
*
*     Copyright:    (c) 2018 DSP Concepts, Inc. All rights reserved.
*                   3235 Kifer Road
*                   Santa Clara, CA 95054
*
*******************************************************************************/
#include "usbd_audio.h"

#define AUDIO_SAMPLE_FREQ(frq)      (uint8_t)(frq), (uint8_t)((frq >> 8)), (uint8_t)((frq >> 16))

#define AUDIO_PACKET_SZE(frq)          (uint8_t)(((frq * 2 * 2)/1000) & 0xFF), \
                                       (uint8_t)((((frq * 2 * 2)/1000) >> 8) & 0xFF)

/* USB AUDIO device Configuration Descriptor */
__ALIGN_BEGIN const uint8_t USBD_AUDIO_CfgDesc[USB_AUDIO_CONFIG_DESC_SIZ] __ALIGN_END =
{
  /* Configuration 1 */
  0x09,                                 /* bLength */
  USB_DESC_TYPE_CONFIGURATION,          /* bDescriptorType */
  LOBYTE(USB_AUDIO_CONFIG_DESC_SIZ),    /* wTotalLength  141 bytes*/
  HIBYTE(USB_AUDIO_CONFIG_DESC_SIZ),
  USBD_MAX_NUM_INTERFACES,              /* bNumInterfaces */
  0x01,                                 /* bConfigurationValue */
  0x00,                                 /* iConfiguration */
  0xC0,                                 /* bmAttributes  BUS Powred*/
  0x32,                                 /* bMaxPower = 100 mA*/
  /* 09 byte*/

  /* USB Speaker Standard interface descriptor */
  AUDIO_INTERFACE_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_INTERFACE,              /* bDescriptorType */
  0x00,                                 /* bInterfaceNumber */
  0x00,                                 /* bAlternateSetting */
  0x00,                                 /* bNumEndpoints */
  USB_DEVICE_CLASS_AUDIO,               /* bInterfaceClass */
  AUDIO_SUBCLASS_AUDIOCONTROL,          /* bInterfaceSubClass */
  AUDIO_PROTOCOL_UNDEFINED,             /* bInterfaceProtocol */
  0x00,                                 /* iInterface */
  /* 09 byte*/

  /* USB Speaker Class-specific AC Interface Descriptor */
  AUDIO_INTERFACE_DESC_SIZE,            /* bLength */
  AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */
  AUDIO_CONTROL_HEADER,                 /* bDescriptorSubtype */
  0x00,          /* 1.00 */             /* bcdADC */
  0x01,
  0x27,                                 /* wTotalLength = 39 */
  0x00,
  0x01,                                 /* bInCollection */
  0x01,                                 /* baInterfaceNr */
  /* 09 byte*/

  /* USB Speaker Input Terminal Descriptor */
  AUDIO_INPUT_TERMINAL_DESC_SIZE,       /* bLength */
  AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */
  AUDIO_CONTROL_INPUT_TERMINAL,         /* bDescriptorSubtype */
  0x01,                                 /* bTerminalID */
  0x01,                                 /* wTerminalType AUDIO_TERMINAL_USB_STREAMING   0x0101 */
  0x01,
  0x00,                                 /* bAssocTerminal */
  0x01,                                 /* bNrChannels */
  0x00,                                 /* wChannelConfig 0x0000  Mono */
  0x00,
  0x00,                                 /* iChannelNames */
  0x00,                                 /* iTerminal */
  /* 12 byte*/

  /* USB Speaker Audio Feature Unit Descriptor */
  0x09,                                 /* bLength */
  AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */
  AUDIO_CONTROL_FEATURE_UNIT,           /* bDescriptorSubtype */
  AUDIO_OUT_STREAMING_CTRL,             /* bUnitID */
  0x01,                                 /* bSourceID */
  0x01,                                 /* bControlSize */
  AUDIO_CONTROL_MUTE | AUDIO_CONTROL_VOLUME, /* bmaControls(0) */
  0x00,                                 /* bmaControls(1) */
  0x00,                                 /* iTerminal */
  /* 09 byte*/

  /*USB Speaker Output Terminal Descriptor */
  0x09,                                 /* bLength */
  AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */
  AUDIO_CONTROL_OUTPUT_TERMINAL,        /* bDescriptorSubtype */
  0x03,                                 /* bTerminalID */
  0x01,                                 /* wTerminalType  0x0301*/
  0x03,
  0x00,                                 /* bAssocTerminal */
  0x02,                                 /* bSourceID */
  0x00,                                 /* iTerminal */
  /* 09 byte*/

  /* USB Speaker Standard AS Interface Descriptor - Audio Streaming Zero Bandwith */
  /* Interface 1, Alternate Setting 0                                             */
  AUDIO_INTERFACE_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_INTERFACE,              /* bDescriptorType */
  0x01,                                 /* bInterfaceNumber */
  0x00,                                 /* bAlternateSetting */
  0x00,                                 /* bNumEndpoints */
  USB_DEVICE_CLASS_AUDIO,               /* bInterfaceClass */
  AUDIO_SUBCLASS_AUDIOSTREAMING,        /* bInterfaceSubClass */
  AUDIO_PROTOCOL_UNDEFINED,             /* bInterfaceProtocol */
  0x00,                                 /* iInterface */
  /* 09 byte*/

  /* USB Speaker Standard AS Interface Descriptor - Audio Streaming Operational */
  /* Interface 1, Alternate Setting 1                                           */
  AUDIO_INTERFACE_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_INTERFACE,              /* bDescriptorType */
  0x01,                                 /* bInterfaceNumber */
  0x01,                                 /* bAlternateSetting */
  0x01,                                 /* bNumEndpoints */
  USB_DEVICE_CLASS_AUDIO,               /* bInterfaceClass */
  AUDIO_SUBCLASS_AUDIOSTREAMING,        /* bInterfaceSubClass */
  AUDIO_PROTOCOL_UNDEFINED,             /* bInterfaceProtocol */
  0x00,                                 /* iInterface */
  /* 09 byte*/

  /* USB Speaker Audio Streaming Interface Descriptor */
  AUDIO_STREAMING_INTERFACE_DESC_SIZE,  /* bLength */
  AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */
  AUDIO_STREAMING_GENERAL,              /* bDescriptorSubtype */
  0x01,                                 /* bTerminalLink */
  0x01,                                 /* bDelay */
  0x01,                                 /* wFormatTag AUDIO_FORMAT_PCM  0x0001*/
  0x00,
  /* 07 byte*/

  /* USB Speaker Audio Type III Format Interface Descriptor */
  0x0B,                                 /* bLength */
  AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */
  AUDIO_STREAMING_FORMAT_TYPE,          /* bDescriptorSubtype */
  AUDIO_FORMAT_TYPE_III,                /* bFormatType */
  0x02,                                 /* bNrChannels */
  0x02,                                 /* bSubFrameSize :  2 Bytes per frame (16bits) */
  16,                                   /* bBitResolution (16-bits per sample) */
  0x01,                                 /* bSamFreqType only one frequency supported */
  AUDIO_SAMPLE_FREQ(USBD_AUDIO_FREQ),         /* Audio sampling frequency coded on 3 bytes */
  /* 11 byte*/

  /* Endpoint 1 - Standard Descriptor */
  AUDIO_STANDARD_ENDPOINT_DESC_SIZE,    /* bLength */
  USB_DESC_TYPE_ENDPOINT,               /* bDescriptorType */
  AUDIO_OUT_EP,                         /* bEndpointAddress 1 out endpoint*/
  USBD_EP_TYPE_ISOC,                    /* bmAttributes */
  AUDIO_PACKET_SZE(USBD_AUDIO_FREQ),    /* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  0x01,                                 /* bInterval */
  0x00,                                 /* bRefresh */
  0x00,                                 /* bSynchAddress */
  /* 09 byte*/

  /* Endpoint - Audio Streaming Descriptor*/
  AUDIO_STREAMING_ENDPOINT_DESC_SIZE,   /* bLength */
  AUDIO_ENDPOINT_DESCRIPTOR_TYPE,       /* bDescriptorType */
  AUDIO_ENDPOINT_GENERAL,               /* bDescriptor */
  0x00,                                 /* bmAttributes */
  0x00,                                 /* bLockDelayUnits */
  0x00,                                 /* wLockDelay */
  0x00,
  /* 07 byte*/

    //************* Descriptor of Custom HID interface ***************
    USB_INTERFACE_DESC_SIZE,          // bLength            : Interface Descriptor size
    USB_INTERFACE_DESCRIPTOR_TYPE,    // bDescriptorType    : Interface descriptor type
    HID_INTERFACE_NUMBER,             // bInterfaceNumber   : Number of Interface
    0x00,                             // bAlternateSetting  : Alternate setting
    0x02,                             // bNumEndpoints      : 2 endpoints
    USB_DEVICE_CLASS_HID,             // bInterfaceClass    : HID
    HID_SUBCLASS_NONE,                // bInterfaceSubClass : 1=BOOT, 0=no boot
    HID_PROTOCOL_NONE,                // nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse
    0,                                // iInterface         : Index of string descriptor
    //******************* Descriptor of Custom HID HID *******************
    USB_HID_DESC_SIZE,                // bLength            : HID Descriptor size
    HID_DESCRIPTOR_TYPE,              // bDescriptorType    : HID
    WBVAL(0x0110),                    // bcdHID             : HID Class Spec release number
    0x00,                             // bCountryCode       : Hardware target country
    0x01,                             // bNumDescriptors    : Nbr of HID class descriptors to follow
    HID_REPORT_DESCRIPTOR_TYPE,       // bDescriptorType    : HID report descriptor
    WBVAL(REPORT_DESC_SIZE),          // wItemLength        : Total length of Report descriptor
    //******************* Endpoints IN descriptor*****************
    USB_ENDPOINT_DESC_SIZE,           // bLength            : Endpoint Descriptor size
    USB_ENDPOINT_DESCRIPTOR_TYPE,     // bDescriptorType    : Endpoint
    HID_IN_EP,                        // bEndpointAddress   : Endpoint Address (IN)
    USB_ENDPOINT_TYPE_INTERRUPT,      // bmAttributes       : Interrupt endpoint
    WBVAL(HID_EP_BUFFER_SIZE),        // wMaxPacketSize     : 64 Bytes max
    HID_EP_bInterval,                 // bInterval          : Polling Interval (10 ms)
    //******************* Endpoints OUT descriptor*****************
    USB_ENDPOINT_DESC_SIZE,	          // bLength            : Endpoint Descriptor size
    USB_ENDPOINT_DESCRIPTOR_TYPE,     // bDescriptorType    : Endpoint descriptor type
    HID_OUT_EP,	                      // bEndpointAddress   : Endpoint Address (OUT)
    USB_ENDPOINT_TYPE_INTERRUPT,      // bmAttributes       : Interrupt endpoint
    WBVAL(HID_EP_BUFFER_SIZE),        // wMaxPacketSize     : 64 Bytes max
    HID_EP_bInterval                  // bInterval          : Polling Interval (10 ms)
};

__ALIGN_BEGIN const uint8_t HID_ReportDescriptor[REPORT_DESC_SIZE] __ALIGN_END =
{
    0x06, 0x00, 0xFF,// USAGE_PAGE (Vendor Defined)
    0x09, 0x01,      // USAGE (Vendor Usage 1)

    0xA1, 0x01,      // COLLECTION (Application)

	0x15, 0x00,		 // LOGICAL MINIMUM (0)
	0x25, 0xFF,		 // LOGICAL MAXIMUM (255)

	// Input Report
	0x85, 0x01,		 // Report ID 1
	0x75, 0x08,		 // REPORT SIZE (8 bits)
	0x95, 0x37, 	 // REPORT COUNT (56 bytes)
	0x09, 0x02,		 // USAGE (Vendor Usage 2)
	0x81, 0x86,		 // (DATA, VAR, ABSOLUTE, BUFFERED BYTES)

	// Output Report
    0x85, 0x01,		 // Report ID 1
	0x75, 0x08,		 // REPORT SIZE (8 bits)
	0x95, 0x37, 	 // REPORT COUNT (56 bytes)
	0x09, 0x02,		 // USAGE (Vendor Usage 2)
	0x91, 0x86,		 // (DATA, VAR, ABSOLUTE, BUFFERED BYTES)

	0xC0		 	 // END COLLECTION (Application)

};	// End HID_ReportDescriptor

__ALIGN_BEGIN const uint8_t USBD_HID_Desc[USB_HID_DESC_SIZE] __ALIGN_END  =
{
  /* 18 */
  0x09,                 /*bLength: HID Descriptor size*/
  HID_DESCRIPTOR_TYPE,  /*bDescriptorType: HID*/
  0x11,                 /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,                 /*bCountryCode: Hardware target country*/
  0x01,                 /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,                 /*bDescriptorType*/
  REPORT_DESC_SIZE,     /*wItemLength: Total length of Report descriptor*/
  0x00,
};

/* USB Standard Device Descriptor */
__ALIGN_BEGIN const uint8_t USBD_AUDIO_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC] __ALIGN_END =
{
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00,
};
