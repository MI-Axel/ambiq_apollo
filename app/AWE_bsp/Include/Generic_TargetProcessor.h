/* ----------------------------------------------------------------------------
 *	 Preprocessor Definitions
 * ------------------------------------------------------------------------- */

#ifndef GENERIC_TARGET_PROCESSOR_H_
#define GENERIC_TARGET_PROCESSOR_H_

#ifdef _MSC_VER
#define VEC_RESTRICT	__restrict
#define VEC_INLINE		__inline
#endif

#ifdef __ARMCC_VERSION
#define VEC_RESTRICT	__restrict
#define VEC_INLINE		__inline
#endif

#ifdef __GNUC__
#if defined(DMX) || defined(HMD)
#define VEC_RESTRICT
#else
#define VEC_RESTRICT	__restrict__
#endif
#define VEC_INLINE		__inline__
#endif

#ifdef __TI_COMPILER_VERSION__
#define VEC_RESTRICT	restrict
#define VEC_INLINE		inline
#endif

#ifdef __VISUALDSPVERSION__
#define VEC_RESTRICT	restrict
#define VEC_INLINE		inline
#else
#if defined(__CCESVERSION__)
#define VEC_RESTRICT	restrict
#define VEC_INLINE		inline
#endif
#endif

#ifdef __ICCARM__
#define VEC_RESTRICT	restrict
#define VEC_INLINE		inline
#endif

#if defined(WIN32)
#include "Windows.h"
#define DISABLE_INTERRUPTS()
#define ENABLE_INTERRUPTS()
#endif

#ifdef DSPC_CORTEX_A
#define DISABLE_INTERRUPTS()
#define ENABLE_INTERRUPTS()
#define USE_SIMD4
#include <time.h>
#endif // DSPC_CORTEX_A

#if defined(LINUX) && LINUX != 0
#define DISABLE_INTERRUPTS()
#define ENABLE_INTERRUPTS()
#define INT64 long long
#include <time.h>
#endif // LINUX

#ifdef CEVA_X2
#define DISABLE_INTERRUPTS()
#define ENABLE_INTERRUPTS()
#endif

#ifdef OMAP_DSP
#define DISABLE_INTERRUPTS()
#define ENABLE_INTERRUPTS()
#define INT64			long long
#endif // OMAP_DSP

#ifdef __ADSP21000__
#define USE_SIMD2
#endif	  //  __ADSP21000__

#ifdef __2116x__
#include <def21161.h>
#endif //2116x__

#ifdef __2126x__
#include <def21262.h>
#ifdef __ECC__
asm("#include <def21262.h>");
#define DISABLE_INTERRUPTS()		asm("bit clr MODE1 IRPTEN; nop; nop;")
#define ENABLE_INTERRUPTS()			   asm("bit set MODE1 IRPTEN; nop; nop;")
#endif
#endif //__2126x__

#ifdef __2136x__
#if defined(__ADSP21367__) || defined(__ADSP21368__) || defined(__ADSP21369__)
#include <def21369.h>
#ifdef __ECC__
asm("#include <def21369.h>");
#define DISABLE_INTERRUPTS()		asm("bit clr MODE1 IRPTEN; nop; nop;")
#define ENABLE_INTERRUPTS()			   asm("bit set MODE1 IRPTEN; nop; nop;")
#endif

#else
#include <def21365.h>
#ifdef __ECC__
asm("#include <def21364.h>");
#define DISABLE_INTERRUPTS()		asm("bit clr MODE1 IRPTEN; nop; nop;")
#define ENABLE_INTERRUPTS()			   asm("bit set MODE1 IRPTEN; nop; nop;")
#endif
#endif
#endif //__2136x__

#ifdef __2137x__
#include <def21375.h>
#ifdef __ECC__
asm("#include <def21375.h>");
#define DISABLE_INTERRUPTS()		asm("bit clr MODE1 IRPTEN; nop; nop;")
#define ENABLE_INTERRUPTS()			   asm("bit set MODE1 IRPTEN; nop; nop;")
#endif

/* Define the macro if anomaly exists */
#define WORKAROUND_FOR_ANOMALY_15000004
#define WORKAROUND_FOR_ANOMALY_09000018

#endif //__2137x__

#ifdef __ADSP21469__
#include <def21469.h>
#ifdef __ECC__
asm("#include <def21469.h>");
#define DISABLE_INTERRUPTS()		asm("bit clr MODE1 IRPTEN; nop; nop;")
#define ENABLE_INTERRUPTS()			   asm("bit set MODE1 IRPTEN; nop; nop;")
#endif

/* Define the macro if anomaly exists */
#define WORKAROUND_FOR_ANOMALY_15000004
#endif //__ADSP21469__

#ifdef __ADSP21479__
#include <def21479.h>
#ifdef __ECC__
asm("#include <def21479.h>");
#define DISABLE_INTERRUPTS()		asm("bit clr MODE1 IRPTEN; nop; nop;")
#define ENABLE_INTERRUPTS()			   asm("bit set MODE1 IRPTEN; nop; nop;")
#endif

/* Define the macro if anomaly exists */
#define WORKAROUND_FOR_ANOMALY_15000004
#endif //__ADSP21479__


#ifdef __ADSP21489__
#include <def21489.h>
#ifdef __ECC__
asm("#include <def21489.h>");
#define DISABLE_INTERRUPTS()		asm("bit clr MODE1 IRPTEN; nop; nop;")
#define ENABLE_INTERRUPTS()			   asm("bit set MODE1 IRPTEN; nop; nop;")
#endif

/* Define the macro if anomaly exists */
#define WORKAROUND_FOR_ANOMALY_15000004
#endif //__ADSP21489__

#ifdef __ADSPBLACKFIN__

#if defined(__ADSPBF537__)
#include <cdefbf537.h>
#include <defbf537.h>
#elif defined(__ADSPBF561__)
#include <cdefbf561.h>
#include <defbf561.h>
#elif defined(__ADSPBF527__)
#include <cdefbf527.h>
#include <defbf527.h>
#elif defined(__ADSPBF548__)
#include <cdefBF548.h>
#include <defBF548.h>
#elif defined(__ADSPBF592A__)
#include <cdefBF592-A.h>
#include <defBF592-A.h>
#elif defined(__ADSPBF609__)
#include <cdefBF609.h>
#include <defBF609.h>
#elif defined(__ADSPBF707__)
#include <cdefBF707.h>
#include <defBF707.h>
#else
// For now, assume 532/533/531
#include <cdefbf532.h>
#include <defbf532.h>
#endif

#include <ccblkfn.h>

#define DISABLE_INTERRUPTS()	{\
								asm("SSYNC;");\
								unsigned int imask = cli()

#define ENABLE_INTERRUPTS()		asm("SSYNC;");\
								sti(imask);\
								}
#endif

#if defined(HMD) || defined(DMX)
#include <xtensa/xtruntime.h>
#define DISABLE_INTERRUPTS()	{ \
		unsigned nPrevIntState = XTOS_SET_INTLEVEL(XCHAL_EXCM_LEVEL); \

#define ENABLE_INTERRUPTS()		\
		XTOS_RESTORE_JUST_INTLEVEL(nPrevIntState); \
								}

#else
#if defined(DSPC_CORTEX_M) || defined(DSPC_CORTEX_R) || defined(CHIP_WM0010) || defined(XTENSA) || defined(XTENSA2)

#define DISABLE_INTERRUPTS()
#define ENABLE_INTERRUPTS()

#endif
#endif

#if defined(_TMS320C6X)
#include <c6x.h>				/* IER,ISR,CSR registers				*/
#define DISABLE_INTERRUPTS()
#define ENABLE_INTERRUPTS()
#endif

#if defined(IMX25)
#define DISABLE_INTERRUPTS()	{ int tmp; __asm("MRS tmp, CPSR; ORR tmp, tmp, 0xC0; MSR CPSR_c, tmp;"); }
#define ENABLE_INTERRUPTS()		{ int tmp; __asm("MRS tmp, CPSR; BIC tmp, tmp, 0xC0; MSR CPSR_c, tmp;"); }
#define INT64 long long
#endif

#if defined(TEAKLITE3)
#define DISABLE_INTERRUPTS()
#define ENABLE_INTERRUPTS()
#define INT64 long long
#define ufract16	unsigned short
#endif

#if defined(TEAKLITE4)
#define DISABLE_INTERRUPTS()
#define ENABLE_INTERRUPTS()
#endif

#if defined(XTENSA_FORD_HIFI4)
#define DISABLE_INTERRUPTS()
#define ENABLE_INTERRUPTS()
#endif

// This is for all other processors for which these values haven't been set

#ifndef DISABLE_INTERRUPTS
#define DISABLE_INTERRUPTS()
#endif

#ifndef ENABLE_INTERRUPTS
#define ENABLE_INTERRUPTS()
#endif

#ifndef VEC_RESTRICT
#error VEC_RESTRICT undefined
//#define VEC_RESTRICT
#endif

#ifndef VEC_INLINE
#error VEC_INLINE undefined
//#define VEC_INLINE
#endif

/**
 * @def FW_RESTRICT
 * @brief Compiler-specific C99 restrict keyword.
 */
#if defined(__ADSP21000__)
#define FW_RESTRICT		restrict
#elif defined(_TMS320C6X)
#define FW_RESTRICT		restrict
#else /* !__ADSP21000__ */
#define FW_RESTRICT
#endif /* !__ADSP21000__ */



/* ----------------------------------------------------------------------
** MISRA rule checking on ADI processors.
** ------------------------------------------------------------------- */


#if defined(__ADSP21000__) || defined(__ADSPBLACKFIN__)
#ifdef _MISRA_RULES
#pragma diag(push)
#pragma diag(suppress:misra_rule_19_4:"Section definitions required for ADI processors")
#endif	/* _MISRA_RULES */
#ifdef _MISRA_RULES
#pragma diag(pop)
/* allow violations of MISRA rule 19.4 to be detected again */
#endif	/* _MISRA_RULES */
#endif


/* ----------------------------------------------------------------------
** Memory segments for various processors
** ------------------------------------------------------------------- */

#if defined(TEAKLITE3)
#define AWE_FW_FAST_CODE	  __attribute__ ((section (".CSECT AWE_fast_code_sect")))
#define AWE_FW_SLOW_CODE	  __attribute__ ((section (".CSECT AWE_slow_code_sect")))
#define AWE_MOD_FAST_CODE	   __attribute__ ((section (".CSECT AWE_fast_code_sect")))
#define AWE_MOD_SLOW_CODE	   __attribute__ ((section (".CSECT AWE_slow_code_sect")))

#elif defined(__ADSP21000__) || defined(__ADSPBLACKFIN__)

#ifdef __ECC__
// SHARC and Blackfin C segment names

#define AWE_MOD_SLOW_CODE section("awe_mod_slowcode")
#define AWE_MOD_FAST_CODE section("awe_mod_fastcode")

#define AWE_FW_SLOW_CODE section("awe_fw_slowcode")
#define AWE_FW_FAST_CODE section("awe_fw_fastcode")

#define AWE_USB_INTERNAL_CODE section("awe_usb_internalcode")

#define AWE_PRIO0_FAST_CODE section("awe_prio0_fastcode")

#define AWE_MOD_SLOW_DM_DATA section("awe_mod_slowdmdata")
#define AWE_MOD_FAST_DM_DATA section("awe_mod_fastdmdata")
#define AWE_MOD_SLOW_PM_DATA section("awe_mod_slowpmdata")
#define AWE_MOD_FAST_PM_DATA section("awe_mod_fastpmdata")

#define AWE_FW_SLOW_DM_DATA section("awe_fw_slowdmdata")
#define AWE_FW_FAST_DM_DATA section("awe_fw_fastdmdata")
#define AWE_FW_SLOW_PM_DATA section("awe_fw_slowpmdata")
#define AWE_FW_FAST_PM_DATA section("awe_fw_fastpmdata")

// Used by statically generated code
#define AWE_FW_WIRE_DATA section("awe_fw_wiredata")

#define AWE_USB_INTERNAL_DATA section("awe_usb_internaldata")

#define AWE_FAST_DMA_DATA section("awe_fastdmadata")

#define AWE_MOD_SLOW_DM_CONST section("awe_mod_slowdmconst")
#define AWE_MOD_FAST_DM_CONST section("awe_mod_fastdmconst")
#define AWE_MOD_SLOW_PM_CONST section("awe_mod_slowpmconst")
#define AWE_MOD_FAST_PM_CONST section("awe_mod_fastpmconst")
#define AWE_MOD_SLOW_ANY_DATA section("awe_mod_slowanydata")
#define AWE_MOD_FAST_ANY_DATA section("awe_mod_fastanydata")

#define AWE_MOD_SLOW_ANY_CONST section("awe_mod_slowanyconst")
#define AWE_MOD_FAST_ANY_CONST section("awe_mod_fastanyconst")

#define AWE_FW_SLOW_DM_CONST section("awe_fw_slowdmconst")
#define AWE_FW_FAST_DM_CONST section("awe_fw_fastdmconst")
#define AWE_FW_SLOW_PM_CONST section("awe_fw_slowpmconst")
#define AWE_FW_FAST_PM_CONST section("awe_fw_fastpmconst")
#define AWE_FW_SLOW_ANY_DATA section("awe_fw_slowanydata")
#define AWE_FW_FAST_ANY_DATA section("awe_fw_fastanydata")

#define AWE_FW_SLOW_ANY_CONST section("awe_fw_slowanyconst")
#define AWE_FW_FAST_ANY_CONST section("awe_fw_fastanyconst")

/* Note that a #define statement cannot include a #pragma (this is
** a limitation of the C language).	 Fortunately, VDSP offers
** a work around. */

#define AWE_OPTIMIZE_FOR_SPEED _Pragma("optimize_for_speed")
#define AWE_OPTIMIZE_FOR_SPACE _Pragma("optimize_for_space")
#define AWE_OPTIMIZE_OFF _Pragma("optimize_off")

#else
// SHARC and Blackfin ASM segment names
#define AWE_PRIO0_FAST_CODE .segment /pm awe_prio0_fastcode;

#endif

#elif defined(CHIP_WM0010)

#define AWE_MOD_SLOW_CODE	__attribute__((section(".awe_mod_slowcode")))
#define AWE_MOD_FAST_CODE	__attribute__((section(".awe_mod_fastcode")))

#define AWE_FW_SLOW_CODE	__attribute__((section(".awe_fw_slowcode")))
#define AWE_FW_FAST_CODE	__attribute__((section(".awe_fw_fastcode")))

#define AWE_USB_INTERNAL_CODE

#define AWE_PRIO0_FAST_CODE		__attribute__((section(".awe_prio0_fastcode")))

#define AWE_MOD_SLOW_DM_DATA
#define AWE_MOD_FAST_DM_DATA
#define AWE_MOD_SLOW_PM_DATA
#define AWE_MOD_FAST_PM_DATA

#define AWE_FW_SLOW_DM_DATA
#define AWE_FW_FAST_DM_DATA
#define AWE_FW_SLOW_PM_DATA
#define AWE_FW_FAST_PM_DATA

#define AWE_USB_INTERNAL_DATA

#define AWE_FAST_DMA_DATA

#define AWE_MOD_SLOW_DM_CONST	__attribute__((section(".awe_mod_fastconst")))
#define AWE_MOD_FAST_DM_CONST	__attribute__((section(".awe_mod_fastconst")))
#define AWE_MOD_SLOW_PM_CONST	__attribute__((section(".awe_mod_fastconst")))
#define AWE_MOD_FAST_PM_CONST	__attribute__((section(".awe_mod_fastconst")))
#define AWE_MOD_SLOW_ANY_DATA	__attribute__((section(".awe_mod_fastdata")))
#define AWE_MOD_FAST_ANY_DATA	__attribute__((section(".awe_mod_fastdata")))

#define AWE_MOD_SLOW_ANY_CONST	__attribute__((section(".awe_mod_fastconst")))
#define AWE_MOD_FAST_ANY_CONST	__attribute__((section(".awe_mod_fastconst")))

#define AWE_FW_SLOW_DM_CONST	__attribute__((section(".awe_fw_fastconst")))
#define AWE_FW_FAST_DM_CONST	__attribute__((section(".awe_fw_fastconst")))
#define AWE_FW_SLOW_PM_CONST	__attribute__((section(".awe_fw_fastconst")))
#define AWE_FW_FAST_PM_CONST	__attribute__((section(".awe_fw_fastconst")))
#define AWE_FW_SLOW_ANY_DATA	__attribute__((section(".awe_fw_fastdata")))
#define AWE_FW_FAST_ANY_DATA	__attribute__((section(".awe_fw_fastdata")))

#define AWE_FW_SLOW_ANY_CONST	__attribute__((section(".awe_fw_fastconst")))
#define AWE_FW_FAST_ANY_CONST	__attribute__((section(".awe_fw_fastconst")))

#define AWE_OPTIMIZE_FOR_SPEED
#define AWE_OPTIMIZE_FOR_SPACE
#define AWE_OPTIMIZE_OFF
#else
#define AWE_MOD_SLOW_CODE
#define AWE_MOD_FAST_CODE
#define AWE_FW_SLOW_CODE
#define AWE_FW_FAST_CODE

#define AWE_USB_INTERNAL_CODE

#define AWE_PRIO0_FAST_CODE

#define AWE_MOD_SLOW_DM_DATA
#define AWE_MOD_FAST_DM_DATA
#define AWE_MOD_SLOW_PM_DATA
#define AWE_MOD_FAST_PM_DATA

#define AWE_FW_SLOW_DM_DATA
#define AWE_FW_FAST_DM_DATA
#define AWE_FW_SLOW_PM_DATA
#define AWE_FW_FAST_PM_DATA

#define AWE_USB_INTERNAL_DATA

#define AWE_FAST_DMA_DATA

#define AWE_MOD_SLOW_DM_CONST
#define AWE_MOD_FAST_DM_CONST
#define AWE_MOD_SLOW_PM_CONST
#define AWE_MOD_FAST_PM_CONST
#define AWE_MOD_SLOW_ANY_DATA
#define AWE_MOD_FAST_ANY_DATA

#define AWE_MOD_SLOW_ANY_CONST
#define AWE_MOD_FAST_ANY_CONST

#define AWE_FW_SLOW_DM_CONST
#define AWE_FW_FAST_DM_CONST
#define AWE_FW_SLOW_PM_CONST
#define AWE_FW_FAST_PM_CONST
#define AWE_FW_SLOW_ANY_DATA
#define AWE_FW_FAST_ANY_DATA

#define AWE_FW_WIRE_DATA

#define AWE_FW_SLOW_ANY_CONST
#define AWE_FW_FAST_ANY_CONST

#define AWE_OPTIMIZE_FOR_SPEED
#define AWE_OPTIMIZE_FOR_SPACE
#define AWE_OPTIMIZE_OFF

#endif

/* ----------------------------------------------------------------------
** Standard Audio Weaver data types
** ------------------------------------------------------------------- */

#if defined(__ADSP21000__) || defined(__ADSPBLACKFIN__)
#if defined(_LANGUAGE_C)
#define __STDC__ 1
#else
#define __STDC__ 0
#endif
#endif

#if (__STDC__ > 0) || defined(WIN32) || defined(DSPC_CORTEX_M)

#ifndef UINT32
typedef unsigned int UINT32;
#endif

#ifndef INT32
typedef int INT32;
#endif

#ifndef MAXINT32
#define MAXINT32 ((INT32)0x7fffffffUL)
#endif

#ifndef MININT32
#define MININT32 ((INT32)~MAXINT32)
#endif

#if defined(INT64) && !defined(NO_USE_STDINT)
#include <stdint.h>
#endif


#ifndef INT64
#if defined(WIN32)
typedef __int64 INT64;
#elif defined(__APPLE__)
	typedef long long INT64;
#elif (defined(LINUX) || defined(DSPC_CORTEX_A) || defined(DSPC_CORTEX_M) || defined(DSPC_CORTEX_R))
#include <stdint.h>
typedef int64_t INT64;
#elif defined(__ADSP21000__)
typedef long INT64;
#elif defined(__ADSPBLACKFIN__)
typedef long long INT64;
#elif defined(ARM_M4)
typedef long long INT64;
#elif defined(XTENSA) || defined(XTENSA2) || defined(CEVA_X2)
typedef long long INT64;
#endif
#endif

#ifndef MAXINT64
#define MAXINT64 ((INT64)0x7ffffffffffffffffULL)
#endif

#ifndef MININT64
#define MININT64 ((INT64)~MAXINT64)
#endif

#ifndef UINT64
#if defined(WIN32)
typedef __uint64 UINT64;
#elif defined(__APPLE__)
	typedef unsigned long long UINT64;
#elif (defined(LINUX) || defined(DSPC_CORTEX_A) || defined(DSPC_CORTEX_M) || defined(DSPC_CORTEX_R))
#include <stdint.h>
typedef uint64_t UINT64;
#elif defined(__ADSP21000__)
typedef unsigned long UINT64;
#elif defined(__ADSPBLACKFIN__)
typedef unsigned long long UINT64;
#elif defined(ARM_M4)
typedef unsigned long long UINT64;
#elif defined(XTENSA) || defined(XTENSA2)
typedef unsigned long long UINT64;
#endif
#endif

#ifndef BOOL
#ifdef __APPLE__
typedef signed char BOOL;
#elif !defined(HMD) && !defined(HIFI4)
typedef int BOOL;
#endif
#endif

#ifndef FLOAT32

#if defined(USE_AFLOAT)
typedef fr32 FLOAT32;
#else
typedef float FLOAT32;
#endif

#endif

#ifndef INT16
typedef short INT16;
#endif

#ifndef UINT16
typedef unsigned short UINT16;
#endif

#ifndef INT8
typedef signed char INT8;
#endif

#ifndef UINT8
typedef unsigned char UINT8;
#endif

/* These definitions on needed for Linux */
#ifndef INT
typedef int INT;
#endif

#ifndef UINT
typedef unsigned int UINT;
#endif

#ifndef BYTE
//#if !(defined(ARM_M4) || defined(DSPC_CORTEX_M) || defined(DSPC_CORTEX_R))
#define BYTE unsigned char
//#endif
#define PBYTE unsigned char *
#endif

#ifndef BOOL
#define BOOL INT32
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef PCHAR
#define PCHAR char *
#endif

#ifndef WORD
#if !(defined(ARM_M4) || defined(DSPC_CORTEX_M) || defined(DSPC_CORTEX_R))
#define WORD unsigned short
#endif
#endif

#ifndef PWORD
#define PWORD unsigned short *
#endif

#ifndef DWORD
#if (defined(CHIP_6713) || defined(CHIP_6747) || defined(OMAP_DSP) || defined(DSPC_CORTEX_M))
#define DWORD unsigned int
#else
#define DWORD unsigned long
#endif // CHIP_6713
#endif // DWORD

#ifndef PDWORD
#if (defined(CHIP_6713) || defined(CHIP_6747) || defined(OMAP_DSP) || defined(DSPC_CORTEX_M))
#define PDWORD unsigned int *
#else
#define PDWORD unsigned long *
#endif // CHIP_6713
#endif // PDWORD

#endif // __STDC__

/* ----------------------------------------------------------------------
** Cycle counting macros
** ------------------------------------------------------------------- */

#if __STDC__ || defined(WIN32)
extern UINT32 aweuser_getCycleCount(void);
extern UINT32 aweuser_getElapsedCycles(UINT32 start_time, UINT32 end_time);

static VEC_INLINE void awe_fwCycleInit(void)
{
#if defined(DSPC_CORTEX_A) && !defined(BARE_METAL)
	asm volatile("mcr p15, 0, %0, c9, c12, 0" :: "r"(5));
	asm volatile("mcr p15, 0, %0, c9, c12, 1" :: "r"(1<<31));
#endif
}

#if defined(XTENSA) || defined(XTENSA2)
#include "xtensa/core-macros.h"
#endif

#if defined(XTENSA) || defined(XTENSA2)
# define GET_CCOUNT()	({ int __ccount; \
				__asm__ volatile("rsr.ccount %0" : "=a"(__ccount)); \
				__ccount; })
#endif

#if defined(AARCH64_NXP)
extern int64_t current_time_hires(void);
#endif

static VEC_INLINE UINT32 awe_getCycleCount(void)
{
#if defined(AARCH64_NXP)

    int64_t usec =  current_time_hires();
    UINT32 t = (UINT32)(usec & 0xffffffff);
#ifdef PROFILE_DIVIDER
	return ((t / PROFILE_DIVIDER) & 0xffffffff);
#else
	return (t & 0xffffffff);
#endif

#elif defined(__ADSP21000__)

	UINT32 _tcount;
	__asm volatile ("%0=EMUCLK;" : "=d" (_tcount));
#ifdef PROFILE_DIVIDER
	return _tcount / PROFILE_DIVIDER;
#else
	return _tcount;
#endif

#elif defined(__ADSPBLACKFIN__)

	UINT32 _tcount;
	__asm volatile ("%0=CYCLES;" : "=d" (_tcount));
#ifdef PROFILE_DIVIDER
	return _tcount / PROFILE_DIVIDER;
#else
	return _tcount;
#endif

#elif defined(WIN32)

	LARGE_INTEGER ltime;
	LARGE_INTEGER freq;
	UINT32 cycles;
	double ftime;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&ltime);
	ftime = ((double)ltime.QuadPart / (double)freq.QuadPart) * 1e7;
#ifdef PROFILE_DIVIDER
	cycles = (UINT32)(ftime / PROFILE_DIVIDER);
#else
	cycles = (UINT32)ftime;
#endif
	return (cycles);

#elif defined(LINUX)
	#if defined(TESLA)
			UINT32 cycles_high, cycles_low;
			asm volatile ("CPUID\n\t" "RDTSC\n\t"
						  "mov %%edx, %0\n\t"
						  "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
						  "%rax", "%rbx", "%rcx", "%rdx");
#ifdef PROFILE_DIVIDER
			return cycles_low / PROFILE_DIVIDER;
#else
			return cycles_low;
#endif
	#elif defined(DSPC_CORTEX_A)
		#if defined(PMU_ENABLED)
			//#warning "DSPC_CORTEX_A cycle couting for enabled PMU"
			UINT32 ncyc;
			asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(ncyc));
#ifdef PROFILE_DIVIDER
			return ncyc / PROFILE_DIVIDER;
#else
			return ncyc;
#endif
		#else
			//#warning "DSPC_CORTEX_A cycle counting via clock_gettime"
			struct timespec tv;
			clock_gettime(CLOCK_REALTIME, &tv);
			int64_t usec = (tv.tv_sec * 10000000) + (tv.tv_nsec / 100);
			//printf("C = %lld", (usec & 0xffffffff));
#ifdef PROFILE_DIVIDER
			return ((usec / PROFILE_DIVIDER) & 0xffffffff);
#else
			return (usec & 0xffffffff);
#endif
		#endif
	#else
		//#warning "Generic Linux cycle counting via clock_gettime"
		struct timespec tv;
		clock_gettime(CLOCK_REALTIME, &tv);
		int64_t usec = (tv.tv_sec * 10000000) + (tv.tv_nsec / 100);
#ifdef PROFILE_DIVIDER
		return ((usec / PROFILE_DIVIDER) & 0xffffffff);
#else
		return (usec & 0xffffffff);
#endif
	#endif

#elif defined(DSPC_CORTEX_A) &&	 !defined(BARE_METAL)

	unsigned ncyc;
	asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(ncyc));
#ifdef PROFILE_DIVIDER
	return ncyc / PROFILE_DIVIDER;
#else
	return ncyc;
#endif

#elif defined(_TMS320C6X)

#ifdef PROFILE_DIVIDER
	return (TSCL / PROFILE_DIVIDER);
#else
	return (TSCL);
#endif

#elif defined(XTENSA) || defined(XTENSA2)

//	return XTHAL_GET_CCOUNT();
#ifdef PROFILE_DIVIDER
	return GET_CCOUNT() / PROFILE_DIVIDER;
#else
	return GET_CCOUNT();
#endif

#elif defined(X86)
	//#warning "x86 cycle counting via rdtsc"
	// unsigned hi, lo;
	// __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
	// return lo;
#else

	UINT32 cycles = 0;
	cycles = aweuser_getCycleCount();
#ifdef PROFILE_DIVIDER
	return (cycles / PROFILE_DIVIDER);
#else
	return (cycles);
#endif

#endif
}


static VEC_INLINE UINT32 awe_getElapsedCycles(UINT32 start_time, UINT32 end_time)
{
  UINT elapsedTime;

#if defined(DSPC_CORTEX_M)
	elapsedTime = aweuser_getElapsedCycles(start_time, end_time);
#else
	if (end_time > start_time)
	{
		elapsedTime = end_time - start_time;
	}
	else
	{
		elapsedTime = ((((UINT32)0xFFFFFFFF) - start_time) + end_time + 1);
	}
#endif

	return elapsedTime;
}

#endif // __STDC__

#endif	  /* !defined  GENERIC_TARGET_PROCESSOR_H_ */
