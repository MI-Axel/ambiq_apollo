"""
Usage:
    apollo_hp_plot.py <register_value> [--frequency=<fs>]

Arguments:
    <register_value>                        high pass filter register hex value
Options:
    -h, --help                              Show this screen
    -f <fs>, --frequency=<fs>               sample frequency.[default: 16000]
"""
from docopt import docopt
import numpy as np
import scipy
from scipy import signal
import matplotlib.pyplot as plt

args = docopt(__doc__)

HP_Gain = np.int(args['<register_value>'], 16) * (-1)

Fs = np.int(args['--frequency'])

filtNumer = np.array([1., -1.], dtype=float)

filtDenom = np.array([1, -(1-2**HP_Gain)], dtype=float)

w, h = signal.freqz(filtNumer, filtDenom, fs=Fs)

cutFreqIndx = np.where(20*np.log10(abs(h)) > -3)[0][0]

print("the cut off frequency is {} HZ.".format(w[cutFreqIndx]))

fig, ax1 = plt.subplots()
ax1.set_title('linear phase filter frequency response')
ax1.plot(w, 20 * np.log10(abs(h)), 'b')
ax1.plot(w[cutFreqIndx], 20*np.log10(abs(h[cutFreqIndx])), linewidth=6, markersize=10, marker='x', color='y')
ax1.set_ylabel('Amplitude [dB]', color='b')
ax1.set_xlabel('Frequency [HZ]')
ax2 = ax1.twinx()
angles = np.unwrap(np.angle(h))
ax2.plot(w, angles, 'g')
ax2.set_ylabel('Angle (radians)', color='g')
ax2.grid()
ax2.axis('tight')
plt.show()
