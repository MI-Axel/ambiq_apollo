function [ fir_coefficients, attenuation] = compute_fir_coefficients( WEIGHTS, NUM_TAPS, PLT )
%COMPUTE_FIR_COEFFICIENTS Given frequency domains coefficient, compute the
%equivalent time domain coefficients for a causal FIR filter.

if nargin < 3
    PLT = false;
end

if mod(NUM_TAPS,2) ~= 1
    error('Must be an odd number of taps.')
end

[num_mics, nbins] = size(WEIGHTS);
if mod(nbins,2) ~= 1
    error('Must be an even FFT length.')
end
nfft = (nbins-1)*2;  % assuming odd number of frequency bins

% truncate true impulse response
shift_amount = nfft/2;
trunc_region = (NUM_TAPS-1)/2;
attenuation = zeros(num_mics,1);
fir_coefficients = zeros(num_mics, NUM_TAPS);

for m = 1:num_mics
    
    % compute true impulse response 
    F = [WEIGHTS(m,:),conj(fliplr(WEIGHTS(m,2:(end-1))))];
    impulse_resp = real(ifft(F));
    
    % shift "main part" to center and truncate
    filter_m = circshift(impulse_resp,shift_amount);
    filter_m_trunc = filter_m;
    filter_m_trunc(1:(shift_amount-trunc_region-1))=0;
    filter_m_trunc((shift_amount+trunc_region+1):end)=0;
    fir_coefficients(m,:) = filter_m_trunc(shift_amount-trunc_region:shift_amount+trunc_region);
    
    % compute attenuation
    mag_resp = 20*log10(abs(fft(filter_m)));
    mag_resp_trunc = 20*log10(abs(fft(filter_m_trunc)));
    attenuation(m) = mean(abs(mag_resp - mag_resp_trunc));
    
    if PLT
        
        figure;
        subplot(3,1,1)
        plot(mag_resp)
        hold on
        plot(mag_resp_trunc)
        grid on
        title(['Magnitude response, (avg) attenuation = ' num2str(attenuation(m),3)])
        legend('Original','Truncated')
        axis tight

        subplot(3,1,2)
        plot(unwrap(angle(fft(filter_m))))
        hold on
        plot(unwrap(angle(fft(filter_m_trunc))))
        grid on
        title('Phase response')
        legend('Original','Truncated')
        axis tight

        subplot(3,1,3)
        plot(20*log10(abs(filter_m)))
        hold on
        plot(20*log10(abs(filter_m_trunc)))
        grid on
        title('Impulse response')
        legend('Original','Truncated')
        axis tight
        
    end
    
end



end

