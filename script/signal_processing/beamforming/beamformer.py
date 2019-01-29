import numpy as np
import scipy
from scipy import signal
import pandas as pd
import matplotlib.pyplot as plt
import librosa

# For now, we only support end-fire beamforming calculation
class mic(object):
    def __init__(self, directivity, FS):
        if directivity == 'omni':                   # Omni mic config
            self.angles = [0, 360]
        self.frequence_sample = FS


class mic_array(object):
    def __init__(self, mic, geometry, num_mics, spacing, *, rotation=False, FS=16000, mic_noise_level=30, center=False):
        self.geometry = geometry
        self.mic_num = num_mics
        self.rotation = rotation
        self.center = center
        self.mic = mic
        self.noise_var = 10**((mic_noise_level-94)/10)
        if self.geometry == 'linear':
            self.mic_loc = np.array([[0,0]]*self.mic_num, dtype=float)
            for indx in range(self.mic_num):
                self.mic_loc[indx][0] += spacing*indx
            if self.center == True:
                center_value = np.mean(self.mic_loc, axis=0)[0]
                for indx in range(self.mic_num):
                    self.mic_loc[indx][0] -= center_value
    
    def array_plot(self, figure_size=(12,9)):
        fig = plt.figure(figsize=figure_size)
        for mic in self.mic_loc:
            plt.scatter(mic[0], mic[1], s=400, c='b', marker='o')
        plt.grid(True)
        plt.xlabel('centimeters')
        plt.ylabel('centimeters')
        plt.show()        


class beamformer(object):
    def load(self, load_path=None):
        context = pd.read_csv(load_path, header=None)
        self.channels = len(context.columns)
        dic_converter = {}
        for i in range(self.channels):
            dic_converter[i] = self._complex_parse
        params = pd.read_csv(load_path, header=None, converters=dic_converter)
        self.nfft = (np.shape(params)[0]-1)*2
        self.params = np.zeros(shape=(self.channels, self.nfft//2+1), dtype=complex)
        for indx in range(self.channels):
            self.params[indx] = np.array(params.loc[:, indx])     
    
    def _complex_parse(self, str_num):
        complex_num = complex(str_num.replace(" ", "").replace('i', 'j'))
        return complex_num
  
