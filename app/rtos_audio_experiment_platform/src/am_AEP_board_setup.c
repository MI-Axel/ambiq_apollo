
/* This file is the seyup code of ap3blue evb for the audio experiment platform. */
#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_devices.h"
#include "am_util.h"

#include "am_AEP_config.h"
#include "am_AEP_board_setup.h"

//*****************************************************************************
// BUTTON pins configuration settings.
//*****************************************************************************
const am_hal_gpio_pincfg_t g_AP3EVB_button0 = {
    .uFuncSel       = 3, // GPIO
    .eGPOutcfg      = AM_HAL_GPIO_PIN_OUTCFG_DISABLE,
    .eGPInput       = AM_HAL_GPIO_PIN_INPUT_ENABLE,
    .eGPRdZero      = AM_HAL_GPIO_PIN_RDZERO_READPIN,
    .eIntDir        = AM_HAL_GPIO_PIN_INTDIR_HI2LO,
    .ePullup        = AM_HAL_GPIO_PIN_PULLUP_WEAK

};

//**************************************
// Burst mode configuration.
//**************************************
am_hal_burst_avail_e          eBurstModeAvailable;
am_hal_burst_mode_e           eBurstMode;

#if configUSE_PDM_DATA
//*****************************************************************************
// PDM configuration information.
//*****************************************************************************
void* PDMHandle;
uint32_t g_ui32PCMDataBuff[PCM_FRAME_SIZE];

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

void am_AEP_pdm_init(void) 
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
        .bHighPassEnable = 1,
        .ui32HighPassCutoff = 0xB,
        .ePDMClkSpeed = AM_HAL_PDM_CLK_750KHZ,
        .bInvertI2SBCLK = 0,
        .ePDMClkSource = AM_HAL_PDM_INTERNAL_CLK,
        .bPDMSampleDelay = 0,
        .bDataPacking = 1,
        .ePCMChannels = AM_HAL_PDM_CHANNEL_STEREO,
        .bLRSwap = 0,
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


#endif // configUSE_PDM_DATA

//*****************************************************************************
//
// Function to initialize Timer A0 to interrupt every 1/4 second.
//
//*****************************************************************************
void am_AEP_board_setup(void)
{
    //
    // Set the clock frequency.
    //
    am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_SYSCLK_MAX, 0);
    
    //
    // Set the default cache configuration
    //
    am_hal_cachectrl_config(&am_hal_cachectrl_defaults);
    am_hal_cachectrl_enable();
    
    //
    // Configure the board for low power operation.
    //
    am_bsp_low_power_init();



#if defined(AM_BSP_NUM_BUTTONS) && defined(AM_BSP_NUM_LEDS)
    //
    // Configure the button pin.
    //
    am_hal_gpio_pinconfig(AM_BSP_GPIO_BUTTON0, g_AP3EVB_button0);
    
    //
    // Clear the GPIO Interrupt (write to clear).
    //
    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON0));
    
    //
    // Enable the GPIO/button interrupt.
    //
//    am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON0));
    
    //
    // Configure the LEDs.
    //
    am_devices_led_array_init(am_bsp_psLEDs, AM_BSP_NUM_LEDS);
    
    //
    // Turn the LEDs off
    //
    for (int ix = 0; ix < AM_BSP_NUM_LEDS; ix++) 
    {
        am_devices_led_off(am_bsp_psLEDs, ix);
    }

#endif  // defined(AM_BSP_NUM_BUTTONS)  &&  defined(AM_BSP_NUM_LEDS)

#if configUSE_PDM_DATA
    // Turn on PDM
    am_AEP_pdm_init();
#endif // configUSE_PDM_DATA


#if AM_CMSIS_REGS
//    NVIC_SetPriority(GPIO_IRQn, 4);     // if you want to use API in this isr, you can't set higher than 4.
//    NVIC_EnableIRQ(GPIO_IRQn);
#else   // AM_CMSIS_REGS
//    am_hal_interrupt_enable(AM_HAL_INTERRUPT_GPIO);
#endif  // AM_CMSIS_REGS

    
    //
    // Initialize the printf interface for UART output
    //
    am_bsp_uart_printf_enable();

    //
    // Configure of burst mode
    //
    if (AM_HAL_STATUS_SUCCESS == am_hal_burst_mode_initialize(&eBurstModeAvailable))
    {
        if (AM_HAL_BURST_AVAIL == eBurstModeAvailable)
        {
//            am_util_stdio_printf("Apollo3 Burst Mode is Available\r\n");
        }
        else
        {
//            am_util_stdio_printf("Apollo3 Burst Mode is Not Available\r\n");
        }
    }
    else
    {
//        am_util_stdio_printf("Failed to Initialize for Burst Mode operation\r\n");
    }

#if configUSE_BURST_ALWAYS_ON
    // Put the MCU into "Burst" mode.
    if (AM_HAL_STATUS_SUCCESS == am_hal_burst_mode_enable(&eBurstMode))
    {
        if (AM_HAL_BURST_MODE == eBurstMode)
        {
//            am_util_stdio_printf("Apollo3 operating in Burst Mode (96MHz)\r\n");
        }
    }
    else
    {
//        am_util_stdio_printf("Failed to Enable Burst Mode operation\r\n");
    }

#endif // configUSE_BURST_ALWAYS_ON
   
    //
    // Enable interrupts to the core.
    //
    am_hal_interrupt_master_enable();

}


