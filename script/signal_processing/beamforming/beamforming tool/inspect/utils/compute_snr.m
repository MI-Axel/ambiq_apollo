% function SNR = compute_snr( BF, W, A, mic_noise_var )
% 
% A_sig = A(BF.signal==1, :);
% 
% % Assume that the signals add coherently
% signal_energy = abs(sum(BF.signal_std * A_sig * W))^2;
% 
% % Assume that noises sum incoherently
% diffuse_noise_energy = sum(abs(A * W * BF.diffuse_noise_std).^2);
% mic_noise_energy = sum(mic_noise_var*abs(W).^2);
% 
% % Compute SNR
% SNR = 10 * log10(signal_energy / (diffuse_noise_energy + mic_noise_energy));
% 
% end


function [ SNR ] = compute_snr( W, ARR, LOOK, FREQ, ...
    DIFFUSE_NOISE_VAR, SIGNAL_VAR, SPEED_SOUND)
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
%       SIGNAL_VAR : signal variance for the frequency FREQ.
%       SPEED_SOUND : speed of sound in m/s. Default is 343.
%


if nargin < 6
    SPEED_SOUND = 343;
end

% steering vectors under far-field assumption
d = compute_steering_vectors(LOOK, FREQ, ARR.pos, SPEED_SOUND)';

% isotropic noise
Phi = DIFFUSE_NOISE_VAR*sinc(2*pi*FREQ*ARR.edm/SPEED_SOUND / pi); % matlab uses normalized sinc

% self noise
self_noise_var = ARR.noise_var;
DL = self_noise_var*eye(ARR.num_mics);

% compute SNR gain
% SNR = SIGNAL_VAR * abs(W'*(d'*d)*W) / abs(W'*(Phi + DL)*W);
SNR = SIGNAL_VAR * abs(W'*(d*d')*W) / abs(W'*(Phi + DL)*W);
SNR = 10 * log10(SNR);


end