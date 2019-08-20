%%
%
% Evaluate and plot performance measures for multiple beamformers stored in
% separate .mat files. This is essentially what happens "under the hood"
% when comparing beamformers with the GUI.
%
%%

BF_functions_dir = '..\inspect';
addpath(fullfile(BF_functions_dir,'weight_computation'))
addpath(fullfile(BF_functions_dir,'utils'))

%% which beamformers to compare
bf_file_names = {'MAXSNR_trillium_target_0.mat', 'CVX_trillium_target_0.mat'};
figure_labels = {'MAXSNR', 'CVX'};

%% plotting options
plt_compare.mic_arrays = false;
plt_compare.filter_responses = false;
plt_compare.frequency_responses = false;
plt_compare.heatmap_2d = false;
plt_compare.heatmap_3d = false;
plt_compare.beam_patterns = true;
plt_compare.snr = false;
plt_compare.snr_gain = true;
plt_compare.directivity_idx = false;
plt_compare.beamwidth = false;
plt_compare.uncorrelated_noise_gain = false;
plt_compare.ambient_noise_gain = false;
plt_compare.total_noise_gain = false;

%% evaluate each beamformer
num_eval_angles = 360;
num_eval_freqs = 500;
bfs = cell(length(bf_file_names));
evals = cell(length(bf_file_names));
for k = 1:length(bf_file_names)
    bf = load(bf_file_names{k});
    bfs{k} = bf.beamformer;
    evals{k} = evaluate_beamformer( bfs{k}, num_eval_angles, ...
        num_eval_freqs, plt_compare, figure_labels{k}, 1);
end

%% compare
compare_evals(bfs, evals, figure_labels, plt_compare);

% %% remove paths
% rmpath(fullfile(BF_functions_dir,'weight_computation'))
% rmpath(fullfile(BF_functions_dir,'utils'))