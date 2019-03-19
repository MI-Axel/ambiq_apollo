/* ----------------------------------------------------------------------------
 *	 Preprocessor Definitions
 * ------------------------------------------------------------------------- */

#ifndef ARM_CORTEXM7_TARGET_PROCESSOR_H_
#define ARM_CORTEXM7_TARGET_PROCESSOR_H_

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

#if defined ( __ICCARM__ )

    #include "Intrinsics.h"

    #define DISABLE_INTERRUPTS() __disable_interrupt()
    #define ENABLE_INTERRUPTS() __enable_interrupt()

    #define __ssat __SSAT
    #define __clz __CLZ
	#define __schedule_barrier __DSB

#endif

#if defined ( __CC_ARM )

    #define DISABLE_INTERRUPTS()  __disable_irq()
    #define ENABLE_INTERRUPTS()  __enable_irq()

#endif

#if defined( __GNUC__ )

#define DISABLE_INTERRUPTS() __disable_interrupt()
#define ENABLE_INTERRUPTS() __enable_interrupt()

#endif

/**
 * @def FW_RESTRICT
 * @brief Compiler-specific C99 restrict keyword.
 */

#define FW_RESTRICT

#include "StandardDefs.h"

#define awe_fwIsSIMDAllowed(ADDR) 0

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

UINT32 awe_pltGetCycleCount(void);
UINT32 awe_pltElapsedCycles(UINT32 start_time, UINT32 end_time);

static VEC_INLINE UINT32 awe_fwGetCycles(void)
{
  UINT32 cycles = 0;
  cycles = awe_pltGetCycleCount();
  return (cycles);
}


static VEC_INLINE UINT32 awe_fwElapsedCycles(UINT32 start_time, UINT32 end_time)
{
  UINT elapsedTime;
    
  elapsedTime = awe_pltElapsedCycles(start_time, end_time);
  return elapsedTime;
}

#endif	  /* !defined  ARM_CORTEXM7_TARGET_PROCESSOR_H_ */
