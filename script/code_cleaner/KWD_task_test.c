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




#include "am_audio_buffer.h"




//#define USE_QSD_DEBUG



extern void am_app_KWD_codec_encode(void *, const void *, size_t, void *, size_t, ssize_t *);
void mute_mic_button_process(void);

bool g_bEnableWakeWordDetection;
bool g_bAmaIsReady = false;





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





                break;

            case AM_APP_MESSAGE_LONG:
                transmit_length = (int32_t)QueueElement.info.ui32Length;
                while(transmit_length > 0)
                {


                    
                    if(transmit_length < UART_TRANSMIT_BUFFER)
                    {                
                        AM_CRITICAL_BEGIN_VOS;
//                        am_app_utils_ring_buffer_pop(QueueElement.pDataBuffer, &transmit_buff,
//                                                    transmit_length, FALSE);
                        am_app_utils_ring_buffer_pop(QueueElement.pDataBuffer, &transmit_buff,
                                                        transmit_length);

                        AM_CRITICAL_END_VOS;





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


                        








}







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


                


              
                transmit_length = (int32_t)strlen(&g_prStdioBuff[QueueElement.info.ui32Indx]); 
               
                configASSERT(transmit_length < AM_APP_PRINTF_BUFFSIZE);
                
                for(index=0; index < transmit_length; index++)
                {
                    transmit_buff[index + color_offset] = g_prStdioBuff[QueueElement.info.ui32Indx + index]; 
                }
                transmit_buff[transmit_length + color_offset] = NULL;


                


                break;
            default: 
                break;
        }
    
    }


}

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


    }

}
//****************************************************************************
//
// RTT switch task to turn on/off RTT recorder
//
//****************************************************************************


//*****************************************************************************
//
// AWE task to execute the AWE frame work
//
//*****************************************************************************


#define QSD_OFF_DELAY_COUNT     200      // 1 count is ~5ms
uint16_t ui16QsdOffDelayCount = 0;      // "QSD off" means QSD detected quiet environment 
                                        // and turns AWE processing off
void am_app_KWD_AWE_processing_task(void *pvParameters)
{
    am_app_utils_task_queue_element_t QueueElement;
    int32_t in32LRSample[AWE_FRAME_SIZE];





    while(1)
    {
        am_app_utils_task_read(AM_APP_TASK_AUD_PROCESSING, &QueueElement);

        switch(QueueElement.ui32MessageType)
        {
            case AM_APP_MESSAGE_SHORT:


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


                            // enable push to talk interrupt again
                            am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(CTRL_BUTTON3));
                            am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(CTRL_BUTTON3));


                        }
                    }

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
        



        if (qsdFlag || g_ui8KwdDetectedFlag || g_ui8PushTalkFlag || g_ui8ProvideSpeechFlag)
        {
            // Place the samples in the AWE processing buffers


            am_app_KWD_AWE_handler(in32LRSample);
            ui16QsdOffDelayCount = QSD_OFF_DELAY_COUNT;


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


            }
            else
            {








//                AM_CRITICAL_BEGIN_VOS;
//				am_audio_buffer_stereo_to_mono(in32LRSample, QueueElement.info.ui32Length);
//                am_audio_buffer_push(AM_AUDIO_BUFFER_MONO, in32LRSample, QueueElement.info.ui32Length / 2);
//				AM_CRITICAL_END_VOS;
            }



        }
        /*}}}*/

        am_app_KWD_AWE_handler(in32LRSample);


//        AM_CRITICAL_END_VOS;
        



        awe_fwTick(&g_AWEInstance);

        if (g_bAudioPump2Active == TRUE)
        {
            g_bAudioPump2Active = FALSE;


        }
     }

}




//*****************************************************************************
//
// AWE task to execute the AWE frame work
//
//*****************************************************************************


//*****************************************************************************
//
// AWE result output and tick task.
//
//*****************************************************************************

void am_app_KWD_AWE_tick_task(void *pvParameters)
{


    am_app_utils_task_queue_element_t QueueElement;

    while(1)
    {
       
        am_app_utils_task_read(AM_APP_TASK_AWE_TICK, &QueueElement);



            awe_fwTick(&g_AWEInstance);

        // Indicate that this idle loop call is getting CPU attention
//        vTaskDelay(xDelay5ms);
    }
}



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



                break;



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


 


//                          vTaskSuspendAll();
                        am_app_KWD_codec_encode(NULL, p_CodecInBuf, CODEC_IN_RING_BUFF_SIZE,
                                p_CodecOutBuf, CODEC_OUT_RING_BUFF_SIZE, &i32CompressedLen);
//                          xTaskResumeAll();


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


//                            }
//                        xTaskResumeAll();
//                        AM_CRITICAL_END_VOS;




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



//                #endif //#if configUSE_AUDIO_POST_BUFF




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

                                        am_app_KWD_AMA_stream_send(g_BleDataBuffer, index);





                                    index = 0;
                                }
                            }
                            AM_CRITICAL_BEGIN;
                            ui32StreamLen = am_app_utils_get_ring_buffer_status(QueueElement.pDataBuffer);
                            AM_CRITICAL_END;
                            
                        }
                    }
    


                break;
            
            default: 
                break;

        }
        
    }
}


//*****************************************************************************
//
// Software timer callback functions
//
//*****************************************************************************
void am_app_KWD_timer_heart_beat_callback(TimerHandle_t xTimer)
{








    am_hal_gpio_state_write(LED_SYSTEM, AM_HAL_GPIO_OUTPUT_TOGGLE);

    






		


}


void am_app_KWD_timer_postbuff_timeout_callback(TimerHandle_t xTimer)
{
    am_app_KWD_reset_detected_flag();

    am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO]);
    am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED]);


    AM_APP_LOG_INFO("am_app_KWD_timer_postbuff_timeout_callback()\n");









}





void am_app_KWD_logic_task(void *pvParameters)
{
    am_app_utils_task_queue_element_t QueueElement;
    
    g_LogicPowerState = APP_LOGIC_POWERING_UP;
//    // power up swirl
//    am_app_logic_led_swirl(1);

    g_LogicPowerState = APP_LOGIC_POWER_ON;

    // Enable system heart beat LED
//    xTimerStart(am_KWD_timers[AM_APP_TIMER_HEART_BEAT], 0);    
//#if configUSE_GSENSOR  
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





        // button pressed, send a msg to trigger push to talk
        am_app_utils_task_send_fromISR(AM_APP_TASK_AUD_PROCESSING, AM_APP_TASK_AUD_PROCESSING, AM_APP_MESSAGE_SHORT, KEY_WORD_GOT_MESSAGE, NULL);
    }
}




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






            am_app_KWD_reset_detected_flag();


            am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO]);
            am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED]);


            bMicStatus = false;

            AM_APP_LOG_WARNING("== MICs are muted! ==\n");
        }
        else
        {
            // mics are off, unmute them
            PDMInit();

            am_app_KWD_reset_detected_flag();


            am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_MONO]);
            am_app_utils_flush_ring_buffer(&am_audio_ring_buffers[AM_AUDIO_BUFFER_ENCODED]);


            bMicStatus = true;
            AM_APP_LOG_WARNING("== MICs are unmuted! ==\n");
        }
        AM_CRITICAL_END_VOS;
    }
}


