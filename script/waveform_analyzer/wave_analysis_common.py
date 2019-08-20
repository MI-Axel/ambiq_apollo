from numpy import array_equal, polyfit, sqrt, mean, absolute, log10, arange
import numpy as np
from scipy.stats import gmean

def rms_flat(a):
    """
    Return the root mean square of all the elements of *a*, flattened out.
    """
    return sqrt(mean(absolute(a)**2))


def find(condition):
    "Return the indices where ravel(condition) is true"
    res, = np.nonzero(np.ravel(condition))
    return res


def dB(q):
    """
    Return the level of a field quantity in decibels.
    """
    return 20 * log10(q)


