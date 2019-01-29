import struct
import serial
import soundfile as sf
import matplotlib.pyplot as plt
import numpy as np
import time

plt.close('all')

# Define serial connection
port = 'COM3'
baudrate = 460800
timeout = 10

def serialGetdata():
    dataStream = bytes()
    while True:
        size = ser.in_waiting
        if size == 0:
            return dataStream
        else:
            while size != 0:
                dataByte = ser.read(1)
                dataStream += (dataByte)
                size -= 1
 
try:
    detect_times = 0
    ser = serial.Serial(port, baudrate, timeout=0.001)
    ser.reset_input_buffer()
    print("serial port is open.")
    now = time.strftime("-%Y-%m-%d-%H_%M", time.localtime(time.time()))
    f = open('FAR_log' + now + '.txt', 'w') 
    while True:
        dataStream = serialGetdata()
        if len(dataStream) > 0:
            log = struct.unpack('<'+'B'*len(dataStream), dataStream)
            log = np.array(log, dtype=int)
            if [0x55, 0x11, 0x11, 0xaa] in log[:]:
                now = time.strftime("%H-%M-%d", time.localtime(time.time()))
                print("The key word is detected at {}".format(now))
                f.write("The key word is detected at {}\n".format(now))
                detect_times += 1
            else:
                now = time.strftime("%H-%M-%d", time.localtime(time.time()))
                f.write("the received data is {}. There might be something wrong at {}.\n".format(log, now))
except KeyboardInterrupt:
    ser.close()
    print('the serial port is closed. Start to process data...')
    f.write("there are totally {} times of key word detected!\n".format(detect_times))
    f.write("The test is over.")
    f.close()
