function compute_snr_gain_180( BF, ratiosdB )
% compute SNR gain for linear array, pointing towards 0 degrees.

FREQS_log = logspace(log10(100), log10(8000), 500); % for log plots
SNR_gain = zeros(length(FREQS_log),1);



ratios = 10.^(ratiosdB/20);  % undB20
alphas = ratios ./ (1+ratios);  % ratio to fraction of uncorrelated noise

FREQS_log = logspace(log10(100), log10(8000), 500); % for log plots

figure;
maxSNRgain = -60;
legend_text = [];
for idx = 1:length(alphas)
    
    alpha = alphas(idx);
    legend_text = [legend_text; {[num2str(ratiosdB(idx)), ' dB']}];

    SNR_gain = zeros(length(FREQS_log),1);

    for k = 1:length(FREQS_log)

        f = FREQS_log(k);

        % convert to index for corresponding weights
        [~, fidx] = min(abs(BF.freqs-f)); 
        W = BF.weights(:,fidx);

        % steering vectors under far-field assumption
        d = compute_steering_vectors(BF.angle_tar, f, BF.mic_array.pos, BF.speed_sound, BF.mic_array.directivities)';

        % isotropic noise
        Phi = (1-alpha)*sinc(2*pi*f*BF.mic_array.edm/BF.speed_sound / pi); % matlab uses normalized sinc

        % self noise
        DL = alpha*eye(BF.mic_array.num_mics);

        % compute SNR gain
        SNR_gain(k) = abs(W'*(d*d')*W) / abs(W'*(Phi + DL)*W);
        SNR_gain(k) = 10 * log10(SNR_gain(k));

    end
    
    maxSNRgain = max(maxSNRgain, max(SNR_gain));

    % plot
    semilogx(FREQS_log, SNR_gain);
    hold('on')
    
end

grid('on')
title('SNR gain, varying uncorrelated:diffuse noise ratios');
xlabel('Frequency (Hz)');
ylabel('dB');
xlim([min(FREQS_log), max(FREQS_log)]);
ylim([ -3, maxSNRgain] );
legend(legend_text, 'Location', 'southeast')
hold('off')

end

