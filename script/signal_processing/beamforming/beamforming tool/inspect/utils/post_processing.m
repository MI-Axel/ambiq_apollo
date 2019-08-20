function [ BF ] = post_processing( BF, POST )
% post_processing - Window for desired frequency response and try to ensure
% causality.

% compute window
[ wind ] = compute_post_window( BF.freqs, POST.fmin, POST.fbeg, ...
    POST.fend, POST.fmax );

% apply it
for m = 1:size(BF.weights, 1)
    BF.weights(m,:) = wind'.*BF.weights(m,:);
end

% % try to make causal (will probably still need some sort of zero padding
% % according to max delay)
% phase_max = -Inf;
% for m = 1:size(BF.weights,1)
%     phase_max = max(phase_max,max(unwrap(angle(BF.weights(m,:)))));
% end
% BF.weights = BF.weights*exp(-1i*phase_max);

end

