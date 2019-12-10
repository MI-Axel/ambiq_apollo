/*******************************************************************************
*
*               Audio Framework
*               ---------------
*
********************************************************************************
*     AudioDriver.c
********************************************************************************
*
*     Description:  AudioWeaver Audio Driver for STM Discovery board
*
*     Copyright:    (c) 2018 DSP Concepts, Inc. All rights reserved.
*                   3235 Kifer Road
*                   Santa Clara, CA 95054
*
*******************************************************************************/
#include "Platform.h"
#include <string.h>

extern I2S_HandleTypeDef hI2S2;

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
__ALIGN_BEGIN INT16 USBBuffer[USB_BUFFER_SIZE_IN_SAMPLES] __ALIGN_END;

volatile UINT32 nUSBReadBufferNdx = 0;
volatile UINT32 nUSBWriteBufferNdx = 0;

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
__ALIGN_BEGIN INT16 I2SBuffer[CODEC_BUFFER_SIZE_IN_SAMPLES] __ALIGN_END;

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
__ALIGN_BEGIN INT16 USB_ASRCBuffer[USB_ASRC_BUFFER_SIZE_IN_SAMPLES] __ALIGN_END;

#if defined ( __ICCARM__ ) // IAR Compiler
  #pragma data_alignment=4
#endif
__ALIGN_BEGIN INT16 USB_asrcAccumulator[DSPC_ASRC_ACCUM_LEN(STEREO_CHANNEL_COUNT)] __ALIGN_END;

INT16 USB_ASRCSamples[STEREO_BLOCK_SIZE_IN_SAMPLES];
INT16 ZeroedSamples[STEREO_BLOCK_SIZE_IN_SAMPLES];

#ifdef ENABLE_MIC

    #if defined ( __ICCARM__ ) /*!< IAR Compiler */
      #pragma data_alignment=4
    #endif
    __ALIGN_BEGIN UINT16 PDMBuffer[PDM_BUFFER_SIZE] __ALIGN_END;

    #if defined ( __ICCARM__ ) /*!< IAR Compiler */
      #pragma data_alignment=4
    #endif
    __ALIGN_BEGIN INT16 PCMBuffer[PCM_BUFFER_SIZE_IN_SAMPLES] __ALIGN_END;

#endif

volatile BOOL g_bAudioPump1Active = FALSE;
volatile BOOL g_bAudioPump2Active = FALSE;

volatile BOOL g_bPlaying = FALSE;

volatile UINT32 g_nPumpCount = 0;

DSPC_ASRC USB_ASRC;

static volatile fract32 nVolCurrentGain = 0;

volatile fract32 g_nNewVolGain = 0;


//-----------------------------------------------------------------------------
// METHOD:  AudioInit
// PURPOSE: Initialize AWE
//-----------------------------------------------------------------------------
AWE_OPTIMIZE_FOR_SPACE
AWE_FW_SLOW_CODE
void AudioInit(void)
{
    // When no USB audio playing pass this buffer of silence to the CODEC
    memset(ZeroedSamples, 0, STEREO_BLOCK_SIZE_IN_SAMPLES * sizeof(INT16) );

    // CODEC double buffer
    memset(I2SBuffer, 0, CODEC_BUFFER_SIZE_IN_SAMPLES * sizeof(INT16) );

   // Initialize the ASRC for USB Playback
	dspc_asrc_init_Q15(&DSPC_ASRC_48000_TO_48000_32M_080DB_PROPS,
                       USB_ASRCBuffer,
                       USB_STATE_LEN,
                       DSPC_ASRC_GUARD_LEN(ASRC_FS_IN_48000, ASRC_FS_OUT_48000, ASRC_PHASELEN_28, CODEC_OUTPUT_BLOCKSIZE),
                       USB_asrcAccumulator,
                       DSPC_ASRC_ACCUM_LEN(STEREO_CHANNEL_COUNT),
                       STEREO_CHANNEL_COUNT,
                       &USB_ASRC);

    dspc_asrc_write_zeros_Q15(&USB_ASRC, USB_STATE_LEN / 2);

    // USB audio interrupt
    HAL_NVIC_SetPriority(OTG_FS_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(OTG_FS_IRQn);

    // Ready to send next USB reply packet
    HAL_NVIC_SetPriority(ProcessUSBMsg_IRQ, 2, 0);
    HAL_NVIC_EnableIRQ(ProcessUSBMsg_IRQ);

    // CODEC I2S Processing Interrupt
    HAL_NVIC_SetPriority(I2S3_DMAx_IRQ, 3, 0);
    HAL_NVIC_EnableIRQ(I2S3_DMAx_IRQ);

    // Mic I2S Processing Interrupt
    HAL_NVIC_SetPriority(I2S2_DMAx_IRQ, 3, 0);
    HAL_NVIC_EnableIRQ(I2S2_DMAx_IRQ);

    // DPC to process writing to ASRC
    HAL_NVIC_SetPriority(ProcessWriteASRC_IRQ, 3, 0);
    HAL_NVIC_EnableIRQ(ProcessWriteASRC_IRQ);

    // Higher Level AWE Processing Interrupt
    HAL_NVIC_SetPriority(AudioWeaverPump_IRQ1, 6, 0);
    HAL_NVIC_EnableIRQ(AudioWeaverPump_IRQ1);

    // Lower level AWE Processing Interrupt
    HAL_NVIC_SetPriority(AudioWeaverPump_IRQ2, 7, 0);
    HAL_NVIC_EnableIRQ(AudioWeaverPump_IRQ2);

    BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_AUTO, AUDIO_DEFAULT_VOLUME, CODEC_FREQ);

#ifdef ENABLE_MIC
    // PDM double buffer
    memset(PDMBuffer, 0, PDM_BUFFER_SIZE * sizeof(INT16) );

    BSP_AUDIO_IN_Init(MIC_AUDIO_IN_FREQ, MIC_AUDIO_IN_BIT_RESOLUTION, MIC_AUDIO_IN_CHANNEL_NBR);

    BSP_AUDIO_IN_Record(PDMBuffer, PDM_BUFFER_SIZE);
#endif

    // Start CODEC continuously playing
    BSP_AUDIO_OUT_Play( (UINT16 *)I2SBuffer, CODEC_BUFFER_SIZE_IN_SAMPLES);

}	// End AudioInit


#ifdef ENABLE_MIC
//-----------------------------------------------------------------------------
// METHOD:  I2S2_DMA_Complete_CallBack
// PURPOSE: DMA complete interrupt handler for the Mic
//-----------------------------------------------------------------------------
void I2S2_DMA_Complete_CallBack(void)
{
    static INT32 nPDMBufferNdx = 0;
    static INT32 nPCMBufferNdx = 0;

    BSP_AUDIO_IN_PDMToPCM(&PDMBuffer[nPDMBufferNdx], (UINT16 *)&PCMBuffer[nPCMBufferNdx]);

    // Double buffer index
    nPDMBufferNdx = (nPDMBufferNdx + NEW_PDM_SAMPLES) % PDM_BUFFER_SIZE;
    nPCMBufferNdx = (nPCMBufferNdx + MIC_INPUT_BLOCKSIZE) % PCM_BUFFER_SIZE_IN_SAMPLES;

}   // End I2S2_DMA_Complete_CallBack
#endif


//-----------------------------------------------------------------------------
// METHOD:  ProcessWriteASRC_IRQHandler
// PURPOSE: DPC for writing to ASRC buffer for USB
//-----------------------------------------------------------------------------
void ProcessWriteASRC_IRQHandler(void)
{
    INT32 nSamplesAvail;

    nSamplesAvail = dspc_asrc_input_avail(&USB_ASRC);

    if (nSamplesAvail >= USB_PLAYBACK_BLOCKSIZE)
    {
        // Insert 48 stereo samples that just arrived over USB into the ASRC jitter buffer
        dspc_asrc_write_input_Q15(&USB_ASRC, USBBuffer, USB_PLAYBACK_BLOCKSIZE);
    }

    // Manually clear software interrupt
    NVIC_ClearPendingIRQ(ProcessWriteASRC_IRQ);

}   // End ProcessWriteASRC_IRQHandler


//-----------------------------------------------------------------------------
// METHOD:  I2S3_DMA_Complete_CallBack
// PURPOSE: DMA interrupt complete for the CODEC
//-----------------------------------------------------------------------------
void I2S3_DMA_Complete_CallBack(void)
{
    int nSamplesAvail;
    fract16 * pUSBSamples;
    INT32 layoutMask;

    INT32 bAudioIsStarted;
    INT32 bLayoutValid;

    static INT32 nI2SBufferNdx = 0;
    static INT32 nPCMBufferNdx = 0;

    // Default to zeros
    pUSBSamples = ZeroedSamples;

    if (g_bPlaying)
    {
        // Get the number of available USB samples in the ASRC jitter buffer
        nSamplesAvail = dspc_asrc_output_avail(&USB_ASRC);

        if (nSamplesAvail >= CODEC_OUTPUT_BLOCKSIZE)
        {
            // Read a block of samples from the ASRC jitter buffer
            dspc_asrc_read_output_linear_Q15(&USB_ASRC, USB_ASRCSamples, CODEC_OUTPUT_BLOCKSIZE);

            pUSBSamples = USB_ASRCSamples;
        }
    }

	bAudioIsStarted = awe_audioIsStarted(&g_AWEInstance);
    bLayoutValid = awe_layoutIsValid(&g_AWEInstance);

	// If no audio processing running
    if (!bAudioIsStarted)
    {
        memset(I2SBuffer, 0, sizeof(I2SBuffer) );
    }
    else if (!bLayoutValid)
    {
        memcpy(&I2SBuffer[nI2SBufferNdx], pUSBSamples, STEREO_BLOCK_SIZE_IN_SAMPLES * PCM_SIZE_IN_BYTES);
    }
    else
    {
        // Insert the received USB samples into the AudioWeaver buffer
        awe_audioImportSamples(&g_AWEInstance, pUSBSamples, STRIDE2, CHANNEL1, Sample16bit);
        awe_audioImportSamples(&g_AWEInstance, &pUSBSamples[1], STRIDE2, CHANNEL2, Sample16bit);

        // Insert the received Mic samples into the Audio Weaver buffer
        awe_audioImportSamples(&g_AWEInstance, &PCMBuffer[nPCMBufferNdx], STRIDE1, CHANNEL3, Sample16bit);

        // Insert the processed Audio Weaver samples into the CODEC output buffer
        awe_audioExportSamples(&g_AWEInstance,  &I2SBuffer[nI2SBufferNdx], STRIDE2, CHANNEL1, Sample16bit);
        awe_audioExportSamples(&g_AWEInstance,  &I2SBuffer[nI2SBufferNdx + 1], STRIDE2, CHANNEL2, Sample16bit);

        layoutMask = awe_audioGetPumpMask(&g_AWEInstance);

        if (layoutMask > 0)
        {
            // If higher priority level processing ready pend an interrupt for it
            if (layoutMask & 1)
            {
                if (!g_bAudioPump1Active)
                {
                    NVIC_SetPendingIRQ(AudioWeaverPump_IRQ1);
                }
            }

            // If lower priority level processing ready pend an interrupt for it
            if (layoutMask & 2)
            {
                if (!g_bAudioPump2Active)
                {
                    NVIC_SetPendingIRQ(AudioWeaverPump_IRQ2);
                }
            }
        }
    }

    // CODEC double buffer
    nI2SBufferNdx = (nI2SBufferNdx + STEREO_BLOCK_SIZE_IN_SAMPLES) % CODEC_BUFFER_SIZE_IN_SAMPLES;
    nPCMBufferNdx = (nPCMBufferNdx + AUDIO_BLOCK_SIZE) % PCM_BUFFER_SIZE_IN_SAMPLES;

 }  // End I2S3_DMA_Complete_CallBack


//-----------------------------------------------------------------------------
// METHOD:  AudioWeaver Pump Interrupt Handler
// PURPOSE: Perform AudioWeaver Processing
//-----------------------------------------------------------------------------
void AudioWeaverPump_IRQHandler1(void)
{
    g_bAudioPump1Active = TRUE;

    // If IDLE loop did not get some CPU time then skip the pump
    // g_nPumpCount gets reset in the idle loop method awe_pltTick
    if (g_nPumpCount++ < MAX_PUMP_COUNT)
    {
        //awe_pltGPIOSetPin(33, 1);

        // Perform highest priority AWE processing
        g_bDeferredProcessingRequired |= awe_audioPump(&g_AWEInstance, 0);

        //awe_pltGPIOSetPin(33, 0);
    }

    g_bAudioPump1Active = FALSE;

    // Manually clear software interrupt
    NVIC_ClearPendingIRQ(AudioWeaverPump_IRQ1);

}   // End AudioWeaverPump_IRQHandler1


//-----------------------------------------------------------------------------
// METHOD:  AudioWeaver Pump Interrupt Handler
// PURPOSE: Perform AudioWeaver Processing
//-----------------------------------------------------------------------------
void AudioWeaverPump_IRQHandler2(void)
{
    g_bAudioPump2Active = TRUE;

    // Perform medium priority AWE processing (FFT, etc)
    g_bDeferredProcessingRequired |= awe_audioPump(&g_AWEInstance, 1);

    g_bAudioPump2Active = FALSE;

    // Manually clear software interrupt
    NVIC_ClearPendingIRQ(AudioWeaverPump_IRQ2);

}   // End AudioWeaverPump_IRQHandler2

