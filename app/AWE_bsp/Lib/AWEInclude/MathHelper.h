#ifndef _math_helper_h
#define _math_helper_h

#ifndef IA610
#include <math.h>
#endif

#include "FractMath.h"

#ifdef WIN32
#pragma warning( disable : 4211)
#endif

#ifndef IA610

// These are double precision values
#ifndef PI
#define PI 3.141592653589793
#endif

#define TWO_PI 6.283185307179586
#define PIDIV4 .785398163397448

// These are float values
#ifndef PIF
#define PIF 3.141592653589793f
#endif

#define TWO_PIF 6.283185307179586f
#define PIDIV4F .785398163397448f

#define AWE_FLOAT_ZERO 0.0f
#define AWE_FLOAT_ONE_HUNDREDTH 0.01f
#define AWE_FLOAT_ONE_THOUSANDTH 0.001f
#define AWE_FLOAT_QUARTER 0.25f
#define AWE_FLOAT_HALF 0.5f
#define AWE_FLOAT_ONE 1.0f
#define AWE_FLOAT_TWO 2.0f
#define AWE_FLOAT_FOUR 4.0f
#define AWE_FLOAT_TEN 10.0f
#define AWE_FLOAT_ONE_HUNDRED 100.0f
#define AWE_FLOAT_ONE_THOUSAND 1000.0f
#define AWE_FLOAT_E 2.7182818284f
#define AWE_FLOAT_32768 32768.0f
#define AWE_FLOAT_MINUS_32768 -32768.0f
#define AWE_FLOAT_INV_SQRT_TWO 0.707106781186548f
#define AWE_MIN_FLOAT 1.175494351e-38f
#define AWE_MAX_FLOAT 3.402823466e+38f

#else

#define PI (fr32)0x43243F6B
#define TWO_PI (fr32)0x45243F6B
#define PIDIV4 (fr32)0x3F243F6B
#define PIF (fr32)0x43243F6B
#define TWO_PIF (fr32)0x45243F6B
#define PIDIV4F (fr32)0x3F243F6B
#define AWE_FLOAT_ZERO (fr32)0x00000000
#define AWE_FLOAT_ONE_HUNDREDTH (fr32)0x328F5C29
#define AWE_FLOAT_ONE_THOUSANDTH (fr32)0x2C0C49BA
#define AWE_FLOAT_QUARTER (fr32)0x3C000000
#define AWE_FLOAT_HALF (fr32)0x3E000000
#define AWE_FLOAT_ONE (fr32)0x40000000
#define AWE_FLOAT_TWO (fr32)0x42000000
#define AWE_FLOAT_FOUR (fr32)0x44000000
#define AWE_FLOAT_TEN (fr32)0x46800000
#define AWE_FLOAT_ONE_HUNDRED (fr32)0x4D200000
#define AWE_FLOAT_ONE_THOUSAND (fr32)0x53E80000
#define AWE_FLOAT_E (fr32)0x42B7E151
#define AWE_FLOAT_32768 (fr32)0x5E000000
#define AWE_FLOAT_MINUS_32768 (fr32)0xDE000000
#define AWE_FLOAT_INV_SQRT_TWO (fr32)0x3ED413CD

// 3.4924596548080444e-010
#define AWE_MIN_FLOAT (fr32)0x01000000
// 4294967232
#define AWE_MAX_FLOAT (fr32)0x7FFFFFFF

#endif

#if (defined(WIN32) || defined(__linux__) || defined(DSPC_CORTEX_M) || defined(OMAP_DSP) || defined(IMX25))

#ifndef fmaxf
#define fmaxf(x, y)	(((x) > (y)) ? (x): (y))
#endif

#ifndef fminf
#define fminf(x, y)	(((x) < (y)) ? (x) : (y))
#endif

#endif // WIN32 || DSPC_CORTEX_M || OMAP_DSP || IMX25

#if defined(_TMS320C6700)

#ifndef fminf
static VEC_INLINE FLOAT32 fminf(FLOAT32 x, FLOAT32 y)
{
  return (x < y) ? x : y;
}
#endif

#ifndef fmaxf
static VEC_INLINE FLOAT32 fmaxf(FLOAT32 x, FLOAT32 y)
{
  return (x > y) ? x : y;
}
#endif

#ifndef min
#define min(x, y) (((x) < (y)) ? (x) : (y))
#endif

#ifndef max
#define max(x, y) (((x) > (y)) ? (x) : (y))
#endif

#define divf_approx(num, den) ((num) * _rcpsp(den))

#else

#define divf_approx(num, den) ((num) / (den))

#endif // !defined(_TMS320C6700)

// Visual Studio version must be less than VS2015
#if defined(WIN32) && (_MSC_VER < 1900)

#ifndef fabsf
static VEC_INLINE FLOAT32 fabsf(FLOAT32 x)
{
  return (x < 0.0f) ? -x : x;
}
#endif

#if !defined(expf) && !defined(_M_AMD64)
static VEC_INLINE FLOAT32 expf(FLOAT32 v)
{
	return (float)exp(v);
}
#endif

#if !defined(sqrtf) && !defined(_M_AMD64)
static VEC_INLINE FLOAT32 sqrtf(FLOAT32 v)
{
  return (float)sqrt(v);
}
#endif

#if !defined(sinf) && !defined(_M_AMD64)
static VEC_INLINE FLOAT32 sinf(FLOAT32 v)
{
  return (float)sin(v);
}
#endif

#if !defined(cosf) && !defined(_M_AMD64)
static VEC_INLINE FLOAT32 cosf(FLOAT32 v)
{
  return (float)cos(v);
}
#endif

#if !defined(tanf) && !defined(_M_AMD64)
static VEC_INLINE FLOAT32 tanf(FLOAT32 v)
{
  return (float)tan(v);
}
#endif

#if !defined(sinhf) && !defined(_M_AMD64)
static VEC_INLINE FLOAT32 sinhf(FLOAT32 v)
{
  return (float)sinh(v);
}
#endif

#if !defined(floorf) && !defined(_M_AMD64)
static VEC_INLINE FLOAT32 floorf(FLOAT32 X)
{
  return (float)floor(X);
}
#endif

#if !defined(logf) && !defined(_M_AMD64)
static VEC_INLINE FLOAT32 logf(FLOAT32 X)
{
  return (float)log(X);
}
#endif

#if !defined(coshf) && !defined(_M_AMD64)
static VEC_INLINE FLOAT32 coshf(FLOAT32 X)
{
  return (float)cosh(X);
}
#endif

#if !defined(ceilf) && !defined(_M_AMD64)
static VEC_INLINE FLOAT32 ceilf(FLOAT32 X)
{
  return (float)ceil(X);
}
#endif

#if !defined(atanf) && !defined(_M_AMD64)
static VEC_INLINE FLOAT32 atanf(FLOAT32 X)
{
  return (float)atan(X);
}
#endif

#if !defined(atan2f) && !defined(_M_AMD64)
static VEC_INLINE FLOAT32 atan2f(FLOAT32 Y, FLOAT32 X)
{
  return (float)atan2(Y, X);
}
#endif

#if !defined(asinf) && !defined(_M_AMD64)
static VEC_INLINE FLOAT32 asinf(FLOAT32 X)
{
  return (float)asin(X);
}
#endif

#if !defined(acosf) && !defined(_M_AMD64)
static VEC_INLINE FLOAT32 acosf(FLOAT32 X)
{
  return (float)acos(X);
}
#endif

#if !defined(fmodf) && !defined(_M_AMD64)
static VEC_INLINE FLOAT32 fmodf(FLOAT32 X, FLOAT32 Y)
{
  return (float)fmod(X, Y);
}
#endif

#if !defined(tanhf) && !defined(_M_AMD64)
static VEC_INLINE FLOAT32 tanhf(FLOAT32 X)
{
  return (float)tanh(X);
}
#endif

#if !defined(powf) && !defined(_M_AMD64)
static VEC_INLINE FLOAT32 powf(FLOAT32 X, FLOAT32 Y)
{
  return (float)pow(X, Y);
}
#endif

#ifndef frexpf
static VEC_INLINE FLOAT32 frexpf(FLOAT32 X, int *E)
{
  return (float)frexp(X, E);
}
#endif

#ifndef ldexpf
static VEC_INLINE FLOAT32 ldexpf(FLOAT32 X, int E)
{
  return (float)ldexp(X, E);
}
#endif

#ifndef modff
static VEC_INLINE FLOAT32 modff(FLOAT32 X, FLOAT32 *N)
{
  FLOAT32 fval;
  double dummy;

  fval = (float)modf(X, &dummy);

  // For some reason, this call always returns nval=0.  So, compute
  // it again here.

  *N = X-fval;

  return (float)fval;
}
#endif

#endif	//WIN32

#ifdef IA610

#define frexpf(X, Y) fr32_frexpf(X, Y)
#define fabsf(X) fr32_fabsf(X)
#define ldexpf(X, E) fr32_ldexpf(X, E)
#define fminf(X, Y) fr32_fminf(X, Y)
#define fmaxf(X, Y) fr32_fmaxf(X, Y)
#define expf(X) fr32_expf(X)
#define logf(X) fr32_logf(X)
#define exp10f(X) fr32_exp10f(X)
#define log10f(X) fr32_log10f(X)
#define exp2f(X) fr32_exp2f(X)
#define log2f(X) fr32_log2f(X)
#define powf(X, Y) fr32_powf(X, Y)
#define sinf(X) fr32_sinf(X)
#define cosf(X) fr32_cosf(X)
#define tanf(X) fr32_tanf(X)
#define asinf(X) fr32_asinf(X)
#define acosf(X) fr32_acosf(X)
#define atanf(X) fr32_atanf(X)
#define atan2f(X, Y) fr32_atan2f(X, Y)
#define sinhf(X) fr32_sinhf(X)
#define coshf(X) fr32_coshf(X)
#define tanhf(X) fr32_tanhf(X)
#define sqrtf(X) fr32_sqrtf(X)
#define truncf(X) fr32_truncf(X)
#define floorf(X) fr32_floorf(X)
#define ceilf(X) fr32_ceilf(X)
#define modff(X, Y) fr32_modff(X, Y)
#define fmodf(X, Y) fr32_fmodf(X, Y)
#define fdimf(X, Y) fr32_fdimf(X, Y)

//#define db10f(X) fr32_db10f(X)
//#define undb10f(X) fr32_undb10f(X)
//#define db20f(X) fr32_db20f(X)
//#define undb20f(X) fr32_undb20f(X)

#endif


/* ----------------------------------------------------------------------
** Fast approximation to the log2() function.  It uses a two step
** process.  First, it decomposes the floating-point number into
** a fractional component F and an exponent E.  The fraction component
** is used in a polynomial approximation and then the exponent added
** to the result.  A 3rd order polynomial is used and the result
** when computing db20() is accurate to 7.984884e-003 dB.
** ------------------------------------------------------------------- */

extern FLOAT32 log2f_approx_coeff[4];

static VEC_INLINE FLOAT32 log2f_approx(FLOAT32 X)
{
	FLOAT32 *C = &log2f_approx_coeff[0];
	FLOAT32 Y;
	FLOAT32 F;
	INT32 E;

	// This is the approximation to log2()
	F = frexpf(X, &E);

	//  Y = C[0]*F*F*F + C[1]*F*F + C[2]*F + C[3] + E;
	Y = *C++;
	Y *= F;
	Y += (*C++);
	Y *= F;
	Y += (*C++);
	Y *= F;
	Y += (*C++);

#ifdef IA610
	Y += int_to_afloat(E);
#else
	Y += E;
#endif

	return Y;
}

/* ----------------------------------------------------------------------
** Computes the log2 of a fractional value and returns the result in
** Q6.26 format.  The function is accurate to 1.326392691030e-3 (when
** viewed as a floating-point number.
** ------------------------------------------------------------------- */

extern fract32 log2_coeff_fract32[4];
extern int signbits(fract32 x);

static VEC_INLINE fract32 log2_fract32(fract32 X)
{

  fract32 *C = log2_coeff_fract32;
  fract32 y;
  int E;
  fract32 M;

  if (X == 0)
	  // Special case handling for 0.  Return the smallest possible number
	  return((fract32)0x80000000);
  else if (X < 0)
	  X = -X;

  // Turn into exponent and mantissa.
  E = signbits(X);
  M = shl_fr1x32(X, (short) E);

  y = *C++;
  y = mult_fr1x32x32NS(y, M);
  y += (*C++);
  y = mult_fr1x32x32NS(y, M);
  y += (*C++);
  y = mult_fr1x32x32NS(y, M);
  y += (*C++);

  return(y - (E << 26));
}

/* ----------------------------------------------------------------------
** Computes the db20 of a fractional Q1.31 value and returns the result
** in Q6.26 format.  The function is accurate to 8e-3 (when
** viewed as a floating-point number.
** ------------------------------------------------------------------- */

extern fract32 LinearToDecibels_coeff_fract32[5];

static VEC_INLINE fract32 db20_fract32(fract32 X)
{
	fract32 y;
	// input is Q16.16
	// the relayed function expects a value in format Q1.31 and produces a result in Q6.26
	// add offset to compensate the difference between the actual input in Q16.16
	y = log2_fract32(X) + ((31 - 16) << 26);
	// Shift 3 spaces to allow values of up to 190dB plus 3 more to prepare the function for the next multiplication
	y >>= 3;
	// Shift 3 more bits to the right to pre-multiply by 8 for the following operation
	// Handling for 0. Return the gretest negative number
	if (X == 0)
		y = (fract32)0x80000000;
	else
		// Multiply by db20(2) / 8
		// round((db20(2)/8)) * 2^31
		y = mult_fr1x32x32NS(y, 1616142483);

	return y;
}

/* ----------------------------------------------------------------------
** Fast approximation to the pow2() function.  It uses a two step
** process.  First, it decomposes the floating-point number into
** an integer I and fractional component F.  The fraction component
** is used in a polynomial approximation and then the exponent raised to
** the power of 2 multiplies the result.  The function uses the ldexpf
** function for speed.  A 6th order polynomial is used and the result
** when computing undb20() is accurate to 3.228661e-002 dB
** ------------------------------------------------------------------- */

extern FLOAT32 pow2f_approx_coeff[6];

static VEC_INLINE FLOAT32 pow2f_approx(FLOAT32 X)
{
	FLOAT32 *C = &pow2f_approx_coeff[0];
	FLOAT32 I;
	FLOAT32 F;
	FLOAT32 Y;

	// This is the integer component
	I = floorf(X);

	// This is the fractional component
	F = X - I;

	Y = *C++;
	Y *= F;
	Y += (*C++);
	Y *= F;
	Y += (*C++);
	Y *= F;
	Y += (*C++);
	Y *= F;
	Y += (*C++);
	Y *= F;
	Y += (*C++);

	  // This is the integer component
#ifdef IA610
	Y = ldexpf(Y, afloat_to_int(I));
#else
	Y = ldexpf(Y, (INT32)I);
#endif

	return Y;
}



/* ----------------------------------------------------------------------
** Computes the pow2 of a fractional value. The input is in Q6.26 format
** and the output in Q16.16 format.  You have to ensure that the inputs 
** are in the proper range.  That is the integer part of the input must
** be in the range [-15 15] or there will be numerical problems.  
** (This isn't checked here because it is often easier to do in the 
** higher level calling function.)
** ------------------------------------------------------------------- */

extern fract32 pow2_coeff_fract32[7];

static VEC_INLINE fract32 pow2_fract32(fract32 x)
{
  fract32 *C = pow2_coeff_fract32;
  fract32 y;
  int I;
  fract32 F;
  fract32 val;
  int E;

  // Compute the integer and fractional portions of the Q6.26 input
  I = x >> 26;
  F = (0x03FFFFFF & x) << 5;

  // Evaluate the 6th order polynomial

  y = *C++;
  y = mult_fr1x32x32NS(y, F);
  y += (*C++);
  y = mult_fr1x32x32NS(y, F);
  y += (*C++);
  y = mult_fr1x32x32NS(y, F);
  y += (*C++);
  y = mult_fr1x32x32NS(y, F);
  y += (*C++);
  y = mult_fr1x32x32NS(y, F);
  y += (*C++);
  y = mult_fr1x32x32NS(y, F);
  y += (*C++);

  // Now keep track of the final number of bits to shift.
  // We have to shift:
  //    15 bits right because we want to convert from Q1.31 to Q16.16
  //    3 bits left because the coefficients were scaled down by 1/8
  //    Then the integer number of bits to the right

  E = 15 - 3 - I;
  if (E < 0)
    val = y << (-E);
  else
    val = y >> E;

  return val;
}

#ifndef db10f
static VEC_INLINE FLOAT32 db10f(FLOAT32 X)
{
	X = fabsf(X);

#ifdef IA610
	if (X < AWE_MIN_FLOAT)
	{
		return (fr32)0xCCF48CAB; //  -94.568686021917173
	}
	else
	{
		return (logf(X) * (fr32)0x442BE59E);
	}
#else
	if (X < AWE_MIN_FLOAT)
	{
		return -3.7929779e+02f;
	}
	else
	{
		return logf(X) * 4.34294481903252f;
	}
#endif
}

#endif

#ifndef db10f_approx
static VEC_INLINE FLOAT32 db10f_approx(FLOAT32 X)
{
	X = fabsf(X);

#ifdef IA610
	if (X < AWE_MIN_FLOAT)
	{
		return (fr32)0xCCF48CAB; //  -94.568686021917173
	}
	return (log2f_approx(X) * (fr32)0x4302A305);
#else
	if (X < AWE_MIN_FLOAT)
	{
		return -3.7929779e+02f;
	}
	return log2f_approx(X) * 3.010299956639812f;
#endif
}
#endif

#ifndef undb10f

static VEC_INLINE FLOAT32 undb10f(FLOAT32 X)
{	
#ifdef IA610
	return expf(X * (fr32)0x3BAF238C);
#else
    return expf(X * 0.230258509299405f);
#endif
}
#endif


#ifndef undb10f_approx
static VEC_INLINE FLOAT32 undb10f_approx(FLOAT32 X)
{
#ifdef IA610
	return pow2f_approx(X * (fr32)0x3CA854B4);
#else
	return pow2f_approx(X * 0.332192809488736f);
#endif
}
#endif


#ifndef db20f
static VEC_INLINE FLOAT32 db20f(FLOAT32 X)
{
	X = fabsf(X);

#ifdef IA610

	if (X < AWE_MIN_FLOAT)
	{
		return (fr32)0xCEF48CAB;  //  -1.891373720438344e+02
	} 
	else
	{
		return (logf(X) * (fr32)0x462BE59E);
	}
#else
	if (X < AWE_MIN_FLOAT)
	{
		return -7.5859558e+02f;
	} 
	else
	{
		return logf(X) * 8.68588963806504f;
	}
#endif
}
#endif

#ifndef db20f_approx
static VEC_INLINE FLOAT32 db20f_approx(FLOAT32 X)
{
	X = fabsf(X);
     
#ifdef IA610
    if (X < AWE_MIN_FLOAT)
    {
		return (fr32)0xCEF48CAB;  //  -1.891373720438344e+02
    }
    return (log2f_approx(X) * (fr32)0x4502A305);
#else
    if (X < AWE_MIN_FLOAT)
    {
		return -7.5859558e+02f;
    }
    return log2f_approx(X) * 6.020599913279624f;
#endif
}
#endif

#ifndef undb20f
static VEC_INLINE FLOAT32 undb20f(FLOAT32 X)
{
#ifdef IA610
	return expf(X * (fr32)0x39AF238C);
#else
	return expf(X * 0.115129254649702f);
#endif
}
#endif


#ifndef undb20f_approx
static VEC_INLINE FLOAT32 undb20f_approx(FLOAT32 X)
{
#ifdef IA610
	// Y = pow2_approx((X/20)*log2(10), ORDER);
	return pow2f_approx(X * (fr32)0x3AA854B4);
#else
	// Y = pow2_approx((X/20)*log2(10), ORDER);
	return pow2f_approx(X * 0.166096404744368f);
#endif
}
#endif


  /* ----------------------------------------------------------------------
  ** Converts floating-point values in the range [-1 +1) to fractional
  ** values
  ** ------------------------------------------------------------------- */

#ifndef float_to_fract32
static VEC_INLINE fract32 float_to_fract32(FLOAT32 x)
{
    // Clip to the allowable range
	FLOAT32 temp;

#ifdef IA610

    if (x < FR32_MINUS_ONE)
    {
        return (fract32)0x80000000;
    }

    if (x >= FR32_ONE)
    {
        return 0x7FFFFFFF;
    }

	temp = x * float_to_afloat(2147483648.0f);

	if (temp > FR32_ZERO)
	{
		temp += float_to_afloat(0.5f);
	}
	else
	{
		temp += float_to_afloat(-0.5f);
	}

    // Multiply by 2^31
    return (fract32)(afloat_to_int(temp));

#else

    if (x < -1.0f)
    {
        return (fract32)0x80000000;
    }

    if (x >= 1.0f)
    {
        return 0x7FFFFFFF;
    }

	temp = x * 2147483648.0f;
	temp += temp > 0.0f? 0.5f : -0.5f;

    // Multiply by 2^31
    return (fract32)(temp);

#endif
}
#endif

  /* ----------------------------------------------------------------------
  ** Converts fractional values to their floating-point equivalents in the
  ** range [-1 +1)
  ** ------------------------------------------------------------------- */

#ifndef fract32_to_float
static VEC_INLINE FLOAT32 fract32_to_float(fract32 x)
{
#ifdef IA610
    // Multiply by 2^(-31)
    return (int_to_afloat(x) * float_to_afloat(4.6566128731e-010f));
#else
    // Multiply by 2^(-31)
    return ((FLOAT32)x * 4.6566128731e-010f);
#endif
}
#endif

//// SHARC intrinsic functions
//
//#if defined(WIN32) || defined(__ADSPBLACKFIN__) || (__CC_ARM || defined(__GNUC__))
//fract32 float_to_fract32(FLOAT32 x);
//FLOAT32 fract32_to_float(fract32 x);
//#endif /* WIN32 or Blackfin */
//





#endif  // _math_helper_h
