"""
Scripts to combine the short .WAV files to a long test-useing .WAV file.

Usage:
    audio_synthesis.py [--input_path=<audio_path>] [--audio_file=<file_name>] [--silent_ms=<silent_duration_ms>] [--output_path=<target_path>]

Options: 
    -h --help                                   Show this screen.
    --input_path=<audio_path>                   Input path of audio file.[default: ./../KWS certification/AVS Certification/Audio test files _ NEW/Silence_Test/Silence_Test/utts/]
    --audio_file=<file_name>                    The names of files need to be synthesised.[default: ALL] 
    --silent_ms=<silent_duration_ms>            The duration of silent between 2 RAR commands.[default: 5000]
    --output_path=<target_path>                 the path of the output file.[default: ./all_Utterances_xsDelay.wav]
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
audioOutputPath = args['--output_path']
print(silencePeriod_ms)

if args['--audio_file'] == 'ALL':
    fileList = glob.glob(audioInputPath + '*.wav')   

silenceInterval = AudioSegment.silent(duration=silencePeriod_ms, frame_rate=16000) 

comboAudio = AudioSegment.empty()

comboAudio = comboAudio + silenceInterval

for filename in fileList:
    audio = AudioSegment.from_wav(filename)
    comboAudio = comboAudio + audio
    comboAudio = comboAudio + silenceInterval

comboAudio.export(audioOutputPath, format='wav')

#    previous_segments = []
#    alexa_segments = []
#    alexa_insert_list = []
#    negatives_insert_list = []
#
#    background_data = AudioSegment.from_wav(background[0])
#
#    for alexa_sample in alexa_sample_list:
#        alexa_insert_list.append(AudioSegment.from_wav(alexa_sample))
#
#    for negatives_sample in negatives_sample_list:
#        negatives_insert_list.append(AudioSegment.from_wav(negatives_sample))
#
#    new_clip = background_data
#
#    for audio in alexa_insert_list:
#        new_clip, previous_segments = insert_audio_clip(new_clip, audio, previous_segments)
#    alexa_segments = alexa_segments + previous_segments
#    for audio in negatives_insert_list:
#        new_clip, previous_segments = insert_audio_clip(new_clip, audio, previous_segments)
#
#    return new_clip, previous_segments, alexa_segments
#
