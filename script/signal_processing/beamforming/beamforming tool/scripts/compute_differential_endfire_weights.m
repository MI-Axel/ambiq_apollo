%%
%
% This script shows how to compute weights in a "hand-written" manner, i.e.
% without using one of the pre-defined approaches. In this case, we compute
% differential endfire weights in the frequency domain and adjust the
% magnitude of the weights to obtain unity gain in the target direction
% while staying below a certain uncorrelated noise gain.
%
% By using the same utility functions to create a mic array and beamformer
% (initialized to MVDR) struct the same function 'evaluate_beamformer' can
% be used to measure the performance of the beamformer. The 'weights' field
% simply needs to be set to the "hand-written" weights as done in Line 64.
%
%%


BF_functions_dir = '..\inspect';
addpath(fullfile(BF_functions_dir,'weight_computation'))
addpath(fullfile(BF_functions_dir,'utils'))

% constants
sample_rate = 16000;
nfft = 512;
speed_sound = 343;
distance = 10 * 1e-3;    % 21.4 (746), 15 (769), 10 (AMBIQ)
delay = distance/speed_sound;
angle_tar = 0;

% constraints
max_wng = 15;

% create beamformer structs
mic_array = create_mic_array( 'Linear', 2, distance, 0, sample_rate,0,false,1,1,true );
beamformer = create_beamformer( mic_array, 'MVDR', speed_sound, nfft, angle_tar, ...
    60, 60, 50);
[ beamformer ] = compute_mvdr( beamformer );

% compute endfire weights
W_endfire = zeros(2,length(beamformer.freqs));
target_resp = zeros(length(beamformer.freqs),1);
gains = ones(length(beamformer.freqs),1);
uncorrelated_noise_gain_pre = zeros(length(beamformer.freqs),1);
uncorrelated_noise_gain_post = zeros(length(beamformer.freqs),1);
for k = 1:length(beamformer.freqs)
    
    % endfire/differential weights
    f = beamformer.freqs(k);
    W_endfire(:,k) = [1, -exp(-1j*2*pi*f*delay)]'/2;
    
    % calculate uncorrelated noise gain
    uncorrelated_noise_gain_pre(k) = 10*log10(W_endfire(:,k)'*W_endfire(:,k));
    
    % compute gain for distortionless response under wng constraint
    gains(k) = undb20(max_wng-uncorrelated_noise_gain_pre(k));
    W_endfire(:,k) = W_endfire(:,k) * gains(k);
    [ target_resp(k) ] = compute_beam_pattern( W_endfire(:,k), f, mic_array.pos, sample_rate, angle_tar, speed_sound, false );
    if target_resp(k) > 1
        gains(k) = 1 / target_resp(k);
        W_endfire(:,k) = W_endfire(:,k) * gains(k);
    end
    uncorrelated_noise_gain_post(k) = 10*log10(W_endfire(:,k)'*W_endfire(:,k));
    
end
beamformer.weights = W_endfire;

%% compute polar plots for multiple frequencies
frequencies = [300, 500, 1000, 2000, 3000];
lower_bound = -10;
polarax = plot_polar_plots( beamformer, frequencies, lower_bound);
title(sprintf('%.1f mm, %d mic linear, Differential',distance*1000,2))
polarax.RLim = [lower_bound,0];
polarax.RTick = lower_bound:2:0;

%% pre and post beamformer
figure;
semilogx(beamformer.freqs, uncorrelated_noise_gain_pre)
hold on
semilogx(beamformer.freqs, uncorrelated_noise_gain_post)
legend('Pre','Post')
title('Uncorrelated noise gain, before and after gain correction')
grid on
axis tight
hold off

%% evaluation
num_eval_angles = 500;
num_eval_freqs = 500;

clear plt
plt.filter_responses = false;
plt.frequency_responses = true;
plt.heatmap_2d = false;
plt.heatmap_3d = false;
plt.beam_patterns = true;
plt.snr = false;
plt.snr_gain = true;
plt.directivity_idx = false;
plt.beamwidth = false;
plt.uncorrelated_noise_gain = true;
plt.ambient_noise_gain = false;
plt.total_noise_gain = false;

[ eval ] = evaluate_beamformer( beamformer, num_eval_angles, num_eval_freqs, plt);
% csvwrite('differential.csv',transpose(W_endfire))


%% compute FIR coefficients
num_taps = 49;
[ fir_coefficients, attenuation] = compute_fir_coefficients( beamformer.weights, num_taps, 1 );

% %% remove paths
% rmpath(fullfile(BF_functions_dir,'weight_computation'))
% rmpath(fullfile(BF_functions_dir,'utils'))
