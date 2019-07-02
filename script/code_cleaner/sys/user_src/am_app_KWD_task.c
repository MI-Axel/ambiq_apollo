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
#include "am_app_KWD_task.h"

#include "dm_api.h"
#include "amvos_api.h"
#include "am_app_KWD_AMA.h"

#if VOS_MAYA_BOARD
#include "am_app_KWD_logic.h"
#endif // #if VOS_MAYA_BOARD

#include "am_audio_buffer.h"

#if USE_WAKE_ON_SOUND
extern uint8_t pdm_enable_flag;
#endif // USE_WAKE_ON_SOUND

//#define USE_QSD_DEBUG
#ifdef USE_QSD_DEBUG
typedef enum
{
    VOS_QSD_INIT = 0,
    VOS_QSD_NOISY,
    VOS_QSD_DELAYED,
    VOS_QSD_QUIET
} eVosQSDStatus_t;
#endif // USE_QSD_DEBUG

extern void am_app_KWD_codec_encode(void *, const void *, size_t, void *, size_t, ssize_t *);
void mute_mic_button_process(void);

bool g_bEnableWakeWordDetection;
bool g_bAmaIsReady = false;

#if (VOS_configUSE_LOG_UART0 || VOS_configUSE_PRINTF_UART0)
//*****************************************************************************
//
// Serial communication task to transmit data.
//
//*****************************************************************************

void am_app_KWD_uart0_gatekeeper_task(void *pvParameters)
{
    const TickType_t xDelay1ms = pdMS_TO_TICKS(1);
    am_app_utils_task_queue_element_t QueueElement;
    uint8_t transmit_buff[UART_TRANSMIT_BUFFER];
    int32_t transmit_length = 0;
    uint32_t index = 0;
    uint32_t ui32RxSize = 0;
    uint32_t ui32TxSize = 0;

#if defined (AM_PART_APOLLO3)
    uint32_t ui32BytesWritten = 0;
    am_hal_uart_transfer_t sUartWrite;
#endif // #if defined (AM_PART_APOLLO3)

    while(1)
    {       
        am_app_utils_task_read(AM_APP_TASK_UART0, &QueueElement);
       
        switch(QueueElement.ui32MessageType)
        {
            case AM_APP_MESSAGE_SHORT:
                transmit_length = 4;
                for(index=0; index < 4; index++)
                {
                    transmit_buff[index] = *((uint8_t*)&QueueElement.info.ui32Note+index); 
                }
#if defined (AM_PART_APOLLO2)
                for(index=0; index < transmit_length; index++)
                {
                    am_hal_uart_char_transmit_buffered(0, transmit_buff[index]);
                }
#endif // #if defined (AM_PART_APOLLO2)
#if defined (AM_PART_APOLLO3)                    
                    ui32BytesWritten = 0;
                    sUartWrite.ui32Direction = AM_HAL_UART_WRITE;
                    sUartWrite.pui8Data = (uint8_t *) transmit_buff;
                    sUartWrite.ui32NumBytes = transmit_length;
                    sUartWrite.ui32TimeoutMs = 0;
                    sUartWrite.pui32BytesTransferred = &ui32BytesWritten;

                    extern void* g_sCOMUART;
                    am_hal_uart_transfer(g_sCOMUART, &sUartWrite);
#endif // #if defined (AM_PART_APOLLO3)

                break;

            case AM_APP_MESSAGE_LONG:
                transmit_length = (int32_t)QueueElement.info.ui32Length;
                while(transmit_length > 0)
                {
#if defined (AM_PART_APOLLO2)
                    while(ui32TxSize > (UART0_BUFFER_SIZE - UART_TRANSMIT_BUFFER))
                    {
                        vTaskDelay(xDelay1ms);
                        am_hal_uart_get_status_buffered(UART0_MODULE, &ui32RxSize, &ui32TxSize);
                   
                    }
#endif // #if defined (AM_PART_APOLLO2)
                    
                    if(transmit_length < UART_TRANSMIT_BUFFER)
                    {                
                        AM_CRITICAL_BEGIN_VOS;
//                        am_app_utils_ring_buffer_pop(QueueElement.pDataBuffer, &transmit_buff,
//                                                    transmit_length, FALSE);
                        am_app_utils_ring_buffer_pop(QueueElement.pDataBuffer, &transmit_buff,
                                                        transmit_length);

                        AM_CRITICAL_END_VOS;
#if defined (AM_PART_APOLLO2)
                        for(index=0; index < transmit_length; index++)
                        {
                            am_hal_uart_char_transmit_buffered(0, transmit_buff[index]);
                        }
#endif // #if defined (AM_PART_APOLLO2)

#if defined (AM_PART_APOLLO3)
                        //
                        // Print the string via the UART.
                        //
                        ui32BytesWritten = 0;
                        sUartWrite.ui32Direction = AM_HAL_UART_WRITE;
                        sUartWrite.pui8Data = (uint8_t *) transmit_buff;
                        sUartWrite.ui32NumBytes = transmit_length;
                        sUartWrite.ui32TimeoutMs = 0;
                        sUartWrite.pui32BytesTransferred = &ui32BytesWritten;

                        extern void* g_sCOMUART;
                        am_hal_uart_transfer(g_sCOMUART, &sUartWrite);
                       
#endif // #if defined (AM_PART_APOLLO3)
                        transmit_length = 0;
                    }
                    else
                    {
                        AM_CRITICAL_BEGIN_VOS;
//                        am_app_utils_ring_buffer_pop(QueueElement.pDataBuffer, 
//                                                    &transmit_buff, UART_TRANSMIT_BUFFER, FALSE);
                        am_app_utils_ring_buffer_pop(QueueElement.pDataBuffer, 
                                                        &transmit_buff, UART_TRANSMIT_BUFFER);

                        AM_CRITICAL_END_VOS;
#if defined (AM_PART_APOLLO2) 
                        for(index=0; index < UART_TRANSMIT_BUFFER; index++)
                        {
                            am_hal_uart_char_transmit_buffered(0, transmit_buff[index]);
                        }
                        transmit_length -= UART_TRANSMIT_BUFFER;
                    }

                    am_hal_uart_get_status_buffered(UART0_MODULE, &ui32RxSize, &ui32TxSize);
                }
                break;
            
            case AM_APP_MESSAGE_STR:
                transmit_length = (int32_t)strlen(&g_prStdioBuff[QueueElement.info.ui32Indx]); 
                for(index=0; index < transmit_length; index++)
                {
                    transmit_buff[index] = g_prStdioBuff[QueueElement.info.ui32Indx + index]; 
                }               
                
                for(index=0; index < transmit_length; index++)
                {
                    am_hal_uart_char_transmit_buffered(0, transmit_buff[index]);
                }
                break;
            
            default: 
                break;
        }
    }

}
#endif // #if defined (AM_PART_APOLLO2)
                        
#if defined (AM_PART_APOLLO3)                    
                        ui32BytesWritten = 0;
                        sUartWrite.ui32Direction = AM_HAL_UART_WRITE;
                        sUartWrite.pui8Data = (uint8_t *) transmit_buff;
                        sUartWrite.ui32NumBytes = transmit_length;
                        sUartWrite.ui32TimeoutMs = 0;
                        sUartWrite.pui32BytesTransferred = &ui32BytesWritten;

                        extern void* g_sCOMUART;
                        am_hal_uart_transfer(g_sCOMUART, &sUartWrite);

                        transmit_length -= UART_TRANSMIT_BUFFER;
                    }
                }
                break;

            case AM_APP_MESSAGE_STR:
                transmit_length = (int32_t)strlen(&g_prStdioBuff[QueueElement.info.ui32Indx]); 
                for(index=0; index < transmit_length; index++)
                {
                    transmit_buff[index] = g_prStdioBuff[QueueElement.info.ui32Indx + index]; 
                }               
                
                ui32BytesWritten = 0;
                sUartWrite.ui32Direction = AM_HAL_UART_WRITE;
                sUartWrite.pui8Data = (uint8_t *) transmit_buff;
                sUartWrite.ui32NumBytes = transmit_length;
                sUartWrite.ui32TimeoutMs = 0;
                sUartWrite.pui32BytesTransferred = &ui32BytesWritten;

                extern void* g_sCOMUART;
                am_hal_uart_transfer(g_sCOMUART, &sUartWrite);

                break;
            
            default: 
                break;
        }
    }
}
#endif // #if defined (AM_PART_APOLLO3)

#endif // #if (VOS_configUSE_LOG_UART0 || VOS_configUSE_PRINTF_UART0)

#if VOS_configUSE_PRINTF_SWO

//*****************************************************************************
//
// @brief Enable printing over ITM.
// Override the bsp function
//
//*****************************************************************************
void
am_app_itm_printf_enable(void)
{
#if defined (AM_PART_APOLLO2)
    
    am_hal_tpiu_config_t TPIUcfg;

    if ( g_ui32HALflags & AM_HAL_FLAGS_ITMSKIPENABLEDISABLE_M )
    {
        return;
    }

    //
    // Write to the ITM control and status register.
    //
    AM_REGVAL(AM_REG_ITM_TCR_O) =
        AM_WRITE_SM(AM_REG_ITM_TCR_ATB_ID, 0x15)      |
        AM_WRITE_SM(AM_REG_ITM_TCR_TS_FREQ, 1)        |
        AM_WRITE_SM(AM_REG_ITM_TCR_TS_PRESCALE, 1)    |
        AM_WRITE_SM(AM_REG_ITM_TCR_SWV_ENABLE, 1)     |
        AM_WRITE_SM(AM_REG_ITM_TCR_DWT_ENABLE, 0)     |
        AM_WRITE_SM(AM_REG_ITM_TCR_SYNC_ENABLE, 0)    |
        AM_WRITE_SM(AM_REG_ITM_TCR_TS_ENABLE, 0)      |
        AM_WRITE_SM(AM_REG_ITM_TCR_ITM_ENABLE, 1);

    //
    // Enable the ITM and TPIU
    //
    TPIUcfg.ui32SetItmBaud = AM_HAL_TPIU_BAUD_1M;
    am_hal_tpiu_enable(&TPIUcfg);
    am_bsp_pin_enable(ITM_SWO);
    
    am_util_stdio_printf_init((am_util_stdio_print_char_t) am_hal_itm_print);
    am_hal_itm_enable();
    
#elif defined (AM_PART_APOLLO3)
    
    am_hal_tpiu_config_t TPIUcfg;
    //
    // Set the global print interface.
    //
    //g_ui32PrintInterface = AM_BSP_PRINT_INFC_SWO;

    //
    // Enable the ITM interface and the SWO pin.
    //
    am_hal_itm_enable();

    //
    // Enable the ITM and TPIU
    // Set the BAUD clock for 1M
    //
    TPIUcfg.ui32SetItmBaud = AM_HAL_TPIU_BAUD_1M;
    am_hal_tpiu_enable(&TPIUcfg);
    am_hal_gpio_pinconfig(AM_BSP_GPIO_ITM_SWO, g_AM_BSP_GPIO_ITM_SWO);

    //
    // Attach the ITM to the STDIO driver.
    //
    am_util_stdio_printf_init(am_hal_itm_print);
    
#endif // AM_PART_APOLLO2, AM_PART_APOLLO3
}
#endif // #if VOS_configUSE_PRINTF_SWO

#if VOS_configUSE_STDIO_PRINTF

#if VOS_configUSE_PRINTF_SWO
    bool swo_init_flag = false;
#endif //#if VOS_configUSE_PRINTF_SWO

//*****************************************************************************
//
// Standard IO task to print data on configured interface
//
//*****************************************************************************
void am_app_KWD_stdIO_gatekeeper_task(void* pvParameters)
{
    am_app_utils_task_queue_element_t QueueElement;
    uint8_t transmit_buff[AM_APP_PRINTF_BUFFSIZE*AM_APP_STDIO_BUFFNUM + 8 + 7 + 4]; // extra 19 bytes for color coding, RTT (BG = 8bytes, text = 7bytes, reset = 4bytes)
    int32_t transmit_length = 0;
    uint32_t index = 0;

    // during init
    // rtt print examples:
    AM_APP_LOG_DEBUG("Example: Use AM_APP_LOG_DEBUG(); for Debug log print on RTT. \n");
    AM_APP_LOG_INFO("Example: Use AM_APP_LOG_INFO(); for Info log print on RTT. \n"); 
    AM_APP_LOG_WARNING("Example: Use AM_APP_LOG_WARNING(); for Warning log print on RTT. \n");
    
//    AM_APP_LOG_DEBUG("BG coding length = %d, Text coding length = %d, Ctrl reset coding length = %d \n", strlen(RTT_CTRL_BG_BLACK),  strlen(RTT_CTRL_TEXT_BRIGHT_GREEN), strlen(RTT_CTRL_RESET));
    
    while(1)
    {
        am_app_utils_task_read(AM_APP_TASK_STDIO, &QueueElement);
        uint8_t color_offset = 0;
        switch(QueueElement.ui32MessageType)
        {
            case AM_APP_MESSAGE_STR:
#if VOS_configUSE_PRINTF_RTT
                switch(QueueElement.Source)
                {
                    case 0:
                      // plain text, write
                      memcpy(transmit_buff, RTT_CTRL_RESET, strlen(RTT_CTRL_RESET));
                      color_offset = strlen(RTT_CTRL_RESET);
                      break;
                    case 1:
                      // debug, green, black background
                      memcpy(transmit_buff, RTT_CTRL_BG_BLACK, strlen(RTT_CTRL_BG_BLACK));
                      memcpy(transmit_buff + strlen(RTT_CTRL_BG_BLACK), RTT_CTRL_TEXT_BRIGHT_GREEN, strlen(RTT_CTRL_TEXT_BRIGHT_GREEN));
                      color_offset = strlen(RTT_CTRL_BG_BLACK) + strlen(RTT_CTRL_TEXT_BRIGHT_GREEN);
                      break;
                    case 2:
                      // warning, white, red background
                      memcpy(transmit_buff, RTT_CTRL_BG_RED, strlen(RTT_CTRL_BG_RED));
                      memcpy(transmit_buff + strlen(RTT_CTRL_BG_RED), RTT_CTRL_TEXT_BRIGHT_WHITE, strlen(RTT_CTRL_TEXT_BRIGHT_WHITE));
                      color_offset = strlen(RTT_CTRL_BG_RED) + strlen(RTT_CTRL_TEXT_BRIGHT_WHITE);
                      break;
                    case 3:
                      // info, cyan, black background
                      memcpy(transmit_buff, RTT_CTRL_BG_BLACK, strlen(RTT_CTRL_BG_BLACK));
                      memcpy(transmit_buff + strlen(RTT_CTRL_BG_BLACK), RTT_CTRL_TEXT_BRIGHT_CYAN, strlen(RTT_CTRL_TEXT_BRIGHT_CYAN));
                      color_offset = strlen(RTT_CTRL_BG_BLACK) + strlen(RTT_CTRL_TEXT_BRIGHT_CYAN);
                      break;
                    default:
                      // plain text, write
                      memcpy(transmit_buff, RTT_CTRL_RESET, strlen(RTT_CTRL_RESET));
                      color_offset = strlen(RTT_CTRL_RESET);
                      break;
//                    SEGGER_RTT_Write(0, transmit_buff, transmit_length);
                }
#endif //#if VOS_configUSE_PRINTF_RTT
                
#if VOS_configUSE_PRINTF_SWO
                color_offset = 0;
                
#endif //#if VOS_configUSE_PRINTF_SWO
              
                transmit_length = (int32_t)strlen(&g_prStdioBuff[QueueElement.info.ui32Indx]); 
               
                configASSERT(transmit_length < AM_APP_PRINTF_BUFFSIZE);
                
                for(index=0; index < transmit_length; index++)
                {
                    transmit_buff[index + color_offset] = g_prStdioBuff[QueueElement.info.ui32Indx + index]; 
                }
                transmit_buff[transmit_length + color_offset] = NULL;
#if VOS_configUSE_PRINTF_RTT
                SEGGER_RTT_printf(0, (const char *)transmit_buff);
#endif //#if VOS_configUSE_PRINTF_RTT
                
#if VOS_configUSE_PRINTF_SWO
//                if(swo_init_flag == false)
//                {
//                    swo_init_flag = true;
//                    //init SWO print here
//                    am_app_itm_printf_enable();
//                }
                am_util_stdio_printf((const char *)transmit_buff);
#endif
                break;
            default: 
                break;
        }
    
    }


}
#endif
//*****************************************************************************
//
// LED task to indicate external events, such as heart beat and key word detected.
//
//*****************************************************************************

void am_app_KWD_led_task(void *pvParameters)
{
    const TickType_t xDelay500ms = pdMS_TO_TICKS(500);
    const TickType_t xDelay200ms = pdMS_TO_TICKS(200);
    const TickType_t xDelaySwirl = pdMS_TO_TICKS(35);
    am_app_utils_task_queue_element_t QueueElement;
    while(1)
    {

        am_app_utils_task_read(AM_APP_TASK_LED, &QueueElement);
       
//****************************************************************************
//
// LED display pattern to indicate key word is detected
//
//****************************************************************************
#if defined (AM_PART_APOLLO2)

        am_hal_gpio_out_bit_toggle(LED_D5);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_out_bit_toggle(LED_D6);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_out_bit_toggle(LED_D7);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_out_bit_toggle(LED_D8);
        vTaskDelay(xDelaySwirl);

        am_hal_gpio_out_bit_toggle(LED_D5);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_out_bit_toggle(LED_D6);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_out_bit_toggle(LED_D7);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_out_bit_toggle(LED_D8);
        vTaskDelay(xDelaySwirl);

        am_hal_gpio_out_bit_clear(LED_D5);
        am_hal_gpio_out_bit_clear(LED_D6);
        am_hal_gpio_out_bit_clear(LED_D7);
        am_hal_gpio_out_bit_clear(LED_D8);
#endif // #if defined (AM_PART_APOLLO2)

#if defined (AM_PART_APOLLO3)
#if VOS_COREBOARD_APOLLO3_BLUE_EVB
        am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_TOGGLE);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_TOGGLE);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_TOGGLE);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_TOGGLE);
        vTaskDelay(xDelaySwirl);

        am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_TOGGLE);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_TOGGLE);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_TOGGLE);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_TOGGLE);
        vTaskDelay(xDelaySwirl);
#endif // #if VOS_COREBOARD_APOLLO3_BLUE_EVB
        
#if VOS_MAYA_BOARD
        am_hal_gpio_state_write(LED_D1, AM_HAL_GPIO_OUTPUT_SET);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_state_write(LED_D2, AM_HAL_GPIO_OUTPUT_SET);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_state_write(LED_D3, AM_HAL_GPIO_OUTPUT_SET);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_state_write(LED_D4, AM_HAL_GPIO_OUTPUT_SET);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_SET);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_SET);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_SET);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_SET);
        vTaskDelay(xDelaySwirl);

        am_hal_gpio_state_write(LED_D1, AM_HAL_GPIO_OUTPUT_CLEAR);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_state_write(LED_D2, AM_HAL_GPIO_OUTPUT_CLEAR);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_state_write(LED_D3, AM_HAL_GPIO_OUTPUT_CLEAR);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_state_write(LED_D4, AM_HAL_GPIO_OUTPUT_CLEAR);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_CLEAR);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_CLEAR);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_CLEAR);
        vTaskDelay(xDelaySwirl);
        am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_CLEAR);
        vTaskDelay(xDelaySwirl);

        // enable button2 interrupt.  
        
        if (QueueElement.Source == AM_APP_ISR_GPIO)
          {
            vTaskDelay(xDelay200ms);
            am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON2));
          }
        
#endif // #if VOS_COREBOARD_APOLLO3_BLUE_EVB
//        am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_TOGGLE);
//        am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_TOGGLE);
//        am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_TOGGLE);
//        am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_TOGGLE);
//        vTaskDelay(xDelay500ms);
//
//        am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_TOGGLE);
//        am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_TOGGLE);
//        am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_TOGGLE);
//        am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_TOGGLE);
//        vTaskDelay(xDelay500ms);
//
//        am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_TOGGLE);
//        am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_TOGGLE);
//        am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_TOGGLE);
//        am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_TOGGLE);
//        vTaskDelay(xDelay500ms);
//
//        am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_CLEAR);
//        am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_CLEAR);
//        am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_CLEAR);
//        am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_CLEAR);
#endif //#if defined (AM_PART_APOLLO3)

    }

}
//****************************************************************************
//
// RTT switch task to turn on/off RTT recorder
//
//****************************************************************************
#if VOS_configUSE_RTT_RECORDER
void am_app_KWD_rtt_switch_task(void *pvParameters)
{
    uint8_t record_switch = 1;
    uint8_t switch_times = 0;
    const TickType_t xDelay100ms = pdMS_TO_TICKS(100);
    am_app_utils_task_queue_element_t QueueElement;

    while(1)
    {
        //
        //Key anti jitter
        //
        record_switch = am_hal_gpio_input_bit_read(CTRL_BUTTON2);          // set low to turn off LED
        if((record_switch==0)&&(switch_times<10))
            switch_times++;
        else if((record_switch==1)&&(switch_times<=2))
            switch_times = 0;
        //
        //Key action is confirmed
        //
        if((switch_times>2)&&(record_switch==1))
        {
            if(g_ui8RTTStartFlag == 0)
                g_ui8RTTStartFlag = 1;
            else
                g_ui8RTTStartFlag = 0;
//            am_hal_gpio_out_bit_toggle(LED_D7);
            switch_times = 0;
        
            if(g_ui8RTTStartFlag == 1)
            {
                xTimerChangePeriod(am_KWD_timers[AM_APP_TIMER_HEART_BEAT], RTT_RECORDER_RUNNING, 0);
            }
            else
            {
                xTimerChangePeriod(am_KWD_timers[AM_APP_TIMER_HEART_BEAT], HEART_BEAT_PERIOD, 0);      
            }
        }
        vTaskDelay(xDelay100ms);
    }

}
#endif //#if VOS_configUSE_RTT_RECORDER
//*****************************************************************************
//
// AWE task to execute the AWE frame work
//
//*****************************************************************************
#if VOS_configUSE_AWE

#define QSD_OFF_DELAY_COUNT     200      // 1 count is ~5ms
uint16_t ui16QsdOffDelayCount = 0;      // "QSD off" means QSD detected quiet environment 
                                        // and turns AWE processing off
void am_app_KWD_AWE_processing_task(void *pvParameters)
{
    am_app_utils_task_queue_element_t QueueElement;
    int32_t in32LRSample[AWE_FRAME_SIZE];
    #if VOS_configUSE_AWE_TUNING 
        uint8_t bReplyReady = 0;
    #endif
    #if VOS_configUSE_QSD
        int16_t in16AudioStreamBuff[AWE_FRAME_SIZE];
    #endif

    while(1)
    {
        am_app_utils_task_read(AM_APP_TASK_AUD_PROCESSING, &QueueElement);

        switch(QueueElement.ui32MessageType)
        {
            case AM_APP_MESSAGE_SHORT:
#if VOS_configUSE_PUSH_TO_TALK

                    if(QueueElement.info.ui32Note == KEY_WORD_GOT_MESSAGE)
                    {
                        if(g_bEnableWakeWordDetection == true)
                        {
                            // push to talk event
                            am_kwd_streaming_start();
                            g_bEnableWakeWordDetection = false;
                            AM_APP_LOG_INFO("[AM-VoS] Push to talk!\n");
                        }
                        else
                        {
                            // barge-in not allowed
#if VOS_configUSE_PUSH_TO_TALK
#if defined (AM_PART_APOLLO3)
                            // enable push to talk interrupt again
                            am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
                            am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
#else
                            // enable push to talk interrupt again
                            am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
                            am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
#endif //#if defined (AM_PART_APOLLO3)
#endif // VOS_configUSE_PUSH_TO_TALK
                        }
                    }
#endif // VOS_configUSE_PUSH_TO_TALK
                break;

            case AM_APP_MESSAGE_LONG:
                configASSERT(QueueElement.info.ui32Length <= AWE_FRAME_SIZE * BYTES_PER_SAMPLE);                
//                AM_CRITICAL_BEGIN_VOS;
//                am_app_utils_ring_buffer_pop(QueueElement.pDataBuffer, in32LRSample, QueueElement.info.ui32Length, FALSE);

                if(QueueElement.Source == AM_APP_ISR_PDM)
                {
                    am_audio_buffer_nested_pop(AM_AUDIO_BUFFER_STEREO, AM_AUDIO_BUFFER_MONO, in32LRSample, QueueElement.info.ui32Length);
                }
                else
                {
//                    am_app_utils_ring_buffer_pop(QueueElement.pDataBuffer, in32LRSample, QueueElement.info.ui32Length);
                }
//                AM_CRITICAL_END_VOS;
                break;

            default: 
                break;
        }

    /*{{{*/    
//        AM_CRITICAL_BEGIN_VOS;
        
#if VOS_configUSE_QSD
        int32_t qsdFlag;
        qsdFlag = dspc_qsd_process_fract16(&Q, (short int *)in32LRSample, 2);
#ifdef USE_QSD_DEBUG
            static eVosQSDStatus_t eQsdStatus = VOS_QSD_INIT;
#endif //USE_QSD_DEBUG
        if (qsdFlag || g_ui8KwdDetectedFlag || g_ui8PushTalkFlag || g_ui8ProvideSpeechFlag)
        {
            // Place the samples in the AWE processing buffers
#ifdef AM_PART_APOLLO3
//            am_app_burst_mode_enable(); // noisy or keyword detected
#endif // #ifdef AM_PART_APOLLO3
            am_app_KWD_AWE_handler(in32LRSample);
            ui16QsdOffDelayCount = QSD_OFF_DELAY_COUNT;
#ifdef USE_QSD_DEBUG
                if(eQsdStatus != VOS_QSD_NOISY) {
                    AM_APP_LOG_INFO("QN ");
                    eQsdStatus = VOS_QSD_NOISY;
                }
#endif // USE_QSD_DEBUG
        }
        else
        {
            //
            // QSD needs a delayed turning off
            //
            if(ui16QsdOffDelayCount)
            {
                ui16QsdOffDelayCount--;
                // Place the samples in the AWE processing buffers
                am_app_KWD_AWE_handler(in32LRSample);
#ifdef USE_QSD_DEBUG
                    if(eQsdStatus != VOS_QSD_DELAYED) {
                        AM_APP_LOG_INFO("QD ");
                        eQsdStatus = VOS_QSD_DELAYED;
                    }
#endif // USE_QSD_DEBUG
            }
            else
            {

//                AM_CRITICAL_BEGIN_VOS;
//				am_audio_buffer_stereo_to_mono(in32LRSample, QueueElement.info.ui32Length);
//                am_audio_buffer_push(AM_AUDIO_BUFFER_MONO, in32LRSample, QueueElement.info.ui32Length / 2);
//				AM_CRITICAL_END_VOS;
            }

#if USE_WAKE_ON_SOUND
            if(pdm_enable_flag)	// PDM isr is invoked every 5ms. therefore 50 ms timeout.
            {
                //APP_TRACE_INFO2("WOS_MODE_PIN %d pdm_enable_flag %d", am_hal_gpio_out_bit_read(WOS_MODE_PIN) , pdm_enable_flag);
                // Make WoS mode On and waiting for 50ms
                uint32_t ui32PinState = 0xFF;
                am_hal_gpio_state_read(WOS_MODE_PIN, AM_HAL_GPIO_INPUT_READ, &ui32PinState);

                if(!ui32PinState)
                  am_hal_gpio_state_write(WOS_MODE_PIN, AM_HAL_GPIO_OUTPUT_SET);
            }
            else if(pdm_enable_flag == 0)
            {
                kwd_pdm_disable(); // VM1010 didn't send WoS signal for 50 ms, then PDM off.
            }

            if(pdm_enable_flag > 0)
              pdm_enable_flag--;
#endif // #if USE_WAKE_ON_SOUND
        }
        /*}}}*/
#else   // #if VOS_configUSE_QSD

        am_app_KWD_AWE_handler(in32LRSample);
#endif  // #if VOS_configUSE_QSD

//        AM_CRITICAL_END_VOS;
        
    #if VOS_configUSE_AWE_TUNING 
        CheckForUARTPacketReady();
    
        bReplyReady = awe_pltTuningTick();
    
        if (bReplyReady == REPLY_READY)
        {
            UART0SendReply();
    
            if (awe_pltIsReboot())
            {
                am_util_delay_ms(500);
                am_hal_sysctrl_aircr_reset();
            }
        }
    #endif

        awe_fwTick(&g_AWEInstance);

        if (g_bAudioPump2Active == TRUE)
        {
            g_bAudioPump2Active = FALSE;
    #if VOS_configUSE_MODEL_INFERENCE
            if(g_bEnableWakeWordDetection == true)
            {
                am_app_utils_task_send(AM_APP_TASK_AUD_PROCESSING, AM_APP_TASK_MODEL_INFERENCE,
                                        AM_APP_MESSAGE_SHORT, EMPTY_MESSAGE, NULL);
    
            }
    #endif // VOS_configUSE_MODEL_INFERENCE
        }
     }

}
#endif // #if VOS_configUSE_AWE

#if VOS_configUSE_SENSORY_THF_ONLY
void am_app_KWD_AWE_processing_task(void *pvParameters)
{
    am_app_utils_task_queue_element_t QueueElement;
    uint8_t bReplyReady = 0;
    int32_t in32LRSample[AWE_FRAME_SIZE];

    while(1)
    {
        am_app_utils_task_read(AM_APP_TASK_AUD_PROCESSING, &QueueElement);

        switch(QueueElement.ui32MessageType)
        {
            case AM_APP_MESSAGE_SHORT:
                break;

            case AM_APP_MESSAGE_LONG:
                configASSERT(QueueElement.info.ui32Length <= AWE_FRAME_SIZE * BYTES_PER_SAMPLE);                
                AM_CRITICAL_BEGIN;
//                am_app_utils_ring_buffer_pop(QueueElement.pDataBuffer, in32LRSample, QueueElement.info.ui32Length, FALSE);
                am_app_utils_ring_buffer_pop(QueueElement.pDataBuffer, in32LRSample, QueueElement.info.ui32Length);
                AM_CRITICAL_END;
                break;

            default: 
                break;
        }

        am_app_KWD_AWE_handler(in32LRSample);
    }
}
#endif
//*****************************************************************************
//
// AWE task to execute the AWE frame work
//
//*****************************************************************************
#if VOS_configUSE_MODEL_INFERENCE
void am_app_KWD_model_inference_task(void *pvParameters)
{

    g_bEnableWakeWordDetection = true;

    am_app_utils_task_queue_element_t QueueElement;
    
    while(1)
    {
        am_app_utils_task_read(AM_APP_TASK_MODEL_INFERENCE, &QueueElement);

        // Fire the layout at user interrupt level
        awe_fwPump(&g_AWEInstance, 1);
        g_bAudioPump2Active = FALSE;

        ProcessControlIO();

//        am_app_utils_task_send(AM_APP_TASK_MODEL_INFERENCE, AM_APP_TASK_AWE_TICK,
//                                                AM_APP_MESSAGE_SHORT, EMPTY_MESSAGE, NULL);

    }

}
#endif // #if VOS_configUSE_MODEL_INFERENCE
//*****************************************************************************
//
// AWE result output and tick task.
//
//*****************************************************************************

void am_app_KWD_AWE_tick_task(void *pvParameters)
{
#if VOS_configUSE_AWE_TUNING 
    uint8_t bReplyReady = 0;
#endif // #if VOS_configUSE_AWE_TUNING
    am_app_utils_task_queue_element_t QueueElement;

    while(1)
    {
       
        am_app_utils_task_read(AM_APP_TASK_AWE_TICK, &QueueElement);
        #if VOS_configUSE_AWE_TUNING 
           CheckForUARTPacketReady();

           bReplyReady = awe_pltTuningTick();

           if (bReplyReady == REPLY_READY)
           {
               UART0SendReply();

               if (awe_pltIsReboot())
               {
                   am_util_delay_ms(500);
                   am_hal_sysctrl_aircr_reset();
               }
           }
        #endif
        #if VOS_configUSE_AWE
            awe_fwTick(&g_AWEInstance);
        #endif
        // Indicate that this idle loop call is getting CPU attention
//        vTaskDelay(xDelay5ms);
    }
}


#if VOS_configUSE_AUDIO_CODEC
//*****************************************************************************
//
// Audio codec task
//
//*****************************************************************************

void am_app_KWD_codec_task(void *pvParameters)
{
    am_app_utils_task_queue_element_t QueueElement;

    int8_t codecInputBuffer[CODEC_IN_RING_BUFF_SIZE];
    uint8_t codecOutputBuffer[CODEC_OUT_RING_BUFF_SIZE];
    int8_t *p_CodecInBuf = codecInputBuffer;
    uint8_t *p_CodecOutBuf = codecOutputBuffer;

    int32_t i32CompressedLen;
    uint32_t ui32StreamLen;    
    uint16_t index = 0;
    while(1)
    {
        am_app_utils_task_read(AM_APP_TASK_CODEC, &QueueElement);

        switch(QueueElement.Source)
        {
            case AM_APP_TASK_AUD_PROCESSING:

                    AM_CRITICAL_BEGIN_VOS;
                    ui32StreamLen = am_app_utils_get_ring_buffer_status(&am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO]);

                    AM_CRITICAL_END_VOS;
                    static uint8_t ui8EncoderLoopCount = 0;
                    while(ui32StreamLen >= CODEC_IN_RING_BUFF_SIZE) 
                    {
                        if(ui8EncoderLoopCount == 0)
                        {
                            vTaskSuspendAll();
                        }

                        ui8EncoderLoopCount++;

                        am_audio_buffer_nested_pop(AM_AUDIO_BUFFER_MONO, AM_AUDIO_BUFFER_ENCODED, codecInputBuffer, CODEC_IN_RING_BUFF_SIZE);
#if (VOS_configUSE_MSBC_BLUEZ || VOS_configUSE_SBC_BLUEZ)
                        am_app_KWD_codec_encode(&g_BluezSBCInstance, p_CodecInBuf, 
                                                    CODEC_IN_RING_BUFF_SIZE, p_CodecOutBuf, CODEC_OUT_RING_BUFF_SIZE, (int32_t *)&i32CompressedLen);
#endif
 
#if VOS_configUSE_OPTIM_OPUS

//                          vTaskSuspendAll();
                        am_app_KWD_codec_encode(NULL, p_CodecInBuf, CODEC_IN_RING_BUFF_SIZE,
                                p_CodecOutBuf, CODEC_OUT_RING_BUFF_SIZE, &i32CompressedLen);
//                          xTaskResumeAll();
#endif

//                            AM_APP_LOG_DEBUG("i32CompressedLen = %d\n", i32CompressedLen); 

//                            vTaskSuspendAll();
//                            AM_CRITICAL_BEGIN_VOS;
//                        am_audio_buffer_push(AM_AUDIO_BUFFER_ENCODED, p_CodecOutBuf, i32CompressedLen);
                          am_audio_buffer_nested_push(AM_AUDIO_BUFFER_ENCODED, AM_AUDIO_BUFFER_MONO, p_CodecOutBuf, i32CompressedLen);
//                            am_audio_buffer_update_mono_pointers();

//                        if(am_audio_buffer_update_mono_pointers())
//                        {
                                // no data of high density exist anymore
//                            AM_APP_LOG_DEBUG("----mono consumed, encoded tail = 0x%08x, encoded left = %d, mono tail = 0x%08x\n", am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED].ui32BufferTail_write, 
//                                ((am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED].ui32BufferTail_write + BYTES_UNIVERSAL_BUFFER_SIZE - am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED].ui32BufferHead_read))%BYTES_UNIVERSAL_BUFFER_SIZE,
//                                am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO].ui32BufferTail_write);
#ifdef AM_PART_APOLLO3
//                            am_app_burst_mode_disable();
#endif // AM_PART_APOLLO3
//                            }
//                        xTaskResumeAll();
//                        AM_CRITICAL_END_VOS;

#if AUDIO_BUFFER_DEBUG
                        AM_APP_LOG_DEBUG("Push, type: encoded, head: %d, tail: %d\n", 
                                            am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED].ui32BufferHead_read, 
                                            am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED].ui32BufferTail_write);
#endif // #if AUDIO_BUFFER_DEBUG

//                       ui32StreamLen -= CODEC_IN_RING_BUFF_SIZE;

                        if(am_app_utils_get_ring_buffer_status(&am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED]) >= BLE_DATA_BUFFER_SIZE)
                        {

                            am_app_KWD_ble_stream_start();
                        }


                        AM_CRITICAL_BEGIN_VOS;
                        ui32StreamLen = am_app_utils_get_ring_buffer_status(&am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO]);
                        AM_CRITICAL_END_VOS;
                        if((ui32StreamLen <= CODEC_IN_RING_BUFF_SIZE)||(ui8EncoderLoopCount > 1))
                        {
                            ui8EncoderLoopCount = 0;
                            xTaskResumeAll();
                        }
                    }



//                #endif //#if VOS_configUSE_AUDIO_POST_BUFF
#if 0
                #if VOS_configUSE_AUDIO_POST_BUFF
                    AM_CRITICAL_BEGIN;
                    ui32StreamLen = am_app_utils_get_ring_buffer_status(QueueElement.pDataBuffer);
                    AM_CRITICAL_END;    
                    if (g_ui8KwdDetectedFlag == 1 || g_ui8PushTalkFlag == 1 || g_ui8ProvideSpeechFlag == 1)
                    {
                        #if VOS_configUSE_AUDIO_PRE_BUFF_AMA
                            if(g_ui8KwdRequiredConsume)
                            {
                                uint32_t ui32BuffConsumeCnt = 0;
                                if((BYTES_PER_DSPC_SAMPLE*PCM_SAMPLE_RATE_MS*AUDIO_BUFF_LEN_MS  - BYTES_PER_1MS_DSPC_SAMPLE * AUDIO_PREBUFF_TIME_MS) > (g_delayedSample * BYTES_PER_DSPC_SAMPLE))
                                {
                                    ui32BuffConsumeCnt = (BYTES_PER_DSPC_SAMPLE*PCM_SAMPLE_RATE_MS*AUDIO_BUFF_LEN_MS  - BYTES_PER_1MS_DSPC_SAMPLE * AUDIO_PREBUFF_TIME_MS) - g_delayedSample * BYTES_PER_DSPC_SAMPLE;
                                }
                                else
                                {
                                    AM_APP_LOG_WARNING("No need consumed!!\n");
                                }
                                for(int i = 0; i < ui32BuffConsumeCnt / CODEC_IN_RING_BUFF_SIZE; i++)
                                {
                                    am_app_utils_ring_buffer_pop(QueueElement.pDataBuffer, codecInputBuffer, 
                                                                      CODEC_IN_RING_BUFF_SIZE);
                                }
                                if(ui32BuffConsumeCnt % CODEC_IN_RING_BUFF_SIZE)
                                {
                                    am_app_utils_ring_buffer_pop(QueueElement.pDataBuffer, codecInputBuffer, 
                                                                      ui32BuffConsumeCnt % CODEC_IN_RING_BUFF_SIZE);
                                }
                                AM_APP_LOG_INFO("ui32StreamLen %d Buff consume: %d\n", ui32StreamLen, ui32BuffConsumeCnt);

                                g_ui8KwdRequiredConsume = 0;

                                AM_CRITICAL_BEGIN;
                                ui32StreamLen = am_app_utils_get_ring_buffer_status(QueueElement.pDataBuffer);
                                AM_CRITICAL_END;
                            }
                        #endif
                        while(ui32StreamLen >= CODEC_IN_RING_BUFF_SIZE) 
                        {
                            am_app_utils_ring_buffer_pop(QueueElement.pDataBuffer, codecInputBuffer, 
                                                              CODEC_IN_RING_BUFF_SIZE);

                            am_app_KWD_codec_encode(&g_BluezSBCInstance, p_CodecInBuf, 
                                                    CODEC_IN_RING_BUFF_SIZE, p_CodecOutBuf, CODEC_OUT_RING_BUFF_SIZE, (int32_t *)&i32CompressedLen);
                            ui32StreamLen -= CODEC_IN_RING_BUFF_SIZE;

                            if(i32CompressedLen)
                            {
                                memcpy(&g_BleDataBuffer[index], codecOutputBuffer, i32CompressedLen);
                                index += i32CompressedLen;
                                if(index >= BLE_DATA_BUFFER_SIZE)
                                {
                                    #if VOS_configUSE_BLE
                                        am_app_KWD_AMA_stream_send(g_BleDataBuffer, index);
                                        #if VOS_configUSE_AUDIO_PRE_BUFF_AMA
                                            #if defined (AM_PART_APOLLO3)
                                                if(g_ui32AmaDialogID == 0)          // Lewis : Workaround for Pre-roll version's 1st command issue (not enough bandwidth)
                                                      vTaskDelay(pdMS_TO_TICKS(5));
                                            #endif
                                        #endif
                                    #endif
                                    index = 0;
                                }
                            }
                            AM_CRITICAL_BEGIN;
                            ui32StreamLen = am_app_utils_get_ring_buffer_status(QueueElement.pDataBuffer);
                            AM_CRITICAL_END;
                            
                        }
                    }
    
                #endif
#endif // #if 0
                break;
            
            default: 
                break;

        }
        
    }
}
#endif

//*****************************************************************************
//
// Software timer callback functions
//
//*****************************************************************************
void am_app_KWD_timer_heart_beat_callback(TimerHandle_t xTimer)
{
#if USE_OUTPUT_AMVOS_AMA
    static uint8_t keep_alive_cnt = 0;
#endif // USE_OUTPUT_AMVOS_AMA

#if defined (AM_PART_APOLLO2)
    am_hal_gpio_out_bit_toggle(LED_SYSTEM);
#endif // #if defined (AM_PART_APOLLO2)

#if defined (AM_PART_APOLLO3)
#if VOS_COREBOARD_APOLLO3_BLUE_EVB
    am_hal_gpio_state_write(LED_SYSTEM, AM_HAL_GPIO_OUTPUT_TOGGLE);
#endif // #if VOS_COREBOARD_APOLLO3_BLUE_EVB
    
#if VOS_MAYA_BOARD
    if(amvosIsConnected())
    {
        am_app_logic_led_all_on();
        vTaskDelay(pdMS_TO_TICKS(10));
        am_app_logic_led_all_off();
        vTaskDelay(pdMS_TO_TICKS(150));
        am_app_logic_led_all_on();
        vTaskDelay(pdMS_TO_TICKS(10));
        am_app_logic_led_all_off();
    }
    else
    {
        am_app_logic_led_all_on();
        vTaskDelay(pdMS_TO_TICKS(20));
        am_app_logic_led_all_off();
    }
    
#endif // #if VOS_MAYA_BOARD
#endif // #if defined (AM_PART_APOLLO3)

#if 0 //USE_OUTPUT_AMVOS_AMA
    if((g_eAmaStatus == VOS_AMA_IDLE) && (g_AmaConnId != DM_CONN_ID_NONE) && (g_ui8KwdDetectedFlag == 0))
    {
        if(++keep_alive_cnt == 10)
        {
            am_app_KWD_AMA_keep_alive_send();
            keep_alive_cnt = 0;
//            AM_APP_LOG_INFO("[AMA] Cmd KEEP_ALIVE sent\n");
        }
    }
    else
        keep_alive_cnt = 0;
#endif // USE_OUTPUT_AMVOS_AMA
		
    #if VOS_configUSE_BLE_Measure_Throughput
        if(g_ui32AmaDataSentLength > 0)
        {
            AM_APP_LOG_INFO("[AMA] Data sent %d B/s\n", g_ui32AmaDataSentLength * g_ui32AmaDataCnfCnt / g_ui32AmaDataSentCnt);
            g_ui32AmaDataSentLength = 0;
            g_ui32AmaDataSentCnt -= g_ui32AmaDataCnfCnt;
            g_ui32AmaDataCnfCnt = 0;
        }
    #endif
}


void am_app_KWD_timer_postbuff_timeout_callback(TimerHandle_t xTimer)
{
    am_app_KWD_reset_detected_flag();
#if USE_UNIVERSAL_AUDIO_BUFFER
    am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO]);
    am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED]);
#endif // USE_UNIVERSAL_AUDIO_BUFFER

    AM_APP_LOG_INFO("am_app_KWD_timer_postbuff_timeout_callback()\n");

#if USE_OUTPUT_AMVOS_AMA
    g_eAmaStatus = VOS_AMA_IDLE;
#endif

#if defined (AM_PART_APOLLO2)
    am_hal_gpio_out_bit_clear(LED_D6);
    am_hal_gpio_out_bit_clear(LED_D7);
    am_hal_gpio_out_bit_clear(LED_D8);
#endif

#if defined (AM_PART_APOLLO3)
    am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_CLEAR);
#endif // #if defined (AM_PART_APOLLO3)
}

#if VOS_MAYA_BOARD
void am_app_KWD_buzzer_task(void *pvParameters)
{
    am_app_utils_task_queue_element_t QueueElement;
    
    while(1)
    {
        am_app_utils_task_read(AM_APP_TASK_BUZZER, &QueueElement);
        am_app_util_buzzer_process();
    }
}

#if VOS_configUSE_GSENSOR
void am_app_KWD_gsensor_task(void *pvParameters)
{
    am_app_utils_task_queue_element_t QueueElement;
    
    //am_app_util_gsensor_process();    
    //xTimerStart(am_KWD_timers[AM_APP_TIMER_GSENSOR_PERIOD], 0);

    while(1)
    {
        //am_app_util_gsensor_power_down();
        //am_app_utils_task_suspend(AM_APP_TASK_GSENSOR);
        am_app_utils_task_read(AM_APP_TASK_GSENSOR, &QueueElement);
            
        switch(QueueElement.Source)
        {
            case AM_APP_ISR_GPIO:
                am_app_util_gsensor_button2_disble_handler();
              break;  

            // FROM itself.    
            case AM_APP_TASK_GSENSOR:
                am_app_util_gsensor_powerdown();
                break;

            default:
                break;

        }
    }
}
#endif

void am_app_KWD_logic_task(void *pvParameters)
{
    am_app_utils_task_queue_element_t QueueElement;
    
    g_LogicPowerState = APP_LOGIC_POWERING_UP;
//    // power up swirl
//    am_app_logic_led_swirl(1);

    g_LogicPowerState = APP_LOGIC_POWER_ON;

    // Enable system heart beat LED
//    xTimerStart(am_KWD_timers[AM_APP_TIMER_HEART_BEAT], 0);    
//#if VOS_configUSE_GSENSOR  
//    xTimerStart(am_KWD_timers[AM_APP_TIMER_GSENSOR_PERIOD], 0);
//#endif

    while(1)
    {
        am_app_utils_task_read(AM_APP_TASK_LOGIC, &QueueElement);
        
        // there is a button press
        // switching off 
        g_LogicPowerState = APP_LOGIC_POWERING_DOWN;
        am_app_util_buzzer_power_down();

        am_app_logic_system_power_off();

        g_LogicPowerState = APP_LOGIC_POWER_OFF;
        // reinitialize the interrupt
        am_app_logic_button_init();
        while(1)
        {
            am_hal_interrupt_master_disable();
            
            //
            // Only keep flash0 and DTCM0 power on to save power.
            //
            PWRCTRL->MEMPWREN =
                (_VAL2FLD(PWRCTRL_MEMPWREN_DTCM, PWRCTRL_MEMPWREN_DTCM_GROUP0DTCM0) |
                 _VAL2FLD(PWRCTRL_MEMPWREN_FLASH0, PWRCTRL_MEMPWREN_FLASH0_EN));

            SCB->SCR |= _VAL2FLD(SCB_SCR_SLEEPDEEP, 1);
            __DSB();
            #define SYNC_READ       0x5FFF0000

            //
            // CAUTION!!! It is unsafe. Read the value to 0x10001000. 
            // The sram only keep 8k size to 0x10002000. 
            // It's OK under low level optimization, the behavior may different under high lever optimization.
            //
            if ( 1 )                                                           
            {                                                                  
                *((uint32_t*)0x10001000) = *((uint32_t*)SYNC_READ);                   
                //*(&g_ui32BusWriteFlush) = *pui32Flush;     
            }

            
            //
            // Execute the sleep instruction.
            //
            __WFI();
            //
            // Upon wake, execute the Instruction Sync Barrier instruction.
            //
            __ISB();

            //
            // Wake up from deep sleep, power on sram all. There must have no function call, or it will invoke stack region 
            // that has been cleared by sram power down operation.
            //
            PWRCTRL->MEMPWREN =
                (AM_HAL_PWRCTRL_MEMEN_SRAM_384K    |
                 _VAL2FLD(PWRCTRL_MEMPWREN_FLASH0, PWRCTRL_MEMPWREN_FLASH0_EN));
            
            //
            // 6 nop delay.
            //            
            __asm (
            " nop\n"
            " nop\n"
            " nop\n"
            " nop\n"
            " nop\n"
            " nop\n"
            );
 
            //
            // clear STIME configuration.
            //   
            CTIMER->STCFG = 0;
          
            //
            // SWPOI software reset.
            // 
            RSTGEN->SWPOI =
                _VAL2FLD(RSTGEN_SWPOI_SWPOIKEY, RSTGEN_SWPOI_SWPOIKEY_KEYVALUE);
            
            while(1);
        }
    }
}
#endif // #if VOS_MAYA_BOARD

#if VOS_configUSE_PUSH_TO_TALK
//*****************************************************************************
//
// Simple button detection function with debounce
//
//*****************************************************************************
static bool push_to_talk_check_button(uint32_t gpio)
{
    uint64_t pinVal = 0;

    for(uint8_t i = 0; i < 3 ; i++)
    {
#if defined (AM_PART_APOLLO3)
        pinVal = am_hal_gpio_input_read(gpio);
#endif // defined (AM_PART_APOLLO3)

#if defined (AM_PART_APOLLO2)
        pinVal = (am_hal_gpio_input_read() & AM_HAL_GPIO_BIT(gpio));
#endif // defined (AM_PART_APOLLO2)

        if(pinVal)
        {
            return false;
        }
        am_util_delay_us(100);
    }

    return true;
}

void push_to_talk_button_process(void)
{
    // disable interrupt on this pin

    if(push_to_talk_check_button(CTRL_BUTTON3))
    {
#if defined (AM_PART_APOLLO3)
        am_hal_gpio_interrupt_disable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
        am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
#endif 

#if defined (AM_PART_APOLLO2)
        am_hal_gpio_int_disable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
        am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
#endif 
        // button pressed, send a msg to trigger push to talk
        am_app_utils_task_send_fromISR(AM_APP_TASK_AUD_PROCESSING, AM_APP_TASK_AUD_PROCESSING, AM_APP_MESSAGE_SHORT, KEY_WORD_GOT_MESSAGE, NULL);
    }
}

#endif // VOS_configUSE_PUSH_TO_TALK

#if VOS_configUSE_MUTE_MIC
//*****************************************************************************
//
// Simple button detection function with debounce
//
//*****************************************************************************
static bool mute_mic_check_button(uint32_t gpio)
{
    uint64_t pinVal = 0;

    for(uint8_t i = 0; i < 3 ; i++)
    {
#if defined (AM_PART_APOLLO3)
        pinVal = am_hal_gpio_input_read(gpio);
#endif // defined (AM_PART_APOLLO3)

#if defined (AM_PART_APOLLO2)
        pinVal = (am_hal_gpio_input_read() & AM_HAL_GPIO_BIT(gpio));
#endif // defined (AM_PART_APOLLO2)

        if(pinVal)
        {
            return false;
        }
        am_util_delay_us(100);
    }

    return true;
}
static bool bMicStatus = true; // true = mic on, false = mic off

bool bLongPressStatus = false;  // button not pressed
uint16_t ui16LongPressCount = 0;

void mute_mic_long_press_handler(void)
{
    if(bLongPressStatus == false) // enter from ISR
    {
        if(mute_mic_check_button(CTRL_BUTTON4))
        {
#if defined (AM_PART_APOLLO3)
            am_hal_gpio_interrupt_disable(AM_HAL_GPIO_BIT(CTRL_BUTTON4));
            am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON4));
#endif 

#if defined (AM_PART_APOLLO2)
            am_hal_gpio_int_disable(AM_HAL_GPIO_BIT(CTRL_BUTTON4));
            am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON4));
#endif 

            // pressed, start a 100ms timer
            xTimerStartFromISR(am_KWD_timers[AM_APP_TIMER_LONG_PRESS], 0);
            xTimerChangePeriodFromISR(am_KWD_timers[AM_APP_TIMER_LONG_PRESS], pdMS_TO_TICKS(LONG_PRESS_TIMER_PERIOD_MS), 0);
            bLongPressStatus = true;
            ui16LongPressCount++;
        }
    }
    else // enter from timer callback
    {
        ui16LongPressCount++;
        if(ui16LongPressCount > (LONG_PRESS_EFFECTIVE_MS/LONG_PRESS_TIMER_PERIOD_MS))
        {
            // long press over effective period, take action
            AM_APP_LOG_WARNING("== Long press effective! ==\n");
            mute_mic_button_process();

            ui16LongPressCount = 0;
            bLongPressStatus = false;

#if defined (AM_PART_APOLLO3)
            am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON4));
            am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON4));
#endif 

#if defined (AM_PART_APOLLO2)
            am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON4));
            am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON4));
#endif 
            
        }
        else
        {
            // keep counting
            if(mute_mic_check_button(CTRL_BUTTON4))
            {
                // pressed, start a 100ms timer
                xTimerStartFromISR(am_KWD_timers[AM_APP_TIMER_LONG_PRESS], 0);
                xTimerChangePeriodFromISR(am_KWD_timers[AM_APP_TIMER_LONG_PRESS], pdMS_TO_TICKS(LONG_PRESS_TIMER_PERIOD_MS), 0);
            }
            else
            {
                // button released
                AM_APP_LOG_WARNING("== Button released! pressed for %d ms ==\n", (ui16LongPressCount*LONG_PRESS_TIMER_PERIOD_MS));
                
                ui16LongPressCount = 0;
                bLongPressStatus = false;

#if defined (AM_PART_APOLLO3)
                am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON4));
                am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON4));
#endif 

#if defined (AM_PART_APOLLO2)
                am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON4));
                am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON4));
#endif 
            }
            
        }
    }
    
}

void am_app_KWD_timer_longpress_callback(TimerHandle_t xTimer)
{
    mute_mic_long_press_handler();
}


void mute_mic_button_process(void)
{
    // disable interrupt on this pin

    if(mute_mic_check_button(CTRL_BUTTON4))
    {
        AM_CRITICAL_BEGIN_VOS;
        // button pressed, process to mute or unmute the mic
        if(bMicStatus == true)
        {
            // mics are on, mute them
            //
            // Notes: if the system has push-to-talk, we should keep the 
            // functionality of the system, e.g. ble connection
            // Otherwise, we should be able to shut down everything and go to deep sleep
            //
#if defined (AM_PART_APOLLO2)
            am_hal_pdm_disable();
            am_hal_gpio_pin_config(PDM_CLK, AM_HAL_PIN_INPUT); 
            am_hal_gpio_pin_config(PDM_DATA, AM_HAL_PIN_INPUT);
            am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PDM);
#endif // #if defined (AM_PART_APOLLO2)

#if defined (AM_PART_APOLLO3)
            extern void *PDMHandle;
//            am_hal_pdm_disable(PDMHandle);
            am_hal_gpio_pinconfig(PDM_CLK, g_AM_HAL_GPIO_INPUT);
            am_hal_gpio_pinconfig(PDM_DATA, g_AM_HAL_GPIO_INPUT);
//            am_hal_pdm_power_control(PDMHandle, AM_HAL_PDM_POWER_OFF, false);
            PDMDeInit();
#endif // #if defined (AM_PART_APOLLO3)

            am_app_KWD_reset_detected_flag();

#if USE_UNIVERSAL_AUDIO_BUFFER
            am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO]);
            am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED]);
#endif // USE_UNIVERSAL_AUDIO_BUFFER

            bMicStatus = false;

            AM_APP_LOG_WARNING("== MICs are muted! ==\n");
        }
        else
        {
            // mics are off, unmute them
            PDMInit();

            am_app_KWD_reset_detected_flag();

#if USE_UNIVERSAL_AUDIO_BUFFER
            am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO]);
            am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED]);
#endif // USE_UNIVERSAL_AUDIO_BUFFER

            bMicStatus = true;
            AM_APP_LOG_WARNING("== MICs are unmuted! ==\n");
        }
        AM_CRITICAL_END_VOS;
    }
}

#endif // VOS_configUSE_MUTE_MIC
