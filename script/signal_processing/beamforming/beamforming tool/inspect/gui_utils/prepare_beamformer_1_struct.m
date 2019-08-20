function beamformer = prepare_beamformer_1_struct(handles, mic_array)

METHOD = handles.method.String{handles.method.Value};
C = str2double(handles.speed_sound.String);
FFT_LEN = str2double(handles.fft_length.String);
ANGLE_TAR = str2double(handles.angle_tar.String);
SIGNAL_BEAM_WIDTH = str2double(handles.signal_beamwidth.String);
SPEECH_LEVEL = str2double(handles.speech_level.String);
DIFFUSE_NOISE_LEVEL = str2double(handles.diffuse_noise_level.String);
beamformer = create_beamformer( mic_array, METHOD, C, FFT_LEN, ANGLE_TAR, ...
    SIGNAL_BEAM_WIDTH, SPEECH_LEVEL, DIFFUSE_NOISE_LEVEL);

% method dependent parameters
if strcmp( METHOD, 'MAXSNR' )
    if handles.arbitrary_angles_checkbox.Value
        try
            beamformer.angles = eval(handles.num_angles.String);
        catch err
            rethrow(err)
        end
        beamformer.num_angles = length(beamformer.angles);
        beamformer.arbitrary_angles = handles.num_angles.String;
    else
        beamformer.num_angles = str2double(handles.num_angles.String);
        beamformer.arbitrary_angles = 0;
    end
elseif strcmp( METHOD, 'CVX' )
    if handles.arbitrary_angles_checkbox.Value
        try
            beamformer.angles = eval(handles.num_angles.String);
        catch err
            rethrow(err)
        end
        beamformer.num_angles = length(beamformer.angles);
        beamformer.arbitrary_angles = handles.num_angles.String;
    else
        beamformer.num_angles = str2double(handles.num_angles.String);
        beamformer.arbitrary_angles = 0;
    end
    if handles.arbitrary_freq_checkbox.Value
        try
            beamformer.freqs_opt = eval(handles.num_freqs.String);
        catch err
            rethrow(err)
        end
        beamformer.num_freqs = length(beamformer.freqs_opt);
        beamformer.arbitrary_freqs = handles.num_freqs.String;
    else
        beamformer.num_freqs = str2double(handles.num_freqs.String);
        beamformer.freqs_opt = linspace(0, mic_array.samp_freq/2, beamformer.num_freqs);
        beamformer.arbitrary_freqs = 0;
    end
    beamformer.min_beamwidth = handles.min_beamwidth.Value;
    beamformer.wng = 10^(str2double(handles.white_noise_gain.String)/20);
    if beamformer.min_beamwidth
        beamformer.transition_width = str2double(handles.transition_width.String);
        if str2double(handles.passband_ripple.String) < 0
            msgbox('Passband ripple must be non-negative!')
            error('Passband ripple must be non-negative!')
        else
            beamformer.pass_ripple = 1-10^(str2double(handles.passband_ripple.String)/-20);
        end
    end
elseif strcmp( METHOD, 'Import' )
%    if strcmp(ARRAY_GEOMETRY, 'Custom')
%        if NUM_MICS ~= length(X_COORD)  % check for Custom
%            msgbox('Number of entered coordinates does not match number of microphones according to imported weights!')
%            error('Number of entered coordinates does not match number of microphones according to imported weights!')
%        end
%    end
end