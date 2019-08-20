awe_modSbBeamformerV2Instance *S = (awe_modSbBeamformerV2Instance *) pInstance;
WireInstance **pWires = ClassModule_GetWires(S);
INT32 numBeams = S->numBeams;
FLOAT32 *dst, *src;
INT32 blockSize, numChannels;
INT32 calcNoiseGain = (ClassModule_GetNOutWires(S) == 2);
    
if (ClassModule_GetNInWires(S) == 2)
{
    blockSize = ClassWire_GetBlockSize(pWires[1]) >> 1;
    numChannels = ClassWire_GetChannelCount(pWires[1]);
    
    src = (FLOAT32 *) (pWires[1]->buffer);
    dst = (FLOAT32 *) (pWires[2]->buffer);
                
    // Single output channel.  Just copy the first input channel.
    // Real part
    awe_vecCopy(src, 2 * numChannels, dst, 2, blockSize);
    
    // Imaginary part
    awe_vecCopy(src + 1, 2 * numChannels, dst + 1, 2, blockSize);
    if (calcNoiseGain)
    {
      // Output 1s for noise gains
      awe_vecFill((FLOAT32 *) (pWires[3]->buffer), 1, 1.0f, blockSize);
    }
   
}
else
{
    // Multichannel output.  Copy the first input channel to all
    // beam outputs.
        
    INT32 index;
    
    blockSize = ClassWire_GetBlockSize(pWires[0]) >> 1;
    numChannels = ClassWire_GetChannelCount(pWires[0]);
    
    for (index = 0; index < S->numBeams; index++)
    {
        src = (FLOAT32 *) (pWires[0]->buffer);
        dst = (FLOAT32 *) (pWires[1]->buffer);
    
        // Real part
        awe_vecCopy(src, 2 * numChannels, dst + (2 * index), 2 * S->numBeams, blockSize);
    
        // Imaginary part
        awe_vecCopy(src + 1, 2 * numChannels, dst + (2 * index) + 1, 2 * S->numBeams, blockSize);
    }
    if (calcNoiseGain)
    {
      // Output 1s for noise gains
      awe_vecFill((FLOAT32 *) (pWires[2]->buffer), 1, 1.0f, blockSize * S->numBeams);
    }
}

