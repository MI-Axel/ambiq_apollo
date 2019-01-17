/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

/* This file is the main file of the audio experiment platform. */

#include <stdint.h>
#include "am_bsp.h"
#include "am_mcu_apollo.h"  // Defines AM_CMSIS_REGS
#include "am_util.h"

#include "board_setup.h"
#include "audio_driver.h"
/* app utils include file */
//#include "am_app_utils.h"
/* opus include file */
//#include "am_opus_config.h"

//#include "opus.h"
//#include "debug.h"
//#include "opus_types.h"
//#include "opus_private.h"
//#include "opus_multistream.h"

#define ARM_MATH_CM4
#include <arm_math.h>

q7_t g_scores[4] = {0};


int main(void)
{
    am_util_id_t sIdDevice;
    uint32_t ui32StrBuf;
    
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
    
    // Turn on PDM
    pdm_init();
    
    //
    // Initialize the printf interface for UART output
    //
    am_bsp_uart_printf_enable();
    
    //
    // Print the banner.
    //
//    am_util_stdio_terminal_clear();
    DebugLog("Starting streaming test\r\n\n");
    //
    // Start timer A0
    //
    am_hal_ctimer_start(0, AM_HAL_CTIMER_TIMERA);

    // Score variables
//    q7_t max_score = 0;
//    uint32_t max_score_index = 0;
    
    while (1)
    {
//        am_hal_interrupt_master_disable();

         if (g_bPDMDataReady) 
        {
            g_bPDMDataReady = false;
            g_numFramesCaptured++;

            if (g_numFramesCaptured < NUM_FRAMES) 
            {
                pdm_data_get();  // Start converting the next set of PCM samples.
            }

            else 
            {
                g_numFramesCaptured = 0;
                g_audioRunningFlag = 0;
                am_hal_pdm_disable(PDMHandle);
                am_devices_led_off(am_bsp_psLEDs, 0);
                DebugLog("PDM data recording ends!\r\n");
            }
        }
        if (g_ui32TimerCount >=1)
        {
            g_ui32TimerCount = 0;
            am_devices_led_toggle(am_bsp_psLEDs, 1);
        
        }
    //
    // Go to Deep Sleep.
    //
        am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_DEEP);

//        am_hal_interrupt_master_enable();
    }

}
