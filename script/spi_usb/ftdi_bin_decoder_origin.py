"""
Scripts to decode bin file get from apollo via ftdi or call the data receiver and decode the received data.

Usage:
    ftdi_bin_decoder.py decode <input_bin> [--integrity_check] [--output=<path>] [--format=<type>]
    ftdi_bin_decoder.py logger [--integrity_check] [--output=<path>] 

Arguments:
    input_bin                                       path of input bin file.
Options: 
    -h --help                                       Show this screen.
    -o --output=<path>                              Path to save the output decoded file. file type depends on the data type.[default: apollo_spi_log]
    -f --format=<type>                              data format of general purpose data.[default: char]
    -c --integrity_check                            whether check the integrity of received data log
"""
from docopt import docopt
import struct
import soundfile as sf
import numpy as np
import pandas as pd
import subprocess
import time

args = docopt(__doc__)
#print(args)

class Frame(object):
    def __init__(self):
        self.content = np.array([], dtype=np.int)
        # keep note of the header index in data stream
        self.header_indx = 0
        self.len = 0
        self.type = 0
        self.data_format = 'char'
        self.frameCheck = False
        self.packet_num = 0
# data type: (frameType value could be only one of following list)
# 0x0000: general purpose data no specific format. User needs to decode it himself, data_format could be selected: char(byte), int16, uint16, int32, uint32, float32_t
# 0x0001: PCM raw data from apollo pcm data register. data_format: int16_t
# 0x0002: SPP filtered data (1-ch). data_format: int16_t
# 0x0003: OPUS output data
buff_0000 = np.array([], dtype=np.uint8)
buffsize_0000 = 0
buff_0001 = np.array([], dtype=np.uint8)
buffsize_0001 = 0
buff_0002 = np.array([], dtype=np.uint8)
buffsize_0002 = 0
buff_0003 = np.array([], dtype=np.uint8)
buffsize_0003 = 0

            



if args['decode'] == True:
    input_bin_path = args['<input_bin>']
    output_file_name = args['--output']
    binFile = open(input_bin_path, 'rb')
    binContxt = binFile.read()

    dataStream = struct.unpack('<'+'B'*(len(binContxt)), binContxt)
    dataStream = np.array(dataStream, dtype=np.uint8)
#    byteTest = bytes(dataStream)
#    with open('test.bin', 'wb') as test:
#        test.write(byteTest)

# Looking for a complete frame
    i = 0
#    for i in range(len(dataStream)-6):
    while i < (len(dataStream)-6):
        if (dataStream[i] == 0x4a) and (dataStream[i+1] == 0x00):
            newOne = Frame()
            # check whether it's a real header of frame
            newOne.header_indx = i
            newOne.len = dataStream[newOne.header_indx+2] + 256 * dataStream[newOne.header_indx+3] 
            newOne.type = dataStream[newOne.header_indx+4] + 256 * dataStream[newOne.header_indx+5]
            if newOne.type in [0, 1, 2, 3]:
                # the frame is not the last one
                if ((newOne.header_indx + newOne.len+2)<len(dataStream)) and (dataStream[newOne.header_indx+newOne.len+2] == 0x4a) and (dataStream[newOne.header_indx+newOne.len+3] == 0x00):
                    newOne.frameCheck = True
                    i = i + newOne.len + 2    # point to next frame index
                # the frame is the last one
                elif((newOne.header_indx+newOne.len+2)==len(dataStream)):
                    print("The last frame is completed...")
                    newOne.frameCheck = True
                    i = i + newOne.len + 2    # point to next frame index
                else:
                    i = i + 1
                    continue
            else:
                i = i + 1
                print("unkown data type....")
                continue
        else:
            i = i + 1

        if newOne.frameCheck == True:
                newOne.frameCheck = False
                if newOne.type == 0x0000:
                    buff_0000 = np.append(buff_0000, dataStream[newOne.header_indx+6:newOne.header_indx+newOne.len+2])              
                    buffsize_0000 += newOne.len
                elif newOne.type == 0x0001:
                    buff_0001 = np.append(buff_0001, dataStream[newOne.header_indx+6:newOne.header_indx+newOne.len+2])              
                    buffsize_0001 += newOne.len
                elif newOne.type == 0x0002:
                    buff_0002 = np.append(buff_0002, dataStream[newOne.header_indx+6:newOne.header_indx+newOne.len+2])              
                    buffsize_0002 += newOne.len
                elif newOne.type == 0x0003:
                    buff_0003 = np.append(buff_0003, dataStream[newOne.header_indx+6:newOne.header_indx+newOne.len+2])              
                    buffsize_0003 += newOne.len
    
    binFile.close()

    buff_byte_0 = bytes(buff_0000)
    buff_byte_1 = bytes(buff_0001)
    buff_byte_2 = bytes(buff_0002)
    buff_byte_3 = bytes(buff_0003)

    print("Get {} bytes general data".format(buffsize_0000))
    print("Get {} bytes pcm data".format(buffsize_0001))
    print("Get {} bytes spp/merged data".format(buffsize_0002))
    print("Get {} bytes opus data".format(buffsize_0003))
    with open(output_file_name+'_general', 'wb')as output_0:
        output_0.write(buff_byte_0)
    with open(output_file_name+'_pcm', 'wb')as output_1:
        output_1.write(buff_byte_1)
    with open(output_file_name+'_spp', 'wb')as output_2:
        output_2.write(buff_byte_2)
    with open(output_file_name+'_opus', 'wb')as output_3:
        output_3.write(buff_byte_3)

if args['logger'] == True:
    try:
        subprocess.call('.\AmU2S_exe\AmU2S.exe apollo_spi.bin', shell=True)
        #subprocess.call('.\dll\AmU2S_v0.3.exe apollo_spi.bin', shell=True)
    
    except KeyboardInterrupt:
        print("\n")
        print("Processing data......")
        output_file_name = args['--output']
        binFile = open('apollo_spi.bin', 'rb')
        binContxt = binFile.read()
    
        dataStream = struct.unpack('<'+'B'*(len(binContxt)), binContxt)
        dataStream = np.array(dataStream, dtype=np.uint8)
    #    byteTest = bytes(dataStream)
    #    with open('test.bin', 'wb') as test:
    #        test.write(byteTest)
    
    # Looking for a complete frame
        if args['--integrity_check'] == True:
            generic_packet_num = np.array([], dtype=np.int)
            pcm_packet_num = np.array([], dtype=np.int)
            spp_packet_num = np.array([], dtype=np.int)
            codec_packet_num = np.array([], dtype=np.int)
            generic_data_missing_flag = False
            pcm_data_missing_flag = False
            spp_data_missing_flag = False
            codec_data_missing_flag = False
        
        i = 0
        while i < (len(dataStream)-6):
#        for i in range(len(dataStream)-6):
            if (dataStream[i] == 0x4a) and (dataStream[i+1] == 0x00):
                newOne = Frame()
                # check whether it's a real header of frame
                newOne.header_indx = i
                newOne.len = dataStream[newOne.header_indx+2] + 256 * dataStream[newOne.header_indx+3] 
                newOne.type = dataStream[newOne.header_indx+4] + 256 * dataStream[newOne.header_indx+5]
                newOne.packet_num = dataStream[newOne.header_indx+6] + 256*dataStream[newOne.header_indx+7]
                if newOne.type in [0, 1, 2, 3]:
                    # the frame is not the last one
                    if ((newOne.header_indx + newOne.len+2)<len(dataStream)) and (dataStream[newOne.header_indx+newOne.len+2] == 0x4a) and (dataStream[newOne.header_indx+newOne.len+3] == 0x00):
                        newOne.frameCheck = True
                        i = i + newOne.len + 2    # point to next frame index
                        if args['--integrity_check'] == True:
                            if newOne.type == 0:
                                generic_packet_num = np.append(generic_packet_num, newOne.packet_num)
                            elif newOne.type == 1:
                                pcm_packet_num = np.append(pcm_packet_num, newOne.packet_num)
                            elif newOne.type == 2:
                                spp_packet_num = np.append(spp_packet_num, newOne.packet_num)
                            elif newOne.type == 3:
                                codec_packet_num = np.append(codec_packet_num, newOne.packet_num)
                    # the frame is the last one
                    elif((newOne.header_indx+newOne.len+2)==len(dataStream)):
                        print("The last frame is completed...")
                        newOne.frameCheck = True
                        i = i + newOne.len + 2    # point to next frame index
                        if args['--integrity_check'] == True:
                            if newOne.type == 0:
                                generic_packet_num = np.append(generic_packet_num, newOne.packet_num)
                            elif newOne.type == 1:
                                pcm_packet_num = np.append(pcm_packet_num, newOne.packet_num)
                            elif newOne.type == 2:
                                spp_packet_num = np.append(spp_packet_num, newOne.packet_num)
                            elif newOne.type == 3:
                                codec_packet_num = np.append(codec_packet_num, newOne.packet_num)
                    else:
                        i = i + 1
                        continue
                else:
                    i = i + 1
                    continue
            else:
                i = i + 1

            if newOne.frameCheck == True:
                    newOne.frameCheck = False
                    if newOne.type == 0x0000:
                        buff_0000 = np.append(buff_0000, dataStream[newOne.header_indx+8:newOne.header_indx+newOne.len+2])              
                        buffsize_0000 += (newOne.len - 6)
                    elif newOne.type == 0x0001:
                        buff_0001 = np.append(buff_0001, dataStream[newOne.header_indx+8:newOne.header_indx+newOne.len+2])              
                        buffsize_0001 += (newOne.len - 6)
#                        if newOne.len != 326:
#                            print("---- PCM Length error: %d" %(newOne.len))
                    elif newOne.type == 0x0002:
                        buff_0002 = np.append(buff_0002, dataStream[newOne.header_indx+8:newOne.header_indx+newOne.len+2])              
                        buffsize_0002 += (newOne.len - 6)
#                        if newOne.len != 166:
#                            print("---- Preprocessed Length error: %d" %(newOne.len))						
                    elif newOne.type == 0x0003:
                        buff_0003 = np.append(buff_0003, dataStream[newOne.header_indx+8:newOne.header_indx+newOne.len+2])
                        buffsize_0003 += (newOne.len - 6)
#                        if newOne.len != 86:
#                            print("---- Encoded Length error: %d" %(newOne.len))        
        
        if args['--integrity_check'] == True:
            if len(generic_packet_num) > 1:
                for i in range(len(generic_packet_num)-1):
                    if generic_packet_num[i+1] - generic_packet_num[i] != 1:
                        generic_data_missing_flag = True
                        print("Generic Data: there might be some packet missing between these frames: {}, {}".format(generic_packet_num[i], generic_packet_num[i+1]))
            elif len(generic_packet_num) == 1:
                if generic_packet_num[0] > 0:
                    generic_data_missing_flag = True
                    print("Generic Data: we only got 1 frame data but there should be more...\n")
            if len(pcm_packet_num) > 1:
                for i in range(len(pcm_packet_num)-1):
                    if pcm_packet_num[i+1] - pcm_packet_num[i] != 1:
                        pcm_data_missing_flag = True
                        print("PCM Data: there might be some packet missing between these frames: {}, {}".format(pcm_packet_num[i], pcm_packet_num[i+1]))
            elif len(pcm_packet_num) == 1:
                if pcm_packet_num[0] > 0:
                    pcm_data_missing_flag = True
                    print("PCM Data: we only got 1 frame data but there should be more...\n")
            if len(spp_packet_num) > 1:
                for i in range(len(spp_packet_num)-1):
                    if spp_packet_num[i+1] - spp_packet_num[i] != 1:
                        spp_data_missing_flag = True
                        print("SPP Data: there might be some packet missing between these frames: {}, {}".format(spp_packet_num[i], spp_packet_num[i+1]))
            elif len(spp_packet_num) == 1:
                if spp_packet_num[0] > 0:
                    spp_data_missing_flag = True
                    print("SPP Data: we only got 1 frame data but there should be more...\n")
            if len(codec_packet_num) > 1:
                for i in range(len(codec_packet_num)-1):
                    if codec_packet_num[i+1] - codec_packet_num[i] != 1:
                        codec_data_missing_flag = True
                        print("Codec Data: there might be some packet missing between these frames: {}, {}".format(codec_packet_num[i], codec_packet_num[i+1]))
            elif len(codec_packet_num) == 1:
                if codec_packet_num[0] > 0:
                    codec_data_missing_flag = True
                    print("Codec Data: we only got 1 frame data but there should be more...\n")
        binFile.close()

        if args['--integrity_check'] == True:
            if generic_data_missing_flag:
                print("there is data missing in generic data log")
            if pcm_data_missing_flag:
                print("there is data missing in pcm data log")
            if spp_data_missing_flag:
                print("there is data missing in spp data log")
            if codec_data_missing_flag:
                print("there is data missing in codec data log")

        buff_byte_0 = bytes(buff_0000)
        buff_byte_1 = bytes(buff_0001)
        buff_byte_2 = bytes(buff_0002)
        buff_byte_3 = bytes(buff_0003)
    
        print("Get {} bytes general data".format(buffsize_0000))
        print("  Saved to file %s" %(output_file_name+'_general'))
        print("Get {} bytes pcm data".format(buffsize_0001))
        print("  Saved to file %s" %(output_file_name+'_pcm'))
        print("Get {} bytes spp/merged data".format(buffsize_0002))
        print("  Saved to file %s" %(output_file_name+'_spp'))
        print("Get {} bytes opus data".format(buffsize_0003))
        print("  Saved to file %s" %(output_file_name+'_opus'))
        with open(output_file_name+'_general', 'wb')as output_0:
            output_0.write(buff_byte_0)
        with open(output_file_name+'_pcm', 'wb')as output_1:
            output_1.write(buff_byte_1)
        with open(output_file_name+'_spp', 'wb')as output_2:
            output_2.write(buff_byte_2)
        with open(output_file_name+'_opus', 'wb')as output_3:
            output_3.write(buff_byte_3)
  
