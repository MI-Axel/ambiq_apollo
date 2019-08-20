function [ beamformer ] = create_beamformer( MIC_ARRAY, METHOD, C, FFT_LEN, ANGLE_TAR, ...
    SIGNAL_BEAM_WIDTH, SPEECH_LEVEL, DIFFUSE_NOISE_LEVEL)
% create_beamformer

beamformer.mic_array = MIC_ARRAY;

beamformer.method = METHOD;

beamformer.speed_sound = C;
beamformer.nfft = FFT_LEN;

beamformer.angle_tar = ANGLE_TAR;
beamformer.beamwidth = SIGNAL_BEAM_WIDTH;
beamformer.src_cart = [cosd(ANGLE_TAR); sind(ANGLE_TAR)];   % cartesian coordinates for source (far-field assumption will be used)
    
beamformer.signal_std = 10 ^ ( (SPEECH_LEVEL - 94) / 20 );
beamformer.diffuse_noise_std = 10 ^ ( (DIFFUSE_NOISE_LEVEL - 94) / 20 );


end

