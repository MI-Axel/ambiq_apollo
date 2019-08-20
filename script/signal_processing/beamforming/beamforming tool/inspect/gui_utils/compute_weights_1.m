function handles = compute_weights_1(handles)

% create microphone array struct
fprintf('Creating mic array #1...\n')
mic_array = save_array_1_struct(handles);

% create beamformer struct
beamformer = prepare_beamformer_1_struct(handles, mic_array);

% compute weights only if some parameter changed
if isfield(handles,'export_freq_bins')
    beamformer.freqs = (0:(beamformer.nfft/2)) * (beamformer.mic_array.samp_freq/beamformer.nfft);
    beamformer.freqs = beamformer.freqs(handles.export_freq_bins);
end
if isfield(handles,'disable_weights_progress')
    progress_bar = false;
else
    progress_bar = true;
end

fprintf('Computing beamformer #1...\n')
if (isfield(handles, 'beamformer_pre') && ~isequal(handles.beamformer_pre, beamformer)) || ~isfield(handles, 'beamformer_pre')
    METHOD = handles.method.String{handles.method.Value};
    if strcmp( METHOD, 'DAS' )
        [ beamformer_post ] = compute_das( beamformer );
    elseif strcmp( beamformer.method, 'MVDR' )
        [ beamformer_post ] = compute_mvdr( beamformer );
    elseif strcmp( beamformer.method, 'MAXSNR' )
        [ beamformer_post ] = compute_max_snr( beamformer, progress_bar );
    elseif strcmp( beamformer.method, 'CVX' )
        [ beamformer_post ] = cvx_approach( beamformer, progress_bar );
    elseif strcmp( METHOD, 'Import' )
        beamformer_post = beamformer;
        beamformer_post.freq_domain = 1;
        beamformer_post.freqs = (0:(beamformer_post.nfft/2)) * (beamformer_post.mic_array.samp_freq/beamformer_post.nfft);
        beamformer_post.num_freqs = length(beamformer_post.freqs);
        beamformer_post.weights = transpose(handles.imported_weights_1);
    end
    if isfield(beamformer_post,'weights')
        handles.beamformer_post = beamformer_post;
        handles.beamformer_pre = beamformer;
    else
        handles.beamformer_post = 0;
        handles.beamformer_pre = 0;
        return
    end
end