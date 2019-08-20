function PASS = test_sb_beamformer_v2(M)
% PASS = test_sb_beamformer_v2
% Performs a standard set of regression tests on the SbBeamformerV2
% module.
%
% PASS = test_sb_beamformer(M)
% Tests the specific instance of the module M

% Copyright 2017.  DSP Concepts, Inc.  All Rights Reserved.

% Set random number generator to default settings for repeatable results.
awe_rng('default');

numBlocks = 10;

if (nargin == 0)
    
    % Each row contains [blockSize numMics numBeams]
    
    CONFIG=[32 6 4; 1 3 7; 63 7 8; 20 3 4];
    PASS=1;
    
    for noiseGainOut = 0:1
        for i=1:size(CONFIG,1)
            
            blockSize = CONFIG(i,1);
            numMics = CONFIG(i,2);
            numBeams = CONFIG(i,3);
            
            for allOut = 0:1
                if (allOut == 0)
                    PTIN={new_pin_type(1, 1, [], 'int') new_pin_type(numMics, blockSize, [], 'float', 1)};
                    PTIN{1}.data = rem(0 : numBlocks - 1, numBeams).';
                    PTOUT={new_pin_type(1, blockSize,[], 'float', 1)};
                    if noiseGainOut == 1
                        PTOUT{2} = new_pin_type(1, blockSize,[], 'float');
                    end
                        
                else
                    PTIN={new_pin_type(numMics, blockSize, [], 'float', 1)};
                    PTOUT={new_pin_type(numBeams, blockSize,[], 'float', 1)};
                    if noiseGainOut == 1
                        PTOUT{2} = new_pin_type(numBeams, blockSize,[], 'float');
                    end
                end
                
                MUT = sb_beamformer_v2_module('MUT', numBeams, allOut, blockSize, numMics, noiseGainOut);
                MUT.coeffs = randn(MUT.coeffs.size);
                
                pass=test_server_vs_matlab(MUT, PTIN, PTOUT, numBlocks);
                
                PASS=(pass && PASS);
                if (PASS == 0)
                    break;
                end
            end
            if (PASS == 0)
                break;
            end
        end
    end
else
    PASS = test_server_vs_matlab(M, {}, {}, numBlocks);
end


