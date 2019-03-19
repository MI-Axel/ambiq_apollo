/****************************************************************************
 *
 *		Target Tuning Symbol File
 *		-------------------------
 *
 *          Generated on:  15-Nov-2018 10:16:41
 *
 ***************************************************************************/

#ifndef AM_2CM_FBF_SCNR_THF_NTSIMPLE_H
#define AM_2CM_FBF_SCNR_THF_NTSIMPLE_H

// ----------------------------------------------------------------------
// Sink3 [Sink]
// Copies the data at the input pin and stores it in an internal buffer.

#define AWE_Sink3_ID 30000

// int enable - To enable or disable the plotting.
// Default value: 0
// Range: unrestricted
#define AWE_Sink3_enable_OFFSET 8
#define AWE_Sink3_enable_MASK 0x00000100
#define AWE_Sink3_enable_SIZE -1

// float value[1] - Captured values.
#define AWE_Sink3_value_OFFSET 9
#define AWE_Sink3_value_MASK 0x00000200
#define AWE_Sink3_value_SIZE 1

// float yRange[2] - Y-axis range.
// Default value:
//     -5  5
// Range: unrestricted
#define AWE_Sink3_yRange_OFFSET 10
#define AWE_Sink3_yRange_MASK 0x00000400
#define AWE_Sink3_yRange_SIZE 2



#endif // AM_2CM_FBF_SCNR_THF_NTSIMPLE_H

