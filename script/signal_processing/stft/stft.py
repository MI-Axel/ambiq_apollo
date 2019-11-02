import numpy as np
import scipy
from scipy import signal

def stft(x, fftsize=128, hop=80):
    w = signal.windows.hann(fftsize, sym=False)
#    w = scipy.hanning(fftsize)
    return np.array([np.fft.rfft(w*x[i:i+fftsize]) for i in range(0, len(x)+1-fftsize, hop)])

def istft(X, fftsize=128 ,hop=80):
    w = signal.windows.hann(fftsize, sym=False)
    x = scipy.zeros((X.shape[0]-1)*hop+fftsize)
    wsum = scipy.zeros((X.shape[0]-1)*hop+fftsize) 
    for n,i in enumerate(range(0, len(x)-fftsize+1, hop)):
        x[i:i+fftsize] += scipy.real(np.fft.irfft(X[n])) * w   # overlap-add
        wsum[i:i+fftsize] += w ** 2.
    pos = wsum != 0
    x[pos] /= wsum[pos]
    return x

