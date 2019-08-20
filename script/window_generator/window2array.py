"""
Usage:
    window2array.py <window_name> <window_length> [<output_path>]

Arguments:
    <window_name>                               The name of observe-window: hanning, hamming, bartlett, blackman, kaiser
    <window_length>                             The length of observe-window
    <output_path>                               The output path (optional, e.g. ~/KWS/ . no need of name and last / required)
Options:
    -h, --help                                  Show this screen
"""

from docopt import docopt
import numpy as np
from scipy import signal

arguments = docopt(__doc__)

windowName = arguments['<window_name>']

windowLength = np.int(arguments['<window_length>'])

savedPath = arguments['<output_path>']

if windowName == 'hanning':
    # unsymmetrical window needed for reconstruction 
    windowArray = signal.windows.hann(windowLength, sym=False)
elif windowName == 'hamming':
    windowArray = np.hamming(windowLength)
elif windowName == 'bartlett':
    windowArray = np.bartlett(windowLength)
elif windowName == 'blackman':
    windowArray = np.blackman(windowLength)
#elif windowName == 'kaiser':
#    windowArray = np.kaiser(windowLength)

if savedPath: 
    fileName = savedPath + windowName + '_' + arguments['<window_length>'] +'.h'
else:
    fileName = windowName + '_' + arguments['<window_length>'] + '.h'

initialComment = '/*\n*window function array created from window2array python script.\n*'+ windowName + '_' +arguments['<window_length>'] + '.h\n*\n*/\n\n'

arrayName = 'const float32_t g_f32' + windowName[0].upper() + windowName[1:] + 'Window' + '[' + str(windowLength) + '] = {\n' + '    '

with open(fileName, 'w') as window_header:
    window_header.write(initialComment)
    window_header.write(arrayName)
    for indx in range(len(windowArray)):
        window_header.write(str(format(windowArray[indx], '.6f')))

        if indx == len(windowArray) - 1:
            window_header.write('\n'+'};')
        else:
            window_header.write(', ')
        if (indx+1) % 10 == 0:
            window_header.write('\n'+'    ')
