function [ MOV ] = create_beam_movie( PATTERNS, BF, ANGLES, FREQS )
% create_beam_movie

ANGLES = ANGLES(:);
num_freq = length(FREQS);

figure;
for k = 1:num_freq
    
    freq = FREQS(k);
    
    plot(PATTERNS(:,k).*cos(pi*ANGLES/180), ...
        PATTERNS(:,k).*sin(pi*ANGLES/180), 'b-', 'LineWidth', 1);
    hold on
    plot(cos(pi*ANGLES/180), ...
        sin(pi*ANGLES/180), 'k--', 'LineWidth', 0.5);
    text(1.05,0,'1');
    
    plot([0, cosd(BF.angle_tar)], ...
        [0, sind(BF.angle_tar)], 'g--' ,'LineWidth', 1.5);
    
    label = [num2str(freq) ' Hz'];
    title(label);
    
    axis equal;
    axis off;
    grid on;
    hold off
    
    MOV(k) = getframe(gcf);
    
end

v = VideoWriter(['beam_patterns_look_' num2str(BF.angle_tar) '_' BF.method '.avi']);
v.FrameRate = 10;
open(v)
writeVideo(v,MOV)
close(v)


end

