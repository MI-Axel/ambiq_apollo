//*****************************************************************************
//
//! @file opus_step1.c
//!
//! @brief This example is the step 1 for opus optimization progress.
//! The project loads a pre-recorded sound file into the flash 
//! and waiting for opus compression.
//! burst mode APIs and GPIO toggle APIs are added into the project for support.
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2019, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// Third party software included in this distribution is subject to the
// additional license terms as defined in the /docs/licenses directory.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision v2.0.0 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_util.h"

#include "ae_api.h"
#if 1  // supplied vector
#include "capture_usp0905.bin.h"
short *p_pcm_samples = (short*)&capture_usp0905_bin[0];
#define MAX_INPUT_SAMPLE (sizeof(capture_usp0905_bin)/2)

#else   // 
short fre07_clip1 []= {
#include "fre07_clip1_c.h"
};
short *p_pcm_samples = &fre07_clip1[0];

#define MAX_INPUT_SAMPLE (sizeof(fre07_clip1)/2)
#endif
//*****************************************************************************
//
// Macros
//
//*****************************************************************************
//
// The default is to use the LFRC as the clock source.
// Can  use the XTAL via the USE_XTAL define.
//
//#define USE_XTAL    1
#if USE_XTAL
#define BC_CLKSRC   "XTAL"
#else
#define BC_CLKSRC   "LFRC"
#endif

#ifdef AM_BSP_NUM_LEDS
#define NUM_LEDS    AM_BSP_NUM_LEDS
#else
#define NUM_LEDS    5       // Make up an arbitrary number of LEDs
#endif

//*****************************************************************************
//
// Globals
//
//*****************************************************************************
volatile uint32_t g_ui32TimerCount = 0;

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
    if ( g_ui32TimerCount >= (1 << NUM_LEDS) )
    {
        //
        // Reset the global.
        //
        g_ui32TimerCount = 0;
    }

    //
    // Clear TimerA0 Interrupt (write to clear).
    //
    am_hal_ctimer_int_clear(AM_HAL_CTIMER_INT_TIMERA0);
}
char encoded_buffer[50*1024];

//*****************************************************************************
//
// Main function.
//
//*****************************************************************************
int
main(void)
{
    am_hal_burst_avail_e          eBurstModeAvailable;
    am_hal_burst_mode_e           eBurstMode;

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

#ifdef AM_BSP_NUM_LEDS
    //
    // Initialize the LED array
    //
    am_devices_led_array_init(am_bsp_psLEDs, AM_BSP_NUM_LEDS);
#endif

    //
    // Initialize the printf interface for ITM/SWO output.
    //
    am_bsp_itm_printf_enable();

    //
    // Clear the terminal and print the banner.
    //
    am_util_stdio_terminal_clear();
    am_util_stdio_printf("Binary Counter Example\n");
    am_util_stdio_printf("  (Timer clock source is " BC_CLKSRC ")\n");

    //
    // TimerA0 init.
    //
    timerA0_init();
    

    // Check that the Burst Feature is available.
    // example only, no need to print...
    if (AM_HAL_STATUS_SUCCESS == am_hal_burst_mode_initialize(&eBurstModeAvailable))
    {
        if (AM_HAL_BURST_AVAIL == eBurstModeAvailable)
        {
            am_util_stdio_printf("Apollo3 Burst Mode is Available\n");
        }
        else
        {
            am_util_stdio_printf("Apollo3 Burst Mode is Not Available\n");
        }
    }
    else
    {
        am_util_stdio_printf("Failed to Initialize for Burst Mode operation\n");
    }

    // Make sure we are in "Normal" mode.
    // example only, no need to print...
    if (AM_HAL_STATUS_SUCCESS == am_hal_burst_mode_disable(&eBurstMode))
    {
        if (AM_HAL_NORMAL_MODE == eBurstMode)
        {
            am_util_stdio_printf("Apollo3 operating in Normal Mode (48MHz)\n");
        }
    }
    else
    {
        am_util_stdio_printf("Failed to Disable Burst Mode operation\n");
    }


    // Put the MCU into "Burst" mode.
    // example only, no need to print...
    if (AM_HAL_STATUS_SUCCESS == am_hal_burst_mode_enable(&eBurstMode))
    {
        if (AM_HAL_BURST_MODE == eBurstMode)
        {
            am_util_stdio_printf("Apollo3 operating in Burst Mode (96MHz)\n");
        }
    }
    else
    {
        am_util_stdio_printf("Failed to Enable Burst Mode operation\n");
    }
    // return to 48MHz operation
    am_hal_burst_mode_disable(&eBurstMode); 
#ifdef    NRC
    //
    // Enable the timer Interrupt.
    //
    am_hal_ctimer_int_enable(AM_HAL_CTIMER_INT_TIMERA0);

    //
    // Enable the timer interrupt in the NVIC.
    //
    NVIC_EnableIRQ(CTIMER_IRQn);
    am_hal_interrupt_master_enable();

    //
    // Start timer A0
    //
    am_hal_ctimer_start(0, AM_HAL_CTIMER_TIMERA);
    
#endif   

    //
    // We are done printing. Disable debug printf messages on ITM.
    //
    am_bsp_debug_printf_disable();

    
    /* initialize the audio encoder */
    audio_enc_init();

    //
    // Loop forever.
    //
    int frame_count = 0;
    int framesize = 320;
    int input_samples_processed = 0;
    int encoded_bytes = 0;
    int output_bytes_produced = 0;
    short *p_input_samples = p_pcm_samples;
    char *p_output_bytes = &encoded_buffer[0];
    while (1)
    {
        //
        // Go to Deep Sleep.
        //
#ifdef    NRC
        am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_DEEP);
#endif        

#ifdef AM_BSP_NUM_LEDS
        //
        // Set the LEDs.
        //
        am_devices_led_array_out(am_bsp_psLEDs, AM_BSP_NUM_LEDS,
                                 g_ui32TimerCount);
#endif
        //
        // Enable debug printf messages using ITM on SWO pin
        //
        am_bsp_debug_printf_enable();


        encoded_bytes = audio_enc_encode_frame(p_input_samples, framesize, (unsigned char*)p_output_bytes);
        //prn_encoded_buffer(p_output_bytes, encoded_bytes);
#ifndef REPEAT_FIRST_FRAME   // repeat same freme for test purpose 
        p_input_samples += framesize;  
#endif
        p_output_bytes += encoded_bytes;
        
        output_bytes_produced += encoded_bytes;
        input_samples_processed += framesize;
        if(output_bytes_produced >= sizeof(encoded_buffer))
        {
          printf("encoded buffer space full, %d(0x%0X) bytes output saved at 0x%0X  to 0x%0X.  Exitting... \n", output_bytes_produced, output_bytes_produced, encoded_buffer, encoded_buffer + output_bytes_produced);
          break;
        }else if(input_samples_processed >= MAX_INPUT_SAMPLE )
        {
           printf("input buffer empty, %d(0x%0X) bytes output saved at 0x%0X  to 0x%0X.  Exitting... \n", output_bytes_produced, output_bytes_produced, encoded_buffer, encoded_buffer + output_bytes_produced);
           break;         
          
        }else
        {
          frame_count++;
          if((frame_count&63) == 0)
          {
            printf(".");
          }
        }
        am_util_stdio_printf("%d ", g_ui32TimerCount & 0x7);
        if ( (g_ui32TimerCount & ((1 << NUM_LEDS) - 1)) == 0 )
        {
            // example here, only to prevent data array from being optimized by linker
            if(p_pcm_samples[g_ui32TimerCount] != 0x00)
            {
                am_util_stdio_printf("\n");
            }
        }

        //
        // example of gpio toggling
        //
        am_hal_gpio_pinconfig(35, g_AM_HAL_GPIO_OUTPUT);    // no need to call this in a loop... only for example
        am_hal_gpio_output_set(35);                         // set gpio35 to high
        am_util_delay_ms(2);                                // blocking delay 10ms
        am_hal_gpio_output_clear(35);                       // set gpio35 to low
        am_util_delay_us(200);                              // blocking delay for 200us
        am_hal_gpio_output_toggle(35);                      // toggle gpio35 output
        am_util_delay_us(500);                              // blocking delay for 500us
        am_hal_gpio_output_toggle(35);                      // toggle gpio35 output
        //
        // We are done printing. Disable debug printf messages on ITM.
        //
        am_bsp_debug_printf_disable();
    }
}
