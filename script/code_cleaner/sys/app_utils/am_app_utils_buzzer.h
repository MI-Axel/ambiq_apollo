//*****************************************************************************
//
//! @file am_app_utils_buzzer.h
//!
//! @brief RTOS printf functions for app layer use
//! 
//!
//
//*****************************************************************************
#ifndef AM_APP_UTILS_BUZZER_H
#define AM_APP_UTILS_BUZZER_H

// Macros
#define BUZZER_TIMER_CLOCK_HZ       12000000    // CTimer clock frequency
#define BUZZER_FREQ_HZ              4500        // approx. C Sharp 8 
#define BUZZER_PERIOD               (BUZZER_TIMER_CLOCK_HZ/BUZZER_FREQ_HZ)

// C7 Double high C
#define BUZZER_C7_FREQ_HZ           2093
#define BUZZER_C7_PERIOD            (BUZZER_TIMER_CLOCK_HZ/BUZZER_C7_FREQ_HZ)

// E7
#define BUZZER_E7_FREQ_HZ           2637
#define BUZZER_E7_PERIOD            (BUZZER_TIMER_CLOCK_HZ/BUZZER_E7_FREQ_HZ)

// G7 
#define BUZZER_G7_FREQ_HZ           3136
#define BUZZER_G7_PERIOD            (BUZZER_TIMER_CLOCK_HZ/BUZZER_G7_FREQ_HZ)

//C8 Eighth octave 	4186
#define BUZZER_C8_FREQ_HZ           4186
#define BUZZER_C8_PERIOD            (BUZZER_TIMER_CLOCK_HZ/BUZZER_C8_FREQ_HZ)

#define BUZZER_50PER_ON_TIME_MS     pdMS_TO_TICKS(100)         // 50% pwm on period of the buzzer
#define BUZZER_MAX_FADING_COUNT     4000        // less than 1 sec
#define BUZZER_MAX_FADING_ON_COUNT  1500        // max/starting duty for fading
#define BUZZER_FADING_SPEED_1       1           // in unit of period, higher value -> faster fade
#define BUZZER_FADING_SPEED_2       2           // in unit of period 

#define BUZZER_MIN_CHARGE_TIME_MS   500         // minimum time to guarrantee the charge of buzzer cap


#define BUZZER_CAP_PWR_PIN          38          // GPIO to control the buzzer power
#define BUZZER_PWM_OUTPUT_PIN       44          // GPIO to control the buzzer pwm

#define BUZZER_PWM_TIMER            1           // Ctimer number
#define BUZZER_PWM_TIMER_SEG        AM_HAL_CTIMER_TIMERA    // Ctimer pwm
#define BUZZER_PWM_TIMER_INT        AM_HAL_CTIMER_INT_TIMERA1C0 // Ctimer interrupt

typedef struct 
{
    bool        on;            // buzzer is on
    bool        fading;        // buzzer tone is fading
    uint32_t    fadingCount;   // counter to indicate the fading duration
    uint32_t    fadingOnCount; // 
    uint8_t     fadingSpeed;   // to control the fading speed of the tone
    
}amAppUtilBuzzerCb_t;

extern amAppUtilBuzzerCb_t amAppUtilBuzzerCb;

extern void am_app_util_buzzer_init(void);
extern bool am_app_util_buzzer_start(void);
extern void am_app_util_buzzer_process(void);
extern void am_app_util_buzzer_power_up(void);
extern void am_app_util_buzzer_power_down(void);
extern void am_app_util_buzzer_interrupt_routine(void);

#endif // #ifndef AM_APP_UTILS_BUZZER_H
