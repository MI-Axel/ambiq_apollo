/******************************* SOURCE LICENSE *********************************
Copyright (c) 2019 MicroModeler.

A non-exclusive, nontransferable, perpetual, royalty-free license is granted to the Licensee to 
use the following Information for academic, non-profit, or government-sponsored research purposes.
Use of the following Information under this License is restricted to NON-COMMERCIAL PURPOSES ONLY.
Commercial use of the following Information requires a separately executed written license agreement.

This Information is distributed WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

******************************* END OF LICENSE *********************************/

// A commercial license for MicroModeler DSP can be obtained at http://www.micromodeler.com/launch.jsp

#include "digital_filter.h"

#include <stdlib.h> // For malloc/free
#include <string.h> // For memset

float high_pass_filter_coefficients[5] = 
{
// Scaled for floating point

    0.9565432255568771, -1.9130864511137542, 0.9565432255568771, 1.9111970674260734, -0.9149758348014341// b0, b1, b2, a1, a2

};


high_pass_filterType *high_pass_filter_create( void )
{
	high_pass_filterType *result = (high_pass_filterType *)malloc( sizeof( high_pass_filterType ) );	// Allocate memory for the object
	high_pass_filter_init( result );											// Initialize it
	return result;																// Return the result
}

void high_pass_filter_destroy( high_pass_filterType *pObject )
{
	free( pObject );
}

 void high_pass_filter_init( high_pass_filterType * pThis )
{
	high_pass_filter_reset( pThis );

}

 void high_pass_filter_reset( high_pass_filterType * pThis )
{
	memset( &pThis->state, 0, sizeof( pThis->state ) ); // Reset state to 0
	pThis->output = 0;									// Reset output

}

 int high_pass_filter_filterBlock( high_pass_filterType * pThis, float * pInput, float * pOutput, unsigned int count )
{
	high_pass_filter_executionState executionState;          // The executionState structure holds call data, minimizing stack reads and writes 
	if( ! count ) return 0;                         // If there are no input samples, return immediately
	executionState.pInput = pInput;                 // Pointers to the input and output buffers that each call to filterBiquad() will use
	executionState.pOutput = pOutput;               // - pInput and pOutput can be equal, allowing reuse of the same memory.
	executionState.count = count;                   // The number of samples to be processed
	executionState.pState = pThis->state;                   // Pointer to the biquad's internal state and coefficients. 
	executionState.pCoefficients = high_pass_filter_coefficients;    // Each call to filterBiquad() will advance pState and pCoefficients to the next biquad

	// The 1st call to filter1_filterBiquad() reads from the caller supplied input buffer and writes to the output buffer.
	// The remaining calls to filterBiquad() recycle the same output buffer, so that multiple intermediate buffers are not required.

	high_pass_filter_filterBiquad( &executionState );		// Run biquad #0
	executionState.pInput = executionState.pOutput;         // The remaining biquads will now re-use the same output buffer.

	// At this point, the caller-supplied output buffer will contain the filtered samples and the input buffer will contain the unmodified input samples.  
	return count;		// Return the number of samples processed, the same as the number of input samples

}

 void high_pass_filter_filterBiquad( high_pass_filter_executionState * pExecState )
{

	// Read state variables
	float x0;
	float x1 = pExecState->pState[0];
	float x2 = pExecState->pState[1];
	float y1 = pExecState->pState[2];
	float y2 = pExecState->pState[3];

	// Read coefficients into work registers
	float b0 = *(pExecState->pCoefficients++);
	float b1 = *(pExecState->pCoefficients++);
	float b2 = *(pExecState->pCoefficients++);
	float a1 = *(pExecState->pCoefficients++);
	float a2 = *(pExecState->pCoefficients++);

	// Read source and target pointers
	float *pInput  = pExecState->pInput;
	float *pOutput = pExecState->pOutput;
	short count = pExecState->count;
	float accumulator;

	while( count-- )
	{
		x0 = *(pInput++);
	
		accumulator  = x2 * b2;
		accumulator += x1 * b1;
		accumulator += x0 * b0;
	
		x2 = x1;		// Shuffle left history buffer
		x1 = x0;
	
		accumulator += y2 * a2;
		accumulator += y1 * a1;
	
		y2 = y1;		// Shuffle right history buffer
		y1 = accumulator ;
	
		*(pOutput++) = accumulator ;
	}

	*(pExecState->pState++) = x1;
	*(pExecState->pState++) = x2;
	*(pExecState->pState++) = y1;
	*(pExecState->pState++) = y2;


}



