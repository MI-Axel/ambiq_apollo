"""
Usage:
    data_loader.py <input_format> [options] <input_file> [<output_file>]

Arguments:
    <input_format>                          Load data format: pcm, wav, encode, raw
Options:
    -h, --help                              Show this screen
    -f <fs>, --frequency=<fs>               Audio recorder sample rate.[default: 16000]
    -b <bs>, --bits_sample=<bs>             Bits number per input sample.[default: 16]
    --channels=<cn>                         Input audio channels.[default: 2]
    --wav                                   Output data as WAV file.
    -n, --norm                              Output WAV file is normlized.
    -v <nb>, --verbose=<nb>                 Print out the first <nb> bytes of the input file.[default: 320]
    --raw_view_format=<form>                Raw data viewing format: INT16, INT32, UINT16, UINT32.[default: INT16]
    --endian=<BOL>                          Endian of raw data print out.[default: LITTLE]
    -s, --save                              Save the new format raw data or not. 
"""
from docopt import docopt
import numpy as np
import scipy
from scipy import signal
import matplotlib.pyplot as plt
import struct
import time
import subprocess
import soundfile as sf

class DataLoader(object):
    def __init__(self, data_format, bits_per_sample, sample_frequency, audio_channels=2, LRswap=False, chunk_size_byte=None, hop_size_byte=None):
        self.chunk = chunk_size_byte
        self.hop = hop_size_byte
        self.format = data_format
        if self.format == 'pcm':
            self.sample_bits = bits_per_sample
            self.sample_frequency = sample_frequency
            self.channels = audio_channels
            self.LRswap = LRswap
            if self.channels == 2:
                self.pcmLeftStream = np.array([], dtype=int)
                self.pcmRightStream = np.array([], dtype=int)
            elif self.channels == 1:
                self.pcmMonoStream = np.array([], dtype=int)
        elif self.format == 'wav':
            self.sample_frequency = sample_frequency
            self.wavStream = np.array([], dtype=float)
        elif self.format == 'raw':
            self.rawData = np.array([], dtype=int)

    def stream_input_parse(self, input_file):
        if self.format == 'pcm': 
            binStream = open(arguments['<input_file>'], 'rb').read()
            print("read input file of {} bytes...".format(len(binStream)))
            if (self.channels == 2) and (self.sample_bits == 16):
                parseData = struct.unpack('<'+'h'*(len(binStream)//2), binStream)
                parseData = np.array(parseData)
                self.pcmLeftStream = np.array([0]*(len(parseData)//2), dtype=int)
                self.pcmRightStream = np.array([0]*(len(parseData)//2), dtype=int)
                if(self.LRswap == False):
                    for i in range(len(self.pcmLeftStream)):
                        self.pcmLeftStream[i] = parseData[2*i]
                        self.pcmRightStream[i] = parseData[2*i+1]
                else:
                    for i in range(len(self.pcmLeftStream)):
                        self.pcmLeftStream[i] = parseData[2*i+1]
                        self.pcmRightStream[i] = parseData[2*i]
            elif (self.channels == 1) and (self.sample_bits == 16):
                parseData = struct.unpack('<'+'h'*(len(binStream)//2), binStream)
                self.pcmMonoStream = np.array(parseData, dtype=int)
        if self.format == 'raw':
            readBytes = np.int(arguments['--verbose'])
            binStream = open(arguments['<input_file>'], 'rb').read(readBytes)
            print("read input file of {} bytes...\n".format(len(binStream)))

            if arguments['--endian'] == 'LITTLE':
                rawOutFormat = '<'  
            elif arguments['--endian'] == 'BIG':
                rawOutFormat = '>'
            
            if arguments['--raw_view_format'] == 'INT16':
                rawOutFormat += 'h' * (len(binStream)//2)
            elif arguments['--raw_view_format'] == 'INT32':
                rawOutFormat += 'i' * (len(binStream)//4)
            elif arguments['--raw_view_format'] == 'UINT16':
                rawOutFormat += 'H' * (len(binStream)//2)
            elif arguments['--raw_view_format'] == 'UINT32':
                rawOutFormat += 'I' * (len(binStream)//4)
            rawParse = struct.unpack(rawOutFormat, binStream)
            print('First {} bytes raw data are listed as following:\n {}\n'.format(len(binStream), rawParse))




    def wav_output(self, output_file,  Norm=False):
        if self.channels == 2:
            wavStream = (self.pcmLeftStream + self.pcmRightStream) * 0.5 / (2**(self.sample_bits))
        elif self.channels == 1:
            wavStream = self.pcmMonoStream / np.float(2.**(self.sample_bits))
        
        if Norm:
            wavStream = wavStream - np.mean(wavStream)
            wavStream = wavStream / np.max(np.abs(wavStream))

        sf.write(output_file, wavStream, self.sample_frequency)	
        print("output wav file of {duration:8.3f} seconds with {freq:8.1f} HZ sample rate.\n"\
                .format(duration=len(wavStream)/self.sample_frequency, freq=self.sample_frequency))

    def mSBC_data_to_wav_float(self, msbc_bin_fn):
        exe_name = 'ia_msbc_dec_test.exe'
        now = time.strftime("-%Y-%m-%d-%H_%M", time.localtime(time.time()))
        out_fn = 'mSBC_deco_'+ now + '.wav'
        subprocess.call('{} -ifile:{} -ofile:{}'.format(exe_name, msbc_bin_fn, out_fn), shell=True)
        x, fs = sf.read(out_fn)
        x = x - np.mean(x)
        x = x/np.max(np.abs(x))
        sf.write('Norm_'+out_fn, x, fs)	

#    def data_chunk_generator(self, file_object):
#        """Lazy function (generator) to read a file piece by piece."""
#        pcm_data = file_object.read(self.chunk)
#        left_audio, right_audio = self.pcm_data_to_wav_float(pcm_data)
#        while True:
#            yield left_audio, right_audio
#            new_data = file_object.read(self.hop)
#            if not new_data:
#                break
#            left_new, right_new = self.pcm_data_to_wav_float(pcm_data)
#            left_audio = np.concatenate((left_audio[self.hop:], left_new))
#            right_audio = np.concatenate((right_audio[self.hop:], right_new))

if __name__ == '__main__':
    arguments = docopt(__doc__)
    print("the command line arguements are listed as following:\n{}".format(arguments))
    
    InFs = np.int(arguments['--frequency'])
    
    InChannels = np.int(arguments['--channels'])
    
    InBits = np.int(arguments['--bits_sample'])

    InFormat = arguments['<input_format>']

    AudioIn = DataLoader(data_format=InFormat, bits_per_sample=InBits, sample_frequency=InFs, audio_channels=InChannels)
    
    AudioIn.stream_input_parse(arguments['<input_file>'])

    if arguments['<output_file>']:
        if arguments['--wav']:
            AudioIn.wav_output(arguments['<output_file>'], Norm=arguments['--norm'])



