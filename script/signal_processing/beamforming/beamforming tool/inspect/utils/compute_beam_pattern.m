function [ dir ] = compute_beam_pattern( weights, freq, loc, fs, angles, c, plt )
% plotBeamPattern Plot the beampattern for a fixed set of FREQUENCY DOMAIN weights for a
% given frequency.
%
%   Args: 
%       weights : weights for beamforming.
%              This should be a matrix of size M by F where M is the number
%              of microphones and F is the number of frequency bins 
%              (nfft/2+1).
%              Or it could be an M by 1 vector if the weights for the
%              corresponding frequency are given.
%       freq : Frequency (Hz) for which to compute the beam pattern.
%       loc : microphone positions (in meters)
%             M by 2 matrix where M is the number of microphones
%       fs : Sampling frequency (Hz).
%       angles : Angles (in degrees) over which to compute the beampattern.
%                Default is 0:1:360.
%       c : Speed of sound (m/s). Default is 343.
%       plt : boolean for whether or not to plot. Default is 'true'.
%
%   Returns:
%       dir : magnitude response of beam pattern
%
%   Example:
%       >> dir = computeBeamPattern(W, 2000, loc, fs);

if nargin < 7
    plt = true;
end
if nargin < 6
    c = 343;
end
if nargin < 5
    angles = 0:360;
end
if nargin < 4
    fs = 16000;
end

angles = angles(:); % column vec

%% compute capture/steering vector (far-field)
far_delays = -(kron(cosd(angles),loc(:,1)') + kron(sind(angles),loc(:,2)'))/c;
steer = exp(-1i*2*pi*freq*far_delays);  % exp(-j*tau*f)*X(f) --> x(t-tau)

%% compute directivity
[~, nFreq] = size(weights);
if nFreq == 1
    dir = abs(steer*weights);
else
    nfft = (nFreq-1)*2;
    fidx = round(freq/fs*nfft)+1; % convert to index for corresponding weights
    dir = abs(steer*weights(:,fidx));
end

%% plot directivity
if plt
    
    figure; polarplot(angles*pi/180,dir, 'b-', 'LineWidth', 1)
    hold on;

    % unit circle
    polarplot(angles*pi/180,ones(length(angles),1), 'k--', 'LineWidth', 0.5)

    label = ['Beam pattern for ' num2str(freq) ' Hz'];
    title(label);

    grid on;
    hold off
end

end

