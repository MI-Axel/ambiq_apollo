'compute_beamformer.m' 

This scripts shows how to compute the beamformer weights with scripting. It is 
essentially what happens behind the GUI. There are some additional 
visualization that are not available from the GUI (which take place at the 
bottom of the script):

1) The function 'plot_polar_plots' lays multiple polar plots (of user
specified frequencies) on top of each other.
2) The function 'plot_snr_gain' compute the SNR gain for multiple uncorrelated 
to diffuse noise ratios (specified by the user in dB).
3) The function 'compute_fir_coefficients' computes the FIR coefficients with 
the number of taps specified by the user. The attenuation due to truncation is 
also visualized.

-------------------------------------------------------------------------------

'compute_differential_endfire_weights.m'

This script shows how to compute weights in a "hand-written" manner, i.e. without using one of the pre-defined approaches, and use the utilities for 
analyzing the performance of the beamformer. In this case, we compute 
differential endfire weights in the frequency domain and adjust the magnitude 
of the weights to obtain unity gain (distortionless response) in the target 
direction while staying below a certain uncorrelated noise gain.

-------------------------------------------------------------------------------

'compare_beamformers.m'

After computing the beamformers (with the 'compute_beamformer.m' or with the 
GUI) and saving their structs to a ".mat" file, they can be compared with this 
scripts. This script is what essentially happens when two beamformers are 
compared with the GUI. However, more than two beamformers can be compared with 
this script (including those that contain "hand-written" weights, e.g. from 
'compute_differential_endfire_weights.m').