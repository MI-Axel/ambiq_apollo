"""
Scripts to decode OPUS data to WAV file with opus_demo.

Usage:
    opus_bitstream_decode.py <input> <output>

Options: 
    -h --help                                   Show this screen.
"""
from docopt import docopt
import struct
import numpy as np
import time
import soundfile as sf


args = docopt(__doc__)

opusFileName = args['<input>'] 

outputFileName = args['<output>']

#opusBits = open(opusFileName, 'rb')

#bitFrame = opusBits.read(320)

#charStream = struct.unpack('<'+'I'*(len(bitFrame)//4), bitFrame)

#intStream = struct.unpack('>'+'I'*(len(bitFrame)//4), bitFrame)

#print("the lenth of bitFrame:", len(bitFrame), "\n")

#print(charStream)

#print(intStream)

#opusBits.close()

binFile = open(opusFileName, 'rb')

binStream = binFile.read()

wavStream = struct.unpack('>'+'d'*(len(binStream)//8), binStream)

sf.write(outputFileName+'.wav', wavStream, 48000)
