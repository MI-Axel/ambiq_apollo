function [M, WIRE_OUT] = sb_beamformer_bypass(M, WIRE_IN)
% [M, WIRE_OUT] = sb_beamformer_bypass(M, WIRE_IN)
% Matlab bypass function for the SbBeamformer module.  Arguments:
%   M - @awe_module object.
%   WIRE_IN - cell array of input wires.
% The function returns the module object and a cell array of output wires.

% Copyright 2017.  DSP Concepts, Inc.  All Rights Reserved.

blockSize = M.inputPin{1}.type.blockSize;


if (length(WIRE_IN) == 1)
    % Multichannel.  Replicate the first channel.
    IN = WIRE_IN{1};
    OUT = zeros(blockSize, M.numBeams);

    OUT = repmat(IN(:, 1), 1, M.numBeams);
else
    % Single channel.  Just output the first channel.
    IN = WIRE_IN{2};
    OUT = IN(:, 1);
end

WIRE_OUT{1}=OUT;

return;
