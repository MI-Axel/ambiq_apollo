function [ steer ] = compute_steering_vectors( angles, frequencies, mic_pos, speed_sound, array_directivities )
% compute_steering_vectors Compute steering vectors under the far-field
% assumption.

frequencies = frequencies(:);
angles = angles(:);

NUM_FREQS = length(frequencies);
NUM_ANGLES = length(angles);
NUM_MICS = length(mic_pos);

if nargin == 5
    freq_points = repmat(array_directivities.frequencies',1,length(array_directivities.angles));
    angle_points = repmat(array_directivities.angles,length(array_directivities.frequencies),1);
end

% planar wavefronts
far_delays = -(kron(cosd(angles),mic_pos(:,1)') + kron(sind(angles),mic_pos(:,2)'))/speed_sound;

if NUM_FREQS == 1
    
    if nargin == 5
        % interpolate to find directivities for given angle across all frequencies
        DIR = zeros(NUM_ANGLES, NUM_MICS);
        for m = 1:NUM_MICS
            V = squeeze(array_directivities.patterns(m,:,:));
            DIR(:,m) =  interp2(angle_points, freq_points, V, angles, frequencies*ones(NUM_ANGLES,1));
        end
    end
    
    steer = exp(-1i*2*pi*frequencies*far_delays);
    
elseif NUM_ANGLES == 1
    
    if nargin == 5
        % interpolate to find directivities for given angle across all frequencies
        DIR = zeros(NUM_FREQS, NUM_MICS);
        for m = 1:NUM_MICS
            V = squeeze(array_directivities.patterns(m,:,:));
            DIR(:,m) =  interp2(angle_points, freq_points, V, angles*ones(NUM_FREQS,1), frequencies);
        end
    end
    
    steer = exp(-1i*2*pi*kron(frequencies,far_delays));
    
else
    
    if nargin == 5
        % interpolate to find directivities for given angles and
        % frequencies
        DIR = zeros(NUM_FREQS, NUM_ANGLES, NUM_MICS);
        eval_freq_points = repmat(frequencies,1,NUM_ANGLES);
        eval_angle_points = repmat(angles',NUM_FREQS,1);
        for m = 1:NUM_MICS
            V = squeeze(array_directivities.patterns(m,:,:));
            DIR(:,:,m) =  interp2(angle_points, freq_points, V, eval_angle_points, eval_freq_points);
        end
    end
    
    steer = zeros(NUM_FREQS, NUM_ANGLES, NUM_MICS);
    for k = 1:NUM_FREQS
        steer(k,:,:) = exp(-1i*2*pi*frequencies(k)*far_delays);
    end
    
end

if nargin == 5
    
    if size(DIR) ~= size(steer)
        warning('Invalid shape for array directivities. Assuming omnidirectional microphones.');
    else
        steer = DIR .* steer;
    end
end

end

