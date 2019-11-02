"""
Usage:
    audio_format.py one_shot <input_file> [options] <output_file>
    audio_format.py recursive <input_folder> [options] <output_folder>

Arguments:
    <output_file>                           Output audio file name and type
    <input_folder>                          Folder contains input .wav files
    <output_folder>                         Folder contains output .wav files
Options:
    -h, --help                              Show this screen
    --format=<fm>                           Input data format, including raw, pcm, wav.[default: wav] 
    -f <fs>, --frequency=<fs>               Input audio sample rate.[default: 16000]
    -b <bs>, --bits_sample=<bs>             Input bits number per input sample.[default: 16]
    --channels=<cn>                         Input audio channels.[default: 2]
    --out_samplerate=<osr>                  Formatted audio stream sample rate.[default: 16000]
    -d <dr>, --duration=<dr>                Formatted audio stream length in seconds.[default: 1]
    -n, --norm                              Output WAV file is normlized.
"""
from docopt import docopt
import numpy as np
from data_loader import DataLoader
from qsd import SoundDetector
import soundfile as sf
import glob
import os.path
import hashlib

args = docopt(__doc__)

print(args)

if args['one_shot']:

    inputFormat = args['--format']
    
    inFrequency = np.int(args['--frequency'])
    
    inBitsPerSample = np.int(args['--bits_sample'])
    
    inChannels = np.int(args['--channels'])
    
    audioIn = DataLoader(data_format=inputFormat, bits_per_sample=inBitsPerSample, \
                            sample_frequency=inFrequency, audio_channels=inChannels)
    
    audioIn.stream_input_parse(args['<input_file>'])
    
    inFrame_ms = 20
    
    inChunkSize =np.int(inFrame_ms * audioIn.sample_frequency / 1000)
    
    outLength_s = np.float(args['--duration'])
    
    outSampleRate = np.int(args['--out_samplerate'])
    
    qSD = SoundDetector(noise_threshold=-50, snr_threshold=6, \
                        sample_frequency=audioIn.sample_frequency, chunk_size= inChunkSize)
    
    g_qSDRet = False
    
    g_noisyIndx = []
    
    for indx in range(len(audioIn.wavStream)//qSD.chunkSize):
        dataFrame = audioIn.wavStream[indx*qSD.chunkSize:(indx+1)*qSD.chunkSize]
        g_qSDRet = qSD.QSD_process(audioIn.format, dataFrame)
        if g_qSDRet:
            g_noisyIndx.append(indx)
    
    for frameIndx in g_noisyIndx:
        if ((frameIndx+1) in g_noisyIndx) and ((frameIndx+2) in g_noisyIndx) \
                and ((frameIndx+3) in g_noisyIndx):
            audioStartIndx = frameIndx
            break
    
    outStartIndex = np.int(audioStartIndx * inFrame_ms * audioIn.sample_frequency / 1000)
    
    outDataLength = np.int(outSampleRate * outLength_s)
    
    captureAudio = audioIn.wavStream[(outStartIndex):(outDataLength+outStartIndex)]
    
    outFileName = args['--output_file']

    sf.write(outFileName, captureAudio, outSampleRate)

elif args['recursive']: 

    inputFormat = args['--format']
    
    inFrequency = np.int(args['--frequency'])
    
    inChannels = np.int(args['--channels'])
    
    inBitsPerSample = np.int(args['--bits_sample'])

# if data format is wav, the other 3 parameters are invalid.
    audioIn = DataLoader(data_format=inputFormat, bits_per_sample=inBitsPerSample, \
                            sample_frequency=inFrequency, audio_channels=inChannels)
    
    inFrame_ms = 20
    
    
    outLength_s = np.float(args['--duration'])
    
    outSampleRate = np.int(args['--out_samplerate'])

    inputPath = args['<input_folder>']

    outputPath = args['<output_folder>']

    targetFileList = glob.glob(inputPath + '*.wav')

    for input_file in targetFileList:
        
        audioIn.stream_input_parse(input_file)
        
        inChunkSize =np.int(inFrame_ms * audioIn.sample_frequency / 1000)
        
        baseNameList = list(os.path.basename(input_file))

        insertPos = baseNameList.index('_')

        baseNameList.insert(insertPos, '_nohash') 

        newFileName = outputPath + "".join(baseNameList)

        qSD = SoundDetector(noise_threshold=-50, snr_threshold=6, \
                            sample_frequency=audioIn.sample_frequency, chunk_size= inChunkSize)
    
        g_qSDRet = False
    
        g_noisyIndx = []
    
        for indx in range(len(audioIn.wavStream)//qSD.chunkSize):
            dataFrame = audioIn.wavStream[indx*qSD.chunkSize:(indx+1)*qSD.chunkSize]
            g_qSDRet = qSD.QSD_process(audioIn.format, dataFrame)
            if g_qSDRet:
                g_noisyIndx.append(indx)
    
        for frameIndx in g_noisyIndx:
            if ((frameIndx+1) in g_noisyIndx) and ((frameIndx+2) in g_noisyIndx) \
                    and ((frameIndx+3) in g_noisyIndx):
                audioStartIndx = frameIndx
                break
        outStartIndex = np.int(audioStartIndx * inFrame_ms * audioIn.sample_frequency / 1000)
    
        outDataLength = np.int(outSampleRate * outLength_s)
        
        if outDataLength <= (len(audioIn.wavStream)-outStartIndex):
            captureAudio = audioIn.wavStream[(outStartIndex):(outDataLength+outStartIndex)]
        else:
            captureAudio = audioIn.wavStream[(outStartIndex):len(audioIn.wavStream)]
            paddingZero = np.array([0]*(outDataLength+outStartIndex-len(audioIn.wavStream)), dtype=float)
            captureAudio = np.append(captureAudio, paddingZero)
        
        sf.write(newFileName, captureAudio, outSampleRate)

