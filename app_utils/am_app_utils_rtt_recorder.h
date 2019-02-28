/* header file of rtt recorder source file*/

#ifndef AM_RTT_RECORDER_H
#define AM_RTT_RECORDER_H
#include <stdint.h>
#include <stdbool.h>
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"
#include "am_app_utils.h"


extern void am_app_utils_rtt_init(uint8_t* rttBuffer, uint32_t LenBytes);

extern void am_app_utils_rtt_record(void* pBuffer, uint32_t NumBytes);













































#endif
