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
timeout = 10
dataLen = np.int(16000 * 0.5 )
AudioStream = bytes() 

def serialGetdata():
    global AudioStream
    while True:
        size = ser.in_waiting
        if size == 0:
            break
        else:
            while size != 0:
                dataByte = ser.read(1)
                AudioStream += (dataByte)
                size -= 1
## Read from serial port
try:
    ser = serial.Serial(port, baudrate, timeout=0.001)
    ser.reset_input_buffer()
    print("serial port is open.") 
    while True:
        serialGetdata()
except KeyboardInterrupt:
    print('Length of audio stream: {}'.format(len(AudioStream)))
    ser.close()
    print('the serial port is closed. Start to process data...')
    WavStream = struct.unpack('<'+'h'*(len(AudioStream)//2), AudioStream)
    WavStream = np.array(WavStream, dtype=float)
    WavStream = WavStream / 32768
    sf.write('NewFrameWork_PreNorm.wav', WavStream, 16000)
    WavStream = WavStream/np.max([np.max(WavStream),np.abs(np.min(WavStream))])
#    WavStream = WavStream - np.mean(WavStream)
    sf.write('NewFrameWork_Norm.wav', WavStream, 16000)
    print('The data process is finished. The wav file is saved.')
#print('Length of b: {}'.format(len(b)))
#x=np.array(x)
#AudioStream = np.array([0]*(len(x)//2), dtype=float)
#for i in range(len(x)//2):
#    AudioStream[i] = x[i*2]*0.5 + x[i*2+1]*0.5 
#print('Length of audio stream: {}'.format(len(AudioStream)))
#
##plt.subplot(211)
##plt.plot(x)
#AudioStream = AudioStream/65535
##plt.subplot(212)
##plt.plot(x)
#AudioStream = AudioStream - np.mean(AudioStream)
#sf.write('PreNorm.wav', AudioStream, 16000)

#sf.write('Norm.wav', x, 16000)
#plt.plot(t,x)
#plt.show()




