#Listen to the music from VOS dev-kit

From previous articles, we learned about how to record the audio signla using VOS dev-kit. Now, we learn about using python script to translate the binary file of audio signal to wav file. With that, we could evaluate the signal chain and audio signal processing algorithm by our ears. It's really useful and intuitive in some user cases. 

## Binary file and Endianness

###binary file
The RTT log file we got in the last article is saved as a **binary file**. This file is computer-readable but not human-readable. All executable programs are stored in binary files, as are most numeric data files. In contrast, text files are stored in a form (usually ASCII) that is human-readable.

###Endianness

From the previous article, we know the 1 sample of audio data is combined as 4 bytes. Problems happen when computers try to read multiple bytes. Now problems start:

-When you read multi-byte data, where does the biggest byte appear? 

* **Big endian machine:** Stores data big-end first. When looking at multiple bytes, the first byte (lowest address) is the biggest. 

* **Little endian machine:** Stores data little-end first. When looking at multiple bytes, the first byte is smallest.

Since apollo MCU uses little endian machine, we could also process the binary file transmit from VOS dev-kit as little endian machine. 

##Convert Binary file to Wav file with Python

Here is the section of python code to finish binary-wav translation.


```
binStream = open(input_file, 'rb').read()
print("read input file of {} bytes...".format(len(binStream)))
if (self.channels == 2) and (self.sample_bits == 16):
    parseData = struct.unpack('<'+'h'*(len(binStream)//2), binStream)
    parseData = np.array(parseData)
    self.pcmLeftStream = np.array([0]*(len(parseData)//2), dtype=int)
    self.pcmRightStream = np.array([0]*(len(parseData)//2), dtype=int)
    if(self.LRswap == False):
        for i in range(len(self.pcmLeftStream)):
            self.pcmLeftStream[i] = parseData[2*i]
            self.pcmRightStream[i] = parseData[2*i+1]
    else:
        for i in range(len(self.pcmLeftStream)):
            self.pcmLeftStream[i] = parseData[2*i+1]
            self.pcmRightStream[i] = parseData[2*i]
elif (self.channels == 1) and (self.sample_bits == 16):
    parseData = struct.unpack('<'+'h'*(len(binStream)//2), binStream)
    self.pcmMonoStream = np.array(parseData, dtype=int)

```