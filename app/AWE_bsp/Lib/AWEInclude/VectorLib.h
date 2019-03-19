/* ----------------------------------------------------------------------
*
*               Audio Framework
*               ---------------
*
****************************************************************************
*     VectorLib.h
****************************************************************************
*
*     Description:  Vector main header.
*
*     Copyright:    DSP Concepts, Inc., 2007 - 2015
*                   1800 Wyatt Drive, Suite 14
*                   Sunnyvale, CA 95054
*
***************************************************************************/

/**
   \mainpage Audio Weaver Vector Functions Library
   *
   * Introduction
   * ------------
   *
   * This user manual describes the Audio Weaver Vector functions Library,
   * a suite of common signal processing functions for use on any processor based device.
   *
   * The library has separate functions for operating on 32-bit integer and 32-bit floating-point values.
   *
   * The library functions are declared in the public file <code>VectorLib.h</code> which is placed in the <code>Include</code> folder.
   * Simply include this file and link the appropriate library in the application and begin calling the library functions.
   *
   * Examples
   * --------
   *
   * The library ships with a number of examples which demonstrate how to use the library functions.
   *
   */


/**
 * @defgroup VectorFunctions Audio Weaver Vector Functions
 */

 
 
/**
 * @addtogroup VectorFunctions
 * @{
 */

/**
 * @file
 * @brief Vector main header
 */

#ifndef _GENERIC_VECTOR_H
#define _GENERIC_VECTOR_H

/* Include the math library so that the built-in intrinsic functions on the
   SHARC expand to the correct instruction */
#ifndef IA610
#include <math.h>
#endif

#if (defined(DSPC_CORTEX_M) || defined(DSPC_CORTEX_R))
#undef PI
#include "arm_math.h"
#endif

//#if (defined(OPT_HIFI2))
//#include "pp_config.h"
//#endif

#include "Framework.h"
#include "MathHelper.h"
#include "FractMath.h"
#include "TargetProcessor.h"

/* ----------------------------------------------------------------------------
 *   Function Prototypes
 * ------------------------------------------------------------------------- */

/* Enter C naming convention. */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief awe_vecDb20_Approx  function
 * @param[in] src		 	  array of input data,
 * @param[out] dst            array of output data,
 * @param[in] blockSize		  blockSize,
 */

void awe_vecDb20_Approx(
                 FLOAT32 				*   src,
                FLOAT32                   *   dst,
				int							blockSize);
	
/**
 * @brief awe_vecUnDb20_Approx  function
 * @param[in] src		 	  array of input data,
 * @param[out] dst            array of output data,
 * @param[in] blockSize		  blockSize,
 */

void awe_vecUnDb20_Approx(
                 FLOAT32 				*   src,
                FLOAT32                   *   dst,
				int							blockSize);

/**
 * @brief awe_vecDb20_Approx  function
 * @param[in] src		 	  array of input data,
 * @param[out] dst            array of output data,
 * @param[in] blockSize		  blockSize,
 */

void awe_vecDb20(
                 FLOAT32 				*   src,
                FLOAT32                   *   dst,
				int							blockSize);

/**
 * @brief awe_vecUnDb20_Approx  function
 * @param[in] src		 	  array of input data,
 * @param[out] dst            array of output data,
 * @param[in] blockSize		  blockSize,
 */

void awe_vecUnDb20(
                 FLOAT32 				*   src,
                FLOAT32                   *   dst,
				int							blockSize);
									


/**
 * @brief FIRDecimator  function
 * @param[in] inputpointer	 	  array of input data contained number of channels
 * @param[in] n                   Number of input channels.
 * @param[out] output pointer	  Array of output data
 * @param[in] Coeffs			  Array of Coefficients.
 * @param[in] stateLen			  State Buffer Length.	
 * @param[in] statePtr		 	  State Base Pointer.
 * @param[in/out] stateIndexPtr	  State Index pointer.
 * @param[in] loopsperblock		  blockSize.
 * @param[in] interpolatorFactor  interpolatorFactor.
 * @param[in] polyphaseLen	  	  polyphaseLen.
 */
 void awe_vecFIR_Interpolate(FLOAT32 *  inPtr,			// pointer to input buffer
 							int					 numInChannels,		// number of input channels
 							FLOAT32 *  outPtr,			// pointer to output buffer
 							FLOAT32 * VEC_RESTRICT coeffs,			// pointer to coefficients buffer
 							int					 stateLen,			// state length ( state size)
 							FLOAT32 * VEC_RESTRICT statePtr,			// pointer state buffer
 							int				   * stateIndexPtr,		// pointer to state Index
 							int				     blockSize,			// number of loops for FIR Decimator for channel
 							int 				 interpolatorFactor,// interpolator factor
 							int 				 polyphaseLen);		// polyphase length
 							


/**
 * @brief FIRDecimator  function
 * @param[in] inputpointer	 	  array of input data contained number of channels
 * @param[in] n                   Number of input channels.
 * @param[out] Realdata			  Array of output data
 * @param[in] n				      Number of input channels.
 * @param[in] Coeffs			  Array of Coefficients.
 * @param[in] statePtr		 	  State Base Pointer.
 * @param[in/out] stateIndexPtr	  State Index pointer.
 * @param[in] loopsperblock		  blockSize/decimationFactor.
 * @param[in] numTaps			  numTaps(length of coefficents buffer).
 * @param[in] stateLen			  State Buffer Length.	
 * @param[in] decimationFactor	  FIR decimation factor.
 */
void awe_vecFIR_Decimate( FLOAT32 *  inPtr,		// pointer to input buffer
							int					 numInChannels,	// number of input channels
							FLOAT32 *  outPtr,		// pointer to output buffer
							int					 numOutChannels,// number of output channels
							const FLOAT32 * VEC_RESTRICT coeffs,	// pointer to coefficients buffer
							FLOAT32 * VEC_RESTRICT statePtr,		// pointer state buffer
							int				   * stateIndexPtr,	// pointer to state Index
							int				     loops,			// number of loops for FIR Decimator for channel
							int				     numTaps,		// filter size
							int					 stateLen,		// state length ( state size)
							int					 decimationFactor);// decimation factor

/** 
 * @brief FIR Sparse filter
 * @param[in] tapDelay              Points to the array of current delay per tap
 * @param[out] dst                  Points to the destination location
 * @param[in] coeffPtr              Points to the coefficient applied to each tap output
 * @param[in] numTaps               Number of coefficients
 * @param[in] blockSize             Number of samples to process
 * @param[in] readIndex0			Points to current read point in state array
 * @param[in] stateLen				State array length
 * @param[in] state					Points to state variables
 */
void awe_vecFIRSparseReader( INT32   *					  tapDelay,
							 FLOAT32 *					  dst,
							 const FLOAT32 * VEC_RESTRICT coeffPtr,
							 INT32						  numTaps,
							 INT32                        blockSize,
							 INT32                        readIndex0,
							 INT32						  stateLen,
							 FLOAT32 * VEC_RESTRICT       state);

/** 
 * @brief FIR Sparse filter
 * @param[in] tapDelay              Points to the array of current delay per tap
 * @param[out] dst                  Points to the destination location
 * @param[in] coeffPtr              Points to the coefficient applied to each tap output
 * @param[in] numTaps               Number of coefficients
 * @param[in] blockSize             Number of samples to process
 * @param[in] readIndex0			Points to current read point in state array
 * @param[in] stateLen				State array length
 * @param[in] state					Points to state variables
 * @param[in] postShift	  			Number of bits to shift.
 */

void awe_vecFIRSparseReaderFract32( INT32   *					  tapDelay,
									fract32 *					  dst,
									const fract32 * VEC_RESTRICT coeffPtr,
									INT32						  numTaps,
									INT32                        blockSize,
									INT32                        readIndex0,
									INT32						  stateLen,
									fract32 * VEC_RESTRICT       state,
									INT32                        postShift);


/** 
 * @brief FIR Sparse filter
 * @param[in] tapDelay              Points to the array of current delay per tap
 * @param[out] dst                  Points to the destination location
 * @param[in] coeffPtr              Points to the coefficient applied to each tap output
 * @param[in] numTaps               Number of coefficients
 * @param[in] blockSize             Number of samples to process
 * @param[in] readIndex0			Points to current read point in state array
 * @param[in] stateLen				State array length
 * @param[in] state					Points to state variables
 * @param[in] postShift	  			Number of bits to shift.
 */

void awe_vecFIRSparseReaderFract16( INT32   *					  tapDelay,
									fract32 *					  dst,
									const fract16 * VEC_RESTRICT coeffPtr,
									INT32						  numTaps,
									INT32                        blockSize,
									INT32                        readIndex0,
									INT32						  stateLen,
									fract16 * VEC_RESTRICT       state,
									INT32                        postShift);

/**
 * @brief WithinRange  function
 * @param[in] inputpointer	 	  array of input data contained number of channels
 * @param[out] output pointer	  Array of output data
 * @param[in]  lower              Lower edge of the allowable range.
 * @param[in]  upper              Upper edge of the allowable range.
 * @param[in]  outputValue        Specifies the behavior of the output pin.
 * @param[in]  withinRange        Equals 1 if all input samples in the block are within range.  Otherwise equals 0.
 * @param[in] numSamples          Number of words to process
 */
void awe_vecWithinRange(  FLOAT32 *  src,                        // src - source pointer
						int			 *  dst,                        // srcInc - source increment
						FLOAT32						 lower,                      // lower - Lower edge
						FLOAT32						 upper,                      // upper - Upper edge
						int						     outputValue,                // outputValue - Specifies the behavior of the output pin
						int						   * withinRange,                // withinRange - Holds the instantaneous output value
						int							 numSamples);                // numSamples - Number of words to process


/**
 * @brief FIRInterpolator  function
 * @param[in] inputpointer	 	  array of input data contained number of channels
 * @param[in] n                   Number of input channels.
 * @param[out] output pointer	  Array of output data
 * @param[in] n				      Number of output channels.
 * @param[in] Coeffs			  Array of Coefficients.
 * @param[in] statePtr		 	  State Base Pointer.
 * @param[in/out] stateIndexPtr	  State Index pointer.
 * @param[in] stateLen			  State Buffer Length.	
 * @param[in] loopsperblock		  blockSize.
 * @param[in] interpolatorFactor  interpolatorFactor.
 * @param[in] polyphaseLen	  	  polyphaseLen.
 * @param[in] postShift	  	      Number of bits to shift.
 */
void awe_vecFIR_InterpolateFract32(fract32 *  src,                  // src - source pointer 
							int                          srcInc,                // srcInc - source increment
							fract32 *        dst,                   // dst - destination pointer
							int                          dstInc,                 // dstInc - destination increment
							fract32 * VEC_RESTRICT       coeffsFract32,          // coeffsFract32 - coefficient pointer 
							fract32 * VEC_RESTRICT       statePtr,                // statePtr - state pointer
							int                        * stateIndexPtr,           // stateIndexPtr - state Index pointer
							int 						 stateLen,               // stateLen - length of state buffer
							int                          inBlockSize,            // inBlockSize - number of input samples 
							int                          interPolateFactor,      //interPolateFactor - interPolate factor
							int 						 polyPhaseLen,            //polyPhaseLen - polyphase length
							int                          postShift);              //postShift - Number of bits to shift  


/**
 * @brief FIRDecimator  function
 * @param[in] inputpointer	 	  array of input data contained number of channels
 * @param[in] n                   Number of input channels.
 * @param[out] output pointer	  Array of output data
 * @param[in] n				      Number of output channels.
 * @param[in] Coeffs			  Array of Coefficients.
 * @param[in] statePtr		 	  State Base Pointer.
 * @param[in/out] stateIndexPtr	  State Index pointer.
 * @param[in] loopsperblock		  blockSize.
 * @param[in] numTaps			  numTaps(length of coefficents buffer).
 * @param[in] stateLen			  State Buffer Length.	
 * @param[in] decimationFactor	  FIR decimation factor.
 * @param[in] postShift	  	      Number of bits to shift.
 */

void awe_vecFIR_DecimateFract32( fract32 *  src,	                          // src - source pointer 
								int                          srcInc,					        // srcInc - source increment
								fract32 *        dst,					        // dst - destination pointer
								int                          dstInc,					        // dstInc - destination increment
								const fract32 * VEC_RESTRICT coeffs,					    // coeffs - coefficient pointer
								fract32 * VEC_RESTRICT       statePtr,				        // statePtr - state pointer
								int                        * stateIndexPtr,			        // stateIndexPtr - state Index pointer
								int                          outBlockSize,				        // outBlockSize - number of output samples to get
								int                          numTaps,				        // numTaps - coefficeint buffer size
								int 						  stateLen,				        // stateLen - length of state buffer
								int 						  decimationFactor,               // decimationFactor - decimation factor
								int                          postShift);                     //postShift - Number of bits to shift



/**
 * @brief LMSNorm  function
 * @param[in] inputpointer	 	  array of input data contained number of channels
 * @param[in] inputpointer	 	  array of reference data contained number of channels
 * @param[out] output pointer	  Array of output data
 * @param[out] output pointer	  Array of error data
 * @param[in] state			 	  State Base Pointer.
 * @param[in] Coeffs			  Array of Coefficients.
 * @param[in] inputpointer	 	  Energy of the input
 * @param[in/out] prev_sample     Previous input sample. 
 * @param[in] loopsperblock		  blockSize.
 * @param[in] n                   Number of input channels.
 * @param[in] numTaps			  numTaps(length of coefficents buffer).
 * @param[in] mu                  stepsize
 * @param[in] postShift	  	      Number of bits to shift.
 */

void awe_vecLMSNormFract32( fract32 *   src,								//src - source pointer 
						    fract32 *   ref,								//ref - reference data pointer
						   fract32 * 		 out,								//out - output pointer
						   fract32 * VEC_RESTRICT		 err,								//err - error pointer
						   fract32 * VEC_RESTRICT	     state,								//state - state pointer
						   fract32 * VEC_RESTRICT		 coeffs,							//coeffs - coefficient pointer
						   fract32						*E,									//E - energy
						   fract32						*prev_sample,						//prev_sample - previous input sample
					       int							 blockSize,							//blockSize - blocksize
						   int							 inc,								//inc - increment
					       int							 numTaps,							//numTaps - length of coefficents buffer
						   fract32						 mu,								//mu - stepsize
						   int							 postShift);						//postShift - Number of bits to shift


/**
 * @brief AGC Core  function
 * @param[out] output pointer				Array of output data.
 * @param[in] level_instantaneous			Instantaneous energy of the input samples.
 * @param[in] level_smoothed				smoothed energy of the input samples.
 * @param[in] activationThresholdFract32	Activation threshold of the AGC.
 * @param[in] targetLevelFract32			Target audio level.
 * @param[in] oneOverSlopeFract32			Used by the processing function to compute the amount of cut/boost.
 * @param[in] maxGainFract32				Maximum gain of the AGC.
 * @param[in] maxAttenuationFract32			Maximum attenuation of the AGC.
 * @param[in] targetGainFract32				Target gain of the smoothing operation.
 * @param[in] recoveryRateDownFract32		Recovery rate coefficient when decreasing the gain.
 * @param[in] recoveryRateUpFract32			Recovery rate coefficient when increasing the gain.
 * @param[in/out] currentGainFract32		Instantaneous gain of the smoothing operation.
 * @param[in] smoothingCoeffSampleFract32	Sample-by-sample smoothing coefficient.
 * @param[in] loopsperblock					blockSize.
 */
void awe_vecAGCCoreFract32( fract32 * 	out,									//out - output pointer
							fract32					level_instantaneous,					//level_instantaneous - instantaneous energy
							fract32					level_smoothed,							//level_smoothed - smoothed energy
							fract32					activationThresholdFract32,				//activationThresholdFract32 - activation threshold of the AGC 
							fract32					targetLevelFract32,						//targetLevelFract32 - Target audio level
							fract32					oneOverSlopeFract32,					//oneOverSlopeFract32 - used to compute the amount of cut/boost
							fract32					maxGainFract32,							//maxGainFract32 - maximum gain of the AGC
							fract32					maxAttenuationFract32,					//maxAttenuationFract32 - maximum attenuation of the AGC
							fract32					targetGainFract32,						//targetGainFract32 - target gain of the smoothing operation
							fract32					recoveryRateDownFract32,				//recoveryRateDownFract32 - recovery rate coefficient when decreasing the gain
							fract32					recoveryRateUpFract32,					//recoveryRateUpFract32 - recovery rate coefficient when increasing the gain
							fract32				  * currentGainFract32,						//currentGainFract32 - instantaneous gain of the smoothing operation
							fract32					smoothingCoeffSampleFract32,			//smoothingCoeffSampleFract32 - Sample-by-sample smoothing coefficient
							unsigned int			blockSize);								//blockSize - blocksize


/**
 * @brief WithinRange  function
 * @param[in] inputpointer	 	  array of input data contained number of channels
 * @param[out] output pointer	  Array of output data
 * @param[in]  lower              Lower edge of the allowable range.
 * @param[in]  upper              Upper edge of the allowable range.
 * @param[in]  outputValue        Specifies the behavior of the output pin.
 * @param[in]  withinRange        Equals 1 if all input samples in the block are within range.  Otherwise equals 0.
 * @param[in] numSamples          Number of words to process
 */
void awe_vecWithinRangeFract32(  fract32 *  src,                        // src - source pointer 
								int       *  dst,                        // srcInc - source increment
								fract32						 lower,                      // lower - Lower edge 
								fract32						 upper,                      // upper - Upper edge 
								int						     outputValue,                // outputValue - Specifies the behavior of the output pin
								int						   * withinRange,                // withinRange - Holds the instantaneous output value
								int							 numSamples);                // numSamples - Number of words to process

/**
 * @brief ZeroCrossingDetector  function
 * @param[in] inputpointer	 	  array of input data contained number of channels
 * @param[in] n                   Number of input channels.
 * @param[out] output pointer	  Array of output data
 * @param[in] n				      Number of output channels.
 * @param[in] detectorType        Determines which zero crossings are detected.
 * @param[in/out] lastSign        Holds the sign of the last input value in each channel.
 * @param[in] loopsperblock		  blockSize.
 */
void awe_vecZeroCrossingDetectorFract32( fract32		*  src,             // src - source pointer 
										int								   srcInc,          // srcInc - source increment
										fract32				*  dst,             // dst - destination pointer
										int					               dstInc,          // dstInc - destination increment
										int					               detectorType,    // detectorType -detector type
										int					             * lastSign,        // lastSign - Holds the sign of the last input value
										unsigned int                       blockSize);      // blockSize - number of input samples			

/**
 * @brief Complex FFT .  Forward after modulation and inverse before demodulation.
 * @param[inout] data               Array of complex interleaved values
 * @param[in] n                     Number of samples.  Must be a power of 2.
 * @param[in] isInterleaveZero		Interleave sample is zero or nor if 1 interleave is zero.
 * @param[in] dir                   Transform direction.  =1 for forward.  =-1 for inverse.
 */
void awe_vecCfftMod(
			FLOAT32 	* VEC_RESTRICT     src, 
			int							 n,
			int						 	 isInterleaveZero,
			int						  	 dir,
			FLOAT32 * VEC_RESTRICT modulationTab);

/**
 * @brief Fills a buffer with a specified value and increment.
 * @param[out] ptr                  Pointer to the start of the buffer
 * @param[in] inc                   Pointer increment
 * @param[in] value                 Value to fill
 * @param[in] blockSize             Number of words to fill.
 */
void awe_vecFill(
        FLOAT32 *  ptr,
        int        inc,
        FLOAT32    value,
        int        blockSize);


#ifndef CHIP_6713		
/** 
 * @brief FIR filter
 * @param[in] src                   Points to the source location
 * @param[out] dst                  Points to the destination location
 * @param[in] numChannels           Number of channels = increment between src,dst, and state samples
 * @param[in] coeffs                Points to FIR filter taps stored in normal order
 * @param[in/out] state             Points to state variables.  These are modified upon exit
 * @param[in/out] stateIndex        Points to starting point in state array.  This is modified on exit
 * @param[in] blockSize             Number of samples to process
 * @param[in] numTaps               Number of FIR filter coefficients
 */
void awe_vecFIR( FLOAT32 *  src,
	     int                        srcInc, 
	     FLOAT32 *        dst,
	     int                        dstInc, 
	     const FLOAT32 * VEC_RESTRICT coeffs,
	     FLOAT32 * VEC_RESTRICT       state,
	     int                        blockSize,
	     int                        numTaps,
		 int                      * stateIndex);
#else
/** 
 * @brief FIR filter
 * @param[in] src                   Points to the source location
 * @param[out] dst                  Points to the destination location
 * @param[in] numChannels           Number of channels = increment between src,dst, and state samples
 * @param[in] coeffs                Points to FIR filter taps stored in normal order
 * @param[in/out] state             Points to state variables.  These are modified upon exit
 * @param[in/out] tempdst           Points to starting point in temp destination array.  This is modified on exit
 * @param[in] blockSize             Number of samples to process
 * @param[in] numTaps               Number of FIR filter coefficients
 */
void awe_vecFIR( FLOAT32 *  src,
	     int                        srcInc, 
	     FLOAT32 *        dst,
	     int                        dstInc, 
	     const FLOAT32 * VEC_RESTRICT coeffs,
	     FLOAT32 * VEC_RESTRICT       state,
	     int                        blockSize,
	     int                        numTaps,
		 FLOAT32 * VEC_RESTRICT       tempdst);
#endif
	     
/** 
 * @brief FIR LMS filter

 * @param[in] in                    Points to the source location of desired filter output
 * @param[in] ref                   Points to the source location of reference data, (filter input)
 * @param[out] out                  Points to the destination location for filter output data
 * @param[out] err                  Points to the destination location for error data
 * @param[in/out] coeffs            Points to FIR filter taps stored in normal order
 * @param[in/out] state             Points to state variables.  These are modified upon exit
 * @param[in/out] stateIndex        Points to starting point in state array.  This is modified on exit
 * @param[in] blockSize             Number of samples to process
 * @param[in] numTaps               Number of FIR filter coefficients
 * @param[in] mu                    LMS step size parameter
 */
void awe_vecLMS( FLOAT32 *  in,
         FLOAT32 *  ref,
	     FLOAT32 *  out,
         FLOAT32 * VEC_RESTRICT       err,
	     FLOAT32 * VEC_RESTRICT       coeffs,
	     FLOAT32 * VEC_RESTRICT       state,
	     int                      * stateIndex,
	     int                        blockSize,
	     int                        numTaps,
         FLOAT32                      mu);


/** 
 * @brief Normalized LMS filter
 * @param[in] in                    Points to the source location of filter input data
 * @param[in] ref                   Points to the source location of reference data, (desired filter ouput)
 * @param[out] out                  Points to the destination location for filter output data
 * @param[out] err                  Points to the destination location for error data
 * @param[in/out] coeffs            Points to FIR filter taps stored in normal order
 * @param[in/out] state             Points to state variables.  These are modified upon exit
 * @param[in/out] stateIndex        Points to starting point in state array.  This is modified on exit
 * @param[in] blockSize             Number of samples to process
 * @param[in] numTaps               Number of FIR filter coefficients
 * @param[in] mu                    LMS step size parameter
 * @param[in] gamma                 Minimum denominator for coefficient update calculation
 * @param[in/out] xNorm             Running norm of input data.  This is modified on exit
 */
void awe_vecLMSNorm( FLOAT32 *  in,
          FLOAT32 *  ref,
	     FLOAT32 *        out,
         FLOAT32 * VEC_RESTRICT       err,
	     FLOAT32 * VEC_RESTRICT       coeffs,
	     FLOAT32 * VEC_RESTRICT       state,
	     int                      * stateIndex,
	     int                        blockSize,
	     int                        numTaps,
         FLOAT32                      mu,
         FLOAT32                      gamma,
         FLOAT32                    * xNorm);





/**
 * @brief Multiplies two buffers sample by sample
 * @param[in] inA                   Pointer to the first input buffer
 * @param[in] incA                  Increment between samples in inA
 * @param[in] inB                   Pointer to the second input buffer
 * @param[in] incB                  Increment between samples in inB
 * @param[out] out                  Pointer to the output buffer @param[in]
 * @param[in] incC                  Increment between samples in out
 * @param[in] blockSize             Number of words to process
 */

void awe_vecMultiply2x1(
		      FLOAT32 *  inA,
		     int                        incA,
		      FLOAT32 *  inB,
		     int                        incB,
		     FLOAT32 *        out,
		     int                        incC,
		     int                        blockSize);
		     
/**
 * @brief Multiplies two buffers and accumulates a buffer sample by sample
 * @param[in] inA                   Pointer to the first input buffer
 * @param[in] incA                  Increment between samples in inA
 * @param[in] inB                   Pointer to the second input buffer
 * @param[in] incB                  Increment between samples in inB
 * @param[in] pAdd                  Pointer to the addition buffer
 * @param[in] incAdd                Increment between samples in pAdd
 * @param[out] pDst                 Pointer to the output buffer
 * @param[in] incDst                Increment between samples in pDst
 * @param[in] blockSize             Number of words to process
 */
void awe_vecMultiplyAdd(
                              const FLOAT32 *              inA,
                              int                        incA,
		              const FLOAT32 *              inB,
                              int                        incB,
                              FLOAT32 *                    pAdd,
                              int                        incAdd,
		              FLOAT32 *                    pDst,
                              int                        incDst,
		              int                        blockSize);


/** 
 * @brief Adds two buffers sample by sample
 * @param[in] inA                   Pointer to the first input buffer
 * @param[in] inB                   Pointer to the second input buffer
 * @param[out] out                  Pointer to the output buffer @param[in]
 * @param[in] blockSize             Number of words to process
 */
void awe_vecAdd2x1(
        FLOAT32 *  inA,
        int        incA,
        FLOAT32 *  inB,
        int        incB,
        FLOAT32 *  out,
        int        incC,
        int        blockSize);



/**
 * @brief Subtracts two buffers sample by sample
 * @param[in] inA                   Pointer to the first input buffer
 * @param[in] incA                  Stride for the first input
 * @param[in] inB                   Pointer to the second input buffer
 * @param[in] incB                  Stride for the second input
 * @param[out] out                  Pointer to the output buffer
 * @param[in] incC                  Stride for the output buffer
 * @param[in] blockSize             Number of words to process
 */
void awe_vecSubtract2x1(
        FLOAT32 *   inA,
        int       incA, 
        FLOAT32 *   inB,
        int       incB, 
        FLOAT32 *   out,
        int       incC, 
        int       blockSize);

        
/**
 * @brief Divides two buffers sample by sample
 * @param[in] inA                   Pointer to the first input buffer
 * @param[in] inB                   Pointer to the second input buffer
 * @param[out] out                  Pointer to the output buffer @param[in]
 * @param[in] blockSize             Number of words to process
 */
void awe_vecDivide2x1(
        FLOAT32 *  inA,
        FLOAT32 *  inB,
        FLOAT32       *  out,
        int                        blockSize);


/** 
 * @brief Copies a buffer of samples with increments on the source and
 * destination pointers.  Operates on integer data.
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment for the source pointer
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment for the destination pointer
 * @param[in] blockSize             Number of words to copy
 */

void awe_vecCopy32(INT32 *  src, 
		   int srcInc, 
		   INT32 *  dst, 
		   int dstInc, 
		   int blockSize);



/** 
 * @brief Copies a buffer of samples with increments on the source and
 * destination pointers.
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment for the source pointer
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment for the destination pointer
 * @param[in] blockSize             Number of words to copy
 */


 static VEC_INLINE void awe_vecCopy(FLOAT32 *  src,
				 int srcInc, 
				 FLOAT32 *  dst,
				 int dstInc, 
				 int blockSize)
{
  awe_vecCopy32( (int *) src, srcInc, (int *) dst, dstInc, blockSize);
}

/** 
 * @brief Copies and scales an int buffer by an int
 * @param[in] src                   Points to the source location
 * @param[in] srcStride             Source sample pitch
 * @param[out] dst                  Points to the destination location
 * @param[in] dstStrid              Destination sample pitch
 * @param[in] K                     Scale factor
 * @param[in] numSamples            Number of words to process
 */
void awe_vecIntegerScale(
        int   *  src, 
        int                        srcStride, 
        int         *  dst, 
        int                        dstStride, 
        int                        K, 
        int                        numSamples);

/** 
 * @brief Sample and Holds the input signal based on trigger signal
 * @param[in] src                   Points to the source location
 * @param[in] srcStride             Source sample pitch
 * @param[out] dst                  Points to the destination location
 * @param[in] dstStrid              Destination sample pitch
 * @param[in] trigger               Points to the trigger location
 * @param[in] triggerStide          Trigger sample pitch
 * @param[in] value                 Points to the last data value which was sampled
 * @param[in] blockSize             Number of words to process
 */
void awe_vecSampleAndHold(
 FLOAT32 *  	src,
        int                  	srcStride, 
        FLOAT32 *  	dst,
        int                  	dstStride, 
		int *  	trigger, 
        int                  	triggerStide, 
		FLOAT32 *               value,
        int                  	blockSize);

/** 
 * @brief Copies and scales a buffer
 * @param[in] src                   Points to the source location
 * @param[in] srcStride             Source sample pitch
 * @param[out] dst                  Points to the destination location
 * @param[in] dstStrid              Destination sample pitch
 * @param[in] K                     Scale factor
 * @param[in] numSamples            Number of words to process
 */
void awe_vecScale(
        FLOAT32 *  src,
        int                        srcStride, 
        FLOAT32       *  dst,
        int                        dstStride, 
        FLOAT32                      K,
        int                        numSamples);


/** 
 * @brief Computes scaled sum and difference of 2  inputs
 * @param[in] src1                   Points to 1st input buffer
 * @param[in] src2                   Points to 2nd input buffer
 * @param[out] dst1                  Points to 1st output buffer
 * @param[out] dst2                  Points to 2nd output buffer
 * @param[in] scaleFactor           Scale factor
 * @param[in] blockSize             Number of words to process
 */
void awe_vecScaleSumDiff(
      FLOAT32 * VEC_RESTRICT src1,
		FLOAT32 *  src2,
		FLOAT32       * VEC_RESTRICT dst1,
		FLOAT32       *  dst2,
		int         blockSize);


/** 
 * @brief Scale and sum two buffers
 * @param[in] srcA                  Points to the first source buffer
 * @param[in] scaleA                Scale factor for the first buffer
 * @param[in] srcB                  Points to the second source buffer
 * @param[in] scaleB                Scale factor for the second buffer
 * @param[out] dst                  Destination buffer.
 * @param[in] blockSize             Number of words to process
 */
void awe_vecScale2x1(
        FLOAT32 *  srcA,
        FLOAT32                      scaleA,
        FLOAT32 *  srcB,
        FLOAT32                      scaleB,
        FLOAT32       *  dst,
        int                        blockSize);

                
/**
 * @brief Scales a buffer and adds the result to another buffer
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source values
 * @param[out] dst                  Points to the destination accumulation buffer
 * @param[in] dstInc                Increment between destination values
 * @param[in] K                     Scale factor for the src buffer
 * @param[in] blockSize             Number of words to process
 */
void awe_vecScaleAdd(
        FLOAT32 *  src,
        int                        srcInc, 
        FLOAT32       *  dst,
        int                        dstInc, 
        FLOAT32                      K,
        int                        blockSize);
		
/**
 * @brief Scales a buffer and adds the result to another buffer
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source values
 * @param[out] dst                  Points to the destination accumulation buffer
 * @param[in] dstInc                Increment between destination values
 * @param[in] gain1                 Scale factor for the src buffer for dst[i]
 * @param[in] gain2                 Scale factor for the src buffer for dst[i+1]
 * @param[in] blockSize             Number of words to process
 */     
void awe_vecMixerSmoothedV2b(
        const FLOAT32 * src,
        int                     srcInc, 
        FLOAT32       * dst,
        int                     dstInc, 
        const FLOAT32 			gain1,
        const FLOAT32 			gain2,
        int                     blockSize);

        
/**
 * @brief Smoothly scales a buffer
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source values
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination values
 * @param[in] currentAmp            Starting amplitude for the smoothing operation.
 *                                  This is returned updated at the end of the call.
 * @param[in,out] targetAmp         Final amplitude which the smoothing operation
 *                                  approaches
 * @param[in] smoothingCoeff        Coefficient which controls the rate of the smoothing
 *                                  operation.
 * @param[in] blockSize             Number of words to process
 */
void awe_vecScaleSmooth(
        FLOAT32 *  src,
        int                        srcInc, 
        FLOAT32       *  dst,
        int                        dstInc, 
        FLOAT32       *  currentAmp,
        FLOAT32                      targetAmp,
        FLOAT32                      smoothingCoeff,
        int                        blockSize);

        
/**
 * @brief Smoothly scales a buffer and adds it to another buffer
 * @param[in] src                   Points to the source location
 * @param[out] dst                  Points to the destination (accumulation) location
 * @param[in,out] *currentAmp       Starting amplitude for the smoothing
 *                                  operation. This is returned updated at the 
 *                                  end of the call.
 * @param[in] targetAmp             Final amplitude which the smoothing operation
 *                                  approaches
 * @param[in] smoothingCoeff        Coefficient which controls the rate of the smoothing
 *                                  operation.
 * @param[in] blockSize             Number of words to process
 */
void awe_vecScaleAddSmooth(
        FLOAT32 *  src,
        int                        srcInc, 
        FLOAT32       *  dst,
        int                        dstInc, 
        FLOAT32       *  currentAmp,
        FLOAT32                      targetAmp,
        FLOAT32                      smoothingCoeff,
        int                        blockSize);
                      
/**
 * @brief Smoothly scales a buffer and adds it to another buffer.  N channel.
 * @param[in] src                   Points to the source location
 * @param[out] dst                  Points to the destination (accumulation) location
 * @param[in] numChannels           Number of interleaved channels in src and dst
 * @param[in,out] *currentAmp       Starting amplitude for the smoothing
 *                                  operation. This is returned updated at the 
 *                                  end of the call.
 * @param[in] targetAmp             Final amplitude which the smoothing operation
 *                                  approaches
 * @param[in] smoothingCoeff        Coefficient which controls the rate of the smoothing
 *                                  operation.
 * @param[in] blockSize             Number of words to process
 */

void awe_vecScaleAddSmooth_Nch(
        FLOAT32 *  src,
        FLOAT32       *  dst,
        int         numChannels,
        FLOAT32       *  currentAmp,
        FLOAT32                      targetAmp,
        FLOAT32                      smoothingCoeff,
        int                        blockSize);

/** 
 * @brief Scale a signal, applying gains from a buffer to subblocks of size
 *        numSamples / numGains.  numGains must evenly divide numSamples
 * @param[in] src           Points to the source location
 * @param[in] srcInc        Increment between interleaved source values
 * @param[out] dst          Points to the destination location
 * @param[in] dstInc        Increment between interleaved destination values
 * @param[in] gains         Buffer of scale factors
 * @param[in] numGains      Numbers of elements in gains array
 * @param[in] numSamples    Number of words to process
 */
void awe_vecScaleSubblock(
        FLOAT32 *  src,
        int      srcInc,
        FLOAT32 *  dst,
        int      dstInc,
        FLOAT32    *gains,
        int      numGains,
        int      numSamples);

/**
 * @brief Scale a signal, using smoothly varying gains with target values
 *        from a buffer for each subblock of size blockSize / numGains.
 *        numGains must evenly divide blockSize.
 * @param[in] src               Points to the source location
 * @param[in] srcInc            Increment between source values
 * @param[out] dst              Points to the destination location
 * @param[in] dstInc            Increment between destination values
 * @param[in, out] currentAmp   Starting amplitude for the smoothing operation.
 *                              This is updated at the end of the call.
 * @param[in] targetAmps        Array of final amplitudes which the smoothing
 *                              operation approaches for each subblock
 * @param[in] smoothingCoeff    Coefficient which controls the rate of the
 *                              smoothing operation.
 * @param[in] numGains          Number of elems in targetAmps array
 * @param[in] blockSize         Number of words to process
 */
void awe_vecScaleSmoothSubblock(
        FLOAT32  * src,
        int      srcInc,
        FLOAT32  * dst,
        int      dstInc,
        FLOAT32  * currentAmp,
        FLOAT32  * targetAmps,
        FLOAT32    smoothingCoeff,
        int      numGains,
        int      blockSize);

/**
 * @brief Scale a multichannel signal, using smoothly varying gains with
 *        target values from a buffer for each subblock of size
 *        blockSize / numGains.  numGains must evenly divide blockSize.
 * @param[in] src               Points to the source location
 * @param[out] dst              Points to the destination location
 * @param[in] numChannels       Number of channels in input signal
 * @param[in, out] currentAmp   Starting amplitude for the smoothing operation.
 *                              This is updated at the end of the call.
 * @param[in] targetAmps        Array of final amplitudes which the smoothing
 *                              operation approaches for each subblock
 * @param[in] smoothingCoeff    Coefficient which controls the rate of the
 *                              smoothing operation.
 * @param[in] numGains          Number of elems in targetAmps array
 * @param[in] blockSize         Number of words to process
 */
void awe_vecScaleSmoothSubblock_Nch(
        FLOAT32  * src,
        FLOAT32  * dst,
        int      numChannels,
        FLOAT32  * currentAmp,
        FLOAT32  * targetAmps,
        FLOAT32    smoothingCoeff,
        int      numGains,
        int      blockSize);

/** 
 * @brief Interleaves two mono buffers to form a stereo buffer
 * @param[in] monoA                 Points to the first mono buffer
 * @param[in] monoB                 Points to the second mono buffer
 * @param[out] dst                  Points to the stereo destination buffer
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecInterleave(
        const FLOAT32 *  monoA,
        const FLOAT32 *  monoB,
        FLOAT32       * VEC_RESTRICT dst,
        int                        blockSize);

/** 
 * @brief Accumulates all of the values in a buffer
 * @param[in] src                   Points to the buffer of data
 * @param[in] blockSize             Number of samples to process
 * @return                          Sum of values
 */
FLOAT32 awe_vecSum(
        const FLOAT32 *  src,
        int              blockSize);

/** 
 * @brief Determines the maximum value in a buffer
 * @param[in] src                   Points to the buffer of data
 * @param[in] blockSize             Number of samples to process
 * @param[out] *index               Index of the maximum value returned here
 *                                  (always 0)
 * @return                          Maximum value
 */
FLOAT32 awe_vecMax(
        const FLOAT32 * VEC_RESTRICT src,
        int                        blockSize, 
        int         * VEC_RESTRICT index);

/** 
 * @brief Determines the maximum value in a buffer
 * @param[in] src                   Points to the buffer of data
 * @param[in] blockSize             Number of samples to process
 * @param[out] *index               Index of the maximum value returned here
 * @return                          Maximum value
 */
FLOAT32 awe_vecMaxIndex(
        const FLOAT32 * VEC_RESTRICT src,
        int                        blockSize, 
        int         * VEC_RESTRICT index);

/**
 * @brief Determines the maximum absolute value in a buffer
 * @param[in] src                   Points to the buffer of data
 * @param[in] blockSize             Number of samples to process
 * @param[out] *index               Index of the maximum absolute value returned
 * here (unused)
 * @return                          Maximum absolute value
 */
FLOAT32 awe_vecMaxAbs(
        const FLOAT32 * VEC_RESTRICT src,
        int                        srcInc,
        int                        blockSize, 
        int         * VEC_RESTRICT index);
/**
 * @brief Determines the maximum absolute value in a buffer
 * @param[in] src                   Points to the buffer of data
 * @param[in] blockSize             Number of samples to process
 * @param[out] *index               Index of the maximum absolute value returned here 
 * @return                          Maximum absolute value
 */
FLOAT32 awe_vecMaxAbsIndex(
        const FLOAT32 * VEC_RESTRICT src,
        int                        srcInc,
        int                        blockSize, 
        int         * VEC_RESTRICT index);
/**
 * @brief Determines the minimum absolute value in a buffer
 * @param[in] src                   Points to the buffer of data
 * @param[in] blockSize             Number of samples to process
 * @param[out] *index               Index of the minimum absolute value returned here
 * @return                          Minimum absolute value
 */
FLOAT32 awe_vecMinAbs(
        const FLOAT32 * VEC_RESTRICT src,
        int                        srcInc,
        int                        blockSize, 
        int         * VEC_RESTRICT index);

/** 
 * @brief Determines the minimum value in a buffer
 * @param[in] src                   Points to the buffer of data
 * @param[in] blockSize             Number of samples to process
 * @param[out] *index               Index of the minimum value (always 0)
 * @return                          Minimum value
 */
FLOAT32 awe_vecMin(
        const FLOAT32 * VEC_RESTRICT src,
        int                        blockSize, 
        int         * VEC_RESTRICT index);

/** 
 * @brief Determines the minimum value in a buffer
 * @param[in] src                   Points to the buffer of data
 * @param[in] blockSize             Number of samples to process
 * @param[out] *index               Index of the minimum value returned here
 * @return                          Minimum value
 */
FLOAT32 awe_vecMinIndex(
        const FLOAT32 * VEC_RESTRICT src,
        int                        blockSize, 
        int         * VEC_RESTRICT index);

/**
 * @brief Computes the sum of the squares of a buffer
 * @param[in] src                   Points to the buffer of data
 * @param[in] blockSize             Number of samples to process
 * @return                          Sum of the squares
 */
FLOAT32 awe_vecSumSquared(
        const FLOAT32 *  src,
        int                        blockSize);

/**
 * @brief Computes the absolute value of a buffer of FLOAT32 ing-point data
 * @param[in] src                   Points to the source buffer
 * @param[in] srcInc                Source data pitch
 * @param[out] dst                  Points to the destination buffer
 * @param[in] dstInc                Destination data pitch
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecAbs(
        FLOAT32 *  src,
        int                        srcInc, 
        FLOAT32       *  dst,
        int                        dstInc, 
        int                        blockSize);

/**
 * @brief Computes the absolute value of a buffer of FLOAT32 ing-point data
 * @param[in] src                   Points to the source buffer
 * @param[out] dst                  Points to the destination buffer
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecAbs_2ch(
        FLOAT32 *  src,
        FLOAT32       *  dst,
        int                        blockSize);

/**
 * @brief Computes the absolute value of a buffer of integer data.
 * @param[in] src                   Points to the source buffer
 * @param[in] srcInc                Source data pitch
 * @param[out] dst                  Points to the destination buffer
 * @param[in] dstInc                Destination data pitch
 * @param[in] blockSize             Number of samples to process
 */

void awe_vecAbsInt(
        const int * VEC_RESTRICT src, 
        int                      srcInc, 
        int       * VEC_RESTRICT dst, 
        int                      dstInc, 
        int                      blockSize);

/**
 * @brief Converts a buffer of integer data to FLOAT32 
 * @param[in] src                   Points to the source buffer
 * @param[in] srcInc                Source data pitch
 * @param[out] dst                  Points to the destination buffer
 * @param[in] dstInc                Destination data pitch
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecIntToFloat(
        const   int * VEC_RESTRICT src,
        int                        srcInc, 
        FLOAT32       * VEC_RESTRICT dst,
        int                        dstInc, 
        int                        blockSize);

/**
 * @brief Converts a buffer of FLOAT32 data to integer
 * @param[in] src                   Points to the source buffer
 * @param[in] srcInc                Source data pitch
 * @param[out] dst                  Points to the destination buffer
 * @param[in] dstInc                Destination data pitch
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecFloatToInt(
        const FLOAT32 * VEC_RESTRICT src,
        int                        srcInc, 
        int         * VEC_RESTRICT dst, 
        int                        dstInc, 
        int                        blockSize);





/**
 * @brief Clips a buffer of data to specified lower and upper bounds
 * @param[in] src                   Points to the source buffer
 * @param[out] dst                  Points to the destination buffer
 * @param[in] clipLower             Lower clipping threshold
 * @param[in] clipUpper             Upper clipping threshold
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecClipAsym(
        FLOAT32 *  src,
        FLOAT32       *  dst,
        FLOAT32                      clipLower,
        FLOAT32                      clipUpper,
        int                        blockSize);

/** 
 * @brief Weighed sum of two blocks of data
 * @param[in] src1                  Points to the first source buffer
 * @param[in] src2                  Points to the second source buffer
 * @param[out] dst                  Points to the destination buffer
 * @param[in] scale1                Scale factor applied to the first buffer
 * @param[in] scale2                Scale factor applied to the second buffer
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecWeightedAdd(
        FLOAT32 *  src1,
        FLOAT32 *  src2,
        FLOAT32       *  dst,
        FLOAT32                      scale1,
        FLOAT32                      scale2,
        int                        blockSize);

/**
 * @brief Generates uniformly distributed white noise.
 * @param[out] dst                  Points to the destination buffer
 * @param[in] dstInc                Increment between samples in the destination array
 * @param[in] scale                 Standard deviation of the output
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecWhiteNoise(
        FLOAT32 *  dst,
        int                  dstInc, 
        FLOAT32                scale,
        int                  blockSize);

/**
 * @brief Converts linear values to decibels
 * @param[in] src                   Points to the source buffer
 * @param[out] dst                  Points to the destination buffer
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecLinearToDB(
        FLOAT32 *  src,
        FLOAT32       *  dst,
        int                        blockSize);

/** 
 * @brief Converts linear values to decibels
 * @param[in] src                   Points to the source buffer
 * @param[in] dst                   Points to the destination buffer
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecDBToLinear(
        FLOAT32 *  src,
        FLOAT32       *  dst,
        int                        blockSize);

/** 
 * @brief Converts linear values to decibels in fract32 format
 * @param[in] src                   Points to the source buffer
 * @param[in] dst                   Points to the destination buffer
 * @param[in] blockSize             Number of samples to process
 * src and dst are in 8.24 format.
 */

void awe_vecDBToLinearFract32(
        fract32 *  src, 
        fract32 *  dst, 
        int        blockSize);

/** 
 * @brief Converts DB values to linear in fract32 format
 * @param[in] src                   Points to the source buffer
 * @param[in] dst                   Points to the destination buffer
 * @param[in] blockSize             Number of samples to process
   @param[in]  INFOR      format for the input value ex:1 for 1.31 and 2 for 2.30 etc
   @param[in]  OUTFOR     format for the output value ex:1 for 1.31 and 2 for 2.30 etc
 */
void awe_vecLinearToDBFract32(fract32 *src, 
                         fract32 *dst, 
                         int blockSize,
                         int INFORMAT,
                         int OUTFORMAT);

/** 
 * @brief Outputs square root of input
 * @param[in] src                   Points to the source buffer
 * @param[out] dst                  Points to the destination buffer
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecSqrt(
        FLOAT32 *  src,
        int                        srcInc, 
        FLOAT32       *  dst,
        int                        dstInc, 
        int                        blockSize);
        
/** 
 * @brief Outputs inverse of input
 * @param[in] src                   Points to the source buffer
 * @param[out] dst                  Points to the destination buffer
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecReciprocal(
        FLOAT32       *              src,
        int                        srcInc,
        FLOAT32       *              dst,
        int                        dstInc, 
        int                        blockSize);

/** 
 * @brief Sample-by-sample polynomial
 * @param[in] src                   Points to the source buffer
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination buffer
 * @param[in] dstInc                Increment between output samples
 * @param[in] numCoeffs             Number of coefficients in the polynomial.  Order = numCoeffs - 1.
 * @param[in] coeffs                Pointer to the coefficients: C[0]*X^(N-1) + C[1]*X^(N-2) + ... + C[N-2] * X + C[N-1]
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecPolynomial(
        FLOAT32       *              src,
        int                        srcInc, 
        FLOAT32       *              dst,
        int                        dstInc, 
        int                        numCoeffs, 
        const FLOAT32 * VEC_RESTRICT coeffs,
        int                        blockSize);

/** 
 * @brief Scales and offsets a buffer
 * @param[in] src                   Points to the source location
 * @param[out] dst                  Points to the destination location
 * @param[in] K                     Scale factor
 * @param[in] offset                Offset value
 * @param[in] blockSize             Number of words to process
 * @param[in] stride                Increment between input and output samples
 */
void awe_vecScaleOffset(
        FLOAT32           *          src,
        int                        srcStride,
        FLOAT32           *          dst,
        int                        dstStride,
        FLOAT32                      K,
        FLOAT32                      offset,
        int                        blockSize);
        
/** 
 * @brief Scales by an integer and offsets a buffer
 * @param[in] src                   Points to the source location
 * @param[out] dst                  Points to the destination location
 * @param[in] K                     Scale factor
 * @param[in] offset                Offset value
 * @param[in] blockSize             Number of words to process
 * @param[in] stride                Increment between input and output samples
 */
void awe_vecScaleOffsetInt32(
        int           *          src,
        int                      srcStride,
        int           *          dst,
        int                      dstStride,
        int                      K,
        int                      offset,
        int                      blockSize);
        
/**
 * @brief Scales and offsets a buffer
 * @param[in] pSrcA            Points to the source location
 * @param[out] incA            Space between samples at pSrcA
 * @param[in] scalar           Offset factor
 * @param[in] pDst             Destination buffer
 * @param[in] incC             Space between samples at pDst
 * @param[in] blockSize        Number of samples to process
 */
void awe_vecOffset(
                            const FLOAT32 * VEC_RESTRICT pSrcA,
                            int                        incA,
                            const FLOAT32                scalar,
                            FLOAT32 * VEC_RESTRICT       pDst,
                            int                        incC,
                            int                        blockSize);

/** 
 * @brief Squares a buffer and accumulates the result to another buffer
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] blockSize             Number of words to process
 */
void awe_vecSquareAdd(
		   FLOAT32 *  src,
		   int                        srcInc, 
		   FLOAT32 *        dst,
		   int                        dstInc, 
		   int                        blockSize);

/** 
 * @brief Second order IIR filter
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] coeffs                Points to 5 coefficients arranged as: b0, b1, b2, a1, a2
 * @param[in/out] state             Points to 2 state variables.  These are modified upon exit
 * @param[in] blockSize             Number of words to process
 */
void awe_vecBiquad( FLOAT32 *  src,
		int                        srcInc, 
		FLOAT32 *        dst,
		int                        dstInc, 
		const FLOAT32 * VEC_RESTRICT coeffs,
		FLOAT32 * VEC_RESTRICT       state,
    #ifndef CHIP_6713
        int   blockSize				                
    #else				
        int   blockSize_divby_3, 
        int   blockSize_rem								
	#endif   //#ifndef CHIP_6713
		);

/** 
 * @brief Second order IIR filter using a state space implementation.  Single channel.
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] coeffs                Points to 5 coefficients arranged as: Fb, Gaa, Gab, K, Fa
 * @param[in/out] state             Points to 2 state variables.  These are modified upon exit
 * @param[in] blockSize             Number of words to process
 */
void awe_vecBiquadSS(const FLOAT32 * src,
		int                        srcInc, 
		FLOAT32                    * dst,
		int                        dstInc, 
		const FLOAT32 * VEC_RESTRICT coeffs,
		FLOAT32 * VEC_RESTRICT       state,
        int   blockSize				                
		);

/** 
 * @brief Second order IIR filter using a state space implementation.  Stereo.
 * @param[in] src                   Points to the source location.  Interleaved L/R.
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination
 *                                  location. Interleaved L/R.
 * @param[in] dstInc                Increment between destination samples
 * @param[in] coeffs                Points to 5 coefficients arranged as: Fb, Gaa, Gab, K, Fa
 * @param[in/out] state             Points to 4 state variables.  These are modified upon exit
 * @param[in] blockSize             Number of words to process
 */

void awe_vecBiquadSS_2ch(FLOAT32 * src,
 		     int                        srcInc, 
		     FLOAT32                    * dst,
		     int                        dstInc, 
		     const FLOAT32 * VEC_RESTRICT coeffs,
		     FLOAT32 * VEC_RESTRICT       state,
             int   blockSize				                
    );


void awe_vecBiquad_4ch( FLOAT32 * pSrc,
		int                     srcInc, 
		FLOAT32 *					pDst,
		int                     dstInc, 
		const FLOAT32 *			coeffs,
		FLOAT32 *					state,
		int                     blockSize);

void awe_vecBiquad_2ch( FLOAT32 * pSrc,
		int                     srcInc, 
		FLOAT32 *					pDst,
		int                     dstInc, 
		const FLOAT32 *			coeffs,
		FLOAT32 *					state,
		int                     blockSize);

void awe_vecBiquadCascade_DF1( FLOAT32 *  src,
		int                        srcInc, 
		FLOAT32 *                  dst,
		int                        dstInc, 
		const FLOAT32 * VEC_RESTRICT coeffs,
		FLOAT32 * VEC_RESTRICT       state,
		int						   nStages,
		int                        blockSize);


/** 
 * @brief Second order IIR filter with the Extended Precision version on SHARC processor
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] coeffs                Points to 5 coefficients arranged as: b0, b1, b2, a1, a2
 * @param[in/out] state             Points to 2 state variables.  These are modified upon exit
 * @param[in] blockSize             Number of words to process
 */
void awe_vecBiquad40( FLOAT32 *  src,
		int									srcInc, 
		FLOAT32 * 				dst,
		int									dstInc, 
		const FLOAT32 * VEC_RESTRICT	coeffs,
		FLOAT32 * VEC_RESTRICT			state,
		int									blockSize);

/** 
 * @brief Second order IIR Cascade filter 
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] coeffs                Points to (5*number of stages) coefficients arranged as: b01, b11, b21, a11, a21, b02, b12, b22, a12, a22,.... b0n, b1n, b2n, a1n, a2n 
 * @param[in/out] state             Points to (2*number of stages) state variables.  These are modified upon exit
 * @param[in] nStages           Number of the cascade sections
 * @param[in] blockSize             Number of words to process
 */
void awe_vecBiquadCascade( FLOAT32 *  src,
		int                        srcInc, 
		FLOAT32 *        dst,
		int                        dstInc, 
		const FLOAT32 * VEC_RESTRICT coeffs,
		FLOAT32 * VEC_RESTRICT      state,
		int						   nStages,
		int                        blockSize);
		
/** 
 * @brief Second order IIR Cascade filter with the SIMD version on SHARC processor
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] coeffs                Points to (5*number of stages) coefficients arranged as: b01, b11, b21, a11, a21, b02, b12, b22, a12, a22,.... b0n, b1n, b2n, a1n, a2n 
 * @param[in/out] state             Points to (2*number of stages) state variables.  These are modified upon exit
 * @param[in] nStages           Number of the cascade sections
 * @param[in] blockSize             Number of words to process
 */

void awe_vecBiquadCascade_2ch( FLOAT32 *  src,
		int                        srcInc, 
		FLOAT32 *        dst,
		int                        dstInc, 
		const FLOAT32 * VEC_RESTRICT coeffs,
		FLOAT32 * VEC_RESTRICT      state,
		int						   nStages,
		int                        blockSize);


/** 
 * @brief Second order IIR Cascade filter with State Space implementation
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] coeffs                Points to (5*number of stages) coefficients arranged as: Fb1, Gaa1, Gab1, K1, Fa1, Fb2, Gaa2, Gab2, K2, Fa2,.... Fbn, Gaan, Gabn, Kn, Fan 
 * @param[in/out] state             Points to (2*number of stages) state variables.  These are modified upon exit
 * @param[in] nStages				Number of the cascade sections
 * @param[in] blockSize             Number of words to process
 */
void awe_vecBiquadCascadeSS( FLOAT32 *  src,
		int                        srcInc, 
		FLOAT32 *        dst,
		int                        dstInc, 
		const FLOAT32 * VEC_RESTRICT coeffs,
		FLOAT32 * VEC_RESTRICT      state,
		int						   nStages,
		int                        blockSize);
		
/** 
 * @brief Second order IIR Cascade filter with the SIMD version on SHARC processor
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] coeffs                Points to (5*number of stages) coefficients arranged as: Fb1, Gaa1, Gab1, K1, Fa1, Fb2, Gaa2, Gab2, K2, Fa2,.... Fbn, Gaan, Gabn, Kn, Fan 
 * @param[in/out] state             Points to (2*number of stages) state variables.  These are modified upon exit
 * @param[in] nStages				Number of the cascade sections
 * @param[in] blockSize             Number of words to process
 */

void awe_vecBiquadCascadeSS_2ch( FLOAT32 *  src,
		int                        srcInc, 
		FLOAT32 *        dst,
		int                        dstInc, 
		const FLOAT32 * VEC_RESTRICT coeffs,
		FLOAT32 * VEC_RESTRICT      state,
		int						   nStages,
		int                        blockSize);

/** 
 * @brief Second order IIR Cascade filter with the NEON SIMD for ARM Cortex-A
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] coeffs                Points to (5*number of stages) coefficients arranged as: b01, b11, b21, a11, a21, b02, b12, b22, a12, a22,.... b0n, b1n, b2n, a1n, a2n 
 * @param[in/out] state             Points to (2*number of stages) state variables.  These are modified upon exit
 * @param[in] blockSize             Number of words to process
 */
		
void awe_vecBiquadCascadeDelay(FLOAT32 * src,
                              int srcInc,
                              FLOAT32 * dst,
                              int dstInc,
                              const FLOAT32 * VEC_RESTRICT coeffs,
                              FLOAT32 * VEC_RESTRICT state,
                              int blockSize);

/** 
 * @brief Second order IIR Cascade filter with the SIMD version on SHARC processor
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] coeffs1               Points to (5*number of stages) coefficients for channel1 arranged as: b01, b11, b21, a11, a21, b02, b12, b22, a12, a22,.... b0n, b1n, b2n, a1n, a2n 
 * @param[in] coeffs2               Points to (5*number of stages) coefficients for channel2 arranged as: b01, b11, b21, a11, a21, b02, b12, b22, a12, a22,.... b0n, b1n, b2n, a1n, a2n 
 * @param[in/out] state             Points to (2*number of stages) state variables.  These are modified upon exit
 * @param[in] nStages           Number of the cascade sections
 * @param[in] blockSize             Number of words to process
 */
void awe_vecBiquadNCascade_2ch( FLOAT32 *  src,
		int                        srcInc, 
		FLOAT32 *        dst,
		int                        dstInc, 
		const FLOAT32 * VEC_RESTRICT coeffs1,
		const FLOAT32 * VEC_RESTRICT coeffs2,
		FLOAT32 * VEC_RESTRICT      state,
		int						   nStages,
		int                        blockSize);		
				
/** 
 * @brief Second order IIR Cascade filter with the Extended Precision version on SHARC processor
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] coeffs                Points to (5*number of stages) coefficients arranged as: b01, b11, b21, a11, a21, b02, b12, b22, a12, a22,.... b0n, b1n, b2n, a1n, a2n 
 * @param[in/out] state             Points to (2*number of stages) state variables.  These are modified upon exit
 * @param[in] nStages           Number of the cascade sections
 * @param[in] blockSize             Number of words to process
 */
void awe_vecBiquadCascade40( FLOAT32 *  src,
		int                        srcInc, 
		FLOAT32 *        dst,
		int                        dstInc, 
		const FLOAT32 * VEC_RESTRICT coeffs,
		FLOAT32 * VEC_RESTRICT       state,
		int						   nStages,
		int                        blockSize);


#ifndef IA610
/** 
 * @brief Converts the 64 bit variable into 40 bit variable on the SHARC processor
 * @param[in] src              Points to the source double buffer or twice of 32 bit buffer 
 * @param[in] blockSize             Number of words to process
 * @param[out] dst                  Points to the destination 40 bit buffer
  */
void awe_vecConvertCoeff64To40(const long double * VEC_RESTRICT src,
		int						blockSize,
		long double * VEC_RESTRICT    dst);

/** 
 * @brief Smooths the 40 bit coefficients.
 * @param[in/out] currentCoeffs         Points to the Current coefficients
 * @param[in] targetCoeffs			    Points to the Target coefficients
 * @param[in] oneMinusRate              1.0 - Smoothing coefficient
 * @param[in] smoothingCoeff            Smoothing Coefficient.
  */
void awe_vecUpdateCoeffs40(long double * VEC_RESTRICT current_coeffs, 
		long double * VEC_RESTRICT targetCoeffs, 
		FLOAT32 				 oneMinusRate,
		FLOAT32 				 smoothingCoeff);

#endif

/** 
 * @brief Performs the Arthematic Shift
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] bitsToShift           Number of bits to shift
 * @param[in] blockSize             Number of words to process
 */		
void awe_vecShift(
        int *  src, 
        int             srcInc, 
        int *  dst, 
        int             dstInc, 		
		int		   bitsToShift,
        int        blockSize);

/** 
 * @brief Performs a logical shift
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] bitsToShift           Number of bits to shift
 * @param[in] blockSize             Number of words to process
 */		
void awe_vecLShift(
        int *  src, 
        int             srcInc, 
        int *  dst, 
        int             dstInc, 		
		int		   bitsToShift,
        int        blockSize);

/** 
 * @brief Performs the Arthematic Shift without Saturation. User can use this only 
 *		to shift bit position irrespective of value after shift.
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] bitsToShift           Number of bits to shift. 
 * @param[in] blockSize             Number of words to process
 */        
void awe_vecShiftNoSat(
        int *  src, 
        int             srcInc, 
        int *  dst, 
        int             dstInc, 		
		int		   bitsToShift,
        int        blockSize);        

/** 
 * @brief Implements an envelope follower with specified attack/release behavior
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] attackCoeff           Attack coefficient used when the src value is greater than envelop.
 * @param[in] releaseCoeff          Release coefficient used when the src value is not greater than envelop.
 * @param[in/out] state				Pointer to the envelop.
 * @param[in] blockSize             Number of words to process
 */
void awe_vecAttackRelease(
         FLOAT32 *  src,
		int                        srcInc,
        FLOAT32       *  dst,
		int                        dstInc,
		FLOAT32                      attackCoeff,
		FLOAT32                      releaseCoeff,
		FLOAT32                    * state,
        int                        blockSize);


void awe_vecAttackDecaySustainRelease(
                FLOAT32 *   src,
                int       srcInc,
                FLOAT32  *  dst,
                int       dstInc,
                FLOAT32     attackCoeff,
                FLOAT32     decayCoeff,
                FLOAT32     sustainLevel,
                FLOAT32     releaseCoeff,
				FLOAT32     maxLevel,
				int    *  releaseState,
                int    *  envStage,
                FLOAT32  *  state,
                int       blockSize);

/**
 * @brief Writes data into a circular buffer
 * @param[in] circBuffer			Points to the base of the circular buffer
 * @param[in] L                     Length of the buffer, in words
 * @param[in/out] writeOffset       First sample is written into the circular buffer at this offset
 *                                  The function returns the updated offset here.
 * @param[in] bufferInc             Stride through the circular buffer.  Can be negative.
 *                                  Must be in the range [-L +L]
 * @param[in] src                   Points to the source buffer
 * @param[in] srcInc                Stride through the source buffer
 * @param[in] blockSize             Number of samples to process
 */
  void awe_vecCircWrite(
		    int * VEC_RESTRICT circBuffer,
		    int	L,
		    int *writeOffset,
		    int bufferInc,
		    int * VEC_RESTRICT src,
		    int srcInc,
		    int blockSize);

/**
 * @brief Writes data into a circular buffer
 * @param[in] circBuffer			Points to the base of the circular buffer
 * @param[in] L                     Length of the buffer, in words
 * @param[in/out] writeOffset       First sample is written into the circular buffer at this offset
 *                                  The function returns the updated offset here.
 * @param[in] bufferInc             Stride through the circular buffer.  Can be negative.
 *                                  Must be in the range [-L +L]
 * @param[in] src                   Points to the source buffer
 * @param[in] srcInc                Stride through the source buffer
 * @param[in] blockSize             Number of samples to process
 */
  void awe_vecCircWrite16(
		    short * VEC_RESTRICT circBuffer,
		    int	L,
		    int *writeOffset,
		    int bufferInc,
		    int * VEC_RESTRICT src,
		    int srcInc,
		    int blockSize);
		   
/**
 * @brief Reads data from a circular buffer
 * @param[in] circBuffer			Points to the base of the circular buffer
 * @param[in] L                     Length of the buffer, in words
 * @param[in,out] readOffset        First sample is read from the circular buffer at this offset
 *                                  The updated offset is also returned.
 * @param[in] bufferInc             Stride through the circular buffer.  Can be negative.
 *                                  Must be in the range [-L +L]
 * @param[in] dst                   Points to the where the output will be written
 * @param[in] dstInc                Stride through the output buffer
 * @param[in] blockSize             Number of samples to process
 */
  
  void awe_vecCircRead(
		   int * VEC_RESTRICT circBuffer,
		   int	L,
		   int *readOffset,
		   int bufferInc,
		   int * VEC_RESTRICT dst,
		   int dstInc,
		   int blockSize);


/**
 * @brief Reads data from a circular buffer
 * @param[in] circBuffer			Points to the base of the circular buffer
 * @param[in] L                     Length of the buffer, in words
 * @param[in,out] readOffset        First sample is read from the circular buffer at this offset
 *                                  The updated offset is also returned.
 * @param[in] bufferInc             Stride through the circular buffer.  Can be negative.
 *                                  Must be in the range [-L +L]
 * @param[in] dst                   Points to the where the output will be written
 * @param[in] dstInc                Stride through the output buffer
 * @param[in] blockSize             Number of samples to process
 */
  void awe_vecCircReadFract32(
		   int * VEC_RESTRICT circBuffer,
		   int	L,
		   int *readOffset,
		   int bufferInc,
		   int * VEC_RESTRICT dst,
		   int * dst_base,
		   int dst_length,
		   int dstInc,
		   int blockSize);

/**
 * @brief Writes into and reads from a circular buffer
 * @param[in] circBuffer            Points to the base of the circular buffer
 * @param[in] L                     Length of the buffer, in words
 * @param[in,out] writeOffset       First sample is written into the circular buffer at this offset
 * @param[in,out] readOffset        First sample is read from the circular buffer at this offset
 * @param[in] incA                  Stride through the circular buffer.  Can be negative.
 *                                  Must be in the range [-L +L].  Applies to both reading and writing
 * @param[in] src                   Points to the where the input is read from
 * @param[in] dst                   Points to the where the output will be written
 * @param[in] incB                  Stride through the src and dst buffers
 * @param[in] blockSize             Number of samples to process 
 */
  void awe_vecCircWriteRead(
			 int * VEC_RESTRICT circBuffer,
			 int	L,
			 int *writeOffset,
			 int *readOffset,
			 int incA,
			 const int * VEC_RESTRICT src,
			 int * VEC_RESTRICT dst,
			 int incB,
			 int blockSize);

/**
 * @brief Writes into and reads from a 16-bit circular buffer
 * @param[in] circBuffer            Points to the base of the circular buffer
 * @param[in] L                     Length of the buffer, in words
 * @param[in,out] writeOffset       First sample is written into the circular buffer at this offset
 * @param[in,out] readOffset        First sample is read from the circular buffer at this offset
 *                                  Must be in the range [-L +L].  Applies to both reading and writing
 * @param[in] src                   Points to the where the input is read from
 * @param[in] dst                   Points to the where the output will be written
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecCircWriteRead16(short * VEC_RESTRICT circ_buffer,
							int	length,
							int *write_index,
							int *read_index,
							const int * VEC_RESTRICT src,
							int * VEC_RESTRICT dst,
							int block_size);

/**
 * @brief Writes into and reads from a 16-bit circular buffer
 * @param[in] circBuffer            Points to the base of the circular buffer
 * @param[in] L                     Length of the buffer, in words
 * @param[in,out] writeOffset       First sample is written into the circular buffer at this offset
 * @param[in,out] readOffset        First sample is read from the circular buffer at this offset
 *                                  Must be in the range [-L +L].  Applies to both reading and writing
 * @param[in] src                   Points to the where the input is read from
 * @param[in] dst                   Points to the where the output will be written
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecCircWriteRead16Float(short * VEC_RESTRICT circ_buffer,
								 int length,
								 int *write_index,
								 int *read_index,
								 const FLOAT32 * VEC_RESTRICT src,
								 FLOAT32 * VEC_RESTRICT dst,
								 int block_size);

/**
 * @brief Writes into and reads from a 16-bit circular buffer
 * @param[in] circBuffer            Points to the base of the circular buffer
 * @param[in] L                     Length of the buffer, in words
 * @param[in,out] writeOffset       First sample is written into the circular buffer at this offset
 * @param[in,out] readOffset        First sample is read from the circular buffer at this offset
 *                                  Must be in the range [-L +L].  Applies to both reading and writing
 * @param[in] src                   Points to the where the input is read from
 * @param[in] dst                   Points to the where the output will be written
 * @param[in] coef                  Feedback/-feedforward coefficient for the allpass delay
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecAllpassDelay16(short * VEC_RESTRICT state,
							int	length,
							int *write_index,
							int *read_index,
							const FLOAT32 * VEC_RESTRICT src,
							FLOAT32 * VEC_RESTRICT dst1,
							FLOAT32 * VEC_RESTRICT dst2,
							FLOAT32 coef,
							int block_size);


/**
 * @brief Writes into and reads from a 16-bit circular buffer
 * @param[in] circBuffer            Points to the base of the circular buffer
 * @param[in] L                     Length of the buffer, in words
 * @param[in,out] writeOffset       First sample is written into the circular buffer at this offset
 * @param[in,out] readOffset        First sample is read from the circular buffer at this offset
 *                                  Must be in the range [-L +L].  Applies to both reading and writing
 * @param[in] src                   Points to the where the input is read from
 * @param[in] dst                   Points to the where the output will be written
 * @param[in] coef                  Feedback/-feedforward coefficient for the allpass delay
 * @param[in] postShift             Number of bits to shift after the fractional multiply.
 * @param[in] blockSize             Number of samples to process
 *
 * The function returns the
 */

void awe_vecAllpassDelay16Fract32(INT16 * VEC_RESTRICT state,
								INT32	length,
								INT32 *write_index,
								INT32 *read_index,
								const fract32 * VEC_RESTRICT src,
								fract32 * VEC_RESTRICT dst1,
								fract32 * VEC_RESTRICT dst2,
								fract32 coef,
								INT32 postShift,
                                INT32 block_size);

/**
 * @brief Writes into and reads from a 16-bit circular buffer
 * @param[in] circBuffer            Points to the base of the circular buffer
 * @param[in] L                     Length of the buffer, in words
 * @param[in,out] writeOffset       First sample is written into the circular buffer at this offset
 * @param[in,out] readOffset        First sample is read from the circular buffer at this offset
 *                                  Must be in the range [-L +L].  Applies to both reading and writing
 * @param[in] src                   Points to the where the input is read from
 * @param[in] dst                   Points to the where the output will be written
 * @param[in] coef                  Feedback/-feedforward coefficient for the allpass delay
 * @param[in] postShift             Number of bits to shift after the fractional multiply.
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecAllpassDelay16Fract32(INT16 * VEC_RESTRICT state,
								INT32	length,
								INT32 *write_index,
								INT32 *read_index,
								const fract32 * VEC_RESTRICT src,
								fract32 * VEC_RESTRICT dst1,
								fract32 * VEC_RESTRICT dst2,
								fract32 coef,
								int postShift,
								INT32 block_size);

/** 
 * @brief Logic compare Equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] inB                   Points to the second source location
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareEqual(
        const FLOAT32 * VEC_RESTRICT inA,
        const FLOAT32 * VEC_RESTRICT inB,
        int			* VEC_RESTRICT out, 
        int         blockSize);

/** 
 * @brief Logic compare Not Equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] inB                   Points to the second source location
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareNotEqual(
        const FLOAT32 * VEC_RESTRICT inA,
        const FLOAT32 * VEC_RESTRICT inB,
        int			* VEC_RESTRICT out, 
        int         blockSize);

/** 
 * @brief Logic compare LessThan module
 * @param[in] inA                   Points to the first source location
 * @param[in] inB                   Points to the second source location
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareLessThan(
        const FLOAT32 * VEC_RESTRICT inA,
        const FLOAT32 * VEC_RESTRICT inB,
        int			* VEC_RESTRICT out, 
        int         blockSize);
/** 
 * @brief Logic compare lessThan Equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] inB                   Points to the second source location
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareLessOrEqual(
        const FLOAT32 * VEC_RESTRICT inA,
        const FLOAT32 * VEC_RESTRICT inB,
        int			* VEC_RESTRICT out, 
        int         blockSize);
/** 
 * @brief Logic compare Greater than module
 * @param[in] inA                   Points to the first source location
 * @param[in] inB                   Points to the second source location
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareGreater(
        const FLOAT32 * VEC_RESTRICT inA,
        const FLOAT32 * VEC_RESTRICT inB,
        int			* VEC_RESTRICT out, 
        int         blockSize);
/** 
 * @brief Logic compare Greater Than equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] inB                   Points to the second source location
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareGreaterOrEqual(
        const FLOAT32 * VEC_RESTRICT inA,
        const FLOAT32 * VEC_RESTRICT inB,
        int			* VEC_RESTRICT out, 
        int         blockSize);

/** 
 * @brief Logic compare equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] const_value           constant value which needs to compare against to source 
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareConstEqual(
        const FLOAT32 * VEC_RESTRICT inA,
        FLOAT32 		const_value, 
        int			* VEC_RESTRICT out, 
        int         blockSize);

  /** 
 * @brief Logic compare not equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] const_value           constant value which needs to compare against to source 
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareConstNotEqual(
        const FLOAT32 * VEC_RESTRICT inA,
        FLOAT32 		const_value, 
        int			* VEC_RESTRICT out, 
        int         blockSize);

  /** 
 * @brief Logic compare less Than module
 * @param[in] inA                   Points to the first source location
 * @param[in] const_value           constant value which needs to compare against to source 
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareConstLessThan(
		const FLOAT32 * VEC_RESTRICT inA,
        FLOAT32 		const_value, 
        int			* VEC_RESTRICT out, 
        int         blockSize);

  /** 
 * @brief Logic compare less Than equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] const_value           constant value which needs to compare against to source 
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareConstLessOrEqual(
		const FLOAT32 * VEC_RESTRICT inA,
        FLOAT32 		const_value, 
        int			* VEC_RESTRICT out, 
        int         blockSize);

  /** 
 * @brief Logic compare Greater Than module
 * @param[in] inA                   Points to the first source location
 * @param[in] const_value           constant value which needs to compare against to source 
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareConstGreater(
		const FLOAT32 * VEC_RESTRICT inA,
        FLOAT32 		const_value, 
        int			* VEC_RESTRICT out, 
        int         blockSize);

 /** 
 * @brief Logic compare Greater Than equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] const_value           constant value which needs to compare against to source 
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareConstGreaterOrEqual(
		const FLOAT32 * VEC_RESTRICT inA,
        FLOAT32 		const_value, 
        int			* VEC_RESTRICT out, 
        int         blockSize);
        

/** 
 * @brief Logic compare equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] const_value           constant value which needs to compare against to source 
 * @param[out] out					             Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareConstEqualInt32(
        const int * VEC_RESTRICT inA, 
        int		const_value, 
        int			* VEC_RESTRICT out, 
        int         blockSize);

  /** 
 * @brief Logic compare not equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] const_value           constant value which needs to compare against to source 
 * @param[out] out					             Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareConstNotEqualInt32(
        const int * VEC_RESTRICT inA, 
        int		const_value, 
        int			* VEC_RESTRICT out, 
        int         blockSize);

  /** 
 * @brief Logic compare less Than module
 * @param[in] inA                   Points to the first source location
 * @param[in] const_value           constant value which needs to compare against to source 
 * @param[out] out					             Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareConstLessThanInt32(
		const int * VEC_RESTRICT inA, 
        int		const_value, 
        int			* VEC_RESTRICT out, 
        int         blockSize);

  /** 
 * @brief Logic compare less Than equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] const_value           constant value which needs to compare against to source 
 * @param[out] out					             Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareConstLessOrEqualInt32(
		const int * VEC_RESTRICT inA, 
        int		const_value, 
        int			* VEC_RESTRICT out, 
        int         blockSize);

  /** 
 * @brief Logic compare Greater Than module
 * @param[in] inA                   Points to the first source location
 * @param[in] const_value           constant value which needs to compare against to source 
 * @param[out] out					             Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareConstGreaterInt32(
		const int * VEC_RESTRICT inA, 
        int		const_value, 
        int			* VEC_RESTRICT out, 
        int         blockSize);

 /** 
 * @brief Logic compare Greater Than equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] const_value           constant value which needs to compare against to source 
 * @param[out] out					             Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareConstGreaterOrEqualInt32(
		const int * VEC_RESTRICT inA, 
        int		const_value, 
        int			* VEC_RESTRICT out, 
        int         blockSize);

 /** 
 * @brief Generates random numbers using a linear congruential generator
 * @param[out] dst                  Random numbers written here
 * @param[inout] seed               Starting random number seed and seed for next call
 * @param[in] numSamples            Number of random words to generate
 */
  void awe_vecRand(
		int * VEC_RESTRICT dst, 
		unsigned int * VEC_RESTRICT seed,
		int                  numSamples);


 /** 
 * @brief Complex FFT.  Forward and inverse.
 * @param[inout] data               Array of complex interleaved values
 * @param[int] N                    Number of complex samples.  Must be a power of 2.
 * @param[in] dir                   Transform direction.  =1 for forward.  =-1 for inverse.
 */
  void awe_vecCfft(
		FLOAT32 *  data,
		int                        N, 
		int                        dir);


  /** 
 * @brief Complex multiplication and addition.
 * @param[in] in1			Points to first buffer of complex input data
 * @param[in] in2			Points to second buffer of complex input data
 * @param[out] dst			Points to complex accumulator buffer
 * @param[in] numComplexSamples			Number of samples (FFT length)
 */

void awe_vecComplexMultAdd(FLOAT32 *in1,
	FLOAT32 *in2,
	FLOAT32 *dst,
	int numComplexSamples);


 /** 
 * @brief Complex FIR filter.
 * @param[in] state_real_base		Points to real part of FFT state memory
 * @param[in] state_imag_base		Points to imag part of FFT state memory
 * @param[in] coeffs_real_ptr		Points to real part of FFT coeffs
 * @param[in] coeffs_imag_ptr		Points to imag part of FFT coeffs
 * @param[out] out_real_ptr			Points to real accumulator buffer
 * @param[out] out_imag_ptr			Points to imag accumulator buffer
 * @param[in] circ_buf_length		Length of real/imag circular buffer length
 * @param[in] numTaps				Number of FIR filter taps
 * @param[in] stateIndex			Current index in to complex state memory
 * @param[in] fft_len				Number of samples (FFT length)
 */
void awe_vecComplexFIR(FLOAT32 *state_real_base,
					   FLOAT32 *state_imag_base,
					   FLOAT32 *coeffs_real_ptr,
					   FLOAT32 *coeffs_imag_ptr,
					   FLOAT32 *out_real_ptr,
					   FLOAT32 *out_imag_ptr,
					   int circ_buf_length,
					   int numTaps,
					   int stateIndex,
					   int fft_len);

 /** 
 * @brief Complex FIR filter with variable tap length in each bin.
 * @param[in] src				Points to input complex data
 * @param[out] dst				Points to output complex data
 * @param[in] state				Points to complex state memory
 * @param[in] coeffs			Points to complex coeffs memory
 * @param[in] numTaps			Array of number of FIR filter taps in each bin
 * @param[in] stateIndex		Current index in to complex state memory in each bin
 * @param[in] fft_len			Number of samples (FFT length)
 */
void awe_vecComplexFIRvl(FLOAT32 *src,
						FLOAT32 *dst,
						FLOAT32 *state,
					    FLOAT32 *coeffs,
					    int *numTaps,
					    int *stateIndex,
					    int FFTSize);

  /** 
 * @brief  complex-by-complex multiplication 
 * @param[in]  *pSrcA points to the first input vector 
 * @param[in]  *pSrcB points to the second input vector 
 * @param[out]  *pDst  points to the output vector 
 * @param[in]  numSamples number of complex samples in each vector 
 * @return none. 
 */
 
void awe_vecComplexMult(FLOAT32 * pSrcA,
					FLOAT32 * pSrcB,
					FLOAT32 * pDst,
					int blockSize);

  /** 
 * @brief  Q31 complex-by-complex multiplication 
 * @param[in]  *pSrcA points to the first input vector 
 * @param[in]  *pSrcB points to the second input vector 
 * @param[out]  *pDst  points to the output vector 
 * @param[in]  numSamples number of complex samples in each vector 
 * @return none. 
 */
 
void awe_vecComplexMultFract32(fract32 * pSrcA, 
							  fract32 * pSrcB, 
							  fract32 * pDst, 
							  UINT32 blockSize);

/**  
 * @brief division of two fixed point (fract32) complex numbers.  
 * @param[in]       *pSrcA points to the first input vector  
 * @param[in]       *pSrcB points to the second input vector  
 * @param[out]      *pDst points to the output vector  
 * @param[in]       blockSize number of samples in each vector  
 * @return none.
 */ 
void awe_vecComplexDivideFract32(fract32 * pSrcA, 
							  fract32 * pSrcB, 
							  fract32 * pDst, 
							  UINT32 blockSize);

/**  
 * @brief division of two FLOAT32 complex numbers.
 * @param[in]       *pSrcA points to the first input vector  
 * @param[in]       *pSrcB points to the second input vector  
 * @param[out]      *pDst points to the output vector  
 * @param[in]       blockSize number of samples in each vector  
 * @return none.
 */ 
void awe_vecComplexDivide(FLOAT32 * pSrcA,
						FLOAT32 * pSrcB,
						FLOAT32 * pDst,
						UINT32 blockSize);


 /** 
 * @brief Real FFT.  Forward and inverse.
 * @param[inout] data               Array of complex interleaved values
 * @param[int] N                    2*N equals number of real samples  Must be a power of 2.
 * @param[in] dir                   Transform direction.  =1 for forward.  =-1 for inverse.
 */
  void awe_vecRfft(
		FLOAT32 *  data,
		int                        N, 
		int                        dir);



  /** 
 * @brief Copies and scales a buffer
 * @param[in] src                   Source pointer
 * @param[in] dst	                Destination pointer
 * @param[out] channels             Number of channels
 * @param[in] currentGain           Current Gain
 * @param[in] targetGain            Target gain
 * @param[in] smoothingCoeff        Smoothing coefficient
 * @param[in] blockSize             Number of samples to process
 */

void awe_vecScaleSmooth_Nch(
	FLOAT32 * src,
	FLOAT32 * dst,
	int	channels,
	FLOAT32 * currentGain,
	FLOAT32 	targetGain,
	FLOAT32 	smoothingCoeff,
	int	blockSize);


 /** 
 * @brief Copies and scales a buffer
 * @param[in] src                   Source pointer
 * @param[in] dst	                Destination pointer
 * @param[out] numChannels             Number of channels
 * @param[in] currentGain           Current Gain
 * @param[in] targetGain            Target gain
 * @param[in] shift                 shift adjustment in gain format
 * @param[in] smoothingCoeff        Smoothing coefficient
 * @param[in] numSamples             Number of samples to process
 */
void awe_vecScaleSmooth_NchFract32(
        fract32						*src, 
        fract32						*dst, 
        int							numChannels, 
        fract32						*currentGain,
        fract32						targetGain,
        int                          shift,
		fract32						smoothingCoeff,
        int                          numSamples);


  /** 
 * @brief Copies and scales a buffer
 * @param[in] src                   Points to the source location
 * @param[in] srcStride             Source sample pitch
 * @param[out] dst                  Points to the destination location
 * @param[in] dstStrid              Destination sample pitch
 * @param[in] m                     Scale magnitude
 * @param[in] shift                 Exponant value to support scaler values more than -1.0 to 1.0(max value supported is 4)
 * @param[in] numSamples            Number of words to process
 */
void awe_vecScaleFract32(
        fract32 *  src, 
        int                          srcStride, 
        fract32       *  dst, 
        int                          dstStride, 
        fract32                      m,
        int                          shift,
        int                        numSamples);

/**
 * @brief Smoothly scales a buffer
 * @param[in] src                   Points to the source location
 * @param[in] srcInc				Increment between source values
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination values
 * @param[in] currentGainFract      Starting amplitude for the smoothing operation.
 *										This is returned updated at the end of the call.
 * @param[in,out] targetGainFract   Final amplitude which the smoothing operation
 *                                  approaches
 * @param[in] postShift             Number of bits to shift after the fractional multiply.

 * @param[in] smoothingCoeff        Coefficient which controls the rate of the smoothing
 *                                  operation.
 * @param[in] blockSize             Number of words to process
 */
void awe_vecScaleSmoothFract32(
		     fract32 *  src, 
		     int                          srcInc, 
		     fract32       *  dst, 
		     int                          dstInc, 
		     fract32       * VEC_RESTRICT currentGainFract,
		     fract32                      targetGainFract,
		     int                          postShift,
		     fract32                      smoothingCoeff, 
		     int                          blockSize);


/**
 * @brief Smoothly scales a buffer and adds it to another buffer
 * @param[in] src                   Points to the source location
 * @param[in] srcInc				Increment between source values
 * @param[out] dst                  Points to the destination (accumulation) location
 * @param[in] dstInc                Increment between destination values
 * @param[in,out] *currentGainFract       Starting amplitude for the smoothing
 *                                  operation. This is returned updated at the 
 *                                  end of the call.
 * @param[in] targetGainFract             Final amplitude which the smoothing operation
 *                                  approaches
 * @param[in] postShift             Number of bits to shift after the fractional multiply.
 * @param[in] smoothingCoeff        Coefficient which controls the rate of the smoothing
 *                                  operation.
 * @param[in] blockSize             Number of words to process
 */

void awe_vecScaleAddSmoothFract32(
		     fract32 *  src, 
		     int                          srcInc, 
		     fract32       *  dst, 
		     int                          dstInc, 
		     fract32       * VEC_RESTRICT currentGainFract,
		     fract32                      targetGainFract,
		     int                          postShift,
		     fract32                      smoothingCoeff, 
		     int                          blockSize);


/** 
 * @brief Logical OR of two buffers sample by sample
 * @param[in] inA                   Pointer to the first input buffer
 * @param[in] incA                  Increment between source values
 * @param[in] inB                   Pointer to the second input buffer
 * @param[in] incB                  Increment between source values
 * @param[out] out                  Pointer to the output buffer @param[in]
 * @param[in] incC                  Increment between destination values
 * @param[in] blockSize             Number of words to process
 */
void awe_vecOr2x1(
        int * VEC_RESTRICT inA, 
        int                        incA, 
        int * VEC_RESTRICT inB, 
        int                        incB, 
        int		  *  out, 
        int                        incC, 
        int                        blockSize);



/** 
 * @brief Logical AND of two buffers sample by sample
 * @param[in] inA                   Pointer to the first input buffer
 * @param[in] incA                  Increment between source values
 * @param[in] inB                   Pointer to the second input buffer
 * @param[in] incB                  Increment between source values
 * @param[out] out                  Pointer to the output buffer @param[in]
 * @param[in] incC                  Increment between destination values
 * @param[in] blockSize             Number of words to process
 */
void awe_vecAnd2x1(
        int * VEC_RESTRICT inA, 
        int                        incA, 
        int * VEC_RESTRICT inB, 
        int                        incB, 
        int		  *  out, 
        int                        incC, 
        int                        blockSize);


/** 
 * @brief Logical NOT of two buffers sample by sample
 * @param[in] inA                   Pointer to the first input buffer
 * @param[in] incA                  Increment between source values
 * @param[out] out                  Pointer to the output buffer @param[in]
 * @param[in] incC                   Increment between destination values
 * @param[in] blockSize             Number of words to process
 */
void awe_vecNot1x1(
        int *  inA, 
        int                        incA,        
        int		  *  out, 
        int                        incC, 
        int                        blockSize);


/** 
 * @brief Logical XOR of two buffers sample by sample
 * @param[in] inA                   Pointer to the first input buffer
 * @param[in] incA                  Increment between source values
 * @param[in] inB                   Pointer to the second input buffer
 * @param[in] incB                  Increment between source values
 * @param[out] out                  Pointer to the output buffer @param[in]
 * @param[in] incC                  Increment between destination values
 * @param[in] blockSize             Number of words to process
 */
void awe_vecXor2x1(
        int * VEC_RESTRICT inA, 
        int                        incA, 
        int * VEC_RESTRICT inB, 
        int                        incB, 
        int		  *  out, 
        int                        incC,
        int                        blockSize);


/**
 * @brief Softclipper
 * @param[in] src                  Pointer to the first input buffer
 * @param[in] threshold            Beginning of the knee
 * @param[out] endKnee             End of the knee
 * @param[in] dst                  ointer to the output buffer
 * @param[in] numSamples           Number of samples to process
 */
void awe_vecSoftClip(
                         const FLOAT32 *  src,
                         const FLOAT32    threshold,
                         const FLOAT32    endKnee,
                         FLOAT32 *        dst,
                         const int      numSamples);

void awe_vecSoftClipFract32(
                         const fract32 *  src,
                         const fract32    threshold,
                         const fract32    endKnee,
                         fract32 *        dst,
                         const int      numSamples);

/**
 * @brief Table interpolation functions
 * @param[in] src                  Pointer to the first input buffer
 * @param[in] XY                   Buffer to points table
 * @param[in] numSegments          Number of segments
 * @param[in] polyCoeffs           Coefficients buffer
 * @param[in] dst                  ointer to the output buffer
 * @param[in] numSamples           Number of samples to process
 */
void awe_vecTableInterpRuntime(
                             const FLOAT32 *  src,
                             const FLOAT32 *  XY,
                             const int      numSegments,
                             const FLOAT32 *  polyCoeffs,
                             FLOAT32 *        dst,
                             const int      numSamples);


void awe_vecTableInterp(
                             const FLOAT32 *  src,
                             const FLOAT32 *  XY,
                             const int      numSegments,
                             const FLOAT32 *  polyCoeffs,
                             FLOAT32 *        dst,
                             const int      numSamples);

void awe_vecTableInterpFract32(
                             const fract32 * src,
                             const fract32 * XY,
                             const int       numSegments,
                             const fract32 * polyCoeffs,
                             fract32 *       dst,
                             const int       numSamples);

/**
 * @brief FIR filter
 * @param[in] src                   Points to the source location
 * @param[in] srcStride             Increment between source values
 * @param[out] dst                  Points to the destination location
 * @param[in] coeffs                Points to FIR filter taps stored in normal order
 * @param[in/out] state             Points to state variables.  These are modified upon exit
 * @param[in/out] stateIndex        Points to starting point in state array.  This is modified on exit
 * @param[in] postShift             Number of bits to shift after the fractional multiply.
 * @param[in] blockSize             Number of samples to process
 * @param[in] numTaps               Number of FIR filter coefficients
 */
void awe_vecFIRFract32(
            fract32       *              src, 
            int                          srcStride, 
            fract32       *              dst, 
            int                          dstStride,
            const fract32 * VEC_RESTRICT coeffs, 
            fract32       * VEC_RESTRICT state,
            int                          blockSize,
            int                          numTaps, 
            fract32       *              stateIndex,
            int                          postShift);
	    
/** 
 * @brief Log10
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source values
 * @param[out] dst                   Points to the destination location
 * @param[in] dstInc                 Increment between destination values
 * @param[in] blockSize              Number of samples to process
 */
void awe_vecLog10Fract32(
         fract32 *  src, 
        int                          srcInc, 
        fract32       *  dst, 
        int                          dstInc,
	    int                        blockSize);

	    	   
 /** 
 * @brief reciprocal
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source values
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination values
 * @param[out] postShift			Number of guard bits of the reciprocal output.
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecReciprocalFract32(
        fract32 *  src, 
        int                          srcInc, 
        fract32       *  dst, 
        int                          dstInc,
        int							 postShift,
	    int                          blockSize);
	     
/** 
 * @brief FIR LMS filter
 * @param[in] in                    Points to the source location of filter input data
 * @param[in] ref                   Points to the source location of reference data, (desired filter ouput)
 * @param[out] out                  Points to the destination location for filter output data
 * @param[out] err                  Points to the destination location for error data
 * @param[in/out] coeffs            Points to FIR filter taps stored in normal order
 * @param[in/out] state             Points to state variables.  These are modified upon exit
 * @param[in/out] stateIndex        Points to starting point in state array.  This is modified on exit
 * @param[in] postShift             Number of bits to shift after the fractional multiply.
 * @param[in] blockSize             Number of samples to process
 * @param[in] numTaps               Number of FIR filter coefficients
 * @param[in] mu                    LMS step size parameter
 */
void awe_vecLMSFract32( fract32 *  in,
          fract32 *  ref, 
	     fract32 *        out,
         fract32 * VEC_RESTRICT       err, 
	     fract32 * VEC_RESTRICT       coeffs, 
	     fract32 * VEC_RESTRICT       state, 
	     int                          * stateIndex,
         int                          postShift,
	     int                          blockSize,
	     int                          numTaps,
         fract32                      mu);


/** 
 * @brief Adds two buffers sample by sample
 * @param[in] inA                   Pointer to the first input buffer
 * @param[in] incA                  Increment between source values
 * @param[in] inB                   Pointer to the second input buffer
 * @param[in] incB                  Increment between source values
 * @param[out] out                  Pointer to the output buffer @param[in]
 * @param[out] incC                 Increment between Destination values
 * @param[in] blockSize             Number of words to process
 */
void awe_vecAdd2x1Fract32(
        fract32 * inA, 
        int             incA, 
        fract32 * inB, 
        int             incB, 
        fract32       * out, 
        int             incC, 
        int             blockSize);


/** 
 * @brief Computes scaled sum and difference of 2  inputs
 * @param[in] src1                   Points to 1st input buffer
 * @param[in] src2                   Points to 2nd input buffer
 * @param[out] dst1                  Points to 1st output buffer
 * @param[out] dst2                  Points to 2nd output buffer
  * @param[in] blockSize             Number of words to process
 */
void awe_vecScaleSumDiffFract32(
         fract32 * VEC_RESTRICT src1, 
		 fract32 *  src2,
		fract32 * VEC_RESTRICT dst1,
		fract32 *  dst2,
		int blockSize);

/**
 * @brief Fills a buffer with a specified value and increment.
 * @param[out] ptr                  Pointer to the start of the buffer
 * @param[in] inc                   Pointer increment
 * @param[in] value                 Value to fill
 * @param[in] blockSize             Number of words to fill.
 */
void awe_vecFillFract32(
        fract32 *  ptr, 
        int                  inc, 
        fract32                value,
        int                  blockSize);


/**
 * @brief Subtracts two buffers sample by sample
 * @param[in] inA                   Pointer to the first input buffer
 * @param[in] incA                  Increment between source values
 * @param[in] inB                   Pointer to the second input buffer
 * @param[in] incB                  Increment between source values
 * @param[out] out                  Pointer to the output buffer @param[in]
 * @param[out] incC                 Increment between Destination values
 * @param[in] blockSize             Number of words to process
 */
void awe_vecSubtract2x1Fract32(
        fract32 * inA, 
        int             incA, 
        fract32 * inB, 
        int             incB, 
        fract32       * out, 
        int             incC, 
        int             blockSize);


/**
 * @brief Fractional Multiplication two buffers sample by sample
 * @param[in] inA                   Pointer to the first input buffer
 * @param[in] incA                  Increment between samples in inA
 * @param[in] inB                   Pointer to the second input buffer
 * @param[in] incB                  Increment between samples in inB
 * @param[out] out                  Pointer to the output buffer @param[in]
 * @param[in] incC                  Increment between samples in out
 * @param[in] blockSize             Number of words to process
 */
void awe_vecMultiply2x1Fract32(
		      fract32 *  inA,
		     int                        incA,
		      fract32 *  inB,
		     int                        incB,
		     fract32 *        out,
		     int                        incC,
		     int                        blockSize);

/**
 * @brief Fractional Multiplication two buffers sample by sample
 * @param[in] pSrcA                 Pointer to the first input buffer
 * @param[in] incA                  Increment between samples in inA
 * @param[in] pSrcB                 Pointer to the second input buffer
 * @param[in] incB                  Increment between samples in inB
 * @param[in] pAdd                  Pointer to the second input buffer
 * @param[in] incAdd                Increment between samples in inB
 * @param[out] pDst                 Pointer to the output buffer @param[in]
 * @param[in] incDst                Increment between samples in out
 * @param[in] blockSize             Number of words to process
 */
void awe_vecMultiplyAddFract32(
                            const fract32 *              pSrcA,
                            int                        incA,
                            const fract32 *              pSrcB,
                            int                        incB,
                            fract32 *                    pAdd,
                            int                        incAdd,
                            fract32 *                    pDst,
                            int                        incDst,
                            int                        blockSize);

/**
 * @brief Fractional AGC Multiplication two buffers sample by sample
 * @param[in] inA                   Pointer to the first input buffer
 * @param[in] incA                  Increment between samples in inA
 * @param[in] inB                   Pointer to the second input buffer
 * @param[in] incB                  Increment between samples in inB
 * @param[out] out                  Pointer to the output buffer @param[in]
 * @param[in] incC                  Increment between samples in out
 * @param[in] shift                 Number of bits to shift after the fractional multiply.
 * @param[in] blockSize             Number of words to process
 */
void awe_vecAGCMultiplierFract32(
        fract32 *  src1, 
        int                          src1Stride, 
		 fract32 *  src2, 
        int                          src2Stride, 
        fract32       *  dst, 
        int                          dstStride, 
        int                          shift,
        int                          numSamples);

/** 
 * @brief Scales and offsets a buffer
 * @param[in] src                   Points to the source location
 * @param[out] dst                  Points to the destination location
 * @param[in] K                     Scale factor
 * @param[in] offset                Offset value
 * @param[in] blockSize             Number of words to process
 * @param[in] stride                Increment between input and output samples
 */
void awe_vecScaleOffsetFract32(
        fract32 *  src, 
        int                          srcStride, 
        fract32       *  dst, 
        int                          dstStride, 
        fract32                      m,
        int                          shift,
		fract32						offset,
        int                          numSamples);


/**
 * @brief Computes the absolute value of fractional buffer of FLOAT32 ing-point data
 * @param[in] src                   Points to the source buffer
 * @param[in] srcInc                Source data pitch
 * @param[out] dst                  Points to the destination buffer
 * @param[in] dstInc                Destination data pitch
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecAbsFract32(
         fract32 *  src, 
        int                        srcInc, 
        fract32       *  dst, 
        int                        dstInc, 
        int                        blockSize);

/** 
 * @brief Squares a buffer and accumulates the result to another buffer
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] blockSize             Number of words to process
 */
void awe_vecSquareAddFract32(
		    fract32 *  src, 
		   int                        srcInc, 
		   fract32 *        dst, 
		   int                        dstInc, 
		   int                        blockSize);


/**
 * @brief Clips a buffer of data to specified lower and upper bounds
 * @param[in] src                   Points to the source buffer
 * @param[out] dst                  Points to the destination buffer
 * @param[in] clipLower             Lower clipping threshold
 * @param[in] clipUpper             Upper clipping threshold
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecClipAsymFract32(
         fract32 *  src, 
        fract32       *  dst, 
        fract32                clipLower, 
        fract32                clipUpper, 
        int                    blockSize);


/**
 * @brief Scales a buffer and adds the result to another buffer
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source values
 * @param[out] dst                  Points to the destination accumulation buffer
 * @param[in] dstInc                Increment between destination values
 * @param[in] gain                  Scale factor for the src buffer
 * @param[in] postShift             post shift value
 * @param[in] blockSize             Number of words to process
 */
void awe_vecScaleAddFract32(
         fract32 *  src, 
        int                        srcInc, 
        fract32       *  dst, 
        int                        dstInc, 
        fract32                      gain, 
		int                          postShift,
        int                        blockSize);

/** 
 * @brief Sample-by-sample polynomial
 * @param[in] src                   Points to the source buffer
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination buffer
 * @param[in] dstInc                Increment between output samples
 * @param[in] numCoeffs             Number of coefficients in the polynomial.  Order = numCoeffs - 1.
 * @param[in] coeffs                Pointer to the coefficients: C[0]*X^(N-1) + C[1]*X^(N-2) + ... + C[N-2] * X + C[N-1]
 * @param[in] postShift             post shift value
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecPolynomialFract32(
        fract32 *  src, 
        int                        srcInc, 
        fract32       *  dst, 
        int                        dstInc, 
        int                        numCoeffs, 
        const fract32 * VEC_RESTRICT coeffs, 
		int						   postShift,
        int                        blockSize);


/** 
 * @brief Converts FLOAT32 values from input buffer to fractional values in output buffer
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] blockSize             Number of words to process
 */
void awe_vecFloatToFract32(
        const FLOAT32 * VEC_RESTRICT src,
        int                        srcInc, 
        fract32         * VEC_RESTRICT dst, 
        int                        dstInc, 
        int                        blockSize);


/** 
 * @brief Converts FLOAT32 values from input buffer to 16-bit fractional values in output buffer
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] blockSize             Number of words to process
 */
void awe_vecFloatToFract16(
        const FLOAT32 * VEC_RESTRICT src,
        int                        srcInc, 
        fract16         * VEC_RESTRICT dst, 
        int                        dstInc, 
        int                        blockSize);          
/** 
 * @brief Converts fractional values from input buffer to  FLOAT32 values in output buffer
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] blockSize             Number of words to process
 */
void awe_vecFract32ToFloat(
        const fract32 * VEC_RESTRICT src,
        int                        srcInc, 
        FLOAT32       * VEC_RESTRICT dst,
        int                        dstInc, 
        int                        blockSize);

        
/**
 * @brief Determines the maximum absolute value in a buffer
 * @param[in] src                   Points to the buffer of data
 * @param[in] blockSize             Number of samples to process
 * @param[out] *index               Index of the maximum absolute value returned here
 * @return                          Maximum absolute value
 */
fract32 awe_vecMaxAbsFract32(
        const fract32 * VEC_RESTRICT src, 
        int                        srcInc,
        int                        blockSize, 
        int         * VEC_RESTRICT index);


/** 
 * @brief Logic compare equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] const_value           constant value which needs to compare against to source 
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
void awe_vecLogicCompareConstEqualFract32(
        const fract32 * VEC_RESTRICT inA, 
        fract32		const_value, 
        int			* VEC_RESTRICT out, 
        int         blockSize);

/** 
 * @brief Logic compare not equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] const_value           constant value which needs to compare against to source 
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
void awe_vecLogicCompareConstNotEqualFract32(
        const fract32 * VEC_RESTRICT inA, 
        fract32		const_value, 
        int			* VEC_RESTRICT out, 
        int         blockSize);

/** 
 * @brief Logic compare less Than module
 * @param[in] inA                   Points to the first source location
 * @param[in] const_value           constant value which needs to compare against to source 
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
void awe_vecLogicCompareConstLessThanFract32(
        const fract32 * VEC_RESTRICT inA, 
        fract32		const_value, 
        int			* VEC_RESTRICT out, 
        int         blockSize);

  /** 
 * @brief Logic compare less Than equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] const_value           constant value which needs to compare against to source 
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
void awe_vecLogicCompareConstLessOrEqualFract32(
        const fract32 * VEC_RESTRICT inA, 
        fract32		const_value, 
        int			* VEC_RESTRICT out, 
        int         blockSize);

  /** 
 * @brief Logic compare Greater Than module
 * @param[in] inA                   Points to the first source location
 * @param[in] const_value           constant value which needs to compare against to source 
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
void awe_vecLogicCompareConstGreaterFract32(
        const fract32 * VEC_RESTRICT inA, 
        fract32		const_value, 
        int			* VEC_RESTRICT out, 
        int         blockSize);

 /** 
 * @brief Logic compare Greater Than equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] const_value           constant value which needs to compare against to source 
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
void awe_vecLogicCompareConstGreaterOrEqualFract32(
        const fract32 * VEC_RESTRICT inA, 
        fract32		const_value, 
        int			* VEC_RESTRICT out, 
        int         blockSize);

/** 
 * @brief Logic compare Equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] inB                   Points to the second source location
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
void awe_vecLogicCompareEqualFract32(
	const fract32 * VEC_RESTRICT inA, 
	const fract32 * VEC_RESTRICT inB, 
	int			* VEC_RESTRICT out, 
	int         blockSize);

/** 
 * @brief Logic compare Not Equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] inB                   Points to the second source location
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
void awe_vecLogicCompareNotEqualFract32(
		const fract32 * VEC_RESTRICT inA, 
		const fract32 * VEC_RESTRICT inB, 
		int			* VEC_RESTRICT out, 
		int         blockSize);

/** 
 * @brief Logic compare LessThan module
 * @param[in] inA                   Points to the first source location
 * @param[in] inB                   Points to the second source location
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
void awe_vecLogicCompareLessThanFract32(
		const fract32 * VEC_RESTRICT inA, 
		const fract32 * VEC_RESTRICT inB, 
		int			* VEC_RESTRICT out, 
		int         blockSize);

/** 
 * @brief Logic compare lessThan Equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] inB                   Points to the second source location
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
void awe_vecLogicCompareLessOrEqualFract32(
		const fract32 * VEC_RESTRICT inA, 
		const fract32 * VEC_RESTRICT inB, 
		int			* VEC_RESTRICT out, 
		int         blockSize);

/** 
 * @brief Logic compare Greater than module
 * @param[in] inA                   Points to the first source location
 * @param[in] inB                   Points to the second source location
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
void awe_vecLogicCompareGreaterFract32(
		const fract32 * VEC_RESTRICT inA, 
		const fract32 * VEC_RESTRICT inB, 
		int			* VEC_RESTRICT out, 
		int         blockSize);

/** 
 * @brief Logic compare Greater Than equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] inB                   Points to the second source location
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
void awe_vecLogicCompareGreaterOrEqualFract32(
		const fract32 * VEC_RESTRICT inA, 
		const fract32 * VEC_RESTRICT inB, 
		int			* VEC_RESTRICT out, 
		int         blockSize);


/** 
 * @brief Logic compare Equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] inB                   Points to the second source location
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareEqualInt32(
        const int * VEC_RESTRICT inA, 
        const int * VEC_RESTRICT inB, 
        int			* VEC_RESTRICT out, 
        int         blockSize);

/** 
 * @brief Logic compare Not Equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] inB                   Points to the second source location
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareNotEqualInt32(
        const int * VEC_RESTRICT inA, 
        const int * VEC_RESTRICT inB, 
        int			* VEC_RESTRICT out, 
        int         blockSize);

/** 
 * @brief Logic compare LessThan module
 * @param[in] inA                   Points to the first source location
 * @param[in] inB                   Points to the second source location
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareLessThanInt32(
        const int * VEC_RESTRICT inA, 
        const int * VEC_RESTRICT inB, 
        int			* VEC_RESTRICT out, 
        int         blockSize);
/** 
 * @brief Logic compare lessThan Equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] inB                   Points to the second source location
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareLessOrEqualInt32(
        const int * VEC_RESTRICT inA, 
        const int * VEC_RESTRICT inB, 
        int			* VEC_RESTRICT out, 
        int         blockSize);
/** 
 * @brief Logic compare Greater than module
 * @param[in] inA                   Points to the first source location
 * @param[in] inB                   Points to the second source location
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareGreaterInt32(
        const int * VEC_RESTRICT inA, 
        const int * VEC_RESTRICT inB, 
        int			* VEC_RESTRICT out, 
        int         blockSize);
/** 
 * @brief Logic compare Greater Than equal module
 * @param[in] inA                   Points to the first source location
 * @param[in] inB                   Points to the second source location
 * @param[out] out					Points to destination location
 * @param[in] blockSize             Number of words to process
 */
  void awe_vecLogicCompareGreaterOrEqualInt32(
        const int * VEC_RESTRICT inA, 
        const int * VEC_RESTRICT inB, 
        int			* VEC_RESTRICT out, 
        int         blockSize);
        
        
/** 
 * @brief Outputs square root of input
 * @param[in] src                   Points to the source buffer
 * @param[out] dst                  Points to the destination buffer
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecSqrtFract32(fract32 * src,
						int       srcInc,
					    fract32 * dst,
						int       dstInc,
						int       blockSize);

/** 
 * @brief Outputs inverse of input
 * @param[in] num                   the source value
 * @param[out] dst                  Points to the destination value 
 */

unsigned int awe_vecRecipFract32(fract32 num, 
					fract32   *  dst);

/** 
 * @brief implements sine of a number.
 * @param[in] num                   source value
 **/

fract32 awe_vecSineFract32(fract32 num);

/** 
 * @brief Implements a Sawtooth wave generator
 * @param[out] out                  Points to the destination location
 * @param[in/out] *phase			Pointer to the stored phase of the sawtooth module.
 * @param[in] phaseIncrement        The amount that the oscillator phase is incremented for each output sample.
 * @param[in] blockSize             Number of words to process
 */
void awe_vecSawtoothFract32(
		fract32 * VEC_RESTRICT 	out, 
        fract32                	*phase, 
        fract32                	phaseIncrement,
        int                  	blockSize);

/** 
 * @brief Implements an envelope follower with specified attack/release behavior
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] attackCoeff           Attack coefficient used when the src value is greater than envelop.
 * @param[in] releaseCoeff          Release coefficient used when the src value is not greater than envelop.
 * @param[in/out] state				Pointer to the envelop.
 * @param[in] blockSize             Number of words to process
 */
void awe_vecAttackReleaseFract32(
     fract32 *  src, 
	int                        srcInc,
    fract32		  *  dst, 
	int                        dstInc,
	fract32                      attackCoeff,
	fract32                      releaseCoeff,
	fract32                    * state,
    int                        blockSize);

void awe_vecBiquadFract24x24A56( fract32       *              src,
    int                          srcInc,
    fract32       *              dst,
    int                          dstInc,
    const fract32 * VEC_RESTRICT coeffs,
    fract32       * VEC_RESTRICT state,
    int                          bShift,
    int                          aShift,
    int                          blockSize);

/** 
 * @brief Second order IIR filter
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] coeffs                Points to 5 coefficients arranged as: b0, b1, b2, a1, a2
 * @param[in/out] state             Points to 4 state variables.  These are modified upon exit
 * @param[in] bShift			    b coefficients shift value
 * @param[in] aShift			    a coefficients shift value
 * @param[in] blockSize             Number of words to process
 */
void awe_vecBiquadFract32x32A64( fract32   * src, 
                int                          srcInc, 
                fract32                    * dst,
                int                          dstInc, 
                const fract32 * VEC_RESTRICT coeffs, 
                fract32 * VEC_RESTRICT       state, 
                int							 bShift,
                int							 aShift,
                int							 blockSize);
  
  
/** 
 * @brief Second order IIR filter
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] coeffs                Points to 5 coefficients arranged as: b0, b1, b2, a1, a2
 * @param[in/out] state             Points to 4 state variables.  These are modified upon exit
 * @param[in] bShift			    b coefficients shift value
 * @param[in] aShift			    a coefficients shift value
 * @param[in] blockSize             Number of words to process
 */
void awe_vecBiquadFract32x32A32( fract32   * src, 
                int                          srcInc, 
                fract32                    * dst,
                int                          dstInc, 
                const fract32 * VEC_RESTRICT coeffs, 
                fract32 * VEC_RESTRICT       state, 
                int							 bShift,
                int							 aShift,
                int							 blockSize);
 
/** 
 * @brief Second order IIR filter
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] coeffs                Points to 5 coefficients arranged as: b0, b1, b2, a1, a2
 * @param[in/out] state             Points to 4 state variables.  These are modified upon exit
 * @param[in] bShift			    b coefficients shift value
 * @param[in] aShift			    a coefficients shift value
 * @param[in] blockSize             Number of words to process
 */
void awe_vecBiquadFract24x24A56( fract32   * src, 
                int                          srcInc, 
                fract32                    * dst,
                int                          dstInc, 
                const fract32 * VEC_RESTRICT coeffs, 
                fract32 * VEC_RESTRICT       state, 
                int							 bShift,
                int							 aShift,
                int							 blockSize);

/** 
 * @brief Second order IIR filter
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] coeffs                Points to 5 coefficients arranged as: b0, b1, b2, a1, a2
 * @param[in/out] state             Points to 4 state variables.  These are modified upon exit
 * @param[in] bShift			    b coefficients shift value
 * @param[in] aShift			    a coefficients shift value
 * @param[in] blockSize             Number of words to process
 */
void awe_vecBiquadFract24x24A24( fract32   * src, 
                int                          srcInc, 
                fract32                    * dst,
                int                          dstInc, 
                const fract32 * VEC_RESTRICT coeffs, 
                fract32 * VEC_RESTRICT       state, 
                int							 bShift,
                int							 aShift,
                int							 blockSize);

/** 
 * @brief Second order IIR filter
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] coeffs                Points to 5 coefficients arranged as: b0, b1, b2, a1, a2
 * @param[in/out] state             Points to 4 state variables.  These are modified upon exit
 * @param[in]  postShift			postShift value
 * @param[in] blockSize             Number of words to process
 */
void awe_vecBiquadFract32( fract32 * src, 
		int                        srcInc, 
		fract32 * dst,
		int                        dstInc, 
		const fract32 * VEC_RESTRICT coeffs, 
		fract32 * VEC_RESTRICT       state, 
		int							postShift,
		int							blockSize);

void awe_vecBiquadFract32_single( fract32 * src, 
		fract32 * dst,
		const fract32 * VEC_RESTRICT coeffs, 
		fract32 * VEC_RESTRICT       state, 
		int							postShift,
		int							blockSize);


/** 
 * @brief Second order cascade IIR filter
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] coeffs                Points to 5 coefficients arranged as: b0, b1, b2, a1, a2
 * @param[in/out] state             Points to 4 state variables.  These are modified upon exit
 * @param[in]  postShift			points to the postShift values
 * @param[in] blockSize             Number of words to process
 * @param[in] numStages             Number of stages
 */	

void awe_vecBiquadCascadeFract32( fract32 *  src, 
		int                        srcInc, 
		fract32 *        dst,
		int                        dstInc, 
		const fract32 * VEC_RESTRICT coeffs, 
		fract32 * VEC_RESTRICT       state, 
		int *                    postShift,
		int                        blockSize,
		int                        numStages);


void awe_vecBiquadCascadeFract32_single( fract32 *  src, 
		fract32 *        dst,
		const fract32 * VEC_RESTRICT coeffs, 
		fract32 * VEC_RESTRICT       state, 
		int *                    postShift,
		int                        blockSize,
		int                        numStages);

/** 
 * @brief Logical AND of two buffers sample by sample
 * @param[in] inA                   Pointer to the first input buffer
 * @param[out] dst                  Pointer to the output buffer @param[in]
 * @param[in] mask                  Mask value
 * @param[in] blockSize             Number of words to process
 */
void awe_vecAndConstInt32(
					    unsigned int *  src, 
					   unsigned int *        dst, 
					   unsigned int                      mask,
					   int                               blockSize);

/**
 * @brief Computes the sum of the squares of a fractional buffer
 * @param[in] src                   Points to the buffer of data
 * @param[in] blockSize             Number of samples to process
 * @return                          Sum of the squares
 */
fract64 awe_vecSumSquaredFract32(
        const fract32 *  src, 
        int                        blockSize);

#if defined(WIN32) || defined(LINUX) || defined(_TMS320C6X)

/**
 * @brief Updates circular buffer curr_ptr by bufferInc( supports either positive or negative)
 * @param[1] curr_ptr              Points to the current location of circular buffer
 * @param[2] bufferInc             Increment in bytes or decrement in bytes
 * @param[3] base_ptr              Points to the Base of circular buffer
 * @param[4] L					   Length of the circular buffer
  */

int *__builtin_circptr(int *curr_ptr, int bufferInc, int *base_ptr, int	L);

#endif

/** 
 * @brief Determines the minimum value in a buffer
 * @param[in] src                   Points to the buffer of data
 * @param[in] blockSize             Number of samples to process
 * @param[out] *index               Index of the minimum value returned here
 * @return                          Minimum value
 */
fract32 awe_vecMinFract32(
        const fract32 * VEC_RESTRICT src, 
        int                        blockSize, 
        int         * VEC_RESTRICT index);

/** 
 * @brief Determines the maximum value in a buffer
 * @param[in] src                   Points to the buffer of data
 * @param[in] blockSize             Number of samples to process
 * @param[out] *index               Index of the maximum value returned here
 * @return                          Maximum value
 */
fract32 awe_vecMaxFract32(
        const fract32 * VEC_RESTRICT src, 
        int                        blockSize, 
        int         * VEC_RESTRICT index);

/**
 * @brief Mean Value for the block of samples
 * @param[in] src                   Points to the source buffer
  * @param[in] blockSize             Number of samples to process
 */
fract32 awe_vecMeanFract32(
        const fract32 * src, 
        int                        blockSize);

/* @brief RootMean Sqaue  Value for the block of samples
 * @param[in] src                   Points to the source buffer
 * @param[in] blockSize             Number of samples to process
 */
fract32 awe_vecRMSFract32(
        const fract32 * src, 
        int                        blockSize);

/* @brief Standard Deviation Value for the block of samples
 * @param[in] src                   Points to the source buffer
 * @param[in] blockSize             Number of samples to process
 */
fract32 awe_vecSDFract32(
        const fract32 * src, 
        int                        blockSize);

/* @brief Variance  Value for the block of samples
 * @param[in] src                   Points to the source buffer
 * @param[in] blockSize             Number of samples to process
 */
fract32 awe_vecVarianceFract32(
        const fract32 * src, 
        int                        blockSize);

/* @brief Average Enery  Value for the block of samples
 * @param[in] src                   Points to the source buffer
 * @param[in] blockSize             Number of samples to process
 */
fract32 awe_vecAvgEnergyFract32(
        const fract32 * src, 
        int                        blockSize); 

/** 
 * @brief Adds two buffers sample by sample
 * @param[in] inA                   Pointer to the first input buffer
 * @param[in] incA                   Increment between source samples
 * @param[in] inB                   Pointer to the second input buffer
 * @param[in] incB                   Increment between source samples
 * @param[out] out                  Pointer to the output buffer @param[in]
 * @param[out] incC                  Increment between destination samples
 * @param[in] blockSize             Number of words to process
 */
void awe_vecAdd2x1Int32(
        int *  inA, 
        int                        incA, 
        int *  inB, 
        int                        incB, 
        int       *  out, 
        int                        incC, 
        int                        blockSize);

/**
 * @brief Fills a buffer with a specified value and increment.
 * @param[out] ptr                  Pointer to the start of the buffer
 * @param[in] inc                   Pointer increment
 * @param[in] value                 Value to fill
 * @param[in] blockSize             Number of words to fill.
 */
void awe_vecFillInt32(
        int *  ptr, 
        int                  inc, 
        int					 value,
        int                  blockSize);


/** 
 * @brief Computes scaled sum and difference of 2  inputs
 * @param[in] src1                   Points to 1st input buffer
 * @param[in] src2                   Points to 2nd input buffer
 * @param[out] dst1                  Points to 1st output buffer
 * @param[out] dst2                  Points to 2nd output buffer
 * @param[in] scaleFactor           Scale factor
 * @param[in] blockSize             Number of words to process
 */
void awe_vecScaleSumDiffInt32(
         int * VEC_RESTRICT src1, 
		int *  src2,
		int * VEC_RESTRICT dst1,
		int *  dst2,
		int blockSize);

/**
 * @brief Subtracts two buffers sample by sample
 * @param[in] inA                   Pointer to the first input buffer
 * @param[in] inB                   Pointer to the second input buffer
 * @param[out] out                  Pointer to the output buffer @param[in]
 * @param[in] blockSize             Number of words to process
 */
void awe_vecSubtract2x1Int32(
        int * inA, 
        int * inB, 
        int       * out, 
        int            blockSize);


/**
 * @brief Converts a buffer of integer data to fractional data
 * @param[in] src                   Points to the source buffer
 * @param[in] srcInc                Source data pitch
 * @param[out] dst                  Points to the destination buffer
 * @param[in] dstInc                Destination data pitch
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecIntToFract32(
        const int * VEC_RESTRICT src,
        int                        srcInc, 
        fract32       * VEC_RESTRICT dst, 
        int                        dstInc, 
        int                        blockSize);

/**
 * @brief Converts a buffer of fractional data to integer data
 * @param[in] src                   Points to the source buffer
 * @param[in] srcInc                Source data pitch
 * @param[out] dst                  Points to the destination buffer
 * @param[in] dstInc                Destination data pitch
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecFract32ToInt(
        const fract32 * VEC_RESTRICT src,
        int                        srcInc, 
        int       * VEC_RESTRICT dst, 
        int                        dstInc, 
        int                        blockSize);


/**
 * @brief Mean Value for the block of samples
 * @param[in] src                   Points to the source buffer
  * @param[in] blockSize             Number of samples to process
 */
FLOAT32 awe_vecMean(
        const FLOAT32 *  src,
        int                        blockSize);

/* @brief RootMean Sqaue  Value for the block of samples
 * @param[in] src                   Points to the source buffer
 * @param[in] blockSize             Number of samples to process
 */
FLOAT32 awe_vecRMS(
        const FLOAT32 *  src,
        int                        blockSize);

/* @brief Standard Deviation Value for the block of samples
 * @param[in] src                   Points to the source buffer
 * @param[in] blockSize             Number of samples to process
 */
FLOAT32 awe_vecSD(
        const FLOAT32 *  src,
        int                        blockSize);

/* @brief Variance  Value for the block of samples
 * @param[in] src                   Points to the source buffer
 * @param[in] blockSize             Number of samples to process
 */
FLOAT32 awe_vecVariance(
        const FLOAT32 *  src,
        int                        blockSize);

/* @brief Average Enery  Value for the block of samples
 * @param[in] src                   Points to the source buffer
 * @param[in] blockSize             Number of samples to process
 */
FLOAT32 awe_vecAvgEnergy(
        const FLOAT32 *  src,
        int                        blockSize); 

/** 
 * @brief MultiplyComplexByComplex process
 * @param[in] inA              Pointer to the first input buffer
 * @param[in] incA             Increment between samples in inA
 * @param[in] inB			   Pointer to the second input buffer
 * @param[in] incB             Increment between samples in inB
 * @param[out] out             Pointer to the output buffer 
 * @param[in] incOut           Increment between samples in out
 * @param[in] blockSize        Number of words to process
 */
void awe_vecMultiplyComplexByComplex(
			  FLOAT32 *              inA,
		     int                        incA, 
		     FLOAT32 *              inB,
		     int                        incB, 
		     FLOAT32 *                    out,
		     int                        incOut, 
		     int                        blockSize);
/** 
 * @brief MultiplyRealByComplex process
 * @param[in] inReal           Pointer to the real input buffer
 * @param[in] incReal          Increment between samples in inReal
 * @param[in] inComplex		   Pointer to the complex input buffer
 * @param[in] incComplex       Increment between samples in inComplex
 * @param[out] out             Pointer to the output buffer 
 * @param[in] incOut           Increment between samples in out
 * @param[in] blockSize        Number of words to process
 */
void awe_vecMultiplyRealByComplex(
			 const FLOAT32 * VEC_RESTRICT inReal,
		     int                        incReal, 
		     const FLOAT32 *              inComplex,
		     int                        incComplex, 
		     FLOAT32 *                    out,
		     int                        incOut, 
		     int                        blockSize);
/** 
 * @brief Atan2 process
 * @param[in] src1           Pointer to the first input buffer
 * @param[in] srcInc1        Increment between samples in src1
 * @param[in] src2		     Pointer to the second input buffer
 * @param[in] srcInc2        Increment between samples in src2
 * @param[out] dst           Pointer to the output buffer 
 * @param[in] dstInc         Increment between samples in dst
 * @param[in] blockSize      Number of words to process
 */
void awe_vecAtan2(
        const FLOAT32 * VEC_RESTRICT src1,
        int                        srcInc1, 
		const FLOAT32 * VEC_RESTRICT src2,
        int                        srcInc2, 
        FLOAT32       * VEC_RESTRICT dst,
        int                        dstInc, 
        int                        blockSize);
/** 
 * @brief Magnitude process
 * @param[in] src_complex      Pointer to the complex input buffer
 * @param[in] srcInc           Increment between samples in src_complex
 * @param[out] dst_real        Pointer to the real output buffer 
 * @param[in] dstInc           Increment between samples in dst_real
 * @param[in] blockSize        Number of words to process
 */
void awe_vecMagnitude(
        const FLOAT32 * VEC_RESTRICT src_complex,
        int                        srcInc, 
		FLOAT32       * VEC_RESTRICT dst_real,
        int                        dstInc, 
        int                        blockSize);

/** 
 * @brief Magnitude process
 * @param[in] src_complex      Pointer to the complex input buffer
 * @param[in] srcInc           Increment between samples in src_complex
 * @param[out] dst_real        Pointer to the real output buffer 
 * @param[in] dstInc           Increment between samples in dst_real
 * @param[in] blockSize        Number of words to process
 */
void awe_vecMagnitudeFract32(
        const fract32 * VEC_RESTRICT src_complex,
        int                        srcInc, 
		fract32       * VEC_RESTRICT dst_real, 
        int                        dstInc, 
        int                        blockSize);
/** 
 * @brief MagnitudeSquared process
 * @param[in] src_complex      Pointer to the complex input buffer
 * @param[in] srcInc           Increment between samples in src_complex
 * @param[out] dst_real        Pointer to the real output buffer 
 * @param[in] dstInc           Increment between samples in dst_real
 * @param[in] blockSize        Number of words to process
 */
void awe_vecMagnitudeSquared(
        const FLOAT32 * VEC_RESTRICT src_complex,
        int                        srcInc, 
		FLOAT32       * VEC_RESTRICT dst_real,
        int                        dstInc, 
        int                        blockSize);
/** 
 * @brief PolarToComplex process
 * @param[in] src_magnitude     Pointer to the Polar magnitude input buffer
 * @param[in] srcInc1           Increment between samples in src_magnitude
 * @param[in] src_angle         Pointer to the Polar angle input buffer
 * @param[in] srcInc2           Increment between samples in src_angle
 * @param[out] dst_complex      Pointer to the complex output buffer 
 * @param[in] dstInc            Increment between samples in dst_complex
 * @param[in] blockSize         Number of words to process
 */
void awe_vecPolarToComplex(
        const FLOAT32 * VEC_RESTRICT src_magnitude,
        int                        srcInc1, 
		const FLOAT32 * VEC_RESTRICT src_angle,
        int                        srcInc2, 
		FLOAT32       * VEC_RESTRICT dst_complex,
        int                        dstInc, 
        int                        blockSize);
        
void awe_vecFastSin(
        const FLOAT32 * VEC_RESTRICT src,
        int                        srcInc,
		FLOAT32       * VEC_RESTRICT dst,
        int                        dstInc, 
        int                        blockSize);
        
void awe_vecFastCos(
        const FLOAT32 * VEC_RESTRICT src,
        int                        srcInc,
		FLOAT32       * VEC_RESTRICT dst,
        int                        dstInc, 
        int                        blockSize);

void awe_vecFastAtan2(
        const FLOAT32 * VEC_RESTRICT src1,
        int                        srcInc1, 
		const FLOAT32 * VEC_RESTRICT src2,
        int                        srcInc2, 
        FLOAT32       * VEC_RESTRICT dst,
        int                        dstInc, 
		FLOAT32 		* VEC_RESTRICT scratch,
        int                        blockSize);

/** 
 * @brief Bit reversal
 * @param[in] src                   Points to the source location
 * @param[in] n						2 * FFT_size */

void awe_vecBitReversal(
         fract32 *     src, 
		int								n);


/** 
 * @brief Caluclates the complex FFT of FFT_size
 * @param[in] FFT_pt						            FFT_size 
 * @param[in] Twid_table_scale						  Twiddle modifier 
 * @param[in] No_of_stages						      Number of stages
 * @param[in] src                     Points to the source location in which real and imag terms are interleaved
 * @param[in] Twiddle_Cos_table						 Cos twiddle factors 
 * @param[in] Twiddle_Sin_table						 Sin twiddle factors */
 
short awe_vecCfftFract32(int FFT_pt,
                         int Twid_table_scale,
                         int No_of_stages,
                         fract32 * VEC_RESTRICT src, 
                         fract32 * VEC_RESTRICT Twiddle_Cos_table,
                         fract32 * VEC_RESTRICT Twiddle_Sin_table);

/** 
 * @brief Caluclates the complex FFT of FFT_size
 * @param[in] src            Points to the source location in which real and imag terms are interleaved
 * @param[in] blockSize						FFT_size */
 
short awe_vecCfftFract32Wrapper(fract32 *src, int blockSize);


/**
 * @brief Adds data into a circular buffer
 * @param[in] circBuffer			Points to the base of the circular buffer
 * @param[in] L                     Length of the buffer, in words
 * @param[in/out] writeOffset       First sample is written into the circular buffer at this offset
 *                                  The function returns the updated offset here.
 * @param[in] bufferInc             Stride through the circular buffer.  Can be negative.
 *                                  Must be in the range [-L +L]
 * @param[in] src                   Points to the source buffer
 * @param[in] srcInc                Stride through the source buffer
 * @param[in] blockSize             Number of samples to process
 *
 * The function returns the final offset value which can be used for the next call.
 */

void awe_vecCircAdd(
		    FLOAT32 * VEC_RESTRICT circBuffer,
		    int	L,
		    int *writeOffset,
		    int bufferInc,
		    const FLOAT32 * VEC_RESTRICT src,
		    int srcInc,
		    int blockSize);


/**
 * @brief Adds data into a circular buffer operations on fixed point
 * @param[in] circBuffer			Points to the base of the circular buffer
 * @param[in] L                     Length of the buffer, in words
 * @param[in/out] writeOffset       First sample is written into the circular buffer at this offset
 *                                  The function returns the updated offset here.
 * @param[in] bufferInc             Stride through the circular buffer.  Can be negative.
 *                                  Must be in the range [-L +L]
 * @param[in] src                   Points to the source buffer
 * @param[in] srcInc                Stride through the source buffer
 * @param[in] blockSize             Number of samples to process
 */

void awe_vecCircAddFract32(
		    fract32 * VEC_RESTRICT circBuffer,
		    int	L,
		    int *writeOffset,
		    int bufferInc,
		    const fract32 * VEC_RESTRICT src,
		    int srcInc,
		    int blockSize);


/**
 * @brief Fills data into circular buffer 
 * @param[in] circBuffer			Points to the base of the circular buffer
 * @param[in] L                     Length of the buffer, in words
 * @param[in/out] writeOffset       First sample is written into the circular buffer at this offset
 *                                  The function returns the updated offset here.
 * @param[in] bufferInc             Stride through the circular buffer.  Can be negative.
 *                                  Must be in the range [-L +L]
 * @param[in] value                 Value to be written
 * @param[in] blockSize             Number of samples to process
 *
 * The function returns the final offset value which can be used for the next call.
 */

void awe_vecCircFill(
		    FLOAT32 * VEC_RESTRICT circBuffer,
		    int	L,
		    int *writeOffset,
		    int bufferInc,
		    FLOAT32 value,
		    int blockSize);


/**
 * @brief Fills data into circular buffer 
 * @param[in] circBuffer			Points to the base of the circular buffer
 * @param[in] L                     Length of the buffer, in words
 * @param[in/out] writeOffset       First sample is written into the circular buffer at this offset
 *                                  The function returns the updated offset here.
 * @param[in] bufferInc             Stride through the circular buffer.  Can be negative.
 *                                  Must be in the range [-L +L]
 * @param[in] value                 Value to be written
 * @param[in] blockSize             Number of samples to process
 */
  
void awe_vecCircFillFract32(
		    fract32 * VEC_RESTRICT circBuffer,
		    int	L,
		    int *writeOffset,
		    int bufferInc,
		    fract32 value,
		    int blockSize);

  FLOAT32 awe_vecAGCCompressorCore(
         FLOAT32 *  in,
		FLOAT32 		* out,
        unsigned int  blockSize, 
		FLOAT32 		* envState,
		FLOAT32 		  attackCoef,
		FLOAT32 		  decayCoef,
		FLOAT32 		  attackCoefSmoothing,
		FLOAT32         decayCoeffSmoothing,
        FLOAT32         smoothingState,
		FLOAT32 		  threshold,
		FLOAT32 		  slope,
		FLOAT32 		  gain);

  FLOAT32 awe_vecAGCLimiterCore(
         FLOAT32 *  in,
		FLOAT32 		*  out,
        unsigned int  blockSize, 
		FLOAT32 * VEC_RESTRICT envStatePtr,
		FLOAT32 		  attackCoef,
		FLOAT32 		  decayCoef,
		FLOAT32 		  threshold,
		FLOAT32         kneeDepth,
        FLOAT32         slope,
		FLOAT32 		  sharpnessFactor,
		FLOAT32 		  gain);

  void awe_vecAGCLimiterCoreFract32(fract32 * in,
								fract32 * out,
								fract32 *envState,
								fract32 attackCoef,
								fract32 decayCoef,
								fract32 threshold,
								fract32 slope,
								fract32 gain,
								fract32 kneeDepth,
								fract32 sharpnessFactor,
								int tickSize);

void awe_vecFirstOrderSmoother( 
        FLOAT32       * VEC_RESTRICT dst,
        FLOAT32       * VEC_RESTRICT currentGain,
        FLOAT32                      targetGain,
        FLOAT32                      smoothingCoeff,
        int                        blockSize);

 /** 
 * @brief Saw tooth signal generator
 * @param[out] out                   Points to the output buffer
 * @param[in] phase                  Starting phase of the signal
 * @param[in] phaseIncrement        Phase increment
 * @param[in] blockSize             Number of samples to process
 */
  FLOAT32 awe_vecSawTooth(
			FLOAT32 *  out,
			FLOAT32                phase,
			FLOAT32                phaseIncrement,
			int                  blockSize);

/** 
 * @brief Square wave signal generator
 * @param[out] out                   Points to the output buffer
 * @param[in] phase                  Starting phase of the signal
 * @param[in] phaseIncrement        Phase increment
 * @param[in] blockSize             Number of samples to process
 */
  void awe_vecSquareWaveGen(
			FLOAT32 * VEC_RESTRICT out,
			FLOAT32 *              phase,
			FLOAT32                phaseIncrement,
			int                  blockSize);
   
   
/** 
 * @brief Triangle wave signal generator
 * @param[out] out                   Points to the output buffer
 * @param[in] phase                  Starting phase of the signal
 * @param[in] phaseIncrement        Phase increment
 * @param[in] blockSize             Number of samples to process
 */
  void awe_vecTriangleWaveGen(
			FLOAT32 * VEC_RESTRICT out,
			FLOAT32 *              phase,
			FLOAT32                phaseIncrement,
			int                  blockSize);
   
   
/** 
 * @brief Saw tooth signal generator
 * @param[out] dst                   Points to the output buffer
 * @param[in/out] phase              Starting phase of the signal
 * @param[in/out] phaseInc           Current Phase increment
 * @param[in] phaseIncTarget         Target Phase increment
 * @param[in] smoothingCoeff         Phase smoothing coefficient
 * @param[in] blockSize              Number of samples to process
*/
  void awe_vecSineGenSmoothed(
        FLOAT32       * VEC_RESTRICT dst,
        FLOAT32                    * phase,
        FLOAT32       * VEC_RESTRICT phaseInc,
        FLOAT32                      phaseIncTarget,
        FLOAT32                      smoothingCoeff,
        int                        blockSize);
		
  void awe_vecSineGenSmoothedFract32(
        fract32       * VEC_RESTRICT dst, 
        fract32                    * phase, 
        fract32       * VEC_RESTRICT phaseInc, 
        fract32                      phaseIncTarget, 
        fract32                      smoothingCoeff, 
        int                        blockSize);
/** 
 * @brief Saw tooth signal generator
 * @param[out] dst                   Points to the output buffer
 * @param[in] incReal                Phase increment for real part
 * @param[in] incImag                Phase increment for imaginary part
 * @param[in/out] stateRealPtr       State pointer for real part
 * @param[in/out] stateImagPtr       State pointer for imaginary part
 * @param[in] numChannels            number of channels (1 for only sine, else for quad)
 * @param[in] blockSize              Number of samples to process
*/
  void awe_vecSineGen(
        FLOAT32       * VEC_RESTRICT dst,
        FLOAT32                      incReal,
        FLOAT32 					   incImag, 
        FLOAT32       * VEC_RESTRICT stateRealPtr,
		FLOAT32       * VEC_RESTRICT stateImagPtr,
        int                        numChannels, 
        int                        blockSize);

/**
 * @brief Cross correlation function subset
 * @param[in] a     signal a input
 * @param[in] ainc  a increment: distance between samples of a
 * @param[in] alen  samples in signal a
 * @param[in] b     signal b values...
 * @param[in] binc
 * @param[in] blen
 * @param[out] out  buffer gets output signal
 * @param[in] oinc  distance between output samples
 * @param[in] olen  number of output samples to write
 * @param[in] oskip skip this many initial output samples
 */
void awe_vecCorr(const FLOAT32 *VEC_RESTRICT _a, int _ainc, int _alen,
    const FLOAT32 *VEC_RESTRICT _b, int _binc, int _blen,
    FLOAT32 *VEC_RESTRICT _out, int _oinc, int _olen, int _oskip);

/**
 * @brief Vector convolution function subset
 * @param[in] a     signal a input
 * @param[in] ainc  a increment: distance between samples of a
 * @param[in] alen  samples in signal a
 * @param[in] b     signal b values...
 * @param[in] binc
 * @param[in] blen
 * @param[out] out  buffer gets output signal
 * @param[in] oinc  distance between output samples
 * @param[in] olen  number of output samples to write
 * @param[in] oskip skip this many initial output samples
 */
void awe_vecConv(const FLOAT32 *VEC_RESTRICT _a, int _ainc, int _alen,
    const FLOAT32 *VEC_RESTRICT _b, int _binc, int _blen,
    FLOAT32 *VEC_RESTRICT _out, int _oinc, int _olen, int _oskip);


/**
 * @brief Mixing of interleaved buffers.
 * @param[in] src             interleaved input signal
 * @param[in] numInChannels   number of channels in input signal
 * @param[out] dst            interleaved output signal
 * @param[in] numOutChannels  number of channels in the output signal
 * @param[in] gain            matrix of numInChannels x numOutChannels gain 
 *                            values
 * @param[in] blockSize       number of samples to process
 */

void awe_vecMixerDense(
    const FLOAT32 * VEC_RESTRICT src,
    int                        numInChannels, 
    FLOAT32       * VEC_RESTRICT dst,
    int                        numOutChannels, 
    const FLOAT32 * VEC_RESTRICT gain,
    int                        blockSize);

/**
 * @brief Mixing of interleaved buffers.
 * @param[in] src             interleaved input signal
 * @param[in] numInChannels   number of channels in input signal
 * @param[out] dst            interleaved output signal
 * @param[in] numOutChannels  number of channels in the output signal
 * @param[in] gain            matrix of numInChannels x numOutChannels gain 
 *                            values
 * @param[in] postShift       number of bits to shift the output by
 * @param[in] blockSize       number of samples to process
 */

void awe_vecMixerDenseFract32(
    const fract32 * VEC_RESTRICT src, 
    int                          numInChannels, 
    fract32       * VEC_RESTRICT dst, 
    int                          numOutChannels, 
    const fract32 * VEC_RESTRICT gain, 
    int                          postShift, 
    int                          blockSize);

/**
 * @brief Complex exponential on unit-interval with linear interpolation
 * @param[in] src       input signal, unit interval arguments
 * @param[in] srcinc    source increment, distance between input samples
 * @param[out] dst      output signal, gets adjacent pairs of cos/sin values
 * @param[in] dstinc    dest increment, distance between pairs of outputs
 * @param[in] bs        block size, number of samples to process
 */
void awe_vecCexpuiLinear(const FLOAT32 *_src, int _srcinc,
    FLOAT32 *_dst, int _dstinc, int _bs);

/**
 * @brief Complex exponential on unit-interval using nearest table values
 * @param[in] src       input signal, unit interval arguments
 * @param[in] srcinc    source increment, distance between input samples
 * @param[out] dst      output signal, gets adjacent pairs of cos/sin values
 * @param[in] dstinc    dest increment, distance between pairs of outputs
 * @param[in] bs        block size, number of samples to process
 */
void awe_vecCexpuiNear(const FLOAT32 *_src, int _srcinc,
    FLOAT32 *_dst, int _dstinc, int _bs);

/**
 * @brief Cosine on unit-interval with linear interpolation
 * @param[in] src       input signal, unit interval arguments
 * @param[in] srcinc    source increment, distance between input samples
 * @param[out] dst      output signal, gets cos values
 * @param[in] dstinc    dest increment, distance between pairs of outputs
 * @param[in] bs        block size, number of samples to process
 */
void awe_vecCosuiLinear(const FLOAT32 *_src, int _srcinc,
    FLOAT32 *_dst, int _dstinc, int _bs);

/**
 * @brief Cosine on unit-interval using nearest table value
 * @param[in] src       input signal, unit interval arguments
 * @param[in] srcinc    source increment, distance between input samples
 * @param[out] dst      output signal, gets cos values
 * @param[in] dstinc    dest increment, distance between pairs of outputs
 * @param[in] bs        block size, number of samples to process
 */
void awe_vecCosuiNear(const FLOAT32 *_src, int _srcinc,
    FLOAT32 *_dst, int _dstinc, int _bs);

/**
 * @brief Sine on unit-interval with linear interpolation
 * @param[in] src       input signal, unit interval arguments
 * @param[in] srcinc    source increment, distance between input samples
 * @param[out] dst      output signal, gets sin values
 * @param[in] dstinc    dest increment, distance between pairs of outputs
 * @param[in] bs        block size, number of samples to process
 */
void awe_vecSinuiLinear(const FLOAT32 *_src, int _srcinc,
    FLOAT32 *_dst, int _dstinc, int _bs);

/**
 * @brief Sine on unit-interval using nearest table value
 * @param[in] src       input signal, unit interval arguments
 * @param[in] srcinc    source increment, distance between input samples
 * @param[out] dst      output signal, gets sin values
 * @param[in] dstinc    dest increment, distance between pairs of outputs
 * @param[in] bs        block size, number of samples to process
 */
void awe_vecSinuiNear(const FLOAT32 *_src, int _srcinc,
    FLOAT32 *_dst, int _dstinc, int _bs);

/**
 * @brief Four-quadrant arctan to unit interval using nearest table value
 * @param[in] src       input signal, unit interval arguments
 * @param[in] srcinc    source increment, distance between input samples
 * @param[out] dst      output signal, gets unit-interval valued arctan
 * @param[in] dstinc    dest increment, distance between pairs of outputs
 * @param[in] bs        block size, number of samples to process
 */
void awe_vecAtan2uiNear(const FLOAT32 *_srcy, int _srcyinc,
    const FLOAT32 *_srcx, int _srcxinc, FLOAT32 *_dst, int _dstinc, int _bs);

/**
 * @brief Four-quadrant arctan to unit interval with linear interpolation
 * @param[in] src       input signal, unit interval arguments
 * @param[in] srcinc    source increment, distance between input samples
 * @param[out] dst      output signal, gets unit-interval valued arctan
 * @param[in] dstinc    dest increment, distance between pairs of outputs
 * @param[in] bs        block size, number of samples to process
 */
void awe_vecAtan2uiLinear(const FLOAT32 *_srcy, int _srcyinc,
    const FLOAT32 *_srcx, int _srcxinc, FLOAT32 *_dst, int _dstinc, int _bs);


/* vector funciton called by AGCLimiter */
void awe_vecAGCLimiterCoreFract32(fract32 * in,
								fract32 * out,
								fract32 *envState,
								fract32 attackCoef,
								fract32 decayCoef,
								fract32 threshold,
								fract32 slope,
								fract32 gain,
								fract32 kneeDepth,
								fract32 sharpnessFactor,
								int blockSize); 


/* vector functions used by the processing functions in
   subblock statistics modules
 */
/* Fract32 case */
#if OPT_HIFI2
void awe_vecSumSubblockFract32(
        fract32 * src,
        fract32 * dst,
        int       numSamples,
        int       numSubblocks,
        int       subblockSize); //subblockSize = numSamples / numSubblocks;
void awe_vecVarianceSubblockFract32(
        fract32 * src,
        fract32 * dst,
        int       numSamples,
        int       numSubblocks,
        int       subblockSize); //subblockSize = numSamples / numSubblocks;

void awe_vecSumSquaredSubblockFract32(
        fract32 * src,
        fract32 * dst,
        int       numSamples,
        int       numSubblocks,
        int       subblockSize); //subblockSize = numSamples / numSubblocks;

void awe_vecSDSubblockFract32(
        fract32 * src,
        fract32 * dst,
        int       numSamples,
        int       numSubblocks,
        int       subblockSize); //subblockSize = numSamples / numSubblocks;

void awe_vecMeanSubblockFract32(
fract32 * src,
fract32 * dst,
int       numSamples,
int       numSubblocks,
int       subblockSize); //subblockSize = numSamples / numSubblocks;

void awe_vecMaxAbsSubblockFract32(
        fract32 * src,
        fract32 * dst,
        int numSamples,
        int numSubblocks,
        int subblockSize); //subblockSize = numSamples / numSubblocks;

void awe_vecMaxSubblockFract32(
        fract32 * src,
        fract32 * dst,
        int       numSamples,
        int       numSubblocks,
        int       subblockSize);

void awe_vecRMSSubblockFract32(
fract32 * src,
fract32 * dst,
int       numSamples,
int       numSubblocks,
int       subblockSize); //subblockSize = numSamples / numSubblocks;

void awe_vecMinSubblockFract32(
fract32 * src,
fract32 * dst,
int       numSamples,
int       numSubblocks,
int       subblockSize); //subblockSize = numSamples / numSubblocks;

void awe_vecAvgEnergySubblockFract32(
        fract32 * src,
        fract32 * dst,
        int       numSamples,
        int       numSubblocks,
        int       subblockSize); //subblockSize = numSamples / numSubblocks;

#else
void awe_vecSumSubblockFract32(
        fract32 * src, 
        fract32 * dst,
        int numSamples,
        int numSubblocks);

void awe_vecVarianceSubblockFract32(
        fract32 * src, 
        fract32 * dst,
        int numSamples,
        int numSubblocks);

void awe_vecSumSquaredSubblockFract32(
        fract32 * src,
        fract32 * dst,
        int numSamples,
        int numSubblocks);

void awe_vecSDSubblockFract32(
        fract32 * src,
        fract32 * dst,
        int numSamples,
        int numSubblocks);

void awe_vecMeanSubblockFract32(
        fract32 * src,
        fract32 * dst,
        int numSamples,
        int numSubblocks);

void awe_vecMaxAbsSubblockFract32(
        fract32 * src,
        fract32 * dst,
        int numSamples,
        int numSubblocks);

void awe_vecMaxSubblockFract32(
        fract32 * src,
        fract32 * dst,
        int numSamples,
        int numSubblocks);

void awe_vecRMSSubblockFract32(
        fract32 * src, 
        fract32 * dst,
        int numSamples,
        int numSubblocks);

void awe_vecMinSubblockFract32(
        fract32 * src, 
        fract32 * dst,
        int numSamples,
        int numSubblocks);

void awe_vecAvgEnergySubblockFract32(
        fract32 * src,
        fract32 * dst,
        int numSamples,
        int numSubblocks);
#endif



/* for Float32 case */
void awe_vecSumSubblock(
        FLOAT32 * src, 
        FLOAT32 * dst,
        int numSamples,
        int numSubblocks);

void awe_vecVarianceSubblock(
        FLOAT32 * src, 
        FLOAT32 * dst,
        int numSamples,
        int numSubblocks);

void awe_vecMaxSubblock(
        FLOAT32 * src, 
        FLOAT32 * dst,
        int numSamples,
        int numSubblocks);

void awe_vecSumSquaredSubblock(
        FLOAT32 * src, 
        FLOAT32 * dst,
        int numSamples,
        int numSubblocks);

void awe_vecSDSubblock(
        FLOAT32 * src, 
        FLOAT32 * dst,
        int numSamples,
        int numSubblocks);

void awe_vecMeanSubblock(
        FLOAT32 * src, 
        FLOAT32 * dst,
        int numSamples,
        int numSubblocks);

void awe_vecMaxAbsSubblock(
        FLOAT32 * src, 
        FLOAT32 * dst,
        int numSamples,
        int numSubblocks);

void awe_vecRMSSubblock(
        FLOAT32 * src, 
        FLOAT32 * dst,
        int numSamples,
        int numSubblocks);

void awe_vecMinSubblock(
        FLOAT32 * src, 
        FLOAT32 * dst,
        int numSamples,
        int numSubblocks);

void awe_vecAvgEnergySubblock(
        FLOAT32 * src, 
        FLOAT32 * dst,
        int numSamples,
        int numSubblocks);


// High Precision Filters

/** 
 * @brief Second order IIR filter using high precision implementation.  Single channel.
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] coeffs                Points to 5 coefficients arranged as: Fb, Gaa, Gab, K, Fa
 * @param[in/out] state             Points to 2 state variables.  These are modified upon exit
 * @param[in] blockSize             Number of words to process
 */
void awe_vecBiquadHP(const FLOAT32 * src,
		int                        srcInc, 
		FLOAT32                    * dst,
		int                        dstInc, 
		const FLOAT32 * VEC_RESTRICT coeffs,
		FLOAT32 * VEC_RESTRICT       state,
        int   blockSize				                
		);

/** 
 * @brief Second order IIR filter using high precision implementation.  Stereo.
 * @param[in] src                   Points to the source location.  Interleaved L/R.
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination
 *                                  location. Interleaved L/R.
 * @param[in] dstInc                Increment between destination samples
 * @param[in] coeffs                Points to 5 coefficients arranged as: Fb, Gaa, Gab, K, Fa
 * @param[in/out] state             Points to 4 state variables.  These are modified upon exit
 * @param[in] blockSize             Number of words to process
 */

void awe_vecBiquadHP_2ch(const FLOAT32 * src,
 		     int                        srcInc, 
		     FLOAT32                    * dst,
		     int                        dstInc, 
		     const FLOAT32 * VEC_RESTRICT coeffs,
		     FLOAT32 * VEC_RESTRICT       state,
             int   blockSize				                
    );

/** 
 * @brief Second order IIR Cascade filter with high precision implementation
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] coeffs                Points to (5*number of stages) coefficients arranged as: Fb1, Gaa1, Gab1, K1, Fa1, Fb2, Gaa2, Gab2, K2, Fa2,.... Fbn, Gaan, Gabn, Kn, Fan 
 * @param[in/out] state             Points to (2*number of stages) state variables.  These are modified upon exit
 * @param[in] nStages				Number of the cascade sections
 * @param[in] blockSize             Number of words to process
 */
void awe_vecBiquadCascadeHP(FLOAT32 *  src,
		int                        srcInc, 
		FLOAT32 *        dst,
		int                        dstInc, 
		const FLOAT32 * VEC_RESTRICT coeffs,
		FLOAT32 * VEC_RESTRICT      state,
		int						   nStages,
		int                        blockSize);
		
/** 
 * @brief Second order IIR Cascade filter with the SIMD version on SHARC processor
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] coeffs                Points to (5*number of stages) coefficients arranged as: Fb1, Gaa1, Gab1, K1, Fa1, Fb2, Gaa2, Gab2, K2, Fa2,.... Fbn, Gaan, Gabn, Kn, Fan 
 * @param[in/out] state             Points to (2*number of stages) state variables.  These are modified upon exit
 * @param[in] nStages				Number of the cascade sections
 * @param[in] blockSize             Number of words to process
 */

void awe_vecBiquadCascadeHP_2ch(FLOAT32 *  src,
		int                        srcInc, 
		FLOAT32 *                  dst,
		int                        dstInc, 
		const FLOAT32 * VEC_RESTRICT coeffs,
		FLOAT32 * VEC_RESTRICT      state,
		int						   nStages,
		int                        blockSize);

/** 
 * @brief In place quicksort
 * @param[in] arr                   Points to the array to be sorted
 * @param[in] int					Number of elements to be sorted
 */
void awe_vecSort(FLOAT32 *arr, int elements);


/** 
 * @brief Unwrap phase radians
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source samples
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination samples
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecUnwrap( FLOAT32 * src,
                    int       srcInc, 
                    FLOAT32 * dst,
                    int       dstInc, 
                    int       blockSize);


  /** 
 * @brief Copies a buffer of samples with increments on the source and
 * destination pointers.
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment for the source pointer
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment for the destination pointer
 * @param[in] blockSize             Number of words to copy
 */

static VEC_INLINE void awe_vecCopyFract32( fract32 *  src,
					INT32 srcInc, 
					fract32 *  dst, 
					INT32 dstInc, 
					INT32 blockSize)
{
  awe_vecCopy32( (INT32 *) src, srcInc, (INT32 *) dst, dstInc, blockSize);
}

/** 
 * @brief Copies a buffer of samples with increments on the source and
 * destination pointers.
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment for the source pointer
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment for the destination pointer
 * @param[in] blockSize             Number of words to copy
 */
static VEC_INLINE void awe_vecCopyInt32( INT32 *  src,
				      INT32 srcInc, 
				      INT32 *  dst, 
				      INT32 dstInc, 
				      INT32 blockSize)
{
  awe_vecCopy32( (INT32 *) src, srcInc, (INT32 *) dst, dstInc, blockSize);
}

void awe_vecBiquadCascade32x32x64(FLOAT32 *                  src,
                                int						     srcInc,
                                FLOAT32 * 				     dst,
                                int						     dstInc,
                                const fract32 * VEC_RESTRICT coeffs,
                                fract32 * VEC_RESTRICT	     inState,
                                int	*	                     inStateIndexPtr,
                                fract32 * VEC_RESTRICT	     outState,
                                int	*	                     outStateIndexPtr,
                                int						     blockSize,
                                int							 numStages);

void awe_vecBiquad_DF1( FLOAT32 *  src,
		int                        srcInc, 
		FLOAT32 *                  dst,
		int                        dstInc, 
		const FLOAT32 * VEC_RESTRICT coeffs,
		FLOAT32 * VEC_RESTRICT       state,
		int                        blockSize);


// ***************** DEPRECATED ***************************************************************
#if 0

/**
 * @brief SHARC Only. Reads data from a circular buffer and writes circularly.
 * @param[in] circBuffer			Points to the base of the circular buffer
 * @param[in] L                     Length of the buffer, in words
 * @param[in,out] readOffset        First sample is read from the circular buffer at this offset
 *                                  The updated offset is also returned.
 * @param[in] bufferInc             Stride through the circular buffer.  Can be negative.
 *                                  Must be in the range [-L +L]
 * @param[in] dst                   Points to the where the output will be written 
 * @param[in] dst_base              Points to the base of the dst cirular buffer
 * @param[in] dst_length            Length of the cirular buffer
 * @param[in] dstInc                Stride through the output buffer
 * @param[in] blockSize             Number of samples to process
 */
  void awe_VecCircReadCirc(
		   int * VEC_RESTRICT circBuffer,
		   int	L,
		   int *readOffset,
		   int bufferInc,
		   int * VEC_RESTRICT dst,
		   int * dst_base,
		   int dst_length,
		   int dstInc,
		   int blockSize);


  /**
 * @brief SHARC Only. Reads data from a circular buffer and writes circularly.
 * @param[in] circBuffer			Points to the base of the circular buffer
 * @param[in] L                     Length of the buffer, in words
 * @param[in,out] readOffset        First sample is read from the circular buffer at this offset
 *                                  The updated offset is also returned.
 *                                  Must be in the range [-L +L]
 * @param[in] dst                   Points to the where the output will be written 
 * @param[in] dst_base              Points to the base of the dst cirular buffer
 * @param[in] dst_length            Length of the cirular buffer
 * @param[in] blockSize             Number of samples to process
 */ 
  void awe_VecCircReadCirc_2ch(
		   int * VEC_RESTRICT circBuffer,
		   int	L,
		   int *readOffset,
		   int * VEC_RESTRICT dst,
		   int * dst_base,
		   int dst_length,
		   int blockSize);

  /**
 * @brief SHARC Only. Computes the absolute value of a buffer of FLOAT32 ing-point data
 * @param[in] src                   Points to the source buffer
 * @param[out] dst                  Points to the destination buffer
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecAbs_2ch(
        FLOAT32 *  src,
        FLOAT32 *  dst,
        int        blockSize);


/** 
 * @brief BLACKFIN Only. ACCUMULATE
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source values
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination values
 * @param[in] fmt					Input format
 * @param[out] outBlockExp			Number of bits to shift after the fractional multiply.
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecAccumulateFract32(
         fract32 *  src, 
        int                          srcInc, 
        fract32       *  dst, 
        int                          dstInc,
        short						*postShift,
	    int                          blockSize);

/** 
 * @brief SHARC Only. Adds two buffers sample by sample
 * @param[in] inA                   Pointer to the first input buffer
 * @param[in] inB                   Pointer to the second input buffer
 * @param[out] out                  Pointer to the output buffer @param[in]
 * @param[in] blockSize             Number of words to process
 */
void awe_vecAdd2x1_2ch(
        FLOAT32 *  inA,
        FLOAT32 *  inB,
        FLOAT32 *  out,
        int     blockSize);
		
void awe_vecBiquad_DF1_1ch_SIMD4( FLOAT32 *  pSrc,
		int                        srcInc, 
		FLOAT32 *                  pDst,
		int                        dstInc, 
		const FLOAT32 * VEC_RESTRICT pb0,
		FLOAT32 * VEC_RESTRICT      state,
		int                        blockSize);
		
void awe_vecBiquad_DF1_2ch_SIMD4( FLOAT32 *  pSrc,
		int                        srcInc, 
		FLOAT32 *                  pDst,
		int                        dstInc, 
		const FLOAT32 * VEC_RESTRICT pb0,
		FLOAT32 * VEC_RESTRICT       state,
		int                        blockSize);

void awe_vecBiquad_DF1_4ch(FLOAT32 * pSrc,
		int                        srcInc, 
		FLOAT32 *				       pDst,
		int                        dstInc, 
		const FLOAT32 *			   pb0,
		FLOAT32 *				       state,
		int                        blockSize);

void awe_vecBiquadCascade_DF1_1ch_SIMD4( FLOAT32 *  pSrc,
		int                        srcInc, 
		FLOAT32 *                  pDst,
		int                        dstInc, 
		const FLOAT32 * VEC_RESTRICT pb0,
		FLOAT32 * VEC_RESTRICT      state,
		int						   nStages,
		int                        blockSize);

void awe_vecBiquadCascade_DF1_2ch_SIMD4( FLOAT32 *  pSrc,
		int                        srcInc, 
		FLOAT32 *                  pDst,
		int                        dstInc, 
		const FLOAT32 * VEC_RESTRICT pb0,
		FLOAT32 * VEC_RESTRICT      state,
		int						   nStages,
		int                        blockSize);
		
void awe_vecBiquadCascade_DF1_4ch_SIMD4( FLOAT32 *  pSrc,
		int                        srcInc, 
		FLOAT32 *                  pDst,
		int                        dstInc, 
		const FLOAT32 * VEC_RESTRICT pb0,
		FLOAT32 * VEC_RESTRICT      state,
		int						   nStages,
		int                        blockSize);
		
void awe_vecBiquadCascadeN_DF1_2ch_SIMD4( FLOAT32 *  pSrc,
		int                        srcInc, 
		FLOAT32 *                  pDst,
		int                        dstInc, 
		const FLOAT32 * VEC_RESTRICT pb0,
		FLOAT32 * VEC_RESTRICT      state,
		int						   nStages,
		int                        blockSize);
		
void awe_vecBiquadCascadeN_DF1_4ch_SIMD4( FLOAT32 *  pSrc,
		int                        srcInc, 
		FLOAT32 *                  pDst,
		int                        dstInc, 
		const FLOAT32 * VEC_RESTRICT pb0,
		FLOAT32 * VEC_RESTRICT      state,
		int						   nStages,
		int                        blockSize);
        
void awe_vecBlockScale(FLOAT32 *, FLOAT32 *, FLOAT32 *, unsigned int, int);

										
/**
 * @brief CFFT optimized function
 * @param[in/out] Realdata        Array of complex interleaved values
 * @param[in/out] Imagdata        Array of complex interleaved values
 * @param[in] scratch buffer      Scratch array
 * @param[in] scratch buffer      Scratch array
 * @param[in] Twiddle cos Tab 	  Array of complex cos twiddle factor values
 * @param[in] Twiddle sin Tab 	  Array of complex sin twiddle factor values
 * @param[in] blockSize           Number of samples.
 */										
void awe_vecCfftFast(FLOAT32 *input_r, FLOAT32 *input_i,
      FLOAT32 *temp_r, FLOAT32 *temp_i,
      FLOAT32 *twid_r, FLOAT32 *twid_i, int blockSize);

/**
 * @brief SHARC Only. Forward FFT after modulation and inverse FFT before demodulation.
 * @param[in] Object pointer 	  Pointer to fft structure
 * @param[in/out] Realdata               Array of complex interleaved values
 * @param[in/out] Imagdata               Array of complex interleaved values
 * @param[in] n                     Number of samples.
 * @param[in] Realscratch               Array of complex interleaved values
 * @param[in] Imagscratch               Array of complex interleaved values
 * @param[in] isInterleaveZero		Interleave sample is zero or nor if 1 interleave is zero.
 * @param[in] dir                   Transform direction.  =1 for forward.  =-1 for inverse.
 */
void awe_vecCfftModAsm(FLOAT32 *objectPtr,
			FLOAT32 * VEC_RESTRICT    srcReal,
			FLOAT32 * VEC_RESTRICT    srcImag,
			int		n,
			FLOAT32 * VEC_RESTRICT    scratchRealPtr,
			FLOAT32 * VEC_RESTRICT    scratchImagPtr,
			int	 isInterleave,
			int		flag,
			FLOAT32 * VEC_RESTRICT cosTab,
			FLOAT32 * VEC_RESTRICT sinTab,
			FLOAT32 * VEC_RESTRICT modulationTab);
   
void awe_vecCfftOpt(FLOAT32 *input, FLOAT32 *temp,
      FLOAT32 *output, FLOAT32 *twid, int twidStride, int blockSize);

/**
 * @brief CIFFT optimized function
 * @param[in/out] Realdata        Array of complex interleaved values
 * @param[in/out] Imagdata        Array of complex interleaved values
 * @param[in] scratch buffer      Scratch array
 * @param[in] scratch buffer      Scratch array
 * @param[in] Twiddle cos Tab 	  Array of complex cos twiddle factor values
 * @param[in] Twiddle sin Tab 	  Array of complex sin twiddle factor values
 * @param[in] blockSize           Number of samples.
 */										
void awe_vecCifftFast(FLOAT32 *input_r, FLOAT32 *input_i,
      FLOAT32 *temp_r, FLOAT32 *temp_i,
      FLOAT32 *twid_r, FLOAT32 *twid_i, int blockSize);
      
void awe_vecCifftOpt(FLOAT32 *input, FLOAT32 *temp,
      FLOAT32 *output, FLOAT32 *twid, int twidStride, int blockSize);

/**
 * @brief SHARC Only. Reads data from a circular buffer
 * @param[in] circBuffer			Points to the base of the circular buffer
 * @param[in] L                     Length of the buffer, in words
 * @param[in,out] readOffset        First sample is read from the circular buffer at this offset
 *                                  The updated offset is also returned.
 * @param[in] bufferInc             Stride through the circular buffer.  Can be negative.
 *                                  Must be in the range [-L +L]
 * @param[in] dst                   Points to the where the output will be written
 * @param[in] dstInc                Stride through the output buffer
 * @param[in] blockSize             Number of samples to process
 */
  void awe_vecCircReadNC(
		   int * VEC_RESTRICT circBuffer,
		   int	L,
		   int *readOffset,
		   int bufferInc,
		   int * VEC_RESTRICT dst,
		   int dstInc,
		   int blockSize);

  /**
 * @brief SHARC Only. Reads data from a circular buffer
 * @param[in] circBuffer			Points to the base of the circular buffer
 * @param[in] L                     Length of the buffer, in words
 * @param[in,out] readOffset        First sample is read from the circular buffer at this offset
 *                                  The updated offset is also returned.
 *                                  Must be in the range [-L +L]
 * @param[in] dst                   Points to the where the output will be written
 * @param[in] blockSize             Number of samples to process
 */
  
  void awe_vecCircRead_2ch(
		   int * VEC_RESTRICT circBuffer,
		   int	L,
		   int *readOffset,
		   int * VEC_RESTRICT dst,
		   int blockSize);

  /**
 * @brief SHARC Only. Writes data into a circular buffer
 * @param[in] circBuffer			Points to the base of the circular buffer
 * @param[in] L                     Length of the buffer, in words
 * @param[in/out] writeOffset       First sample is written into the circular buffer at this offset
 *                                  The function returns the updated offset here.
 *                                  Must be in the range [-L +L]
 * @param[in] src                   Points to the source buffer
 * @param[in] blockSize             Number of samples to process
 */
  void awe_vecCircWrite_2ch(
		    int * VEC_RESTRICT circBuffer,
		    int	L,
		    int *writeOffset,
		    const int * VEC_RESTRICT src,
		    int blockSize);

/** 
 * @brief Copies a buffer of samples with increments on the source and
 * destination pointers.
 * @param[in] src                   Points to the source location
 * @param[out] dst                  Points to the destination location
 * @param[in] blockSize             Number of words to copy
 */
 
 void awe_vecCopy_2ch(FLOAT32 *  src,
		   FLOAT32 *  dst,
		   int blockSize);

 /**
 * @brief DoublePrecision Multiplication
 * @param[in] srcA                   Points to the source location
 * @param[in] srcAInc                Increment between source values
 * @param[in] srcB                   Points to the source location
 * @param[in] srcBInc                Increment between source values
 * @param[out] dst                   Points to the destination location
 * @param[in] dstInc                 Increment between destination values
 * @param[in] blockSize              Number of samples to process
 */
void awe_vecDoublePrecisionFract32(
        fract32 *  srcA, 
        int        srcAInc, 
        fract32 *  srcB, 
        int        srcBInc,
        fract32 *  dst, 
        int        dstInc,
	    int        blockSize);

/**
 * @brief Fills a buffer with a specified value and increment.
 * @param[out] ptr                  Pointer to the start of the buffer
 * @param[in] value                 Value to fill
 * @param[in] blockSize             Number of words to fill.
 */
void awe_vecFill_2ch(
        FLOAT32 * ptr,
        FLOAT32 value,
        int blockSize);

/** 
 * @brief Converts FLOAT32 values from input buffer to fractional values in output buffer
 * @param[in] src                   Points to the source location
 * @param[out] dst                  Points to the destination location
 * @param[in] blockSize             Number of words to process
 */
void awe_vecFloatToFract32_2ch(
        const FLOAT32 * VEC_RESTRICT src,
        fract32 * VEC_RESTRICT dst, 
        int blockSize);


void awe_vecFloatToFract32_asm(
        const FLOAT32 * VEC_RESTRICT src,
        int                        srcInc, 
        fract32         * VEC_RESTRICT dst, 
        int                        dstInc, 
        int                        blockSize);
        
/** 
 * @brief Converts fractional values from input buffer to  FLOAT32 values in output buffer
 * @param[in] src                   Points to the source location
 * @param[out] dst                  Points to the destination location
 * @param[in] blockSize             Number of words to process
 */
void awe_vecFract32ToFloat_2ch(
        const fract32 * VEC_RESTRICT src,
        FLOAT32       * VEC_RESTRICT dst,
        int           blockSize);

/** 
 * @brief Copies integer samples from input buffer to output buffer
 * @param[in] src                   Pointer to the first input buffer
 * @param[in] srcInc                Increment between source values
 * @param[out] dst                  Pointer to the output buffer 
 * @param[in] dstInc                Increment between destination values
 * @param[in] blockSize             Number of words to process
 */
void awe_vecIntCopy(
        int *  src,
        int                        srcInc,
        int       *  dst,
        int                        dstInc,
        int                        blockSize);

/**
 * @brief Multiplies two buffers sample by sample
 * @param[in] inA                   Pointer to the first input buffer
 * @param[in] inB                   Pointer to the second input buffer
 * @param[out] out                  Pointer to the output buffer @param[in]
 * @param[in] blockSize             Number of words to process
 */

void awe_vecMultiply2x1_2ch(
		     FLOAT32 *  inA,
		     FLOAT32 *  inB,
		     FLOAT32 *  out,
		     int        blockSize);

/** 
 * @brief power
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source values
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination values
 * @param[in] fmt					Input format
 * @param[out] postShift			Number of bits to shift after the fractional multiply.
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecPowerFract32(
         fract32 *  src, 
        int                          srcInc, 
        fract32       *  dst, 
        int                          dstInc,
        int 						 fmt,
        int							 *postShift,
	    int                          blockSize);

/** 
 * @brief Scale and sum two buffers
 * @param[in] srcA                  Points to the first source buffer
 * @param[in] scaleA                Scale factor for the first buffer
 * @param[in] srcB                  Points to the second source buffer
 * @param[in] scaleB                Scale factor for the second buffer
 * @param[out] dst                  Destination buffer.
 * @param[in] blockSize             Number of words to process
 */
void awe_vecScale2x1_2ch(
        FLOAT32 *  srcA,
        FLOAT32    scaleA,
        FLOAT32 *  srcB,
        FLOAT32    scaleB,
        FLOAT32 *  dst,
        int        blockSize);

/**
 * @brief Smoothly scales a buffer and adds it to another buffer
 * @param[in] src                   Points to the source location
 * @param[out] dst                  Points to the destination (accumulation) location
 * @param[in,out] *currentAmp       Starting amplitude for the smoothing
 *                                  operation. This is returned updated at the 
 *                                  end of the call.
 * @param[in] targetAmp             Final amplitude which the smoothing operation
 *                                  approaches
 * @param[in] smoothingCoeff        Coefficient which controls the rate of the smoothing
 *                                  operation.
 * @param[in] blockSize             Number of words to process
 */
void awe_vecScaleAddSmooth_2ch(
        FLOAT32 *  src,
        int        srcInc, 
        FLOAT32 *  dst,
        int        dstInc, 
        FLOAT32 *  currentAmp,
        FLOAT32    targetAmp,
        FLOAT32    smoothingCoeff,
        int        blockSize);
               
/**
 * @brief Scales a buffer and adds the result to another buffer
 * @param[in] src                   Points to the source location
 * @param[out] dst                  Points to the destination accumulation buffer
 * @param[in] K                     Scale factor for the src buffer
 * @param[in] blockSize             Number of words to process
 */
void awe_vecScaleAdd_2ch(
        FLOAT32 *  src,
        FLOAT32 *  dst,
        FLOAT32    K,
        int        blockSize);
       
/** 
 * @brief Scales and offsets a buffer
 * @param[in] src                   Points to the source location
 * @param[out] dst                  Points to the destination location
 * @param[in] K                     Scale factor
 * @param[in] offset                Offset value
 * @param[in] blockSize             Number of words to process
 */
void awe_vecScaleOffset_2ch(
        FLOAT32 *  src,
        FLOAT32 *  dst,
        FLOAT32    K,
        FLOAT32    offset,
        int        blockSize);
        
/**
 * @brief Smoothly scales a buffer
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source values
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination values
 * @param[in] currentAmp            Starting amplitude for the smoothing operation.
 *                                  This is returned updated at the end of the call.
 * @param[in,out] targetAmp         Final amplitude which the smoothing operation
 *                                  approaches
 * @param[in] smoothingCoeff        Coefficient which controls the rate of the smoothing
 *                                  operation.
 * @param[in] blockSize             Number of words to process
 */
void awe_vecScaleSmooth_2ch(
        FLOAT32 *  src,
        int        srcInc, 
        FLOAT32 *  dst,
        int        dstInc, 
        FLOAT32 *  currentAmp,
        FLOAT32    targetAmp,
        FLOAT32    smoothingCoeff,
        int        blockSize);


/** 
 * @brief Computes scaled sum and difference of 2  inputs
 * @param[in] src1                   Points to 1st input buffer
 * @param[in] src2                   Points to 2nd input buffer
 * @param[out] dst1                  Points to 1st output buffer
 * @param[out] dst2                  Points to 2nd output buffer
 * @param[in] scaleFactor           Scale factor
 * @param[in] blockSize             Number of words to process
 */
void awe_vecScaleSumDiff_2ch(
        FLOAT32 * VEC_RESTRICT src1,
		FLOAT32 * src2,
		FLOAT32 * VEC_RESTRICT dst1,
		FLOAT32 * dst2,
		int       blockSize);

/** 
 * @brief Copies and scales a buffer
 * @param[in] src                   Points to the source location
 * @param[out] dst                  Points to the destination location
 * @param[in] K                     Scale factor
 * @param[in] numSamples            Number of words to process
 */
void awe_vecScale_2ch(
        FLOAT32 *  src,
        FLOAT32 *  dst,
        FLOAT32    K,
        int        numSamples);
	    
/** 
 * @brief BLACKFIN Only. SQRT
 * @param[in] src                   Points to the source location
 * @param[in] srcInc                Increment between source values
 * @param[out] dst                  Points to the destination location
 * @param[in] dstInc                Increment between destination values
 * @param[in] fmt					Input format
 * @param[out] postShift			Number of bits to shift after the fractional multiply.
 * @param[in] blockSize             Number of samples to process
 */
void awe_vecSqrtFract32ASM(
        fract32 *   src, 
        int         srcInc, 
        fract32 *   dst, 
        int         dstInc,
        int 		fmt,
        int	*       postShift,
	    int         blockSize);

/**
 * @brief Subtracts two buffers sample by sample
 * @param[in] inA                   Pointer to the first input buffer
 * @param[in] inB                   Pointer to the second input buffer
 * @param[out] out                  Pointer to the output buffer @param[in]
 * @param[in] blockSize             Number of words to process
 */
void awe_vecSubtract2x1_2ch(
        FLOAT32 *   inA,
        FLOAT32 *   inB,
        FLOAT32 *   out,
        int         blockSize);

/**
 * @brief CFFT function
 * @param[in] Object pointer 	  Pointer to fft structure
 */
void awe_vec_Cfft_Calc(FLOAT32  *objectPtr);	// pointer to fft object

/**
 * @brief CFFT init function
 * @param[in] Object pointer 	  Pointer to fft structure
 * @param[in] n                   Number of samples.
 * @param[in/out] Realdata        Array of complex interleaved values
 * @param[in/out] Imagdata        Array of complex interleaved values
 * @param[in] Twiddle cos Tab 	  Array of complex cos twiddle factor values
 * @param[in] Twiddle sin Tab 	  Array of complex sin twiddle factor values
 * @param[in] scratch buffer      Scratch array
 * @param[in] scratch buffer      Scratch array
 */
void awe_vec_Cfft_Calc_init(FLOAT32 *objectPtr,	// pointer to fft object
			int n,				// size of fft, must be a power of 2
			FLOAT32 * VEC_RESTRICT    srcReal,	// pointer to real input data of size N
			FLOAT32 * VEC_RESTRICT    srcImag,	// pointer to imag input data of size N
			FLOAT32 * VEC_RESTRICT	cosTab,		// pointer to real twiddle array of size N/2
			FLOAT32 * VEC_RESTRICT	sinTab,		// pointer to imag twiddle array of size N/2
			FLOAT32 * VEC_RESTRICT	scratchRealPtr,				// pointer to real temp array of size N
			FLOAT32 * VEC_RESTRICT	scratchImagPtr);	// pointer to imag temp array of size N

/**
 * @brief Complex Multiplication and Addition
 * @param[in] Realdata               Array of complex interleaved values
 * @param[in] Imagdata               Array of complex interleaved values
 * @param[in] Real coefficients          Array of Real Coeffs
 * @param[in] n                     Number of samples.
 * @param[in/out] Destinatio real	Array of output real
 * @param[in/out] Destination imag	Array of output imag
 * @param[in] Imag Coefficients		Array of Imag Coeffs
 */
void awe_vec_Complex_Multiply_Add( FLOAT32 *  srcReal,
			FLOAT32 *     srcImag,
			FLOAT32 * VEC_RESTRICT    coeffreal,
			int n,
			FLOAT32 *     dstReal,
			FLOAT32 *     dstImag,
			FLOAT32 * VEC_RESTRICT    coeffImag);

#endif


/* Leave C Naming Convention. */
#ifdef __cplusplus
}
#endif /* __cplusplus */



#endif // _GENERIC_VECTOR_H

/**
 * @}
 * End of file
 */


