function handles = compute_weights_2(handles)

% create second beamformer struct
fprintf('Creating mic array #2...\n')
mic_array_2 = save_array_2_struct(handles);

beamformer_2 = prepare_beamformer_2_struct(handles, mic_array_2);

% compute weights only if some parameter changed
if isfield(handles,'export_freq_bins')
    beamformer_2.freqs = (0:(beamformer_2.nfft/2)) * (beamformer_2.mic_array.samp_freq/beamformer_2.nfft);
    beamformer_2.freqs = beamformer_2.freqs(handles.export_freq_bins);
end
if isfield(handles,'disable_weights_progress')
    progress_bar = false;
else
    progress_bar = true;
end

fprintf('Computing beamformer #2...\n')
if (isfield(handles, 'beamformer_pre_2') && ~isequal(handles.beamformer_pre_2, beamformer_2)) ...
        || ~isfield(handles, 'beamformer_pre_2')
    METHOD = handles.method.String{handles.method_choice_2.Value};
    if strcmp( METHOD, 'DAS' )
        [ beamformer_post_2 ] = compute_das( beamformer_2 );
    elseif strcmp( METHOD, 'MVDR' )
        [ beamformer_post_2 ] = compute_mvdr( beamformer_2 );
    elseif strcmp( METHOD, 'MAXSNR' )
        [ beamformer_post_2 ] = compute_max_snr( beamformer_2, progress_bar );
    elseif strcmp( METHOD, 'CVX' )
        [ beamformer_post_2 ] = cvx_approach( beamformer_2, progress_bar );
    elseif strcmp( METHOD, 'Import' )
        beamformer_post_2 = beamformer_2;
        beamformer_post_2.freq_domain = 1;
        beamformer_post_2.freqs = (0:(beamformer_post_2.nfft/2)) * (beamformer_post_2.mic_array.samp_freq/beamformer_post_2.nfft);
        beamformer_post_2.num_freqs = length(beamformer_post_2.freqs);
        beamformer_post_2.weights = transpose(handles.imported_weights_1);
    end
    if isfield(beamformer_post_2,'weights')
        handles.beamformer_post_2 = beamformer_post_2;
        handles.beamformer_pre_2 = beamformer_2;
    else
        handles.beamformer_post_2 = 0;
        handles.beamformer_pre_2 = 0;
        return
    end
end