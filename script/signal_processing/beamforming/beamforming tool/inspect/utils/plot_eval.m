function plot_eval( BF, EVAL, LABEL, PLT )

if nargin < 4
    PLT.filter_responses = true;
    PLT.frequency_responses = true;
    PLT.heatmap_2d = true;
    PLT.heatmap_3d = true;
    PLT.beam_patterns = true;
    PLT.snr = true;
    PLT.snr_gain = true;
    PLT.directivity_idx = true;
    PLT.beamwidth = true;
    PLT.uncorrelated_noise_gain = true;
    PLT.ambient_noise_gain = true;
    PLT.total_noise_gain = true;
end

if PLT.filter_responses || PLT.frequency_responses || PLT.heatmap_2d || ...
      PLT.heatmap_3d || PLT.beam_patterns || PLT.snr || PLT.snr_gain || ...
      PLT.directivity_idx || PLT.beamwidth || PLT.uncorrelated_noise_gain || ...
      PLT.ambient_noise_gain || PLT.total_noise_gain
  
  fig_handle = figure('Name', LABEL,'NumberTitle','off',...
      'Position', [80, 120, 800, 650]);
  tg = uitabgroup;
  
else
    return;
end


%% --------------- FILTER RESPONSES --------------- %%

if PLT.filter_responses
    filtertab = uitab(tg, 'Title', 'Filter Resp.');
    axes('Parent',filtertab);
    num_mics = size(EVAL.magnitude_resp,1);
    for m = 1:num_mics
        subplot(num_mics,3,(m-1)*3+1)
        semilogx(EVAL.freq_scale, EVAL.magnitude_resp(m,:))
        if m==1
            title(['Mag Resp'])
        end
        xlabel('Hz')
        ylabel('dB')
        tix=get(gca,'ytick')';
        set(gca,'yticklabel',num2str(tix,'%.2f'))
        grid on
        axis tight
        
        subplot(num_mics,3,(m-1)*3+2)
        semilogx(EVAL.freq_scale, EVAL.phase_resp(m,:))
        if m==1
            title(['Phase Resp'])
        end
        xlabel('Hz')
        grid on
        axis tight
        
        subplot(num_mics,3,(m-1)*3+3)
        plot(EVAL.time_scale, EVAL.impulse_resp(m,:))
        if m==1
            title(['Impulse Resp'])
        end
        xlabel('Seconds')
        grid on
        axis tight
    end
    hold off
end


%% --------------- FREQUENCY RESPONSE --------------- %%

function plot_freq_resp(hObj,event)
    
    dev = event.AffectedObject.Value;
    look_angle = BF.angle_tar + event.AffectedObject.Value;
    
    if look_angle ~= BF.angle_tar
        freq_resp = zeros(length(EVAL.freqs_log),1);
        src = [cosd(look_angle); sind(look_angle)];

        for k = 1:length(EVAL.freqs_log)

            f = EVAL.freqs_log(k);

            % convert to index for corresponding weights
            [~, fidx] = min(abs(BF.freqs-f)); 
            weights = BF.weights(:,fidx);

            % compute response
            delays = BF.mic_array.pos*src/BF.speed_sound;
            steer = exp(1i*2*pi*f*delays); 
            freq_resp(k) = 20*log10(abs(transpose(steer)*weights)+eps);

        end
    else
        freq_resp = freq_resp_tar;
    end
    
    % plot
    if look_angle ~= BF.angle_tar
        semilogx(freqtabax, EVAL.freqs_log, freq_resp_tar)
        hold(freqtabax, 'on')
        semilogx(freqtabax, EVAL.freqs_log, freq_resp)
        if dev > 0
            legend(freqtabax, {'target', ['target + ' num2str(abs(dev),3)]}, 'Location', 'southeast')
        else
            legend(freqtabax, {'target', ['target - ' num2str(abs(dev),3)]}, 'Location', 'southeast')
        end
        title(freqtabax, ['Frequency responses']);
        hold(freqtabax, 'off')
    else
        semilogx(freqtabax, EVAL.freqs_log, freq_resp)
        title(freqtabax, ['Frequency response']);
        legend(freqtabax, {'target'}, 'Location', 'southeast')
    end
    xlabel(freqtabax, 'Frequency [Hz]')
    ylabel(freqtabax, 'dB')
    axis(freqtabax, 'tight')
    ylim(freqtabax, [-24,max(max(freq_resp),max(freq_resp_tar))])
    xlim(freqtabax, [min(EVAL.freqs_log), max(EVAL.freqs_log)]);
    grid(freqtabax, 'on')
end

if PLT.frequency_responses

    freqtab = uitab(tg, 'Title', 'Freq. Resp.');
    freqtabax = axes('Parent',freqtab);
    
    % frequency response for look angle for reference
    freq_resp_tar = zeros(length(EVAL.freqs_log),1);
    src_tar = [cosd(BF.angle_tar); sind(BF.angle_tar)];
    for j = 1:length(EVAL.freqs_log)
        frequency = EVAL.freqs_log(j);
        
        % convert to index for corresponding weights
        [~, f_idx] = min(abs(BF.freqs-frequency)); 
        W_k = BF.weights(:,f_idx);
        
        % compute response
        delays_tar = BF.mic_array.pos*src_tar/BF.speed_sound;
        steer_tar = exp(1i*2*pi*frequency*delays_tar);
        freq_resp_tar(j) = 20*log10(abs(transpose(steer_tar)*W_k)+eps);
    end
    
    % initialize plot
    event.AffectedObject.Value = 0;
    plot_freq_resp([], event)

    bgcolor = fig_handle.Color;
    bl3 = uicontrol('Parent',freqtab,'Style','text','Position',[1.8,22,147,18],...
                    'String','Deviation from target [degrees]','BackgroundColor',bgcolor,...
                    'FontSize', 7, 'FontWeight','bold');
    bl1 = uicontrol('Parent',freqtab,'Style','text','Position',[0.4,3.8,25.8,17.2],...
                    'String','-180','BackgroundColor',bgcolor);
    bl2 = uicontrol('Parent',freqtab,'Style','text','Position',[117.2,2.2,34.2,18],...
                    'String','+180','BackgroundColor',bgcolor);
    b = uicontrol('Parent',freqtab,'Style','slider','Position',[26.8,4.2,90.2,18.4],...
        'value',event.AffectedObject.Value, 'min',-180, 'max',180);
    addlistener(b,'Value','PostSet', @plot_freq_resp);

end

%% --------------- HEAT MAPS --------------- %%

if PLT.heatmap_2d
    
    %max_freq = min(4000,max(EVAL.freqs));
    max_freq = max(EVAL.freqs);
    frequencies = EVAL.freqs(EVAL.freqs<=max_freq);
    patterns = EVAL.patterns(:,EVAL.freqs<=max_freq);
    
%     max_freq = max(EVAL.freqs);
%     frequencies = EVAL.freqs;
%     patterns = EVAL.patterns;
    
    heatmap2dtab = uitab(tg, 'Title', 'Beam Patterns 2D');
    H = axes('Parent',heatmap2dtab);
    imagesc(frequencies, EVAL.angles, 20*log10(patterns));
    xlabel('Frequency (Hz)');
    ylabel('Angle (degrees)');
    title(['Beam patterns [dB]']);
    set(gca, 'XLim', [0 max_freq]);
%     colorbar
    grid
    caxis([-10 0])
%     colorbar(H)
    % Overlay with text annotations showing amplitudes
    XTick = get(gca, 'XTick');
    YTick = get(gca, 'YTick');
    for i=2:(length(XTick)-1)
        for j=1:length(YTick)
            Vq = interp2(frequencies, EVAL.angles, ...
                20*log10(patterns), XTick(i), YTick(j));
            ho = text(XTick(i), YTick(j), sprintf('%.2f', Vq));
            set(ho, 'HorizontalAlignment', 'center');
        end
    end
    axis tight
    hold off
end

if PLT.heatmap_3d
    heatmap3dtab = uitab(tg, 'Title', 'Beam Patterns 3D');
    H = axes('Parent',heatmap3dtab);
    patternsdB = 20*log10(EVAL.patterns);
    patternsdB(patternsdB<-40) = -40;
    waterfall(EVAL.freqs, EVAL.angles, patternsdB)
    xlabel('Frequency (Hz)');
    ylabel('Degrees');
    caxis([-20 0])
    title(['Beam patterns [dB]']);
    colorbar(H)
    axis tight
    set(gca,'zlim',[-40 0])
    hold off
end

%% --------------- POLAR PLOTS --------------- %%

function plot_polar_plot(hObj,event)
    
    f = event.AffectedObject.Value;
    
    % compute steering vectors
    steer = compute_steering_vectors( EVAL.angles, f, BF.mic_array.pos, BF.speed_sound, BF.mic_array.directivities );
    
    % select appropriate weights and compute directivity
    [~, fidx] = min(abs(BF.freqs-f)); % convert to index for corresponding weights
    weights = BF.weights(:,fidx);
    resp = abs(steer*weights);
    
    % plot
    lower_bound = -10;
    resp = 20*log10(resp);
    resp(resp<lower_bound) = lower_bound;
    polartabax.ThetaTick = (0:45:315);
    polartabax.RLim = [lower_bound,0];
    
    
    polarplot(polartabax, EVAL.angles*pi/180,resp)
    hold(polartabax, 'on')
    title(polartabax, ['Polar plot [dB] : ' num2str(f,3) ' Hz']);
    polarplot(polartabax,[EVAL.angle_tar*pi/180, EVAL.angle_tar*pi/180], [lower_bound, 0], 'k--')
    hold(polartabax, 'off')
    axis(polartabax, 'tight')
    
    polartabax.RTick = [-10,-6,-3,0];
end

if PLT.beam_patterns

    polartab = uitab(tg, 'Title', 'Polar plot');
    axes('Parent',polartab);
    polarplot([0 pi/2 pi],[1 2 3])   % create PolarAxes object
    polartabax = gca;
    
    event.AffectedObject.Value = min(max(EVAL.freqs),1000);
    plot_polar_plot([], event)

    bgcolor = fig_handle.Color;
    bl3 = uicontrol('Parent',polartab,'Style','text','Position',[51.8,30,100,23],...
                    'String','Frequency [Hz]','BackgroundColor',bgcolor,'FontWeight','bold');
    bl1 = uicontrol('Parent',polartab,'Style','text','Position',[10.4,10.8,12.8,17.2],...
                    'String','0','BackgroundColor',bgcolor);
    bl2 = uicontrol('Parent',polartab,'Style','text','Position',[170.2,14,40.8,14.2],...
                    'String','8000','BackgroundColor',bgcolor);
    b = uicontrol('Parent',polartab,'Style','slider','Position',[27.4,10,148,25],...
        'value',event.AffectedObject.Value, 'min',0, 'max',8000);
    addlistener(b,'Value','PostSet', @plot_polar_plot);

end


%% --------------- SNR --------------- %%

function plot_snr(hObj, event)
    
    dev = event.AffectedObject.Value;
    look_angle = mod(BF.angle_tar + event.AffectedObject.Value,360);
    
    snr = zeros(length(EVAL.freqs_log),1);
    if look_angle ~= BF.angle_tar
        for k = 1:length(EVAL.freqs_log)

            f = EVAL.freqs_log(k);

            % convert to index for corresponding weights
            [~, fidx] = min(abs(BF.freqs-f)); 
            W = BF.weights(:,fidx);

            % compute snr
            snr(k) = compute_snr(W, BF.mic_array, look_angle, f, ...
                BF.diffuse_noise_std^2, BF.signal_std^2, BF.speed_sound); 
        end
    else
        snr = snr_tar;
    end
    
    % plot
    if look_angle ~= BF.angle_tar
        semilogx(snr_ax, EVAL.freqs_log, snr_tar)
        hold(snr_ax, 'on')
        semilogx(snr_ax, EVAL.freqs_log, snr)
        if dev > 0
            legend(snr_ax, {'target', ['target + ' num2str(abs(dev),3)]}, 'Location', 'southeast')
        else
            legend(snr_ax, {'target', ['target - ' num2str(abs(dev),3)]}, 'Location', 'southeast')
        end
        hold(snr_ax, 'off')
    else
        semilogx(snr_ax, EVAL.freqs_log, snr_tar)
        legend(snr_ax, {'target'}, 'Location', 'southeast')
    end
    title(snr_ax, ['Signal-to-noise ratio']);
    xlabel(snr_ax, 'Frequency [Hz]')
    ylabel(snr_ax, 'dB')
    axis(snr_ax, 'tight')
    ylim(snr_ax, [-6, max(maxSNRVal, max(snr))]);
    xlim(snr_ax, [min(EVAL.freqs_log), max(EVAL.freqs_log)]);
    grid(snr_ax, 'on')
    
end

if PLT.snr

    snrtab = uitab(tg, 'Title', 'SNR');
    snr_ax = axes('Parent',snrtab);
    
    % SNR for look angle for reference
    snr_tar = zeros(length(EVAL.freqs_log),1);
    for i = 1:length(EVAL.freqs_log)
        
        f = EVAL.freqs_log(i);
        
        % convert to index for corresponding weights
        [~, fidx] = min(abs(BF.freqs-f)); 
        W = BF.weights(:,fidx);
        
        % compute snr
        snr_tar(i) = compute_snr(W, BF.mic_array, BF.angle_tar, f, ...
            BF.diffuse_noise_std^2, BF.signal_std^2, BF.speed_sound); 
    end
    
    % initialize plot
    event.AffectedObject.Value = 0;
    maxSNRVal = 0; snr = 0;
    plot_snr([], event)
    
    maxSNRVal = max(snr);

    bgcolor = fig_handle.Color;
    bl3 = uicontrol('Parent',snrtab,'Style','text','Position',[1.8,22,147,18],...
                    'String','Deviation from target [degrees]','BackgroundColor',bgcolor,...
                    'FontSize', 7, 'FontWeight','bold');
    bl1 = uicontrol('Parent',snrtab,'Style','text','Position',[0.4,3.8,25.8,17.2],...
                    'String','-180','BackgroundColor',bgcolor);
    bl2 = uicontrol('Parent',snrtab,'Style','text','Position',[117.2,2.2,34.2,18],...
                    'String','+180','BackgroundColor',bgcolor);
    b = uicontrol('Parent',snrtab,'Style','slider','Position',[26.8,4.2,90.2,18.4],...
        'value',event.AffectedObject.Value, 'min',-180, 'max',180);
    addlistener(b,'Value','PostSet', @plot_snr);

end

%% --------------- SNR GAIN --------------- %%

function plot_snr_gain(hObj, event)
    
    alpha = event.AffectedObject.Value;   % ratio of mic noise
    SNR_gain = zeros(length(EVAL.freqs_log),1);
    
    for k = 1:length(EVAL.freqs_log)
        
        f = EVAL.freqs_log(k);
        
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
    
    % plot
    semilogx(snrgainax, EVAL.freqs_log, SNR_gain);
    grid(snrgainax)
    title(snrgainax, ['SNR gain : \alpha = ' num2str(alpha,3)]);
    xlabel(snrgainax, 'Frequency (Hz)');
    ylabel(snrgainax, 'dB');
    xlim(snrgainax, [min(EVAL.freqs_log), max(EVAL.freqs_log)]);
    ylim(snrgainax, [ max(-6,min(SNR_gain)), max(maxSNRGain,max(SNR_gain))] );
    
end

if PLT.snr_gain
    snrgaintab = uitab(tg, 'Title', 'SNR Gain');
    snrgainax = axes('Parent',snrgaintab);
    
    event.AffectedObject.Value = BF.mic_array.noise_var / ...
        (BF.diffuse_noise_std^2 + BF.mic_array.noise_var);
    maxSNRGain = 0;
    plot_snr_gain([], event)
    maxSNRGain = max(SNR_gain);
    
    bgcolor = fig_handle.Color;
    b14 = uicontrol('Parent',snrgaintab,'Style','text','Position',[-7.6,21,230.6,16.6],...
                    'String','Mic Noise / (Mic Noise + Diffuse Noise)','BackgroundColor',bgcolor,...
                    'FontWeight','bold','FontSize',8);
    bl3 = uicontrol('Parent',snrgaintab,'Style','text','Position',[-12,2.6,52.4,21.6],...
                    'String','a','FontName','symbol','BackgroundColor',bgcolor,...
                    'FontWeight','bold','FontSize',12);
    bl1 = uicontrol('Parent',snrgaintab,'Style','text','Position',[28,1.8,12.8,17.2],...
                    'String','0','BackgroundColor',bgcolor);
    bl2 = uicontrol('Parent',snrgaintab,'Style','text','Position',[176.8,3.8,23.6,14.2],...
                    'String','1','BackgroundColor',bgcolor);
%     b = uicontrol('Parent',snrgaintab,'Style','slider','Position',[45,1,132,21],...
%         'value', event.AffectedObject.Value, 'min',log10(eps), 'max',log10(1));
    b = uicontrol('Parent',snrgaintab,'Style','slider','Position',[45,1,132,21],...
        'value', event.AffectedObject.Value, 'min',0, 'max',1);
    addlistener(b,'Value','PostSet', @plot_snr_gain);
end

%% --------------- DIRECTIVITY --------------- %%

function plot_directivity(hObj, event)
    
    dev = event.AffectedObject.Value;
    look_angle = mod(BF.angle_tar + event.AffectedObject.Value,360);
    [~,lookidx]=min(abs(EVAL.angles-look_angle));
    angle_res = EVAL.angles(2)-EVAL.angles(1);
    
    directivity_idx = zeros(length(EVAL.freqs_log),1);
    for k = 1:length(EVAL.freqs_log)
        % compute directivity index
        D = EVAL.patterns_log(lookidx,k)^2 / (sum(EVAL.patterns_log(2:length(EVAL.angles),k).^2)*angle_res) * 360;
        directivity_idx(k) = 10*log10( D );  
    end
    
    % plot
    semilogx(directivityax, EVAL.freqs_log, directivity_idx);
    if dev > 0
        title(directivityax, ['Directivity for (target + ' num2str(abs(dev),3) ') degrees'])
    elseif dev < 0
        title(directivityax, ['Directivity for (target - ' num2str(abs(dev),3) ') degrees'])
    else
        title(directivityax, ['Directivity for target direction'])
    end
    xlabel(directivityax, 'Frequency [Hz]')
    ylabel(directivityax, 'dB')
    axis(directivityax, 'tight')
    ylim(directivityax, [-6, max(maxVal, max(directivity_idx))]);
    xlim(directivityax, [min(EVAL.freqs_log), max(EVAL.freqs_log)]);
    grid(directivityax, 'on')
end

if PLT.directivity_idx

    directivitytab = uitab(tg, 'Title', 'Directivity');
    directivityax = axes('Parent',directivitytab);
    
    % initialize plot
    event.AffectedObject.Value = 0;
    maxVal = 0; directivity_idx= 0;
    plot_directivity([], event)
    
    maxVal = max(directivity_idx);

    bgcolor = fig_handle.Color;
    bl3 = uicontrol('Parent',directivitytab,'Style','text','Position',[1.8,22,147,18],...
                    'String','Deviation from target [degrees]','BackgroundColor',bgcolor,...
                    'FontSize', 7, 'FontWeight','bold');
    bl1 = uicontrol('Parent',directivitytab,'Style','text','Position',[0.4,3.8,25.8,17.2],...
                    'String','-180','BackgroundColor',bgcolor);
    bl2 = uicontrol('Parent',directivitytab,'Style','text','Position',[117.2,2.2,34.2,18],...
                    'String','+180','BackgroundColor',bgcolor);
    b = uicontrol('Parent',directivitytab,'Style','slider','Position',[26.8,4.2,90.2,18.4],...
        'value',event.AffectedObject.Value, 'min',-180, 'max',180);
    addlistener(b,'Value','PostSet', @plot_directivity);

end

%% --------------- BEAM WIDTH --------------- %%

if PLT.beamwidth
    bwtab = uitab(tg, 'Title', 'Beam width');
    bw_ax = axes('Parent',bwtab);
    semilogx(EVAL.freqs_log, EVAL.beam_width);
    hold on
    semilogx(EVAL.freqs_log, EVAL.signal_beamwidth*ones(length(EVAL.freqs_log),1), 'g-');
    title(['Beam width']);
    legend('Beamformer', 'Signal beam width', 'Location', 'north')
    grid
    xlabel('Frequency (Hz)');
    ylabel('degrees');
    axis tight
    ylim([0,360])
    hold off  
end

%% --------------- NOISE GAIN --------------- %%

if ~PLT.total_noise_gain
    if PLT.uncorrelated_noise_gain
        wngtab = uitab(tg, 'Title', 'Uncorrelated Noise Gain');
        axes('Parent',wngtab);
        semilogx(EVAL.freqs_log, EVAL.uncorrelated_noise_gain);
        title(['Uncorrelated Noise Gain']);
        grid
        xlabel('Frequency (Hz)');
        ylabel('dB');
%         tix=get(gca,'ytick')';
%         set(gca,'yticklabel',num2str(tix,'%.2f'))
        hold off
        axis tight
    end
    
    if PLT.ambient_noise_gain
        ambienttab = uitab(tg, 'Title', 'Ambient Noise Gain');
        axes('Parent',ambienttab);
        semilogx(EVAL.freqs_log, EVAL.ambient_noise_gain);
        title(['Ambient Noise Gain']);
        grid
        xlabel('Frequency (Hz)');
        ylabel('dB');
        hold off
        axis tight
    end
    
else
    noisetab = uitab(tg, 'Title', 'Noise Gain');
    axes('Parent',noisetab);
    semilogx(EVAL.freqs_log, EVAL.uncorrelated_noise_gain);
    hold on
    semilogx(EVAL.freqs_log, EVAL.ambient_noise_gain);
    semilogx(EVAL.freqs_log, EVAL.total_noise_gain);
    title(['Noise Gain']);
    legend(['Uncorrelated -  \sigma_I^2 = ' num2str(10*log10(EVAL.mic_noise_var),2) ' dB'], ...
        ['Ambient - \sigma_A^2 = ' num2str(10*log10(EVAL.diffuse_noise_var),2) ' dB'], ...
        'Total', 'Location', 'north')
    grid
    xlabel('Frequency (Hz)');
    ylabel('dB');
    hold off
    axis tight
end



end

