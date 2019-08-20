function visualize_filters( ARR, BF )
% visualizeFilters Summary of this function goes here
%   Detailed explanation goes here
%
%   Args: 
%       weights : weights for beamforming.
%              This should be a matrix of size M by F where M is the number
%              of microphones and F is the number of frequency bins 
%              (nfft/2+1).
%
%   Example:
%       >> visualizeFilters( W, fs );

figure;
if BF.freq_domain
    for m = 1:ARR.num_mics

        % plot magnitude response (half)
        Fmag = abs(BF.weights(m,:));
        subplot(ARR.num_mics,3,(m-1)*3+1)
        semilogx(BF.freqs, 20*log10(Fmag))
        if m==1
            title('Magnitude Response')
        end
        xlabel('Hz')
        ylabel('dB')
        grid on
        axis tight

        % plot phase response (half)
%         Fph = unwrap(angle(BF.weights(m,:)));
        Fph = angle(BF.weights(m,:));
        subplot(ARR.num_mics,3,(m-1)*3+2)
        semilogx(BF.freqs, Fph)
        if m==1
            title('Phase Response')
        end
        xlabel('Hz')
        grid on
        axis tight

        % compute and plot impulse response
        F = [BF.weights(m,:),conj(fliplr(BF.weights(m,2:(end-1))))];
        f = real(ifft(F));
        subplot(ARR.num_mics,3,(m-1)*3+3)
        plot((0:(length(f)-1))*ARR.samp_freq,f)
        if m==1
            title('Impulse Response')
        end
        xlabel('Seconds')
        grid on
        axis tight

    end
else
    for m = 1:ARR.num_mics

        % plot magnitude response (half)
        W = fft(BF.weights(m,:));
        nfft = length(W);
        nbin = nfft/2+1;
        frequencies = (0:(nbin-1))*ARR.samp_freq/nfft;
        Fmag = abs(W);
        subplot(ARR.num_mics,3,(m-1)*3+1)
        semilogx(frequencies, 20*log10(Fmag))
        ylim([0,1.1*max(Fmag)])
        if m==1
            title('Magnitude Response')
        end
        xlabel('Hz')
        ylabel('dB')
        grid on
        axis tight

        % plot phase response (half)
        Fph = unwrap(angle(W));
        subplot(ARR.num_mics,3,(m-1)*3+2)
        plot(frequencies, Fph(1:nbin))
        if m==1
            title('Phase Response')
        end
        xlabel('Hz')
        grid on
        axis tight

        % compute and plot impulse response
        subplot(ARR.num_mics,3,(m-1)*3+3)
        stem((0:(BF.num_taps-1))*ARR.samp_freq,BF.weights(m,:))
        if m==1
            title('Impulse Response')
        end
        xlabel('Seconds')
        grid on
        axis tight
        

    end
end


end

