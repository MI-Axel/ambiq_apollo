
/* This file is the setup code of ap3blue evb for the microphone verification project. */
/* AEP config header file */ 
#include "am_app_mic_verif_config.h"

#include "am_app_mic_verif_board_setup.h"
#include "am_app_mic_verif_isr.h"

#if AM_APP_MIC_CALIBRATION
#include "am_mikro_calibration.h"
#endif // AM_APP_MIC_CALIBRATION

#if AM_APP_MIC_THD
#include "am_mikro_thd.h"
#endif // AM_APP_MIC_THD

/* application utils header files */
#include "am_app_utils_ring_buffer.h"

//*****************************************************************************
//
// Globals
//
//*****************************************************************************
volatile uint32_t g_ui32TimerCount = 0;

volatile uint8_t g_ui8DebounceFlag = 0;

volatile uint32_t g_ui32DebounceTimerCount = 0;

volatile  am_app_AEP_key_value_enum_t g_sysKeyValue = AM_APP_KEY_NONE;

volatile uint8_t g_ui8ButtonPushedFlag = 0;

volatile int32_t g_DebugValue = 0;

volatile bool g_bPDMDataReady = false;

volatile uint32_t g_ui32PCMDataBuff[PCM_FRAME_SIZE];  // Location of 1-second data buffer

volatile bool g_audioRunningFlag = 0;    

//******************************************************************************
//Global data buffers used by ring buffers
//*****************************************************************************
volatile uint8_t g_ui8PCMDataRingBuff[PCM_DATA_BYTES*AVERAGE_WINDOW_LENGTH];

am_app_utils_ring_buffer_t am_sys_ring_buffers[AM_APP_RINGBUFF_MAX];

static const am_app_utils_ringbuff_setup_t g_SysRingBuffSetup[] = 
{
    {AM_APP_RINGBUFF_PCM, g_ui8PCMDataRingBuff, AVERAGE_WINDOW_LENGTH*PCM_DATA_BYTES}
};
#define SYS_RINGBUFF_INIT_COUNT     (sizeof(g_SysRingBuffSetup)/sizeof(am_app_utils_ringbuff_setup_t))

//*****************************************************************************
// The stdio function for debug usage
//*****************************************************************************

void DebugLog(const char* s) { am_util_stdio_printf("%s", s); }
void DebugLogInt32(int32_t i) { am_util_stdio_printf("%d", i); }
void DebugLogUInt32(uint32_t i) { am_util_stdio_printf("%d", i); }
void DebugLogHex(uint32_t i) { am_util_stdio_printf("0x%8x", i); }
void DebugLogFloat(float i) { am_util_stdio_printf("%f", i); }
//*****************************************************************************
// BUTTON pins configuration settings.
//*****************************************************************************
const am_hal_gpio_pincfg_t g_switch_button0 = {
    .uFuncSel = 3,
    .eIntDir = AM_HAL_GPIO_PIN_INTDIR_LO2HI,
    .eGPInput = AM_HAL_GPIO_PIN_INPUT_ENABLE,
};

const am_hal_gpio_pincfg_t g_switch_button1 = {
    .uFuncSel = 3,
    .eIntDir = AM_HAL_GPIO_PIN_INTDIR_LO2HI,
    .eGPInput = AM_HAL_GPIO_PIN_INPUT_ENABLE,
};

const am_hal_gpio_pincfg_t g_switch_button2 = {
    .uFuncSel = 3,
    .eIntDir = AM_HAL_GPIO_PIN_INTDIR_LO2HI,
    .eGPInput = AM_HAL_GPIO_PIN_INPUT_ENABLE,
};

//**************************************
// Timer configuration.
//**************************************
am_hal_ctimer_config_t g_sTimer0 =
{
    // Don't link timers.
    0,

    // Set up Timer0A.
    (AM_HAL_CTIMER_FN_REPEAT    |
     AM_HAL_CTIMER_INT_ENABLE   |
//    AM_HAL_CTIMER_XT_32_768KHZ),
    AM_HAL_CTIMER_HFRC_12MHZ), 
    // No configuration for Timer0B.
    0,
};

//**************************************
// Burst mode configuration.
//**************************************
am_hal_burst_avail_e          eBurstModeAvailable;
am_hal_burst_mode_e           eBurstMode;

//*****************************************************************************
//
// Function to initialize Timer A0 to interrupt every 1/4 second.
//
//*****************************************************************************
void
timerA0_init(void)
{
    uint32_t ui32Period;

    //
    // Enable the LFRC.
    //
    am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_XTAL_START, 0);
    

    //
    // Set up timer A0.
    //
    am_hal_ctimer_clear(0, AM_HAL_CTIMER_TIMERA);
    am_hal_ctimer_config(0, &g_sTimer0);

    //
    // Set up timerA0 to 32Hz from LFRC divided to 1 second period.
    //
    ui32Period = 12000;
    am_hal_ctimer_period_set(0, AM_HAL_CTIMER_TIMERA, ui32Period,
                             (ui32Period >> 1));

    //
    // Clear the timer Interrupt
    //
    am_hal_ctimer_int_clear(AM_HAL_CTIMER_INT_TIMERA0);
}

//*****************************************************************************
// PDM configuration information.
//*****************************************************************************
void* PDMHandle;

//*****************************************************************************
// PDM initialization.
//*****************************************************************************
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

void am_app_mic_verif_pdm_init(void) 
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
        .eClkDivider = AM_HAL_PDM_MCLKDIV_1,                            // PDM clock divider
        .eLeftGain = AM_HAL_PDM_GAIN_P105DB,                            // Left channel PCM data gain 
        .eRightGain = AM_HAL_PDM_GAIN_P105DB,                           // Right channel PCM data gain
        .ui32DecimationRate = 24,                                       // OSR = 1500/16 = 96 = 2*SINCRATE --> SINC_RATE = 48
        .bHighPassEnable = 0,                                           // Enable high-pass filter
        .ui32HighPassCutoff = 0x8,                                      // high-pass filter register value
        .ePDMClkSpeed = AM_HAL_PDM_CLK_750KHZ,                          // PDM clock frequency 
        .bInvertI2SBCLK = 0,                                            
        .ePDMClkSource = AM_HAL_PDM_INTERNAL_CLK,                       // PDM clock source selection
        .bPDMSampleDelay = 0,                                           // PDM delayed samples number
        .bDataPacking = 1,                                              // make PCM data packed
        .ePCMChannels = AM_HAL_PDM_CHANNEL_STEREO,                      // using 2 channels: right and left
        .bLRSwap = 0,                                                   // not swap the left and right channel data 
    };
    
//
  // Initialize, power-up, and configure the PDM.
  //
    am_hal_pdm_initialize(0, &PDMHandle);
    am_hal_pdm_power_control(PDMHandle, AM_HAL_PDM_POWER_ON, false);
    am_hal_pdm_configure(PDMHandle, &g_sPdmConfig);
    am_hal_pdm_fifo_flush(PDMHandle);

    am_util_stdio_printf("PDM Settings:\r\n");
    am_util_stdio_printf("PDM Clock (Hz):         %12d\r\n", 750000);
    am_util_stdio_printf("Effective Sample Freq.: %12d\r\n\n", 16000);

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
// Function to initialize Timer A0 to interrupt every 1/4 second.
//
//*****************************************************************************
void am_app_mic_verif_sys_init(void)
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
    am_hal_gpio_pinconfig(AM_BSP_GPIO_BUTTON0, g_switch_button0);
    am_hal_gpio_pinconfig(AM_BSP_GPIO_BUTTON1, g_switch_button1);
    am_hal_gpio_pinconfig(AM_BSP_GPIO_BUTTON2, g_switch_button2);
    //
    // Clear the GPIO Interrupt (write to clear).
    //
    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON0));
    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON1));
    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON2));
    //
    // Enable the GPIO/button interrupt.
    //
    am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON0));
    am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON1));
    am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON2));
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
    //
    // TimerA0 init.
    //
    timerA0_init();

    //
    // Enable the timer Interrupt.
    //
    am_hal_ctimer_int_enable(AM_HAL_CTIMER_INT_TIMERA0);

#endif  // defined(AM_BSP_NUM_BUTTONS)  &&  defined(AM_BSP_NUM_LEDS)
 
#if AM_CMSIS_REGS
    NVIC_EnableIRQ(GPIO_IRQn);
    NVIC_EnableIRQ(CTIMER_IRQn);
#else   // AM_CMSIS_REGS
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_GPIO);
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_CTIMER);
#endif  // AM_CMSIS_REGS

    //
    // Enable interrupts to the core.
    //
    am_hal_interrupt_master_enable();
   
    //
    // Initialize the printf interface for UART output
    //
    am_bsp_uart_printf_enable();

    //
    // Configure and enable burst mode
    //
    if (AM_HAL_STATUS_SUCCESS == am_hal_burst_mode_initialize(&eBurstModeAvailable))
    {
        if (AM_HAL_BURST_AVAIL == eBurstModeAvailable)
        {
            // Put the MCU into "Burst" mode.
            if (AM_HAL_STATUS_SUCCESS == am_hal_burst_mode_enable(&eBurstMode))
            {
                if (AM_HAL_BURST_MODE == eBurstMode)
                {
                    am_util_stdio_printf("Apollo3 operating in Burst Mode (96MHz)\r\n\n");
                }
            }

        }
    }

    // Turn on PDM
    am_app_mic_verif_pdm_init();

    am_hal_ctimer_start(0, AM_HAL_CTIMER_TIMERA);

    am_app_utils_ring_buffer_init_all(am_sys_ring_buffers, g_SysRingBuffSetup, SYS_RINGBUFF_INIT_COUNT);

}


