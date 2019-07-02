//*****************************************************************************
//
//! @file am_app_KWD_logic.h
//!
//! @brief 
//! 
//!
//
//*****************************************************************************
#ifndef AM_APP_KWD_LOGIC_H
#define AM_APP_KWD_LOGIC_H

typedef enum logic_power_states{
    APP_LOGIC_POWERING_UP,
    APP_LOGIC_POWER_ON,
    APP_LOGIC_POWERING_DOWN,
    APP_LOGIC_POWER_OFF
}enum_logic_power_states_t;

extern enum_logic_power_states_t g_LogicPowerState;

extern bool g_LogicButtonWakeUp;

extern void am_app_logic_led_all_on(void);
extern void am_app_logic_led_all_off(void);
extern void am_app_logic_led_swirl(uint8_t type);
extern void am_app_logic_button_init(void);
extern void am_app_logic_button_process(void);
extern void am_app_logic_system_power_off(void);


#endif // #ifndef AM_APP_KWD_LOGIC_H
