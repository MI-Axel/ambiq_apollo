function [ BF ] = cvx_approach( BF, progress_bar )
% cvx_approach

if nargin < 2
    progress_bar = true;
end

warning('off','all')

% check if CVX is installed
try
    cvx_begin
    cvx_end
catch err
    msgbox('CVX Toolbox is not installed! Please go to their website (http://cvxr.com/cvx/download/) and follow their instructions (unpack in an empty directory and run the ''cvx_setup'' script).',...
        'CVX Toolbox not installed!')
    warning('on','all')
    rethrow(err);
end

ARR = BF.mic_array;

%% discretization for optimization
if isfield(BF, 'angles')
    angles = BF.angles(:);  % column vector
else
    angles = ((0:(BF.num_angles-1)) * (360/BF.num_angles))';
end
if ~isfield(BF, 'freqs_opt')
    BF.freqs_opt = linspace(0, ARR.samp_freq/2, BF.num_freqs);
end
if isfield(BF, 'freqs')
    BF.freqs_opt = BF.freqs;
    BF.num_freqs = length(BF.freqs_opt);
end

%% compute steering vectors
if BF.min_beamwidth
    steer_tot = compute_steering_vectors( angles, BF.freqs_opt, ARR.pos, BF.speed_sound, ARR.directivities );
else
    steer_tot = compute_steering_vectors( BF.angle_tar, BF.freqs_opt, ARR.pos, BF.speed_sound, ARR.directivities );
end

%% optimization bin by bin
if BF.min_beamwidth
    bw = BF.beamwidth;
end
WCoefs = zeros(ARR.num_mics,BF.num_freqs);
BF.freq_domain = true; % frequency domain weights

if progress_bar
    h = waitbar(0,'1','Name','Computing CVX weights...',...
                'CreateCancelBtn',...
                'setappdata(gcbf,''canceling'',1)');
    setappdata(h,'canceling',0)
end
    
for idx = 1:BF.num_freqs
    
    fprintf('Bin %i out of %i\n', idx, BF.num_freqs)
    
    % Check for Cancel button press
    if progress_bar
        if getappdata(h,'canceling')
            delete(h)
            try
                cvx_end
                return
            catch
                return
            end
        end
        waitbar(idx / BF.num_freqs,h,sprintf('%d/%d',idx,BF.num_freqs))
    end

    % MVDR approach with white noise constraint
    % may need to fix cvx with this snippet : http://ask.cvxr.com/t/cholinc-in-quad-form-m-has-been-removed-in-matlab-13/196/2
    Phi = BF.diffuse_noise_std * ...
        sinc(2*pi*BF.freqs_opt(idx)*ARR.edm/BF.speed_sound/pi) ...
        + sqrt(ARR.noise_var)*eye(ARR.num_mics);
    
    if BF.min_beamwidth

        dp = squeeze(steer_tot(idx,:,:));
        
        while bw <= 360 && bw >= 0
            
            % passband indices
            upper_beam_edge = mod(BF.angle_tar + bw/2, 360);
            lower_beam_edge = mod(BF.angle_tar - bw/2, 360);
            if upper_beam_edge < lower_beam_edge
                thetaPassInd = find( angles >= lower_beam_edge | angles < upper_beam_edge );
            else
                thetaPassInd = find( angles >= lower_beam_edge & angles < upper_beam_edge );
            end
            
            % stopband indices
            upper_beam_edge = mod(BF.angle_tar + bw/2 + BF.transition_width, 360);
            lower_beam_edge = mod(BF.angle_tar - bw/2 - BF.transition_width, 360);
            if upper_beam_edge < lower_beam_edge
                thetaStopInd = find( ~(angles >= lower_beam_edge | angles < upper_beam_edge) );
            else
                thetaStopInd = find( ~(angles >= lower_beam_edge & angles < upper_beam_edge) );
            end
            
            % Passband and stopband steering matrices
            Dstop = dp(thetaStopInd,:);
            Dpass = dp(thetaPassInd,:);
            
            cvx_begin quiet
            variable w(ARR.num_mics) complex
            minimize(w'*Phi*w)
            subject to
            if isfield(BF, 'pass_ripple')
                norm(Dpass*w - 1,2) <= BF.pass_ripple;
            else
                norm(Dpass*w - 1,2) <= 0;
            end
            norm(Dstop*w, inf) <= 1;
            
            if isfield(BF, 'wng')
                norm(w,2) <= BF.wng;
            end
            cvx_end
            
            if strfind(cvx_status,'Solved')
                break;
            else % infeasible
                bw = bw - 2;
                fprintf(1,'Problem is not feasible; reducing beamwidth to %i.\n', bw);
            end
            
        end
        
        
    else

        dp_tar = squeeze(steer_tot(idx,:,:));
        
        cvx_begin quiet
        variable w(ARR.num_mics) complex
        minimize(w'*Phi*w)
        subject to
        dp_tar*w == 1;
        if isfield(BF, 'wng')
            norm(w,2) <= BF.wng;
        end
        cvx_end
        
    end
    
    
    if strfind(cvx_status,'Solved') % feasible
        WCoefs(:,idx) = w;
    else % infeasible, keep weights as zero
        fprintf(1,'Problem is not feasible for frequency %d\n', num2str(BF.freqs_opt(idx),3));
    end
    
end

% close waitbar
if progress_bar
    delete(h) 
end

BF.weights_opt = WCoefs;

warning('on','all')

% map to nfft/2 + 1 bins for frequency domain processing
if ~isfield(BF, 'freqs')
    BF.freqs = (0:(BF.nfft/2)) * (ARR.samp_freq/BF.nfft);
end
BF.num_freqs = length(BF.freqs);
BF.weights = zeros(ARR.num_mics, BF.num_freqs);
for k = 1:BF.num_freqs
    [~, fidx] = min(abs(BF.freqs_opt-BF.freqs(k)));
    BF.weights(:,k) = BF.weights_opt(:,fidx);
end



end



