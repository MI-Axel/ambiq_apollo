function [ SNR_gain ] = compute_snr_gain( W, ARR, LOOK, FREQ, ...
    DIFFUSE_NOISE_VAR, SPEED_SOUND)
% compute_snr_gain - Compute the SNR gain for a given set of weights and
% microphone array at a certain frequency and direction.
%
%   Args: 
%       W : beamforming weights, M X 1 vector where M is the number of
%       microphones.
%       ARR : mic array struct.
%       LOOK : Angle in degrees for which to compute the SNR gain.
%       FREQ : Frequency in Hz for which to compute the SNR gain.
%       DIFFUSE_NOISE_VAR : diffuse noise variance. SNR gain is computed
%       assuming isotropic homogenous noise.
%       SPEED_SOUND : speed of sound in m/s. Default is 343.
%


if nargin < 6
    SPEED_SOUND = 343;
end

% steering vectors under far-field assumption
d = compute_steering_vectors(LOOK, FREQ, ARR.pos, SPEED_SOUND)';

% isotropic noise
tot_noise_pwr = DIFFUSE_NOISE_VAR + ARR.noise_var;
Phi = DIFFUSE_NOISE_VAR/tot_noise_pwr*sinc(2*pi*FREQ*ARR.edm/SPEED_SOUND / pi); % matlab uses normalized sinc

% self noise
self_noise_var = ARR.noise_var;
DL = self_noise_var/tot_noise_pwr*eye(ARR.num_mics);

% compute SNR gain
SNR_gain = abs(W'*(d*d')*W) / abs(W'*(Phi + DL)*W);
SNR_gain = 10 * log10(SNR_gain);


end

