
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

volatile bool g_audioRunningFlag = 0;    

volatile uint32_t g_ui32PCMDataSumBytes = 0;

//
// Target location of PDM DMA
//
volatile uint32_t g_ui32PCMDataBuff[PCM_FRAME_SIZE];


//******************************************************************************
//Global data buffers used by ring buffers
//*****************************************************************************
volatile uint8_t g_ui8PCMDataRingBuff[PCM_DATA_BYTES*AUDIO_DATA_LENGTH];

#if AM_APP_ANALOG_MIC

volatile uint8_t g_ui8AMicDataRingBuff[ANALOG_MIC_DATA_BYTES*AUDIO_DATA_LENGTH];

volatile uint32_t g_ui32AMicDataSumBytes = 0;

volatile bool g_bAMicDataReady = false;

volatile bool g_bAMicEvalFlag = false;

#endif // AM_APP_ANALOG_MIC


am_app_utils_ring_buffer_t am_sys_ring_buffers[AM_APP_RINGBUFF_MAX];

static const am_app_utils_ringbuff_setup_t g_SysRingBuffSetup[] = 
{
#if AM_APP_ANALOG_MIC
    {AM_APP_RINGBUFF_ANA, g_ui8AMicDataRingBuff, AUDIO_DATA_LENGTH*ANALOG_MIC_DATA_BYTES},
#endif // AM_APP_ANALOG_MIC

    {AM_APP_RINGBUFF_PCM, g_ui8PCMDataRingBuff, AUDIO_DATA_LENGTH*PCM_DATA_BYTES}
};
#define SYS_RINGBUFF_INIT_COUNT     (sizeof(g_SysRingBuffSetup)/sizeof(am_app_utils_ringbuff_setup_t))

//*****************************************************************************
// The stdio function for debug usage
//*****************************************************************************

void DebugLog(const char* s) { am_util_stdio_printf("%s", s); }
void DebugLogInt32(int32_t i) { am_util_stdio_printf("%d", i); }
void DebugLogUInt32(uint32_t i) { am_util_stdio_printf("%u", i); }
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
// PDM configuration information.
//*****************************************************************************
void* PDMHandle;

#if AM_APP_ANALOG_MIC
//
// ADC DMA target address
//
uint32_t g_ui32ADCSampleBuffer[ADC_SAMPLE_COUNT];

am_hal_adc_sample_t SampleBuffer[ADC_SAMPLE_COUNT];

//
// ADC Device Handle.
//
void *g_ADCHandle;

//
// ADC DMA complete flag.
//
volatile bool                   g_bADCDMAComplete;

//
// ADC DMA error flag.
//
volatile bool                   g_bADCDMAError;

//
// Define the ADC SE0 pin to be used.
//
const am_hal_gpio_pincfg_t g_AM_PIN_33_ADCSE5 =
{
    .uFuncSel       = AM_HAL_PIN_33_ADCSE5,
};

#endif // AM_APP_ANALOG_MIC

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


    //
    // Enable PDM
    //
    am_hal_pdm_enable(PDMHandle);
    pdm_trigger_dma();

}

//*****************************************************************************
//
// Configure the ADC.
//
//*****************************************************************************
void
adc_config_dma(void)
{
    am_hal_adc_dma_config_t       ADCDMAConfig;

    //
    // Configure the ADC to use DMA for the sample transfer.
    //
    ADCDMAConfig.bDynamicPriority = true;
    ADCDMAConfig.ePriority = AM_HAL_ADC_PRIOR_SERVICE_IMMED;
    ADCDMAConfig.bDMAEnable = true;
    ADCDMAConfig.ui32SampleCount = ADC_SAMPLE_COUNT;
    ADCDMAConfig.ui32TargetAddress = (uint32_t)g_ui32ADCSampleBuffer;
    if (AM_HAL_STATUS_SUCCESS != am_hal_adc_configure_dma(g_ADCHandle, &ADCDMAConfig))
    {
        am_util_stdio_printf("Error - configuring ADC DMA failed.\n");
    }

    //
    // Reset the ADC DMA flags.
    //
    g_bADCDMAComplete = false;
    g_bADCDMAError = false;
}


void adc_config(void)
{
    am_hal_adc_config_t           ADCConfig;
    am_hal_adc_slot_config_t      ADCSlotConfig;

    //
    // Initialize the ADC and get the handle.
    //
    if ( AM_HAL_STATUS_SUCCESS != am_hal_adc_initialize(0, &g_ADCHandle) )
    {
        am_util_stdio_printf("Error - reservation of the ADC instance failed.\n");
    }

    //
    // Power on the ADC.
    //
    if (AM_HAL_STATUS_SUCCESS != am_hal_adc_power_control(g_ADCHandle,
                                                          AM_HAL_SYSCTRL_WAKE,
                                                          false) )
    {
        am_util_stdio_printf("Error - ADC power on failed.\n");
    }

    //
    // Set up the ADC configuration parameters. These settings are reasonable
    // for accurate measurements at a low sample rate.
    //
    ADCConfig.eClock             = AM_HAL_ADC_CLKSEL_HFRC;
    ADCConfig.ePolarity          = AM_HAL_ADC_TRIGPOL_RISING;
    ADCConfig.eTrigger           = AM_HAL_ADC_TRIGSEL_SOFTWARE;
    ADCConfig.eReference         = AM_HAL_ADC_REFSEL_INT_2P0;
    ADCConfig.eClockMode         = AM_HAL_ADC_CLKMODE_LOW_LATENCY;
    ADCConfig.ePowerMode         = AM_HAL_ADC_LPMODE0;
    ADCConfig.eRepeat            = AM_HAL_ADC_REPEATING_SCAN;
    if (AM_HAL_STATUS_SUCCESS != am_hal_adc_configure(g_ADCHandle, &ADCConfig))
    {
        am_util_stdio_printf("Error - configuring ADC failed.\n");
    }
    //
    // Try to calibrate ADC. It seems useless...
    //
//    am_util_stdio_printf("Start ADC calibration...\r\n");
//    am_util_stdio_printf("ADCCAL reg value is originally %x ...\r\n", *(uint32_t*)0x4002010c);
//    *(uint32_t*)0x4002010c |= 0x00;
//    am_util_stdio_printf("ADC calibration is finished...\n\r");
    //
    // Set up an ADC slot
    //
    ADCSlotConfig.eMeasToAvg      = AM_HAL_ADC_SLOT_AVG_1;
    ADCSlotConfig.ePrecisionMode  = AM_HAL_ADC_SLOT_14BIT;
    ADCSlotConfig.eChannel        = AM_HAL_ADC_SLOT_CHSEL_SE5;
    ADCSlotConfig.bWindowCompare  = false;
    ADCSlotConfig.bEnabled        = true;
    if (AM_HAL_STATUS_SUCCESS != am_hal_adc_configure_slot(g_ADCHandle, 0, &ADCSlotConfig))
    {
        am_util_stdio_printf("Error - configuring ADC Slot 0 failed.\n");
    }
    //
    // Configure the ADC to use DMA for the sample transfer.
    //
    adc_config_dma();

    //
    // For this example, the samples will be coming in slowly. This means we
    // can afford to wake up for every conversion.
    //
    am_hal_adc_interrupt_enable(g_ADCHandle, AM_HAL_ADC_INT_DERR | AM_HAL_ADC_INT_DCMP );

    //
    // Enable the ADC.
    //
    if (AM_HAL_STATUS_SUCCESS != am_hal_adc_enable(g_ADCHandle))
    {
        am_util_stdio_printf("Error - enabling ADC failed.\n");
    }
}

//*****************************************************************************
//
// Configure the ADC.
//
//*****************************************************************************
void
adc_deconfig(void)
{
    //
    // Disable the ADC.
    //
    if (AM_HAL_STATUS_SUCCESS != am_hal_adc_disable(g_ADCHandle))
    {
        am_util_stdio_printf("Error - disable ADC failed.\n");
    }

    //
    // Enable the ADC power domain.
    //
    if (AM_HAL_STATUS_SUCCESS != am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_ADC))
    {
        am_util_stdio_printf("Error - disabling the ADC power domain failed.\n");
    }

    //
    // Initialize the ADC and get the handle.
    //
    if (AM_HAL_STATUS_SUCCESS != am_hal_adc_deinitialize(g_ADCHandle))
    {
        am_util_stdio_printf("Error - return of the ADC instance failed.\n");
    }

}

//*****************************************************************************
//
// Initialize the ADC repetitive sample timer A3.
//
//*****************************************************************************
void
init_timerA3_for_ADC(void)
{
    //
    // Start a timer to trigger the ADC periodically (16000HZ sample rate).
    //
    am_hal_ctimer_config_single(3, AM_HAL_CTIMER_TIMERA,
                                AM_HAL_CTIMER_HFRC_12MHZ    |
                                AM_HAL_CTIMER_FN_REPEAT     );

//    am_hal_ctimer_int_enable(AM_HAL_CTIMER_INT_TIMERA3);

    am_hal_ctimer_period_set(3, AM_HAL_CTIMER_TIMERA, 750, 375);

    //
    // Enable the timer A3 to trigger the ADC directly
    //
    am_hal_ctimer_adc_trigger_enable();

    //
    // Start the timer.
    //
    am_hal_ctimer_start(3, AM_HAL_CTIMER_TIMERA);
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
    if (AM_HAL_STATUS_SUCCESS != am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_SYSCLK_MAX, 0))
    {
        am_util_stdio_printf("Error - configuring the system clock failed.\n");
    }


    //
    // Set the default cache configuration and enable it.
    //
    if (AM_HAL_STATUS_SUCCESS != am_hal_cachectrl_config(&am_hal_cachectrl_defaults))
    {
        am_util_stdio_printf("Error - configuring the system cache failed.\n");
    }
    if (AM_HAL_STATUS_SUCCESS != am_hal_cachectrl_enable())
    {
        am_util_stdio_printf("Error - enabling the system cache failed.\n");
    }

    //
    // Configure the board for low power operation.
    //
    am_bsp_low_power_init();

    //
    // Initialize the printf interface for UART output
    //
#if configUSE_UART_PRINTF
    am_bsp_uart_printf_enable();
#elif configUSE_SWO_PRINTF // configUSE_UART_PRINTF
    am_bsp_itm_printf_enable();
#endif // configUSE_UART_PRINTF


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

#endif  // defined(AM_BSP_NUM_BUTTONS)  &&  defined(AM_BSP_NUM_LEDS)
    
    //
    // Initiate all ring buffers 
    //
    am_app_utils_ring_buffer_init_all(am_sys_ring_buffers, g_SysRingBuffSetup, SYS_RINGBUFF_INIT_COUNT);
    
    //
    // Turn on PDM
    //
    am_app_mic_verif_pdm_init();

#if AM_APP_ANALOG_MIC
    //
    // Set a pin to act as our ADC input
    //
    am_hal_gpio_pinconfig(33, g_AM_PIN_33_ADCSE5);
    //
    // Configure the ADC
    //
    adc_config();
    //
    // Start the CTIMER A3 for timer-based ADC measurements.
    //
    init_timerA3_for_ADC();
#endif // AM_APP_ANALOG_MIC
    //
    // TimerA0 init.
    //
    timerA0_init();

    //
    // Enable the timer Interrupt.
    //
    am_hal_ctimer_int_enable(AM_HAL_CTIMER_INT_TIMERA0);

    NVIC_SetPriority(PDM_IRQn, 4);
    NVIC_EnableIRQ(PDM_IRQn);
    NVIC_EnableIRQ(GPIO_IRQn);
    NVIC_EnableIRQ(CTIMER_IRQn);
    NVIC_EnableIRQ(ADC_IRQn);

    //
    // Enable interrupts to the core.
    //
    am_hal_interrupt_master_enable();
   
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

    am_hal_ctimer_start(0, AM_HAL_CTIMER_TIMERA);

#if AM_APP_ANALOG_MIC
    //
    // Trigger the ADC sampling for the first time manually.
    //
    if (AM_HAL_STATUS_SUCCESS != am_hal_adc_sw_trigger(g_ADCHandle))
    {
        am_util_stdio_printf("Error - triggering the ADC failed.\n");
    }
    while(!(*(uint32_t*)0x4002010c & 0x02));
    am_util_stdio_printf("ADCCAL reg value now is %x ...\r\n", *(uint32_t*)0x4002010c);
#endif // AM_APP_ANALOG_MIC

}


