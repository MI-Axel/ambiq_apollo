import numpy as np
import scipy
from scipy import signal
import matplotlib.pyplot as plt
import librosa
from stft.stft import * 

class SignalProcessor(object):
    def __init__(self, sample_rate, hop_size, window_len, fft_len, anal_window, synth_window):
        self.fs = sample_rate
        self.hop = hop_size
        self.wlen = window_len
        self.nfft = fft_len
        if anal_window == "hann":
            self.awin = signal.windows.hann(self.wlen, sym=False)
        elif anal_window == "hamming":
            self.awin = signal.windows.hamming(self.wlen, sym=False)
        elif anal_window == "rect":
            self.awin = signal.windows.boxcar(self.wlen, sym=False)
        else:
            self.awin = signal.windows.hann(self.wlen, sym=False)
        
        if synth_window == "hann":
            self.swin = signal.windows.hann(self.wlen, sym=False)
        elif synth_window == "hamming":
            self.swin = signal.windows.hamming(self.wlen, sym=False)
        elif synth_window == "rect":
            self.swin = signal.windows.boxcar(self.wlen, sym=False)
        else:
            self.swin = signal.windows.hann(self.wlen, sym=False)


    def stft(self, x):
        STFT, f, t = stft(x, self.hop, self.nfft, self.fs, self.awin)
        return STFT, f, t

    def istft(self, stft):
        x, t = istft(stft, self.hop, self.nfft, self.fs, self.awin, self.swin)
        return x, t
