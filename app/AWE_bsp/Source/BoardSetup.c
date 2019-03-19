// apollo mcu include
#include <stdint.h>
#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_util.h"

#include "Platform.h"
//*****************************************************************************
// GLOBALS
//*****************************************************************************

volatile uint32_t g_ui32TimerCount = 0;
volatile BOOL g_bPDMDataReady = false;
int32_t g_pi32PCMDataBuff[AWE_FRAME_SIZE]; 

//*****************************************************************************
// PDM configuration information.
//*****************************************************************************
void* PDMHandle;
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
/*{{{*/
#if defined (AM_PART_APOLLO2)
static am_hal_uart_config_t g_sUart0Config =
    {
        .ui32BaudRate    = 460800,
        .ui32DataBits    = AM_HAL_UART_DATA_BITS_8,
        .ui32StopBits    = AM_HAL_UART_ONE_STOP_BIT,
        .ui32Parity      = AM_HAL_UART_PARITY_NONE,
        .ui32FlowControl = AM_HAL_UART_FLOW_CTRL_NONE,
    };
    //
    // Enable the UART pins.
    //
    am_hal_gpio_pin_config(22, AM_HAL_PIN_22_UART0TX);
    am_hal_gpio_pin_config(17, AM_HAL_PIN_17_UART0RX);
#endif //#if defined (AM_PART_APOLLO2)

#if defined (AM_PART_APOLLO3)
    am_hal_gpio_pinconfig(AM_BSP_GPIO_COM_UART_TX, g_AM_BSP_GPIO_COM_UART_TX);
    am_hal_gpio_pinconfig(AM_BSP_GPIO_COM_UART_RX, g_AM_BSP_GPIO_COM_UART_RX);
#endif // #if defined (AM_PART_APOLLO3)
/*}}}*/

#if defined (AM_PART_APOLLO2)
    am_hal_uart_pwrctrl_enable(ui32Module);     // Power on the selected UART
    am_hal_uart_clock_enable(ui32Module);       // start UART interface and enable the FIFOs.
    am_hal_uart_disable(ui32Module);            // Disable the UART before configuring it.

    if (ui32Module == 0)
    {
        am_hal_uart_config(ui32Module, &g_sUart0Config);
        am_hal_uart_init_buffered(ui32Module, g_pui8UartRxBuffer0, UART0_BUFFER_SIZE,
                                    g_pui8UartTxBuffer0, UART0_BUFFER_SIZE);
    }

    //
    // Configure the UART FIFO.
    //
    am_hal_uart_fifo_config(ui32Module, AM_HAL_UART_TX_FIFO_1_2 | AM_HAL_UART_RX_FIFO_1_2);

#endif  //#if defined (AM_PART_APOLLO2)

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
#if defined (AM_PART_APOLLO2)
    am_hal_uart_clock_enable(ui32Module);

    am_hal_uart_enable(ui32Module);
    am_hal_uart_int_enable(ui32Module, AM_HAL_UART_INT_RX_TMOUT |
                                       AM_HAL_UART_INT_RX |
                                       AM_HAL_UART_INT_TXCMP);

        am_hal_gpio_pin_config(22, AM_HAL_PIN_22_UART0TX);
        am_hal_gpio_pin_config(17, AM_HAL_PIN_17_UART0RX);
        am_hal_interrupt_priority_set(AM_HAL_INTERRUPT_UART0, AM_HAL_INTERRUPT_PRIORITY(6));

    am_hal_interrupt_enable(AM_HAL_INTERRUPT_UART + ui32Module);
#endif //#if defined (AM_PART_APOLLO2)

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

//*****************************************************************************
// PDM initialization.
//*****************************************************************************
void pdm_trigger_dma(void)
{
    //
    // Configure DMA and target address.
    //
    am_hal_pdm_transfer_t sTransfer;
    sTransfer.ui32TargetAddr = (uint32_t ) g_pi32PCMDataBuff;
    sTransfer.ui32TotalCount = (AWE_FRAME_SIZE * 4);

    //
    // Start the data transfer.
    //
    am_hal_pdm_dma_start(PDMHandle, &sTransfer);
}


void ap3_pdm_init(void) 
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

//*****************************************************************************
//
// Function to initialize Timer A0¡£
//
//*****************************************************************************
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
void
timerA0_init(void)
{
    uint32_t ui32Period;

    //
    // Enable the LFRC.
    //
    am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_HFADJ_ENABLE, 0);
    

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
    timerA0_init();

    //
    // Enable the timer Interrupt.
    //
    am_hal_ctimer_int_enable(AM_HAL_CTIMER_INT_TIMERA0);

#endif  // defined(AM_BSP_NUM_BUTTONS)  &&  defined(AM_BSP_NUM_LEDS)
    
    uart_init(UART0_MODULE);
    uart_enable(UART0_MODULE);
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


    am_hal_ctimer_start(0, AM_HAL_CTIMER_TIMERA);

}

//-----------------------------------------------------------------------------
// METHOD:  CoreInit
// PURPOSE: Setup board peripherals
//-----------------------------------------------------------------------------
void CoreInit(void)
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
    configASSERT(eBurstMode == AM_HAL_BURST_MODE);

//#endif // configUSE_BURST_ALWAYS_ON

}   // End CoreInit


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
    am_hal_ctimer_int_clear(AM_HAL_CTIMER_INT_TIMERA0);
}


//*****************************************************************************
// GPIO ISR
// Will enable the PDM, set number of frames transferred to 0, and turn on LED
//*****************************************************************************
void am_gpio_isr(void) 
{
    //
    // debounce.
    //
//    if(g_ui8DebounceFlag == 0)
//    {
//        g_ui8DebounceFlag = 1;
//        g_ui32DebounceTimerCount = 0;
//    }  
    //
    // Clear the GPIO Interrupt (write to clear).
    //
    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON0));

}


