//*****************************************************************************
//
//! @file am_app_utils_lowpower.c
//!
//! @brief low power functions for core and peripherals
//!
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
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
// This is part of revision v1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************
/*******************************************************************************
*
********************************************************************************
*     am_app_utils_lowpower.c
********************************************************************************
*
*     Description: low power functions of core and peripherals
*
*******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
//*****************************************************************************
//
// Standard AmbiqSuite includes.
//
//*****************************************************************************
#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_devices.h"
#include "am_util.h"

//*****************************************************************************
//
// FreeRTOS include files.
//
//*****************************************************************************
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "queue.h"
#include "FreeRTOSConfig.h"

#include "am_app_utils_lowpower.h"

//*****************************************************************************
//
// Configure IOM for sleep
//
//*****************************************************************************
void
configure_iom_sleep(uint32_t IOMmodule)
{
    //
    // Power down IOM
    //
    am_hal_iom_disable(IOMmodule);

    //
    // Power off the IOM, and save its configuration to SRAM.
    //
//    am_hal_iom_power_off_save(IOM0);

    //
    // Re-configure SPI pins during sleep
    //
//    am_hal_gpio_pin_config(SPI_SCK_GPIO, AM_HAL_PIN_DISABLE);
//    am_hal_gpio_pin_config(SPI_MISO_GPIO, AM_HAL_PIN_OUTPUT);
//    am_hal_gpio_pin_config(SPI_MOSI_GPIO, AM_HAL_PIN_OUTPUT);
//    am_hal_gpio_pin_config(SPI_CS_GPIO, AM_HAL_PIN_DISABLE);
//    am_hal_gpio_out_bit_set(SPI_MISO_GPIO);
//    am_hal_gpio_out_bit_set(SPI_MOSI_GPIO);
}


//*****************************************************************************
//
// Sleep function called from FreeRTOS IDLE task.
// Do necessary application specific Power down operations here
// Return 0 if this function also incorporates the WFI, else return value same
// as idleTime
//
//*****************************************************************************
uint32_t am_freertos_sleep(uint32_t idleTime)
{
//#if USE_OUTPUT_BUFFER_SPI
//    if (am_hal_iom_fifo_full_slots(IOM0 == 0x00))
//    {
//       configure_iom_sleep(0);
//    }
//#endif
//#if USE_OUTPUT_BUFFER_UART0
//    uint32_t TxBuff;
//    uint32_t RxBuff;
//    am_hal_uart_get_status_buffered(0, &RxBuff, &TxBuff);
//    if (TxBuff == 0)
//    {
//        configure_uart_sleep(0);
//    }
//#endif
//#if USE_OUTPUT_BUFFER_UART1
//    uint32_t TxBuff;
//    uint32_t RxBuff;
//    am_hal_uart_get_status_buffered(0, &RxBuff, &TxBuff);
//    if (TxBuff == 0)
//    {
//       configure_uart_sleep(1);
//    }
//#endif

    am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_DEEP);
    return 0;
}

//*****************************************************************************
//
// Configure UART pins for sleep
//
//*****************************************************************************
void
configure_uart_sleep(uint32_t uartmodule)
{
    //
    // Disable the UART clock.
    //
    am_hal_uart_clock_disable(uartmodule);

    //
    // Clear all interrupts before sleeping as having a pending UART interrupt
    // burns power.
    //
    am_hal_uart_int_clear(uartmodule, 0xFFFFFFFF);
    am_hal_uart_int_disable(uartmodule, AM_HAL_UART_INT_RX_TMOUT |
                                       AM_HAL_UART_INT_RX |
                                       AM_HAL_UART_INT_TXCMP);

    //
    // Disable the UART.
    //
    am_hal_uart_disable(uartmodule);

    //
    // Disable the UART pins.
    //
//    if (uartmodule == 0)
//    {
//        am_hal_gpio_pin_config(22, AM_HAL_PIN_OUTPUT);
//        am_hal_gpio_pin_config(23, AM_HAL_PIN_OUTPUT);
//        am_bsp_pin_disable(COM_UART_TX);        // pin 22
//        am_bsp_pin_disable(COM_UART_RX);	// pin 23
//    }
//    else
//    {
//        am_hal_gpio_pin_config(39, AM_HAL_PIN_OUTPUT);
//        am_hal_gpio_pin_config(40, AM_HAL_PIN_OUTPUT);
//        am_hal_gpio_pin_config(39, AM_HAL_PIN_DISABLE);
//        am_hal_gpio_pin_config(40, AM_HAL_PIN_DISABLE);
//    }

}

#if USE_WAKE_ON_SOUND
void kwd_pdm_enable(void)
{
    am_hal_gpio_out_bit_clear(WOS_MODE_PIN);

    am_hal_pwrctrl_periph_enable(AM_HAL_PWRCTRL_PDM);

    //
    // Configure the PDM microphone pins
    //
    am_hal_gpio_pin_config(PDM_CLK, PDM_CLK_PIN_CFG); // Configure GP12 as PDM clock pin output (Need to blue-wire on REV4 Shield)
    am_hal_gpio_pin_config(PDM_DATA, PDM_DATA_PIN_CFG);// Configure GP11/GP23 as PDM data pin for unmodified Shield

    //
    // Configure the PDM module
    //
    PDMregConfig();
    //
    // Make sure interrupts are clear
    //
    AM_REG(PDM, INTCLR) = 0x7;
    AM_REG(PDM, FLUSH) = 0x1;                       // Reset FIFO pointers
    //
    // Enable interrupts PDM
    //
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_PDM);  //NVIC setting
    am_hal_pdm_int_enable(AM_HAL_PDM_INT_FIFO | AM_HAL_PDM_INT_UNDFL | AM_HAL_PDM_INT_OVF);
    am_hal_interrupt_priority_set(AM_HAL_INTERRUPT_PDM, AM_HAL_INTERRUPT_PRIORITY(4));

    am_hal_pdm_enable(); // enable the PDM mic interface

    return;
}

void kwd_pdm_disable(void)
{
	//Power Down PDM interface for WOS
	am_hal_pdm_disable();
	am_hal_gpio_pin_config(PDM_CLK, AM_HAL_PIN_DISABLE); // Disable PDM clk pin
	am_hal_gpio_pin_config(PDM_DATA, AM_HAL_PIN_DISABLE);  //Disable PDM data pin
	
	//Power Down PDM interface to further reduce power
	am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PDM);
	am_hal_gpio_out_bit_set(WOS_MODE_PIN);

    return;
}

#endif    // USE_WAKE_ON_SOUND

