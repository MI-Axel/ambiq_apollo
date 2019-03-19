/* ----------------------------------------------------------------------------
 *	 Preprocessor Definitions
 * ------------------------------------------------------------------------- */

#ifndef TARGET_PROCESSOR_H_
#define TARGET_PROCESSOR_H_

#if defined(WIN32)
#include "Targets/Win_TargetProcessor.h"
#elif defined(__ADSP21000__)
#include "Targets/ADI_SHARC_TargetProcessor.h"
#elif defined(__ADSPBLACKFIN__)
#include "Targets/ADI_Blackfin_TargetProcessor.h"
#elif (defined(DSPC_CORTEX_M) && defined(CORE_M4))
#include "Targets/ARM_CortexM4_TargetProcessor.h"
#elif (defined(DSPC_CORTEX_M) && defined(CORE_M7))
#include "Targets/ARM_CortexM7_TargetProcessor.h"
#elif defined(HEXAGON)
#include "Targets/Generic_TargetProcessor.h"
#elif defined(XTENSA)
#include "Targets/Generic_TargetProcessor.h"
#elif defined(IMX25)
#include "Targets/Generic_TargetProcessor.h"
#elif defined(DSPC_CORTEX_A)
#include "Targets/Generic_TargetProcessor.h"
#elif defined(LINUX)
#include "Targets/Generic_TargetProcessor.h"
#else
//#error "This processor is not defined"
#include "Targets/Generic_TargetProcessor.h"
#endif


#ifndef VEC_RESTRICT
#error VEC_RESTRICT undefined
//#define VEC_RESTRICT
#endif

#ifndef VEC_INLINE
#error VEC_INLINE undefined
//#define VEC_INLINE
#endif

/* ----------------------------------------------------------------------
** Default memory section definitions if they are not defined above.
** ------------------------------------------------------------------- */

#if !defined(AWE_MOD_SLOW_CODE)
#define AWE_MOD_SLOW_CODE
#endif

#if !defined(AWE_MOD_FAST_CODE)
#define AWE_MOD_FAST_CODE
#endif

#if !defined(AWE_FW_SLOW_CODE)
#define AWE_FW_SLOW_CODE
#endif

#if !defined(AWE_FW_FAST_CODE)
#define AWE_FW_FAST_CODE
#endif

#if !defined(AWE_USB_INTERNAL_CODE)
#define AWE_USB_INTERNAL_CODE
#endif

#if !defined(AWE_PRIO0_FAST_CODE)
#define AWE_PRIO0_FAST_CODE
#endif

#if !defined(AWE_MOD_SLOW_DM_DATA)
#define AWE_MOD_SLOW_DM_DATA
#endif

#if !defined(AWE_MOD_FAST_DM_DATA)
#define AWE_MOD_FAST_DM_DATA
#endif

#if !defined(AWE_MOD_SLOW_PM_DATA)
#define AWE_MOD_SLOW_PM_DATA
#endif

#if !defined(AWE_MOD_FAST_PM_DATA)
#define AWE_MOD_FAST_PM_DATA
#endif

#if !defined(AWE_FW_SLOW_DM_DATA)
#define AWE_FW_SLOW_DM_DATA
#endif

#if !defined(AWE_FW_FAST_DM_DATA)
#define AWE_FW_FAST_DM_DATA
#endif

#if !defined(AWE_FW_SLOW_PM_DATA)
#define AWE_FW_SLOW_PM_DATA
#endif

#if !defined(AWE_FW_FAST_PM_DATA)
#define AWE_FW_FAST_PM_DATA
#endif

#if !defined(AWE_USB_INTERNAL_DATA)
#define AWE_USB_INTERNAL_DATA
#endif

#if !defined(AWE_FAST_DMA_DATA)
#define AWE_FAST_DMA_DATA
#endif

#if !defined(AWE_MOD_SLOW_DM_CONST)
#define AWE_MOD_SLOW_DM_CONST
#endif

#if !defined(AWE_MOD_FAST_DM_CONST)
#define AWE_MOD_FAST_DM_CONST
#endif

#if !defined(AWE_MOD_SLOW_PM_CONST)
#define AWE_MOD_SLOW_PM_CONST
#endif

#if !defined(AWE_MOD_FAST_PM_CONST)
#define AWE_MOD_FAST_PM_CONST
#endif

#if !defined(AWE_MOD_SLOW_ANY_DATA)
#define AWE_MOD_SLOW_ANY_DATA
#endif

#if !defined(AWE_MOD_FAST_ANY_DATA)
#define AWE_MOD_FAST_ANY_DATA
#endif

#if !defined(AWE_MOD_SLOW_ANY_CONST)
#define AWE_MOD_SLOW_ANY_CONST
#endif

#if !defined(AWE_MOD_FAST_ANY_CONST)
#define AWE_MOD_FAST_ANY_CONST
#endif

#if !defined(AWE_FW_SLOW_DM_CONST)
#define AWE_FW_SLOW_DM_CONST
#endif

#if !defined(AWE_FW_FAST_DM_CONST)
#define AWE_FW_FAST_DM_CONST
#endif

#if !defined(AWE_FW_SLOW_PM_CONST)
#define AWE_FW_SLOW_PM_CONST
#endif

#if !defined(AWE_FW_FAST_PM_CONST)
#define AWE_FW_FAST_PM_CONST
#endif

#if !defined(AWE_FW_SLOW_ANY_DATA)
#define AWE_FW_SLOW_ANY_DATA
#endif

#if !defined(AWE_FW_FAST_ANY_DATA)
#define AWE_FW_FAST_ANY_DATA
#endif

#if !defined(AWE_FW_WIRE_DATA)
#define AWE_FW_WIRE_DATA
#endif

#if !defined(AWE_FW_SLOW_ANY_CONST)
#define AWE_FW_SLOW_ANY_CONST
#endif

#if !defined(AWE_FW_FAST_ANY_CONST)
#define AWE_FW_FAST_ANY_CONST
#endif

#if !defined(AWE_OPTIMIZE_FOR_SPEED)
#define AWE_OPTIMIZE_FOR_SPEED
#endif

#if !defined(AWE_OPTIMIZE_FOR_SPACE)
#define AWE_OPTIMIZE_FOR_SPACE
#endif

#if !defined(AWE_OPTIMIZE_OFF)
#define AWE_OPTIMIZE_OFF
#endif

#endif	  /* !defined  TARGET_PROCESSOR_H_ */
