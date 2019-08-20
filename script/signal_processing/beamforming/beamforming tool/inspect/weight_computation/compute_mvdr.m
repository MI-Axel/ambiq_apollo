function [ BF ] = compute_mvdr( BF )
% compute_mvdr - Compute MVDR weights for given beamformer
% structure.

ARR = BF.mic_array;

if ~isfield(BF, 'freqs')
    BF.freqs = (0:(BF.nfft/2)) * (ARR.samp_freq/BF.nfft);
end
BF.num_freqs = length(BF.freqs);
BF.freq_domain = true; % frequency domain weights

%% compute steering vectors
steer = compute_steering_vectors( BF.angle_tar, BF.freqs, ARR.pos, BF.speed_sound, ARR.directivities );

%% compute weights
BF.weights = zeros(ARR.num_mics, BF.num_freqs);
for k = 1:BF.num_freqs
    f = BF.freqs(k);
    Phi = BF.diffuse_noise_std*sinc(2*pi*f*ARR.edm/BF.speed_sound / pi) ...
        + sqrt(ARR.noise_var)*eye(ARR.num_mics); % matlab uses normalized sinc

    weights = conj(steer(k,:))/(Phi);
    BF.weights(:,k) = weights / (weights*transpose(steer(k,:)));  % normalize

end


end

