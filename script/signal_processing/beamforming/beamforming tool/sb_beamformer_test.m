GSYS = get_gsys;
SYS = GSYS.SYS;

blockSize = SYS.MUT.inputPin{end}.type.blockSize;
numMics = SYS.MUT.inputPin{end}.type.numChannels;
numBeams = SYS.MUT.numBeams;

% Configure a single nonzero band for each look direction

for i=1:numBeams
    
    COEFFS = zeros(blockSize, numMics);
    COEFFS(i, :) = ones(1, numMics);
    
    SYS.MUT = sb_beamformer_config(SYS.MUT, COEFFS, i - 1);
end

GSYS.SYS = SYS;
set_gsys(GSYS, 'SbBeamformerTest_multichannel.awd');