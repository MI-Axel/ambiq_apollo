function handles = load_array_1(mic_array, handles)

if mic_array.include_center
    handles.include_center.Value = 1;
    handles.num_mics.String = num2str(mic_array.num_mics-1);
else
    handles.include_center.Value = 0;
    handles.num_mics.String = num2str(mic_array.num_mics);
end

ARRAY_GEOMETRY = mic_array.geometry;
handles.geometry_choice.Value = find(strcmp(handles.geometry_choice.String, ARRAY_GEOMETRY));
if strcmp( ARRAY_GEOMETRY, 'Linear' )
    handles.spacing_value.String = num2str(mic_array.spacing*1000);
elseif strcmp( ARRAY_GEOMETRY, 'Circle' )
    handles.spacing_value.String = num2str(mic_array.spacing*1000);
elseif strcmp( ARRAY_GEOMETRY, 'Triangle' )
    handles.spacing_value.String = num2str(mic_array.spacing*1000);
elseif strcmp( ARRAY_GEOMETRY, 'Square' )
    handles.spacing_value.String = num2str(mic_array.spacing*1000);
end
handles.rotation.String = num2str(mic_array.rotation);
if mic_array.ordering == 1
    handles.set_order.Value = 0;
    handles.mic_ordering.Enable = 'off';
else
    handles.set_order.Value = 1;
    order = '[';
    for m = 1:length(mic_array.ordering)
        if m < length(mic_array.ordering)
            order = [order num2str(mic_array.ordering(m)) ','];
        else
            order = [order num2str(mic_array.ordering(m))];
        end
    end
    handles.mic_ordering.String = [order ']'];
    handles.mic_ordering.Enable = 'on';
end

% remove rotation since rotation field shows this
rotation_matrix = [cosd(mic_array.rotation),-1*sind(mic_array.rotation);...
                   sind(mic_array.rotation),cosd(mic_array.rotation)];
MIC_POS = mic_array.pos*rotation_matrix;
% if strcmp( ARRAY_GEOMETRY, 'Custom' )
%     MIC_POS = mic_array.spacing*rotation_matrix;
% else
%     MIC_POS = mic_array.pos*rotation_matrix;
% end
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
handles.x_coord_1.String = X_COORD_STR;
handles.y_coord_1.String = Y_COORD_STR;

handles.directivity_1 = mic_array.directivity_path;
if mic_array.directivity_path == 1
    handles.directivity_status.String = 'Omnidirectional';
else
    [~,NAME,EXT] = fileparts(mic_array.directivity_path);
    handles.directivity_status.String = [NAME EXT];
end