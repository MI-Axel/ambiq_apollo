import numpy as np
import scipy
import math
from data_loader import DataLoader

class SoundDetector(object):
    def __init__(self, noise_threshold, snr_threshold, sample_frequency, chunk_size):
      self.noiseFloorThreshold = noise_threshold
      self.snrThreshold = snr_threshold
      self.sampleFrequency = sample_frequency
      self.chunkSize = chunk_size

    def get_dB(self, input_format, samplevalue):
        if input_format == 'pcm':
            samplevalue = np.max(np.abs(samplevalue), 1)
            return 20*np.log(np.float(samplevalue) /(2**15-1))/np.log(10)
        elif input_format == 'wav':
            samplevalue = np.max(np.abs(samplevalue), 0.0000001)
            return 20*np.log(samplevalue)/np.log(10)


    def QSD_process(self, input_format, chunk_data):
        if input_format == 'wav':
            absNoiseAmplitude = 1.*(10**(self.noiseFloorThreshold/20.))
            sigPwrStream = np.array([0.]*len(chunk_data), dtype=float)
            for indx, samplevalue in enumerate(chunk_data):
                if np.abs(samplevalue) > absNoiseAmplitude:
                    sigPwrStream[indx] = (np.abs(samplevalue)-absNoiseAmplitude)**2
                else:
                    sigPwrStream[indx] = 0.
            if np.mean(sigPwrStream) != 0.:
                snr_dB = 10*(np.log(np.mean(sigPwrStream)/(absNoiseAmplitude**2))/np.log(10))
            else:
                snr_dB = -100.       # make it a small negative data
#            return snr_dB
            if snr_dB > self.snrThreshold:
                return True
            else:
                return False

