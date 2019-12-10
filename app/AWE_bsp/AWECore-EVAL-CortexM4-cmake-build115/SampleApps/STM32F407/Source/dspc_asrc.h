/* ----------------------------------------------------------------------
** Multichannel asynchronous sample rate converter header file
** Fixed-point Q31 and Q15 implementations.
**
** Copyright (c) 2019 DSP Concepts, Inc. All rights reserved.
** ------------------------------------------------------------------- */

/** @file */ 

#ifndef _DSPC_ASRC_H_
#define _DSPC_ASRC_H_

/* Define fract data types if not defined yet*/
#ifndef ASRC_FRACT_TYPES_DEFINED
#include <stdint.h>
typedef int16_t fract16;
typedef int32_t fract32;
typedef int64_t fract64;
#define ASRC_FRACT_TYPES_DEFINED
#endif

/** 
* \defgroup ASRCStructs ASRC Structures
* @{
*/
      
/** This structure defines a single instance of the asynchronous sample rate converter. */
typedef struct _DSPC_ASRC
{
  /** Internal upsample factor.  This must be a power of 2. */
  int M; 
  
  /** Number of phases in filter buffer */
  int step;  

  /** Length of the state buffer for each channel in samples. */
  int stateLen;

  /** Extension to the state buffer. Used to avoid wrapping during reads. */
  int guardLen;

  /** Total length of the state buffer in samples */
  int bufLen;

  /** Points to the filter coefficients.  */
  const void *H;

  /** Length of the filter coefficients.  */
  int filtLen;

  /** 64-bit register which is added to readIndexFract after every output sample is computed.
  ** If the internal regulator is enabled then this value gets updated automatically during
  ** the calls to the read functions. 
  ** If the regulator is disabled, this is set by the user using this relationship:
  **   (FSin / FSout) * (2^(32 + Mbits))
  ** Set this incrementally larger or smaller as the relative sample rates vary. 
  */
  fract64 fStep;

  /** The number of interleaved channels in input and output data. */
  int numChannels;

  /** Indicates if the jitter buffer regulator is active or not. */
  int regEnable;

  /** Internal parameters */

  /** Points to the state variable array (aka, jitterBuffer).  Of total length numChannels * (stateLen + guardLen).  */
  void *state;

  /** Length of each phase of the filter.  Roughly equal to filtLen / M. */
  int phaseLen;

  /** log2(M). Used in setting/getting fStep. */
  int Mbits;

  /** Bit mask used to pull out the M bits from the 64-bit register. */
  int Mmask;

  /** Index where the next input sample is written into the state buffer. */
  int writeIndex;

  /** 64-bit register which advances through the input state buffer.  The register advances at
  ** the output data rate.  The bits in the register are divided as followed:
  **    [ readIndexInt (32-Mbits) | readIndexM (Mbits) | readIndexFract (32-bits)]
  */
  fract64 readIndexFract;

  /** 64-bit register which zeros out the readIndexInt portion of the register.  That is,
  ** it includes 1's at the readIndexM and readIndexFract locations. */
  fract64 readIndexMask;

  /** Accumulator array for filter implementation. Memory allocated by user - see @ref DSPC_ASRC_ACCUM_LEN macro */
  void *accum;

  /*****************************************************
   * The parameters below are for the internal ASRC regulator
   *****************************************************/

  /** Accumulated error-state. */
  float levelErrorAccum;

  /** State variables for the jitter buffer regulator */
  float *regState;

  /** nominal sample rate ratio */
  float fsRatio;

  /** State-space coefficients for the jitter buffer regulator.*/
  const float *a;
  const float *b;
  const float *c; 
  const float *d;
 
} DSPC_ASRC;


/** Coefficient specific properties for a configuration of the ASRC.
**  Used for  @ref dspc_asrc_init_Q15 and @ref dspc_asrc_init_Q31
**  to initialize ASRC instance with required information 
**  and to do required error checking. All of these values are read only
**  and should not be changed by the user.
*/
typedef struct {
  /** fractional frequency step, internal */
  fract64 fStep;                
  /** antialiasing filter impulse response */
  const void *H;		        
  /** input sample rate Hz of filter design */
  float fsIn;			        
  /** readonly: output sample rate Hz of design */
  float fsOut;			       
  /** readonly: passband in Hz, attenuation < 0.1dB */ 
  float fPass;			       
  /** polyphase filter length == filtLen / M */ 
  int phaseLen;			    
  /** internal upsample factor, must be power of 2 */    
  int M;				        
  /** Adjusted upsample factor */
  int step;				        
  /** total length of filter H */
  int filtLen;			        
  /** 1 if coefficients are  interleaved */
  int coeffsInterleaved;        
  /** attenuation level of filter - informational only  */
  int atten;                
  /** array of 2-by-2 A matrix coefficients for regulator */    
  const float *a;		        
  /** array of 2-by-2 B matrix coefficients for regulator */
  const float *b;		        
  /** array of 1-by-2 C matrix coefficients for regulator */
  const float *c;		        
  /** array of 1-by-2 D matrix coefficients for regulator */
  const float *d;		        
  /** array of 2 initial states */
  float *regState;		       
  /** initial accumulated error-state */
  float levelErrorAccum;        
} DSPC_ASRC_PROPS;

/** @}*/


/** 
* \defgroup ASRCAPI ASRC API
* @{
*/

/** Prepare the ASRC runtime state structure from a static property struct
**    and work buffer spec.  Call this once before start of processing for Q15
**    data type applications. This function will enable the internal ASRC
**    regulator and will initialize the provided jitter buffer with zeros.
**    
**  @param[in] *props                   Static coefficient specific property structure
**  @param[in] *pJitterBuffer 			Jitter buffer to be used in ASRC. Memory must be allocated by user 
**  @param[in] stateLen            		Length of the state element of jitter buffer - see @ref DSPC_ASRC_STATE_LEN                    
**  @param[in] guardLen            		Length of the guard element of jitter buffer - see @ref DSPC_ASRC_GUARD_LEN
**  @param[in] *pAccum                  Pointer to accumulator array used in ASRC. Memory must be allocated by user
**  @param[in] accumLen                  Length of accumulator array - see @ref DSPC_ASRC_ACCUM_LEN
**  @param[in] numChannels               Number of channels of audio being passed into ASRC
**  @param[out] *A                       Pointer to ASRC instance to be initialized
**
**  @return 
**    - @ref DSPC_ASRC_SUCCESS upon successful completion of initialization. 
**    - @ref DSPC_ASRC_ERR_ACCUM_LEN if the accumLen parameter passed in is 
**      not large enough for the number of channels being supported. Use 
**      the DSPC_ASRC_ACCUM_LEN macro defined in dspc_asrc.h to avoid this error. 
**    - @ref DSPC_ASRC_ERR_COEFF_ORDER if the loaded coefficient are not ordered as
**      required by the target. See the ASRC User's Guide for more details on 
**      target specific coefficients.
**    - @ref DSPC_ASRC_ERR_MAX_EVALS if more than 10 instances of the ASRC have been
**      initialized in the application.  (Demo/Evaluation libraries only!)
*/
int dspc_asrc_init_Q15(
	DSPC_ASRC_PROPS* props, 	
	fract16* pJitterBuffer, 	
	int stateLen,            	
	int guardLen,            	
	fract16 * pAccum,        	
	int accumLen,            	
	int numChannels,         	
	DSPC_ASRC *A             	
);

/** Prepare the ASRC runtime state structure from a static property struct
**    and work buffer spec.  Call this once before start of processing for Q31
**    data type applications. This function will enable the internal ASRC
**    regulator and will initialize the provided jitter buffer with zeros.
**    
**
**  @param[in] *props                   Static coefficient specific property structure
**  @param[in] *pJitterBuffer 			Jitter buffer to be used in ASRC. Memory must be allocated by user 
**  @param[in] stateLen            		Length of the state element of jitter buffer - see @ref DSPC_ASRC_STATE_LEN                    
**  @param[in] guardLen            		Length of the guard element of jitter buffer - see @ref DSPC_ASRC_GUARD_LEN
**  @param[in] *pAccum                  Pointer to accumulator array used in ASRC. Memory must be allocated by user
**  @param[in] accumLen                  Length of accumulator array - see @ref DSPC_ASRC_ACCUM_LEN
**  @param[in] numChannels               Number of channels of audio being passed into ASRC
**  @param[out] *A                       Pointer to ASRC instance to be initialized
**
**  @return 
**    - @ref DSPC_ASRC_SUCCESS upon successful completion of initialization. 
**    - @ref DSPC_ASRC_ERR_ACCUM_LEN if the accumLen parameter passed in is 
**      not large enough for the number of channels being supported. Use 
**      the DSPC_ASRC_ACCUM_LEN macro defined in dspc_asrc.h to avoid this error. 
**    - @ref DSPC_ASRC_ERR_COEFF_ORDER if the loaded coefficient are not ordered as
**      required by the target. See the ASRC User's Guide for more details on 
**      target specific coefficients.
**    - @ref DSPC_ASRC_ERR_MAX_EVALS if more than 10 instances of the ASRC have been
**      initialized in the application.  (Demo/Evaluation libraries only!)
*/
int dspc_asrc_init_Q31(
	DSPC_ASRC_PROPS * props, 	
	fract32 * pJitterBuffer, 	
	int stateLen,            	
	int guardLen,            	
	fract32 * pAccum,        	
	int accumLen,            	
	int numChannels,         	
	DSPC_ASRC *A             	
);

/** Resets the internal state variables of the Q15 ASRC. 
** @param[in]     *A            Pointer to ASRC instance 
*/
void dspc_asrc_reset_Q15(
    DSPC_ASRC *A    
);

/** Resets the internal state variables of the Q31 ASRC. 
** @param[in]     *A            Pointer to ASRC instance 
*/
void dspc_asrc_reset_Q31(
    DSPC_ASRC *A    
);

/** Returns the number of input samples that can be written into the state buffer.
** The value returned equals the number of samples per channel that can be written 
** into the buffer.  For example, in stereo mode with Q31 data, if the function returns 
** 10 then a total of 20 32-bit samples (L, R, L, R, etc) can be written into the buffer.  
** This function can be called by the user before calling dspc_asrc_write_input_Qxx
** to check if an overrun has occurred. 
**
** @param[in]     *A            Pointer to ASRC instance 
**
** @return Number of samples that can be written into ASRC instance
*/
int dspc_asrc_input_avail(
    DSPC_ASRC *A    
);

/** Returns the number of samples per channel that the ASRC can generate based on 
** the number of samples in the jitter buffer and the conversion factor fStep. 
** For example, in stereo mode with Q31 data, if the function returns 
** 10 then a total of 20 32-bit samples (L, R, L, R, etc) can be read from the buffer.
** Call this function before calling dspc_asrc_read_input_xxx_Qxx to check if 
** an underrun has occurred. 
**
** @param[in]     *A            Pointer to ASRC instance 
**
** @return Number of samples that can be read from ASRC instance
**  
*/
int dspc_asrc_output_avail(
    DSPC_ASRC *A    
);

/** Writes zeros into the state buffer for each channel in the Q15 ASRC Instance. It
** is recommended to call this function after @ref dspc_asrc_init_Q15 to prefill the
** jitter buffer halfway with zeros. This will ensure that the greatest amount
** of asynchronicity can be handled by the ASRC instance without an Xrun.
**
** To prefill a buffer halfway, numZeros should be (stateLen/2).
**
** @param[in]     *A            Pointer to ASRC instance 
** @param[in]     numSamples    Number of zeros to write for each channel
**
**  @return 
**    - @ref DSPC_ASRC_SUCCESS on completion.
*/
int dspc_asrc_write_zeros_Q15(
    DSPC_ASRC *A,    
    int numZeros     
);

/** Writes zeros into the state buffer for each channel in the Q31 ASRC Instance. It
** is recommended to call this function after @ref dspc_asrc_init_Q31 to prefill the
** jitter buffer halfway with zeros. This will ensure that the greatest amount
** of asynchronicity can be handled by the ASRC instance without an Xrun.
**
** To prefill a buffer halfway, numZeros should be (stateLen)/2.
**
** @param[in]     *A            Pointer to ASRC instance 
** @param[in]     numSamples    Number of zeros to write for each channel
**
**  @return 
**    - @ref DSPC_ASRC_SUCCESS on completion.
*/
int dspc_asrc_write_zeros_Q31(
    DSPC_ASRC *A,    
    int numZeros     
);


/** Writes Q15 data into the state buffer. 
** No internal error checking is done in 
** this function so @ref dspc_asrc_input_avail should be called before writing to
** state buffer if some action is to be taken by the application on an Xrun.
**
** @param[in]     *A    Pointer to ASRC instance 
** @param[in]     *IN     Pointer to input Q15 audio data
** @param[in]     numSamples   Number of samples (per channel) to write into ASRC
**
**  @return 
**    - @ref DSPC_ASRC_SUCCESS on completion.
*/
int dspc_asrc_write_input_Q15(
    DSPC_ASRC *A,     
    fract16 *IN,      
    int numSamples    
);


/** Writes Q31 data into the state buffer. 
** No internal error checking is done in 
** this function so @ref dspc_asrc_input_avail should be called before writing to
** state buffer if some action is to be taken by the application on an Xrun.
**
** @param[in]     *A    Pointer to ASRC instance 
** @param[in]     *IN     Pointer to input Q31 audio data
** @param[in]     numSamples   Number of samples (per channel) to write into ASRC
**
**  @return 
**    - @ref DSPC_ASRC_SUCCESS on completion.
*/
int dspc_asrc_write_input_Q31(
    DSPC_ASRC *A,     
    fract32 *IN,      
    int numSamples    
);


/** Main processing function that generates output Q15 data at the expected 
** sample rate. 
** 
** No internal error checking is done in this function so @ref dspc_asrc_output_avail
** should be called first and compared to the number of samples to be read if 
** some action is to be taken by the application on an Xrun.
** 
** If the internal regulator is enabled then fStep is updated
** inside this function.
**
** This function will implement a linear interpolation sample rate converter,
** which in general has better CPU performance but worse audio performance 
** than the cubic interpolation. The application can switch between linear
** and cubic interpolations during runtime if desired.
**
** @param[in]     *A    Pointer to ASRC instance 
** @param[out]    *OUT     Output buffer to be filled with Q15 data 
** @param[in]     numSamples   Number of samples (per channel) to read from ASRC buffer 
**	
**  @return 
**    - @ref DSPC_ASRC_SUCCESS upon completion.
*/
int dspc_asrc_read_output_linear_Q15(
    DSPC_ASRC *A,    
    fract16 *OUT,    
    int numSamples   
);


/** Main processing function that generates output Q31 data at the expected 
** sample rate. 
** 
** No internal error checking is done in this function so @ref dspc_asrc_output_avail
** should be called first and compared to the number of samples to be read if 
** some action is to be taken by the application on an Xrun.
** 
** If the internal regulator is enabled then fStep is updated
** inside this function.
**
** This function will implement a linear interpolation sample rate converter,
** which in general has better CPU performance but worse audio performance 
** than the cubic interpolation. The application can switch between linear
** and cubic interpolations during runtime if desired.
**
** @param[in]     *A    Pointer to ASRC instance 
** @param[out]    *OUT     Output buffer to be filled with Q31 data 
** @param[in]     numSamples   Number of samples (per channel) to read from ASRC buffer 
**	
**  @return 
**    - @ref DSPC_ASRC_SUCCESS upon completion.
*/
int dspc_asrc_read_output_linear_Q31(
    DSPC_ASRC *A,    
    fract32 *OUT,    
    int numSamples   
);

/** Main processing function that generates output Q15 data at the expected 
** sample rate. 
** 
** No internal error checking is done in this function so @ref dspc_asrc_output_avail
** should be called first and compared to the number of samples to be read if 
** some action is to be taken by the application on an Xrun.
** 
** If the internal regulator is enabled then fStep is updated
** inside this function.
**
** This function will implement a cubic interpolation sample rate converter,
** which in general has worse CPU performance but better audio performance 
** than the linear interpolation. The application can switch between linear
** and cubic interpolations during runtime if desired.
**
** @param[in]     *A    Pointer to ASRC instance 
** @param[out]    *OUT     Output buffer to be filled with Q15 data 
** @param[in]     numSamples   Number of samples (per channel) to read from ASRC buffer 
**	
**  @return 
**    - @ref DSPC_ASRC_SUCCESS upon completion.
*/
int dspc_asrc_read_output_cubic_Q15(
    DSPC_ASRC *A,    
    fract16 *OUT,    
    int numSamples   
);
      


/** Main processing function that generates output Q31 data at the expected 
** sample rate. 
** 
** No internal error checking is done in this function so @ref dspc_asrc_output_avail
** should be called first and compared to the number of samples to be read if 
** some action is to be taken by the application on an Xrun.
** 
** If the internal regulator is enabled then fStep is updated
** inside this function.
**
** This function will implement a cubic interpolation sample rate converter,
** which in general has worse CPU performance but better audio performance 
** than the linear interpolation. The application can switch between linear
** and cubic interpolations during runtime if desired.
**
** @param[in]     *A    Pointer to ASRC instance 
** @param[out]    *OUT     Output buffer to be filled with Q31 data 
** @param[in]     numSamples   Number of samples (per channel) to read from ASRC buffer 
**	
**  @return 
**    - @ref DSPC_ASRC_SUCCESS upon completion.
*/
int dspc_asrc_read_output_cubic_Q31(
    DSPC_ASRC *A,    
    fract32 *OUT,    
    int numSamples   
);


/** 
** Helper function that returns the current latency through ASRC in
** input samples. To convert this to time (seconds), divide by the 
** input sample rate.
** @param[in]     *A    Pointer to ASRC instance 
** @return 
** The current number of input samples of latency based on the current
** buffer level and filter length. 
*/
int dspc_asrc_latency(
    DSPC_ASRC *A
);

/** Helper function for returning the current level of the ASRC jitter buffer 
** in samples. The level is the same for every channel of audio in the instance.
** If the internal regulator is turned off, use this function to get feedback
** on the error of the current value of fStep and adjust as needed.
**
** @param[in]     *A    Pointer to ASRC instance 
** @return
**	 Current level of jitter buffer, in samples
*/
int dspc_asrc_get_buffer_level(
    DSPC_ASRC *A    
);

/** @return 
** The major version of the ASRC library 
*/
int dspc_asrc_get_version_major(void);

/** @return 
** The minor version of the ASRC library 
*/
int dspc_asrc_get_version_minor(void);

/** @} */




/** 
* \defgroup ASRCReturns ASRC Error Codes
* @{
*/

/** Successful completion */
#define DSPC_ASRC_SUCCESS 			(0)

/** Input overflow occurred. This means that the jitterBuffer has no room for new samples to be written. _unused_ */
#define DSPC_ASRC_ERR_INPUT_OVERFLOW 	        (-1)

/** Output underflow occurred. This means that the jitterBuffer has no new samples to be read. _unused_ */
#define DSPC_ASRC_ERR_OUTPUT_UNDERFLOW 	        (-2)

/** More than 10 evaluation instances have been initialized. _EVAL packages only_ */
#define DSPC_ASRC_ERR_MAX_EVALS			(-3)		

/** Memory allocated for accumulation buffer is insufficient. See DSPC_ASRC_ACCUM_LEN macro */
#define DSPC_ASRC_ERR_ACCUM_LEN			(-4)

/** Loaded configuration property structure has incorrect order of coefficients */
#define DSPC_ASRC_ERR_COEFF_ORDER		(-5)

/** @}*/


/** 
* \defgroup ASRCBufferSize ASRC Buffer Sizing Macros
* @{
*/

/** Calculate size of state length component of jitterBuffer. Returned value is in number of samples of Q31 or Q15 data */
#define DSPC_ASRC_STATE_LEN(INPUT_BLOCK_SIZE, OUTPUT_BLOCK_SIZE, SR_IN, PHASELEN) \
        ((PHASELEN) + 1 + ((( (((2 * (INPUT_BLOCK_SIZE)) - (OUTPUT_BLOCK_SIZE)) > (OUTPUT_BLOCK_SIZE)) ? \
        (6 * ((2 * (INPUT_BLOCK_SIZE)) - (OUTPUT_BLOCK_SIZE)) * 1000 / ((SR_IN))) : \
        (6 * (OUTPUT_BLOCK_SIZE) * 1000 / ((SR_IN)))) * (SR_IN) / 1000)))

/** Calculate size of guard length component of jitterBuffer. Returned value is in number of samples of Q31 or Q15 data */        
#define DSPC_ASRC_GUARD_LEN(SR_IN, SR_OUT, PHASELEN, OUTPUT_BLOCK_SIZE) \
        ( ( ((SR_IN) * (OUTPUT_BLOCK_SIZE)) / (SR_OUT) ) + 2 + (PHASELEN))
       
/** Calculate total size of jitterBuffer. This equals NUMCHANNELS * (stateLength + guardLength). Returned value is in number of samples of Q31 or Q15 data */
#define DSPC_ASRC_BUFFER_LEN(SR_IN, SR_OUT, PHASELEN, INPUT_BLOCK_SIZE, OUTPUT_BLOCK_SIZE, NUM_CHANNELS) \
        ((NUM_CHANNELS) * (DSPC_ASRC_STATE_LEN(INPUT_BLOCK_SIZE, OUTPUT_BLOCK_SIZE, SR_IN, PHASELEN) + \
        DSPC_ASRC_GUARD_LEN(SR_IN, SR_OUT, PHASELEN, OUTPUT_BLOCK_SIZE))) 
		
/** Calculate size of accumBuffer based on the number of channels. Returned value is in number of samples of Q31 or Q15 data */        
#define DSPC_ASRC_ACCUM_LEN(NUMCHANNELS) (NUMCHANNELS * 8)		

/** @}*/

#endif        /* !defined _DSPC_ASRC_H_ */
