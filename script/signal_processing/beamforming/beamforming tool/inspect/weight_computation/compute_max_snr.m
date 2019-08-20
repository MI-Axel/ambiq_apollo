function [ BF ] = compute_max_snr( BF, progress_bar )
% compute_max_snr - Compute MAXSNR weights for given beamformer
% structure.

if nargin < 2
    progress_bar = true;
end

global NUM_MICS
global A;
global b;
global DIFFUSE_NOISE_STD
global MIC_NOISE_STD;
global SIGNAL_STD;

ARR = BF.mic_array;

if ~isfield(BF, 'freqs')
    BF.freqs = (0:(BF.nfft/2)) * (ARR.samp_freq/BF.nfft);
end
BF.num_freqs = length(BF.freqs);
BF.freq_domain = true; % frequency domain weights

NUM_ANGLES = BF.num_angles;
if isfield(BF, 'angles')
    angles = BF.angles(:);  % column vector
else
    angles = ((0:(NUM_ANGLES-1)) * (360/NUM_ANGLES))';
end


% % use MVDR as initialization
% BF = compute_mvdr( ARR, BF );

% distinguish between angles that contain signal and those that do not
b = zeros(NUM_ANGLES, 1);
upper_beam_edge = mod(BF.angle_tar + (BF.beamwidth / 2), 360);
lower_beam_edge = mod(BF.angle_tar - (BF.beamwidth / 2), 360);
if upper_beam_edge < lower_beam_edge
    b( angles > lower_beam_edge | angles < upper_beam_edge ) = 1;
else
    b( angles > lower_beam_edge & angles < upper_beam_edge ) = 1;
end
if strcmp( ARR.geometry, 'LINEAR' ) % spatial ambiguity
    LOOK_ANGLE_BACK = 360 - BF.angle_tar;
    upper_beam_edge = mod(LOOK_ANGLE_BACK + (BF.beamwidth / 2), 360);
    lower_beam_edge = mod(LOOK_ANGLE_BACK - (BF.beamwidth / 2), 360);
    
    if upper_beam_edge < lower_beam_edge
        b( angles >= lower_beam_edge | angles < upper_beam_edge ) = 1;
    else
        b( angles >= lower_beam_edge & angles < upper_beam_edge ) = 1;
    end
end

NUM_MICS = ARR.num_mics;
DIFFUSE_NOISE_STD = BF.diffuse_noise_std / sqrt(NUM_ANGLES);
SIGNAL_STD = BF.signal_std / sum(b);
MIC_NOISE_STD = sqrt(ARR.noise_var);


%% interpolate to find directivities for eval and test angles
DIR = zeros(BF.num_freqs, NUM_ANGLES, ARR.num_mics);
freq_points = repmat(ARR.directivities.frequencies',1,length(ARR.directivities.angles));
angle_points = repmat(ARR.directivities.angles,length(ARR.directivities.frequencies),1);
eval_freq_points = repmat(BF.freqs',1,NUM_ANGLES);
eval_angle_points = repmat(angles',BF.num_freqs,1);
for m = 1:ARR.num_mics
    V = squeeze(ARR.directivities.patterns(m,:,:));
    DIR(:,:,m) =  interp2(angle_points, freq_points, V, eval_angle_points, eval_freq_points);
end

%% compute steering vectors
steer_tot = compute_steering_vectors( angles, BF.freqs, ARR.pos, BF.speed_sound, ARR.directivities );

%% compute weights
if progress_bar
    h = waitbar(0,'1','Name','Computing MAXSNR weights...',...
                'CreateCancelBtn',...
                'setappdata(gcbf,''canceling'',1)');
    setappdata(h,'canceling',0)
end

BF.weights = zeros(ARR.num_mics, BF.num_freqs);
for k = 1:BF.num_freqs
    
    fprintf('Bin %i out of %i\n', k, BF.num_freqs)
    
    % Check for Cancel button press
    if progress_bar
        if getappdata(h,'canceling')
            delete(h)
            BF = rmfield(BF, 'weights');
            return
        end
        waitbar(k / BF.num_freqs,h,sprintf('%d/%d',k,BF.num_freqs))
    end
    
    f = BF.freqs(k);
    
    A = squeeze(steer_tot(k,:,:));
    
    if (k == 1)
        % First frequency bin assume we average microphones
        x0 = [ones(ARR.num_mics, 1); zeros(ARR.num_mics, 1)] / ARR.num_mics;
    end
    
    %options = optimset('MaxIter', 1e3, 'MaxFunEvals', 1e3, 'TolFun', 1e-4, 'TolX', 1e-6, 'PlotFcns', @optimplotfval );
    options = optimset;
    x = fminsearch(@snr_function, x0, options);
    
    % initialize next iteration to last one's result
    x0 = x;
    
    % Turn into complex data
    xr = x(1:ARR.num_mics);
    xi = x(ARR.num_mics+1:end);
    
    x = xr + sqrt(-1) * xi;
    
    % Scale for unity gain in look direction
    bhat = A * x;
    x = x / max(abs(bhat));

    BF.weights(:, k) = x;
end

% close waitbar
if progress_bar
    delete(h) 
end

end


% ----------------------------------------------------------------------
% Optimization function
% ----------------------------------------------------------------------
function ISNR = snr_function(X)

global NUM_MICS;
global A;
global b;
global SIGNAL_STD;
global DIFFUSE_NOISE_STD;
global MIC_NOISE_STD;

% Turn into complex data
Xr = X(1:NUM_MICS);
Xi = X(NUM_MICS+1:end);

X = Xr + sqrt(-1) * Xi;

A_signal = A(b==1, :);

% Assume that the signals add coherently
signal_energy = abs(sum(SIGNAL_STD * A_signal * X))^2;

% Assume that noises sum incoherently
diffuse_noise_energy = sum(abs(A * X * DIFFUSE_NOISE_STD).^2);

mic_noise_energy = sum(abs(MIC_NOISE_STD * X).^2);

SNR = 10 * log10(signal_energy / (diffuse_noise_energy + mic_noise_energy));

ISNR = -SNR;

end

