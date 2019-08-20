function handles = update_mic_positions_2(handles)

if ~strcmp( handles.geometry_choice_2.String{handles.geometry_choice_2.Value}, 'Custom' )
    
    mic_array = save_array_2_struct(handles);
    
    % remove rotation since rotation field shows this
    rotation_matrix = [cosd(mic_array.rotation),-1*sind(mic_array.rotation);...
                       sind(mic_array.rotation),cosd(mic_array.rotation)];
    MIC_POS = mic_array.pos*rotation_matrix;
    MIC_POS(abs(MIC_POS) < 1e-9) = 0; % anything smaller than nano meter --> 0

    % setting coordinates
    x_coord = MIC_POS(:,1);
    y_coord = MIC_POS(:,2);

    X_COORD_STR = '[';
    Y_COORD_STR = '[';
    for m = 1:length(x_coord)
        if m < length(x_coord)
            X_COORD_STR = [X_COORD_STR num2str(x_coord(m)*1000) ','];  % append and convert to mm
            Y_COORD_STR = [Y_COORD_STR num2str(y_coord(m)*1000) ','];
        else
            X_COORD_STR = [X_COORD_STR num2str(x_coord(m)*1000) ']'];
            Y_COORD_STR = [Y_COORD_STR num2str(y_coord(m)*1000) ']'];
        end
    end
    handles.x_coord_2.String = X_COORD_STR;
    handles.y_coord_2.String = Y_COORD_STR;
    
end