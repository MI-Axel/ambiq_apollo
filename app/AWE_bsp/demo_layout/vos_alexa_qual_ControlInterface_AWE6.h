/****************************************************************************
 *
 *		Target Tuning Symbol File
 *		-------------------------
 *
 * 		This file is populated with symbol information only for modules
 *		that have an object ID of 30000 or greater assigned.
 *
 *          Generated on:  13-Dec-2019 11:11:43
 *
 ***************************************************************************/

#ifndef VOS_ALEXA_QUAL_CONTROLINTERFACE_AWE6_H
#define VOS_ALEXA_QUAL_CONTROLINTERFACE_AWE6_H

/* The current layout contains no controllable modules.
   To access a module via the control API, it must have an assigned objectID that's 30000 or greater.
   To assign an ObjectID, right-click a module, open Properties, then enter a number under the Build tab. */
// ----------------------------------------------------------------------
// DC1 [DCSourceInt]
// Source buffer holding 1 wire of constant data

#define AWE_DC1_ID 30006

// int value - Data Value
// Default value: 0
// Range: 0 to 1
#define AWE_DC1_value_OFFSET 8
#define AWE_DC1_value_MASK 0x00000100
#define AWE_DC1_value_SIZE -1



#endif // VOS_ALEXA_QUAL_CONTROLINTERFACE_AWE6_H

