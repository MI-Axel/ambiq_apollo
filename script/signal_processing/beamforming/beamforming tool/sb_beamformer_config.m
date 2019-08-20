function M = sb_beamformer_config(M, COEFFS, INDEX)
% M = sb_beamformer_config(M, COEFFS, INDEX)
% Configures the coefficients within the subband beamformer module.
% Arguments:
%   M - module instance
%   COEFFS - coefficients
%   INDEX - index of the coefficient set to load.  This is zero based
%     and in the range [0 NUMBEAMS-1].
%
% COEFFS is a matrix of complex coefficients of dimension [blockSize x numMics].
% The function returns the updated module instance.

% Clip index to the allowable range
if (INDEX < 0)
    INDEX = 0;
end
if (INDEX >= M.numBeams)
    INDEX = M.numBeams - 1;
end

blockSize = M.inputPin{end}.type.blockSize;

startCol = (INDEX * blockSize) + 1;
endCol = startCol + blockSize - 1;

COEFFS = COEFFS.';

M.coeffs(:, [startCol:endCol]) = COEFFS;
