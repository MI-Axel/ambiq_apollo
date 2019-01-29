import serial, struct
import soundfile as sf
import matplotlib.pyplot as plt
import numpy as np
import time
import subprocess

plt.close('all')

# Define serial connection
port = 'COM23'
baudrate = 460800
#baudrate = 115200
timeout = 10

# Set up experiment parameters and data structures
kwd = False
data_len = 2*16000*10 #bytes

# Read from serial port
with serial.Serial(port, baudrate, timeout=timeout) as ser:
    ser.reset_input_buffer()
    print('Entered new loop')
    while not kwd:
        if ser.in_waiting>0:
            kwd = True
            b = ser.read(size=data_len)


with open('PreNorm.sbc', 'wb') as f:
	#x = struct.unpack('<'+'h'*(len(b)//2), b)
	f.write(b)
	
fn = 'PreNorm'
exe_name = 'ia_sbc_dec_test.exe'
subprocess.call('{} -ifile:{}.sbc -ofile:{}.wav'.format(
    exe_name, fn, fn), shell=True)

x, fs = sf.read('PreNorm.wav')	
x = x - np.mean(x)
x = x/np.max(np.abs(x))
sf.write('Norm.wav', x, fs)	
