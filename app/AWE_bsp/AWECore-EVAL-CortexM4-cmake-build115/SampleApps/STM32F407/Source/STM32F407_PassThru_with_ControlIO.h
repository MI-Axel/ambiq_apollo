/****************************************************************************
 *
 *		Target Tuning Symbol File
 *		-------------------------
 *
 * 		This file is populated with symbol information only for modules
 *		that have the 'isTunable' property checked in the .awd.
 *
 *          Generated on:  08-Jul-2019 10:51:09
 *
 ***************************************************************************/

#ifndef STM32F769_PASSTHRU_WITH_CONTROLIO_CONTROLINTERFACE_H
#define STM32F769_PASSTHRU_WITH_CONTROLIO_CONTROLINTERFACE_H

// ----------------------------------------------------------------------
//  [DCSourceInt]
// Newly created subsystem

#define AWE_DC1_classID 0xBEEF0873
#define AWE_DC1_ID 30001

// int value - Data Value
// Default value: 0
// Range: -2147483648 to 2147483647
#define AWE_DC1_value_HANDLE 0x07531008
#define AWE_DC1_value_MASK 0x00000100
#define AWE_DC1_value_SIZE 0x00000001


// ----------------------------------------------------------------------
//  [SinkInt]
// Newly created subsystem

#define AWE_SinkInt1_classID 0xBEEF086E
#define AWE_SinkInt1_ID 31001

// int value[1] - Captured values
#define AWE_SinkInt1_value_HANDLE 0x87919008
#define AWE_SinkInt1_value_MASK 0x00000100
#define AWE_SinkInt1_value_SIZE 0x00000001



#endif // STM32F769_PASSTHRU_WITH_CONTROLIO_CONTROLINTERFACE_H

