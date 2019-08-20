function [ mic_array ] = create_mic_array( GEOMETRY, NUM_MICS, SPACING, ROTATION, ...
    FS, MIC_NOISE_LEVEL, CENTER, DIRECTIVITIES_PATH, ORDERING, PLT )
% create_mic_array Create and return a microphone array structure.
%
%   Args: 
%       GEOMETRY : Array geometry - 'Circle', 'Linear', 'Triangle',
%                  'Square' or 'Custom'
%       SPACING : Radius (Circle), Interdistance (Linear), Side length
%       (Triangle and Square), or Microphone Locations (Other)
%       MIC_NOISE_LEVEL :  Microphone self noise level.  Equivalent dB SPL.
%                          Assuming each microphone has the same noise level.
%       ARRAY_GEOMETRY : Array geometry - 'CIRCLE', 'LINEAR', 'TRIANGLE',
%                        or 'OTHER'
%
%   Returns:
%       mic_array : microphone array structure
%

if nargin < 10
    PLT = false;
end
if nargin < 9
    ORDERING = 1;
end
if nargin < 8
    DIRECTIVITIES_PATH = 1;
end
if nargin < 7
    CENTER = false;
end
if nargin < 6
    mic_array.noise_var = 0;
else
    mic_array.noise_var = 10 ^ ( (MIC_NOISE_LEVEL - 94) / 10 );
end

mic_array.geometry = GEOMETRY;

if strcmp( GEOMETRY, 'Circle' )
    
    angle_step = 2*pi/NUM_MICS;
    mic_angles = ((0:NUM_MICS-1)*angle_step)';
    MIC_LOC = SPACING * [cos(mic_angles), sin(mic_angles)];
    
    if CENTER
        MIC_LOC = [MIC_LOC; [0,0]];
        NUM_MICS = NUM_MICS+1;
    end
    
    mic_array.include_center = CENTER;
    
elseif strcmp( GEOMETRY, 'Linear' )
    
    MIC_LOC = [((0:NUM_MICS-1)*SPACING)', zeros(NUM_MICS,1)];
    MIC_LOC = MIC_LOC - repmat(mean(MIC_LOC),size(MIC_LOC,1),1); % centered
    
    mic_array.include_center = false;
    
elseif strcmp( GEOMETRY, 'Triangle' )
    
    % treat as circle with three mics
    angle_step = 2*pi/3; % degrees
    radius = SPACING/2/sin(angle_step/2);
    mic_angles = ((0:2)*angle_step)';
    MIC_LOC = radius * [cos(mic_angles), sin(mic_angles)];
    NUM_MICS = 3;
    
    if CENTER
        MIC_LOC = [MIC_LOC; [0,0]];
        NUM_MICS = NUM_MICS+1;
    end
    
    mic_array.include_center = CENTER;
    
elseif strcmp( GEOMETRY, 'Square' )
    
    % centered at zero
    MIC_LOC = SPACING/2*ones(4,2);
    MIC_LOC(2:3,1) = -1*MIC_LOC(2:3,1);
    MIC_LOC(3:4,2) = -1*MIC_LOC(3:4,2);
    NUM_MICS = 4;
    
    if CENTER
        MIC_LOC = [MIC_LOC; [0,0]];
        NUM_MICS = NUM_MICS+1;
    end
    
    mic_array.include_center = CENTER;
    
elseif strcmp( GEOMETRY, 'XMOS' )
    
    SPACING = 42.38*1e-3;
    NUM_MICS = 6;
    CENTER = true;
    
    angle_step = 2*pi/NUM_MICS;
    mic_angles = ((0:NUM_MICS-1)*angle_step)';
    MIC_LOC = SPACING * [cos(mic_angles), sin(mic_angles)];
    
    if CENTER
        MIC_LOC = [MIC_LOC; [0,0]];
        NUM_MICS = NUM_MICS+1;
    end
    
    mic_array.geometry = 'Circle';
    
    mic_array.include_center = CENTER;
    
    
else
    mic_array.geometry = 'Custom';
    MIC_LOC = SPACING;
    mic_array.include_center = 0;
    NUM_MICS = size(MIC_LOC, 1);
    
end

% anti-clockwise
rotation_matrix = [cosd(-ROTATION),-1*sind(-ROTATION);...
                   sind(-ROTATION),cosd(-ROTATION)];
mic_array.pos = MIC_LOC*rotation_matrix;

if sum(ORDERING ~= 1)
    mic_array.pos = mic_array.pos(ORDERING,:);
end
mic_array.ordering = ORDERING;

if ~strcmp( GEOMETRY, 'Custom' )
    mic_array.rotation = ROTATION;
else
    mic_array.rotation = 0;
end
mic_array.spacing = SPACING;
mic_array.num_mics = size(mic_array.pos,1);
mic_array.samp_freq = FS;
mic_array.edm = zeros(mic_array.num_mics, mic_array.num_mics);
for idx = 1:(mic_array.num_mics-1)
    point_b = mic_array.pos(idx+1:end,:);
    point_a = repmat(mic_array.pos(idx,:), size(point_b,1),1);
    vtmp = point_a - point_b;
    mic_array.edm(idx,idx+1:end) = sqrt(vtmp(:,1).^2 + vtmp(:,2).^2)';
end
mic_array.edm = mic_array.edm+mic_array.edm';

if DIRECTIVITIES_PATH == 1
    % since omni response, keep it lightweight
    mic_array.directivities.angles = [0,360]; 
    mic_array.directivities.frequencies = [0,FS/2];
    mic_array.directivities.patterns = ones(NUM_MICS, length(mic_array.directivities.frequencies), length(mic_array.directivities.angles));
else
    dir = load(DIRECTIVITIES_PATH);
    mic_array.directivities = dir.dir;
    if size(mic_array.directivities.patterns,1) ~= NUM_MICS
        error('Need same number of directivity patterns as microphones!');
    end
end
mic_array.directivity_path = DIRECTIVITIES_PATH;

%% plot mic array
if PLT
    fig_handle = figure('Name', 'Microphone locations' ,'NumberTitle','off');
    ax = axes('Parent',fig_handle);
    plot(ax, mic_array.pos(:,1),mic_array.pos(:,2),'o','MarkerFaceColor', 'b');
    hold(ax, 'on')
    xlabel(ax, 'Meters')
    ylabel(ax, 'Meters')
    axis(ax, 'tight')
    axis(ax, 'square')
    for m = 1:mic_array.num_mics
        x_cor = mic_array.pos(m,1);
        y_cor = mic_array.pos(m,2);
        text(ax, x_cor, y_cor,['MIC ' num2str(m)])
    end
    hold(ax, 'off')
    grid(ax, 'on')
end

end

