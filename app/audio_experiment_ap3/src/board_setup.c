
/* This file is the seyup code of ap3blue evb for the audio experiment platform. */

#include "board_setup.h"
#include "audio_driver.h"

//*****************************************************************************
//
// Globals
//
//*****************************************************************************
volatile uint32_t g_ui32TimerCount = 0;

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
#if USE_XTAL
     AM_HAL_CTIMER_XT_256HZ),
#else
     AM_HAL_CTIMER_LFRC_32HZ),
#endif

    // No configuration for Timer0B.
    0,
};

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
#if USE_XTAL
    am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_XTAL_START, 0);
#else
    am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_LFRC_START, 0);
#endif

    //
    // Set up timer A0.
    //
    am_hal_ctimer_clear(0, AM_HAL_CTIMER_TIMERA);
    am_hal_ctimer_config(0, &g_sTimer0);

    //
    // Set up timerA0 to 32Hz from LFRC divided to 1 second period.
    //
    ui32Period = 32;
#if USE_XTAL
    ui32Period *= 8;
#endif
    am_hal_ctimer_period_set(0, AM_HAL_CTIMER_TIMERA, ui32Period,
                             (ui32Period >> 1));

    //
    // Clear the timer Interrupt
    //
    am_hal_ctimer_int_clear(AM_HAL_CTIMER_INT_TIMERA0);
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
//    if ( g_ui32TimerCount >= 1)
//    {
        //
        // Reset the global.
        //
//        g_ui32TimerCount = 0;
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
    // Delay for debounce.
    //
    am_util_delay_ms(200);
  
    //
    // Clear the GPIO Interrupt (write to clear).
    //
    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(AM_BSP_GPIO_BUTTON0));
    if(g_audioRunningFlag == 0)
    {   
        g_audioRunningFlag = 1;
        am_devices_led_on(am_bsp_psLEDs, 0);
    
        am_hal_pdm_fifo_flush(PDMHandle);
        pdm_data_get();
        am_hal_pdm_enable(PDMHandle);
    } 
    //
    // Turn on LED 0
    //
}


