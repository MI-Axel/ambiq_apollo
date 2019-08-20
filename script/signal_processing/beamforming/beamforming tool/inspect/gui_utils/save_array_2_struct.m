function mic_array = save_array_2_struct(handles, plot_array)

if nargin < 2
    plot_array = false;
end

% create microphone array struct
ARRAY_GEOMETRY = handles.geometry_choice.String{handles.geometry_choice_2.Value};
NUM_MICS = str2double(handles.num_mics_2.String);
SPACING = str2double(handles.spacing_value_2.String)/1000; % to meters
ROTATION = str2double(handles.rotation_2.String);
FS = str2double(handles.sampling_freq.String);
MIC_NOISE_LEVEL = str2double(handles.mic_noise_level.String);
CENTER = handles.include_center_2.Value;
if handles.set_order_2.Value
    check_valid_ordering(handles.mic_ordering_2.String, NUM_MICS+CENTER);
    ORDERING = eval(handles.mic_ordering_2.String);
else
    ORDERING = 1;
end
if strcmp(ARRAY_GEOMETRY, 'Custom')
    X_COORD = eval(handles.x_coord_2.String);
    Y_COORD = eval(handles.y_coord_2.String);
    if length(X_COORD) ~= length(Y_COORD)
        error('X and Y coordinates must have the same length!');
    end
    SPACING = [X_COORD(:), Y_COORD(:)]/1000;
    mic_array = create_mic_array( ARRAY_GEOMETRY, length(X_COORD), SPACING, ROTATION, FS, ...
        MIC_NOISE_LEVEL, false, handles.directivity_2, ORDERING, plot_array );
else
    mic_array = create_mic_array( ARRAY_GEOMETRY, NUM_MICS, SPACING, ROTATION, FS, ...
        MIC_NOISE_LEVEL, CENTER, handles.directivity_2, ORDERING, plot_array );
end