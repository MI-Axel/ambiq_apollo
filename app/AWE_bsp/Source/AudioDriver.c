/*******************************************************************************
*
*               Audio Framework
*               ---------------
*
********************************************************************************
*     AudioDriver.c
********************************************************************************
*
*     Description:  AudioWeaver Driver
*
*
*
*******************************************************************************/

#include "Errors.h"
#include "Framework.h"
#include "Platform.h"

// apollo mcu include
#include "am_mcu_apollo.h"


//*****************************************************************************
//
// PDM interrupt handler.
//
//*****************************************************************************
void am_pdm_isr(void) 
{
    uint32_t ui32Status;
    //
    // Read the interrupt status.
    //
    am_hal_pdm_interrupt_status_get(PDMHandle, &ui32Status, true);
    am_hal_pdm_interrupt_clear(PDMHandle, ui32Status);
    
    if (ui32Status & AM_HAL_PDM_INT_DCMP)
    {
        // trigger next traction
        PDMn(0)->DMATOTCOUNT = AWE_FRAME_SIZE * 4;  // FIFO unit in bytes
        AWEProcessing(g_pi32PCMDataBuff);
//        am_util_debug_printf("PDM DCMP interrupt, pick g_ui32PDMDataBuffer[5] = 0x%8x\n", g_ui32PDMDataBuffer[5]);
    }
    else if(ui32Status & (AM_HAL_PDM_INT_UNDFL | AM_HAL_PDM_INT_OVF))
    {
        am_hal_pdm_fifo_flush(PDMHandle);
    }

}

//-----------------------------------------------------------------------------
// METHOD:  AWEProcessing
// PURPOSE: Pass new samples to Audio Weaver for processing
//-----------------------------------------------------------------------------
void AWEProcessing(INT32 *nLRSample)
{
    uint32_t  fwInCount, fwOutCount;
    uint32_t  chan;
    int32_t   pinStride;
    uint32_t  layoutMask;
    UINT32  nComplete;
    int32_t * dest32BitPtr, * destLeftChannel32BitPtr, * destRightChannel32BitPtr;
    fract32*  src32BitPtr;
    int32_t n32BitSample;
    int16_t n16BitSample;
    const uint32_t nPinNdx = 0;
    int32_t nSample;
    int16_t in16AudioStreamBuff[AWE_FRAME_SIZE];

    if (!in32AudioRunningFlag)
    {
        // Flush the PDM FIFO
#if defined (AM_PART_APOLLO3)
        am_hal_pdm_fifo_flush(PDMHandle);
#else
        am_hal_pdm_fifo_flush();
#endif //#if defined (AM_PART_APOLLO3)
    }
    else
    {
        nComplete = 0;

        // Get Current AWE layout number of channels
        awe_fwGetChannelCount(&g_AWEInstance, &fwInCount, &fwOutCount);

        if(fwInCount > 0)
        {
            if (fwInCount >= 1)
                destLeftChannel32BitPtr = awe_fwGetInputChannelPtr(&g_AWEInstance, nPinNdx, 0, &pinStride);

            if (fwInCount >= 2)
                destRightChannel32BitPtr = awe_fwGetInputChannelPtr(&g_AWEInstance, nPinNdx, 1, &pinStride);

            for (nSample = 0; nSample < AWE_FRAME_SIZE; nSample++)
            {

                if(fwInCount >= 1)
                {
                    *destLeftChannel32BitPtr = nLRSample[nSample] << 16;
                    destLeftChannel32BitPtr += pinStride;
                }

                if (fwInCount >= 2)
                {
                    *destRightChannel32BitPtr = nLRSample[nSample] & 0xFFFF0000;
                    destRightChannel32BitPtr += pinStride;
                }
            }

            // Zero any non-HW AWE layout inputs
            for (chan = 2; chan < fwInCount; chan++)
            {
                // Determine where the Framework wants the input data written
                dest32BitPtr = awe_fwGetInputChannelPtr(&g_AWEInstance, nPinNdx, chan, &pinStride);

                for (nSample = 0; nSample < AWE_FRAME_SIZE; nSample++)
                {
                    *dest32BitPtr = 0;
                    dest32BitPtr += pinStride;
                }
            }
        }

        for (chan = 0; chan < OUTPUT_CHANNEL_COUNT; chan++)
        {
            if (chan < fwOutCount)
            {
                // Determine where the Framework wants the Output data written
                src32BitPtr = (fract32 *)awe_fwGetOutputChannelPtr(&g_AWEInstance, nPinNdx, chan, &pinStride);
                for (nSample = 0; nSample < AWE_FRAME_SIZE; nSample++)
                {
                    n32BitSample = *src32BitPtr;

                    // Not using SPI, so must be using UART or BLE.. both operate on single bytes`
                    // Audio Weaver has sample in high order bytes of 32-bit word
                    n16BitSample = n32BitSample >> 16;
                        
                    in16AudioStreamBuff[nSample] = n16BitSample;

                    src32BitPtr += pinStride;
                }
#if(configUSE_RTT_RECORDER && configUSE_RECORD_FULL_FILTER)
                    //
                    // Record the raw PCM data and send over RTT
                    //
                    if(g_ui8RTTStartFlag == 1)
                        am_app_KWD_rtt_record((void*)in16AudioStreamBuff, AWE_FRAME_SIZE*2); 
#endif //                 
            }
        }

        nComplete |= awe_fwAudioDMAComplete(&g_AWEInstance, nPinNdx, AWE_FRAME_SIZE);

        if (nComplete)
        {
            layoutMask = awe_fwEvalLayoutMask(&g_AWEInstance, NULL);
    
            if(layoutMask & 1)
            {
              if (!g_bAudioPump1Active)
              {
                g_bAudioPump1Active = TRUE;
    
                // If IDLE loop did not get some CPU time then skip the pump
                // g_nPumpCount gets reset in the idle loop method awe_pltTick
                awe_fwPump(&g_AWEInstance, 0);
                g_bAudioPump1Active = FALSE;
        //      am_hal_interrupt_pend_set(AM_HAL_INTERRUPT_SOFTWARE1);
              }
            }
    
            // If lower priority level processing ready pend an interrupt for it
            if (layoutMask & 2)
            {
              if (!g_bAudioPump2Active)
              {
         
                g_bAudioPump2Active = TRUE;
                
        //        am_app_utils_task_send(AM_APP_TASK_AUD_PROCESSING, AM_APP_TASK_MODEL_INFERENCE,
        //                                AM_APP_MESSAGE_SHORT, EMPTY_MESSAGE, NULL);
                // Fire the layout at user interrupt level
        //        awe_fwPump(&g_AWEInstance, 1);
    
        //        g_bAudioPump2Active = FALSE;
        //       am_hal_interrupt_pend_set(AM_HAL_INTERRUPT_SOFTWARE2);
              }
            }
        }

    // When this higher level priority method returns, processing will resume
    // with AudioWeaverPump_IRQ1 or AudioWeaverPump_IRQ2 if triggered.
    // If both were triggered then processing for AudioWeaverPump_IRQ2 will start
    // only when the processing for AudioWeaverPump_IRQ1 has completed
    }
}
#if defined (AM_PART_APOLLO3)
void
am_uart_isr(void)
{
    uint32_t ui32Status, ui32Idle;
    am_hal_uart_interrupt_status_get(g_sCOMUART, &ui32Status, true);
    am_hal_uart_interrupt_clear(g_sCOMUART, ui32Status);
    am_hal_uart_interrupt_service(g_sCOMUART, ui32Status, &ui32Idle);
    if (ui32Status & (AM_HAL_UART_INT_RX_TMOUT | AM_HAL_UART_INT_RX))
    {
        g_bUARTPacketReceived = TRUE;
    }
}
#endif // #if defined (AM_PART_APOLLO3)
//-----------------------------------------------------------------------------
// METHOD:  AudioWeaver Pump Interrupt Handler
// PURPOSE: Perform AudioWeaver Processing
//-----------------------------------------------------------------------------
//AWE_OPTIMIZE_FOR_SPEED
//AWE_FW_FAST_CODE
//void AudioWeaverPump_IRQHandler1(void)
//{
//    g_bAudioPump1Active = TRUE;
//    // If IDLE loop did not get some CPU time then skip the pump
//    // g_nPumpCount gets reset in the idle loop method awe_pltTick
//    if (g_nPumpCount < MAX_PUMP_COUNT)
//    {
//        awe_fwPump(&g_AWEInstance, 0);
//        g_nPumpCount++;
//    }
//    g_bAudioPump1Active = FALSE;
//    // Manually clear software interrupt
//    am_hal_interrupt_pend_clear(AM_HAL_INTERRUPT_SOFTWARE1);
//} // End RenderAudio
//-----------------------------------------------------------------------------
// METHOD:  AudioWeaver Pump Interrupt Handler
// PURPOSE: Perform AudioWeaver Processing
//-----------------------------------------------------------------------------
//AWE_OPTIMIZE_FOR_SPEED
//AWE_FW_FAST_CODE
//void AudioWeaverPump_IRQHandler2(void)
//{
//    g_bAudioPump2Active = TRUE;
//    // Fire the layout at user interrupt level
//    awe_fwPump(&g_AWEInstance, 1);
//    g_bAudioPump2Active = FALSE;
//    // Manually clear software interrupt
//    am_hal_interrupt_pend_clear(AM_HAL_INTERRUPT_SOFTWARE2);
//} // End RenderAudio
