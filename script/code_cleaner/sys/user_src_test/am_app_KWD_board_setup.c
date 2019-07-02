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
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************

/*FILE START*/

/*******************************************************************************
********************************************************************************
*     BoardSetup.c
********************************************************************************
*
*     Description:  Setup board peripherals
*
*******************************************************************************/
#include "usr_include.h"


uint8_t g_PDMfifoFlag = 0;

/*{{{*/
#if (VOS_configUSE_LOG_UART0 || VOS_configUSE_PRINTF_UART0|| VOS_configUSE_AWE_TUNING)
    uint8_t g_pui8UartRxBuffer0[UART0_BUFFER_SIZE];
    uint8_t g_pui8UartTxBuffer0[UART0_BUFFER_SIZE];
    char pcTempBuf0[UART0_BUFFER_SIZE + 1];
#endif    // (VOS_configUSE_LOG_UART0||VOS_configUSE_PRINTF_UART0||VOS_configUSE_AWE_TUNING)
/*}}}*/

/*{{{*/
#if VOS_configUSE_LOG_UART1
    uint8_t g_pui8UartRxBuffer1[UART1_BUFFER_SIZE];
    uint8_t g_pui8UartTxBuffer1[UART1_BUFFER_SIZE];
    char pcTempBuf1[UART1_BUFFER_SIZE + 1];
#endif    // VOS_configUSE_LOG_UART1
/*}}}*/


void SystemClock_Config(void);
void ApolloConfigPeripherals(void);
static void GPIO_Init(void);
void kwd_ctimer_handler(void);
void kwd_button_handler(void);
void sleep_button_handler(void);
void WOS_handler(void);

//*****************************************************************************
//
// C Timer configurations
//
//*****************************************************************************
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

    // Set up Timer0A.
    (AM_HAL_CTIMER_FN_ONCE |
     AM_HAL_CTIMER_INT_ENABLE    |
	 AM_HAL_CTIMER_HFRC_12KHZ),

    // No configuration for Timer0B.
    0,
};
#if defined (PWM_RAMP)
am_hal_ctimer_config_t g_cTimersPWM =
{
    // Don't link timers.
    0,

    // Set up TimerA.
    (AM_HAL_CTIMER_FN_PWM_REPEAT |
     AM_HAL_CTIMER_PIN_ENABLE    |
	 AM_HAL_CTIMER_HFRC_12KHZ),

    // Set up TimerB.
    (AM_HAL_CTIMER_FN_PWM_REPEAT |
     AM_HAL_CTIMER_PIN_ENABLE    |
	 AM_HAL_CTIMER_HFRC_12KHZ),
};
#endif    // defined(PWM_RAMP)

//*****************************************************************************
//
// Init function for Timer 0.
//
//*****************************************************************************
void
timer0_init(void)
{
    //
    // Set up timer A0
    //
    am_hal_ctimer_clear(0, AM_HAL_CTIMER_BOTH);
    am_hal_ctimer_config(0, &g_cTimer0);

    am_hal_ctimer_start(0, AM_HAL_CTIMER_BOTH);

}

//*****************************************************************************
//
// Init function for Timer 1A.
//
//*****************************************************************************
//void
//timer1A_init(void)
//{
//    uint32_t ui32Period = CMD_TIMEOUT_PERIOD;
//    //
//    // Set up timer 1A
//    //
//    am_hal_ctimer_clear(1, AM_HAL_CTIMER_TIMERA);
//    am_hal_ctimer_config(1, &g_cTimer1);
//
//    //
//    // Set up timer 1A to count to 24ms with 12Khz clock.
//    //
//    am_hal_ctimer_period_set(1, AM_HAL_CTIMER_TIMERA, ui32Period,
//                             (ui32Period));
//    am_hal_ctimer_int_register(KWD_CTIMER_INT, kwd_ctimer_handler);
//    am_hal_ctimer_int_enable(AM_HAL_CTIMER_INT_TIMERA1);
//    am_hal_ctimer_int_clear(AM_HAL_CTIMER_INT_TIMERA1);
//}
//
//*****************************************************************************
//
// Init All Timers for PWM.
//
//*****************************************************************************
#if PWM_RAMP
void InitAllTimersForPWM(void)
{
    uint8_t TimerIndex = 0;

    for (TimerIndex = 0; TimerIndex < FOUR_TIMERS; TimerIndex++)
    {
        //config timers
        am_hal_ctimer_config(TimerIndex, &g_cTimersPWM);
        // invert pin
        am_hal_ctimer_pin_invert(TimerIndex, AM_HAL_CTIMER_TIMERA, 1);
        am_hal_ctimer_pin_invert(TimerIndex, AM_HAL_CTIMER_TIMERB, 1);
        // set initial periods
        am_hal_ctimer_period_set(TimerIndex, AM_HAL_CTIMER_TIMERA, \
                                 (LED_RAMP_TIME * 2), LED_RAMP_TIME);
        am_hal_ctimer_period_set(TimerIndex, AM_HAL_CTIMER_TIMERB, \
                                 (LED_RAMP_TIME * 2), LED_RAMP_TIME);
    }
}
#endif    // PWM_RAMP

#if USE_ANALOG_MIC
//*****************************************************************************
//
// Configure the ADC.
//
//*****************************************************************************
void
adc_config(void)
{
    am_hal_adc_config_t sADCConfig;

    //
    // Enable the ADC power domain.
    //
    am_hal_pwrctrl_periph_enable(AM_HAL_PWRCTRL_ADC);

    //
    // Set up the ADC configuration parameters.
    //
    sADCConfig.ui32Clock = AM_HAL_ADC_CLOCK_HFRC;
    sADCConfig.ui32TriggerConfig = AM_HAL_ADC_TRIGGER_SOFT;
    sADCConfig.ui32Reference = AM_HAL_ADC_REF_INT_1P5;
    sADCConfig.ui32ClockMode = AM_HAL_ADC_CK_LOW_POWER;
    sADCConfig.ui32PowerMode = AM_HAL_ADC_LPMODE_0;
    sADCConfig.ui32Repeat = AM_HAL_ADC_REPEAT;

    am_hal_adc_config(&sADCConfig);

    //
    // FIFOOVR1 interrupt enabled.. every 12 samples go empty the FIFO
    //
		am_hal_adc_int_clear(AM_HAL_ADC_INT_FIFOOVR1);
		am_hal_adc_int_enable(AM_HAL_ADC_INT_FIFOOVR1);

    //
    // Set up an ADC slot
    //
    am_hal_adc_slot_config(0, AM_HAL_ADC_SLOT_AVG_1 |
                              AM_HAL_ADC_SLOT_14BIT |
                              ADC_SLOT_CH_SEL |
                              AM_HAL_ADC_SLOT_ENABLE);
    //
    // Enable the ADC.
    //
    am_hal_adc_enable();
}


//*****************************************************************************
//
// Start sampling
//
//*****************************************************************************
void
Init_ADC(void)
{
    am_hal_ctimer_config_single(3, AM_HAL_CTIMER_TIMERA,
                                   AM_HAL_CTIMER_HFRC_12MHZ |
                                   AM_HAL_CTIMER_FN_REPEAT |
				   AM_HAL_CTIMER_PIN_ENABLE |
                                   AM_HAL_CTIMER_INT_ENABLE);

		am_hal_ctimer_int_enable(AM_HAL_CTIMER_INT_TIMERA3);

//		am_hal_ctimer_period_set(3, AM_HAL_CTIMER_TIMERA, 375, 186);  //12M/375=32ksps
		am_hal_ctimer_period_set(3, AM_HAL_CTIMER_TIMERA, 750, 325);  //12M/750=16ksps
    //
    // Enable the timer A3 to trigger the ADC directly
    //
    am_hal_ctimer_adc_trigger_enable();

    //
    // Start the timer.
    //
    am_hal_ctimer_start(3, AM_HAL_CTIMER_TIMERA);
}
#endif    // USE_ANALOG_MIC


//*****************************************************************************
//
// PDM Configuration
//
//*****************************************************************************
//void PDMregConfig(void)
//{
//    am_hal_pdm_config_t g_sPDM_Cfg =
//    {
//        //
//        // uint32_t ui32PDMConfigReg
//        // PDM Configuration (PCFG, PDMCFG) register
//        // Notes:
//        //  Choose from AM_HAL_PDM_PCFG macros.
//        //  For completeness, all PCFG fields should be referenced here.
//        //
//        (
//                #if (USE_A2BLUE_AND_VESPER_MIKRO_MB3 || USE_A2_A3_AND_VESPER_MIKRO_MB3 || USE_A2BLUE_AND_ST_MICS_MIKRO_MB3 || USE_A2_A3_AND_ST_MICS_MIKRO_MB3)
//                  AM_HAL_PDM_PCFG_LRSWAP_ENABLE     |
//                #else
//                  AM_HAL_PDM_PCFG_LRSWAP_DISABLE    |
//                #endif
//                AM_HAL_PDM_PCFG_RIGHT_PGA_P105DB    |	// +10.5dB gain
//                AM_HAL_PDM_PCFG_LEFT_PGA_P105DB     |	// +10.5dB gain
//                AM_HAL_PDM_PCFG_MCLKDIV_DIV1        |
//                AM_HAL_PDM_PCFG_SINC_RATE(24)       |   // over sample rate (decimation)
//                AM_HAL_PDM_PCFG_HPCUTOFF(0xB)       |
//                AM_HAL_PDM_PCFG_SOFTMUTE_DISABLE    |
//                AM_HAL_PDM_PCFG_PDMCORE_DISABLE
//        ),
//
//        //
//        // uint32_t ui32VoiceConfigReg
//        // PDM Voice Config (VCFG, VOICECFG) register
//        // Notes:
//        //  Choose from AM_HAL_PDM_VCFG macros.
//        //  For completeness, all VCFG fields should be referenced here.
//        //  AM_HAL_PDM_IOCLK_xxx also sets AM_REG_PDM_VCFG_IOCLKEN_EN
//        //  RSTB is set to NORMAL by am_hal_pdm_enable.
//        //
//        (
//                AM_HAL_PDM_IOCLK_750KHZ             |   // AM_REG_PDM_VCFG_IOCLKEN_EN
//                AM_HAL_PDM_VCFG_RSTB_RESET          |
//                AM_HAL_PDM_VCFG_PDMCLK_ENABLE       |
//                AM_HAL_PDM_VCFG_I2SMODE_DISABLE     |
//                AM_HAL_PDM_VCFG_BCLKINV_DISABLE     |
//                AM_HAL_PDM_VCFG_DMICDEL_0CYC        |
//                AM_HAL_PDM_VCFG_SELAP_INTERNAL      |
//                AM_HAL_PDM_VCFG_PACK_ENABLE         |
//                AM_HAL_PDM_VCFG_CHANNEL_STEREO
//        ),
//
//        //
//        // uint32_t ui32FIFOThreshold
//        // The PDM controller will generate a processor interrupt when the number
//        // of entries in the FIFO goes *above* this number.
//        //
//        (AWE_FRAME_SIZE - 1)
//    };
//
//    am_hal_pdm_config(&g_sPDM_Cfg);
//
//}
//
#if USE_OUTPUT_BUFFER_SPI
//-----------------------------------------------------------------------------
// METHOD:  spi_init
// PURPOSE: Setup SPI
//-----------------------------------------------------------------------------
void spi_init(void)
{
    const am_hal_iom_config_t g_sIOMConfig =
    {
        .ui32InterfaceMode = AM_HAL_IOM_SPIMODE,
        .ui32ClockFrequency = AM_HAL_IOM_12MHZ,
        .ui8WriteThreshold = 4,
        .ui8ReadThreshold = 16,
        .bSPHA = 0,
        .bSPOL = 0,
    };

//    // set up spi queue
//    // Declare an array to be used for IOM queue transactions. This array will
//    // be big enough to handle 32 IOM transactions.
//    am_hal_iom_queue_entry_t g_psQueueMemory[256];
//    //
//    // Attach the IOM0 queue system to the memory we just allocated.
//    //
//    am_hal_iom_queue_init(0, g_psQueueMemory, sizeof(g_psQueueMemory));

    am_hal_iom_pwrctrl_enable(IOM0);
    am_hal_iom_config(IOM0, &g_sIOMConfig);

    am_hal_iom_enable(IOM0);
    am_hal_iom_int_clear(IOM0, AM_HAL_IOM_INT_CMDCMP | AM_HAL_IOM_INT_THR);
    am_hal_iom_int_enable(IOM0, AM_HAL_IOM_INT_CMDCMP | AM_HAL_IOM_INT_THR);
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_IOMASTER0);
}
#endif    // USE_OUTPUT_BUFFER_SPI

#if defined (AM_PART_APOLLO3)
//*****************************************************************************
//
// UART handle.
//
//*****************************************************************************
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
uint8_t g_pui8TxBuffer[256];
uint8_t g_pui8RxBuffer[2];

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
#endif    // defined(AM_PART_APOLLO3)

//-----------------------------------------------------------------------------
// METHOD:  uart_init
// PURPOSE: Setup UART0 and/or UART1
//-----------------------------------------------------------------------------
void uart_init(uint32_t ui32Module)
{
/*{{{*/
#if (VOS_configUSE_LOG_UART0 || VOS_configUSE_PRINTF_UART0 || VOS_configUSE_AWE_TUNING)
#if defined (AM_PART_APOLLO2)
static am_hal_uart_config_t g_sUart0Config =
    {
        .ui32BaudRate    = 460800,
        .ui32DataBits    = AM_HAL_UART_DATA_BITS_8,
        .bTwoStopBits    = false,
        .ui32Parity      = AM_HAL_UART_PARITY_NONE,
        .ui32FlowCtrl    = AM_HAL_UART_FLOW_CTRL_NONE,
    };

#endif    // defined(AM_PART_APOLLO2)

#if defined (AM_PART_APOLLO3)
    am_hal_gpio_pinconfig(AM_BSP_GPIO_COM_UART_TX, g_AM_BSP_GPIO_COM_UART_TX);
    am_hal_gpio_pinconfig(AM_BSP_GPIO_COM_UART_RX, g_AM_BSP_GPIO_COM_UART_RX);
#endif    // defined(AM_PART_APOLLO3)
#endif    // (VOS_configUSE_LOG_UART0||VOS_configUSE_PRINTF_UART0||VOS_configUSE_AWE_TUNING)
/*}}}*/

/*{{{*/    
#if VOS_configUSE_LOG_UART1
    static am_hal_uart_config_t g_sUart1Config =
    {
        .ui32BaudRate    = 460800,
        .ui32DataBits    = AM_HAL_UART_DATA_BITS_8,
        .ui32StopBits    = AM_HAL_UART_ONE_STOP_BIT,
        .ui32Parity      = AM_HAL_UART_PARITY_NONE,
        .ui32FlowControl = AM_HAL_UART_FLOW_CTRL_NONE,
    };
    if (ui32Module == 1)
    {
      // GW: Added for EM9304 Mikro board support
#if USE_A2_A3_AND_EM9304_MIKRO_MB2
        am_hal_gpio_pin_config(35, AM_HAL_PIN_35_UART1TX);
        am_hal_gpio_pin_config(13, AM_HAL_PIN_13_UART1RX);
#else    // USE_A2_A3_AND_EM9304_MIKRO_MB2
        am_hal_gpio_pin_config(39, AM_HAL_PIN_39_UART1TX);
        am_hal_gpio_pin_config(40, AM_HAL_PIN_40_UART1RX);
#endif    // USE_A2_A3_AND_EM9304_MIKRO_MB2
    }
#endif    // VOS_configUSE_LOG_UART1

/*}}}*/
#if defined (AM_PART_APOLLO2)
    am_hal_uart_pwrctrl_enable(ui32Module);     // Power on the selected UART
    am_hal_uart_clock_enable(ui32Module);       // start UART interface and enable the FIFOs.
    am_hal_uart_disable(ui32Module);            // Disable the UART before configuring it.

/*{{{*/    
#if (VOS_configUSE_LOG_UART0 || VOS_configUSE_PRINTF_UART0 || VOS_configUSE_AWE_TUNING)
    if (ui32Module == 0)
    {
        am_hal_uart_config(ui32Module, &g_sUart0Config);
        am_hal_uart_init_buffered(ui32Module, g_pui8UartRxBuffer0, UART0_BUFFER_SIZE,
                                    g_pui8UartTxBuffer0, UART0_BUFFER_SIZE);
    }

    //
    // Enable the UART pins.
    //
    am_hal_gpio_pin_config(22, AM_HAL_PIN_22_UART0TX);
    am_hal_gpio_pin_config(17, AM_HAL_PIN_17_UART0RX);

#endif    // (VOS_configUSE_LOG_UART0||VOS_configUSE_PRINTF_UART0||VOS_configUSE_AWE_TUNING)
/*}}}*/


/*{{{*/    
#if VOS_configUSE_LOG_UART1
    if (ui32Module == 1)
    {
          am_hal_uart_config(ui32Module, &g_sUart1Config);
          am_hal_uart_init_buffered(ui32Module, g_pui8UartRxBuffer1, UART1_BUFFER_SIZE,
                                    g_pui8UartTxBuffer1, UART1_BUFFER_SIZE);
    }
#endif    // VOS_configUSE_LOG_UART1
/*}}}*/    

    //
    // Configure the UART FIFO.
    //
    am_hal_uart_fifo_config(ui32Module, AM_HAL_UART_TX_FIFO_1_2 | AM_HAL_UART_RX_FIFO_1_2);

#endif    // defined(AM_PART_APOLLO2)

#if defined (AM_PART_APOLLO3)
    //
    // Initialize the printf interface for UART output.
    //
    CHECK_ERRORS(am_hal_uart_initialize(0, &g_sCOMUART));
    CHECK_ERRORS(am_hal_uart_power_control(g_sCOMUART, AM_HAL_SYSCTRL_WAKE, false));
    CHECK_ERRORS(am_hal_uart_configure(g_sCOMUART, &g_sUartConfig));
#endif    // defined(AM_PART_APOLLO3)
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

/*{{{*/    
#if (VOS_configUSE_LOG_UART0 || VOS_configUSE_PRINTF_UART0 || VOS_configUSE_AWE_TUNING)
        am_hal_gpio_pin_config(22, AM_HAL_PIN_22_UART0TX);
        am_hal_gpio_pin_config(17, AM_HAL_PIN_17_UART0RX);
        am_hal_interrupt_priority_set(AM_HAL_INTERRUPT_UART0, AM_HAL_INTERRUPT_PRIORITY(7));
#endif    // (VOS_configUSE_LOG_UART0||VOS_configUSE_PRINTF_UART0||VOS_configUSE_AWE_TUNING)
/*}}}*/

/*{{{*/
#if VOS_configUSE_LOG_UART1
        am_hal_gpio_pin_config(39, AM_HAL_PIN_39_UART1TX);
    am_hal_gpio_pin_config(40, AM_HAL_PIN_40_UART1RX);
    am_hal_interrupt_priority_set(AM_HAL_INTERRUPT_UART1, AM_HAL_INTERRUPT_PRIORITY(7));
#endif    // VOS_configUSE_LOG_UART1
/*}}}*/
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_UART + ui32Module);
#endif    // defined(AM_PART_APOLLO2)

#if defined (AM_PART_APOLLO3)
    //
    // Enable interrupts.
    //
#if AM_CMSIS_REGS
    NVIC_SetPriority(UART0_IRQn, NVIC_configKERNEL_INTERRUPT_PRIORITY);
    NVIC_EnableIRQ((IRQn_Type)(UART0_IRQn + AM_BSP_UART_PRINT_INST));
#else    // AM_CMSIS_REGS
    am_hal_interrupt_priority_set(AM_HAL_INTERRUPT_UART0, NVIC_configKERNEL_INTERRUPT_PRIORITY);
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_UART0);
#endif    // AM_CMSIS_REGS
    am_hal_interrupt_master_enable();
#endif    // defined(AM_PART_APOLLO3)
}

#if ((VOS_COREBOARD_APOLLO2_EVB || VOS_COREBOARD_APOLLO2_BLUE_EVB || VOS_COREBOARD_APOLLO3_BLUE_EVB || VOS_MAYA_BOARD) && VOS_MIKBRD_ST_MICS)
//-----------------------------------------------------------------------------
// METHOD:  GPIO_Init
// PURPOSE: Setup I/O pins
//-----------------------------------------------------------------------------
#if defined (AM_PART_APOLLO2)
void GPIO_Init(void)
{
    /* Config the button 2 */
    am_hal_gpio_pin_config(CTRL_BUTTON2, AM_HAL_PIN_INPUT);
//    am_hal_gpio_int_register(CTRL_BUTTON2, kwd_button_handler);
    // Configure the GPIO/button interrupt polarity.
    am_hal_gpio_int_polarity_bit_set(CTRL_BUTTON2, AM_HAL_GPIO_RISING);
    // Clear the GPIO Interrupt (write to clear).
    am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON2));
    // Enable the GPIO/button interrupt.
    am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON2));

    /* config I/O for LEDs */

    am_hal_gpio_pin_config(LED_SYSTEM, AM_HAL_PIN_OUTPUT);
    am_hal_gpio_out_bit_clear(LED_SYSTEM); //set to OFF

    am_hal_gpio_pin_config(LED_D5, AM_HAL_PIN_OUTPUT);
    am_hal_gpio_out_bit_clear(LED_D5); //set to OFF

    am_hal_gpio_pin_config(LED_D6, AM_HAL_PIN_OUTPUT);
    am_hal_gpio_out_bit_clear(LED_D6); //set to OFF

    am_hal_gpio_pin_config(LED_D7, AM_HAL_PIN_OUTPUT);
    am_hal_gpio_out_bit_clear(LED_D7); //set to OFF

    am_hal_gpio_pin_config(LED_D8, AM_HAL_PIN_OUTPUT);
    am_hal_gpio_out_bit_clear(LED_D8); //set to OFF

#if VOS_configUSE_PUSH_TO_TALK
    //
    // initialize push to talk button
    //
    am_hal_gpio_pin_config(CTRL_BUTTON3, AM_HAL_PIN_INPUT);
    am_hal_gpio_int_polarity_bit_set(CTRL_BUTTON3, AM_HAL_GPIO_FALLING);
    am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
    am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));

#endif    // VOS_configUSE_PUSH_TO_TALK

#if VOS_configUSE_MUTE_MIC
    am_hal_gpio_pin_config(CTRL_BUTTON4, AM_HAL_PIN_INPUT);
    am_hal_gpio_int_polarity_bit_set(CTRL_BUTTON4, AM_HAL_GPIO_FALLING);
    am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON4));
    am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON4));
#endif    // VOS_configUSE_MUTE_MIC

//
//#if USE_I2S
//    am_hal_gpio_pin_config(I2S_BCLK_PIN, AM_HAL_PIN_24_I2S_BCLK);
//    am_hal_gpio_pin_config(I2S_WCLK_PIN, AM_HAL_PIN_3_I2S_WCLK);
//    am_hal_gpio_pin_config(I2S_DAT_PIN, AM_HAL_PIN_6_I2S_DAT);
//#endif
//
//#if USE_GPIO_PULSE_ON_KWD
//    // GPIO init hi.. goes low for 1ms upon KWD, then hi again
//    // choose GPIO 25
//    am_hal_gpio_pin_config(PULSE_GPIO, AM_HAL_PIN_OUTPUT);
//    am_hal_gpio_out_bit_set(PULSE_GPIO); //set to High
//#endif
//
//// GW: Modified for USE_A2_A3_AND_EM9304_MIKRO_MB2
//#if (USE_OUTPUT_BUFFER_SPI || USE_A2_A3_AND_EM9304_MIKRO_MB2)
//    am_hal_gpio_pin_config(SPI_SCK_GPIO, SPI_SCK_CFG);
//    am_hal_gpio_pin_config(SPI_MISO_GPIO, SPI_MISO_CFG);
//    am_hal_gpio_pin_config(SPI_MOSI_GPIO, SPI_MOSI_CFG);
//    am_hal_gpio_pin_config(SPI_CS_GPIO, SPI_CS_CFG);
//#endif
//
//#if USE_ANALOG_MIC
//    am_hal_gpio_pin_config(ADC_MIC_INPUT_PIN, ADC_MIC_PIN_CFG);
//#endif

// fixme testing
//    am_hal_gpio_pin_config(8, AM_HAL_PIN_OUTPUT);
//    am_hal_gpio_out_bit_clear(8); //set to OFF
//    am_hal_gpio_pin_config(9, AM_HAL_PIN_OUTPUT);
//    am_hal_gpio_out_bit_clear(9); //set to OFF
// end fixme

}   // End GPIO_Init
#endif    // defined(AM_PART_APOLLO2)

#if defined (AM_PART_APOLLO3)
void GPIO_Init(void)
{
    am_hal_gpio_pincfg_t sPinCfg = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    /* Config the button 2 */
    sPinCfg.uFuncSel       = 3, // GPIO
    sPinCfg.eGPOutcfg      = AM_HAL_GPIO_PIN_OUTCFG_DISABLE;
    sPinCfg.eGPInput       = AM_HAL_GPIO_PIN_INPUT_ENABLE;
    sPinCfg.eGPRdZero      = AM_HAL_GPIO_PIN_RDZERO_READPIN;
    sPinCfg.eIntDir        = AM_HAL_GPIO_PIN_INTDIR_HI2LO;
    sPinCfg.ePullup        = AM_HAL_GPIO_PIN_PULLUP_WEAK;
        
    am_hal_gpio_pinconfig(CTRL_BUTTON2, sPinCfg);

    // Clear the GPIO Interrupt (write to clear).
    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON2));
    // Enable the GPIO/button interrupt.
    am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON2));

    /* Config the button 3 */
    sPinCfg.uFuncSel       = 3, // GPIO
    sPinCfg.eGPOutcfg      = AM_HAL_GPIO_PIN_OUTCFG_DISABLE;
    sPinCfg.eGPInput       = AM_HAL_GPIO_PIN_INPUT_ENABLE;
    sPinCfg.eGPRdZero      = AM_HAL_GPIO_PIN_RDZERO_READPIN;
    sPinCfg.eIntDir        = AM_HAL_GPIO_PIN_INTDIR_LO2HI;
    am_hal_gpio_pinconfig(CTRL_BUTTON3, sPinCfg);
    // Clear the GPIO Interrupt (write to clear).
    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
    // Enable the GPIO/button interrupt.
    am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));

#if VOS_COREBOARD_APOLLO3_BLUE_EVB
    /* Config the button 4 */
    /* Config the button 3 */
    sPinCfg.uFuncSel       = 3, // GPIO
    sPinCfg.eGPOutcfg      = AM_HAL_GPIO_PIN_OUTCFG_DISABLE;
    sPinCfg.eGPInput       = AM_HAL_GPIO_PIN_INPUT_ENABLE;
    sPinCfg.eGPRdZero      = AM_HAL_GPIO_PIN_RDZERO_READPIN;
    sPinCfg.eIntDir        = AM_HAL_GPIO_PIN_INTDIR_LO2HI;
    am_hal_gpio_pinconfig(CTRL_BUTTON4, sPinCfg);
    // Clear the GPIO Interrupt (write to clear).
    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON4));
    // Enable the GPIO/button interrupt.
    am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON4));

    /* config I/O for LEDs */
    am_hal_gpio_pinconfig(LED_SYSTEM, g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_state_write(LED_SYSTEM, AM_HAL_GPIO_OUTPUT_CLEAR); //set to OFF
#endif    // VOS_COREBOARD_APOLLO3_BLUE_EVB
    
    
#if VOS_MAYA_BOARD
    am_hal_gpio_pinconfig(LED_D1, g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_state_write(LED_D1, AM_HAL_GPIO_OUTPUT_CLEAR); //set to OFF
    am_hal_gpio_pinconfig(LED_D2, g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_state_write(LED_D2, AM_HAL_GPIO_OUTPUT_CLEAR); //set to OFF
    am_hal_gpio_pinconfig(LED_D3, g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_state_write(LED_D3, AM_HAL_GPIO_OUTPUT_CLEAR); //set to OFF
    am_hal_gpio_pinconfig(LED_D4, g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_state_write(LED_D4, AM_HAL_GPIO_OUTPUT_CLEAR); //set to OFF
#endif    // VOS_MAYA_BOARD

#if USE_WAKE_ON_SOUND

    const am_hal_gpio_pincfg_t CFG_WAKE_PIN =
    {
        .uFuncSel       = 3,
        .eGPOutcfg      = AM_HAL_GPIO_PIN_OUTCFG_DISABLE,
        .eGPInput       = AM_HAL_GPIO_PIN_INPUT_ENABLE,
        .eGPRdZero      = AM_HAL_GPIO_PIN_RDZERO_READPIN,
        .eIntDir        = AM_HAL_GPIO_PIN_INTDIR_LO2HI,
    };

    am_hal_gpio_pinconfig(WOS_WAKE1_PIN, CFG_WAKE_PIN);	

    am_hal_gpio_interrupt_register(WOS_WAKE1_PIN, WOS_handler);

    // Clear the GPIO Interrupt (write to clear).
    am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(WOS_WAKE1_PIN));
    // Enable the GPIO Wake interrupt.
    am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(WOS_WAKE1_PIN));

    am_hal_gpio_pinconfig(WOS_MODE_PIN, g_AM_HAL_GPIO_OUTPUT);
    // uncomment to Set MODE pin to Wake On Sound at power up. Otherwise it will
    // happen anyway when QSD determines a quiet condition exists.
    // am_hal_gpio_out_bit_set(WOS_MODE_PIN);
#endif    // USE_WAKE_ON_SOUND

    am_hal_gpio_pinconfig(LED_D5, g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_CLEAR); //set to OFF

    am_hal_gpio_pinconfig(LED_D6, g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_CLEAR); //set to OFF

    am_hal_gpio_pinconfig(LED_D7, g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_CLEAR); //set to OFF

    am_hal_gpio_pinconfig(LED_D8, g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_CLEAR); //set to OFF


#if VOS_configUSE_PUSH_TO_TALK
    //
    // initialize push to talk button
    //
    const am_hal_gpio_pincfg_t CFG_CTRL_BUTTON3 =
    {
        .uFuncSel       = 3,
        .eGPOutcfg      = AM_HAL_GPIO_PIN_OUTCFG_DISABLE,
        .eGPInput       = AM_HAL_GPIO_PIN_INPUT_ENABLE,
        .eGPRdZero      = AM_HAL_GPIO_PIN_RDZERO_READPIN,
        .eIntDir        = AM_HAL_GPIO_PIN_INTDIR_HI2LO,
    };

    am_hal_gpio_pinconfig(CTRL_BUTTON3, CFG_CTRL_BUTTON3);
    am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
#endif    // VOS_configUSE_PUSH_TO_TALK

#if VOS_configUSE_MUTE_MIC

    const am_hal_gpio_pincfg_t CFG_CTRL_BUTTON4 =
    {
        .uFuncSel       = 3,
        .eGPOutcfg      = AM_HAL_GPIO_PIN_OUTCFG_DISABLE,
        .eGPInput       = AM_HAL_GPIO_PIN_INPUT_ENABLE,
        .eGPRdZero      = AM_HAL_GPIO_PIN_RDZERO_READPIN,
        .eIntDir        = AM_HAL_GPIO_PIN_INTDIR_HI2LO,
    };

    am_hal_gpio_pinconfig(CTRL_BUTTON4, CFG_CTRL_BUTTON4);
    am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON4));

#endif    // VOS_configUSE_MUTE_MIC

#if VOS_configUSE_PUSH_TO_TALK || VOS_configUSE_MUTE_MIC
    NVIC_SetPriority(GPIO_IRQn, NVIC_configKERNEL_INTERRUPT_PRIORITY);
    NVIC_EnableIRQ(GPIO_IRQn);
#endif    // VOS_configUSE_PUSH_TO_TALK||VOS_configUSE_MUTE_MIC

}   // End GPIO_Init

#endif    // defined(AM_PART_APOLLO3)
#endif    // ((VOS_COREBOARD_APOLLO2_EVB||VOS_COREBOARD_APOLLO2_BLUE_EVB||VOS_COREBOARD_APOLLO3_BLUE_EVB||VOS_MAYA_BOARD)&&VOS_MIKBRD_ST_MICS)

#if defined (AM_PART_APOLLO2)
//-----------------------------------------------------------------------------
// METHOD:  PDM_Init
// PURPOSE: PDM module configuration
//-----------------------------------------------------------------------------
void PDMInit(void)
{
    //
    // Enable power to PDM module and configure PDM
    //
    am_hal_pwrctrl_periph_enable(AM_HAL_PWRCTRL_PDM);

    //
    // Configure the PDM microphone pins
    //
    am_hal_gpio_pin_config(PDM_CLK, PDM_CLK_PIN_CFG); // Configure GP12 as PDM clock pin output (Need to blue-wire on REV4 Shield)
    am_hal_gpio_pin_config(PDM_DATA, PDM_DATA_PIN_CFG);// Configure GP11/GP23 as PDM data pin for unmodified Shield
    //
    // Configure the PDM module registers
    //
    am_hal_pdm_config_t g_sPDM_Cfg =
    {
        //
        // uint32_t ui32PDMConfigReg
        // PDM Configuration (PCFG, PDMCFG) register
        // Notes:
        //  Choose from AM_HAL_PDM_PCFG macros.
        //  For completeness, all PCFG fields should be referenced here.
        //
        (
#if VOS_MIKBRD_VESPER
                AM_HAL_PDM_PCFG_LRSWAP_DISABLE      |
            #elif VOS_MIKBRD_ST_MICS
                AM_HAL_PDM_PCFG_LRSWAP_ENABLE       |
#endif    // VOS_MIKBRD_VESPER
                AM_HAL_PDM_PCFG_RIGHT_PGA_P105DB    |	// +10.5dB gain
                AM_HAL_PDM_PCFG_LEFT_PGA_P105DB     |	// +10.5dB gain
                AM_HAL_PDM_PCFG_MCLKDIV_DIV1        |
                AM_HAL_PDM_PCFG_SINC_RATE(48)       |   // over sample rate (decimation)
                AM_HAL_PDM_PCFG_SOFTMUTE_DISABLE    |
#if (VOS_configUSE_AWE == 1)
                AM_HAL_PDM_PCFG_ADCHPD_ENABLE       |
                AM_HAL_PDM_PCFG_HPCUTOFF(0xB)       |   // set high pass coefficient. Must do this!
            #elif                                       // no signal preprocessing present, enable High pass filter
                AM_HAL_PDM_PCFG_ADCHPD_ENABLE       |
                AM_HAL_PDM_PCFG_HPCUTOFF(0x0B)      |   
#endif    // (VOS_configUSE_AWE==1)
                AM_HAL_PDM_PCFG_PDMCORE_DISABLE 
        ),

        //
        // uint32_t ui32VoiceConfigReg
        // PDM Voice Config (VCFG, VOICECFG) register
        // Notes:
        //  Choose from AM_HAL_PDM_VCFG macros.
        //  For completeness, all VCFG fields should be referenced here.
        //  AM_HAL_PDM_IOCLK_xxx also sets AM_REG_PDM_VCFG_IOCLKEN_EN
        //  RSTB is set to NORMAL by am_hal_pdm_enable.
        //
        (
                AM_HAL_PDM_IOCLK_1_5MHZ             |   // AM_REG_PDM_VCFG_IOCLKEN_EN
                AM_HAL_PDM_VCFG_RSTB_RESET          |
                AM_HAL_PDM_VCFG_PDMCLK_ENABLE       |
                AM_HAL_PDM_VCFG_I2SMODE_DISABLE     |
                AM_HAL_PDM_VCFG_BCLKINV_DISABLE     |
                AM_HAL_PDM_VCFG_DMICDEL_0CYC        |
                AM_HAL_PDM_VCFG_SELAP_INTERNAL      |
                AM_HAL_PDM_VCFG_PACK_ENABLE         |
                AM_HAL_PDM_VCFG_CHANNEL_STEREO
        ),

        //
        // uint32_t ui32FIFOThreshold
        // The PDM controller will generate a processor interrupt when the number
        // of entries in the FIFO goes *above* this number.
        //
        (PCM_FRAME_SIZE - 1)
    };

    am_hal_pdm_config(&g_sPDM_Cfg);


    //
    // Make sure interrupts are clear
    //
    am_hal_pdm_int_clear(AM_HAL_PDM_INT_FIFO | AM_HAL_PDM_INT_UNDFL | AM_HAL_PDM_INT_OVF);
    am_hal_pdm_fifo_flush();
    // Enable interrupts PDM
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_PDM);  //NVIC setting
    am_hal_pdm_int_enable(AM_HAL_PDM_INT_FIFO | AM_HAL_PDM_INT_UNDFL | AM_HAL_PDM_INT_OVF);
    am_hal_interrupt_priority_set(AM_HAL_INTERRUPT_PDM, AM_HAL_INTERRUPT_PRIORITY(4));

    am_hal_pdm_enable(); // enable the PDM mic interface

}
#endif    // defined(AM_PART_APOLLO2)

#if defined (AM_PART_APOLLO3)
//*****************************************************************************
//
// PDM configuration information.
//
//*****************************************************************************
void *PDMHandle = NULL;

am_hal_pdm_config_t g_sPdmConfig =
{
    .eClkDivider = AM_HAL_PDM_MCLKDIV_1,
    .eLeftGain = AM_HAL_PDM_GAIN_P105DB,
    .eRightGain = AM_HAL_PDM_GAIN_P105DB,
    .ui32DecimationRate = 24,//48,
    .bHighPassEnable = 0, //
    .ui32HighPassCutoff = 0xB,
    .ePDMClkSpeed = AM_HAL_PDM_CLK_750KHZ,//AM_HAL_PDM_CLK_1_5MHZ,
    .bInvertI2SBCLK = 0,
    .ePDMClkSource = AM_HAL_PDM_INTERNAL_CLK,
    .bPDMSampleDelay = 0,
    .bDataPacking = 1,
    .ePCMChannels = AM_HAL_PDM_CHANNEL_STEREO,
    .bLRSwap = 1,
    .bSoftMute = 0,
};

//*****************************************************************************
//
// Start a transaction to get some number of bytes from the PDM interface.
//
//*****************************************************************************
uint32_t g_ui32PDMDataBuffer[PCM_FRAME_SIZE * BYTES_PER_SAMPLE];
void
pdm_trigger_dma(void)
{
    //
    // Configure DMA and target address.
    //
    am_hal_pdm_transfer_t sTransfer;
    sTransfer.ui32TargetAddr = (uint32_t ) g_ui32PDMDataBuffer;
    sTransfer.ui32TotalCount = (PCM_FRAME_SIZE * BYTES_PER_SAMPLE);

    //
    // Start the data transfer.
    //
    am_hal_pdm_dma_start(PDMHandle, &sTransfer);
}

//-----------------------------------------------------------------------------
// METHOD:  PDM_Init
// PURPOSE: PDM module configuration
//-----------------------------------------------------------------------------
void PDMInit(void)
{
    configASSERT(PDMHandle == NULL);

    if (PDMHandle != NULL)
        return;
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
    am_hal_gpio_pinconfig(PDM_CLK, sPinCfg);

    sPinCfg.uFuncSel = AM_HAL_PIN_11_PDMDATA;
    am_hal_gpio_pinconfig(PDM_DATA, sPinCfg);

    am_hal_pdm_fifo_flush(PDMHandle);

    //
    // Configure and enable PDM interrupts (set up to trigger on DMA
    // completion).
    //
    am_hal_pdm_interrupt_enable(PDMHandle, (AM_HAL_PDM_INT_DERR
                                            | AM_HAL_PDM_INT_DCMP
                                            | AM_HAL_PDM_INT_UNDFL
                                            | AM_HAL_PDM_INT_OVF));
#if AM_CMSIS_REGS
    NVIC_EnableIRQ(PDM_IRQn);
    NVIC_SetPriority(PDM_IRQn, NVIC_configKERNEL_INTERRUPT_PRIORITY);
#else    // AM_CMSIS_REGS
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_PDM);
    am_hal_interrupt_priority_set(AM_HAL_INTERRUPT_PDM, NVIC_configKERNEL_INTERRUPT_PRIORITY);
#endif    // AM_CMSIS_REGS

    //
    // Enable PDM
    //
    am_hal_pdm_enable(PDMHandle);
    pdm_trigger_dma();

}

void PDMDeInit()
{
    if(PDMHandle == NULL)
      return;
  
    am_hal_gpio_pinconfig(PDM_CLK, g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_state_write(PDM_CLK, AM_HAL_GPIO_OUTPUT_CLEAR);
	
    am_hal_gpio_pinconfig(PDM_DATA, g_AM_HAL_GPIO_DISABLE);

    am_hal_pdm_disable(PDMHandle);
    am_hal_pdm_deinitialize(PDMHandle);
    PDMHandle = NULL;

    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PDM);
}

#endif    // defined(AM_PART_APOLLO3)

//-----------------------------------------------------------------------------
// METHOD:  ApolloBoardInitialization
// PURPOSE: Setup board peripherals
//-----------------------------------------------------------------------------
#if defined (AM_PART_APOLLO3)
am_hal_burst_avail_e          eBurstModeAvailable;
am_hal_burst_mode_e           eBurstMode;
#endif    // defined(AM_PART_APOLLO3)

void am_app_KWD_board_init(void)
{
#if ((VOS_COREBOARD_APOLLO2_EVB || VOS_COREBOARD_APOLLO2_BLUE_EVB || VOS_COREBOARD_APOLLO3_BLUE_EVB || VOS_MAYA_BOARD) && VOS_MIKBRD_ST_MICS)
    GPIO_Init();
    PDMInit();

    //
    // Enable debug printf messages using ITM on SWO pin
    //
#ifdef AM_DEBUG_PRINTF
#if defined (AM_PART_APOLLO2)
    am_util_stdio_printf_init((am_util_stdio_print_char_t) am_bsp_itm_string_print);
    am_bsp_pin_enable(ITM_SWO);
    am_bsp_debug_printf_enable();
    am_hal_itm_enable();
#endif    // defined(AM_PART_APOLLO2)
#if defined (AM_PART_APOLLO3)
    //
    // Initialize a debug printing interface.
    //
    am_bsp_itm_printf_enable();
#endif    // defined(AM_PART_APOLLO3)
    //
    // Print the banner.
    //
    am_util_stdio_terminal_clear();
    am_util_debug_printf("Commands Demo\n\n");

#endif    // defAM_DEBUG_PRINTF
    
#if VOS_configUSE_PRINTF_SWO
    //init SWO print here
    am_app_itm_printf_enable();
    swo_init_flag = true;
#endif    // VOS_configUSE_PRINTF_SWO
    AM_APP_LOG_DEBUG("\n\r");
    AM_APP_LOG_DEBUG("AMKWD VoS SDK running...\n");
    AM_APP_LOG_DEBUG("Firmware version: ");
    AM_APP_LOG_DEBUG(VOS_AMA_FW_VER_STRING);
    AM_APP_LOG_DEBUG("\n");
    AM_APP_LOG_DEBUG("System reset reason: 0x%08x \n", (*(volatile uint32_t*)0x4FFFF000));

#if defined (AM_PART_APOLLO3)
    // Check that the Burst Feature is available.
    if (AM_HAL_STATUS_SUCCESS == am_hal_burst_mode_initialize(&eBurstModeAvailable))
    {
        if (AM_HAL_BURST_AVAIL == eBurstModeAvailable)
        {
            am_util_stdio_printf("Apollo3 Burst Mode is Available\n");

            // Make sure we are in "Normal" mode.
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

    //
    // Enable burst mode
    // fixme: the project will always run on 96MHz burst mode
    //
//    if (AM_HAL_STATUS_SUCCESS == am_hal_burst_mode_enable(&eBurstMode))
//    {
//        am_hal_burst_mode_enable(&eBurstMode); //fixme
//        AM_APP_LOG_DEBUG("Apollo3 operating in Burst Mode (96MHz)\n");
//    }


#endif    // defined(AM_PART_APOLLO3)

/*{{{*/
#if (VOS_configUSE_LOG_UART0 || VOS_configUSE_PRINTF_UART0 || VOS_configUSE_AWE_TUNING)
            uart_init(UART0_MODULE);
            uart_enable(UART0_MODULE);
#endif    // (VOS_configUSE_LOG_UART0||VOS_configUSE_PRINTF_UART0||VOS_configUSE_AWE_TUNING)
/*}}}*/

/*{{{*/
#if VOS_configUSE_LOG_UART1
            uart_init(UART1_MODULE);
            uart_enable(UART1_MODULE);
#endif    // VOS_configUSE_LOG_UART1
/*}}}*/

    //
    // Enable SPI
    //
#if USE_OUTPUT_BUFFER_SPI
    spi_init();
#endif    // USE_OUTPUT_BUFFER_SPI

    //
    // Enable software interrupts
    //
#if defined (AM_PART_APOLLO2)
    am_hal_interrupt_pend_clear(AM_HAL_INTERRUPT_SOFTWARE1);
    am_hal_interrupt_pend_clear(AM_HAL_INTERRUPT_SOFTWARE2);
//        am_hal_interrupt_enable(AM_HAL_INTERRUPT_SOFTWARE1);
//        am_hal_interrupt_enable(AM_HAL_INTERRUPT_SOFTWARE2);
    am_hal_interrupt_priority_set(AM_HAL_INTERRUPT_SOFTWARE1, AM_HAL_INTERRUPT_PRIORITY(5));
    am_hal_interrupt_priority_set(AM_HAL_INTERRUPT_SOFTWARE2, AM_HAL_INTERRUPT_PRIORITY(6));
#endif    // defined(AM_PART_APOLLO2)

#if defined (AM_PART_APOLLO3)
//    NVIC_ClearPendingIRQ(CLKGEN_IRQn + 2);        // AM_HAL_INTERRUPT_SOFTWARE1
//    NVIC_ClearPendingIRQ(CLKGEN_IRQn + 3);        // AM_HAL_INTERRUPT_SOFTWARE2
//    NVIC_SetPriority(CLKGEN_IRQn + 2, NVIC_configMAX_SYSCALL_INTERRUPT_PRIORITY);
//    NVIC_SetPriority(CLKGEN_IRQn + 3, NVIC_configMAX_SYSCALL_INTERRUPT_PRIORITY);
#endif    // defined(AM_PART_APOLLO3)

    // enable other interrupts
//        am_hal_interrupt_enable(AM_HAL_INTERRUPT_GPIO);
//        am_hal_interrupt_enable(AM_HAL_INTERRUPT_CTIMER);
    // master interrupt enable
    am_hal_interrupt_master_enable();
#endif    // ((VOS_COREBOARD_APOLLO2_EVB||VOS_COREBOARD_APOLLO2_BLUE_EVB||VOS_COREBOARD_APOLLO3_BLUE_EVB||VOS_MAYA_BOARD)&&VOS_MIKBRD_ST_MICS)

#if VOS_configUSE_BLE
    RadioTaskSetup();
#endif    // VOS_configUSE_BLE
}   // End BoardInit

#if defined (AM_PART_APOLLO3)
void am_app_burst_mode_enable(void)
{
    am_hal_burst_mode_enable(&eBurstMode);
}

void am_app_burst_mode_disable(void)
{
    am_hal_burst_mode_disable(&eBurstMode);
}
#endif    // defined(AM_PART_APOLLO3)

//-----------------------------------------------------------------------------
// METHOD:  CoreInit
// PURPOSE: Setup board peripherals
//-----------------------------------------------------------------------------
void CoreInit(void)
{
#if USE_ANALOG_MIC
    adc_config();
    Init_ADC();
    am_hal_adc_trigger();
#endif    // USE_ANALOG_MIC

}   // End CoreInit




/*FILE END*/
