/* ----------------------------------------------------------------------------
 *	 Preprocessor Definitions
 * ------------------------------------------------------------------------- */

#ifndef ARM_CORTEXM4_TARGET_PROCESSOR_H_
#define ARM_CORTEXM4_TARGET_PROCESSOR_H_

#if defined(__ARMCC_VERSION)
#define VEC_RESTRICT	__restrict
#define VEC_INLINE		__inline
#elif defined (__ICCARM__)
#define VEC_RESTRICT	restrict
#define VEC_INLINE		inline
#elif defined( __GNUC__ )
#define VEC_RESTRICT	restrict
#define VEC_INLINE		inline
#else
#error "Unsupported compiler"
#endif

#if defined( __IAR_SYSTEMS_ICC__ )
#include "Intrinsics.h"
#endif

#if defined( __IAR_SYSTEMS_ICC__ ) || defined( __GNUC__ )

    #define DISABLE_INTERRUPTS() __disable_interrupt()
    #define ENABLE_INTERRUPTS() __enable_interrupt()
#else

	#define DISABLE_INTERRUPTS() __disable_irq()
	#define ENABLE_INTERRUPTS() __enable_irq()
#endif

/**
 * @def FW_RESTRICT
 * @brief Compiler-specific C99 restrict keyword.
 */

#define FW_RESTRICT

#include "StandardDefs.h"

#define awe_fwIsSIMDAllowed(ADDR)    0

#if defined( __GNUC__ )

static inline void __disable_interrupt() { __asm("cpsid i"); }
static inline void __enable_interrupt() { __asm("cpsie i"); }

#endif

/* ----------------------------------------------------------------------
** Cycle counting macros
** ------------------------------------------------------------------- */

static VEC_INLINE void awe_fwCycleInit(void)
{
}

UINT32 aweuser_getCycleCount(void);
UINT32 aweuser_getElapsedCycles(UINT32 start_time, UINT32 end_time);

static VEC_INLINE UINT32 awe_getCycleCount(void)
{
  UINT32 cycles = 0;
  cycles = aweuser_getCycleCount();
  return (cycles);
}


static VEC_INLINE UINT32 awe_getElapsedCycles(UINT32 start_time, UINT32 end_time)
{
  UINT elapsedTime;

  elapsedTime = aweuser_getElapsedCycles(start_time, end_time);
  return elapsedTime;
}

#if defined(__BES2000__)

#define AWE_MOD_SLOW_CODE __attribute__((section(".psram_text")))

#define AWE_FW_SLOW_CODE __attribute__((section(".psram_text")))

#define AWE_PRIO0_FAST_CODE __attribute__((section(".psram_text")))

#define AWE_MOD_FAST_CODE __attribute__((section(".psram_text")))

#endif

#endif	  /* !defined  ARM_CORTEXM4_TARGET_PROCESSOR_H_ */
