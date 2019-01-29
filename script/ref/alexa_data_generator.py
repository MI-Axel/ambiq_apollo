import numpy as np
from pydub import AudioSegment
import librosa
import random
import sys
import io
import os
import glob

# Following functions are used to overlay alexa or megatives with background

def get_random_time_segment(segment_ms, clip_ms=10000):
    """
    Gets a random time segment of duration segment_ms in a 10,000 ms audio clip.
    
    Arguments:
    segment_ms -- the duration of the inserted segment in ms ("ms" stands for "milliseconds")
    clip_ms  -- the duration of background clip in ms 
    
    Returns:
    segment_time -- a tuple of (segment_start, segment_end) in ms
    """
    assert clip_ms > segment_ms, "segment_ms should be less than clip_ms."
    segment_start = np.random.randint(low=0, high=clip_ms-segment_ms)   # Make sure segment doesn't run past the 10sec background 
    segment_end = segment_start + segment_ms - 1
    
    return (segment_start, segment_end)

# GRADED FUNCTION: is_overlapping

def is_overlapping(segment_time, previous_segments):
    """
    Checks if the time of a segment overlaps with the times of existing segments.

    Arguments:
    segment_time -- a tuple of (segment_start, segment_end) for the new segment
    previous_segments -- a list of tuples of (segment_start, segment_end) for the existing segments

    Returns:
    True if the time segment overlaps with any of the existing segments, False otherwise
    """

    segment_start, segment_end = segment_time

    ### START CODE HERE ### (≈ 4 line)
    # Step 1: Initialize overlap as a "False" flag. (≈ 1 line)
    overlap = False

    # Step 2: loop over the previous_segments start and end times.
    # Compare start/end times and set the flag to True if there is an overlap (≈ 3 lines)
    for previous_start, previous_end in previous_segments:
        if segment_start <= previous_end and segment_end >= previous_start:
            overlap = True
    ### END CODE HERE ###

    return overlap

# GRADED FUNCTION: insert_audio_clip

def insert_audio_clip(background, audio_clip, previous_segments):
    """
    Insert a new audio segment over the background noise at a random time step, ensuring that the
    audio segment does not overlap with existing segments.

    Arguments:
    background -- a 10 second background audio recording.
    audio_clip -- the audio clip to be inserted/overlaid.
    previous_segments -- times where audio segments have already been placed

    Returns:
    new_background -- the updated background audio
    """

    # Get the duration of the audio clip in ms
    segment_ms = len(audio_clip)
    insert_time = 0
    new_background = background
    new_segments = previous_segments
    ### START CODE HERE ###
    # Step 1: Use one of the helper functions to pick a random time segment onto which to insert
    # the new audio clip. (≈ 1 line)
    segment_time = get_random_time_segment(segment_ms)

    # Step 2: Check if the new segment_time overlaps with one of the previous_segments. If so, keep
    # picking new segment_time at random until it doesn't overlap. (≈ 2 lines)
    while is_overlapping(segment_time, previous_segments):
        segment_time = get_random_time_segment(segment_ms)
        insert_time = insert_time + 1
        if insert_time > 20000:
            return new_background, new_segments
    # Step 3: Add the new segment_time to the list of previous_segments (≈ 1 line)
    new_segments.append(segment_time)

    # Step 4: Superpose audio segment and background
    new_background = background.overlay(audio_clip, position = segment_time[0])

    return new_background, new_segments

# GRADED FUNCTION: insert_ones

def insert_ones(y, segment_end_ms, indicator_number, clip_length_ms):
    """
    Update the label vector y. The labels of the 50 output steps strictly after the end of the segment
    should be set to 1. By strictly we mean that the label of segment_end_y should be 0 while, the
    50 followinf labels should be ones.


    Arguments:
    y -- numpy array of shape (1, Ty), the labels of the training example
    segment_end_ms -- the end time of the segment in ms

    Returns:
    y -- updated labels
    """

    # duration of the background (in terms of spectrogram time-steps)
    Ty = len(y)
    segment_end_y = int(segment_end_ms * Ty / clip_length_ms)

    # Add 1 to the correct index in the background label (y)
    ### START CODE HERE ### (≈ 3 lines)
    for i in range(segment_end_y, segment_end_y + indicator_number):
        if i < Ty:
            y[i] = 1
    ### END CODE HERE ###

    return y

def audio_synthesis(background_list, alexa_list, negatives_list, alexa_max, negatives_max):
    """
    background_list: the list of the background random choice
    alexa_sample_list and negatives_sample_list are the same with it.
    alexa_max and negatives_max are the upper threshold of the random number of alexa and negatives in the audio clip
    alexa_num:[0, alexa_max], negatives_num:[0, negatives_max]
    """
    # overlay 2 Alexa and 2 negatives with background noise
    background = np.random.choice(background_list, 1)
    alexa_num = random.randint(0, alexa_max)
    alexa_sample_list = np.random.choice(alexa_list, alexa_num)
    negatives_num = random.randint(0, negatives_max)
    negatives_sample_list = np.random.choice(negatives_list, negatives_num)

    previous_segments = []
    alexa_segments = []
    alexa_insert_list = []
    negatives_insert_list = []

    background_data = AudioSegment.from_wav(background[0])

    for alexa_sample in alexa_sample_list:
        alexa_insert_list.append(AudioSegment.from_wav(alexa_sample))

    for negatives_sample in negatives_sample_list:
        negatives_insert_list.append(AudioSegment.from_wav(negatives_sample))

    new_clip = background_data

    for audio in alexa_insert_list:
        new_clip, previous_segments = insert_audio_clip(new_clip, audio, previous_segments)
    alexa_segments = alexa_segments + previous_segments
    for audio in negatives_insert_list:
        new_clip, previous_segments = insert_audio_clip(new_clip, audio, previous_segments)

    return new_clip, previous_segments, alexa_segments

# data generator for train, validation and test
# parameters:
def mfcc_data_generator(audio_path, num_features, fft_window, hop_length, pad_length=0):
    wave, sr = librosa.load(audio_path, sr=None)
    mfcc = librosa.feature.mfcc(wave, sr, n_mfcc=num_features, hop_length=int(hop_length*sr), n_fft=int(fft_window*sr))
    if pad_length:
        mfcc = np.pad(mfcc,((0,0),(0,pad_length-len(mfcc[0]))), mode='constant', constant_values=0)

    audio_mfcc = np.array(mfcc).T
    return audio_mfcc


# Label generator for model training 
def train_label_generator(y_label, activate_segment, indicator_number=5, clip_length_ms=10000.0):
    for segment in activate_segment:
        y_label = insert_ones(y_label, segment[-1], indicator_number=indicator_number, clip_length_ms=clip_length_ms)
    return y_label
