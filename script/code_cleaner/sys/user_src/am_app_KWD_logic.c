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

//*****************************************************************************
// Global includes for this project.
//
//*****************************************************************************
#include "usr_include.h"

#if VOS_MAYA_BOARD

#include "am_app_KWD_task.h"
#include "am_app_KWD_logic.h"

bool g_LogicButtonWakeUp = false;
enum_logic_power_states_t g_LogicPowerState = APP_LOGIC_POWERING_UP;

void am_app_logic_led_all_on(void)
{
    //LEDs on
    am_hal_gpio_state_write(LED_D1, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D2, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D3, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D4, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_SET);
}

void am_app_logic_led_all_off(void)
{
    //LEDs off
    am_hal_gpio_state_write(LED_D1, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D2, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D3, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D4, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_CLEAR);
}

void am_app_logic_led_swirl(uint8_t type)
{
    TickType_t xDelaySwirl = pdMS_TO_TICKS(50);
    switch(type)
    {
        case 0: // keyword detection
        break;
        case 1: // power up
            am_hal_gpio_state_write(LED_D1, AM_HAL_GPIO_OUTPUT_SET);
            vTaskDelay(xDelaySwirl);
            am_hal_gpio_state_write(LED_D2, AM_HAL_GPIO_OUTPUT_SET);
            vTaskDelay(xDelaySwirl);
            am_hal_gpio_state_write(LED_D3, AM_HAL_GPIO_OUTPUT_SET);
            vTaskDelay(xDelaySwirl);
            am_hal_gpio_state_write(LED_D4, AM_HAL_GPIO_OUTPUT_SET);
            am_hal_gpio_state_write(LED_D1, AM_HAL_GPIO_OUTPUT_CLEAR);
            vTaskDelay(xDelaySwirl);
            am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_SET);
            am_hal_gpio_state_write(LED_D2, AM_HAL_GPIO_OUTPUT_CLEAR);
            vTaskDelay(xDelaySwirl);
            am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_SET);
            am_hal_gpio_state_write(LED_D3, AM_HAL_GPIO_OUTPUT_CLEAR);
            vTaskDelay(xDelaySwirl);
            am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_SET);
            am_hal_gpio_state_write(LED_D4, AM_HAL_GPIO_OUTPUT_CLEAR);
            vTaskDelay(xDelaySwirl);
            am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_SET);
            am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_CLEAR);
            vTaskDelay(xDelaySwirl);

            am_hal_gpio_state_write(LED_D1, AM_HAL_GPIO_OUTPUT_SET);
            am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_CLEAR);
            vTaskDelay(xDelaySwirl);
            am_hal_gpio_state_write(LED_D2, AM_HAL_GPIO_OUTPUT_SET);
            am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_CLEAR);
            vTaskDelay(xDelaySwirl);
            am_hal_gpio_state_write(LED_D3, AM_HAL_GPIO_OUTPUT_SET);
            am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_CLEAR);
            vTaskDelay(xDelaySwirl);
            am_hal_gpio_state_write(LED_D4, AM_HAL_GPIO_OUTPUT_SET);
            am_hal_gpio_state_write(LED_D1, AM_HAL_GPIO_OUTPUT_CLEAR);
            vTaskDelay(xDelaySwirl);
            am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_SET);
            am_hal_gpio_state_write(LED_D2, AM_HAL_GPIO_OUTPUT_CLEAR);
            vTaskDelay(xDelaySwirl);
            am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_SET);
            am_hal_gpio_state_write(LED_D3, AM_HAL_GPIO_OUTPUT_CLEAR);
            vTaskDelay(xDelaySwirl);
            am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_SET);
            am_hal_gpio_state_write(LED_D4, AM_HAL_GPIO_OUTPUT_CLEAR);
            vTaskDelay(xDelaySwirl);
            am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_SET);
            am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_CLEAR);
            vTaskDelay(xDelaySwirl);

            am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_CLEAR);
            vTaskDelay(xDelaySwirl);
            am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_CLEAR);
            vTaskDelay(xDelaySwirl);
            am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_CLEAR);
            vTaskDelay(xDelaySwirl);

            am_hal_gpio_state_write(LED_D1, AM_HAL_GPIO_OUTPUT_CLEAR);
            am_hal_gpio_state_write(LED_D2, AM_HAL_GPIO_OUTPUT_CLEAR);
            am_hal_gpio_state_write(LED_D3, AM_HAL_GPIO_OUTPUT_CLEAR);
            am_hal_gpio_state_write(LED_D4, AM_HAL_GPIO_OUTPUT_CLEAR);
            am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_CLEAR);
            am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_CLEAR);
            am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_CLEAR);
            am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_CLEAR);
        break;
        case 2: // power down
        break;
        default:
            // do nothing
        break;

    }
}

//*****************************************************************************
//
// Simple button detection function with debounce
//
//*****************************************************************************
static bool logic_check_button(void)
{
    uint32_t pinVal = 0;

    for(uint8_t i = 0; i < 3 ; i++)
    {
        pinVal = am_hal_gpio_input_read(CTRL_BUTTON3);
        if(pinVal)
        {
            return false;
        }
        am_util_delay_us(100);
    }

    return true;
}


static bool logic_check_button2(void)
{
    uint32_t pinVal = 0;

    for(uint8_t i = 0; i < 6 ; i++)
    {
        pinVal = am_hal_gpio_input_read(CTRL_BUTTON2);
        if(pinVal)
        {
            return false;
        }
        am_util_delay_us(100);
    }

    return true;
}


void am_app_logic_button_init(void)
{
    const am_hal_gpio_pincfg_t CFG_CTRL_BUTTON =
    {
        .uFuncSel       = 3,
        .eGPOutcfg      = AM_HAL_GPIO_PIN_OUTCFG_DISABLE,
        .eGPInput       = AM_HAL_GPIO_PIN_INPUT_ENABLE,
        .eGPRdZero      = AM_HAL_GPIO_PIN_RDZERO_READPIN,
        .eIntDir        = AM_HAL_GPIO_PIN_INTDIR_HI2LO,
    };

    g_LogicButtonWakeUp = false;

    am_hal_gpio_pinconfig(CTRL_BUTTON3, CFG_CTRL_BUTTON);
    NVIC_SetPriority(GPIO_IRQn, NVIC_configKERNEL_INTERRUPT_PRIORITY);
    am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
    NVIC_EnableIRQ(GPIO_IRQn);
}

void am_app_logic_button_process(void)
{
    // disable interrupt on this pin

    if(logic_check_button())
    {
        if(g_LogicPowerState == APP_LOGIC_POWER_ON)
        {
            am_hal_gpio_interrupt_disable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
            am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON3));

            // button pressed, send a msg to shut down the system
            am_app_utils_task_send_fromISR(AM_APP_TASK_LOGIC, AM_APP_TASK_LOGIC, AM_APP_MESSAGE_SHORT, EMPTY_MESSAGE, NULL);
        }
    }
}

static uint8_t button2_working = 0;
void am_app_logic_button2_process(void)
{
    //am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON2));

    if (button2_working == 1)
        return;

    button2_working = 1;
    

    if (logic_check_button2())
    {   
      am_hal_gpio_interrupt_disable(AM_HAL_GPIO_BIT(CTRL_BUTTON2));
    
        #if VOS_configUSE_GSENSOR
            am_app_gsensor_button2_process();
        #endif    

        #if VOS_configUSE_PUSH_TO_TALK
            am_app_KWD_reset_detected_flag();
            g_ui8PushTalkFlag = 1;
            
            am_app_utils_task_send_fromISR(AM_APP_ISR_GPIO, AM_APP_TASK_LED, AM_APP_MESSAGE_SHORT, EMPTY_MESSAGE, NULL);
            //xTimerStart(am_KWD_timers[AM_APP_TIMER_KWD_TIME_OUT], 0);    
        #endif
      //am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON2));      
    }

    button2_working = 0;
}


void am_app_logic_system_power_off(void)
{
    //
    // Disable all interrupts
    //
//    am_hal_interrupt_master_disable();

    for(uint8_t i = 0; i < 32; i++)
    {
        NVIC_DisableIRQ(i);         // disable all IRQs
        NVIC_ClearPendingIRQ(i);    // clear all pending IRQs
    }

    //
    // Suspend all tasks
    // 
    vTaskSuspendAll();

    //
    // Stop Stimer
    //
    am_hal_stimer_config(AM_HAL_STIMER_CFG_CLEAR | AM_HAL_STIMER_CFG_FREEZE);

    //
    // Turn off peripherals
    //
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_IOS);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_IOM0);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_IOM1);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_IOM2);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_IOM3);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_IOM4);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_IOM5);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_UART0);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_UART1);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_ADC);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_SCARD);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_MSPI);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_PDM);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_BLEL);

    //
    // Turn OFF Flash1
    //
    if ( am_hal_pwrctrl_memory_enable(AM_HAL_PWRCTRL_MEM_FLASH_512K) )
    {
    }

    //
    // Power down SRAM
    //
    //PWRCTRL->MEMPWDINSLEEP_b.SRAMPWDSLP = PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_ALLBUTLOWER32K;


    // GPIO12 (PDMC) set to low
    am_hal_gpio_pinconfig(PDM_CLK, g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_state_write(PDM_CLK, AM_HAL_GPIO_OUTPUT_CLEAR);

    // GPIO38 (nSPK_POWER) set to low
    am_hal_gpio_pinconfig(BUZZER_CAP_PWR_PIN, g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_state_write(BUZZER_CAP_PWR_PIN, AM_HAL_GPIO_OUTPUT_CLEAR);

    // IOM1 I2C IOs output high
    am_hal_gpio_pinconfig(8, g_AM_HAL_GPIO_OUTPUT);    // scl
    am_hal_gpio_pinconfig(9, g_AM_HAL_GPIO_OUTPUT);    // sda
    am_hal_gpio_pinconfig(7, g_AM_HAL_GPIO_DISABLE);   // int1
    am_hal_gpio_state_write(8, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(9, AM_HAL_GPIO_OUTPUT_SET);
//    am_hal_gpio_state_write(7, AM_HAL_GPIO_OUTPUT_CLEAR);

    // Disable all other GPIOs
    am_hal_gpio_pinconfig(LED_D1, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(LED_D2, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(LED_D3, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(LED_D4, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(LED_D5, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(LED_D6, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(LED_D7, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(LED_D8, g_AM_HAL_GPIO_DISABLE);

    am_hal_gpio_pinconfig(CTRL_BUTTON2, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(PDM_DATA, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(BUZZER_PWM_OUTPUT_PIN, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(4, g_AM_HAL_GPIO_DISABLE);    // wake
    am_hal_gpio_pinconfig(49, g_AM_HAL_GPIO_DISABLE);   // mode
//    am_hal_gpio_pinconfig(7, g_AM_HAL_GPIO_DISABLE);    // int1
//    am_hal_gpio_pinconfig(8, g_AM_HAL_GPIO_DISABLE);    // scl
//    am_hal_gpio_pinconfig(9, g_AM_HAL_GPIO_DISABLE);    // sda
    am_hal_gpio_pinconfig(17, g_AM_HAL_GPIO_DISABLE);   // optional button
    am_hal_gpio_pinconfig(22, g_AM_HAL_GPIO_DISABLE);   // tx0
    am_hal_gpio_pinconfig(23, g_AM_HAL_GPIO_DISABLE);   // rx0
    am_hal_gpio_pinconfig(33, g_AM_HAL_GPIO_DISABLE);   // amic audio out
    am_hal_gpio_pinconfig(41, g_AM_HAL_GPIO_DISABLE);   // swo

    //
    // enable only button interrupt
    //
}

#endif
