"""
Scripts to decode bin file get from apollo via ftdi or call the data receiver and decode the received data.

Usage:
    ftdi_bin_decoder.py decoder <input_bin> [--integrity_check] [--output=<path>] [--format=<type>]
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
import os

args = docopt(__doc__)
#print(args)

# TLV encoded data
# support 4 types of data:(out_bin_name: string data)
# type 0: [output_name]_general
# type 1: [output_name]_pcm
# type 2: [output_name]_spp
# type 3: [output_name]_opus
# frame header: the fixed start pattern of a new frame
# input_bin_path: the path of bin file which needs decoded
# out_bin_name: the name of output files group (split with different data types)
# integrity_check: check the collected data completed or not

class U2SDecoder(object):
    def __init__(self, frame_header, input_bin_path, out_bin_name, integrity_check):
        # keep note of the header index in data stream
        self.header_indx = 0
        # the data pattern of frame header (np.array)
        self.header_pattern = frame_header
        # the length of header info
        # 0x4a, 0x00, len1, len2, typ1, typ2, packet1, packet2
        self.header_packet_len = 8
        # size of bytes
        self.len = 0
        # data type of frame
        self.type = 0
        # integrity check of packet number
        self.packet_num = 0
        # buffer to save the true frame data
        self.frame_buff = bytes()
        # flag to indicate the end of file
        self.file_end = False
        # input bin file handler
        self.usb_bin_handler = open(input_bin_path, 'rb')
        #used to calculate the progress
        self.total_data_bytes = os.path.getsize(input_bin_path)
        # output bin names with different types
        self.output_group_path = out_bin_name
        self.output_tp0 = open(out_bin_name + "_general", 'wb')
        self.output_tp1 = open(out_bin_name + "_pcm", 'wb')
        self.output_tp2 = open(out_bin_name + "_spp", 'wb') 
        self.output_tp3 = open(out_bin_name + "_opus", 'wb') 
        # integrity check
        self.integrity_check = integrity_check
        self.generic_packet_num = np.array([], dtype=np.int)
        self.pcm_packet_num = np.array([], dtype=np.int)
        self.spp_packet_num = np.array([], dtype=np.int)
        self.codec_packet_num = np.array([], dtype=np.int)
        self.generic_data_missing_flag = False
        self.pcm_data_missing_flag = False
        self.spp_data_missing_flag = False
        self.codec_data_missing_flag = False

        # data counts
        self.data_count_tp0 = 0
        self.data_count_tp1 = 0
        self.data_count_tp2 = 0
        self.data_count_tp3 = 0

    # run frame_check after we got 0x4a, 0x00.
    def frame_check(self):
    # read header info from current pos        
        header_packet = self.usb_bin_handler.read(self.header_packet_len-2)
        header_info = struct.unpack('<'+'B'*(len(header_packet)), header_packet)
        self.len = header_info[0] + 256 * header_info[1]
        self.type = header_info[2] + 256 * header_info[3]
        self.packet_num = header_info[4] + 256 * header_info[5]
# check whether the frame length info reasonable or not
        if self.len < (self.header_packet_len - 2):
            self.usb_bin_handler.seek(-(self.header_packet_len-2), 1)
            print("the calculated length of frame is too short: {:d}".format(self.len))
            return False
        if self.type not in [0, 1, 2, 3]:
            self.usb_bin_handler.seek(-(self.header_packet_len-2), 1)
            print("unknown data type...")
            return False
    # check whether the next frame starts with 0x4a, 0x00: read length - 6 + 2 
        data_stream = self.usb_bin_handler.read(self.len - 4)
    # succeed reading the whole wanted data
        if len(data_stream) == (self.len - 4):
            next_header = struct.unpack('<'+'B'*(len(data_stream[-2:])), data_stream[-2:])
            if next_header[0] == self.header_pattern[0] and next_header[1] == self.header_pattern[1]:
                # save the valid buffer data into frame buffer
                self.frame_buff += data_stream[:-2]
                # move file read pointer back
                self.usb_bin_handler.seek(-2, 1)
                #check the data integrity
                if self.integrity_check == True:
                    if self.type == 0:
                        self.generic_packet_num = np.append(self.generic_packet_num, self.packet_num)
                    elif self.type == 1:
                        self.pcm_packet_num = np.append(self.pcm_packet_num, self.packet_num)
                    elif self.type == 2:
                        self.spp_packet_num = np.append(self.spp_packet_num, self.packet_num)
                    elif self.type == 3:
                        self.codec_packet_num = np.append(self.codec_packet_num, self.packet_num)
                return True
            else:
                self.usb_bin_handler.seek(-(self.len+2), 1)
                return False
        # we would abandon the last frame no matter it's completed or not
        else:
            self.file_end = True
            return False
    # loading 1 frame data to target file
    def frame_load(self):
        if self.type == 0:
            self.data_count_tp0 += self.output_tp0.write(self.frame_buff)
        elif self.type == 1:
            self.data_count_tp1 += self.output_tp1.write(self.frame_buff)
        elif self.type == 2:
            self.data_count_tp2 += self.output_tp2.write(self.frame_buff)
        elif self.type == 3:
            self.data_count_tp3 += self.output_tp3.write(self.frame_buff)
        # clear the buffer
        self.frame_buff = bytes()
    
    # return current file read/write pos
    def progress_update(self):
        cur_pos = self.usb_bin_handler.tell()
        percent = cur_pos / self.total_data_bytes
        return cur_pos, percent

    # pump out a frame data 
    def data_pump_out(self):
# read 2 bytes a time to look for header pattern
        data_input = self.usb_bin_handler.read(len(self.header_pattern))
        header = struct.unpack('<'+'B'*(len(data_input)), data_input)
        if header[0] == self.header_pattern[0] and header[1] == self.header_pattern[1]:
            if self.frame_check():
                self.frame_load()
    
    def packet_integrity_check(self):
        if len(self.generic_packet_num) > 1:
            for i in range(len(self.generic_packet_num)-1):
                if self.generic_packet_num[i+1] - self.generic_packet_num[i] != 1 and self.generic_packet_num[i+1] - self.generic_packet_num[i] != -65535:
                    self.generic_data_missing_flag = True
                    print("Generic Data: there might be some packet missing between these frames: {}, {}".format(self.generic_packet_num[i], self.generic_packet_num[i+1]))
        if len(self.pcm_packet_num) > 1:
            for i in range(len(self.pcm_packet_num)-1):
                if self.pcm_packet_num[i+1] - self.pcm_packet_num[i] != 1 and self.pcm_packet_num[i+1] - self.pcm_packet_num[i] != -65535:
                    self.pcm_data_missing_flag = True
                    print("PCM Data: there might be some packet missing between these frames: {}, {}".format(self.pcm_packet_num[i], self.pcm_packet_num[i+1]))
        if len(self.spp_packet_num) > 1:
            for i in range(len(self.spp_packet_num)-1):
                if self.spp_packet_num[i+1] - self.spp_packet_num[i] != 1 and self.spp_packet_num[i+1] - self.spp_packet_num[i] != -65535:
                    self.spp_data_missing_flag = True
                    print("SPP Data: there might be some packet missing between these frames: {}, {}".format(self.spp_packet_num[i], self.spp_packet_num[i+1]))
        if len(self.codec_packet_num) > 1:
            for i in range(len(self.codec_packet_num)-1):
                if self.codec_packet_num[i+1] - self.codec_packet_num[i] != 1 and self.codec_packet_num[i+1] - self.codec_packet_num[i] != -65535:
                    self.codec_data_missing_flag = True
                    print("Codec Data: there might be some packet missing between these frames: {}, {}".format(self.codec_packet_num[i], self.codec_packet_num[i+1]))
        print("\n\r")


    def __del__(self):
        self.usb_bin_handler.close()
        self.output_tp0.close()
        self.output_tp1.close()
        self.output_tp2.close()
        self.output_tp3.close()
        # clean up the 0-size file
        if self.data_count_tp0 == 0:
            os.remove(self.output_group_path + '_general')
        if self.data_count_tp1 == 0:
            os.remove(self.output_group_path +'_pcm')
        if self.data_count_tp2 == 0:
            os.remove(self.output_group_path +'_spp')
        if self.data_count_tp3 == 0:
            os.remove(self.output_group_path +'_opus')


if args['decoder'] == True:
    input_bin_path = args['<input_bin>']
    output_file_name = args['--output']
    integrity_check = args['--integrity_check'] 

    u2s_decoder = U2SDecoder([0x4a, 0x00], input_bin_path, output_file_name, integrity_check)
    
    while u2s_decoder.file_end == False:
        u2s_decoder.data_pump_out()
        decoded_bytes, progress_percent = u2s_decoder.progress_update()
        print("already decoded {:.2f} KB data. {:.2%} completed...\r".format(decoded_bytes/(1<<10), progress_percent), end='')
    
    u2s_decoder.packet_integrity_check()

    print("\n\rAll data decoded...")
    print("Get {} bytes general data".format(u2s_decoder.data_count_tp0))
    print("Get {} bytes pcm data".format(u2s_decoder.data_count_tp1))
    print("Get {} bytes spp/merged data".format(u2s_decoder.data_count_tp2))
    print("Get {} bytes opus data".format(u2s_decoder.data_count_tp3))

    del u2s_decoder

if args['logger'] == True:
    try:
        subprocess.call('.\AmU2S_exe\AmU2S.exe apollo_spi.bin', shell=True)
        #subprocess.call('.\dll\AmU2S_v0.3.exe apollo_spi.bin', shell=True)
    
    except KeyboardInterrupt:
        print("\n")
        print("Processing data......")

        output_file_name = args['--output']
        integrity_check = args['--integrity_check'] 
    
        u2s_decoder = U2SDecoder([0x4a, 0x00], 'apollo_spi.bin', output_file_name, integrity_check)
        
        while u2s_decoder.file_end == False:
            u2s_decoder.data_pump_out()
            decoded_bytes, progress_percent = u2s_decoder.progress_update()
            print("already decoded {:.2f} KB data. {:.2%} completed...\r".format(decoded_bytes/(1<<10), progress_percent), end='')
        
        u2s_decoder.packet_integrity_check()
    
        print("\n\rAll data decoded...")
        print("Get {} bytes general data".format(u2s_decoder.data_count_tp0))
        print("Get {} bytes pcm data".format(u2s_decoder.data_count_tp1))
        print("Get {} bytes spp/merged data".format(u2s_decoder.data_count_tp2))
        print("Get {} bytes opus data".format(u2s_decoder.data_count_tp3))
    
        del u2s_decoder

