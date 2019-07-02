"""
Scripts to combine the short .WAV files to a long test-useing .WAV file.
update: could add response in the long .WAV file in order to answering the potential questions from APP

Usage:
    audio_synthesis.py [options]

Options: 
    -h --help                                                       Show this screen.
    -r, --with_response                                             add no-response at the 2/3 of silent interval
    -i <audio_path>, --input_path=<audio_path>                      Input path of audio file.[default: /Users/axel/KWS/audio/Audio_test_files_NEW/Silence_Test/Silence_Test/utts/]
    -o <output_file>, --out_file=<output_file>                      Output file of the synthesis audio.[default: ./All_Utterances_xs_Delay.wav]
    --silent_ms=<silent_duration_ms>                                The duration of silent between 2 RAR commands.[default: 15000]
"""

from docopt import docopt
import numpy as np
from pydub import AudioSegment
import random
import sys
import io
import os
import glob

args = docopt(__doc__)

audioInputPath = args['--input_path']
silencePeriod_ms = np.float(args['--silent_ms'])
outFile = args['--out_file']
print(args)

fileList = glob.glob(audioInputPath + '*.wav')   


silenceStartInterval = AudioSegment.silent(duration=10000, frame_rate=16000) 

comboAudio = AudioSegment.empty()

comboAudio = comboAudio + silenceStartInterval

if args['--with_response']:
    no_res_audio = AudioSegment.from_wav("no_response.wav")
    silenceInterval_1 = AudioSegment.silent(duration=(silencePeriod_ms*2/3), frame_rate=16000) 
    silenceInterval_2 = AudioSegment.silent(duration=(silencePeriod_ms*1/3), frame_rate=16000) 
    for filename in fileList:
        audio = AudioSegment.from_wav(filename)
        comboAudio = comboAudio + audio
        comboAudio = comboAudio + silenceInterval_1
        comboAudio = comboAudio + no_res_audio
        comboAudio = comboAudio + silenceInterval_2
else:
    silenceInterval = AudioSegment.silent(duration=silencePeriod_ms, frame_rate=16000) 
    for filename in fileList:
        audio = AudioSegment.from_wav(filename)
        comboAudio = comboAudio + audio
        comboAudio = comboAudio + silenceInterval

comboAudio.export(outFile, format='wav')


