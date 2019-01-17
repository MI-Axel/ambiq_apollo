
/**
 *  \file appl_pass.h
 *
 *  Application Header File for Phone Alert Status Sensor.
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_APPL_PASS_
#define _H_APPL_PASS_

/* ----------------------------------------- Header File Inclusion */
#include "BT_api.h"
#include "BT_gatt_db_api.h"
#include "gatt_db.h"
#include "appl_gap.h"

/* --------------------------------------------- Global Definitions */
#define ALRT_STATUS_RINGER_STATE_BIT       0
#define ALRT_STATUS_VIBRATOR_STATE_BIT     1
#define ALRT_STATUS_DISP_ALRT_STATE_BIT    2

#define RINGER_SETTING_RINGER_SILENT   0
#define RINGER_SETTING_RINGER_NORMAL   1

#define APPL_PASS_RINGER_CNTRL_PNT_SILENT_MODE           1
#define APPL_PASS_RINGER_CNTRL_PNT_MUTE_ONCE             2
#define APPL_PASS_RINGER_CNTRL_PNT_CANCEL_SILENT_MODE    3

#define appl_set_bit_value(var,pos)\
        var = (var & (~(1 << pos)))|(1 << pos)

#define appl_clear_bit_value(var,pos)\
        var = (var & (~(1 << pos)))

#define appl_get_bit_value(var,pos)\
        (var & (1 << pos))?1:0

/* --------------------------------------------- Functions */
void appl_pass_init(void);
void appl_pass_connect(DEVICE_HANDLE  * dq_handle);
void appl_update_alert_status (UCHAR * val);
void appl_update_ringer_setting (UCHAR * val);
void appl_ringer_setting_timer_expiry_handler (void *data, UINT16 datalen);
void appl_alert_status_timer_expiry_handler (void *data, UINT16 datalen);
void appl_start_trasnfer (GATT_DB_HANDLE handle, UINT16 config);
void appl_stop_transfer (void);
void appl_send_phone_alert_notifications (APPL_HANDLE * handle);
void appl_pass_ringer_control_point_write_handler
     (
        GATT_DB_HANDLE    * handle,
        ATT_VALUE         * value
     );
void appl_pass_read_request_handler
     (
        GATT_DB_HANDLE    * handle
     );
void appl_pass_server_reinitialize (void);

#ifdef APPL_MENU_OPS
#ifdef BT_SW_TXP
void appl_send_alert_status_ntf(void);
void appl_send_ringer_settings_ntf(void);
const char * appl_get_profile_menu (void);
#else
void appl_profile_menu_handler (void);
#endif /* BT_SW_TXP */
void appl_send_alert_status_ntf(void);
void appl_send_ringer_settings_ntf(void);
#endif /* APPL_MENU_OPS */

/* Profile handling */
#define APPL_PROFILE_INIT         appl_pass_init
#define APPL_PROFILE_CONNECT(x)\
        appl_pass_connect(&APPL_GET_DEVICE_HANDLE((*x)))
#define APPL_SEND_MEASUREMENT(x)  appl_send_phone_alert_notifications(x)
#define APPL_PROFILE_DISCONNECT_HANDLER(...) appl_pass_server_reinitialize()
#define GATT_DB_PROFILE_HANDLER  gatt_db_pass_handler
#define APPL_PROFILE_HVN_NTF_COMPLETE_HANDLER(x,y,z)
#define APPL_PROFILE_HVN_IND_COMPLETE_HANDLER(x,y,z)
#define APPL_PROFILE_MTU_UPDT_COMPLETE_HANDLER(x,y)

#define APPL_USE_IDLE_TIMER
#define APPL_IDLE_TIMEOUT           30
#endif /* _H_APPL_PASS_ */


