import struct
import serial
import soundfile as sf
import matplotlib.pyplot as plt
import numpy as np
import time

plt.close('all')

# Define serial connection
port = 'COM4'
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


print('Length of b: {}'.format(len(b)))
x = struct.unpack('<'+'h'*(len(b)//2), b)
x=np.array(x)
x = x.astype(float)
plt.subplot(211)
plt.plot(x)
x = x/32768
plt.subplot(212)
plt.plot(x)
#x = x - np.mean(x)
sf.write('PreNorm.wav', x, 16000)

x = x/np.max([np.max(x),np.abs(np.min(x))])
sf.write('Norm.wav', x, 16000)
#plt.plot(t,x)
#plt.show()
