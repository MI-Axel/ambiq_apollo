function [ eval ] = evaluate_beamformer( BF, NUM_ANGLES, NUM_FREQS, PLT, FIGURE_LABEL, FORCE_FALSE )
% evaluate_beamformer

if ~isfield(BF,'weights')
    % need weights to evaluate
    eval = 0;
    return
end

if nargin < 5
    FIGURE_LABEL = 'Beamformer Design';
end

if nargin < 4
    PLT.frequency_responses = true;
    PLT.filter_responses = true;
    PLT.heatmap_2d = true;
    PLT.heatmap_3d = true;
    PLT.beam_patterns = true;
    PLT.snr = true;
    PLT.snr_gain = true;
    PLT.directivity_idx = true;
    PLT.beamwidth = true;
    PLT.uncorrelated_noise_gain = true;
    PLT.ambient_noise_gain = true;
    PLT.total_noise_gain = true;
    FIGURE_LABEL = 'Beamformer Design';
end

if nargin == 6  % useful when comparing beamformers (need to compute metrics but will plot later)
    PLT.frequency_responses = false;
    PLT.filter_responses = false;
    PLT.heatmap_2d = false;
    PLT.heatmap_3d = false;
    PLT.beam_patterns = false;
    PLT.snr = false;
    PLT.snr_gain = false;
    PLT.directivity_idx = false;
    PLT.beamwidth = false;
    PLT.uncorrelated_noise_gain = false;
    PLT.ambient_noise_gain = false;
    PLT.total_noise_gain = false;
end

ARR = BF.mic_array;

ANGLES = linspace(0,360,NUM_ANGLES)';  % for wraparound in plotting
angle_res = ANGLES(2)-ANGLES(1);
[~,taridx]=min(abs(ANGLES-BF.angle_tar));
if length(NUM_FREQS) == 1
    FREQS = linspace(100, ARR.samp_freq/2, NUM_FREQS)'; 
    FREQS_log = logspace(log10(100), log10(ARR.samp_freq/2), NUM_FREQS)'; % for log plots
elseif length(NUM_FREQS) == 3
    lower_freq = NUM_FREQS(1);
    upper_freq = NUM_FREQS(2);
    NUM_FREQS = NUM_FREQS(3);
    FREQS = linspace(lower_freq, upper_freq, NUM_FREQS)'; 
    FREQS_log = logspace(log10(lower_freq), log10(upper_freq), NUM_FREQS)'; % for log plots
else
    error('NUM_FREQS must be a scalar or an array of three values denoting [lower freq, upper freq, number of freq]')
end

eval.angles = ANGLES;
eval.freqs = FREQS;
eval.freqs_log = FREQS_log;

% copy over some constants/values
eval.angle_tar = BF.angle_tar;
eval.signal_beamwidth = BF.beamwidth;
eval.mic_noise_var = ARR.noise_var;
eval.diffuse_noise_var = BF.diffuse_noise_std^2;

eval.samp_freq = ARR.samp_freq;
if BF.freq_domain
    
else
    eval.num_taps = BF.num_taps;
end


%% compute magnitude, phase, and impulse response of weights
if BF.freq_domain
    eval.freq_scale = BF.freqs;
    nfft = (length(BF.freqs)-1)*2;
    eval.time_scale = (0:(nfft-1))/ARR.samp_freq;
    
    eval.magnitude_resp = zeros(ARR.num_mics, length(BF.freqs));
    eval.phase_resp = eval.magnitude_resp;
    eval.impulse_resp = zeros(ARR.num_mics, nfft);
    for m = 1:ARR.num_mics
        eval.magnitude_resp(m,:) = 20*log10(abs(BF.weights(m,:)));
        eval.phase_resp(m,:) = unwrap(angle(BF.weights(m,:)));
        F = [BF.weights(m,:),conj(fliplr(BF.weights(m,2:(end-1))))];
        eval.impulse_resp(m,:) = real(ifft(F));
    end
else
    eval.time_scale = (0:(BF.num_taps-1))/ARR.samp_freq;
    eval.freq_scale = (0:(BF.num_taps-1))*ARR.samp_freq/BF.num_taps;
    for m = 1:ARR.num_mics
        W = fft(BF.weights(m,:));
        eval.magnitude_resp(m,:) = 20*log10(abs(W));
        eval.phase_resp(m,:) = unwrap(angle(W));
        eval.impulse_resp(m,:) = BF.weights(m,:);
    end
end

%% compute steering vectors
steering_vecs = compute_steering_vectors( ANGLES, FREQS, ARR.pos, BF.speed_sound, ARR.directivities );
steering_vecs_log = compute_steering_vectors( ANGLES, FREQS_log, ARR.pos, BF.speed_sound, ARR.directivities );

%% characterize each frequency
eval.patterns = zeros(NUM_ANGLES,NUM_FREQS);
eval.snr = zeros(NUM_FREQS, 1);
eval.snr_gain = zeros(NUM_FREQS, 1);
eval.uncorrelated_noise_gain = zeros(NUM_FREQS, 1);
eval.directivity_idx = zeros(NUM_FREQS, 1);
eval.total_noise_gain = zeros(NUM_FREQS, 1);
eval.beam_width = zeros(NUM_FREQS, 1);
weights = zeros(ARR.num_mics, NUM_FREQS);
for k = 1:NUM_FREQS
    
    % beam patterns (linear frequencies since linear spacing looks better for heatmaps) 
    A = squeeze(steering_vecs(k,:,:));
    if BF.freq_domain
        [~, fidx] = min(abs(BF.freqs-FREQS(k))); % convert to index for corresponding weights
        weights(:,k) = BF.weights(:,fidx);
    else
        omega = 2*pi*FREQS(k)/ARR.samp_freq;
        % The DFT vector for the FIR filter: V(omega)*w = W(omega)
        V = exp(-1i*omega*[0:BF.num_taps-1]');
        weights(:,k) = conj(BF.weights*V);
    end
    eval.patterns(:,k) = abs(A*weights(:,k));
    

    %% for rest use log frequency spacing
    A = squeeze(steering_vecs_log(k,:,:));
    if BF.freq_domain
        [~, fidx] = min(abs(BF.freqs-FREQS_log(k))); % convert to index for corresponding weights
        weights(:,k) = BF.weights(:,fidx);
    else
        omega = 2*pi*FREQS_log(k)/ARR.samp_freq;
        % The DFT vector for the FIR filter: V(omega)*w = W(omega)
        V = exp(-1i*omega*[0:BF.num_taps-1]');
        weights(:,k) = conj(BF.weights*V);
    end
    eval.patterns_log(:,k) = abs(A*weights(:,k));
    
    % uncorrelated noise gain (assuming identical mics)
    G = weights(:,k)' * weights(:,k);
    eval.uncorrelated_noise_gain(k) = 10*log10( G );
    
    % directivity index / ambient noise gain
    D = eval.patterns_log(taridx,k)^2 / (sum(eval.patterns_log(2:length(ANGLES),k).^2) ...
        *angle_res) * 360;  % avoid adding 0 and 360    
    eval.ambient_noise_gain(k) = 10*log10( 1./D );
    
    % total noise gain    
    G_tot = (1./D * BF.diffuse_noise_std^2 + G * ARR.noise_var) ...
        / (BF.diffuse_noise_std^2 + ARR.noise_var);
    eval.total_noise_gain(k) = 10*log10(G_tot);
    
    % beam width
    eval.beam_width(k) = compute_beam_width( ...
        eval.patterns_log(:,k), ANGLES, BF.angle_tar);
    
end


%% visualize
plot_eval( BF, eval, FIGURE_LABEL, PLT );


end

