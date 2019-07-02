//*****************************************************************************
//
//! @file am_app_utils_gsenor.h
//!
//! @brief RTOS printf functions for app layer use
//! 
//!
//
//*****************************************************************************
#ifndef AM_APP_UTILS_GSENSOR_H
#define AM_APP_UTILS_GSENSOR_H


extern void am_app_util_gsensor_init(void);
extern void am_app_util_gsensor_process(void);
extern void am_app_util_gsensor_power_down(void);
extern void am_app_util_gsensor_resetTick();

#endif // #ifndef AM_APP_UTILS_GSENSOR_H
