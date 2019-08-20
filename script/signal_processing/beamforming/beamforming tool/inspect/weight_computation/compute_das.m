function [ BF ] = compute_das( BF )
% compute_das - Compute delay-and-sum (DAS) weights for given beamformer
% structure.
%
%   Args: 
%       BF : beamformer parameters contained in a struct with a mic array struct as one of the fields.
%
%   Returns:
%       BF : returns same struct with the weights as a new parameter
%

ARR = BF.mic_array;
if ~isfield(BF, 'freqs')
    BF.freqs = (0:(BF.nfft/2)) * (ARR.samp_freq/BF.nfft);
end
BF.num_freqs = length(BF.freqs);
BF.freq_domain = true; % frequency domain weights

%% interpolate to find directivities for target angle across beamformer frequencies
freq_points = repmat(ARR.directivities.frequencies',1,length(ARR.directivities.angles));
angle_points = repmat(ARR.directivities.angles,length(ARR.directivities.frequencies),1);
DIR = zeros(ARR.num_mics, BF.num_freqs);
for m = 1:ARR.num_mics
    V = squeeze(ARR.directivities.patterns(m,:,:));
    DIR(m,:) =  interp2(angle_points, freq_points, V, BF.angle_tar*ones(BF.num_freqs,1), BF.freqs');
end

%% compute weights
steer = compute_steering_vectors( BF.angle_tar, BF.freqs, ARR.pos, BF.speed_sound );
BF.weights = steer'./DIR / ARR.num_mics;  
% NOTE : normally would multiply by directivity for steering vectors but 
% we divide here so that we can avoid inversion for the weights


end

