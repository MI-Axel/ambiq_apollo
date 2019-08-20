function polarax = plot_polar_plots( BF, FREQS, LOWER_BOUND )
%PLOT_POLAR_PLOTS plot polar plots for a given set of frequencies

angles = 0:360;
legend_text = [];

if nargin < 3
    LOWER_BOUND = -20; % dB
end

figure;
polarplot([0 pi/2 pi],[1 2 3])   % create PolarAxes object
polarax = gca;
for k = 1:length(FREQS)
    
    f = FREQS(k);
    
    legend_text = [legend_text; {[num2str(f), ' Hz']}];
    
    % compute steering vectors
    steer = compute_steering_vectors( angles, f, BF.mic_array.pos, BF.speed_sound, BF.mic_array.directivities );
    
    % select appropriate weights and compute directivity
    [~, fidx] = min(abs(BF.freqs-f)); % convert to index for corresponding weights
    weights = BF.weights(:,fidx);
    resp = abs(steer*weights);
    resp_dB = 20*log10(resp);
    resp_dB(resp_dB<LOWER_BOUND) = LOWER_BOUND;
    
    % plot
    polarplot(polarax, angles*pi/180,resp_dB)
    hold(polarax, 'on')

end
polarax.RLim = [LOWER_BOUND,0];
polarax.RTick = LOWER_BOUND:5:0;
legend(legend_text, 'Location', 'northeastoutside')
polarplot([BF.angle_tar*pi/180, BF.angle_tar*pi/180], [0, 1], 'k--')
hold('off')
axis('tight')
polarax.RLim = [LOWER_BOUND,0];
polarax.RTick = LOWER_BOUND:2:0;


