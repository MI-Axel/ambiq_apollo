awe_modSbBeamformerInstance *S = (awe_modSbBeamformerInstance *) pInstance;
WireInstance **pWires = ClassModule_GetWires(S);
INT32 numBeams = S->numBeams;
FLOAT32 *dst, *src;
INT32 blockSize, numChannels;
    
if (ClassModule_GetNInWires(S) == 2)
{
    // First input pin is the index; second is the complex data.
    // Module output is a single channel.
    INT32 *srcIndex = (INT32 *) (pWires[0]->buffer);
    INT32 index, i, j;
    FLOAT32 sumR, sumI, inR, inI, coeffR, coeffI;
    FLOAT32 *coeffs;
    
    blockSize = ClassWire_GetBlockSize(pWires[1]) >> 1;
    numChannels = ClassWire_GetChannelCount(pWires[1]);
        
    src = (FLOAT32 *) (pWires[1]->buffer);
                
    index = srcIndex[0];
    if (index < 0)
    {
        index = 0;
    }
    if (index >= S->numBeams) {
        index = S->numBeams - 1;
    }
            
    dst = (FLOAT32 *) (pWires[2]->buffer);
            
    // Advance to the set of coefficients specified by index.
    coeffs = S->coeffs + (blockSize * 2 * numChannels * index);
            
    for (i = 0; i < blockSize; i++)
    {
        sumR = 0.0f;
        sumI = 0.0f;
                    
        for (j = 0; j < numChannels; j++)
        {
            coeffR = *coeffs++;
            coeffI = *coeffs++;
            inR = *src++;
            inI = *src++;
                        
            sumR += (coeffR * inR) - (coeffI * inI);
            sumI += (coeffR * inI) + (coeffI * inR);
        }
        *dst++ = sumR;
        *dst++ = sumI;
    }
}
else
{
    // Module is computing all output beams.  It has a single input pin (no index) and
    // a multichannel output pin.
        
    INT32 index, i, j;
    FLOAT32 sumR, sumI, inR, inI, coeffR, coeffI;
    FLOAT32 *coeffs;
     
    blockSize = ClassWire_GetBlockSize(pWires[0]) >> 1;
    numChannels = ClassWire_GetChannelCount(pWires[0]);
    
    for (index = 0; index < S->numBeams; index++)
    {
        src = (FLOAT32 *) (pWires[0]->buffer);
        dst = (FLOAT32 *) (pWires[1]->buffer) + 2 * index;
            
        // Advance to the set of coefficients specified by index.
        coeffs = S->coeffs + (blockSize * 2 * numChannels * index);
            
        for (i = 0; i < blockSize; i++)
        {
            sumR = 0.0f;
            sumI = 0.0f;
                    
            for (j = 0; j < numChannels; j++)
            {
                coeffR = *coeffs++;
                coeffI = *coeffs++;
                inR = *src++;
                inI = *src++;
                        
                sumR += (coeffR * inR) - (coeffI * inI);
                sumI += (coeffR * inI) + (coeffI * inR);
            }
            *dst++ = sumR;
            *dst = sumI;
            dst += (2 * S->numBeams - 1);
        }
    }
}
