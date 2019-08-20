function mic_array = save_array_1_struct(handles, plot_array)

if nargin < 2
    plot_array = false;
end

% create microphone array struct
ARRAY_GEOMETRY = handles.geometry_choice.String{handles.geometry_choice.Value};
NUM_MICS = str2double(handles.num_mics.String);
SPACING = str2double(handles.spacing_value.String)/1000; % to meters
ROTATION = str2double(handles.rotation.String);
FS = str2double(handles.sampling_freq.String);
MIC_NOISE_LEVEL = str2double(handles.mic_noise_level.String);
CENTER = handles.include_center.Value;
if handles.set_order.Value
    check_valid_ordering(handles.mic_ordering.String, NUM_MICS+CENTER);
    ORDERING = eval(handles.mic_ordering.String);
else
    ORDERING = 1;
end
if strcmp(ARRAY_GEOMETRY, 'Custom')
    X_COORD = eval(handles.x_coord_1.String);
    Y_COORD = eval(handles.y_coord_1.String);
    if length(X_COORD) ~= length(Y_COORD)
        error('X and Y coordinates must have the same length!');
    end
    SPACING = [X_COORD(:), Y_COORD(:)]/1000;
    mic_array = create_mic_array( ARRAY_GEOMETRY, length(X_COORD), SPACING, ROTATION, FS, ...
        MIC_NOISE_LEVEL, false, handles.directivity_1, ORDERING, plot_array );
else
    mic_array = create_mic_array( ARRAY_GEOMETRY, NUM_MICS, SPACING, ROTATION, FS, ...
        MIC_NOISE_LEVEL, CENTER, handles.directivity_1, ORDERING, plot_array );
end