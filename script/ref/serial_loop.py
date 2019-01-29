import serial
from random import random
import time
import struct

#ser = serial.Serial("COM49", 115200)
ser = serial.Serial("COM24", 115200)
#ser.timeout = 1

cnt1 = 0
cnt2 = 0
slen = 0
sd = ''
rd = ''
print 'read availble data inside'
ser.timeout = 0.1
bk = ser.read(ser.inWaiting())
print ','.join(['%02x' % ord(i) for i in bk])
ser.timeout = None
ser.timeout = 1

loop_tm = 1000

while True:
    dlen = int(random() * 2048)
    #dlen = 1024
    dli = [chr(int(random()*256)) for i in range(dlen)]
    dat = ''.join(dli)
    #print 'write %d' % len(dat)
    ser.write(dat)
    #print ','.join(['%02x' % ord(i) for i in dli])
    bk = ser.read(dlen)
    #print 'read %d' % len(bk)
    #print ','.join(['%02x' % ord(i) for i in bk])

    if len(bk) != dlen:
        print 'insufficient data, got %d' % len(bk)
        print 'write %d' % len(dat)
        print ','.join(['%02x' % ord(i) for i in dli])
        print 'read %d' % len(bk)
        print ','.join(['%02x' % ord(i) for i in bk])
        break

    wrong = False
    for i, k in zip(dat, bk):
        if i == k:
            slen += 1
            wrong == False
            if sd:
                print sd
                print rd
                print len(sd)/3, len(rd)/3, 'err'
                sd = ''
                rd = ''
        else:
            if not wrong and slen != 0:
                print '%d data passed' % slen
                slen = 0
            wrong == True
            sd += '%02x,' % ord(i)
            rd += '%02x,' % ord(k)
    if sd:
        print 'error frame'
        print sd
        print '====='
        print rd
        print len(sd)/3, len(rd)/3, 'err'
        break

    cnt2 += 1
    print 'loop %d' % (cnt1*100+cnt2)
    if cnt2 == 100:
        cnt1 += 1
        #print 'loop %d' % (cnt1*100)
        cnt2 = 0
    if cnt1*100 + cnt2 > loop_tm:
        pass
        #print 'all right'
        #break
    time.sleep(0.05)
