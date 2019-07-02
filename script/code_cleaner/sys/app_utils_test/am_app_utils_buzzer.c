//*****************************************************************************
//
//! @file am_app_utils_buzzer.c
//!
//! @brief buzzer interface for Maya
//!
//! Functions for performing buzzer actions
//
//*****************************************************************************
#include "usr_include.h"

#if USE_MAYA

#include "am_util.h"
#include "am_app_utils.h"

//*****************************************************************************
//
// Global Variables
//
//*****************************************************************************
amAppUtilBuzzerCb_t amAppUtilBuzzerCb;

//*****************************************************************************
//
//! @brief Sets the interface for printf calls.
//!
//! @param pfnPrintFunc - Function pointer to be used to print to interface
//!
//! This function initializes the global print function which is used for
//! printf. This allows users to define their own printf interface and pass it
//! in as an am_app_utils_stdio_print_t type. 
//!
//! @return None.
//
//*****************************************************************************

void am_app_util_buzzer_init(void)
{
    //
    // Set nSPKR_PWR
    //
    am_hal_gpio_pinconfig(BUZZER_CAP_PWR_PIN, g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_state_write(BUZZER_CAP_PWR_PIN, AM_HAL_GPIO_OUTPUT_CLEAR);      // enable speaker power
    am_hal_gpio_pinconfig(BUZZER_PWM_OUTPUT_PIN, g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_state_write(BUZZER_PWM_OUTPUT_PIN, AM_HAL_GPIO_OUTPUT_CLEAR);   // clear speaker drive pin


//    vTaskDelay(pdMS_TO_TICKS(500));
    am_util_delay_ms(500);
    
    am_hal_ctimer_clear(BUZZER_PWM_TIMER, BUZZER_PWM_TIMER_SEG);
    //
    // Configure the output pin.
    //
    am_hal_ctimer_output_config(BUZZER_PWM_TIMER,
                                BUZZER_PWM_TIMER_SEG,
                                BUZZER_PWM_OUTPUT_PIN,
                                AM_HAL_CTIMER_OUTPUT_NORMAL,
                                AM_HAL_GPIO_PIN_DRIVESTRENGTH_12MA);

    //
    // Configure a timer to drive the LED.
    //
    am_hal_ctimer_config_single(BUZZER_PWM_TIMER,                   // ui32TimerNumber
                                BUZZER_PWM_TIMER_SEG,               // ui32TimerSegment
                                (AM_HAL_CTIMER_FN_PWM_REPEAT    |   // ui32ConfigVal
                                AM_HAL_CTIMER_HFRC_12MHZ        |
                                AM_HAL_CTIMER_INT_ENABLE) );

    //
    // Set up initial timer periods.
    //
    am_hal_ctimer_period_set(BUZZER_PWM_TIMER,
                             BUZZER_PWM_TIMER_SEG, BUZZER_PERIOD, BUZZER_PERIOD/2);
    am_hal_ctimer_aux_period_set(BUZZER_PWM_TIMER,
                                 BUZZER_PWM_TIMER_SEG, BUZZER_PERIOD, 1);



//    am_hal_interrupt_master_enable();
    
    amAppUtilBuzzerCb.on = false;
    amAppUtilBuzzerCb.fading = false;


}

// return true when fail
bool am_app_util_buzzer_start(void)
{
    bool xResult = true;

#if configUSE_BUZZER
    if(amAppUtilBuzzerCb.on == true)
    {
        return true;    // buzzer already on
    }
    
    
    if(xPortIsInsideInterrupt() == pdTRUE)
    {
        //
        // Send an event to the main radio task
        //
        xResult = am_app_utils_task_send_fromISR(AM_APP_TASK_BUZZER, AM_APP_TASK_BUZZER, AM_APP_MESSAGE_SHORT, EMPTY_MESSAGE, NULL);

        //
        // If the radio task is higher-priority than the context we're currently
        // running from, we should yield now and run the radio task.
        //   

    }
    else 
    {
        //
        // If the radio task is higher priority than the context we're currently
        // running from, we should yield now and run the radio task.
        //        
        xResult = am_app_utils_task_send(AM_APP_TASK_BUZZER, AM_APP_TASK_BUZZER, AM_APP_MESSAGE_SHORT, EMPTY_MESSAGE, NULL);
    }

#endif    // configUSE_BUZZER
    return (xResult == false);

}

void am_app_util_buzzer_process(void)
{
    am_hal_ctimer_clear(BUZZER_PWM_TIMER, BUZZER_PWM_TIMER_SEG);
    //
    // Configure the output pin.
    //
    am_hal_ctimer_output_config(BUZZER_PWM_TIMER,
                                BUZZER_PWM_TIMER_SEG,
                                BUZZER_PWM_OUTPUT_PIN,
                                AM_HAL_CTIMER_OUTPUT_NORMAL,
                                AM_HAL_GPIO_PIN_DRIVESTRENGTH_12MA);
    //
    // Set up initial timer periods.
    //
    am_hal_ctimer_period_set(BUZZER_PWM_TIMER,
                             BUZZER_PWM_TIMER_SEG, BUZZER_PERIOD, BUZZER_PERIOD/2);
    
    //
    // Start the timer.
    //
    am_hal_ctimer_start(BUZZER_PWM_TIMER, BUZZER_PWM_TIMER_SEG);
    amAppUtilBuzzerCb.on = true;
    vTaskDelay(BUZZER_50PER_ON_TIME_MS);

    AM_CRITICAL_BEGIN;
    amAppUtilBuzzerCb.fadingCount   = 0;
    amAppUtilBuzzerCb.fadingOnCount = BUZZER_MAX_FADING_ON_COUNT;
    amAppUtilBuzzerCb.fadingSpeed   = BUZZER_FADING_SPEED_2;
    amAppUtilBuzzerCb.fading        = true;    //start fading

    //
    // Enable interrupts for the Timer we are using on this board.
    //
    NVIC_SetPriority(CTIMER_IRQn, NVIC_configKERNEL_INTERRUPT_PRIORITY);
    NVIC_EnableIRQ(CTIMER_IRQn);
    am_hal_ctimer_int_enable(BUZZER_PWM_TIMER_INT);
    AM_CRITICAL_END;
}

void am_app_util_buzzer_power_up(void)
{

#if configUSE_BUZZER
    am_hal_ctimer_clear(BUZZER_PWM_TIMER, BUZZER_PWM_TIMER_SEG);
    //
    // Configure the output pin.
    //
    am_hal_ctimer_output_config(BUZZER_PWM_TIMER,
                                BUZZER_PWM_TIMER_SEG,
                                BUZZER_PWM_OUTPUT_PIN,
                                AM_HAL_CTIMER_OUTPUT_NORMAL,
                                AM_HAL_GPIO_PIN_DRIVESTRENGTH_12MA);
    //
    // Set up initial timer periods.
    //
    am_hal_ctimer_period_set(BUZZER_PWM_TIMER,
                             BUZZER_PWM_TIMER_SEG, BUZZER_C7_PERIOD, BUZZER_C7_PERIOD/2);
    
//    vTaskDelay(pdMS_TO_TICKS(1)); // MUST!!! To avoid abnormal long time delay .
    
    uint8_t xDelaySwirl = 50;
    //
    // Start the timer.
    //
    am_hal_ctimer_start(BUZZER_PWM_TIMER, BUZZER_PWM_TIMER_SEG);
//    amAppUtilBuzzerCb.on = true;

    //vTaskDelay(pdMS_TO_TICKS(125));
//    am_util_delay_ms(125);

    am_hal_gpio_state_write(LED_D1, AM_HAL_GPIO_OUTPUT_SET);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D2, AM_HAL_GPIO_OUTPUT_SET);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D3, AM_HAL_GPIO_OUTPUT_SET);
    am_util_delay_ms(xDelaySwirl/2);
    am_hal_ctimer_period_set(BUZZER_PWM_TIMER,
                             BUZZER_PWM_TIMER_SEG, BUZZER_E7_PERIOD, BUZZER_E7_PERIOD/2);
    am_util_delay_ms(xDelaySwirl/2);

    am_hal_gpio_state_write(LED_D4, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D1, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D2, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D3, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl/2);
    am_hal_ctimer_period_set(BUZZER_PWM_TIMER,
                            BUZZER_PWM_TIMER_SEG, BUZZER_G7_PERIOD, BUZZER_G7_PERIOD/2);
    am_util_delay_ms(xDelaySwirl/2);

    am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D4, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D1, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl/2);
    am_hal_ctimer_period_set(BUZZER_PWM_TIMER,
                            BUZZER_PWM_TIMER_SEG, BUZZER_C8_PERIOD, BUZZER_C8_PERIOD/2);
    am_util_delay_ms(xDelaySwirl/2);

    am_hal_gpio_state_write(LED_D2, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D3, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D4, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D1, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D2, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D3, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D4, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D1, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D2, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D3, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D4, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_CLEAR);

    amAppUtilBuzzerCb.on                = false;
    am_hal_ctimer_stop(BUZZER_PWM_TIMER, BUZZER_PWM_TIMER_SEG);
    am_hal_gpio_pinconfig(BUZZER_PWM_OUTPUT_PIN, g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_state_write(BUZZER_PWM_OUTPUT_PIN, AM_HAL_GPIO_OUTPUT_CLEAR);   // disable pwm output pin
    am_hal_gpio_state_write(BUZZER_CAP_PWR_PIN, AM_HAL_GPIO_OUTPUT_CLEAR);      // enable speaker power
#else    // configUSE_BUZZER

    uint8_t xDelaySwirl = 50;

    am_hal_gpio_state_write(LED_D1, AM_HAL_GPIO_OUTPUT_SET);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D2, AM_HAL_GPIO_OUTPUT_SET);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D3, AM_HAL_GPIO_OUTPUT_SET);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D4, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D1, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D2, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D3, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);

    am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D4, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D1, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);

    am_hal_gpio_state_write(LED_D2, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D3, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D4, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D1, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D2, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D3, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D4, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_SET);
    am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_util_delay_ms(xDelaySwirl);
    am_hal_gpio_state_write(LED_D1, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D2, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D3, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D4, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D5, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D6, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D7, AM_HAL_GPIO_OUTPUT_CLEAR);
    am_hal_gpio_state_write(LED_D8, AM_HAL_GPIO_OUTPUT_CLEAR);

#endif    // configUSE_BUZZER
}

void am_app_util_buzzer_power_down(void)
{
    am_hal_ctimer_clear(BUZZER_PWM_TIMER, BUZZER_PWM_TIMER_SEG);
    am_hal_gpio_state_write(BUZZER_CAP_PWR_PIN, AM_HAL_GPIO_OUTPUT_CLEAR);      // enable speaker power
    //
    // Configure the output pin.
    //
    am_hal_ctimer_output_config(BUZZER_PWM_TIMER,
                                BUZZER_PWM_TIMER_SEG,
                                BUZZER_PWM_OUTPUT_PIN,
                                AM_HAL_CTIMER_OUTPUT_NORMAL,
                                AM_HAL_GPIO_PIN_DRIVESTRENGTH_12MA);
    //
    // Set up initial timer periods.
    //
    am_hal_ctimer_period_set(BUZZER_PWM_TIMER,
                             BUZZER_PWM_TIMER_SEG, BUZZER_C8_PERIOD, BUZZER_C8_PERIOD/2);
    
    //
    // Start the timer.
    //
    am_hal_ctimer_start(BUZZER_PWM_TIMER, BUZZER_PWM_TIMER_SEG);
    amAppUtilBuzzerCb.on = true;

    vTaskDelay(pdMS_TO_TICKS(250));
//    am_util_delay_ms(250);
    am_hal_ctimer_period_set(BUZZER_PWM_TIMER,
                             BUZZER_PWM_TIMER_SEG, BUZZER_G7_PERIOD, BUZZER_G7_PERIOD/2);
    vTaskDelay(pdMS_TO_TICKS(250));
//    am_util_delay_ms(250);
    am_hal_ctimer_period_set(BUZZER_PWM_TIMER,
                            BUZZER_PWM_TIMER_SEG, BUZZER_E7_PERIOD, BUZZER_E7_PERIOD/2);
    vTaskDelay(pdMS_TO_TICKS(250));
//    am_util_delay_ms(250);

    am_hal_ctimer_period_set(BUZZER_PWM_TIMER,
                            BUZZER_PWM_TIMER_SEG, BUZZER_C7_PERIOD, BUZZER_C7_PERIOD/2);
    vTaskDelay(pdMS_TO_TICKS(500));
//    am_util_delay_ms(500);

    amAppUtilBuzzerCb.on                = false;
    am_hal_ctimer_stop(BUZZER_PWM_TIMER, BUZZER_PWM_TIMER_SEG);
    am_hal_gpio_pinconfig(BUZZER_PWM_OUTPUT_PIN, g_AM_HAL_GPIO_OUTPUT);
    am_hal_gpio_state_write(BUZZER_PWM_OUTPUT_PIN, AM_HAL_GPIO_OUTPUT_CLEAR);   // disable pwm output pin
    am_hal_gpio_state_write(BUZZER_CAP_PWR_PIN, AM_HAL_GPIO_OUTPUT_CLEAR);      // enable speaker power
   
}
void am_app_util_buzzer_interrupt_routine(void)
{
    if(amAppUtilBuzzerCb.fading == true)
    {
        amAppUtilBuzzerCb.fadingCount++;        
        if(amAppUtilBuzzerCb.fadingOnCount <= 100)//30)
        {
        }
        else
        {
            amAppUtilBuzzerCb.fadingOnCount -= amAppUtilBuzzerCb.fadingSpeed;
        }
        am_hal_ctimer_period_set(BUZZER_PWM_TIMER,
             BUZZER_PWM_TIMER_SEG, BUZZER_PERIOD, amAppUtilBuzzerCb.fadingOnCount);
        
        if(amAppUtilBuzzerCb.fadingOnCount < 150)
        {
            amAppUtilBuzzerCb.fadingSpeed = BUZZER_FADING_SPEED_1;
            // turn off power
            am_hal_gpio_state_write(BUZZER_CAP_PWR_PIN, AM_HAL_GPIO_OUTPUT_SET);   // disable speaker power
        }
        
        if(amAppUtilBuzzerCb.fadingCount >= BUZZER_MAX_FADING_COUNT)
        {
            amAppUtilBuzzerCb.fading            = false;
            amAppUtilBuzzerCb.fadingCount       = 0;
            amAppUtilBuzzerCb.fadingOnCount     = BUZZER_MAX_FADING_ON_COUNT;
            amAppUtilBuzzerCb.fadingSpeed       = BUZZER_FADING_SPEED_2;
            amAppUtilBuzzerCb.on                = false;
            am_hal_ctimer_stop(BUZZER_PWM_TIMER, BUZZER_PWM_TIMER_SEG);
            am_hal_gpio_pinconfig(BUZZER_PWM_OUTPUT_PIN, g_AM_HAL_GPIO_OUTPUT);
            am_hal_gpio_state_write(BUZZER_PWM_OUTPUT_PIN, AM_HAL_GPIO_OUTPUT_CLEAR);   // disable pwm output pin
            am_hal_gpio_state_write(BUZZER_CAP_PWR_PIN, AM_HAL_GPIO_OUTPUT_CLEAR);      // enable speaker power
            am_hal_ctimer_int_disable(BUZZER_PWM_TIMER_INT);
            NVIC_DisableIRQ(CTIMER_IRQn);
        }
    }   

}
#endif    // USE_MAYA
