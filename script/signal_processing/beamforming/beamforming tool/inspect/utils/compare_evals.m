function compare_evals( BF, EVALS, LABELS, PLT_COMPARE )

if nargin < 3
    PLT_COMPARE.filter_responses = true;
    PLT_COMPARE.frequency_responses = true;
    PLT_COMPARE.heatmap_2d = true;
    PLT_COMPARE.heatmap_3d = true;
    PLT_COMPARE.mic_arrays = true;
    PLT_COMPARE.beam_patterns = true;
    PLT_COMPARE.snr = true;
    PLT_COMPARE.snr_gain = true;
    PLT_COMPARE.directivity_idx = true;
    PLT_COMPARE.beamwidth = true;
    PLT_COMPARE.uncorrelated_noise_gain = true;
    PLT_COMPARE.ambient_noise_gain = true;
    PLT_COMPARE.total_noise_gain = true;
end

if length(EVALS) ~= length(LABELS)
    error('Number of eval structs should be equal to number of labels! Each struct should have a label.');
end

%% comparisons that cannot be put on one figure
PLT = PLT_COMPARE;
PLT.frequency_responses = false;
PLT.beam_patterns = false;
PLT.snr = false;
PLT.snr_gain = false;
PLT.directivity_idx = false;
PLT.beamwidth = false;
PLT.uncorrelated_noise_gain = false;
PLT.ambient_noise_gain = false;
PLT.total_noise_gain = false;
for k = 1:length(EVALS)
    plot_eval( BF{k}, EVALS{k}, LABELS{k}, PLT )
end

%% comparisons that can be put on one figure
if PLT_COMPARE.mic_arrays || PLT_COMPARE.frequency_responses || PLT_COMPARE.beam_patterns || ...
        PLT_COMPARE.snr || PLT_COMPARE.snr_gain || ...
        PLT_COMPARE.directivity_idx || PLT_COMPARE.beamwidth ...
        || PLT_COMPARE.uncorrelated_noise_gain || ...
        PLT_COMPARE.ambient_noise_gain || PLT_COMPARE.total_noise_gain
    
%     fig_handle = figure('Name', [LABELS{1} '     vs.     ' LABELS{2}],...
%         'NumberTitle','off', 'Position', [80, 150, 800, 600]);
    fig_handle = figure('Name', 'Beamformer Design Comparison',...
        'NumberTitle','off', 'Position', [80, 150, 800, 600]);
    tg = uitabgroup;
  
end


if PLT_COMPARE.mic_arrays
    
    color = ['b','r','g','c','m','k','y'];
    shape = ['v','^','<','>','s','d'];
    mic_arrays_tab = uitab(tg, 'Title', 'Mic Arrays');
    axes('Parent',mic_arrays_tab);
    
    for b_idx = 1:length(BF)
        pos = BF{b_idx}.mic_array.pos;
        plot(pos(:,1),pos(:,2),shape(b_idx),'MarkerFaceColor',color(b_idx))
        hold('on')
    end
    
    legend(LABELS, 'Location', 'eastoutside')
    title('Microphone positions')
    xlabel('Meters')
    ylabel('Meters')
    axis('tight')
    axis('square')
    hold('off')
    grid('on')
end


function plot_freq_resps(hObj, event)
    
    dev = event.AffectedObject.Value;
    look_angle = mod(BF{1}.angle_tar + event.AffectedObject.Value,360);
    
    freq_resps = zeros(length(EVALS{1}.freqs),length(BF));
    src = [cosd(look_angle); sind(look_angle)];
    
    for b_idx = 1:length(BF)
        
        for k = 1:length(EVALS{1}.freqs_log)
        
            f = EVALS{1}.freqs_log(k);

            % convert to index for corresponding weights
            [~, fidx] = min(abs(BF{b_idx}.freqs-f));
            weights = BF{b_idx}.weights(:,fidx);

            % compute response
            delays = BF{b_idx}.mic_array.pos*src/BF{b_idx}.speed_sound;
            steer = exp(1i*2*pi*f*delays);
            freq_resps(k, b_idx) = 20*log10(abs(transpose(steer)*weights)+eps);
            
        end
        
    end
    
    % plot
    for b_idx = 1:length(BF)
        semilogx(freqtabax, EVALS{b_idx}.freqs_log, freq_resps(:,b_idx))
        hold(freqtabax, 'on')
    end
    if dev > 0
        title(freqtabax, ['Frequency response for (target + ' num2str(abs(dev),3) ') degrees']);
    elseif dev < 0
        title(freqtabax, ['Frequency response for (target - ' num2str(abs(dev),3) ') degrees']);
    else
        title(freqtabax, ['Frequency response for target direction']);
    end
    legend(freqtabax, LABELS, 'Location', 'south')
    hold(freqtabax, 'off')
    axis(freqtabax, 'tight')
    grid(freqtabax, 'on')
    ylim(freqtabax, [-24,min(max(freq_resps(:)),3)])
    xlim(freqtabax, [min(EVALS{1}.freqs), max(EVALS{1}.freqs)]);
    xlabel(freqtabax, 'Frequency [Hz]')
    ylabel(freqtabax, 'dB')
    
end

if PLT_COMPARE.frequency_responses
    
    freqtab = uitab(tg, 'Title', 'Freq. Resp.');
    freqtabax = axes('Parent',freqtab);
    
    % initialize plot
    event.AffectedObject.Value = 0;
    plot_freq_resps([], event)

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
    addlistener(b,'Value','PostSet', @plot_freq_resps);
    
end


function plot_polar_plots(hObj, event)
    
    f = event.AffectedObject.Value;
    
    resp = zeros(length(EVALS{1}.angles),length(BF));
    for b_idx = 1:length(BF)
        
        % compute steering vectors
        steer = compute_steering_vectors( EVALS{1}.angles, f, BF{b_idx}.mic_array.pos, BF{b_idx}.speed_sound );

        % select appropriate weights and compute directivity
        [~, fidx] = min(abs(BF{b_idx}.freqs-f)); % convert to index for corresponding weights
        weights = BF{b_idx}.weights(:,fidx);
        resp(:,b_idx) = abs(steer*weights);
        
    end
    
    % plot
    lower_bound = -10;
    polartabax.RLim = [lower_bound,0];
    for b_idx = 1:length(BF)
        
        resp_dB = 20*log10(resp(:,b_idx));
        resp_dB(resp_dB<lower_bound) = lower_bound;
        
        polarplot(polartabax, EVALS{1}.angles*pi/180,resp_dB)
        hold(polartabax, 'on')
    end
    
    title(polartabax, ['Polar plot [dB] : ' num2str(f,3) ' Hz']);
    polarplot(polartabax,[EVALS{1}.angle_tar*pi/180, EVALS{1}.angle_tar*pi/180], [lower_bound, 0], 'k--')
    legend(polartabax, LABELS, 'Location', 'southoutside')
    hold(polartabax, 'off')
    axis(polartabax, 'tight')
    
    polartabax.ThetaTick = (0:45:315);
    polartabax.RTick = [-10,-6,-3,0];
end

if PLT_COMPARE.beam_patterns
    
    polartab = uitab(tg, 'Title', 'Polar plot');
    axes('Parent',polartab);
    polarplot([0 pi/2 pi],[1 2 3])   % create PolarAxes object
    polartabax = gca;
    
    event.AffectedObject.Value = min(max(EVALS{1}.freqs),1000);
    plot_polar_plots([], event)

    bgcolor = fig_handle.Color;
    bl3 = uicontrol('Parent',polartab,'Style','text','Position',[44.8,30,100,23],...
                    'String','Frequency [Hz]','BackgroundColor',bgcolor,'FontWeight','bold');
    bl1 = uicontrol('Parent',polartab,'Style','text','Position',[10.4,10.8,38.6,17.2],...
                    'String',num2str(min(EVALS{1}.freqs)),'BackgroundColor',bgcolor);
    bl2 = uicontrol('Parent',polartab,'Style','text','Position',[200.2,14,40.8,14.2],...
                    'String',num2str(max(EVALS{1}.freqs)),'BackgroundColor',bgcolor);
    b = uicontrol('Parent',polartab,'Style','slider','Position',[50.4,10,148,25],...
        'value',event.AffectedObject.Value, 'min',min(EVALS{1}.freqs), 'max',max(EVALS{1}.freqs));
    addlistener(b,'Value','PostSet', @plot_polar_plots);
    
end



function plot_snrs(hObj, event)
    
    dev = event.AffectedObject.Value;
    look_angle = mod(BF{1}.angle_tar + event.AffectedObject.Value,360);
    
    snrs = zeros(length(EVALS{1}.freqs_log),length(BF));
     
    for k = 1:length(EVALS{1}.freqs_log)

        f = EVALS{1}.freqs_log(k);
        
        for b_idx = 1:length(BF)
            
            % convert to index for corresponding weights
            [~, fidx] = min(abs(BF{b_idx}.freqs-f));
            W = BF{b_idx}.weights(:,fidx);
            
            % compute snr
            snrs(k, b_idx) = compute_snr(W, BF{b_idx}.mic_array, ...
                look_angle, f, BF{b_idx}.diffuse_noise_std^2, ...
                BF{b_idx}.signal_std^2, BF{b_idx}.speed_sound);
            
        end
        
    end
    
    % plot
    for b_idx = 1:length(BF)
        semilogx(snr_ax, EVALS{1}.freqs_log, snrs(:,b_idx))
        hold(snr_ax, 'on')
    end
    if dev > 0
        title(snr_ax, ['SNR for (' + num2str(BF{1}.angle_tar,3) + ' + ' num2str(abs(dev),3) ') degrees'])
    elseif dev < 0
        title(snr_ax, ['SNR for (' + num2str(BF{1}.angle_tar,3) + ' - ' num2str(abs(dev),3) ') degrees'])
    else
        title(snr_ax, sprintf('SNR for %d degrees',BF{1}.angle_tar))
    end
    legend(snr_ax, LABELS, 'Location', 'south')
    hold(snr_ax, 'off')
    axis(snr_ax, 'tight')
    grid(snr_ax, 'on')
    ylim(snr_ax, [-6, max(maxValSNR, max(snrs(:)))]);
    xlim(snr_ax, [min(EVALS{1}.freqs_log), max(EVALS{1}.freqs_log)]);
    xlabel(snr_ax, 'Frequency [Hz]')
    ylabel(snr_ax, 'dB')
    
end


if PLT_COMPARE.snr
    snrtab = uitab(tg, 'Title', 'SNR');
    snr_ax = axes('Parent',snrtab);
    
    % initialize plot
    event.AffectedObject.Value = 0;
    maxValSNR = 0; snrs= 0;
    plot_snrs([], event)
    
    maxValSNR = max(snrs(:));
    
    
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
    addlistener(b,'Value','PostSet', @plot_snrs);
end



function plot_snr_gains(hObj, event)
    
%     alpha = 10^(event.AffectedObject.Value);   % ratio of mic noise
    alpha = event.AffectedObject.Value;
    SNR_gain = zeros(length(EVALS{1}.freqs_log),length(BF));
    
    for f_idx = 1:length(EVALS{1}.freqs_log)
        
        f = EVALS{1}.freqs_log(f_idx);
        
        for b_idx = 1:length(BF)
        
            % convert to index for corresponding weights
            [~, fidx] = min(abs(BF{b_idx}.freqs-f)); 
            W = BF{b_idx}.weights(:,fidx);

            % steering vectors under far-field assumption
            d = compute_steering_vectors(BF{b_idx}.angle_tar, f, BF{b_idx}.mic_array.pos, BF{b_idx}.speed_sound)';

            % isotropic noise
            Phi = (1-alpha)*sinc(2*pi*f*BF{b_idx}.mic_array.edm/BF{b_idx}.speed_sound / pi); % matlab uses normalized sinc

            % self noise
            DL = alpha*eye(BF{b_idx}.mic_array.num_mics);

            % compute SNR gain
            SNR_gain(f_idx,b_idx) = abs(W'*(d*d')*W) / abs(W'*(Phi + DL)*W);
            SNR_gain(f_idx,b_idx) = 10 * log10(SNR_gain(f_idx,b_idx));
        
        end
    end
    
    % plot
    for b_idx = 1:length(BF)
        semilogx(snrgainaxes, EVALS{1}.freqs_log, SNR_gain(:,b_idx));
        hold(snrgainaxes, 'on')
    end
    grid(snrgainaxes, 'on')
    title(snrgainaxes, ['SNR gain : \alpha = ' num2str(alpha,3)]);
    legend(snrgainaxes, LABELS, 'Location', 'south')
    xlabel(snrgainaxes, 'Frequency (Hz)');
    ylabel(snrgainaxes, 'dB');
    axis(snrgainaxes, 'tight')
    ylim(snrgainaxes, [ min(min(SNR_gain(:)), 0), max(0,max(SNR_gain(:)))] );
    hold(snrgainaxes, 'off')
    
end

if PLT_COMPARE.snr_gain
    snrgaintab = uitab(tg, 'Title', 'SNR Gain');
    snrgainaxes = axes('Parent',snrgaintab);
    
%     event.AffectedObject.Value = log10(BF{1}.mic_array.noise_var^2 / (BF{1}.diffuse_noise_std^2 + BF{1}.mic_array.noise_var));
    event.AffectedObject.Value = BF{1}.mic_array.noise_var / (BF{1}.diffuse_noise_std^2 + BF{1}.mic_array.noise_var);
    plot_snr_gains([], event)
    
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
    addlistener(b,'Value','PostSet', @plot_snr_gains);
end



function plot_directivities(hObj, event)
    
    dev = event.AffectedObject.Value;
    look_angle = mod(BF{1}.angle_tar + event.AffectedObject.Value,360);
    [~,lookidx]=min(abs(EVALS{1}.angles-look_angle));
    angle_res = EVALS{1}.angles(2)-EVALS{1}.angles(1);
    
    directivities = zeros(length(EVALS{1}.freqs),length(BF));
    
    for b_idx = 1:length(BF)
        
        for k = 1:length(EVALS{1}.freqs_log)
        
            % compute directivity index (uses beam patterns so need to use
            % linear frequency spacing)
            D = EVALS{b_idx}.patterns_log(lookidx,k)^2 / ...
                (sum(EVALS{1}.patterns_log(2:length(EVALS{b_idx}.angles),k).^2)*angle_res) * 360;
            directivities(k, b_idx) = 10*log10( D );
            
        end
        
    end
    
    % plot
    for b_idx = 1:length(BF)
        semilogx(directivity_ax, EVALS{b_idx}.freqs_log, directivities(:,b_idx))
        hold(directivity_ax, 'on')
    end
    if dev > 0
        title(directivity_ax, ['Directivity for (target + ' num2str(abs(dev),3) ') degrees'])
    elseif dev < 0
        title(directivity_ax, ['Directivity for (target - ' num2str(abs(dev),3) ') degrees'])
    else
        title(directivity_ax, ['Directivity for target direction'])
    end
    legend(directivity_ax, LABELS, 'Location', 'south')
    hold(directivity_ax, 'off')
    axis(directivity_ax, 'tight')
    grid(directivity_ax, 'on')
    ylim(directivity_ax, [-6, max(maxVal, max(directivities(:)))]);
    xlim(directivity_ax, [min(EVALS{1}.freqs_log), max(EVALS{1}.freqs_log)]);
    xlabel(directivity_ax, 'Frequency [Hz]')
    ylabel(directivity_ax, 'dB')
    
end


if PLT_COMPARE.directivity_idx
    directivity_tab = uitab(tg, 'Title', 'Directivity');
    directivity_ax = axes('Parent',directivity_tab);
    
    % initialize plot
    event.AffectedObject.Value = 0;
    maxVal = 0; directivities= 0;
    plot_directivities([], event)
    
    maxVal = max(directivities(:));
    
    
    bgcolor = fig_handle.Color;
    bl3 = uicontrol('Parent',directivity_tab,'Style','text','Position',[1.8,22,147,18],...
                    'String','Deviation from target [degrees]','BackgroundColor',bgcolor,...
                    'FontSize', 7, 'FontWeight','bold');
    bl1 = uicontrol('Parent',directivity_tab,'Style','text','Position',[0.4,3.8,25.8,17.2],...
                    'String','-180','BackgroundColor',bgcolor);
    bl2 = uicontrol('Parent',directivity_tab,'Style','text','Position',[117.2,2.2,34.2,18],...
                    'String','+180','BackgroundColor',bgcolor);
    b = uicontrol('Parent',directivity_tab,'Style','slider','Position',[26.8,4.2,90.2,18.4],...
        'value',event.AffectedObject.Value, 'min',-180, 'max',180);
    addlistener(b,'Value','PostSet', @plot_directivities);
end


if PLT_COMPARE.beamwidth
    bwtab = uitab(tg, 'Title', 'Beam width');
    axes('Parent',bwtab);
    for k = 1:length(EVALS)
        semilogx(EVALS{k}.freqs_log, EVALS{k}.beam_width);
        hold on
    end
    semilogx(EVALS{k}.freqs_log, EVALS{k}.signal_beamwidth*ones(length(EVALS{k}.freqs_log),1), 'g-');
    legend([LABELS,'Signal Beamwidth'], 'Location', 'north')
    title('Beam width as a function of frequency');
    grid
    xlabel('Frequency (Hz)');
    ylabel('degrees');
    hold off
    axis tight
end


if PLT_COMPARE.uncorrelated_noise_gain
    uncorrelatedtab = uitab(tg, 'Title', 'Uncorrelated Noise Gain');
    axes('Parent',uncorrelatedtab);
    for k = 1:length(EVALS)
        semilogx(EVALS{k}.freqs_log, EVALS{k}.uncorrelated_noise_gain);
        hold on
    end
    legend(LABELS, 'Location', 'north')
    title('Uncorrelated Noise Gain');
    grid
    xlabel('Frequency (Hz)');
    ylabel('dB');
    hold off
    axis tight
end

if PLT_COMPARE.ambient_noise_gain
    ambienttab = uitab(tg, 'Title', 'Ambient Noise Gain');
    axes('Parent',ambienttab);
    for k = 1:length(EVALS)
        semilogx(EVALS{k}.freqs_log, EVALS{k}.ambient_noise_gain);
        hold on
    end
    legend(LABELS, 'Location', 'north')
    title('Ambient Noise Gain');
    grid
    xlabel('Frequency (Hz)');
    ylabel('dB');
    hold off
    axis tight
end

if PLT_COMPARE.total_noise_gain
    noisetab = uitab(tg, 'Title', 'Total Noise Gain');
    axes('Parent',noisetab);
    for k = 1:length(EVALS)
        semilogx(EVALS{k}.freqs_log, EVALS{k}.total_noise_gain);
        hold on
    end
    legend(LABELS, 'Location', 'north')
    title('Total Noise Gain');
    grid
    xlabel('Frequency (Hz)');
    ylabel('dB');
    hold off
    axis tight
end


end