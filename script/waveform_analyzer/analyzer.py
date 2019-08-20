
import numpy as np
import matplotlib.pyplot as plt
from scipy import signal
import matplotlib.pyplot as plt

def freqEstimator(sig, fs):
    """
    Estimate frequency from peak of FFT
    """
    # Remove DC
    sig -= np.average(sig)
    
    # Compute Fourier transform of windowed signal
    windowed = sig * signal.blackmanharris(len(sig))
    f = np.fft.rfft(windowed)

    # Find the peak and interpolate to get a more accurate peak
    i = np.argmax(np.abs(f))  # Just use this for less-accurate, naive version
    true_i = i
    #true_i = parabolic(np.log(np.abs(f)), i)[0]

    # Convert to equivalent frequency
    return fs * true_i / len(windowed)


def THDN(sig, fs=16000, f0=None):
    """
    Measure THD+N  for signal
    AES-17 Spec defines THD+N as the ratio of RMS levels between signal and notched signal. 
    The notch filter is specified to have a Q of 2 - 5. 
    
    Here we use two stages each with a Q = 2.5
    """
    Q = 2.5     #Quality Factor

    if f0 == None:
        f0 = freqEstimator(sig, fs)
        #print('Fundamental frequency not specified, estimated frequency = %.2f Hz' % (f0))
    
    # Design notch filter
    b, a = signal.iirnotch(f0, Q, fs)

    # Filter twice
    fdata = sig
    fdata = signal.lfilter(b, a, fdata)
    fdata = signal.lfilter(b, a, fdata)
    
    return 20*np.log10(np.std(fdata[100:])/np.std(sig[100:]))

def plotFFT(sig, fs, log=False):
    """
    Plot FFT
    """
    # Remove DC
    sig -= np.average(sig)
    
    NFFT=len(sig)
    
    # Compute Fourier transform of windowed signal
    windowed = sig * signal.blackmanharris(NFFT)
    f = np.fft.rfft(windowed)
    if log:
        plt.semilogx(20*np.log10(np.abs(f)/NFFT))
    else:
        plt.plot(20*np.log10(np.abs(f)/NFFT))
