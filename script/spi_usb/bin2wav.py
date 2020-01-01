import struct
import soundfile as sf
import numpy as np
import os
import time

# bin2wav: translate bin file to wav file
# args:
# input_bin: input audio data of bin format: pcm or spp
# LRswap: used for pcm, whether left ch and right ch swapped
def bin2wav(input_bin, data_type, LRswap=False):
    output_files = []
    bin_file = open(input_bin, 'rb')
    context=bin_file.read()

    if data_type == 'pcm':
        audioStream = struct.unpack('<'+'h'*(len(context)//2), context)
        audioStream = np.array(audioStream)
        wavLeftStream = np.array([0]*(len(audioStream)//2), dtype=float)
        wavRightStream = np.array([0]*(len(audioStream)//2), dtype=float)
        
        for i in range(len(wavLeftStream)):
            if LRswap == True:
                wavLeftStream[i] = audioStream[2*i+1]
                wavRightStream[i] = audioStream[2*i]
            else:
                wavRightStream[i] = audioStream[2*i+1]
                wavLeftStream[i] = audioStream[2*i]
    
        wavLeftStream = wavLeftStream / 32768.
        wavRightStream = wavRightStream / 32768.
        
        now = time.strftime("-%Y-%m-%d-%H_%M", time.localtime(time.time()))
        
        cur_path = os.getcwd() + '/'
        
        file_name = 'pcm_wav_left_Stream' + now + '.wav'
        sf.write(file_name, wavLeftStream, 16000)
        output_files.append(cur_path+file_name)

        file_name = 'pcm_wav_right_Stream' + now + '.wav'
        sf.write(file_name, wavRightStream, 16000)
        output_files.append(cur_path+file_name)
        
        # Normlization for human listening
        wavLeftStream = wavLeftStream/np.max([np.max(wavLeftStream),np.abs(np.min(wavLeftStream))])
        wavRightStream = wavRightStream/np.max([np.max(wavRightStream),np.abs(np.min(wavRightStream))])
        
        file_name = 'pcm_wav_left_NormStream' + now + '.wav'
        sf.write(file_name, wavLeftStream, 16000)
        output_files.append(cur_path+file_name)
        
        file_name = 'pcm_wav_right_NormStream' + now + '.wav'
        sf.write('pcm_wav_right_NormStream' + now +'.wav', wavRightStream, 16000)
        output_files.append(cur_path+file_name)

    elif data_type == 'spp':
        audioStream = struct.unpack('<'+'h'*(len(context)//2), context)
        wavStream = np.array(audioStream)
        wavStream = wavStream / 32768.
        
        now = time.strftime("-%Y-%m-%d-%H_%M", time.localtime(time.time()))
        cur_path = os.getcwd() + '/'

        file_name = 'spp_wavStream' + now + '.wav'
        sf.write(file_name, wavStream, 16000)
        output_files.append(cur_path+file_name)
        
        # Normlization for human listening
        wavStream = wavStream/np.max([np.max(wavStream),np.abs(np.min(wavStream))])
        file_name = 'spp_wavNormStream' + now + '.wav'
        sf.write(file_name, wavStream, 16000)
        output_files.append(cur_path+file_name)
    
    return output_files
