/* This file is the driver of PDM functions*/

/* AEP config header file */ 
#include "am_audio_platform_config.h"

#include "audio_driver.h"
#include "board_setup.h"
#if configUSE_SYSVIEW
#include "SEGGER_SYSVIEW.h"
#endif

#if AM_AEP_MIKRO_CALIBRATION
#include "am_mikro_calibration.h"
#endif // AM_AEP_MIKRO_CALIBRATION

/* application layer utils header file */
#include "am_app_utils_ring_buffer.h"
#if configUSE_RTT_DATA_OUTPUT
#include "am_app_utils_rtt_recorder.h"
#endif

//*****************************************************************************
// GLOBALS
//*****************************************************************************

volatile int32_t g_DebugValue = 0;
volatile bool g_bPDMDataReady = false;
volatile uint32_t 
            g_ui32PCMDataBuff[PCM_FRAME_SIZE];  // Location of 1-second data buffer

volatile bool g_audioRunningFlag = 0;    

//*****************************************************************************
// PDM configuration information.
//*****************************************************************************
void* PDMHandle;



//*****************************************************************************
// PDM initialization.
//*****************************************************************************
void am_app_AEP_pdm_init(void) 
{
  //
  // Configure the necessary pins.
  //
  am_hal_gpio_pincfg_t sPinCfg = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  // ARPIT 181019
  // sPinCfg.uFuncSel = AM_HAL_PIN_10_PDMCLK;
  // am_hal_gpio_pinconfig(10, sPinCfg);
  sPinCfg.uFuncSel = AM_HAL_PIN_12_PDMCLK;
  am_hal_gpio_pinconfig(12, sPinCfg);

  sPinCfg.uFuncSel = AM_HAL_PIN_11_PDMDATA;
  am_hal_gpio_pinconfig(11, sPinCfg);


    am_hal_pdm_config_t g_sPdmConfig = {
        .eClkDivider = AM_HAL_PDM_MCLKDIV_1,
        .eLeftGain = AM_HAL_PDM_GAIN_P105DB,
        .eRightGain = AM_HAL_PDM_GAIN_P105DB,
        .ui32DecimationRate =
            24,  // OSR = 1500/16 = 96 = 2*SINCRATE --> SINC_RATE = 48
        .bHighPassEnable = 0, // Enable high-pass filter
        .ui32HighPassCutoff = 0x4, // high-pass filter register value
        .ePDMClkSpeed = AM_HAL_PDM_CLK_750KHZ,
        .bInvertI2SBCLK = 0,
        .ePDMClkSource = AM_HAL_PDM_INTERNAL_CLK,
        .bPDMSampleDelay = 0,
        .bDataPacking = 1,
        .ePCMChannels = AM_HAL_PDM_CHANNEL_STEREO,
        .bLRSwap = 1,
    };
    
//
  // Initialize, power-up, and configure the PDM.
  //
    am_hal_pdm_initialize(0, &PDMHandle);
    am_hal_pdm_power_control(PDMHandle, AM_HAL_PDM_POWER_ON, false);
    am_hal_pdm_configure(PDMHandle, &g_sPdmConfig);
    am_hal_pdm_fifo_flush(PDMHandle);


  am_hal_pdm_enable(PDMHandle);


  //
  // Configure and enable PDM interrupts (set up to trigger on DMA
  // completion).
  //
  am_hal_pdm_interrupt_enable(PDMHandle,
                              (AM_HAL_PDM_INT_DERR | AM_HAL_PDM_INT_DCMP |
                               AM_HAL_PDM_INT_UNDFL | AM_HAL_PDM_INT_OVF));

#if AM_CMSIS_REGS
    NVIC_SetPriority(PDM_IRQn, 4);
    NVIC_EnableIRQ(PDM_IRQn);
#else
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_PDM);
#endif


    //
    // Enable PDM
    //
    am_hal_pdm_enable(PDMHandle);
    pdm_trigger_dma();

}

//*****************************************************************************
//
// Start a transaction to get some number of bytes from the PDM interface.
//
//*****************************************************************************
//void pdm_data_get(void) 
//{
  //
  // Configure DMA and target address.
  //
//  am_hal_pdm_transfer_t sTransfer;
//  sTransfer.ui32TargetAddr =
//      (uint32_t)(&captured_data[FRAME_SIZE * g_numFramesCaptured]);
//  sTransfer.ui32TotalCount = 4 * FRAME_SIZE;  // Each sample is 2 bytes

  //
  // Start the data transfer.
  //
//  am_hal_pdm_dma_start(PDMHandle, &sTransfer);
//}
void pdm_trigger_dma(void)
{
    //
    // Configure DMA and target address.
    //
    am_hal_pdm_transfer_t sTransfer;
    sTransfer.ui32TargetAddr = (uint32_t ) g_ui32PCMDataBuff;
    sTransfer.ui32TotalCount = (PCM_FRAME_SIZE * PCM_DATA_BYTES);

    //
    // Start the data transfer.
    //
    am_hal_pdm_dma_start(PDMHandle, &sTransfer);
}

//*****************************************************************************
//
// PDM interrupt handler.
//
//*****************************************************************************
void am_pdm0_isr(void) 
{
#if configUSE_SYSVIEW    
    SEGGER_SYSVIEW_RecordEnterISR();
#endif
    uint32_t ui32Status;
    //
    // Read the interrupt status.
    //
    am_hal_pdm_interrupt_status_get(PDMHandle, &ui32Status, true);
    am_hal_pdm_interrupt_clear(PDMHandle, ui32Status);
    
    if (ui32Status & AM_HAL_PDM_INT_DCMP)
    {
        // trigger next traction
        PDMn(0)->DMATOTCOUNT = PCM_FRAME_SIZE*PCM_DATA_BYTES;  // FIFO unit in bytes
        
        if((g_ui8MicCalFlag == 1) && (g_ui8PcmDataReadyFlag==0))
        {
            am_app_utils_ring_buffer_push(&am_sys_ring_buffers[AM_APP_RINGBUFF_PCM], (void*)g_ui32PCMDataBuff, PCM_FRAME_SIZE*PCM_DATA_BYTES);
            g_ui32SampleNum += PCM_FRAME_SIZE;
            if(g_ui32SampleNum >= g_ui32WindowLen)
            {
                g_ui8PcmDataReadyFlag = 1;
            }
        }

#if configUSE_RTT_DATA_OUTPUT
        //
        // Record the raw PCM data and send over RTT
        //
//        if(g_rttRecordingFlag == 1)
//            am_app_utils_rtt_record((void*)g_ui32PCMDataBuff, PCM_FRAME_SIZE*PCM_DATA_BYTES); 
#endif /* USE_RTT_DATA_OUTPUT */ 

//        am_util_debug_printf("PDM DCMP interrupt, pick g_ui32PDMDataBuffer[5] = 0x%8x\n", g_ui32PDMDataBuffer[5]);
    }
    else if(ui32Status & (AM_HAL_PDM_INT_UNDFL | AM_HAL_PDM_INT_OVF))
    {
        am_hal_pdm_fifo_flush(PDMHandle);
    }

#if configUSE_SYSVIEW
    SEGGER_SYSVIEW_RecordExitISR(); //emit Exit ISR signal
#endif

}


