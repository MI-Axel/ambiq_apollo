/* ----------------------------------------------------------------------
** Stereo asynchronous sample rate converter.
** Fixed-point Q31 implementation.
**
** Copyright (c) 2016 DSP Concepts, Inc. All rights reserved.
** ------------------------------------------------------------------- */

#ifndef _DSPC_ASRC_H_
#define _DSPC_ASRC_H_

#ifdef WIN32
//#include <stdint.h>

typedef short fract16;
typedef int fract32;
typedef long long fract64;
#else
#include <stdint.h>

#if !defined(FRACT_TYPES_DEFINED)
typedef int16_t fract16;
typedef int32_t fract32;
typedef int64_t fract64;
#define FRACT_TYPES_DEFINED
#endif
#endif

/* Error conditions */
#define DSPC_ASRC_OK (0)
#define DSPC_ASRC_INPUT_OVERFLOW (-1)
#define DSPC_ASRC_OUTPUT_UNDERFLOW (-2)
           
#define DSPC_ASRC_STATE_LEN(INPUT_BLOCK_SIZE, OUTPUT_BLOCK_SIZE, SR_IN, PHASELEN) \
        ((PHASELEN) + 1 + ((((2 * (INPUT_BLOCK_SIZE) - (OUTPUT_BLOCK_SIZE)) > (OUTPUT_BLOCK_SIZE) ? \
        (6 * (2 * (INPUT_BLOCK_SIZE) - (OUTPUT_BLOCK_SIZE)) * 1000 / ((SR_IN))) : \
        (6 * (OUTPUT_BLOCK_SIZE) * 1000 / ((SR_IN)))) * (SR_IN) / 1000)))
        
#define DSPC_ASRC_GUARD_LEN(SR_IN, SR_OUT, PHASELEN, OUTPUT_BLOCK_SIZE) \
        ( ( ((SR_IN) * (OUTPUT_BLOCK_SIZE)) / (SR_OUT) ) + 2 + (PHASELEN))
       
#define DSPC_ASRC_BUFFER_LEN(SR_IN, SR_OUT, PHASELEN, INPUT_BLOCK_SIZE, OUTPUT_BLOCK_SIZE, NUM_CHANNELS) \
        ((NUM_CHANNELS) * (DSPC_ASRC_STATE_LEN(INPUT_BLOCK_SIZE, OUTPUT_BLOCK_SIZE, SR_IN, PHASELEN) + \
        DSPC_ASRC_GUARD_LEN(SR_IN, SR_OUT, PHASELEN, OUTPUT_BLOCK_SIZE))) 
      
/* This structure defines a single instance of the sample rate converter. */
typedef struct _DSPC_ASRC
{
  /* Parameters that must be configured by the user */

  /* Internal upsample factor.  This must be a power of 2. */
  int M;
  
  /* Number of columns (one per phase) in H matrix */
  int step;  

  /* Length of the state buffer in stereo/mono samples. */
  int stateLen;

  /* Extension to the state buffer. Used to avoid wrapping during reads. */
  int guardLen;

  /* Length of the state buffer in stereo/mono samples plus length */
  int bufLen;

  /* Points to the filter coefficients.  */
  const void *H;

  /* Length of the filter coefficients.  */
  int filtLen;

  /* 64-bit register which is added to readIndexFract after every output sample is computed.
  ** This is set by the user and is equal to:
  **   (FSin / FSout) * (2^(32 + Mbits))
  ** You set this incrementally larger or smaller as the sample rates vary. 
  ** If the buffer regulator is enabled then this value gets updated automatically. */
  fract64 fStep;

  /* The number of interleaved channels in input and output data. */
  int numChannels;

  /* Indicates if the jitter buffer regulator is active or not. */
  int regEnable;

  /* Keeps track of the maximum number of samples contained in the buffer at a given time. */
  int bufferLevelMax;

  /* Keeps track of the minimum number of samples contained in the buffer at a given time. */
  int bufferLevelMin;

  /* Internal parameters */

  /* Points to the state variable array.  Of length numChannels * stateLen.  */
  void *state;

  /* Length of each phase of the filter.  Roughly equal to filtLen / M. */
  int phaseLen;

  /* log2(M). */
  int Mbits;

  /* Bit mask used to pull out the M bits from the 64-bit register. */
  int Mmask;

  /* Index where the next input sample is written into the state buffer. */
  int writeIndex;

  /* 64-bit register which advances through the input state buffer.  The register advances at
  ** the output data rate.  The bits in the register are divided as followed:
  **    [ readIndexInt (32-Mbits) | readIndexM (Mbits) | readIndexFract (32-bits)]
  */
  fract64 readIndexFract;

  /* 64-bit register which zeros out the readIndexInt portion of the register.  That is,
  ** it includes 1's at the readIndexM and readIndexFract locations. */
  fract64 readIndexMask;

  /* Regulator states and parameters */

  /* Jitter buffer error-state. Integrates the difference between the actual buffer 
  ** level and the desired buffer level over time. */
  float levelErrorAccum;

  /* State variables for the jitter buffer regulator */
  float *regState;

  /* State-space coefficients for the jitter buffer regulator.*/
  const float *a;
  const float *b;
  const float *c; 
  const float *d;

  /* Time state */
  int TS;

} DSPC_ASRC;

/* Properties for a configuration of the ASRC; used for dspc_asrc_init() */
typedef struct {
  fract64 fStep;        /* fractional frequency step, internal */
  const void *H;		/* antialiasing filter impulse response */
  float fsIn;			/* readonly: input sample rate Hz of filter design */
  float fsOut;			/* readonly: output sample rate Hz of design */
  float fPass;			/* readonly: passband in Hz, attenuation < 0.1dB */
  int phaseLen;			/* polyphase filter length == filtLen / M */
  int M;				/* internal upsample factor, must be power of 2 */
  int step;				/* [SQ] added, not necessarily the same as M */
  int filtLen;			/* total length of filter H */
  const float *a;		/* array of 2-by-2 A matrix coefficients for regulator */
  const float *b;		/* array of 2-by-2 B matrix coefficients for regulator */
  const float *c;		/* array of 1-by-2 C matrix coefficients for regulator */
  const float *d;		/* array of 1-by-2 D matrix coefficients for regulator */
  float *regState;/* array of 2 initial states */
  float levelErrorAccum;/* initial error-state */
} DSPC_ASRC_PROPS;

/* Prepare the ASRC runtime state structure from a static property struct
   and work buffer spec.  Call this once at the start of processing. */

void dspc_asrc_init_Q15(DSPC_ASRC_PROPS *props, fract16 * JitterBuffer, int stateLen, int guardLen, int numChannels, DSPC_ASRC *A);
void dspc_asrc_init_Q31(DSPC_ASRC_PROPS *props, fract32 * JitterBuffer, int stateLen, int guardLen, int numChannels, DSPC_ASRC *A);

/* Resets the internal state variables of the ASRC. */

void dspc_asrc_reset_Q15(DSPC_ASRC *A);
void dspc_asrc_reset_Q31(DSPC_ASRC *A);

/* Returns the number of input samples that can be written into the state buffer.
** The value returned equals the number of stereo/mono samples that can be written 
** into the buffer.  For example, in stereo mode if the function returns 10 then 
** you can write a total of 20 32-bit words (L, R, L, R, etc) into the buffer.  */

int dspc_asrc_input_avail(DSPC_ASRC *A);

/* Returns the number of stereo/mono samples that the ASRC can generate based on 
** the number of samples in the jitter buffer and the conversion factor fStep. */

int dspc_asrc_output_avail(DSPC_ASRC *A);

/* Writes data into the state buffer.  In stereo mode, IN points to the stereo 
** interleaved input data.  numSamples is the number of stereo/mono samples to 
** write.  Internally, the function calls dspc_asrc_input_avail() and makes sure 
** that there is room for numSamples samples.  The function returns DSPC_ASRC_OK 
** if successful or DSPC_ASRC_INPUT_OVERFLOW if there is not enough room in the 
** jitter buffer to accommodate the data.  If an error occurs, the function 
** returns immediately without writing to the jitter buffer. */

int dspc_asrc_write_input_Q15(DSPC_ASRC *A, fract16 *IN, int numSamples);
int dspc_asrc_write_input_Q31(DSPC_ASRC *A, fract32 *IN, int numSamples);

/* Writes zeros into the state buffer.  In stereo mode, numSamples represents the
** number of stereo sample pairs. The function returns DSPC_ASRC_OK if
** it was able to write numSamples of data into the state buffer.  The
** function returns DSPC_ASRC_INPUT_OVERFLOW if there is not enough
** room in the state buffer. */

int dspc_asrc_write_zeros_Q15(DSPC_ASRC *A, int numZeros);
int dspc_asrc_write_zeros_Q31(DSPC_ASRC *A, int numZeros);

/* Main processing function.  Generates output data. In stereo mode, numSamples represents
** the number of stereo sample pairs.  The function checks if there is enough
** data in the state buffer to satisfy the request.  The function returns DSPC_ASRC_OK
** upon successful completion or DSPC_ASRC_OUTPUT_UNDERFLOW if there are not enough
** samples in the jitter buffer to fulfill the request.
**
** There are two versions of the function:  linear interpolation and cubic
** interpolation. */

int dspc_asrc_read_output_linear_Q15(DSPC_ASRC *A, fract16 *OUT, int numSamples);
int dspc_asrc_read_output_linear_Q31(DSPC_ASRC *A, fract32 *OUT, int numSamples);

int dspc_asrc_read_output_cubic_Q15(DSPC_ASRC *A, fract16 *OUT, int numSamples);
int dspc_asrc_read_output_cubic_Q31(DSPC_ASRC *A, fract32 *OUT, int numSamples);

/* Returns the number of samples of latency based on the input sample rate. */

int dspc_asrc_latency(DSPC_ASRC *A);

/* Clears the buffer and fills it half full with zeros, then turns on the regulator.
** Returns the same status code as dspc_asrc_write_zeros() above. */

int dspc_asrc_reg_init(DSPC_ASRC *A);

/* This is a helper function for computing how many milliseconds of input data the 
** buffer needs to be able to hold. */
int dspc_asrc_msec(int input_blk_size, int output_blk_size, int input_sample_rate);

#endif        /* !defined DSPC_ASRC_H_ */
