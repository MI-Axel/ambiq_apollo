function [ wind ] = compute_post_window( freqs, fmin, fbeg, fend, fmax )
% compute_post_window Compute desired frequency response for the microphone array
% based on the parameters below.

%   Args: 
%       freqs : frequencies (in Hz) for which the window is computed.
%       fmin : Frequency (in Hz) below which the response will be zero.
%       fbeg : Frequency (in Hz) from which the response will be equal to
%              one. Within [fmin, fbeg], a cosine function will be used for
%              a smooth response.
%       fend : Frequency (in Hz) till which the response will be equal to
%              one (starting from fbeg).
%       fmax : Frequency (in Hz) after which the response will be equal to
%              zero.
%
%   Returns:
%       wind : frequency response with the same length as freqs.
%
%   Example:
%       >> freqResp = computeWindow(freqs, 100, 200, 7000, 7500);

nFreq = length(freqs);
wind = zeros(nFreq,1);

for k = 1:nFreq
    f = freqs(k);
    if f >=fmin && f <= fbeg
        wind(k) = 0.5 * (1 + cos(pi*(f-fbeg)/(fbeg-fmin)));
    elseif f > fbeg && f < fend
        wind(k) = 1;
    elseif f >=fend && f <= fmax
        wind(k) = 0.5 * (1 + cos(pi*(f-fend)/(fmax-fend)));
    else % below fmin and above fmax
        wind(k) = 0;
    end
end

end
