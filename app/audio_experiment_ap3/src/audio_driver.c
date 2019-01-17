/* This file is the driver of PDM functions*/

#include "audio_driver.h"

//*****************************************************************************
// GLOBALS
//*****************************************************************************

volatile int16_t g_numFramesCaptured = 0;
volatile bool g_bPDMDataReady = false;
uint32_t
    captured_data[FRAME_SIZE * NUM_FRAMES];  // Location of 1-second data buffer

volatile bool g_audioRunningFlag = 0;    

//*****************************************************************************
// PDM configuration information.
//*****************************************************************************
void* PDMHandle;

am_hal_pdm_config_t g_sPdmConfig = {
    .eClkDivider = AM_HAL_PDM_MCLKDIV_1,
    .eLeftGain = AM_HAL_PDM_GAIN_P225DB,
    .eRightGain = AM_HAL_PDM_GAIN_P225DB,
    .ui32DecimationRate =
        48,  // OSR = 1500/16 = 96 = 2*SINCRATE --> SINC_RATE = 48
    .bHighPassEnable = 0,
    .ui32HighPassCutoff = 0xB,
    .ePDMClkSpeed = AM_HAL_PDM_CLK_1_5MHZ,
    .bInvertI2SBCLK = 0,
    .ePDMClkSource = AM_HAL_PDM_INTERNAL_CLK,
    .bPDMSampleDelay = 0,
    .bDataPacking = 1,
    .ePCMChannels = AM_HAL_PDM_CHANNEL_STEREO,
    .bLRSwap = 0,
};

//*****************************************************************************
// PDM initialization.
//*****************************************************************************
void pdm_init(void) 
{
  //
  // Initialize, power-up, and configure the PDM.
  //
  am_hal_pdm_initialize(0, &PDMHandle);
  am_hal_pdm_power_control(PDMHandle, AM_HAL_PDM_POWER_ON, false);
  am_hal_pdm_configure(PDMHandle, &g_sPdmConfig);
  am_hal_pdm_enable(PDMHandle);

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

  // am_hal_gpio_state_write(14, AM_HAL_GPIO_OUTPUT_CLEAR);
  // am_hal_gpio_pinconfig(14, g_AM_HAL_GPIO_OUTPUT);

  //
  // Configure and enable PDM interrupts (set up to trigger on DMA
  // completion).
  //
  am_hal_pdm_interrupt_enable(PDMHandle,
                              (AM_HAL_PDM_INT_DERR | AM_HAL_PDM_INT_DCMP |
                               AM_HAL_PDM_INT_UNDFL | AM_HAL_PDM_INT_OVF));

#if AM_CMSIS_REGS
  NVIC_EnableIRQ(PDM_IRQn);
#else
  am_hal_interrupt_enable(AM_HAL_INTERRUPT_PDM);
#endif
}

//*****************************************************************************
//
// Start a transaction to get some number of bytes from the PDM interface.
//
//*****************************************************************************
void pdm_data_get(void) 
{
  //
  // Configure DMA and target address.
  //
  am_hal_pdm_transfer_t sTransfer;
  sTransfer.ui32TargetAddr =
      (uint32_t)(&captured_data[FRAME_SIZE * g_numFramesCaptured]);
  sTransfer.ui32TotalCount = 4 * FRAME_SIZE;  // Each sample is 2 bytes

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
void am_pdm_isr(void) 
{
  uint32_t ui32Status;
  //
  // Read the interrupt status.
  //
  am_hal_pdm_interrupt_status_get(PDMHandle, &ui32Status, true);
  am_hal_pdm_interrupt_clear(PDMHandle, ui32Status);

  //
  // Once our DMA transaction completes, send a flag to the main routine
  //
  if (ui32Status & AM_HAL_PDM_INT_DCMP) g_bPDMDataReady = true;
}


