function handles = load_beamformer_2_struct(beamformer, handles)

% constants change for both beamformers!
handles.sampling_freq.String = num2str(beamformer.mic_array.samp_freq);
handles.mic_noise_level.String = num2str(10*log10(beamformer.mic_array.noise_var)+94); % dB SPL
handles.speed_sound.String = num2str(beamformer.speed_sound);
handles.speech_level.String = num2str(20*log10(beamformer.signal_std)+94);
handles.diffuse_noise_level.String = num2str(20*log10(beamformer.diffuse_noise_std)+94);

handles.method_choice_2.Value = find(strcmp(handles.method.String, beamformer.method));

handles.angle_tar_2.String = num2str(beamformer.angle_tar);
handles.signal_beamwidth_2.String = num2str(beamformer.beamwidth);
handles.fft_length_2.String = num2str(beamformer.nfft);

if strcmp( beamformer.method, 'MAXSNR' )
    if beamformer.arbitrary_angles
        handles.arbitrary_angles_checkbox_2.Value = 1;
        handles.num_angles_2.String = beamformer.arbitrary_angles;
    else
        handles.arbitrary_angles_checkbox_2.Value = 0;
        handles.num_angles_2.String = num2str(beamformer.num_angles);
    end
elseif strcmp( beamformer.method, 'CVX' )
    if beamformer.arbitrary_angles
        handles.arbitrary_angles_checkbox_2.Value = 1;
        handles.num_angles_2.String = beamformer.arbitrary_angles;
    else
        handles.arbitrary_angles_checkbox_2.Value = 0;
        handles.num_angles_2.String = num2str(beamformer.num_angles);
    end
    if beamformer.arbitrary_freqs
        handles.arbitrary_freq_checkbox_2.Value = 1;
        handles.num_freqs_2.String = beamformer.arbitrary_freqs;
    else
        handles.arbitrary_freq_checkbox_2.Value = 0;
        handles.num_freqs_2.String = num2str(length(beamformer.freqs_opt));
    end
    
    handles.min_beamwidth_2.Value = beamformer.min_beamwidth;
    handles.white_noise_gain_2.String = num2str(20*log10(beamformer.wng));
    if beamformer.min_beamwidth
        handles.min_beamwidth_2.Value = 1;
        handles.transition_width_2.Enable = 'on';
        handles.passband_ripple_2.Enable = 'on';
        handles.transition_width_2.String = num2str(beamformer.transition_width);
        handles.passband_ripple_2.String = num2str(-20*log10(1-beamformer.pass_ripple));
    else
        handles.min_beamwidth_2.Value = 0;
        handles.transition_width_2.Enable = 'off';
        handles.passband_ripple_2.Enable = 'off';
    end
end

% save in handle
if isfield(beamformer, 'weights')
    beamformer_pre.mic_array = beamformer.mic_array;
    beamformer_pre.method = beamformer.method;
    beamformer_pre.speed_sound = beamformer.speed_sound;
    beamformer_pre.nfft = beamformer.nfft;
    beamformer_pre.angle_tar = beamformer.angle_tar;
    beamformer_pre.beamwidth = beamformer.beamwidth;
    beamformer_pre.src_cart = beamformer.src_cart;
    beamformer_pre.signal_std = beamformer.signal_std;
    beamformer_pre.diffuse_noise_std = beamformer.diffuse_noise_std;

    handles.beamformer_pre_2 = beamformer_pre;
    handles.beamformer_post_2 = beamformer;
end