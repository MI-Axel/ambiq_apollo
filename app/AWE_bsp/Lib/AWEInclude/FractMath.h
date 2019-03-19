/****************************************************************************
*
*		Audio Framework
*		---------------
*
****************************************************************************
*	FractMath.h
****************************************************************************
*
*	Description:	Fractional math support
*
*	Copyright:		DSP Concepts, 2006-2015, All rights reserved.
*	Owner:			DSP Concepts
*					1800 Wyatt Drive, Suite 14
*                   Santa Clara, CA 95054
*
***************************************************************************/

/**
* @addtogroup CFramework
* @{
*/

/**
* @file
* @brief Fractional math support
*/

#ifndef _FRACTMATH_H_
#define _FRACTMATH_H_

// .\Include\Targets\XTENSA_HIFI2 must be in the include path
#if defined(OPT_HIFI2)
#include "xt_hifi2.h"
#endif

#ifdef DSPC_ARM11
// optimize fract32 macros to improve MIPS
// later we can clean up this flag and use the new macro as default
#define LOW_MIPS_FRACT32 1

#endif // DSPC_ARM11


// Check for blackfin target
#if defined(__CCESVERSION__) && defined(__ADSPBLACKFIN__)

#include <fract_typedef.h>

#elif defined(__ADSPBLACKFIN__)

// The Blackfin has native support of these datatypes through the fract.h library.
#include <fract.h>
typedef INT64 fract64;
#define mult_fr1x16x16 mult_fr1x32

// Declare the fract16/32/64 types
#elif defined(WIN32)

#include <wtypes.h>
typedef INT16 fract16;
typedef INT32 fract32;
typedef INT64 fract64;

#elif ( defined(HEXAGON) )

typedef signed short fract16;
typedef signed int fract32;
typedef signed long long fract64;
typedef signed long long INT64;

// I have no idea why these were not in the Hexagon headers.
float fmaxf(float, float);
float fminf(float, float);

#elif (defined(__GNUC__) || defined(DSPC_CORTEX_A) || defined(DSPC_CORTEX_M) || defined(DSPC_CORTEX_R) || defined(IMX25) || defined(DSPC_ARM11))

#include <stdint.h>

#if !defined(CORE_M4) && !defined(CORE_M7) && !defined(FRACT_TYPES_DEFINED)
typedef int16_t fract16;
typedef int32_t fract32;
typedef int64_t fract64;
#define FRACT_TYPES_DEFINED
#endif

#elif defined(__ADSP21000__)
#ifdef __ADSP215xx__
typedef INT16 fract16;
typedef INT32 fract32;
typedef INT64 fract64;
#else
typedef INT32 fract16;
typedef INT32 fract32;
typedef INT64 fract64;
#endif
#elif ( defined(CHIP_6713) || defined(CHIP_6747) )

typedef signed short fract16;
typedef signed int fract32;
typedef signed long long fract64;
typedef signed long long INT64;

#elif defined(CHIP_WM0010)

#ifndef fract16
#define fract16 signed short
#endif
#ifndef fract32
#define fract32 signed int
#endif
#ifndef fract64
#define fract64 signed long long
#endif
typedef signed long long INT64;

#elif defined(ARM_M4)

typedef INT64 fract64;

#elif defined(_TMS320C6X)

#ifndef fract16
#define fract16 signed short
#endif
#ifndef fract32
#define fract32 signed int
#endif
#ifndef fract64
#define fract64 signed long long
#endif

#endif

// for mem alignment in 64-bit in-line asm
typedef union u
{
    fract64 x64;
    fract32 x32[2];
} union64_type;


#if defined(DSPC_CORTEX_M) || defined(DSPC_CORTEX_R) || defined(IMX25) || defined(DSPC_ARM11)

#define DSPC_HAS_CLZ
#define DSPC_HAS_QSUB
#define DSPC_HAS_QADD

#endif


#if defined(DSPC_CORTEX_M) || defined(DSPC_CORTEX_R) || defined(DSPC_ARM11)

#define DSPC_HAS_SSAT
#define DSPC_HAS_SMUAD
#define DSPC_HAS_SMLALD

#endif

#ifndef ATMEL_STUDIO

#if defined(IMX25)

#define __CLZ(a) __clz(a)
#define __QSUB(a,b) __qsub(a,b)
#define __QADD(a,b) __qadd(a,b)

#endif

#if defined(DSPC_HAS_CLZ)

#if defined(__CC_ARM) && (__ARMCC_VERSION < 4100000)

#pragma arm
#define VEC_INLINE inline
static VEC_INLINE fract32 __CLZ(fract32 in)
{
    fract32 ret;

    __asm
    { 
        CLZ ret, in
    };

    return ret;
}
#if defined(__thumb)
#pragma thumb
#endif

#elif defined(__GNUC__)
static VEC_INLINE fract32 __CLZ(fract32 in)
{
    fract32 ret;

    asm volatile( 
        "clz %0, %1\n"
        :"=r"(ret)
        :"r"(in)
        );

    return ret;
}
#endif
#endif


#if defined(DSPC_HAS_QSUB)
#if defined(__CC_ARM) && (__ARMCC_VERSION < 4100000)

#pragma arm
static VEC_INLINE fract32 __QSUB(fract32 a, fract32 b)
{
    fract32 ret;

    __asm
    { 
        QSUB ret, a, b
    };

    return ret;
}
#if defined(__thumb)
#pragma thumb
#endif

#elif defined(__GNUC__) && !defined(CORE_M4) && !defined(CORE_M7)
static VEC_INLINE fract32 __QSUB(fract32 a, fract32 b)
{
    fract32 ret;

    asm volatile( 
        "qsub %0, %1, %2\n"
        :"=r"(ret)
        :"r"(a), "r"(b)
        );

    return ret;
}
#endif
#endif


#if defined(DSPC_HAS_QADD)
#if defined(__CC_ARM) && (__ARMCC_VERSION < 4100000)

#pragma arm
static VEC_INLINE fract32 __QADD(fract32 a, fract32 b)
{
    fract32 ret;

    __asm
    { 
        QADD ret, a, b
    };

    return ret;
}
#if defined(__thumb)
#pragma thumb
#endif

#elif defined(__GNUC__) && !defined(CORE_M4) && !defined(CORE_M7)
static VEC_INLINE fract32 __QADD(fract32 a, fract32 b)
{
    fract32 ret;

    asm volatile( 
        "qadd %0, %1, %2\n"
        :"=r"(ret)
        :"r"(a), "r"(b)
        );

    return ret;
}
#endif
#endif


#if defined(DSPC_HAS_SMUAD)
#if defined(__CC_ARM) && (__ARMCC_VERSION < 4100000)

#pragma arm
static VEC_INLINE fract32 __SMUAD(fract32 a, fract32 b)
{
    fract32 ret;

    __asm
    { 
        SMUAD ret, a, b
    };

    return ret;
}
#if defined(__thumb)
#pragma thumb
#endif

#elif defined(__GNUC__) && !defined(CORE_M4) && !defined(CORE_M7)
static VEC_INLINE fract32 __SMUAD(fract32 a, fract32 b)
{
    fract32 ret;

    asm volatile( 
        "smuad %0, %1, %2\n"
        :"=r"(ret)
        :"r"(a), "r"(b)
        );

    return ret;
}
#endif
#endif


#if defined(DSPC_HAS_SMLALD)
#if defined(__CC_ARM) && (__ARMCC_VERSION < 4100000)

#pragma arm
static VEC_INLINE fract64 __SMLALD(fract32 a, fract32 b)
{
    fract32 c,d;

    union{
        fract64 ll;
        fract32 l[2];
    }ret;

    __asm
    { 
        SMLALD c, d, a, b
    };

    ret.l[0] = c;
    ret.l[1] = d;

    return ret.ll;
}
#if defined(__thumb)
#pragma thumb
#endif

#elif defined(__GNUC__) && !defined(CORE_M4) && !defined(CORE_M7)
static VEC_INLINE fract64 __SMLALD(fract32 a, fract32 b)
{
    fract32 c,d;

    union{
        fract64 ll;
        fract32 l[2];
    }ret;

    asm volatile( 
        "smlald %0, %1, %2, %3\n"
        :"=r"(c), "=r"(d)
        :"r"(a), "r"(b)
        );

    ret.l[0] = c;
    ret.l[1] = d;

    return ret.ll;
}
#endif

#endif


#if defined(DSPC_HAS_SSAT)
#if (defined(__CC_ARM) && (__ARMCC_VERSION < 4100000)) || (defined(__GNUC__) && !defined(CORE_M4) && !defined(CORE_M7))
//could not figure out how to make a drop in replacement for ssat with inline assembly
//it is up to the user of ssat to remake their function to use inline assembly
static VEC_INLINE fract32 __SSAT(
    fract32 x,
    uint32_t y)
{
    int32_t posMax, negMin;
    uint32_t i;

    posMax = 1;
    for (i = 0; i < (y - 1); i++)
    {
        posMax = posMax * 2;
    }

    if(x > 0)
    {
        posMax = (posMax - 1);

        if(x > posMax)
        {
            x = posMax;
        }
    }
    else
    {
        negMin = -posMax;

        if(x < negMin)
        {
            x = negMin;
        }
    }
    return (x);
}

#define DSPC_POUND #

#define DSPC_CONCAT(a,b) DSPC_CONCAT2(a,b)
#define DSPC_CONCAT2(a,b) a##b

#if defined(__CC_ARM)

#define DSPC__SSAT(ret, a, b)                       \
    \
    do {                            				    \
    \
    __asm                       				    \
{                           				    \
    SSAT ret, DSPC_CONCAT(DSPC_POUND,b), a      \
};                          				    \
    \
    }while(0)

#elif defined(__GNUC__)

#define DSPC__SSAT(ret, a, b)                       \
    \
    do {                            				    \
    \
    asm volatile                  				    \
    (                           				    \
    "ssat %0, DSPC_CONCAT(DSPC_POUND,b), %1\n"  \
    :"=r"(ret)                                  \
    :"r"(a)                                     \
    );                          				    \
    \
    }while(0)

#endif //#if defined(__CC_ARM)
#endif //#if (defined(__CC_ARM) && (__ARMCC_VERSION < 4100000)) || defined(__GNUC__)
#endif //#if defined(DSPC_HAS_SSAT

#endif // ATMEL_STUDIO

#if defined (DSPC_ARM11)
**
* @brief definition to pack two 16 bit values.
*/
#define __PKHBT(ARG1, ARG2, ARG3)      ( (((int32_t)(ARG1) <<  0) & (int32_t)0x0000FFFF) | \
    (((int32_t)(ARG2) << ARG3) & (int32_t)0xFFFF0000)  )
#define __PKHTB(ARG1, ARG2, ARG3)      ( (((int32_t)(ARG1) <<  0) & (int32_t)0xFFFF0000) | \
    (((int32_t)(ARG2) >> ARG3) & (int32_t)0x0000FFFF)  )

#endif

#ifndef min
#define min(a, b) (((a) < (b)) ? (a):(b))
#endif
#ifndef max
#define max(a, b) (((a) > (b)) ? (a):(b))
#endif

#define mult_32x32_R_keep32_shiftN(a, x, y, n) \
    a = (fract32) (((fract64) x * y + (0x80000000LL >> n) ) >> (32 - n) )

#define mult_32x32_Rm_keep32_shiftN(a, x, y, n) \
    a = (fract32) (((fract64) x * y ) >> (32 - n) )

// This was originally
//	( max( ((-1)<<(32-s)), min( val, ((1<<(32-s))-1) ) ) )
// But the C compiler complained about the value being out of range (because we
// end up with 0x80000000 - 1.

#define sat(val, s) \
    ( max( ((-1)<<(31-s)), min( val, ((1<<(31-s))-1) ) ) )
#define sum_sat_shift(a, b, post) \
    a = (sat(a + b, post)) << (post-1)
#define sum_sat(a, b) \
    a = (sat(((a>>1) + (b>>1)), 1) << 1)

/**
* @brief Clips a 64-bit fractional value to 32-bit precision.  The 32-bit data
* must be in the low 32-bit bits of the 64-bit word.
* @param x					  64 bit fixed-point value
*/
static VEC_INLINE fract32 clip_fract64_to_32(fract64 x)
{
    if (x <= -2147483648LL)
        return (fract32)-2147483648LL;

    if (x >= 2147483647LL)
        return (fract32)2147483647LL;

    return (fract32)x;
}


/**
* @brief Computes the addition of two 24-bit fixed-point variables and returns
* the result.  The 24-bit data is in the high 24-bits of a 32-bit register.
* Result will be in the same format as the inputs.  Saturation is applied.
* @param x					  24 bit fixed-point value
* @param y					  24 bit fixed-point value
*/
static VEC_INLINE fract32 add_fr1x24(fract32 x, fract32 y)
{
    fract32 result;

    result = (x >> 8) + (y >> 8);

    if(result < (fract32)0xFF800000)
        result = (fract32)0xFF800000;
    else if(result > 0x7FFFFF)
        result = 0x7FFFFF;

    return (result << 8);
}

#ifndef __ADSPBLACKFIN__
/**
* @brief Computes the addition of two fixed-point variables in Q1.31 format.
* The result is in Q1.31 format and saturation occurs.
* @param x					  32 bit fixed-point value
* @param y					  32 bit fixed-point value
*/
static VEC_INLINE fract32 add_fr1x32(fract32 x, fract32 y)
{
#if defined(DSPC_HAS_QADD)
    return __QADD(x, y);
#else
    return clip_fract64_to_32((fract64)x + y);
#endif
}

/**
* @brief Computes the subtraction of two fixed-point variables in Q1.31 format.
* The result is in Q1.31 format and saturation occurs.
* @param x					  32 bit fixed-point value
* @param y					  32 bit fixed-point value
*/
static VEC_INLINE fract32 sub_fr1x32(fract32 x, fract32 y)
{
#if defined(DSPC_HAS_QSUB)
    return __QSUB(x, y);
#else
    return clip_fract64_to_32((fract64)x - y);
#endif
}

/**
* @brief Computes the product of two Q1.23 values.  The 24-bit data is assumed
* to be in the high bits of the 32-bit input variables.  The result is computed
* without saturation.
* @param x					  32 bit fixed-point value with upper 24-bits data
* @param y					  32 bit fixed-point value with upper 24-bits data
*/
static VEC_INLINE fract32 mult_fr1x24x24NS(fract32 x, fract32 y)
{
    fract64 product;

    product = ((fract64)(x >> 8)) * ((fract64)(y >> 8));
    product >>= (23 - 8);

    return (fract32)product;
}

/**
* @brief Computes the multiplication of two Q1.23 variables and returns the 
* result as a 64-bit value in Q7.48 format.  The 24-bit input variables are
* contained in the high 24-bits of a 32-bit register.  The multiplication occurs
* without saturation.
* @param x					  32 bit fixed-point value with upper 24-bits data
* @param y					  32 bit fixed-point value with upper 24-bits data
*/
static VEC_INLINE fract64 mult_fr1x56(fract32 x, fract32 y)
{
    fract64 product;

    product = ((fract64)(x >> 8)) * ((fract64)(y >> 8));
    product <<= 1;

    return product;
}

/**
* @brief Computes the multiplication of two Q1.31 values and returns a Q1.31 result.
* Saturation occurs if the processor easily supports it.
* @param x					  32 bit fixed-point value
* @param y					  32 bit fixed-point value
*/
static VEC_INLINE fract32 mult_fr1x32x32NS(fract32 x, fract32 y)
{
#if defined(IMX25)
    return __qdbl(((fract64)x * y) >> 32);
#elif defined(LOW_MIPS_FRACT32) //takes precedence over DSPC_HAS_SSAT
    // for low MIPS condition,
    return (fract32) (((fract64)x * y) >> 31);
#elif defined(DSPC_HAS_SSAT)
    return __SSAT((fract32)(((fract64)x * y) >> 32), 31) << 1;
#elif defined(_TMS320C6740)
    return _smpy32(x, y);
#elif defined(OPT_HIFI2)
    {
    	ae_p24x2s p = AE_TRUNCP24A32X2( x, y);
    	ae_q56s q = AE_MULFP24S_HL(p, p);
    	return AE_TRUNCA32Q48(q);
    }
#else
    return clip_fract64_to_32(((fract64)x * y) >> 31);
#endif
}

static VEC_INLINE fract32 awe_fos_fract32(fract32 sin, fract32 sout, fract32 smoothingCoeff, fract32 oneMinusRate)
{
#if defined(OPT_HIFI2)
	// calculate (1-smoothingCoeff)*y + smoothingCoeff*x = y + smoothingCoeff*(x-y);
	ae_p24x2s pcoeff = AE_TRUNCP24A32X2(smoothingCoeff, smoothingCoeff);
	ae_p24x2s p = AE_TRUNCP24A32X2(sin,sout);
	ae_q56s q =  AE_CVTQ48A32S(sout);
	AE_MULASFP24S_HH_LL(q, p,pcoeff);
	return AE_TRUNCA32Q48(q);
#else
	return  add_fr1x32(mult_fr1x32x32NS(sout, oneMinusRate), mult_fr1x32x32NS(sin, smoothingCoeff));
#endif
}

/**
* @brief Computes the multiplication of two 16-bit fixed-point variables 
* without saturation and returns 32-bit the result.
* @param x					  16 bit fixed-point value
* @param y					  16 bit fixed-point value
*/
static VEC_INLINE fract32 mult_fr1x16x16(fract16 x, fract16 y)
{
    return ((fract32)x * y) << 1;
}

/**
* @brief Computes the multiplication of two 32-bit fixed-point variables 
* without saturation and returns 64-bit the result.
* @param x					  32 bit fixed-point value
* @param y					  32 bit fixed-point value
*/
static VEC_INLINE fract64 mult_fr1x64(fract32 x, fract32 y)
{
    return ((fract64)x * y) << 1;
}

/**
* @brief Computes the addition of two fixed-point variables and returns the result. Result will be in the same format as inputs.
* @param x					  64 bit fixed-point value
* @param y					  64 bit fixed-point value
*/
static VEC_INLINE fract64 add_fr1x64(fract64 x, fract64 y)
{
    int s1, s2;
    fract64 result1, result2, carry;

    //Get sign bits each input
    s1 = (x >> 63) & 0x1;
    s2 = (y >> 63) & 0x1;

    //one positive and one negative
    if(s1 != s2)
    {
        return x + y;
    }
    else
    {
        if((s1 == 1) && (s2 == 1))
        {
            //Both negative numbers

            //Add low 32-bit of both inputs
            result1 = (x & 0x00000000FFFFFFFFll) + (y & 0x00000000FFFFFFFFll);
            carry = (result1 & 0x0000000100000000ll);

            result2 = ((x >> 32) & 0x00000000FFFFFFFFll) + ((y >> 32) & 0x00000000FFFFFFFFll) + carry;
            carry = (result2 & 0x0000000100000000ll);

            if(carry == 1)
            {
                return (fract64)0x8000000000000000ll;
            }
            else
            {
                return (result1 & 0x00000000FFFFFFFFll) + (result2 << 32);
            }
        }
        else
        {
            result1 = x + y;

            if((result1 >> 63) & 0x1)
            {
                return (fract64)0x7FFFFFFFFFFFFFFFll;
            }
            else
            {
                return result1;
            }
        }
    }
}

/**
* @brief Computes the sum of two Q7.47 variables that are stored in a 64-bit
* register.  Result will be in Q7.47 format.
* @param x					  56 bit fixed-point value
* @param y					  56 bit fixed-point value
*/
static VEC_INLINE fract64 add_fr1x56(fract64 x, fract64 y)
{
    fract64 result;

    result = x + y;

    //Saturate the result
    if(result < (fract64)0xFF80000000000000ll)
    {
        return (fract64)0xFF80000000000000ll;
    }

    if(result > (fract64)0x007FFFFFFFFFFFFFll)
    {
        return (fract64)0x007FFFFFFFFFFFFFll;
    }

    return result;
}


/**
* @brief Left shifts a Q1.31 variable.
* @param x					  32 bit fixed-point value
* @param y					  number of bits to shift
*/
static VEC_INLINE fract32 shl_fr1x32(fract32 x, short y)
{
    // Fast break-out for no-shift case
    if (y == 0)
        return x;

    // Handle shift down (does not require saturating as the number gets smaller)
    if (y < 0)
        return x >> (-y);

    // Handle shift up with saturation
    return clip_fract64_to_32((fract64)x << y);
}

static VEC_INLINE int signbits_64(fract64 var1)
{
    int count, prev_signbit, curr_signbit;
    fract64 mask = (fract64)0x8000000000000000ll;
    int var2 = 64;

    count = 0;


    curr_signbit = (var1 & mask) != 0 ? 1 : 0;
    var1 = var1 << 1;
    prev_signbit = (var1 & mask) != 0 ? 1 : 0;

    while( (curr_signbit == prev_signbit) && (count<(var2-1)) )
    {
        var1 = var1 << 1;
        prev_signbit = curr_signbit;
        curr_signbit = (var1 & mask) != 0 ? 1 : 0;
        count ++;
    }

    return(count);
}

/**
* @brief Left shifts a Q1.23 variable which is stored in the high 24-bits of a
* 32-bit variable.
* @param x					  24 bit fixed-point value
* @param y					  number of bits to shift
*/
static VEC_INLINE fract32 shl_fr1x24(fract32 x, short y)
{
    fract64 result;

    // Fast break-out for no-shift case
    if (y == 0)
        return x;

    // Handle shift down (does not require saturating as the number gets smaller)
    if (y < 0)
        return x >> (-y);

    // Handle shift up with saturation
    result = ((fract64)x >> 8) << y;

    if(result < (fract64)0xFFFFFFFFFF800000ll)
        result = (fract64)0xFFFFFFFFFF800000ll;
    else if(result > 0x7FFFFF)
        result = (fract64)0x7FFFFF;

    return (fract32)(result << 8);
}

/**
* @brief Left which a Q1.63 value with saturation.
* @param x					  64 bit fixed-point value
* @param y					  number of bits to shift
*/
static VEC_INLINE fract64 shl_fr1x64(fract64 x, short y)
{
    int s;

    // Fast break-out for no-shift case
    if (y == 0)
        return x;

    // Handle shift down (does not require saturating as the number gets smaller)
    if (y < 0)
        return x >> (-y);

    // Handle shift up with saturation
    s = signbits_64(x);
    if(s >= y)
        return x << y;
    else
        if(x < 0)
            return (fract64)0x8000000000000000ll;
        else
            return (fract64)0x7FFFFFFFFFFFFFFFll;
}

/**
* @brief Left shifts a Q4.47 fixed-point variable.
* @param x					  56 bit fixed-point value
* @param y					  number of bits to shift
*/
static VEC_INLINE fract64 shl_fr1x56(fract64 x, short y)
{
    int s;

    // Fast break-out for no-shift case
    if (y == 0)
        return x;

    // Handle shift down (does not require saturating as the number gets smaller)
    if (y < 0)
        return x >> (-y);

    // Handle shift up with saturation
    s = signbits_64(x) - 8;
    if(s >= y)
        return x << y;
    else
        if(x < 0)
            return (fract64)0xFF80000000000000ll;
        else
            return (fract64)0x007FFFFFFFFFFFFFll;
}

/**
* @brief Absolute value of Q1.31 values with saturation.
* @param[in] x					  32 bit fixed-point value
*/
static VEC_INLINE fract32 abs_fr1x32(fract32 x)
{
    if (x > 0)
        return x;
    else 
    {
        if (x == (fract32) 0x80000000)
            return (fract32)0x7fffffff;
        else
            return -x;
    }
}

#endif	// __ADSPBLACKFIN__

#if defined(DSPC_HAS_CLZ)
/**
* @brief Computes the number of signbits
* @param val					  input value
* @return						  number of signbits
*/
static VEC_INLINE int signbits(fract32 fact)
{
    return (fact > 0) ? __CLZ(fact) - 1 : __CLZ(__QSUB(0, fact)) - 1;
}

#else
static VEC_INLINE int signbits(fract32 var1)
{
    int count, prev_signbit, curr_signbit;
    fract32 mask = (fract32)0x80000000;
    int var2 = 32;

    count = 0;


    curr_signbit = (var1 & mask) != 0 ? 1 : 0;
    var1 = var1 << 1;
    prev_signbit = (var1 & mask) != 0 ? 1 : 0;

    while( (curr_signbit == prev_signbit) && (count<(var2-1)) )
    {
        var1 = var1 << 1;
        prev_signbit = curr_signbit;
        curr_signbit = (var1 & mask) != 0 ? 1 : 0;
        count ++;
    }

    return(count);
}
#endif


fract16 expadj(fract32 var1, fract16 var2, fract16 var3);

/**
* @brief Multiplies Q1.23 x Q1.47.  The result is in Q8.57 format.
* @param val					  input value
* @return						  number of signbits
*/
static VEC_INLINE fract64 mult_fr1x24x48NS(fract32 x, fract64 y)
{
    unsigned int y0;
    fract32 y1;
    fract64 acc0;   

    y0 = (unsigned int)y & 0xFFFFFF; // LSW
    y1 = (fract32) (y >> 24);        // MSW

    acc0 = (((fract64)x >> 8) * y0) >> 23;    
    acc0 += (((fract64)x >> 8) * y1) << 1;

    return acc0;  
}


/**
* @brief Converts dB20 values to linear.
* @param[in] input                  Input in 8.24 format
* @param[out] output                Output in 8.24 format
*/
static VEC_INLINE fract32 DBtoLinear_fract32(fract32 input)
{
    fract32 flor, value;
    fract32 fraction;
    fract32 temp, sqrfract;

    extern fract32 DecibelsToLinear_coeff_fract32[5];

    value = mult_fr1x32x32NS(input, DecibelsToLinear_coeff_fract32[0]) << 7;
    flor = value >> 24;
    fraction = (value & 0x00ffffff);
    temp = add_fr1x32(DecibelsToLinear_coeff_fract32[1], (mult_fr1x32x32NS(fraction,DecibelsToLinear_coeff_fract32[2])) << 7);
    sqrfract = mult_fr1x32x32NS(fraction,fraction)<<7;
    temp = add_fr1x32(temp, (mult_fr1x32x32NS(sqrfract, DecibelsToLinear_coeff_fract32[3])) << 7);
    fraction = mult_fr1x32x32NS(sqrfract, fraction) << 7;
    temp = add_fr1x32(temp, (mult_fr1x32x32NS(fraction, DecibelsToLinear_coeff_fract32[4])) << 7);
    temp = shl_fr1x32(temp, (short) flor);
    return (flor > 7) ? 0x7fffffff : temp;
}




/**
* @brief Multiplies a fract32 value by an integer
* @param[in] x             integer input
* @param[in] y             fract32 input
*/

static VEC_INLINE fract32 mult_fr1xIntx32NS(int x, fract32 y)
{ 
    fract32 product;
    fract16 xl,yl,yh;

    xl = x & 0x0000FFFF;
    yl = y & 0x0000FFFF;
	yh = (y >> 16) & 0x0000FFFF;

    product = (xl * yh) << 16;
    product += xl * yl;
    return product;
}


/* @brief converts the linear values in to DB using 3rd order polynomial approximation
   @param[in]  input      32 bit value
   @param[in]  *output    32 bit value
   @param[in]  INFOR      format for the input value ex:1 for 1.31 and 2 for 2.30 etc
   @param[in]  OUTFOR     format for the output value ex:1 for 1.31 and 2 for 2.30 etc
 */

static VEC_INLINE fract32 LinearToDB_fract32(fract32 input, int INFOR, int OUTFOR)
{
    int bits, exp, shift;
    fract32 mantissa, sqmantissa, temp;
    extern fract32 LinearToDecibels_coeff_fract32[5];

    // Extra shift for the coefficients to avoid overflow
    #define LinearToDecibels_SHIFT 5

	bits = signbits(input);
	mantissa = shl_fr1x32(input, (short) bits); // mantissa will be 1.31 format 
	exp = INFOR - 1 - bits;   
	shift = 6 + LinearToDecibels_SHIFT - (OUTFOR - 1); // as we are right shifted coeffecients by 6 times result has to be shifted by 6 times left   
	sqmantissa = mult_fr1x32x32NS(mantissa, mantissa);
	temp = add_fr1x32(LinearToDecibels_coeff_fract32[0] >> LinearToDecibels_SHIFT, (mult_fr1xIntx32NS(exp, LinearToDecibels_coeff_fract32[1] >> LinearToDecibels_SHIFT)));
	temp = add_fr1x32(temp,mult_fr1x32x32NS(mantissa, LinearToDecibels_coeff_fract32[2] >> LinearToDecibels_SHIFT));
	temp = add_fr1x32(temp,mult_fr1x32x32NS(sqmantissa, LinearToDecibels_coeff_fract32[3] >> LinearToDecibels_SHIFT));
	sqmantissa = mult_fr1x32x32NS(sqmantissa, mantissa);
	temp = add_fr1x32(temp, (mult_fr1x32x32NS(sqmantissa, LinearToDecibels_coeff_fract32[4] >> LinearToDecibels_SHIFT)));
	return shl_fr1x32(temp, (short) shift);
}


#endif // _FRACTMATH_H_

/**
* @}
* End of file
*/

