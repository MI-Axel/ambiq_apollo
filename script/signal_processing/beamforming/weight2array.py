"""
Usage:
    weight2array.py <weight_csv> [<output_file_name>]

Arguments:
    <weight_csv>                                The input csv file of beamforming weight
    <output_file_name>                          The name of output .c file.
Options:
    -h, --help                                  Show this screen
"""

from docopt import docopt
import numpy as np
import pandas as pd
from scipy import signal

arguments = docopt(__doc__)

input_csv_file = arguments['<weight_csv>']

if arguments['<output_file_name>'] is None: 
    OutputName = "beamforming_weights.c"
else:
    OutputName = arguments['<output_file_name>']

weights_txt = pd.read_csv(input_csv_file, header=None, names=['left', 'right'])

LeftChWeight = weights_txt['left'].str.replace('i', 'j').values.astype('str').astype(np.complex)

RightChWeight = weights_txt['right'].str.replace('i', 'j').values.astype('str').astype(np.complex)

arrayLen_C = len(LeftChWeight) * 2 
# Convert both arrays to arm-c-style arrays
const_params_L = np.array([], dtype=np.float)
const_params_R = np.array([], dtype=np.float)

for i in range(len(LeftChWeight)):
    const_params_L = np.append(const_params_L, LeftChWeight[i].real)
    const_params_L = np.append(const_params_L, LeftChWeight[i].imag)    
    const_params_R = np.append(const_params_R, RightChWeight[i].real)
    const_params_R = np.append(const_params_R, RightChWeight[i].imag)

initialComment = '/*\n*End-fire beamforming weights array created from weight2array python script.\n*\n*/\n'
arrayName_L = 'const float32_t g_f32' + 'BeamformingWeightLeftChPara' + '[' + str(arrayLen_C) + '] = {\n' + '    '
arrayName_R = 'const float32_t g_f32' + 'BeamformingWeightRightChPara' + '[' + str(arrayLen_C) + '] = {\n' + '    '
with open(OutputName, 'w') as bf:
    bf.write(initialComment)
    bf.write(arrayName_L)
    for indx in range(len(const_params_L)):
        bf.write(str(format(const_params_L[indx], '.6f')))
        if indx == len(const_params_L) - 1:
            bf.write('\n'+'};')
        else:
            bf.write(', ')
        if (indx+1) % 10 == 0:
            bf.write('\n'+'    ')

    bf.write('\n')
    bf.write(arrayName_R)
    for indx in range(len(const_params_R)):
        bf.write(str(format(const_params_R[indx], '.6f')))
        if indx == len(const_params_R) - 1:
            bf.write('\n'+'};')
        else:
            bf.write(', ')
        if (indx+1) % 10 == 0:
            bf.write('\n'+'    ')
