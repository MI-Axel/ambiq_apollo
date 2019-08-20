function [ beamwidth ] = compute_beam_width( dir, angles, angle_tar )
% compute_beam_width

angles = angles(:);

pwr_dB = 20*log10(dir);
% if max(pwr_dB) < -3
%     beamwidth = 360;     % no beam
%     return
% end


[~, tarInd] = min( abs(mod(angles,360) - angle_tar) );
mra_resp = pwr_dB(tarInd); % main response axis response
half_power_lvl = mra_resp-3;

tarInd = tarInd+length(angles);
aziRep = [angles;angles+360;angles+720];

% repeat due to wrap-around
bwTest = pwr_dB + abs(half_power_lvl); % make zero-crossing problem
bwTest = [bwTest; bwTest; bwTest];

% find points where main beam reaches -3dB
zerIdx=[];
for i=1:length(bwTest)-1
    if ((bwTest(i)>0 && bwTest(i+1)<0) || (bwTest(i)<0 && bwTest(i+1)>0))
        zerIdx(end+1)=i; % save index of zero-crossing
    end
end

if length(zerIdx) < 2
    beamwidth = 360; % never reaches -3dB
    return
end

above = zerIdx(zerIdx>tarInd);
below = zerIdx(zerIdx<tarInd);

beamwidth = aziRep(above(1))-aziRep(below(end));


end

