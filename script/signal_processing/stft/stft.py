import numpy as np
import scipy
from scipy import signal

def stft(x, hop, nfft, fs, win):
# function: [STFT, f, t] = stft(x, win, hop, nfft, fs)
#
# Input:
# x - signal in the time domain
# hop - hop size
# nfft - number of FFT points
# fs - sampling frequency, Hz
# window - analysis window function name, such as "hann", "hamming"
#
# Output:
# STFT - STFT-matrix (only unique points, time 
#        across columns, frequency across rows)
# f - frequency vector, Hz
# t - time vector, s
# representation of the signal as column-vector
    x = np.array(x, dtype=float)
# determination of the signal length 
    xlen = len(x)
# determination of the window length
    wlen = len(win)
    
    hop = np.int(hop)
# stft matrix size estimation and preallocation
    NUP = np.int(np.ceil((1+nfft)/2))     # calculate the number of unique fft points
    L = np.int(1 + np.floor((xlen-wlen)/hop)) # calculate the number of signal frames
    STFT = np.zeros((NUP, L),dtype=complex)       # preallocate the stft matrix
# STFT (via time-localized FFT)
    for l in range(L):
        # windowing
        xw = x[0+l*hop : wlen+l*hop]*win
        # FFT
        X = np.fft.fft(xw, n = nfft, axis=0)

        # update of the stft matrix
        STFT[:, l] = X[0:NUP]
# calculation of the time and frequency vectors
#    t = [wlen/2:hop:wlen/2+(L-1)*hop]/fs
    t = np.arange(wlen/2, wlen/2+L*hop, hop)/fs
    f = np.arange(NUP)*fs/nfft
    return STFT, f, t

def istft(stft, hop, nfft, fs, awin, swin):
# function: [x, t] = istft(stft, awin, swin, hop, nfft, fs)
#
# Input:
# stft - STFT-matrix (only unique points, time
#        across columns, frequency across rows)
# awin - analysis window function
# swin - synthesis window function
# hop - hop size
# nfft - number of FFT points
# fs - sampling frequency, Hz
#
# Output:
# x - signal in the time domain
# t - time vector, s
# signal length estimation and preallocation
    L = np.shape(stft)[-1]      # determine the number of signal frames
    wlen = len(swin)                 # here we only consider wlen == nfft
    hop = np.int(hop)
    xlen = wlen + (L-1)*hop     # estimate the length of the signal vector
    x = np.zeros(xlen)        # preallocate the signal vector
        
    # reconstruction of the whole spectrum
    if np.remainder(nfft, 2):             
    # odd nfft excludes Nyquist point
        X = np.concatenate((stft, np.conj(np.flipud(stft[1:, :]))))
    else:                        
        # even nfft includes Nyquist point
        X = np.concatenate((stft, np.conj(np.flipud(stft[1:(-1), :]))))
    
    #print(np.shape(np.conj(np.flipud(stft[1:, :]))))
    # columnwise IFFT on the STFT-matrix
    xw = np.fft.ifft(X, axis=0).real
    xw = xw[0:wlen, :]
    # Weighted-OLA
    for l in range(L):
        x[0+l*hop : wlen+l*hop] = x[0+l*hop : wlen+l*hop] + (xw[:, l]*swin)
        
    # scaling of the signal
    W0 = np.sum(awin*swin)
    x = x*hop/W0
    # generation of the time vector
    t = np.arange(xlen)/fs                 
    return x, t
