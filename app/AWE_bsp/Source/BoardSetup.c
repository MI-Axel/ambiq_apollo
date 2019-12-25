#include "BoardSetup.h"
#include "TargetInfo.h"
#include "TuningDriver.h"
#include "amu2s.h"
//*****************************************************************************
// GLOBALS
//*****************************************************************************
volatile uint32_t g_ui32TimerCount = 0;
volatile BOOL g_bPDMDataReady = FALSE;
volatile BOOL g_bUARTPacketReceived = FALSE;
volatile BOOL g_bPacketReceived = FALSE;
volatile int32_t g_pi32PCMDataBuff[AWE_FRAME_SIZE];
volatile int32_t g_pi32DMATempBuff[AWE_FRAME_SIZE];
volatile int16_t g_pi16LeftChBuff[AWE_FRAME_SIZE];
volatile int16_t g_pi16RightChBuff[AWE_FRAME_SIZE];
//*****************************************************************************
//
// UART handle.
//
//*****************************************************************************
#if defined (AM_PART_APOLLO3)
void *g_sCOMUART;

#define CHECK_ERRORS(x)                                                       \
    if ((x) != AM_HAL_STATUS_SUCCESS)                                         \
    {                                                                         \
        error_handler(x);                                                     \
    }

volatile uint32_t ui32LastError;

//*****************************************************************************
//
// Catch HAL errors.
//
//*****************************************************************************
void
error_handler(uint32_t ui32ErrorStatus)
{
    ui32LastError = ui32ErrorStatus;

    while (1);
}
//*****************************************************************************
//
// UART buffers.
//
//*****************************************************************************
uint8_t g_pui8TxBuffer[4*MAX_COMMAND_BUFFER_LEN];
uint8_t g_pui8RxBuffer[4*MAX_COMMAND_BUFFER_LEN];

//*****************************************************************************
//
// UART configuration.
//
//*****************************************************************************
const am_hal_uart_config_t g_sUartConfig =
{
    .ui32BaudRate    = 460800,
    .ui32DataBits    = AM_HAL_UART_DATA_BITS_8,
    .ui32StopBits    = AM_HAL_UART_ONE_STOP_BIT,
    .ui32Parity      = AM_HAL_UART_PARITY_NONE,
    .ui32FlowControl = AM_HAL_UART_FLOW_CTRL_NONE,
    //
    // Set TX and RX FIFOs to interrupt at half-full.
    //
    .ui32FifoLevels = (AM_HAL_UART_TX_FIFO_1_2 |
                       AM_HAL_UART_RX_FIFO_1_2),

    //
    // Buffers
    //
    .pui8TxBuffer = g_pui8TxBuffer,
    .ui32TxBufferSize = sizeof(g_pui8TxBuffer),
    .pui8RxBuffer = g_pui8RxBuffer,
    .ui32RxBufferSize = sizeof(g_pui8RxBuffer),
};
#endif //#if defined (AM_PART_APOLLO3)
//**************************************
// Burst mode configuration.
//**************************************
am_hal_burst_avail_e          eBurstModeAvailable;
am_hal_burst_mode_e           eBurstMode;

//-----------------------------------------------------------------------------
// METHOD:  uart_init
// PURPOSE: Setup UART0 and/or UART1
//-----------------------------------------------------------------------------
void uart_init(uint32_t ui32Module)
{
#if defined (AM_PART_APOLLO3)
    am_hal_gpio_pinconfig(AM_BSP_GPIO_COM_UART_TX, g_AM_BSP_GPIO_COM_UART_TX);
    am_hal_gpio_pinconfig(AM_BSP_GPIO_COM_UART_RX, g_AM_BSP_GPIO_COM_UART_RX);
#endif // #if defined (AM_PART_APOLLO3)
/*}}}*/

#if defined (AM_PART_APOLLO3)
    //
    // Initialize the printf interface for UART output.
    //
    CHECK_ERRORS(am_hal_uart_initialize(ui32Module, &g_sCOMUART));
    CHECK_ERRORS(am_hal_uart_power_control(g_sCOMUART, AM_HAL_SYSCTRL_WAKE, false));
    CHECK_ERRORS(am_hal_uart_configure(g_sCOMUART, &g_sUartConfig));
#endif //#if defined (AM_PART_APOLLO3)
}

//*****************************************************************************
//
// Enable the UART
//
//*****************************************************************************
void uart_enable(uint32_t ui32Module)
{
#if defined (AM_PART_APOLLO3)
    //
    // Enable interrupts.
    //
#if AM_CMSIS_REGS
    NVIC_SetPriority(UART0_IRQn, 0x7);
    NVIC_EnableIRQ((IRQn_Type)(UART0_IRQn + AM_BSP_UART_PRINT_INST));
#endif // AM_CMSIS_REGS
    am_hal_interrupt_master_enable();
#endif
}

//
// Microphone configuration (Analog/Digital)
//
#if AWE_BSP_ConfigUSE_ANALOG_MIC
//
// ADC DMA target address
//
uint32_t g_ui32ADCSampleBuffer[ADC_SAMPLE_COUNT*ADC_MIC_CHANNELS];

//am_hal_adc_sample_t SampleBuffer[ADC_SAMPLE_COUNT];

//uint32_t g_ui32IsrCounter = 0;
//uint32_t g_ui32TaskCounter = 0;

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

const am_hal_gpio_pincfg_t g_AM_PIN_32_ADCSE4 =
{
    .uFuncSel       = AM_HAL_PIN_32_ADCSE4,
};


void adc_config_dma(void)
{
    am_hal_adc_dma_config_t       ADCDMAConfig;

    //
    // Configure the ADC to use DMA for the sample transfer.
    //
    ADCDMAConfig.bDynamicPriority = true;
    ADCDMAConfig.ePriority = AM_HAL_ADC_PRIOR_SERVICE_IMMED;
    ADCDMAConfig.bDMAEnable = true;
    ADCDMAConfig.ui32SampleCount = ADC_SAMPLE_COUNT * ADC_MIC_CHANNELS;
    ADCDMAConfig.ui32TargetAddress = (uint32_t)g_ui32ADCSampleBuffer;
    if (AM_HAL_STATUS_SUCCESS != am_hal_adc_configure_dma(g_ADCHandle, &ADCDMAConfig))
    {
        am_util_stdio_printf("Error - configuring ADC DMA failed.\n");
    }

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
    ADCConfig.eReference         = AM_HAL_ADC_REFSEL_INT_1P5;
    ADCConfig.eClockMode         = AM_HAL_ADC_CLKMODE_LOW_LATENCY;
    ADCConfig.ePowerMode         = AM_HAL_ADC_LPMODE0;
    ADCConfig.eRepeat            = AM_HAL_ADC_REPEATING_SCAN;
    if (AM_HAL_STATUS_SUCCESS != am_hal_adc_configure(g_ADCHandle, &ADCConfig))
    {
        am_util_stdio_printf("Error - configuring ADC failed.\n");
    }

    //
    // Set up an ADC slot
    //
    ADCSlotConfig.bEnabled       = false;
    ADCSlotConfig.bWindowCompare = false;
    ADCSlotConfig.eChannel       = AM_HAL_ADC_SLOT_CHSEL_SE0;    // 0
    ADCSlotConfig.eMeasToAvg     = AM_HAL_ADC_SLOT_AVG_1;        // 0
    ADCSlotConfig.ePrecisionMode = AM_HAL_ADC_SLOT_14BIT;        // 0

    am_hal_adc_configure_slot(g_ADCHandle, 2, &ADCSlotConfig);   // Unused slot
    am_hal_adc_configure_slot(g_ADCHandle, 3, &ADCSlotConfig);   // Unused slot
    am_hal_adc_configure_slot(g_ADCHandle, 4, &ADCSlotConfig);   // Unused slot
    am_hal_adc_configure_slot(g_ADCHandle, 5, &ADCSlotConfig);   // Unused slot
    am_hal_adc_configure_slot(g_ADCHandle, 6, &ADCSlotConfig);   // Unused slot
    am_hal_adc_configure_slot(g_ADCHandle, 7, &ADCSlotConfig);   // Unused slot

    ADCSlotConfig.bEnabled       = true;
    ADCSlotConfig.bWindowCompare = false;
    ADCSlotConfig.eChannel       = AM_HAL_ADC_SLOT_CHSEL_SE5;
    ADCSlotConfig.eMeasToAvg     = AM_HAL_ADC_SLOT_AVG_1;
    ADCSlotConfig.ePrecisionMode = AM_HAL_ADC_SLOT_14BIT;
    am_hal_adc_configure_slot(g_ADCHandle, 0, &ADCSlotConfig);   // micro_shield AN on 33

    ADCSlotConfig.bEnabled       = true;
    ADCSlotConfig.bWindowCompare = false;
    ADCSlotConfig.eChannel       = AM_HAL_ADC_SLOT_CHSEL_SE4;
    ADCSlotConfig.eMeasToAvg     = AM_HAL_ADC_SLOT_AVG_1;
    ADCSlotConfig.ePrecisionMode = AM_HAL_ADC_SLOT_14BIT;
    am_hal_adc_configure_slot(g_ADCHandle, 1, &ADCSlotConfig);   // micro_shield AN on 32

//    ADCSlotConfig.eMeasToAvg      = AM_HAL_ADC_SLOT_AVG_1;
//    ADCSlotConfig.ePrecisionMode  = AM_HAL_ADC_SLOT_14BIT;
//    ADCSlotConfig.eChannel        = AM_HAL_ADC_SLOT_CHSEL_SE5;
//    ADCSlotConfig.bWindowCompare  = false;
//    ADCSlotConfig.bEnabled        = true;
//    if (AM_HAL_STATUS_SUCCESS != am_hal_adc_configure_slot(g_ADCHandle, 1, &ADCSlotConfig))
//    {
//        am_util_stdio_printf("Error - configuring ADC Slot 0 failed.\n");
//    }
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

void init_timerA3_for_ADC(void)
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

#else //  AWE_BSP_ConfigUSE_ANALOG_MIC
//*****************************************************************************
// PDM configuration information.
//*****************************************************************************
void* PDMHandle;

//*****************************************************************************
// PDM initialization.
//*****************************************************************************
am_hal_pdm_config_t g_sPdmConfig =
{
    .eClkDivider = AM_HAL_PDM_MCLKDIV_1,
    .eLeftGain = AM_HAL_PDM_GAIN_P105DB,
    .eRightGain = AM_HAL_PDM_GAIN_P105DB,
    .ui32DecimationRate = 48,//24,//
    .bHighPassEnable = 0,//1, //
    .ui32HighPassCutoff = 0xB,
    .ePDMClkSpeed = AM_HAL_PDM_CLK_1_5MHZ,//AM_HAL_PDM_CLK_750KHZ,//
    .bInvertI2SBCLK = 0,
    .ePDMClkSource = AM_HAL_PDM_INTERNAL_CLK,
    .bPDMSampleDelay = 0,
    .bDataPacking = 1,
    .ePCMChannels = AM_HAL_PDM_CHANNEL_STEREO,
    .bLRSwap = 0,
    .bSoftMute = 0,
};

void pdm_trigger_dma(void)
{
    //
    // Configure DMA and target address.
    //
    am_hal_pdm_transfer_t sTransfer;
    sTransfer.ui32TargetAddr = (uint32_t )g_pi32PCMDataBuff;
    sTransfer.ui32TotalCount = (AWE_FRAME_SIZE * 4);

    //
    // Start the data transfer.
    //
    am_hal_pdm_dma_start(PDMHandle, &sTransfer);
}


void ap3_pdm_init(void) 
{
    //
    // Initialize, power-up, and configure the PDM.
    //
    am_hal_pdm_initialize(0, &PDMHandle);
    am_hal_pdm_power_control(PDMHandle, AM_HAL_PDM_POWER_ON, false);
    am_hal_pdm_configure(PDMHandle, &g_sPdmConfig);

    //
    // Configure the necessary pins.
    //
    am_hal_gpio_pincfg_t sPinCfg = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    sPinCfg.uFuncSel = AM_HAL_PIN_12_PDMCLK;
    am_hal_gpio_pinconfig(12, sPinCfg);

    sPinCfg.uFuncSel = AM_HAL_PIN_11_PDMDATA;
    am_hal_gpio_pinconfig(11, sPinCfg);

    am_hal_pdm_fifo_flush(PDMHandle);

    //
    // Configure and enable PDM interrupts (set up to trigger on DMA
    // completion).
    //
    am_hal_pdm_interrupt_enable(PDMHandle, (AM_HAL_PDM_INT_DERR
                                            | AM_HAL_PDM_INT_DCMP
                                            | AM_HAL_PDM_INT_UNDFL
                                            | AM_HAL_PDM_INT_OVF));
    NVIC_EnableIRQ(PDM_IRQn);
    NVIC_SetPriority(PDM_IRQn, 0x4);


    //
    // Enable PDM
    //
    am_hal_pdm_enable(PDMHandle);
    pdm_trigger_dma();

}
#endif // AWE_BSP_ConfigUSE_ANALOG_MIC
//*****************************************************************************
//
// Function to initialize Timer A0¡£
//
//*****************************************************************************
//**************************************
// Timer configuration.
// Timer 0: Profiling timer used by AWE
// Timer 1: System tick of 1mS
//**************************************

am_hal_ctimer_config_t g_cTimer0 =
{
    // link 16 bit timers for one 32 bit timer.
    1,

    // Set up Timer0A.
    (AM_HAL_CTIMER_FN_CONTINUOUS |
     AM_HAL_CTIMER_HFRC_12MHZ),

    // No configuration for Timer0B.
    0,
};

am_hal_ctimer_config_t g_cTimer1 =
{
    // Don't link timers.
    0,

    // Set up Timer1A.
    (AM_HAL_CTIMER_FN_REPEAT    |
     AM_HAL_CTIMER_INT_ENABLE   |
//    AM_HAL_CTIMER_XT_32_768KHZ),
    AM_HAL_CTIMER_HFRC_12MHZ), 
    // No configuration for Timer0B.
    0,
};


void bsp_timer_init(void)
{
    uint32_t ui32Period;

    //
    // Enable the HFRC for timer 0 and timer 1.
    //
    am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_HFADJ_ENABLE, 0);

    //
    // Set up timer A0 and A1
    //
    am_hal_ctimer_clear(0, AM_HAL_CTIMER_BOTH);
    am_hal_ctimer_config(0, &g_cTimer0);
    
    am_hal_ctimer_clear(1, AM_HAL_CTIMER_TIMERA);
    am_hal_ctimer_config(1, &g_cTimer1);


    //
    // Set up timerA0 to 32Hz from LFRC divided to 1 second period.
    //
    ui32Period = 12000;
    am_hal_ctimer_period_set(1, AM_HAL_CTIMER_TIMERA, ui32Period,
                             (ui32Period >> 1));

    //
    // Clear the timer Interrupt
    //
    am_hal_ctimer_int_clear(AM_HAL_CTIMER_INT_TIMERA1);
}

//-----------------------------------------------------------------------------
// METHOD:  BoardInit
// PURPOSE: Setup board peripherals
//----------------------------------------------------------------------------- 
void BoardInit(void)
{


#if defined(AM_BSP_NUM_BUTTONS) && defined(AM_BSP_NUM_LEDS)
    //
    // Configure the button pin.
    //
//    am_hal_gpio_pinconfig(AM_BSP_GPIO_BUTTON0, g_deepsleep_button0);
    
    //
    // Clear the GPIO Interrupt (write to clear).
    //
//    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON0));
    
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
    //
    // TimerA0 init.
    //
    bsp_timer_init();

    //
    // Enable the timer Interrupt.
    //
    am_hal_ctimer_int_enable(AM_HAL_CTIMER_INT_TIMERA1);

#endif  // defined(AM_BSP_NUM_BUTTONS)  &&  defined(AM_BSP_NUM_LEDS)
    
    uart_init(0);
    uart_enable(0);
    // Turn on PDM
    ap3_pdm_init();
 
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
//    am_bsp_uart_printf_enable();

    //
    // MIPS measurement by GPIO toggle
    //
    am_hal_gpio_pinconfig(48, g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_state_write(48, AM_HAL_GPIO_OUTPUT_CLEAR);
        am_hal_gpio_pinconfig(40, g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_state_write(40, AM_HAL_GPIO_OUTPUT_CLEAR);
    

    am_hal_ctimer_start(0, AM_HAL_CTIMER_BOTH);

    am_hal_ctimer_start(1, AM_HAL_CTIMER_TIMERA);
}

//-----------------------------------------------------------------------------
// METHOD:  targetInit
// PURPOSE: Setup the target board
//-----------------------------------------------------------------------------
void targetInit(void)
{
    // Reset of all peripherals, Initializes the Flash interface and the Systick.
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

    //
    // Configure of burst mode
    //
    am_hal_burst_mode_initialize(&eBurstModeAvailable);

//#if configUSE_BURST_ALWAYS_ON
    // Put the MCU into "Burst" mode.
    am_hal_burst_mode_enable(&eBurstMode);
//    configASSERT(eBurstMode == AM_HAL_BURST_MODE);

    UARTMsgInit();
    
    BoardInit();

//#endif // configUSE_BURST_ALWAYS_ON

}   // End targetInit

//
// ISR of sys
//
//*****************************************************************************
//
// PDM interrupt handler.
//
//*****************************************************************************
#if AM_BSP_ConfigUSE_ANALOG_MIC
        float pfAmicLeftArray[ADC_SAMPLE_COUNT];
        float pfAmicRightArray[ADC_SAMPLE_COUNT];
        float pfAmicLeftFilteredBuff[ADC_SAMPLE_COUNT];
        float pfAmicRightFilteredBuff[ADC_SAMPLE_COUNT];
void am_adc_isr(void)
{
    uint32_t ui32IntMask;
    bool bQueueReValue;
    uint32_t ui32AdcPcmDataBuffer[ADC_SAMPLE_COUNT];
    int16_t in16PcmCh1Val = 0;
    int16_t in16PcmCh2Val = 0;

    uint8_t indx= 0;
    //
    // Read the interrupt status.
    //
    if (AM_HAL_STATUS_SUCCESS != am_hal_adc_interrupt_status(g_ADCHandle, &ui32IntMask, false))
    {
        am_util_stdio_printf("Error reading ADC interrupt status\n");
    }

    //
    // Clear the ADC interrupt.
    //
    if (AM_HAL_STATUS_SUCCESS != am_hal_adc_interrupt_clear(g_ADCHandle, ui32IntMask))
    {
        am_util_stdio_printf("Error clearing ADC interrupt status\n");
    }

    //
    // If we got a DMA complete, set the flag.
    //
    if (ui32IntMask & AM_HAL_ADC_INT_DCMP)
    {
        //
        // Re-configure the ADC DMA.
        //
        adc_config_dma();
        for(indx=0; indx<ADC_SAMPLE_COUNT; indx++)
        {
            ui32AdcPcmDataBuffer[indx] = 0;
            in16PcmCh1Val = ((g_ui32ADCSampleBuffer[indx * ADC_MIC_CHANNELS] >> 6) & 0x00003FFF)-8192;    //0.75: 8192
            in16PcmCh2Val = ((g_ui32ADCSampleBuffer[indx * ADC_MIC_CHANNELS+1] >> 6) & 0x00003FFF)-8192;    //0.75: 8192
            ui32AdcPcmDataBuffer[indx] = (((uint16_t)in16PcmCh1Val) << 16) | ((uint16_t)in16PcmCh2Val);
//            g_ui32DebugVal = ui32AdcPcmDataBuffer[indx];
        }
        am_audio_buffer_push(AM_AUDIO_BUFFER_STEREO, ui32AdcPcmDataBuffer, ADC_SAMPLE_COUNT*ANALOG_MIC_DATA_BYTES);
        bQueueReValue = am_app_utils_task_send_fromISR(AM_APP_ISR_ADC, AM_APP_TASK_AUD_PROCESSING, AM_APP_MESSAGE_LONG, BYTES_PER_SAMPLE*PCM_FRAME_SIZE, &am_audio_ring_buffers[AM_AUDIO_BUFFER_STEREO]);
#if (VOS_configUSE_AMU2S_RECORDER && VOS_configUSE_RECORD_RAW_AMIC)
//        amu2s_send(Amu2s_pcm, i32PDMSampleStereo, AMU2S_PCM_BYTES);
#endif //(VOS_configUSE_AMU2S_RECORDER&&VOS_configUSE_RECORD_RAW_AMIC)
    }

    //
    // If we got a DMA error, set the flag.
    //
    if (ui32IntMask & AM_HAL_ADC_INT_DERR)
    {
        g_bADCDMAError = true;
    }
}


#else // AM_BSP_ConfigUSE_ANALOG_MIC
void am_pdm_isr(void) 
{
    uint32_t ui32Status;
    //
    // Read the interrupt status.
    //
    am_hal_pdm_interrupt_status_get(PDMHandle, &ui32Status, true);
    am_hal_pdm_interrupt_clear(PDMHandle, ui32Status);
    am_hal_gpio_state_write(40, AM_HAL_GPIO_OUTPUT_SET);
    if ((ui32Status & AM_HAL_PDM_INT_DCMP))
    {
        // trigger next traction
        PDMn(0)->DMATOTCOUNT = AWE_FRAME_SIZE * 4;  // FIFO unit in bytes
        g_ui32AudioDMAComplete = 1;
        memcpy((void*)g_pi32DMATempBuff, (void*)g_pi32PCMDataBuff, AWE_FRAME_SIZE*PCM_SAMPLE_BYTES);
//        AWEProcessing(g_pi32PCMDataBuff);
//        am_util_debug_printf("PDM DCMP interrupt, pick g_ui32PDMDataBuffer[5] = 0x%8x\n", g_ui32PDMDataBuffer[5]);
    }
    else
    {
        am_hal_pdm_fifo_flush(PDMHandle);
    }
    am_hal_gpio_state_write(40, AM_HAL_GPIO_OUTPUT_CLEAR);

}
#endif // AM_BSP_ConfigUSE_ANALOG_MIC

void am_uart_isr(void)
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

//*****************************************************************************
//
// Timer Interrupt Service Routine (ISR)
//
//*****************************************************************************
void
am_ctimer_isr(void)
{
    //
    // Increment count and set limit based on the number of LEDs available.
    //
    g_ui32TimerCount++;
//    if ( g_ui8DebounceFlag == 1)
//    {
//        g_ui32DebounceTimerCount++;
//
//        if(g_ui32DebounceTimerCount > 300)
//        {
//            g_sysKeyValue = AM_APP_KEY_0;
//            g_ui8DebounceFlag = 0;
//        }
//    } 

    //
    // Clear TimerA0 Interrupt (write to clear).
    //
    am_hal_ctimer_int_clear(AM_HAL_CTIMER_INT_TIMERA1);
}



