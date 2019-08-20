function [M, WIRE_OUT] = sb_beamformer_v2_process(M, WIRE_IN)
% [M, WIRE_OUT] = sb_beamformer_process(M, WIRE_IN)
% Matlab processing function for the SbBeamformer module.  Arguments:
%   M - @awe_module object.
%   WIRE_IN - cell array of input wires.
% The function returns the module object and a cell array of output wires.

% Copyright 2017.  DSP Concepts, Inc.  All Rights Reserved.

if length(M.outputPin) == 2
    % Noise gain out requested
    WIRE_OUT = cell(2,1);
end

if (length(WIRE_IN) == 1)
    % Multichannel
    blockSize = M.inputPin{1}.type.blockSize;
   
    IN = WIRE_IN{1};
    OUT = zeros(blockSize, M.numBeams);
    
    for index = 0 : (M.numBeams - 1)
        startCol = index * blockSize + 1;
        endCol = startCol + blockSize - 1;
        
        COEFFS = M.coeffs(:, startCol:endCol);
        COEFFS = COEFFS.';

        out = sum(IN .* COEFFS, 2);
        OUT(:, index+1) = out;
    end
    
    if ( length(M.outputPin) == 2)
        % Noise gain out
        WIRE_OUT{2} = M.noiseGain.';
    end
    
else
    % Single channel
    index = WIRE_IN{1}(1);
    
    IN = WIRE_IN{2};
    
    if (index < 0)
        index = 0;
    end
    if (index >= M.numBeams)
        index = M.numBeams - 1;
    end
    
    blockSize = size(IN, 1);
    numMics = size(IN, 2);
    
    startCol = index * blockSize + 1;
    endCol = startCol + blockSize - 1;
    
    COEFFS = M.coeffs(:, startCol:endCol);
    COEFFS = COEFFS.';
    
    OUT = sum(IN .* COEFFS, 2);
    
    if ( length(M.outputPin) == 2)
        % Noise gain out
        WIRE_OUT{2} = M.noiseGain(index+1,:).';
    end
    
end

WIRE_OUT{1}=OUT;

return;
