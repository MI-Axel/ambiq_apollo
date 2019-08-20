%%
%
% Compute weights according to a set of parameters and a particular
% algorithm (DAS, MVDR, MAXSNR, CVX approach)
%
% In the evaluation section, the following can be done:
% 1) Lay multiple polar plots (of different frequencies) on top of each
% other with the 'plot_polar_plots' function.
% 2) Compute SNR gain for multiple uncorrelated to diffuse noise ratios 
% (in dB) with the 'plot_snr_gain' function.
% 3) Apply the Beamformer GUI visualizations with the 'evaluate_beamformer'
% function
% 4) Compute and vizualize the corresponding FIR coefficients with the
% 'plot_snr_gain' function. The number of taps can be passed to
% the function, which will display the corresponding attenuation due to
% truncation.
%
%%

BF_functions_dir = '..\inspect';
addpath(fullfile(BF_functions_dir,'weight_computation'))
addpath(fullfile(BF_functions_dir,'utils'))

% ----------------------------------------------------------------------
% Setup problem
% ----------------------------------------------------------------------

C = 343;            % Speed of sound in meters/second
FS = 16000;         % Sampling frequency

SPEECH_LEVEL = 60;  % Speech level (dB SPL)
DIFFUSE_NOISE_LEVEL = 50;   % Diffuse noise level (dB SPL)
MIC_NOISE_LEVEL = 94 - 64; % Microphone self noise level.  Equivalent dB SPL

ANGLE_TAR = 0;      % look direction in degrees
SIGNAL_BEAM_WIDTH = 45; % +/- half of this (in degrees) around look direction

ARRAY_GEOMETRY = 'Circle';  % Circle, Linear, Triangle (equilateral), Square
SPACING = 0.0429;          % RADIUS, INTER-DISTANCE, SIDE LENGTH (in meters)
ROTATION = 0;
NUM_MICS = 3;               % for Circle, Triangle, Square (excluding possible center mic) and LINEAR
ORDERING = 1;               % 1 for no re-ordering
CENTER = true;              % for circle, triangle, and square; whether to add center mic

% 1 for omni mics OR path to .mat file with a matrix of size M*L (directivities of the M mics) and a vector of length L (denoting the angle discretization)
DIRECTIVITIES_PATH = 1; 
% DIRECTIVITIES_PATH = 'array_directivities\4_mics_omni.mat';     

FFT_LEN = 512;      % Number of points in the frequency domain to compute weights for = FFT_LEN/2+1 (except for CVX method)
METHOD = 'MAXSNR';    % 'DAS', 'MVDR', 'MAXSNR', 'CVX'
% bf_file_name = ['beamformer_mat_files\' METHOD '_target_' num2str(ANGLE_TAR) '_nfft_' ...
%     num2str(FFT_LEN) '_fs_' num2str(FS) '_snap'];  % save to file 

% method specific parameters
if strcmp( METHOD, 'MAXSNR' )
    NUM_ANGLES = 360;       % discretize angles for optimization across azimuth range
elseif strcmp( METHOD, 'CVX' )
    NUM_ANGLES = 100;       % discretize angles for optimization across azimuth range
    NUM_FREQS = 257;         % discretize frequencies for optimization until Nyquist frequency
    MAX_WHITE_NOISE_GAIN = 0;  % in dB
    min_beamwidth = true;   % set minimum beamwidth contraint?
    TRANSITION_WIDTH = 5;   % width of the transition band (in degrees) between target direction beamwidth and stop direction
    PASSBAND_RIPPLE = 1;  % +/- deviation from unit gain in dB
end

% post-processing (window to generate desired frequency response of
% beamformer)
POST_PROC = false;
post_param.fmin = 70; % frequency below which amplitude is zero
post_param.fbeg = 100; % frequency at which amplitude starts to be 1
post_param.fend = 3500; % frequency at which amplitude end being 1
post_param.fmax = 4000; % frequency after which amplitude is zero

%% ----------------------------------------------------------------------
% Create structures
% ----------------------------------------------------------------------

mic_array = create_mic_array( ARRAY_GEOMETRY, NUM_MICS, SPACING, ROTATION, FS, ...
    MIC_NOISE_LEVEL, CENTER, DIRECTIVITIES_PATH, ORDERING, true );

beamformer = create_beamformer( mic_array, METHOD, C, FFT_LEN, ANGLE_TAR, ...
    SIGNAL_BEAM_WIDTH, SPEECH_LEVEL, DIFFUSE_NOISE_LEVEL);

% method dependent parameters
if strcmp( METHOD, 'MAXSNR' )
    beamformer.num_angles = NUM_ANGLES;
elseif strcmp( METHOD, 'CVX' )
    beamformer.min_beamwidth = min_beamwidth;
    beamformer.num_angles = NUM_ANGLES;
    beamformer.num_freqs = NUM_FREQS;
    if min_beamwidth
        beamformer.transition_width = TRANSITION_WIDTH;
        if exist('PASSBAND_RIPPLE','var')
            beamformer.pass_ripple = 1-10^(PASSBAND_RIPPLE/-20);
        end
    end
    if exist('MAX_WHITE_NOISE_GAIN','var')
        beamformer.wng = 10^(MAX_WHITE_NOISE_GAIN/20);
    end
end


%% ----------------------------------------------------------------------
% Compute weights
% ----------------------------------------------------------------------

if strcmp( METHOD, 'DAS' )
    [ beamformer ] = compute_das( beamformer );
elseif strcmp( METHOD, 'MVDR' )
    [ beamformer ] = compute_mvdr( beamformer );
elseif strcmp( METHOD, 'MAXSNR' )
    [ beamformer ] = compute_max_snr( beamformer, false );
elseif strcmp( METHOD, 'CVX' )
    [ beamformer ] = cvx_approach( beamformer, false );   % disable progress bar with second argument
else
    error('Invalid beamforming method.')
end

%% ----------------------------------------------------------------------
% Post-processing
% ----------------------------------------------------------------------

if beamformer.freq_domain && POST_PROC
    beamformer = post_processing( beamformer, post_param );
end

%% ----------------------------------------------------------------------
% Evaluate beamformer
% ----------------------------------------------------------------------

if exist('bf_file_name','var')
    save(bf_file_name, 'beamformer');
end

%% Lay multiple polar plots on top of each other
frequencies = [300, 500, 1000, 2000, 3000];
lower_bound = -10;
polarax = plot_polar_plots( beamformer, frequencies, lower_bound);
title(sprintf('%.1f mm, %d mic %s, %s',SPACING*1000,NUM_MICS,...
    ARRAY_GEOMETRY, METHOD))

%% compute SNR gain for multiple uncorrelated to diffuse noise ratios (in dB)
plot_snr_gain( beamformer, [-30, -50]);

%% same visualizations as GUI
num_eval_angles = 360;
num_eval_freqs = 500;

clear plt
plt.filter_responses = false;
plt.frequency_responses = true;
plt.heatmap_2d = true;
plt.heatmap_3d = false;
plt.beam_patterns = true;
plt.snr = false;
plt.snr_gain = true;
plt.directivity_idx = false;
plt.beamwidth = false;
plt.uncorrelated_noise_gain = false;
plt.ambient_noise_gain = false;
plt.total_noise_gain = true;

[ eval ] = evaluate_beamformer( beamformer, num_eval_angles, num_eval_freqs, plt);

%% compute FIR coefficients (each mics filter will be plotted --> <NUM_MICS> plots) 
num_taps = 49;
[ fir_coefficients, attenuation] = compute_fir_coefficients( beamformer.weights, num_taps, 1 );

% %% remove paths
% rmpath(fullfile(BF_functions_dir,'weight_computation'))
% rmpath(fullfile(BF_functions_dir,'utils'))
