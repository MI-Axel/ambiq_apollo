"""
Scripts to transform PCM data to WAV file.

Usage:
    rtt_to_wav.py (pcm|dspc) [--input=<pcm_bin_file_name>]

Options: 
    -h --help                                   Show this screen.
    --input=<pcm_bin_file_name>                 Input path of pcm data file.[default: .\record_data.bin]
"""
from docopt import docopt
import struct
import soundfile as sf
import numpy as np
import time

args = docopt(__doc__)

audioDataFilePath = args['--input'] 

binFile = open(audioDataFilePath, 'rb')

context=binFile.read()

if args['pcm']:
    audioStream = struct.unpack('<'+'h'*(len(context)//2), context)
    audioStream = np.array(audioStream)
    wavLeftStream = np.array([0]*(len(audioStream)//2), dtype=float)
    wavRightStream = np.array([0]*(len(audioStream)//2), dtype=float)
    
    for i in range(len(wavLeftStream)):
        wavLeftStream[i] = audioStream[2*i+1]
        wavRightStream[i] = audioStream[2*i]

    wavLeftStream = wavLeftStream / 32768.
    wavRightStream = wavRightStream / 32768.
    
    now = time.strftime("-%Y-%m-%d-%H_%M", time.localtime(time.time()))

    sf.write('pcm_wav_left_Stream' + now +'.wav', wavLeftStream, 16000)
    sf.write('pcm_wav_right_Stream' + now +'.wav', wavRightStream, 16000)
    
    # Normlization for human listening
    wavLeftStream = wavLeftStream/np.max([np.max(wavLeftStream),np.abs(np.min(wavLeftStream))])
    wavRightStream = wavRightStream/np.max([np.max(wavRightStream),np.abs(np.min(wavRightStream))])
    
    sf.write('pcm_wav_left_NormStream' + now +'.wav', wavLeftStream, 16000)
    sf.write('pcm_wav_right_NormStream' + now +'.wav', wavRightStream, 16000)

if args['dspc']:
    audioStream = struct.unpack('<'+'h'*(len(context)//2), context)
    wavStream = np.array(audioStream)
    wavStream = wavStream / 32768.

    now = time.strftime("-%Y-%m-%d-%H_%M", time.localtime(time.time()))

    sf.write('dspc_wavStream' + now +'.wav', wavStream, 16000)

    # Normlization for human listening
    wavStream = wavStream/np.max([np.max(wavStream),np.abs(np.min(wavStream))])

    sf.write('dspc_wavNormStream' + now +'.wav', wavStream, 16000)

