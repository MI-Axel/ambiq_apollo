function [ freqResp, freqs ] = compute_freq_resp( weights, angles, loc, fs, freqs, c, plt )
% computeFreqResp Compute the frequency response of a set of weights for a
% particular look direction (angle).
%
%   Args: 
%       weights : weights for beamforming.
%              This should be a matrix of size M by F where M is the number
%              of microphones and F is the number of frequency bins 
%              (nfft/2+1).
%       angles : lok directions (in degrees) for which to compute the
%                frequency response.
%       loc : microphone positions (in meters)
%             M by 2 matrix where M is the number of microphones
%       fs : Sampling frequency (Hz).
%       freqs : Frequencies (HZ) over which to compute the frequency response.
%                Default is logspace(1,log10(fs/2),150).
%       c : Speed of sound (m/s). Default is 343.
%       plt : boolean for whether or not to plot. Default is 'true'.
%
%   Returns:
%       freqResp : frequency response in a particular look direction.
%
%   Example:
%       >> % compute weights before
%       >> freqResp = computeFreqResp(W, angles, loc, fs);

if nargin < 7
    plt = true;
end
if nargin < 6
    c = 343;
end
if nargin < 5
    freqs = logspace(0,log10(fs/2),500);
end

freqs = freqs(freqs<=fs/2);
nFreq = length(freqs);
[~, nBin] = size(weights);
nfft = (nBin-1)*2;
nAngles = length(angles);

%% compute capture/steering vector (far-field)
freqResp = zeros(nAngles,nFreq);
for t = 1:nAngles
    src = [cosd(angles(t)); sind(angles(t))];
    delays = loc*src/c;
    for k = 1:nFreq
        steer = exp(1i*2*pi*freqs(k)*delays); 
        fidx = round(freqs(k)/fs*nfft)+1; % convert to index for corresponding weights
        freqResp(t,k) = abs(transpose(steer)*weights(:,fidx));
    end
    % in dB
    freqResp(t,:) = 20*log10(freqResp(t,:)+eps);
end

%% plot frequency response
if plt
    legend_text = {};
    figure;
    for t = 1:nAngles
        semilogx(freqs,freqResp(t,:))
%         plot(freqs,freqResp(t,:))
        legend_text = [legend_text; {num2str(angles(t))}];
        hold on
    end
    label = ['Frequency responses (angles in degrees)'];
    title(label);
    xlabel('Frequency [Hz]')
    ylabel('dB')
    ylim([-40,min(max(freqResp(:)),10)])
    xlim([min(freqs), max(freqs)])
    legend(legend_text, 'Location', 'northeastoutside')
    grid on;
end


end

