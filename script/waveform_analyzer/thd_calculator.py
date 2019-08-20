import numpy as np
from numpy import array_equal, polyfit, sqrt, mean, absolute, log10, arange
import sys
from scipy import signal
import matplotlib.pyplot as plt
from wave_analysis_common import rms_flat, dB

def freqEstimator(sig, fs):
    """
    Estimate frequency from peak of FFT

    Return estimated fundemental frequency and windowed signal
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
    #print("fundmental frequency index is %d" % true_i)
    # Convert to equivalent frequency
    return fs * true_i / len(windowed), windowed, f

def THDN(sig, fs=16000, Q=2.5, f0=None):
    """
    Measure THD+N  for signal
    AES-17 Spec defines THD+N as the ratio of RMS levels between signal and notched signal. 
    The notch filter is specified to have a Q of 2 - 5. 
    Here we use two stages each with a Q = 2.5
    Return thd+n of float and dB format
    """

    if f0 == None:
        f0, signal_windowed, freq_bins = freqEstimator(sig, fs)
        print('Fundamental frequency not specified, estimated frequency = %.2f Hz' % (f0))
    else:
        # Get rid of DC and window the signal
        sig = np.asarray(sig) + 0.0  # Float-like array
        sig -= np.average(sig)
        signal_windowed = sig * signal.blackmanharris(len(sig))
    
    # Measure the total signal before filtering but after windowing
    total_rms = rms_flat(signal_windowed)
    
    # Design notch filter
    b, a = signal.iirnotch(f0, Q, fs)

    # Filter twice
    noise = signal.lfilter(b, a, sig)
    noise = signal.lfilter(b, a, noise)
    noise_windowed = noise * signal.blackmanharris(len(noise))
    noise_rms = rms_flat(noise_windowed)
    ret = noise_rms / total_rms
    ret_dB = dB(ret)
    print("THD+N: %.4f%% or %.1f dB" % (ret * 100, ret_dB))
    return ret, ret_dB

def THD(sig, fs=16000, f0=None):
    """
    Measure THD for signal
    THD only picks up the harmonic freq slot while THDN picks all except fundemental slot
    Returns measured THD
    """
    if f0 == None:
        f0, signal_windowed, freq_bins = freqEstimator(sig, fs)
        print('Fundamental frequency not specified, estimated frequency = %.2f Hz' % (f0))
    else:
        # Get rid of DC and window the signal
        sig = np.asarray(sig) + 0.0  # Float-like array
        sig -= np.average(sig)
        signal_windowed = sig * signal.blackmanharris(len(sig))
        freq_bins = np.fft.rfft(signal_windowed)
    
    i = np.argmax(np.abs(freq_bins))  # Just use this for less-accurate, naive version
    
    harmonic_num = min(np.int((fs/2)/f0), 25)
    print("THD will calculate %d harmonic slots" % harmonic_num)
    for x in range(1, harmonic_num):
        print('%.3f' % abs(freq_bins[i * x]), end=' ')
    ret = sum([abs(freq_bins[i*x]) for x in range(2, harmonic_num)]) / abs(freq_bins[i])
    ret_dB = dB(ret) 
    print('\nTHD: %f%%' % (ret * 100))
    return ret, ret_dB
