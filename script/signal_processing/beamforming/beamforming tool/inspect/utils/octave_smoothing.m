function [ H_smooth ] = octave_smoothing( H, frequencies, half_width )
% octave_smoothing 

H_smooth = H(:);
frequencies = frequencies(:);

% mirror pad
freq_pad = [-1*flipud(frequencies(2:end)); frequencies; 2*frequencies(end)-flipud(frequencies(1:(end-1)))];
H_pad = [flipud(H(2:end)); H; flipud(H(1:(end-1)))]; 

for k = 2:length(frequencies)
    frequency = frequencies(k);
    
%     half_width = half_width * frequency;
%     lower_freq = frequency - half_width;
%     upper_freq = frequency + half_width;

    lower_freq = frequency * 2^(-half_width);
    upper_freq = frequency * 2^(half_width);
    
    [~, lower_idx] = min(abs(freq_pad-lower_freq));
    [~, upper_idx] = min(abs(freq_pad-upper_freq));
    
    % hamming for more importance to center
    num_points = upper_idx-lower_idx+1;
    if num_points > 0
        window = hamming(num_points);
%         H_smooth(k) = window'*H(lower_idx:upper_idx)/sum(window);
        H_smooth(k) = window'*H_pad(lower_idx:upper_idx)/sum(window);
    end
    
end


end

