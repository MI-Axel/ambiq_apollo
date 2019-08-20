function empirical_vs_theoretical_snr_gain( BF, ANGLES, NUM_FREQS )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

    ANGLES = ANGLES(:);
    NUM_ANGLES = length(ANGLES);
    FREQS_log = logspace(log10(100), log10(8000), NUM_FREQS)';
    
    SNR_gain_theoretical = zeros(NUM_FREQS,1);
    SNR_gain_empirical = zeros(NUM_FREQS,1);
    
    for k = 1:NUM_FREQS
        [~, fidx] = min(abs(BF.freqs-FREQS_log(k))); % convert to index for corresponding weights
        weights = BF.weights(:,fidx);
        
        SNR_gain_theoretical(k) = compute_snr_gain( weights, BF.mic_array, BF.angle_tar, FREQS_log(k), BF.diffuse_noise_std^2, BF.speed_sound);
        
        %% compute empirical SNR gain
        d_tar = compute_steering_vectors(BF.angle_tar, FREQS_log(k), BF.mic_array.pos, BF.speed_sound)';
        numerator = abs(weights'*(d_tar*d_tar')*weights);
        
        total_noise_pwr = BF.diffuse_noise_std^2 + BF.mic_array.noise_var;
        diffuse_noise = 0;
        for t = 1:NUM_ANGLES
            d = compute_steering_vectors(ANGLES(t), FREQS_log(k), BF.mic_array.pos, BF.speed_sound)';
            diffuse_noise = diffuse_noise + BF.diffuse_noise_std^2*abs(weights'*(d*d')*weights);
        end
        diffuse_noise = diffuse_noise / NUM_ANGLES;
        denominator = ( diffuse_noise + BF.mic_array.noise_var*abs(weights'*weights) ) /total_noise_pwr;
        SNR_gain_empirical(k) = 10*log10(numerator / denominator);
        
        
    end
    
    figure;
    semilogx(FREQS_log,SNR_gain_theoretical)
    hold on
    semilogx(FREQS_log,SNR_gain_empirical)
    legend('Theoretical', 'Empirical', 'Location', 'southeast')
    title('SNR gain')
    xlabel('Frequency [Hz]')
    ylabel('dB')
    grid on
    axis tight
    hold off


end

