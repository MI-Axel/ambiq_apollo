
/* This file is the seyup code of ap3blue evb for the audio experiment platform. */

#include "board_setup.h"
#include "audio_driver.h"

//*****************************************************************************
//
// Globals
//
//*****************************************************************************
volatile uint32_t g_ui32TimerCount = 0;

volatile uint8_t g_ui8DebounceFlag = 0;

volatile uint32_t g_ui32DebounceTimerCount = 0;

volatile  am_app_AEP_key_value_enum_t g_sysKeyValue = AM_APP_KEY_NONE;

#if configUSE_RTT_DATA_OUTPUT
uint8_t g_rttRecorderBuff[RTT_BUFFER_LENGTH];
volatile uint8_t g_rttRecordingFlag = 0; 
#endif
//******************************************************************************
//Global data buffers used by ring buffers
//*****************************************************************************
//volatile uint8_t g_ui8PCMDataRingBuff[PCM_FRAME_SIZE*PCM_DATA_BYTES*NUM_PCM_FRAMES];

//am_app_utils_ring_buffer_t am_sys_ring_buffers[AM_APP_RINGBUFF_MAX];

//static const am_app_utils_ringbuff_setup_t g_SysRingBuffSetup[] = 
//{
//    {AM_APP_RINGBUFF_PCM, g_ui8PCMDataRingBuff, PCM_FRAME_SIZE*NUM_PCM_FRAMES*PCM_DATA_BYTES}
//};
//#define SYS_RINGBUFF_INIT_COUNT     (sizeof(g_SysRingBuffSetup)/sizeof(am_app_utils_ringbuff_setup_t))


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
const am_hal_gpio_pincfg_t g_deepsleep_button0 = {
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
    AM_HAL_CTIMER_XT_32_768KHZ),
     //    AM_HAL_CTIMER_HFRC_12MHZ), 
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
    ui32Period = 33;
    am_hal_ctimer_period_set(0, AM_HAL_CTIMER_TIMERA, ui32Period,
                             (ui32Period >> 1));

    //
    // Clear the timer Interrupt
    //
    am_hal_ctimer_int_clear(AM_HAL_CTIMER_INT_TIMERA0);
}


//*****************************************************************************
//
// Function to initialize Timer A0 to interrupt every 1/4 second.
//
//*****************************************************************************
void am_app_AEP_sys_init(void)
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
    am_hal_gpio_pinconfig(AM_BSP_GPIO_BUTTON0, g_deepsleep_button0);
    
    //
    // Clear the GPIO Interrupt (write to clear).
    //
    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON0));
    
    //
    // Enable the GPIO/button interrupt.
    //
    am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON0));
    
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

    // Turn on PDM
//    am_app_AEP_pdm_init();
 
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
#if configUSE_RTT_DATA_OUTPUT 
    am_app_utils_rtt_init(g_rttRecorderBuff, RTT_BUFFER_LENGTH);
#endif

    //
    // Configure of burst mode
    //
    if (AM_HAL_STATUS_SUCCESS == am_hal_burst_mode_initialize(&eBurstModeAvailable))
    {
        if (AM_HAL_BURST_AVAIL == eBurstModeAvailable)
        {
            am_util_stdio_printf("Apollo3 Burst Mode is Available\r\n");
        }
        else
        {
            am_util_stdio_printf("Apollo3 Burst Mode is Not Available\r\n");
        }
    }
    else
    {
        am_util_stdio_printf("Failed to Initialize for Burst Mode operation\r\n");
    }

#if configUSE_BURST_ALWAYS_ON
    // Put the MCU into "Burst" mode.
    if (AM_HAL_STATUS_SUCCESS == am_hal_burst_mode_enable(&eBurstMode))
    {
        if (AM_HAL_BURST_MODE == eBurstMode)
        {
            am_util_stdio_printf("Apollo3 operating in Burst Mode (96MHz)\r\n");
        }
    }
    else
    {
        am_util_stdio_printf("Failed to Enable Burst Mode operation\r\n");
    }

#endif // configUSE_BURST_ALWAYS_ON

    am_hal_ctimer_start(0, AM_HAL_CTIMER_TIMERA);

//    am_app_utils_ring_buffer_init_all(am_sys_ring_buffers, g_SysRingBuffSetup, SYS_RINGBUFF_INIT_COUNT);

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
    if ( g_ui8DebounceFlag == 1)
    {
        g_ui32DebounceTimerCount++;

        if(g_ui32DebounceTimerCount > 300)
        {
            g_sysKeyValue = AM_APP_KEY_0;
            g_ui8DebounceFlag = 0;
        }
    } 

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
    if(g_ui8DebounceFlag == 0)
    {
        g_ui8DebounceFlag = 1;
        g_ui32DebounceTimerCount = 0;
    }  
    //
    // Clear the GPIO Interrupt (write to clear).
    //
    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON0));

}


