"""
Usage: 
    signal_generator.py <clean> <noise> [options]

Arguments:
    <clean>                             Input clean signal
    <noise>                             Input noise signal 
Options:
    -h, --help                          Show this screen
    -s, --snr=<dB>                           SNR in dB.[default: 4]
    -f, --offset=<S>                        The segment before clean signal starts.[default: 5]
    -o, --output=<op>                        Output generated.[default: noisy_sig.wav]
"""
from docopt import docopt
import numpy as np
import soundfile as sf
from scipy import signal
from scipy.io import wavfile

def create_noisy_signal(signal_fp, snr, noise_fp=None, offset=None, output='noisy_sig.wav'):
    """
    Create a noisy signal of a specified SNR.
    Parameters
    ----------
    signal_fp : string
        File path to clean input.
    snr : float
        SNR in dB.
    noise_fp : string
        File path to noise. Default is to use randomly generated white noise.
    offset : float
        Offset in seconds before starting the signal.
    Returns
    -------
    numpy array
        Noisy signal with specified SNR, between [-1,1] and zero mean.
    numpy array
        Clean signal, untouched from WAV file.
    numpy array
        Added noise such that specified SNR is met.
    int
        Sampling rate in Hz.
    """
    clean_signal, fs = sf.read(signal_fp)
    clean_signal = to_float32(clean_signal)
    if offset is not None:
        offset_samp = int(offset * fs)
    else:
        offset_samp = 0
    output_len = len(clean_signal) + offset_samp
    silenceStart = np.zeros(offset_samp)
    # to make clean signal same length with noise
    clean_signal = np.append(silenceStart, clean_signal)

    if noise_fp is not None:
        noise, fs_n = sf.read(noise_fp)
        noise = to_float32(noise)
        if fs_n != fs:
            raise ValueError("Signal and noise WAV files should have same "
                             "sampling rate.")
        # truncate to same length
        if len(noise) < output_len:
            raise ValueError("Length of signal file should be longer than "
                             "noise file.")
        noise = noise[:output_len]
    else:
        raise Exception("there is no noise file found...")

    # weight noise according to desired SNR
    signal_level = rms(clean_signal)
    noise_level = rms(noise[offset_samp:])
    noise_fact = signal_level / noise_level * 10 ** (-snr / 20)
    noise_weighted = noise * noise_fact

    # add signal and noise
    noisy_signal = clean_signal + noise_weighted

    # ensure between [-1, 1]
    norm_fact = np.abs(noisy_signal).max()
    clean_signal /= norm_fact
    noise_weighted /= norm_fact
    noisy_signal /= norm_fact

    # remove any offset
    noisy_signal -= noisy_signal.mean()
    wavfile.write(output, fs, noisy_signal)


def rms(data):
    """
    Compute root mean square of input.
    Parameters
    ----------
    data : numpy array
        Real signal in time domain.
    Returns
    -------
    float
        Root mean square.
    """
    return np.sqrt(np.mean(data * data))


def to_float32(data):
    """
    Cast data (typically from WAV) to float32.
    Parameters
    ----------
    data : numpy array
        Real signal in time domain, typically obtained from WAV file.
    Returns
    -------
    numpy array
        `data` as float32.
    """

    if np.issubdtype(data.dtype, np.integer):
        max_val = abs(np.iinfo(data.dtype).min)
        return data.astype(np.float32) / max_val
    else:
        return data.astype(np.float32)


def to_16b(signal):
    '''
    converts float 32 bit signal (-1 to 1) to a signed 16 bits representation
    No clipping in performed, you are responsible to ensure signal is within
    the correct interval.
    '''
    return ((2**15-1)*signal).astype(np.int16)


if __name__ == "__main__":
    args = docopt(__doc__)
    sig_in = args['<clean>']
    noise_in = args['<noise>']
    snr = np.float(args['--snr'])
    offset = np.float(args['--offset'])
    output = args['--output']
    create_noisy_signal(sig_in, snr, noise_in, offset, output)
