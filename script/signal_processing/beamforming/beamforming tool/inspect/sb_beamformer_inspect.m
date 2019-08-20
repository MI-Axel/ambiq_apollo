function varargout = sb_beamformer_inspect(varargin)
% SB_BEAMFORMER_INSPECT MATLAB code for sb_beamformer_inspect.fig
%      SB_BEAMFORMER_INSPECT, by itself, creates a new SB_BEAMFORMER_INSPECT or raises the existing
%      singleton*.
%
%      H = SB_BEAMFORMER_INSPECT returns the handle to a new SB_BEAMFORMER_INSPECT or the handle to
%      the existing singleton*.
%
%      SB_BEAMFORMER_INSPECT('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SB_BEAMFORMER_INSPECT.M with the given input arguments.
%
%      SB_BEAMFORMER_INSPECT('Property','Value',...) creates a new SB_BEAMFORMER_INSPECT or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before sb_beamformer_inspect_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to sb_beamformer_inspect_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help sb_beamformer_inspect

% Last Modified by GUIDE v2.5 18-Jul-2017 11:07:23

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @sb_beamformer_inspect_OpeningFcn, ...
                   'gui_OutputFcn',  @sb_beamformer_inspect_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before sb_beamformer_inspect is made visible.
function sb_beamformer_inspect_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to sb_beamformer_inspect (see VARARGIN)

%% PART OF DESIGNER 2.0 Boiler plate code %%
action = varargin{1};
if ~strcmpi(action, 'new')
    % New should be the only action that's called for matlab custom
    % inspectors
    return;
end

% Get all the input variables for action == 'new'
M = varargin{2};
sInspectorID = varargin{3};
nGSYSIndex = varargin{4};
windowPosition = varargin{5};

% Set the UD struct with the persisted values
M.inspectUserData.figureHandle = handles.figure1;
M.inspectUserData.sInspectorID = sInspectorID;
M.inspectUserData.designerInstanceID = nGSYSIndex;
M.inspectUserData.position = windowPosition;

% Set the name of the figure to the module name
set(handles.figure1, 'Name', M.name);

%% --------------------------------------- %%

% add path for utility functions
[thisDir] = fileparts(mfilename('fullpath'));
addpath(fullfile(thisDir, 'weight_computation'));
addpath(fullfile(thisDir, 'utils'));
addpath(fullfile(thisDir, 'gui_utils'));

% parse variable argument inputs
handles.M = M;
handles.GSYS_index = nGSYSIndex;
handles.AW_NUMMICS = handles.M.constructorArgument{4}.value;
handles.AW_NUMBINS = handles.M.constructorArgument{3}.value;
handles.AW_NUMBEAMS = handles.M.numBeams;

% set values and options based on Module arguments (fixed)
handles.num_mics.String = num2str(handles.AW_NUMMICS);
handles.num_mics_2.String = num2str(handles.AW_NUMMICS);
handles.num_mics.Enable = 'off';
handles.num_mics_2.Enable = 'off';
if handles.AW_NUMMICS == 2
    handles.geometry_choice.String = {'Linear';'Custom'};
    handles.geometry_choice_2.String = {'Linear';'Custom'};
elseif handles.AW_NUMMICS == 3
    handles.geometry_choice.String = {'Linear';'Circle';'Triangle';'Custom'};
    handles.geometry_choice_2.String = {'Linear';'Circle';'Triangle';'Custom'};
elseif handles.AW_NUMMICS == 4
    handles.geometry_choice.String = {'Linear';'Circle';'Triangle';'Square';'Custom'};
    handles.geometry_choice_2.String = {'Linear';'Circle';'Triangle';'Square';'Custom'};
elseif handles.AW_NUMMICS == 5
    handles.geometry_choice.String = {'Linear';'Circle';'Square';'Custom'};
    handles.geometry_choice_2.String = {'Linear';'Circle';'Square';'Custom'};
else
    handles.geometry_choice.String = {'Linear';'Circle';'Custom'};
    handles.geometry_choice_2.String = {'Linear';'Circle';'Custom'};
end

% initialize beam direction selection for exporting
handles.select_all_beam_indices.Value = 1;
select_all_beam_indices_Callback(hObject, eventdata, handles);
beam_directions = 0:(360/handles.AW_NUMBEAMS):360;
beam_directions = beam_directions(1:handles.AW_NUMBEAMS);
beam_directions_str = '[';
for m = 1:length(beam_directions)
    if m < length(beam_directions)
        beam_directions_str = [beam_directions_str num2str(beam_directions(m)) ','];
    else
        beam_directions_str = [beam_directions_str num2str(beam_directions(m)) ']'];
    end
end
handles.beam_directions.String = beam_directions_str;

% initialize frequency bin selection for exporting
handles.select_all_freq_bins.Value = 1;
select_all_freq_bins_Callback(hObject, eventdata, handles);

% set previous settings
if isfield(M.inspectUserData, 'guiData')
    
    % if one of module arguments changed (NUMBEAMS, NUMBINS, NUMMICS),
    % compare and copy checkboxes
    handles.same_array_as_2.Value = M.inspectUserData.guiData.copy_array_2;
    handles.same_arrays.Value =  M.inspectUserData.guiData.copy_array_1;
    handles.copy_beamformer_2.Value = M.inspectUserData.guiData.copy_beamformer_2;
    handles.copy_beamformer_1.Value = M.inspectUserData.guiData.copy_beamformer_1;
    handles.compare_checkbox.Value = M.inspectUserData.guiData.compare_button;
    
    % beamformers + mic arrays + constants
    handles.figure_label_1.String = M.inspectUserData.guiData.beamformer_1_label;
    handles.figure_label_2.String = M.inspectUserData.guiData.beamformer_2_label;
    if M.inspectUserData.guiData.AW_NUMMICS ~= handles.AW_NUMMICS
        % change mic array struct
        disp('Resetting array to Linear and Omnidirectional directivities as number of microphones has been modified.')
        msgbox('Resetting array to Linear and Omnidirectional directivities as number of microphones has been modified.')
        handles.directivity_1 = 1;
        handles.directivity_2 = 1;
        MIC_NOISE_LEVEL = 10*log10(M.inspectUserData.guiData.beamformer_1.mic_array.noise_var)+94;
        M.inspectUserData.guiData.beamformer_1.mic_array = create_mic_array(...
            'Linear', handles.AW_NUMMICS, 0.071, ...
            M.inspectUserData.guiData.beamformer_1.mic_array.rotation, ...
            M.inspectUserData.guiData.beamformer_1.mic_array.samp_freq, ...
            MIC_NOISE_LEVEL);
        M.inspectUserData.guiData.beamformer_2.mic_array = create_mic_array(...
            'Linear', handles.AW_NUMMICS, 0.071, ...
            M.inspectUserData.guiData.beamformer_2.mic_array.rotation, ...
            M.inspectUserData.guiData.beamformer_2.mic_array.samp_freq, ...
            MIC_NOISE_LEVEL);
    end
    if M.inspectUserData.guiData.AW_NUMBINS ~= handles.AW_NUMBINS
        select_all_freq_bins_Callback(hObject, eventdata, handles);
    end
    handles = load_array_1(M.inspectUserData.guiData.beamformer_1.mic_array, handles);
    handles = load_array_2(M.inspectUserData.guiData.beamformer_2.mic_array, handles);
    handles = load_beamformer_1_struct(M.inspectUserData.guiData.beamformer_1, ...
        handles);
    handles = load_beamformer_2_struct(M.inspectUserData.guiData.beamformer_2, ...
        handles);
    geometry_choice_Callback(hObject, eventdata, handles);
    geometry_choice_2_Callback(hObject, eventdata, handles);
    method_Callback(hObject, eventdata, handles);
    method_choice_2_Callback(hObject, eventdata, handles);
    
    compare_checkbox_Callback(hObject, eventdata, handles);
    
    % eval options
    handles.plot_mic_arrays.Value = M.inspectUserData.guiData.eval_options.arrays;
    handles.plot_filter_responses.Value = M.inspectUserData.guiData.eval_options.filter_responses;
    handles.plot_heatmap_2d.Value = M.inspectUserData.guiData.eval_options.heatmap;
    handles.plot_polar_plots.Value = M.inspectUserData.guiData.eval_options.polar_plots;
    handles.plot_snr.Value = M.inspectUserData.guiData.eval_options.snr;
    handles.plot_snr_gain.Value = M.inspectUserData.guiData.eval_options.snr_gain;
    handles.plot_directivity_idx.Value = M.inspectUserData.guiData.eval_options.directivity_idx;
    handles.plot_beamwidth.Value = M.inspectUserData.guiData.eval_options.beam_width;
    handles.plot_uncorrelated_noise_gain.Value = M.inspectUserData.guiData.eval_options.uncorrelated_noise_gain;
    handles.plot_ambient_noise_gain.Value = M.inspectUserData.guiData.eval_options.ambient_noise_gain;
    handles.plot_total_noise_gain.Value = M.inspectUserData.guiData.eval_options.total_noise_gain;
    
    % export options
    handles.save_path = M.inspectUserData.guiData.save_path;
    handles.radio_button_bf1.Value = M.inspectUserData.guiData.export_options.b1;
    handles.radio_button_bf2.Value = M.inspectUserData.guiData.export_options.b2;
    handles.select_all_freq_bins.Value = M.inspectUserData.guiData.export_options.all_freq_bins;
    handles.select_freq_bins.String = M.inspectUserData.guiData.export_options.freq_bins;
    if handles.AW_NUMBEAMS == M.inspectUserData.guiData.AW_NUMBEAMS
        % use values from last session
        handles.select_all_beam_indices.Value = M.inspectUserData.guiData.export_options.all_beam_idx;
        handles.beam_indices.String = M.inspectUserData.guiData.export_options.beam_idx;
        handles.beam_directions.String = M.inspectUserData.guiData.export_options.beam_directions;
    % else --> re-initialize beam indices and directions for exporting (done above)
    end
    
    % mic array and beamformer entries that use eval (structs won't keep same string)
    if M.inspectUserData.guiData.AW_NUMMICS == handles.AW_NUMMICS
        handles.x_coord_1.String = M.inspectUserData.guiData.x_coord_1;
        handles.y_coord_1.String = M.inspectUserData.guiData.y_coord_1;
        handles.x_coord_2.String = M.inspectUserData.guiData.x_coord_2;
        handles.y_coord_2.String = M.inspectUserData.guiData.y_coord_2;
    end
    handles.num_angles.String = M.inspectUserData.guiData.opt_angles_1;
    handles.num_freqs.String = M.inspectUserData.guiData.opt_freqs_1;
    handles.num_angles_2.String = M.inspectUserData.guiData.opt_angles_2;
    handles.num_freqs_2.String = M.inspectUserData.guiData.opt_freqs_2;
    
else
    
    % initialize gui options (Linear, DAS)
    handles.directivity_1 = 1;
    handles.directivity_2 = 1;
    geometry_choice_Callback(hObject, eventdata, handles);
    geometry_choice_2_Callback(hObject, eventdata, handles);
    method_Callback(hObject, eventdata, handles);
    
    handles.save_path = 0;

    % default to no comparison
    handles.compare_checkbox.Value = 0;
    compare_checkbox_Callback(hObject, eventdata, handles)

    % set default directivity (omni)
    handles.directivity_1 = 1;
    handles.directivity_2 = 1;
    
end

% Choose default command line output for beamformer
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% Put the inspector on top of the other windows and position it correctly
position_window(hObject, windowPosition);

% UIWAIT makes sb_beamformer_inspect wait for user response (see UIRESUME)
% uiwait(handles.figure1);



% --- Outputs from this function are returned to the command line.
function varargout = sb_beamformer_inspect_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
% varargout{1} = copy(handles.M);
varargout{1} = handles.M;



% --- Executes on button press in eval_button.
function eval_button_Callback(hObject, eventdata, handles)
% hObject    handle to eval_button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% evaluation parameters
num_eval_angles = 500;
num_eval_freqs = 500;

plt.filter_responses = handles.plot_filter_responses.Value;
plt.frequency_responses = handles.plot_freq_responses.Value;
ANGLE_TAR = str2double(handles.angle_tar.String);
plt.frequency_responses_angles = [ANGLE_TAR, ANGLE_TAR+30, ANGLE_TAR+45, ...
    ANGLE_TAR+90, ANGLE_TAR+180];
plt.heatmap_2d = handles.plot_heatmap_2d.Value;
plt.heatmap_3d = false;
plt.beam_patterns = handles.plot_polar_plots.Value;
plt.snr = handles.plot_snr.Value;
plt.snr_gain = handles.plot_snr_gain.Value;
plt.directivity_idx = handles.plot_directivity_idx.Value;
plt.beamwidth = handles.plot_beamwidth.Value;
plt.uncorrelated_noise_gain = handles.plot_uncorrelated_noise_gain.Value;
plt.ambient_noise_gain = handles.plot_ambient_noise_gain.Value;
plt.total_noise_gain = handles.plot_total_noise_gain.Value;

% compute beamformer #1
handles = compute_weights_1(handles);


if handles.compare_checkbox.Value
    
    % compute beamformer #2
    handles = compute_weights_2(handles);
    
    % evaluate each struct
    evals = cell(1,2);
    evals{1} = evaluate_beamformer( handles.beamformer_post, num_eval_angles, num_eval_freqs, plt, '', 1);
    evals{2} = evaluate_beamformer( handles.beamformer_post_2, num_eval_angles, num_eval_freqs, plt, '', 1);
    
    % visualization
    if isstruct(evals{1}) && isstruct(evals{2})
        BF = { handles.beamformer_post, handles.beamformer_post_2};
        labels = cell(1,2);
        labels{1} = handles.figure_label_1.String;
        labels{2} = handles.figure_label_2.String;

        plt.mic_arrays = handles.plot_mic_arrays.Value;
        compare_evals( BF, evals, labels, plt )
    elseif isstruct(evals{1})
        evaluate_beamformer( handles.beamformer_post, num_eval_angles, num_eval_freqs, plt, handles.figure_label_1.String);
    elseif isstruct(evals{2})
        evaluate_beamformer( handles.beamformer_post_2, num_eval_angles, num_eval_freqs, plt, handles.figure_label_2.String);
    end
    
else
    
    evaluate_beamformer( handles.beamformer_post, num_eval_angles, num_eval_freqs, plt, handles.figure_label_1.String);

end

guidata(hObject, handles);

%----------------------------%


% --- Executes on button press in load_button.
function load_button_Callback(hObject, eventdata, handles)
% hObject    handle to load_button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if handles.save_path
    [filename, pathname] = uigetfile(fullfile(handles.save_path,'*.mat'), 'Select a .mat file with a beamformer struct.');
else
    [filename, pathname] = uigetfile('*.mat', 'Select a .mat file with a beamformer struct.');
end
if isequal(filename,0)
   disp('User selected Cancel')
   return;
else
   disp(['User selected ', fullfile(pathname, filename)])
   handles.save_path = pathname;
   guidata(hObject, handles);
end

bf = load(fullfile(pathname, filename));
beamformer = bf.beamformer;

% load_beamformer_1_struct(beamformer, hObject, eventdata, handles);
% first load corresponding microphone array
handles = load_array_1(beamformer.mic_array, handles);
if handles.same_arrays.Value
    same_arrays_Callback(hObject, eventdata, handles);
end
geometry_choice_Callback(hObject, eventdata, handles)
if handles.same_array_as_2.Value
    same_array_as_2_Callback(hObject, eventdata, handles);
end

% load beamformer
handles = load_beamformer_1_struct(beamformer, handles);
method_Callback(hObject, eventdata, handles);
guidata(hObject, handles);



% --- Executes on button press in save_button.
function save_button_Callback(hObject, eventdata, handles)
% hObject    handle to save_button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if isfield(handles, 'beamformer_post')
    
    beamformer = handles.beamformer_post;
    bf_file_name = [beamformer.mic_array.geometry '_' num2str(beamformer.mic_array.num_mics) ...
        '_' beamformer.method '_target_' num2str(beamformer.angle_tar) '_nfft_' ...
        num2str(beamformer.nfft) '_fs_' num2str(beamformer.mic_array.samp_freq)]; 
    
    if handles.save_path
        file_path = fullfile(handles.save_path, bf_file_name);
    else
        file_path = bf_file_name;
    end
    [FileName,PathName,~] = uiputfile('*.mat','Save beamformer struct',file_path);
    if isequal(FileName,0)
       disp('User selected Cancel')
       return;
    else
       disp(['Struct saved to: ', fullfile(PathName, FileName)])
    end
    handles.save_path = PathName;
    save(fullfile(handles.save_path,FileName), 'beamformer');
    guidata(hObject, handles);
    
else
    
    disp('Must first compute weights by pressing ''Evaluate''!')
    msgbox('Must first compute weights by pressing ''Evaluate''!')
    
end

% --- Executes on button press in plot_filter_responses.
function plot_filter_responses_Callback(hObject, eventdata, handles)
% hObject    handle to plot_filter_responses (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of plot_filter_responses


% --- Executes on button press in plot_freq_responses.
function plot_freq_responses_Callback(hObject, eventdata, handles)
% hObject    handle to plot_freq_responses (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of plot_freq_responses


% --- Executes on button press in plot_heatmap_2d.
function plot_heatmap_2d_Callback(hObject, eventdata, handles)
% hObject    handle to plot_heatmap_2d (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of plot_heatmap_2d


% --- Executes on button press in plot_mic_arrays.
function plot_mic_arrays_Callback(hObject, eventdata, handles)
% hObject    handle to plot_mic_arrays (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of plot_mic_arrays


% --- Executes on button press in plot_polar_plots.
function plot_polar_plots_Callback(hObject, eventdata, handles)
% hObject    handle to plot_polar_plots (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of plot_polar_plots


% --- Executes on button press in plot_snr.
function plot_snr_Callback(hObject, eventdata, handles)
% hObject    handle to plot_snr (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of plot_snr


% --- Executes on button press in plot_snr_gain.
function plot_snr_gain_Callback(hObject, eventdata, handles)
% hObject    handle to plot_snr_gain (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of plot_snr_gain


% --- Executes on button press in plot_directivity_idx.
function plot_directivity_idx_Callback(hObject, eventdata, handles)
% hObject    handle to plot_directivity_idx (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of plot_directivity_idx


% --- Executes on button press in plot_beamwidth.
function plot_beamwidth_Callback(hObject, eventdata, handles)
% hObject    handle to plot_beamwidth (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of plot_beamwidth


% --- Executes on button press in plot_uncorrelated_noise_gain.
function plot_uncorrelated_noise_gain_Callback(hObject, eventdata, handles)
% hObject    handle to plot_uncorrelated_noise_gain (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of plot_uncorrelated_noise_gain


% --- Executes on button press in plot_ambient_noise_gain.
function plot_ambient_noise_gain_Callback(hObject, eventdata, handles)
% hObject    handle to plot_ambient_noise_gain (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of plot_ambient_noise_gain


% --- Executes on button press in plot_total_noise_gain.
function plot_total_noise_gain_Callback(hObject, eventdata, handles)
% hObject    handle to plot_total_noise_gain (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of plot_total_noise_gain


% --- Executes on selection change in method.
function method_Callback(hObject, eventdata, handles)
% hObject    handle to method (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns method contents as cell array
%        contents{get(hObject,'Value')} returns selected item from method

contents = handles.method.String;
METHOD = contents{handles.method.Value};
handles.fft_length.Enable = 'on';

if strcmp( METHOD, 'DAS' )
    handles.angle_tar.Enable = 'on';
    handles.signal_beamwidth.Enable = 'on';
    
    handles.num_angles.Enable = 'off';
    handles.num_freqs.Enable = 'off';
    handles.white_noise_gain.Enable = 'off';
    handles.min_beamwidth.Enable = 'off';
    handles.transition_width.Enable = 'off';
    handles.passband_ripple.Enable = 'off';
    handles.arbitrary_angles_checkbox.Enable = 'off';
    handles.arbitrary_freq_checkbox.Enable = 'off';
elseif strcmp( METHOD, 'MVDR' )
    handles.angle_tar.Enable = 'on';
    handles.signal_beamwidth.Enable = 'on';
    
    handles.num_angles.Enable = 'off';
    handles.num_freqs.Enable = 'off';
    handles.white_noise_gain.Enable = 'off';
    handles.min_beamwidth.Enable = 'off';
    handles.transition_width.Enable = 'off';
    handles.passband_ripple.Enable = 'off';
    handles.arbitrary_angles_checkbox.Enable = 'off';
    handles.arbitrary_freq_checkbox.Enable = 'off';
elseif strcmp( METHOD, 'MAXSNR' )
    handles.angle_tar.Enable = 'on';
    handles.signal_beamwidth.Enable = 'on';
    
    handles.num_angles.Enable = 'on';
    handles.num_freqs.Enable = 'off';
    handles.white_noise_gain.Enable = 'off';
    handles.min_beamwidth.Enable = 'off';
    handles.transition_width.Enable = 'off';
    handles.passband_ripple.Enable = 'off';
    handles.arbitrary_angles_checkbox.Enable = 'on';
    handles.arbitrary_freq_checkbox.Enable = 'off';
elseif strcmp( METHOD, 'CVX' )
    handles.angle_tar.Enable = 'on';
    handles.signal_beamwidth.Enable = 'on';
    
    handles.num_angles.Enable = 'on';
    handles.num_freqs.Enable = 'on';
    handles.white_noise_gain.Enable = 'on';
    handles.min_beamwidth.Enable = 'on';
    handles.arbitrary_angles_checkbox.Enable = 'on';
    handles.arbitrary_freq_checkbox.Enable = 'on';
    min_beamwidth_Callback(hObject, eventdata, handles);
elseif strcmp(METHOD, 'Import')
    handles.angle_tar.Enable = 'off';
    handles.signal_beamwidth.Enable = 'off';
    handles.fft_length.Enable = 'off';
    
    handles.num_angles.Enable = 'off';
    handles.num_freqs.Enable = 'off';
    handles.white_noise_gain.Enable = 'off';
    handles.min_beamwidth.Enable = 'off';
    handles.arbitrary_angles_checkbox.Enable = 'off';
    handles.arbitrary_freq_checkbox.Enable = 'off';
    handles.passband_ripple.Enable = 'off';
    
    if handles.save_path
        [filename, pathname] = uigetfile(fullfile(handles.save_path,'*.csv'), 'Select CSV file with weights.');
    else
        [filename, pathname] = uigetfile('*.csv', 'Select CSV file with weights.');
    end
    if isequal(filename,0)
        disp('User selected Cancel. Switching to DAS.')
        handles.method.Value = 1;
        method_Callback(hObject, eventdata, handles);
        return;
    else
        handles.save_path = pathname;
        guidata(hObject, handles);
        file_location = fullfile(pathname,filename);
        disp(['User selected ', file_location])
    end
    handles.imported_weights_1 = csvread(file_location);
    disp('Weights matrix should be of size: [nbins x num mics]')
    [nbins,num_mics] = size(handles.imported_weights_1);
    handles.fft_length.String = (nbins-1)*2;
    
    if num_mics ~= str2double(handles.num_mics.String)
        error('Invalid number of microphones!')
    end
    handles.include_center.Enable = 'off';
end

% geometry_choice_Callback(hObject, eventdata, handles)

if handles.copy_beamformer_1.Value && ~strcmp(METHOD, 'Import')
    handles.method_choice_2.Value = handles.method.Value;
end

arbitrary_angles_checkbox_Callback(hObject, eventdata, handles);
arbitrary_freq_checkbox_Callback(hObject, eventdata, handles);

guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function method_CreateFcn(hObject, eventdata, handles)
% hObject    handle to method (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function angle_tar_Callback(hObject, eventdata, handles)
% hObject    handle to angle_tar (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of angle_tar as text
%        str2double(get(hObject,'String')) returns contents of angle_tar as a double


if handles.copy_beamformer_1.Value
    handles.angle_tar_2.String = handles.angle_tar.String;
end

% --- Executes during object creation, after setting all properties.
function angle_tar_CreateFcn(hObject, eventdata, handles)
% hObject    handle to angle_tar (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function signal_beamwidth_Callback(hObject, eventdata, handles)
% hObject    handle to signal_beamwidth (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of signal_beamwidth as text
%        str2double(get(hObject,'String')) returns contents of signal_beamwidth as a double

if handles.copy_beamformer_1.Value
    handles.signal_beamwidth_2.String = handles.signal_beamwidth.String;
end


% --- Executes during object creation, after setting all properties.
function signal_beamwidth_CreateFcn(hObject, eventdata, handles)
% hObject    handle to signal_beamwidth (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function fft_length_Callback(hObject, eventdata, handles)
% hObject    handle to fft_length (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of fft_length as text
%        str2double(get(hObject,'String')) returns contents of fft_length as a double

if handles.copy_beamformer_1.Value
    handles.fft_length_2.String = handles.fft_length.String;
end


% --- Executes during object creation, after setting all properties.
function fft_length_CreateFcn(hObject, eventdata, handles)
% hObject    handle to fft_length (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function num_angles_Callback(hObject, eventdata, handles)
% hObject    handle to num_angles (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of num_angles as text
%        str2double(get(hObject,'String')) returns contents of num_angles as a double

if handles.copy_beamformer_1.Value
    handles.num_angles_2.String = handles.num_angles.String;
end


% --- Executes during object creation, after setting all properties.
function num_angles_CreateFcn(hObject, eventdata, handles)
% hObject    handle to num_angles (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function white_noise_gain_Callback(hObject, eventdata, handles)
% hObject    handle to white_noise_gain (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of white_noise_gain as text
%        str2double(get(hObject,'String')) returns contents of white_noise_gain as a double
         
if handles.copy_beamformer_1.Value
    handles.white_noise_gain_2.String = handles.white_noise_gain.String;
end

% --- Executes during object creation, after setting all properties.
function white_noise_gain_CreateFcn(hObject, eventdata, handles)
% hObject    handle to white_noise_gain (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in min_beamwidth.
function min_beamwidth_Callback(hObject, eventdata, handles)
% hObject    handle to min_beamwidth (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of min_beamwidth

min_beamwidth = handles.min_beamwidth.Value;

if min_beamwidth
    handles.transition_width.Enable = 'on';
    handles.passband_ripple.Enable = 'on';
else
    handles.transition_width.Enable = 'off';
    handles.passband_ripple.Enable = 'off';
end

if handles.copy_beamformer_1.Value
    handles.min_beamwidth_2.Value = handles.min_beamwidth.Value;
end

guidata(hObject, handles);

function transition_width_Callback(hObject, eventdata, handles)
% hObject    handle to transition_width (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of transition_width as text
%        str2double(get(hObject,'String')) returns contents of transition_width as a double

if handles.copy_beamformer_1.Value
    handles.transition_width_2.String = handles.transition_width.String;
end


% --- Executes during object creation, after setting all properties.
function transition_width_CreateFcn(hObject, eventdata, handles)
% hObject    handle to transition_width (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function passband_ripple_Callback(hObject, eventdata, handles)
% hObject    handle to passband_ripple (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of passband_ripple as text
%        str2double(get(hObject,'String')) returns contents of passband_ripple as a double


if handles.copy_beamformer_1.Value
    handles.passband_ripple_2.String = handles.passband_ripple.String;
end

% --- Executes during object creation, after setting all properties.
function passband_ripple_CreateFcn(hObject, eventdata, handles)
% hObject    handle to passband_ripple (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function num_freqs_Callback(hObject, eventdata, handles)
% hObject    handle to num_freqs (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of num_freqs as text
%        str2double(get(hObject,'String')) returns contents of num_freqs as a double

if handles.copy_beamformer_1.Value
    handles.num_freqs_2.String = handles.num_freqs.String;
end


% --- Executes during object creation, after setting all properties.
function num_freqs_CreateFcn(hObject, eventdata, handles)
% hObject    handle to num_freqs (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function speed_sound_Callback(hObject, eventdata, handles)
% hObject    handle to speed_sound (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of speed_sound as text
%        str2double(get(hObject,'String')) returns contents of speed_sound as a double


% --- Executes during object creation, after setting all properties.
function speed_sound_CreateFcn(hObject, eventdata, handles)
% hObject    handle to speed_sound (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function speech_level_Callback(hObject, eventdata, handles)
% hObject    handle to speech_level (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of speech_level as text
%        str2double(get(hObject,'String')) returns contents of speech_level as a double


% --- Executes during object creation, after setting all properties.
function speech_level_CreateFcn(hObject, eventdata, handles)
% hObject    handle to speech_level (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function diffuse_noise_level_Callback(hObject, eventdata, handles)
% hObject    handle to diffuse_noise_level (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of diffuse_noise_level as text
%        str2double(get(hObject,'String')) returns contents of diffuse_noise_level as a double


% --- Executes during object creation, after setting all properties.
function diffuse_noise_level_CreateFcn(hObject, eventdata, handles)
% hObject    handle to diffuse_noise_level (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function num_mics_Callback(hObject, eventdata, handles)
% hObject    handle to num_mics (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of num_mics as text
%        str2double(get(hObject,'String')) returns contents of num_mics as a double


set_order_Callback(hObject, eventdata, handles);

if ~strcmp( handles.geometry_choice.String{handles.geometry_choice.Value}, 'Custom' )
    handles = update_mic_positions_1(handles);
end

guidata(hObject, handles);



% --- Executes during object creation, after setting all properties.
function num_mics_CreateFcn(hObject, eventdata, handles)
% hObject    handle to num_mics (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

%% ----------------------- MICROPHONE #1 PANEL ------------------------- ##


% --- Executes on selection change in geometry_choice.
function geometry_choice_Callback(hObject, eventdata, handles)
% hObject    handle to geometry_choice (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns geometry_choice contents as cell array
%        contents{get(hObject,'Value')} returns selected item from geometry_choice

contents = handles.geometry_choice.String;
GEOMETRY = contents{handles.geometry_choice.Value};

handles.num_mics.String = num2str(handles.AW_NUMMICS);

set_order_Callback(hObject, eventdata, handles);


if strcmp( GEOMETRY, 'Linear' )
    handles.include_center.Value = 0;
    handles.include_center.Enable = 'off';
    handles.spacing_value.Enable = 'on';
    handles.spacing_label.String = 'Spacing [mm]';
    handles.x_coord_1.Enable = 'off';
    handles.y_coord_1.Enable = 'off';
elseif strcmp( GEOMETRY, 'Circle' )
    handles.include_center.Enable = 'on';
    if handles.include_center.Value
        handles.num_mics.String = num2str(handles.AW_NUMMICS-1);
    end
    handles.spacing_value.Enable = 'on';
    handles.spacing_label.String = 'Radius [mm]';
    handles.x_coord_1.Enable = 'off';
    handles.y_coord_1.Enable = 'off';
elseif strcmp( GEOMETRY, 'Triangle' )
    if str2double(handles.num_mics.String)==3
        handles.include_center.Enable = 'off';
        handles.include_center.Value = 0;
    elseif str2double(handles.num_mics.String)==4
        handles.include_center.Enable = 'off';
        handles.include_center.Value = 1;
        handles.num_mics.String = num2str(handles.AW_NUMMICS-1);
    end
    handles.spacing_value.Enable = 'on';
    handles.spacing_label.String = 'Side length [mm]';
    handles.x_coord_1.Enable = 'off';
    handles.y_coord_1.Enable = 'off';
elseif strcmp( GEOMETRY, 'Square' )
    if str2double(handles.num_mics.String)==4
        handles.include_center.Enable = 'off';
        handles.include_center.Value = 0;
    elseif str2double(handles.num_mics.String)==5
        handles.include_center.Enable = 'off';
        handles.include_center.Value = 1;
        handles.num_mics.String = num2str(handles.AW_NUMMICS-1);
    end
    handles.spacing_value.Enable = 'on';
    handles.spacing_label.String = 'Side length [mm]';
    handles.x_coord_1.Enable = 'off';
    handles.y_coord_1.Enable = 'off';
elseif strcmp( GEOMETRY, 'Custom' )
    handles.include_center.Value = 0;
    handles.include_center.Enable = 'off';
    handles.spacing_value.Enable = 'off';
    handles.x_coord_1.Enable = 'on';
    handles.y_coord_1.Enable = 'on';
    
end

handles = update_mic_positions_1(handles);

if handles.same_arrays.Value
    handles.geometry_choice_2.Value = handles.geometry_choice.Value;
    geometry_choice_2_Callback(hObject, eventdata, handles);
    same_arrays_Callback(hObject, eventdata, handles);
end

guidata(hObject, handles);

%-------------------------------------

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
    check_valid_ordering(handles.mic_ordering.String, NUM_MICS);
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




% --- Executes on button press in save_array_1.
function save_array_1_Callback(hObject, eventdata, handles)
% hObject    handle to save_array_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

mic_array = save_array_1_struct(handles);

if strcmp(mic_array.geometry, 'Custom')
    mic_array_file_name = [mic_array.geometry '_num_mics_' num2str(mic_array.num_mics)];
else
    mic_array_file_name = [mic_array.geometry '_num_mics_' num2str(mic_array.num_mics) ...
        '_spacing_' num2str(mic_array.spacing)];
end

if handles.save_path
    file_path = fullfile(handles.save_path, mic_array_file_name);
else
    file_path = mic_array_file_name;
end
[FileName,PathName,~] = uiputfile('*.mat','Save microphone array struct',file_path);
if isequal(FileName,0)
   disp('User selected Cancel')
   return;
else
   disp(['Struct saved to: ', fullfile(PathName, FileName)])
end

handles.save_path = PathName;
save(fullfile(handles.save_path,FileName), 'mic_array');
guidata(hObject, handles);



% --- Executes on button press in load_array_1.
function load_array_1_Callback(hObject, eventdata, handles)
% hObject    handle to load_array_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if handles.save_path
    [filename, pathname] = uigetfile(fullfile(handles.save_path,'*.mat'), 'Select a .mat file with a mic array struct.');
else
    [filename, pathname] = uigetfile('*.mat', 'Select a .mat file with a mic array struct.');
end
if isequal(filename,0)
   disp('User selected Cancel')
   return;
else
   disp(['User selected ', fullfile(pathname, filename)])
   handles.save_path = pathname;
   guidata(hObject, handles);
end

ma = load(fullfile(pathname, filename));
mic_array = ma.mic_array;

% check to see if satisfies number of microphones
if size(mic_array.pos,1)~=handles.AW_NUMMICS
    msgbox(sprintf('Number of microphones in imported array (%d) does not match the number of microphones set through Designer (%d)!',...
        size(mic_array.pos,1),handles.AW_NUMMICS))
    error('Number of microphones in imported array (%d) does not match the number of microphones set through Designer (%d)!',...
        size(mic_array.pos,1),handles.AW_NUMMICS)
end

% load array
handles = load_array_1(mic_array, handles);
if handles.same_arrays.Value
    same_arrays_Callback(hObject, eventdata, handles);
end
geometry_choice_Callback(hObject, eventdata, handles)
guidata(hObject, handles);


% --- Executes on button press in include_center.
function include_center_Callback(hObject, eventdata, handles)
% hObject    handle to include_center (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of include_center

if handles.same_arrays.Value
    handles.include_center_2.Value = handles.include_center.Value;
end

set_order_Callback(hObject, eventdata, handles);

geometry_choice_Callback(hObject, eventdata, handles);

if ~strcmp( handles.geometry_choice.String{handles.geometry_choice.Value}, 'Custom' )
    handles = update_mic_positions_1(handles);
end

guidata(hObject, handles);


% --- Executes on button press in same_array_as_2.
function same_array_as_2_Callback(hObject, eventdata, handles)
% hObject    handle to same_array_as_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


if handles.same_array_as_2.Value  % same arrays
    handles.geometry_choice.Value = handles.geometry_choice_2.Value;
    handles.spacing_label.String = handles.spacing_label_2.String;
    handles.spacing_value.String = handles.spacing_value_2.String;
    handles.num_mics.String = handles.num_mics_2.String;
    handles.x_coord_1.String = handles.x_coord_2.String;
    handles.y_coord_1.String = handles.y_coord_2.String;
    handles.rotation.String = handles.rotation_2.String;
    handles.set_order.Value = handles.set_order_2.Value;
    handles.mic_ordering.String = handles.mic_ordering_2.String;
    handles.include_center.Value = handles.include_center_2.Value;
    handles.set_omni_1.Value = handles.set_omni_2.Value;
    state = 'off';
    handles.same_arrays.Enable = state;
    handles.geometry_choice.Enable = state;
    handles.spacing_value.Enable = state;
    handles.x_coord_1.Enable = state;
    handles.y_coord_1.Enable = state;
    handles.rotation.Enable = state;
    handles.set_order.Enable = state;
    handles.mic_ordering.Enable = state;
    handles.directivity_status.String = handles.directivity_status_2.String;
    handles.directivity_1 = handles.directivity_2;
    handles.save_array_1.Enable = state;
    handles.load_array_1.Enable = state;
    handles.include_center.Enable = state;
    handles.set_omni_1.Enable = state;
else
    state = 'on';
    handles.same_arrays.Enable = state;
    handles.geometry_choice.Enable = state;
    handles.spacing_value.Enable = state;
    handles.x_coord_1.Enable = state;
    handles.y_coord_1.Enable = state;
    handles.rotation.Enable = state;
    handles.set_order.Enable = state;
    handles.mic_ordering.Enable = state;
    handles.import_directivities.Enable = state;
    handles.set_omni_1.Enable = state;
    handles.save_array_1.Enable = state;
    handles.load_array_1.Enable = state;
    handles.include_center.Enable = state;
    geometry_choice_Callback(hObject, eventdata, handles)
end


% Update handles structure
guidata(hObject, handles);



function x_coord_1_Callback(hObject, eventdata, handles)
% hObject    handle to x_coord_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of x_coord_1 as text
%        str2double(get(hObject,'String')) returns contents of x_coord_1 as a double

handles.set_order.Value = 0;
handles.mic_ordering.Enable = 'off';

try
    x_coord = eval(handles.x_coord_1.String);
catch err
    rethrow(err)
end

if length(x_coord)~=handles.AW_NUMMICS
    msgbox(sprintf('Number of coordinates must equal %d!', handles.AW_NUMMICS))
    error('Number of coordinates must equal %d!', handles.AW_NUMMICS)
end

if handles.same_arrays.Value
    handles.x_coord_2.String = handles.x_coord_1.String;
end

% --- Executes during object creation, after setting all properties.
function x_coord_1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to x_coord_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function y_coord_1_Callback(hObject, eventdata, handles)
% hObject    handle to y_coord_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of y_coord_1 as text
%        str2double(get(hObject,'String')) returns contents of y_coord_1 as a double

handles.set_order.Value = 0;
handles.mic_ordering.Enable = 'off';

try
    y_coord = eval(handles.y_coord_1.String);
catch err
    rethrow(err)
end

if length(y_coord)~=handles.AW_NUMMICS
    msgbox(sprintf('Number of coordinates must equal %d!', handles.AW_NUMMICS))
    error('Number of coordinates must equal %d!', handles.AW_NUMMICS)
end

if handles.same_arrays.Value
    handles.y_coord_2.String = handles.y_coord_1.String;
end


% --- Executes during object creation, after setting all properties.
function y_coord_1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to y_coord_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


%% ----------------------- MICROPHONE #2 PANEL ------------------------- ##

%  Executes on button press in same_arrays.
function same_arrays_Callback(hObject, eventdata, handles)
% hObject    handle to same_arrays (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of same_arrays

if handles.same_arrays.Value  % same arrays
    handles.geometry_choice_2.Value = handles.geometry_choice.Value;
    handles.spacing_label_2.String = handles.spacing_label.String;
    handles.spacing_value_2.String = handles.spacing_value.String;
    handles.num_mics_2.String = handles.num_mics.String;
    handles.x_coord_2.String = handles.x_coord_1.String;
    handles.y_coord_2.String = handles.y_coord_1.String;
    handles.rotation_2.String = handles.rotation.String;
    handles.set_order_2.Value = handles.set_order.Value;
    handles.mic_ordering_2.String = handles.mic_ordering.String;
    handles.include_center_2.Value = handles.include_center.Value;
    handles.set_omni_2.Value = handles.set_omni_1.Value;
    state = 'off';
    handles.same_array_as_2.Enable = state;
    handles.geometry_choice_2.Enable = state;
    handles.spacing_value_2.Enable = state;
    handles.x_coord_2.Enable = state;
    handles.y_coord_2.Enable = state;
    handles.rotation_2.Enable = state;
    handles.set_order_2.Enable = state;
    handles.mic_ordering_2.Enable = state;
    handles.set_omni_2.Enable = state;
    handles.import_directivities_2.Enable = state;
    handles.directivity_status_2.String = handles.directivity_status.String;
    handles.directivity_2 = handles.directivity_1;
    handles.save_array_2.Enable = state;
    handles.load_array_2.Enable = state;
    handles.include_center_2.Enable = state;
else
    state = 'on';
    handles.same_array_as_2.Enable = state;
    handles.geometry_choice_2.Enable = state;
    handles.spacing_value_2.Enable = state;
    handles.x_coord_2.Enable = state;
    handles.y_coord_2.Enable = state;
    handles.rotation_2.Enable = state;
    handles.set_order_2.Enable = state;
    handles.mic_ordering_2.Enable = state;
    handles.import_directivities_2.Enable = state;
    handles.set_omni_2.Enable = state;
    handles.save_array_2.Enable = state;
    handles.load_array_2.Enable = state;
    handles.include_center_2.Enable = state;
    geometry_choice_2_Callback(hObject, eventdata, handles)
end

% Update handles structure
guidata(hObject, handles);


% --- Executes on button press in compare_checkbox.
function compare_checkbox_Callback(hObject, eventdata, handles)
% hObject    handle to compare_checkbox (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of compare_checkbox

if handles.compare_checkbox.Value
    state = 'on';
    handles.same_array_as_2.Enable = state;
    handles.same_arrays.Enable = state;
    handles.copy_beamformer_1.Enable = state;
    handles.copy_beamformer_2.Enable = state;
    handles.plot_mic_arrays.Enable = state;
    handles.plot_button_2.Enable = state;
    handles.figure_label_2.Enable = state;
    
    handles.save_button_2.Enable = state;
    handles.load_button_2.Enable = state;

    same_array_as_2_Callback(hObject, eventdata, handles);
    same_arrays_Callback(hObject, eventdata, handles);
    copy_beamformer_1_Callback(hObject, eventdata, handles);
    copy_beamformer_2_Callback(hObject, eventdata, handles);
else
    state = 'off';
    handles.same_array_as_2.Enable = state;
    handles.copy_beamformer_2.Enable = state;
    handles.same_arrays.Enable = state;
    
    handles.copy_beamformer_1.Enable = state;
    handles.plot_mic_arrays.Enable = state;
    handles.figure_label_2.Enable = state;
    
    handles.geometry_choice_2.Enable = state;
    handles.include_center_2.Enable = state;
    handles.spacing_value_2.Enable = state;
    handles.x_coord_2.Enable = state;
    handles.y_coord_2.Enable = state;
    handles.rotation_2.Enable = state;
    handles.set_order_2.Enable = state;
    handles.mic_ordering_2.Enable = state;
    handles.set_omni_2.Enable = state;
    handles.import_directivities_2.Enable = state;
    handles.save_array_2.Enable = state;
    handles.load_array_2.Enable = state;
    handles.plot_button_2.Enable = state;
    handles.load_button_2.Enable = state;
    handles.save_button_2.Enable = state;
    handles.method_choice_2.Enable = state;
    handles.angle_tar_2.Enable = state;
    handles.signal_beamwidth_2.Enable = state;
    handles.fft_length_2.Enable = state;
    handles.num_freqs_2.Enable = state;
    handles.arbitrary_angles_checkbox_2.Enable = state;
    handles.arbitrary_freq_checkbox_2.Enable = state;
    handles.num_angles_2.Enable = state;
    handles.min_beamwidth_2.Enable = state;
    handles.white_noise_gain_2.Enable = state;
    handles.min_beamwidth_2.Enable = state;
    handles.transition_width_2.Enable = state;
    handles.passband_ripple_2.Enable = state;
    
    % make sure array #1 is on (would be off if set to be same array as #2)
    state = 'on';
    if handles.same_array_as_2.Value
%         handles.same_array_as_2.Value = 0;
        handles.same_array_as_2.Enable = 'off';
        handles.geometry_choice.Enable = state;
        handles.include_center.Enable = state;
        handles.spacing_value.Enable = state;
        handles.x_coord_1.Enable = state;
        handles.y_coord_1.Enable = state;
        handles.rotation.Enable = state;
        handles.save_array_1.Enable = state;
        handles.load_array_1.Enable = state;
        handles.set_order.Enable = state;
        handles.set_omni_1.Enable = state;
%         geometry_choice_Callback(hObject, eventdata, handles);
    end
        
    % make sure beamformer #1 is on (would be off if set to be same beamformer as #2)
    if handles.copy_beamformer_2.Value
        handles.copy_beamformer_2.Value = 0;
        handles.copy_beamformer_2.Enable = 'off';
        handles.load_button.Enable = state;
        handles.save_button.Enable = state;
        handles.method.Enable = state;
        handles.angle_tar.Enable = state;
        handles.signal_beamwidth.Enable = state;
        handles.fft_length.Enable = state;
        handles.num_freqs.Enable = state;
        handles.num_angles.Enable = state;
        handles.min_beamwidth.Enable = state;
        handles.white_noise_gain.Enable = state;
        handles.min_beamwidth.Enable = state;
        handles.transition_width.Enable = state;
        handles.passband_ripple.Enable = state;
        method_Callback(hObject, eventdata, handles);
    end
    
end

function num_mics_2_Callback(hObject, eventdata, handles)
% hObject    handle to num_mics_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of num_mics_2 as text
%        str2double(get(hObject,'String')) returns contents of num_mics_2 as a double


% --- Executes during object creation, after setting all properties.
function num_mics_2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to num_mics_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in geometry_choice_2.
function geometry_choice_2_Callback(hObject, eventdata, handles)
% hObject    handle to geometry_choice_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns geometry_choice_2 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from geometry_choice_2


contents = handles.geometry_choice_2.String;
GEOMETRY = contents{handles.geometry_choice_2.Value};

handles.num_mics_2.String = num2str(handles.AW_NUMMICS);

set_order_2_Callback(hObject, eventdata, handles);

if strcmp( GEOMETRY, 'Linear' )
    handles.include_center_2.Value = 0;
    handles.include_center_2.Enable = 'off';
    handles.spacing_label_2.String = 'Spacing [mm]';
    handles.x_coord_2.Enable = 'off';
    handles.y_coord_2.Enable = 'off';
    handles.spacing_value_2.Enable = 'on';
elseif strcmp( GEOMETRY, 'Circle' )
    handles.include_center_2.Enable = 'on';
    if handles.include_center_2.Value
        handles.num_mics_2.String = num2str(handles.AW_NUMMICS-1);
    end
    handles.spacing_label_2.String = 'Radius [mm]';
    handles.x_coord_2.Enable = 'off';
    handles.y_coord_2.Enable = 'off';
    handles.spacing_value_2.Enable = 'on';
elseif strcmp( GEOMETRY, 'Triangle' )
    if str2double(handles.num_mics_2.String)==3
        handles.include_center_2.Enable = 'off';
        handles.include_center_2.Value = 0;
    elseif str2double(handles.num_mics_2.String)==4
        handles.include_center_2.Enable = 'off';
        handles.include_center_2.Value = 1;
        handles.num_mics_2.String = num2str(handles.AW_NUMMICS-1);
    end
    handles.spacing_label_2.String = 'Side length [mm]';
    handles.x_coord_2.Enable = 'off';
    handles.y_coord_2.Enable = 'off';
    handles.spacing_value_2.Enable = 'on';
elseif strcmp( GEOMETRY, 'Square' )
    if str2double(handles.num_mics_2.String)==4
        handles.include_center_2.Enable = 'off';
        handles.include_center_2.Value = 0;
    elseif str2double(handles.num_mics_2.String)==5
        handles.include_center_2.Enable = 'off';
        handles.num_mics_2.String = num2str(handles.AW_NUMMICS-1);
        handles.include_center_2.Value = 1;
    end
    handles.spacing_label_2.String = 'Side length [mm]';
    handles.x_coord_2.Enable = 'off';
    handles.y_coord_2.Enable = 'off';
    handles.spacing_value_2.Enable = 'on';
elseif strcmp( GEOMETRY, 'Custom' )
    handles.include_center_2.Value = 0;
    handles.include_center_2.Enable = 'off';
    handles.spacing_value_2.Enable = 'off';
    handles.x_coord_2.Enable = 'on';
    handles.y_coord_2.Enable = 'on';
end

handles = update_mic_positions_2(handles);

if handles.same_array_as_2.Value
    handles.geometry_choice.Value = handles.geometry_choice_2.Value;
    geometry_choice_Callback(hObject, eventdata, handles);
    same_array_as_2_Callback(hObject, eventdata, handles);
end

guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function geometry_choice_2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to geometry_choice_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in include_center_2.
function include_center_2_Callback(hObject, eventdata, handles)
% hObject    handle to include_center_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of include_center_2

if handles.same_array_as_2.Value
    handles.include_center.Value = handles.include_center_2.Value;
end

set_order_2_Callback(hObject, eventdata, handles);
geometry_choice_2_Callback(hObject, eventdata, handles);

if ~strcmp( handles.geometry_choice_2.String{handles.geometry_choice_2.Value}, 'Custom' )
    handles = update_mic_positions_2(handles);
end

guidata(hObject, handles);


function spacing_value_2_Callback(hObject, eventdata, handles)
% hObject    handle to spacing_value_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of spacing_value_2 as text
%        str2double(get(hObject,'String')) returns contents of spacing_value_2 as a double

if handles.same_array_as_2.Value
    handles.spacing_value.String = handles.spacing_value_2.String;
end

if ~strcmp( handles.geometry_choice_2.String{handles.geometry_choice_2.Value}, 'Custom' )
    handles = update_mic_positions_2(handles);
end

guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function spacing_value_2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to spacing_value_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in plot_button_2.
function plot_button_2_Callback(hObject, eventdata, handles)
% hObject    handle to plot_button_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

save_array_2_struct(handles, true);




function rotation_2_Callback(hObject, eventdata, handles)
% hObject    handle to rotation_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of rotation_2 as text
%        str2double(get(hObject,'String')) returns contents of rotation_2 as a double

if handles.same_array_as_2.Value
    handles.rotation.String = handles.rotation_2.String;
end

% --- Executes during object creation, after setting all properties.
function rotation_2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to rotation_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function x_coord_2_Callback(hObject, eventdata, handles)
% hObject    handle to x_coord_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of x_coord_2 as text
%        str2double(get(hObject,'String')) returns contents of x_coord_2 as a double


try
    x_coord = eval(handles.x_coord_2.String);
catch err
    rethrow(err)
end

if length(x_coord)~=handles.AW_NUMMICS
    msgbox(sprintf('Number of coordinates must equal %d!', handles.AW_NUMMICS))
    error('Number of coordinates must equal %d!', handles.AW_NUMMICS)
end

if handles.same_array_as_2.Value
    handles.x_coord_1.String = handles.x_coord_2.String;
end


% --- Executes during object creation, after setting all properties.
function x_coord_2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to x_coord_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function y_coord_2_Callback(hObject, eventdata, handles)
% hObject    handle to y_coord_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of y_coord_2 as text
%        str2double(get(hObject,'String')) returns contents of y_coord_2 as a double

try
    y_coord = eval(handles.y_coord_2.String);
catch err
    rethrow(err)
end

if length(y_coord)~=handles.AW_NUMMICS
    msgbox(sprintf('Number of coordinates must equal %d!', handles.AW_NUMMICS))
    error('Number of coordinates must equal %d!', handles.AW_NUMMICS)
end

if handles.same_array_as_2.Value
    handles.y_coord_1.String = handles.y_coord_2.String;
end


% --- Executes during object creation, after setting all properties.
function y_coord_2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to y_coord_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



% --- Executes on button press in load_array_2.
function load_array_2_Callback(hObject, eventdata, handles)
% hObject    handle to load_array_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if handles.save_path
    [filename, pathname] = uigetfile(fullfile(handles.save_path,'*.mat'), 'Select a .mat file with a mic array struct.');
else
    [filename, pathname] = uigetfile('*.mat', 'Select a .mat file with a mic array struct.');
end
if isequal(filename,0)
   disp('User selected Cancel')
   return;
else
   disp(['User selected ', fullfile(pathname, filename)])
   handles.save_path = pathname;
   guidata(hObject, handles);
end

ma = load(fullfile(pathname, filename));
mic_array = ma.mic_array;

% check to see if satisfies number of microphones
if size(mic_array.pos,1)~=handles.AW_NUMMICS
    msgbox(sprintf('Number of microphones in imported array (%d) does not match the number of microphones set through Designer (%d)!',...
        size(mic_array.pos,1),handles.AW_NUMMICS))
    error('Number of microphones in imported array (%d) does not match the number of microphones set through Designer (%d)!',...
        size(mic_array.pos,1),handles.AW_NUMMICS)
end

% load microphone array
handles = load_array_2(mic_array, handles);
if handles.same_array_as_2.Value
    same_array_as_2_Callback(hObject, eventdata, handles);
end
geometry_choice_2_Callback(hObject, eventdata, handles)
guidata(hObject, handles);


% --- Executes on button press in save_array_2.
function save_array_2_Callback(hObject, eventdata, handles)
% hObject    handle to save_array_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

mic_array = save_array_2_struct(handles);

if strcmp(mic_array.geometry, 'Custom')
    mic_array_file_name = [mic_array.geometry '_num_mics_' num2str(mic_array.num_mics)];
else
    mic_array_file_name = [mic_array.geometry '_num_mics_' num2str(mic_array.num_mics) ...
        '_spacing_' num2str(mic_array.spacing)];
end

if handles.save_path
    file_path = fullfile(handles.save_path, mic_array_file_name);
else
    file_path = mic_array_file_name;
end
[FileName,PathName,~] = uiputfile('*.mat','Save microphone array struct',file_path);
if isequal(FileName,0)
   disp('User selected Cancel')
   return;
else
   disp(['Struct saved to: ', fullfile(PathName, FileName)])
end

handles.save_path = PathName;
save(fullfile(handles.save_path,FileName), 'mic_array');
guidata(hObject, handles);


%% --------------------------------------------------------------------- %%

% --- Executes during object creation, after setting all properties.
function geometry_choice_CreateFcn(hObject, eventdata, handles)
% hObject    handle to geometry_choice (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function sampling_freq_Callback(hObject, eventdata, handles)
% hObject    handle to sampling_freq (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of sampling_freq as text
%        str2double(get(hObject,'String')) returns contents of sampling_freq as a double


% --- Executes during object creation, after setting all properties.
function sampling_freq_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sampling_freq (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function mic_noise_level_Callback(hObject, eventdata, handles)
% hObject    handle to mic_noise_level (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of mic_noise_level as text
%        str2double(get(hObject,'String')) returns contents of mic_noise_level as a double


% --- Executes during object creation, after setting all properties.
function mic_noise_level_CreateFcn(hObject, eventdata, handles)
% hObject    handle to mic_noise_level (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function spacing_value_Callback(hObject, eventdata, handles)
% hObject    handle to spacing_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of spacing_value as text
%        str2double(get(hObject,'String')) returns contents of spacing_value as a double

if handles.same_arrays.Value
    handles.spacing_value_2.String = handles.spacing_value.String;
end

if ~strcmp( handles.geometry_choice.String{handles.geometry_choice.Value}, 'Custom' )
    handles = update_mic_positions_1(handles);
end

guidata(hObject, handles);



% --- Executes during object creation, after setting all properties.
function spacing_value_CreateFcn(hObject, eventdata, handles)
% hObject    handle to spacing_value (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end




% --- Executes on button press in plot_mic_array_button.
function plot_mic_array_button_Callback(hObject, eventdata, handles)
% hObject    handle to plot_mic_array_button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

save_array_1_struct(handles, true);




function rotation_Callback(hObject, eventdata, handles)
% hObject    handle to rotation (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of rotation as text
%        str2double(get(hObject,'String')) returns contents of rotation as a double

if handles.same_arrays.Value
    handles.rotation_2.String = handles.rotation.String;
end

if ~strcmp( handles.geometry_choice.String{handles.geometry_choice.Value}, 'Custom' )
    handles = update_mic_positions_1(handles);
end

guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function rotation_CreateFcn(hObject, eventdata, handles)
% hObject    handle to rotation (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in close_all_button.
function close_all_button_Callback(hObject, eventdata, handles)
% hObject    handle to close_all_button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

set(handles.figure1, 'HandleVisibility', 'off');
close all;
set(handles.figure1, 'HandleVisibility', 'on');


% --- Executes on button press in select_all_button.
function select_all_button_Callback(hObject, eventdata, handles)
% hObject    handle to select_all_button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if strcmp( hObject.String, 'Select all' )
    handles.plot_filter_responses.Value = 1;
    handles.plot_freq_responses.Value = 1;
    handles.plot_heatmap_2d.Value = 1;
    if handles.compare_checkbox.Value
        handles.plot_mic_arrays.Value = 1;
    end
    handles.plot_polar_plots.Value = 1;
    handles.plot_snr.Value = 1;
    handles.plot_snr_gain.Value = 1;
    handles.plot_directivity_idx.Value = 1;
    handles.plot_beamwidth.Value = 1;
    handles.plot_uncorrelated_noise_gain.Value = 1;
    handles.plot_ambient_noise_gain.Value = 1;
    handles.plot_total_noise_gain.Value = 1;
    hObject.String = 'Deselect all';
else
    handles.plot_filter_responses.Value = 0;
    handles.plot_freq_responses.Value = 0;
    handles.plot_heatmap_2d.Value = 0;
    if handles.compare_checkbox.Value
        handles.plot_mic_arrays.Value = 0;
    end
    handles.plot_polar_plots.Value = 0;
    handles.plot_snr.Value = 0;
    handles.plot_snr_gain.Value = 0;
    handles.plot_directivity_idx.Value = 0;
    handles.plot_beamwidth.Value = 0;
    handles.plot_uncorrelated_noise_gain.Value = 0;
    handles.plot_ambient_noise_gain.Value = 0;
    handles.plot_total_noise_gain.Value = 0;
    hObject.String = 'Select all';
end

guidata(hObject, handles);


% --- If Enable == 'on', executes on mouse press in 5 pixel border.
% --- Otherwise, executes on mouse press in 5 pixel border or over text11.
function text11_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to text11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in load_button_2.
function load_button_2_Callback(hObject, eventdata, handles)
% hObject    handle to load_button_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if handles.save_path
    [filename, pathname] = uigetfile(fullfile(handles.save_path,'*.mat'), 'Select a .mat file with a beamformer struct.');
else
    [filename, pathname] = uigetfile('*.mat', 'Select a .mat file with a beamformer struct.');
end
if isequal(filename,0)
   disp('User selected Cancel')
   return;
else
   disp(['User selected ', fullfile(pathname, filename)])
   handles.save_path = pathname;
   guidata(hObject, handles);
end

bf = load(fullfile(pathname, filename));
beamformer = bf.beamformer;

% first load microphone array
handles = load_array_2(beamformer.mic_array, handles);
if handles.same_array_as_2.Value
    same_array_as_2_Callback(hObject, eventdata, handles);
end
geometry_choice_2_Callback(hObject, eventdata, handles);
if handles.same_arrays.Value
    same_arrays_Callback(hObject, eventdata, handles);
end

% then load beamformer
handles = load_beamformer_2_struct(beamformer, handles);
method_choice_2_Callback(hObject, eventdata, handles)
guidata(hObject, handles);


% --- Executes on button press in save_button_2.
function save_button_2_Callback(hObject, eventdata, handles)
% hObject    handle to save_button_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if isfield(handles, 'beamformer_post_2')
    
    beamformer = handles.beamformer_post_2;
    bf_file_name = [beamformer.mic_array.geometry '_' num2str(beamformer.mic_array.num_mics) ...
        '_' beamformer.method '_target_' num2str(beamformer.angle_tar) '_nfft_' ...
        num2str(beamformer.nfft) '_fs_' num2str(beamformer.mic_array.samp_freq)]; 
    
    if handles.save_path
        file_path = fullfile(handles.save_path, bf_file_name);
    else
        file_path = bf_file_name;
    end
    [FileName,PathName,~] = uiputfile('*.mat','Save beamformer struct',file_path);
    if isequal(FileName,0)
        disp('User selected Cancel')
        return;
    else
        disp(['Struct saved to: ', fullfile(PathName, FileName)])
    end
    handles.save_path = PathName;
    save(fullfile(handles.save_path,FileName), 'beamformer');
    guidata(hObject, handles);
    
else
    
    disp('Must first compute weights by pressing ''Evaluate''!')
    msgbox('Must first compute weights by pressing ''Evaluate''!')
    
end


function num_freqs_2_Callback(hObject, eventdata, handles)
% hObject    handle to num_freqs_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of num_freqs_2 as text
%        str2double(get(hObject,'String')) returns contents of num_freqs_2 as a double

if handles.copy_beamformer_2.Value
    handles.num_freqs.String = handles.num_freqs_2.String;
end

% --- Executes during object creation, after setting all properties.
function num_freqs_2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to num_freqs_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function passband_ripple_2_Callback(hObject, eventdata, handles)
% hObject    handle to passband_ripple_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of passband_ripple_2 as text
%        str2double(get(hObject,'String')) returns contents of passband_ripple_2 as a double

if handles.copy_beamformer_2.Value
    handles.passband_ripple.String = handles.passband_ripple_2.String;
end


% --- Executes during object creation, after setting all properties.
function passband_ripple_2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to passband_ripple_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function transition_width_2_Callback(hObject, eventdata, handles)
% hObject    handle to transition_width_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of transition_width_2 as text
%        str2double(get(hObject,'String')) returns contents of transition_width_2 as a double

if handles.copy_beamformer_2.Value
    handles.transition_width.String = handles.transition_width_2.String;
end


% --- Executes during object creation, after setting all properties.
function transition_width_2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to transition_width_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in min_beamwidth_2.
function min_beamwidth_2_Callback(hObject, eventdata, handles)
% hObject    handle to min_beamwidth_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of min_beamwidth_2

min_beamwidth = handles.min_beamwidth_2.Value;

if min_beamwidth
    handles.transition_width_2.Enable = 'on';
    handles.passband_ripple_2.Enable = 'on';
else
    handles.transition_width_2.Enable = 'off';
    handles.passband_ripple_2.Enable = 'off';
end

if handles.copy_beamformer_2.Value
    handles.min_beamwidth.Value = handles.min_beamwidth_2.Value;
end

guidata(hObject, handles);

function white_noise_gain_2_Callback(hObject, eventdata, handles)
% hObject    handle to white_noise_gain_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of white_noise_gain_2 as text
%        str2double(get(hObject,'String')) returns contents of white_noise_gain_2 as a double

if handles.copy_beamformer_2.Value
    handles.white_noise_gain.String = handles.white_noise_gain_2.String;
end


% --- Executes during object creation, after setting all properties.
function white_noise_gain_2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to white_noise_gain_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function num_angles_2_Callback(hObject, eventdata, handles)
% hObject    handle to num_angles_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of num_angles_2 as text
%        str2double(get(hObject,'String')) returns contents of num_angles_2 as a double

if handles.copy_beamformer_2.Value
    handles.num_angles.String = handles.num_angles_2.String;
end


% --- Executes during object creation, after setting all properties.
function num_angles_2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to num_angles_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function fft_length_2_Callback(hObject, eventdata, handles)
% hObject    handle to fft_length_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of fft_length_2 as text
%        str2double(get(hObject,'String')) returns contents of fft_length_2 as a double

if handles.copy_beamformer_2.Value
    handles.fft_length.String = handles.fft_length_2.String;
end


% --- Executes during object creation, after setting all properties.
function fft_length_2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to fft_length_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function signal_beamwidth_2_Callback(hObject, eventdata, handles)
% hObject    handle to signal_beamwidth_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of signal_beamwidth_2 as text
%        str2double(get(hObject,'String')) returns contents of signal_beamwidth_2 as a double

if handles.copy_beamformer_2.Value
    handles.signal_beamwidth.String = handles.signal_beamwidth_2.String;
end


% --- Executes during object creation, after setting all properties.
function signal_beamwidth_2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to signal_beamwidth_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function angle_tar_2_Callback(hObject, eventdata, handles)
% hObject    handle to angle_tar_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of angle_tar_2 as text
%        str2double(get(hObject,'String')) returns contents of angle_tar_2 as a double

if handles.copy_beamformer_2.Value
    handles.angle_tar.String = handles.angle_tar_2.String;
end

% --- Executes during object creation, after setting all properties.
function angle_tar_2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to angle_tar_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in method_choice_2.
function method_choice_2_Callback(hObject, eventdata, handles)
% hObject    handle to method_choice_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns method_choice_2 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from method_choice_2

contents = handles.method_choice_2.String;
METHOD = contents{handles.method_choice_2.Value};

if strcmp( METHOD, 'DAS' )
    handles.num_angles_2.Enable = 'off';
    handles.num_freqs_2.Enable = 'off';
    handles.white_noise_gain_2.Enable = 'off';
    handles.min_beamwidth_2.Enable = 'off';
    handles.transition_width_2.Enable = 'off';
    handles.passband_ripple_2.Enable = 'off';
    handles.arbitrary_angles_checkbox_2.Enable = 'off';
    handles.arbitrary_freq_checkbox_2.Enable = 'off';
elseif strcmp( METHOD, 'MVDR' )
    handles.num_angles_2.Enable = 'off';
    handles.num_freqs_2.Enable = 'off';
    handles.white_noise_gain_2.Enable = 'off';
    handles.min_beamwidth_2.Enable = 'off';
    handles.transition_width_2.Enable = 'off';
    handles.passband_ripple_2.Enable = 'off';
    handles.arbitrary_angles_checkbox_2.Enable = 'off';
    handles.arbitrary_freq_checkbox_2.Enable = 'off';
elseif strcmp( METHOD, 'MAXSNR' )
    handles.num_angles_2.Enable = 'on';
    handles.num_freqs_2.Enable = 'off';
    handles.white_noise_gain_2.Enable = 'off';
    handles.min_beamwidth_2.Enable = 'off';
    handles.transition_width_2.Enable = 'off';
    handles.passband_ripple_2.Enable = 'off';
    handles.arbitrary_angles_checkbox_2.Enable = 'on';
%     handles.arbitrary_angles_checkbox_2.Value = 0;
    handles.arbitrary_freq_checkbox_2.Enable = 'off';
elseif strcmp( METHOD, 'CVX' )
    handles.num_angles_2.Enable = 'on';
    handles.num_freqs_2.Enable = 'on';
    handles.white_noise_gain_2.Enable = 'on';
    handles.min_beamwidth_2.Enable = 'on';
    handles.arbitrary_angles_checkbox_2.Enable = 'on';
    handles.arbitrary_freq_checkbox_2.Enable = 'on';
    min_beamwidth_2_Callback(hObject, eventdata, handles);
elseif strcmp(METHOD, 'Import')
    handles.angle_tar_2.Enable = 'off';
    handles.signal_beamwidth_2.Enable = 'off';
    handles.fft_length_2.Enable = 'off';
    
    handles.num_angles_2.Enable = 'off';
    handles.num_freqs_2.Enable = 'off';
    handles.white_noise_gain_2.Enable = 'off';
    handles.min_beamwidth_2.Enable = 'off';
    handles.arbitrary_angles_checkbox_2.Enable = 'off';
    handles.arbitrary_freq_checkbox_2.Enable = 'off';
    handles.passband_ripple_2.Enable = 'off';
    
    if handles.save_path
        [filename, pathname] = uigetfile(fullfile(handles.save_path,'*.csv'), 'Select CSV file with weights.');
    else
        [filename, pathname] = uigetfile('*.csv', 'Select CSV file with weights.');
    end
    
    if isequal(filename,0)
        disp('User selected Cancel. Switching to DAS.')
        handles.method_choice_2.Value = 1;
        method_choice_2_Callback(hObject, eventdata, handles);
        return;
    else
        handles.save_path = pathname;
        guidata(hObject, handles);
        file_location = fullfile(pathname,filename);
        disp(['User selected ', file_location])
    end
    handles.imported_weights_2 = csvread(file_location);
    disp('Weights matrix should be of size: [nbins x num mics]')
    [nbins,num_mics] = size(handles.imported_weights_2);
    handles.fft_length_2.String = (nbins-1)*2;
    if num_mics ~= str2double(handles.num_mics_2.String)
        error('Invalid number of microphones!')
    end
    handles.include_center_2.Enable = 'off';
end

% geometry_choice_2_Callback(hObject, eventdata, handles)

arbitrary_angles_checkbox_2_Callback(hObject, eventdata, handles);
arbitrary_freq_checkbox_2_Callback(hObject, eventdata, handles);

if handles.copy_beamformer_2.Value
    handles.method.Value = handles.method_choice_2.Value;
end

guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function method_choice_2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to method_choice_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in copy_beamformer_1.
function copy_beamformer_1_Callback(hObject, eventdata, handles)
% hObject    handle to copy_beamformer_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of copy_beamformer_1

if handles.copy_beamformer_1.Value
    state = 'off';
    
    handles.copy_beamformer_2.Enable = state;
    
    handles.method_choice_2.Value = handles.method.Value;
    handles.method_choice_2.Enable = state;
    handles.angle_tar_2.String = handles.angle_tar.String;
    handles.angle_tar_2.Enable = state;
    handles.signal_beamwidth_2.String = handles.signal_beamwidth.String;
    handles.signal_beamwidth_2.Enable = state;
    handles.fft_length_2.String = handles.fft_length.String;
    handles.fft_length_2.Enable = state;
    handles.arbitrary_freq_checkbox_2.Value = handles.arbitrary_freq_checkbox.Value;
    handles.arbitrary_freq_checkbox_2.Enable = state;
    handles.num_freqs_2.String = handles.num_freqs.String;
    handles.num_freqs_2.Enable = state;
    handles.arbitrary_angles_checkbox_2.Value = handles.arbitrary_angles_checkbox.Value;
    handles.arbitrary_angles_checkbox_2.Enable = state;
    handles.num_angles_2.String = handles.num_angles.String;
    handles.num_angles_2.Enable = state;
    handles.white_noise_gain_2.String = handles.white_noise_gain.String;
    handles.white_noise_gain_2.Enable = state;
    handles.min_beamwidth_2.Value = handles.min_beamwidth.Value;
    handles.min_beamwidth_2.Enable = state;
    handles.transition_width_2.String = handles.transition_width.String;
    handles.transition_width_2.Enable = state;
    handles.passband_ripple_2.String = handles.passband_ripple.String;
    handles.passband_ripple_2.Enable = state;
    
    contents = handles.method.String;
    METHOD = contents{handles.method.Value};
    if strcmp( METHOD, 'Import' )
        handles.imported_weights_2 = handles.imported_weights_1;
    end

    
else
    state = 'on';
    
    handles.copy_beamformer_2.Enable = state;
    
    handles.method_choice_2.Enable = state;
    handles.angle_tar_2.Enable = state;
    handles.signal_beamwidth_2.Enable = state;
    handles.fft_length_2.Enable = state;
    handles.num_freqs_2.Enable = state;
    handles.arbitrary_freq_checkbox_2.Enable = state;
    handles.num_angles_2.Enable = state;
    handles.arbitrary_angles_checkbox_2.Enable = state;
    handles.white_noise_gain_2.Enable = state;
    handles.min_beamwidth_2.Enable = state;
    handles.transition_width_2.Enable = state;
    handles.passband_ripple_2.Enable = state;
    
    method_choice_2_Callback(hObject, eventdata, handles);
end


% --- Executes on button press in copy_beamformer_2.
function copy_beamformer_2_Callback(hObject, eventdata, handles)
% hObject    handle to copy_beamformer_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of copy_beamformer_2

if handles.copy_beamformer_2.Value
    state = 'off';
    
    handles.copy_beamformer_1.Enable = state;
    
    handles.method.Value = handles.method_choice_2.Value;
    handles.method.Enable = state;
    handles.angle_tar.String = handles.angle_tar_2.String;
    handles.angle_tar.Enable = state;
    handles.signal_beamwidth.String = handles.signal_beamwidth_2.String;
    handles.signal_beamwidth.Enable = state;
    handles.fft_length.String = handles.fft_length_2.String;
    handles.fft_length.Enable = state;
    handles.arbitrary_freq_checkbox.Value = handles.arbitrary_freq_checkbox_2.Value;
    handles.arbitrary_freq_checkbox.Enable = state;
    handles.num_freqs.String = handles.num_freqs_2.String;
    handles.num_freqs.Enable = state;
    handles.arbitrary_angles_checkbox.Value = handles.arbitrary_angles_checkbox_2.Value;
    handles.arbitrary_angles_checkbox.Enable = state;
    handles.num_angles.String = handles.num_angles_2.String;
    handles.num_angles.Enable = state;
    handles.white_noise_gain.String = handles.white_noise_gain_2.String;
    handles.white_noise_gain.Enable = state;
    handles.min_beamwidth.Value = handles.min_beamwidth_2.Value;
    handles.min_beamwidth.Enable = state;
    handles.transition_width.String = handles.transition_width_2.String;
    handles.transition_width.Enable = state;
    handles.passband_ripple.String = handles.passband_ripple_2.String;
    handles.passband_ripple.Enable = state;
    
    contents = handles.method.String;
    METHOD = contents{handles.method.Value};
    if strcmp( METHOD, 'Import' )
        handles.imported_weights_1 = handles.imported_weights_2;
    end

    
else
    state = 'on';
    
    handles.copy_beamformer_1.Enable = state;
    
    handles.method.Enable = state;
    handles.angle_tar.Enable = state;
    handles.signal_beamwidth.Enable = state;
    handles.fft_length.Enable = state;
    handles.num_freqs.Enable = state;
    handles.arbitrary_freq_checkbox.Enable = state;
    handles.num_angles.Enable = state;
    handles.arbitrary_angles_checkbox.Enable = state;
    handles.white_noise_gain.Enable = state;
    handles.min_beamwidth.Enable = state;
    handles.transition_width.Enable = state;
    handles.passband_ripple.Enable = state;
    
    method_Callback(hObject, eventdata, handles);
end


% --- Executes on button press in arbitrary_angles_checkbox.
function arbitrary_angles_checkbox_Callback(hObject, eventdata, handles)
% hObject    handle to arbitrary_angles_checkbox (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of arbitrary_angles_checkbox

if handles.arbitrary_angles_checkbox.Value
    handles.opt_angle_label.String = 'Optimization angles';
%     if strcmp(handles.method.String{handles.method.Value}, 'MAXSNR')
%         handles.num_angles.String = '[linspace(0,50,100), linspace(51,310,100), linspace(311,360,100)]';
%     elseif strcmp(handles.method.String{handles.method.Value}, 'CVX')
%         handles.num_angles.String = '[linspace(0,30,30), linspace(31,329,30), linspace(330,360,30)]';
%     end
else
    handles.opt_angle_label.String = 'Num. of optimization angles';
%     if strcmp(handles.method.String{handles.method.Value}, 'MAXSNR')
%         handles.num_angles.String = '360';
%     elseif strcmp(handles.method.String{handles.method.Value}, 'CVX')
%         handles.num_angles.String = '90';
%     end
end

if handles.copy_beamformer_1.Value
    handles.arbitrary_angles_checkbox_2.Value = handles.arbitrary_angles_checkbox.Value;
    handles.num_angles_2.String = handles.num_angles.String;
end


% --- Executes on button press in arbitrary_freq_checkbox.
function arbitrary_freq_checkbox_Callback(hObject, eventdata, handles)
% hObject    handle to arbitrary_freq_checkbox (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of arbitrary_freq_checkbox


if handles.arbitrary_freq_checkbox.Value
    handles.opt_freq_label.String = 'Optimization frequencies';
%     handles.num_freqs.String = '[logspace(log10(100), log10(8000), 100)]';
else
    handles.opt_freq_label.String = 'Num. of optimization freq.';
% 	handles.num_freqs.String = '100';
end

if handles.copy_beamformer_1.Value
    handles.arbitrary_freq_checkbox_2.Value = handles.arbitrary_freq_checkbox.Value;
    handles.num_freqs_2.String = handles.num_freqs.String;
end


% --- Executes on button press in arbitrary_freq_checkbox_2.
function arbitrary_freq_checkbox_2_Callback(hObject, eventdata, handles)
% hObject    handle to arbitrary_freq_checkbox_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of arbitrary_freq_checkbox_2

if handles.arbitrary_freq_checkbox_2.Value
    handles.opt_freq_label_2.String = 'Optimization frequencies';
%     handles.num_freqs_2.String = '[logspace(log10(100), log10(8000), 100)]';
else
    handles.opt_freq_label_2.String = 'Num. of optimization freq.';
% 	handles.num_freqs_2.String = '100';
end

if handles.copy_beamformer_2.Value
    handles.arbitrary_freq_checkbox.Value = handles.arbitrary_freq_checkbox_2.Value;
    handles.num_freqs.String = handles.num_freqs_2.String;
end


% --- Executes on button press in arbitrary_angles_checkbox_2.
function arbitrary_angles_checkbox_2_Callback(hObject, eventdata, handles)
% hObject    handle to arbitrary_angles_checkbox_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of arbitrary_angles_checkbox_2

if handles.arbitrary_angles_checkbox_2.Value
    handles.opt_angle_label_2.String = 'Optimization angles';
%     if strcmp(handles.method_choice_2.String{handles.method_choice_2.Value}, 'MAXSNR')
%         handles.num_angles_2.String = '[linspace(0,50,100), linspace(51,310,100), linspace(311,360,100)]';
%     elseif strcmp(handles.method_choice_2.String{handles.method_choice_2.Value}, 'CVX')
%         handles.num_angles_2.String = '[linspace(0,30,30), linspace(31,329,30), linspace(330,360,30)]';
%     end
else
    handles.opt_angle_label_2.String = 'Num. of optimization angles';
%     if strcmp(handles.method_choice_2.String{handles.method_choice_2.Value}, 'MAXSNR')
%         handles.num_angles_2.String = '360';
%     elseif strcmp(handles.method_choice_2.String{handles.method_choice_2.Value}, 'CVX')
%         handles.num_angles_2.String = '90';
%     end
end

if handles.copy_beamformer_2.Value
    handles.arbitrary_angles_checkbox.Value = handles.arbitrary_angles_checkbox_2.Value;
    handles.num_angles.String = handles.num_angles_2.String;
end



function mic_ordering_2_Callback(hObject, eventdata, handles)
% hObject    handle to mic_ordering_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of mic_ordering_2 as text
%        str2double(get(hObject,'String')) returns contents of mic_ordering_2 as a double

check_valid_ordering(handles.mic_ordering_2.String, handles.AW_NUMMICS);

if handles.same_array_as_2.Value
    handles.mic_ordering.String = handles.mic_ordering_2.String;
end


% --- Executes during object creation, after setting all properties.
function mic_ordering_2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to mic_ordering_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function directivity_status_2_Callback(hObject, eventdata, handles)
% hObject    handle to directivity_status_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of directivity_status_2 as text
%        str2double(get(hObject,'String')) returns contents of directivity_status_2 as a double


% --- Executes during object creation, after setting all properties.
function directivity_status_2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to directivity_status_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in import_directivities_2.
function import_directivities_2_Callback(hObject, eventdata, handles)
% hObject    handle to import_directivities_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if handles.save_path
    [filename, pathname] = uigetfile(fullfile(handles.save_path,'*.mat'), 'Select a .mat file with directivity patterns.');
else
    [filename, pathname] = uigetfile('*.mat', 'Select a .mat file with directivity patterns.');
end
if isequal(filename,0)
   disp('User selected Cancel')
   return;
else
   disp(['User selected ', fullfile(pathname, filename)])
   handles.save_path = pathname;
   guidata(hObject, handles);
end

handles.directivity_status_2.String = filename;
handles.directivity_2 = fullfile(pathname, filename);
handles.set_omni_2.Value = 0;

if handles.same_array_as_2.Value
    handles.set_omni_1.Value = handles.set_omni_2.Value;
    handles.directivity_status.String = filename;
    handles.directivity_1 = fullfile(pathname, filename);
end

% Update handles structure
guidata(hObject, handles);

% --- Executes on button press in set_order_2.
function set_order_2_Callback(hObject, eventdata, handles)
% hObject    handle to set_order_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of set_order_2

if handles.set_order_2.Value
    handles.mic_ordering_2.Enable = 'on';
    
else
    handles.mic_ordering_2.Enable = 'off';
end

if handles.same_array_as_2.Value
    handles.set_order.Value = handles.set_order_2.Value;
    handles.mic_ordering.String = handles.mic_ordering_2.String;
end

% --------------------------------------



function mic_ordering_Callback(hObject, eventdata, handles)
% hObject    handle to mic_ordering (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of mic_ordering as text
%        str2double(get(hObject,'String')) returns contents of mic_ordering as a double


check_valid_ordering(handles.mic_ordering.String, handles.AW_NUMMICS);

if handles.same_arrays.Value
    handles.mic_ordering_2.String = handles.mic_ordering.String;
end


% --- Executes during object creation, after setting all properties.
function mic_ordering_CreateFcn(hObject, eventdata, handles)
% hObject    handle to mic_ordering (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function directivity_status_Callback(hObject, eventdata, handles)
% hObject    handle to directivity_status (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of directivity_status as text
%        str2double(get(hObject,'String')) returns contents of directivity_status as a double


% --- Executes during object creation, after setting all properties.
function directivity_status_CreateFcn(hObject, eventdata, handles)
% hObject    handle to directivity_status (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in import_directivities.
function import_directivities_Callback(hObject, eventdata, handles)
% hObject    handle to import_directivities (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if handles.save_path
    [filename, pathname] = uigetfile(fullfile(handles.save_path,'*.mat'), 'Select a .mat file with directivity patterns.');
else
    [filename, pathname] = uigetfile('*.mat', 'Select a .mat file with directivity patterns.');
end
if isequal(filename,0)
   disp('User selected Cancel')
   return;
else
   disp(['User selected ', fullfile(pathname, filename)])
   handles.save_path = pathname;
   guidata(hObject, handles);
end

handles.directivity_status.String = filename;
handles.directivity_1 = fullfile(pathname, filename);
handles.set_omni_1.Value = 0;

if handles.same_arrays.Value
    handles.set_omni_2.Value = handles.set_omni_1.Value;
    handles.directivity_status_2.String = filename;
    handles.directivity_2 = fullfile(pathname, filename);
end

% Update handles structure
guidata(hObject, handles);


% --- Executes on button press in set_order.
function set_order_Callback(hObject, eventdata, handles)
% hObject    handle to set_order (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of set_order

if handles.set_order.Value
    handles.mic_ordering.Enable = 'on';
    
else
    handles.mic_ordering.Enable = 'off';
end

if handles.same_arrays.Value
    handles.set_order_2.Value = handles.set_order.Value;
    handles.mic_ordering_2.String = handles.mic_ordering.String;
end


% --- Executes on button press in set_omni_2.
function set_omni_2_Callback(hObject, eventdata, handles)
% hObject    handle to set_omni_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of set_omni_2

if handles.set_omni_2.Value
    handles.directivity_status_2.String = 'Omnidirectional';
    handles.directivity_2 = 1;
end

if handles.same_array_as_2.Value
    handles.directivity_1 = handles.directivity_2;
    handles.set_omni_1.Value = handles.set_omni_2.Value;
    handles.directivity_status.String = handles.directivity_status_2.String;
end

% Update handles structure
guidata(hObject, handles);


% --- Executes on button press in set_omni_1.
function set_omni_1_Callback(hObject, eventdata, handles)
% hObject    handle to set_omni_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of set_omni_1

if handles.set_omni_1.Value
    handles.directivity_status.String = 'Omnidirectional';
    handles.directivity_1 = 1;
end

if handles.same_arrays.Value
    handles.directivity_2 = handles.directivity_1;
    handles.set_omni_2.Value = handles.set_omni_1.Value;
    handles.directivity_status_2.String = handles.directivity_status.String;
end

% Update handles structure
guidata(hObject, handles);


% --- Executes on button press in radio_button_bf1.
function radio_button_bf1_Callback(hObject, eventdata, handles)
% hObject    handle to radio_button_bf1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of radio_button_bf1


% --- Executes on button press in radio_button_bf2.
function radio_button_bf2_Callback(hObject, eventdata, handles)
% hObject    handle to radio_button_bf2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of radio_button_bf2


% --- Executes on button press in select_awd_button.
function select_awd_button_Callback(hObject, eventdata, handles)
% hObject    handle to select_awd_button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

[filename, pathname] = uigetfile('*.awd', 'Select an .awd file containing a beamformer.');
if isequal(filename,0)
   disp('User selected Cancel')
   return;
else
   disp(['User selected ', fullfile(pathname, filename)])
end

handles.selected_awd_file.String = filename;
handles.awd_file = fullfile(pathname, filename);

% Update handles structure
guidata(hObject, handles);



function selected_awd_file_Callback(hObject, eventdata, handles)
% hObject    handle to selected_awd_file (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of selected_awd_file as text
%        str2double(get(hObject,'String')) returns contents of selected_awd_file as a double


% --- Executes during object creation, after setting all properties.
function selected_awd_file_CreateFcn(hObject, eventdata, handles)
% hObject    handle to selected_awd_file (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function source_module_name_Callback(hObject, eventdata, handles)
% hObject    handle to source_module_name (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of source_module_name as text
%        str2double(get(hObject,'String')) returns contents of source_module_name as a double


% --- Executes during object creation, after setting all properties.
function source_module_name_CreateFcn(hObject, eventdata, handles)
% hObject    handle to source_module_name (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in export_button.
function export_button_Callback(hObject, eventdata, handles)
% hObject    handle to export_button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

[freq_bins, beam_indices, beam_directions] = check_export_values(handles);

% loading bar
h = waitbar(0,sprintf('0/%d',length(beam_directions)),'Name','Computing multiple beams...',...
        'CreateCancelBtn','setappdata(gcbf,''canceling'',1)');
setappdata(h,'canceling',0)
handles.disable_weights_progress = true;

% compute weights
handles.export_freq_bins = freq_bins;
guidata(hObject, handles);
weights = containers.Map('KeyType','double','ValueType','any');
if handles.radio_button_bf1.Value
    
    prev_target = handles.angle_tar.String;
    
    for k = 1:length(beam_directions)
        
        % Check for Cancel button press
        if getappdata(h,'canceling')
            delete(h)
            handles.angle_tar.String = prev_target;
            return
        end
        
        fprintf('Computing weights for direction = %d degrees...\n', beam_directions(k))
        handles.angle_tar.String = num2str(beam_directions(k));
        handles = compute_weights_1(handles);
        weights(beam_indices(k)) = handles.beamformer_post.weights;
        
        % update wait bar
        waitbar(k / length(beam_directions),h,sprintf('%d/%d',k,length(beam_directions)))
        
    end
    
    handles.angle_tar.String = prev_target;
    
elseif handles.radio_button_bf2.Value
    
    prev_target = handles.angle_tar_2.String;
    
    for k = 1:length(beam_directions)
        
        % Check for Cancel button press
        if getappdata(h,'canceling')
            delete(h)
            handles.angle_tar_2.String = prev_target;
            return
        end
        
        fprintf('Computing weights for direction = %d degrees...\n', beam_directions(k))
        handles.angle_tar_2.String = num2str(beam_directions(k));
        handles = compute_weights_2(handles);
        weights(beam_indices(k)) = handles.beamformer_post_2.weights;
        
        % update wait bar
        waitbar(k / length(beam_directions),h,sprintf('%d/%d',k,length(beam_directions)))
        
    end
    
    handles.angle_tar_2.String = prev_target;
      
end

delete(h);
handles = rmfield(handles, 'disable_weights_progress');

% check number of bins and number of mics
[num_mics, num_bins] = size(weights(beam_indices(k)));
if num_mics ~= handles.AW_NUMMICS
    msgbox(sprintf('Number of mics must be equal to %d!',handles.AW_NUMMICS))
    error('Number of mics must be equal to %d!',handles.AW_NUMMICS)
end
if num_bins ~= handles.AW_NUMBINS
    msgbox(sprintf('Number of bins must be equal to %d!',handles.AW_NUMBINS))
    error('Number of bins must be equal to %d!',handles.AW_NUMBINS)
end

% Get new M from GSYS because handles.M could be stale
GSYS_idx = handles.GSYS_index;
GSYS = get_gsys(GSYS_idx);
hierName = handles.M.hierarchyName;
M = get_module(GSYS.SYS, hierName);

% write to AudioWeaver array
if handles.select_all_beam_indices.Value
    weights_array = zeros(handles.AW_NUMMICS, handles.AW_NUMBINS*handles.AW_NUMBEAMS);
    for k = 0:(handles.AW_NUMBEAMS-1)
        start_idx = k*handles.AW_NUMBINS + 1;
        end_idx = (k+1)*handles.AW_NUMBINS;
        weights_array(:,start_idx:end_idx) = weights(k);
    end
    M.coeffs = weights_array;
elseif length(beam_indices)==1
    start_idx = beam_indices*handles.AW_NUMBINS + 1;
    end_idx = (beam_indices+1)*handles.AW_NUMBINS;
    M.coeffs(:,start_idx:end_idx) = weights(beam_indices);
else
    weights_array = handles.M.coeffs; 
    for k = 0:(handles.AW_NUMBEAMS-1)
        start_idx = k*handles.AW_NUMBINS + 1;
        end_idx = (k+1)*handles.AW_NUMBINS;
        if isKey(weights,k)
            weights_array(:,start_idx:end_idx) = weights(k);
        end
    end
    M.coeffs = weights_array;
end

% Update the stale M
handles.M = M;
GSYS.SYS.(hierName) = M;
GSYS = mod_to_canvas(GSYS, get_parent_hierarchy_name(hierName), M);

set_gsys(GSYS, GSYS_idx);


% Update handles structure
handles = rmfield(handles,'export_freq_bins');
guidata(hObject, handles);

msgbox('Weights successfully exported!');



% --- Executes on button press in togglebutton1.
function togglebutton1_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of togglebutton1



function figure_label_2_Callback(hObject, eventdata, handles)
% hObject    handle to figure_label_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of figure_label_2 as text
%        str2double(get(hObject,'String')) returns contents of figure_label_2 as a double


% --- Executes during object creation, after setting all properties.
function figure_label_2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to figure_label_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function figure_label_1_Callback(hObject, eventdata, handles)
% hObject    handle to figure_label_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of figure_label_1 as text
%        str2double(get(hObject,'String')) returns contents of figure_label_1 as a double


% --- Executes during object creation, after setting all properties.
function figure_label_1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to figure_label_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in csv_export.
function csv_export_Callback(hObject, eventdata, handles)
% hObject    handle to csv_export (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

[freq_bins, beam_indices, beam_directions] = check_export_values(handles);

% loading bar
h = waitbar(0,sprintf('0/%d',length(beam_directions)),'Name','Computing multiple beams...',...
        'CreateCancelBtn','setappdata(gcbf,''canceling'',1)');
setappdata(h,'canceling',0)
handles.disable_weights_progress = true;


% compute weights
handles.export_freq_bins = freq_bins;
guidata(hObject, handles);
weights = containers.Map('KeyType','double','ValueType','any');
if handles.radio_button_bf1.Value
    
    prev_target = handles.angle_tar.String;
    
    for k = 1:length(beam_directions)
        
        % Check for Cancel button press
        if getappdata(h,'canceling')
            delete(h)
            handles.angle_tar.String = prev_target;
            return
        end
        
        fprintf('Computing weights for direction = %d degrees...\n', beam_directions(k))
        handles.angle_tar.String = num2str(beam_directions(k));
        handles = compute_weights_1(handles);
        weights(beam_indices(k)) = handles.beamformer_post.weights;

        waitbar(k / length(beam_directions),h,sprintf('%d/%d',k,length(beam_directions)))
        
    end
    
    handles.angle_tar.String = prev_target;
    
elseif handles.radio_button_bf2.Value
    
    prev_target = handles.angle_tar_2.String;
    
    for k = 1:length(beam_directions)
        
        % Check for Cancel button press
        if getappdata(h,'canceling')
            delete(h)
            handles.angle_tar_2.String = prev_target;
            return
        end
        
        fprintf('Computing weights for direction = %d degrees...\n', beam_directions(k))
        handles.angle_tar_2.String = num2str(beam_directions(k));
        handles = compute_weights_2(handles);
        weights(beam_indices(k)) = handles.beamformer_post_2.weights;
        
        waitbar(k / length(beam_directions),h,sprintf('%d/%d',k,length(beam_directions)))
        
    end
    
    handles.angle_tar_2.String = prev_target;
      
end

delete(h);
handles = rmfield(handles, 'disable_weights_progress');

% check number of bins and number of mics
[num_mics, num_bins] = size(weights(beam_indices(k)));
if num_mics ~= handles.AW_NUMMICS
    msgbox(sprintf('Number of mics must be equal to %d!',handles.AW_NUMMICS))
    error('Number of mics must be equal to %d!',handles.AW_NUMMICS)
end
if num_bins ~= handles.AW_NUMBINS
    msgbox(sprintf('Number of bins must be equal to %d!',handles.AW_NUMBINS))
    error('Number of bins must be equal to %d!',handles.AW_NUMBINS)
end


% export to CSV
% fill other indices with 0
weights_array = zeros(handles.AW_NUMMICS, handles.AW_NUMBINS*handles.AW_NUMBEAMS);
for k = 0:(handles.AW_NUMBEAMS-1)
    start_idx = k*handles.AW_NUMBINS + 1;
    end_idx = (k+1)*handles.AW_NUMBINS;
    if isKey(weights,k)
        weights_array(:,start_idx:end_idx) = weights(k);
    end
end

if handles.save_path
    file_path = fullfile(handles.save_path, 'weights.csv');
else
    file_path = 'weights.csv';
end
[FileName,PathName,~] = uiputfile('*.csv','Save beamformer weights to CSV',file_path);
if isequal(FileName,0)
   disp('User selected Cancel')
   return;
else
   disp(['Struct saved to: ', fullfile(PathName, FileName)])
end
handles.save_path = PathName;
file_location = fullfile(PathName,FileName);
csvwrite(file_location,weights_array)
msgbox(['Beamformer weights have been saved to: ' file_location])

% Update handles structure
handles = rmfield(handles,'export_freq_bins');
guidata(hObject, handles);




function beam_directions_Callback(hObject, eventdata, handles)
% hObject    handle to beam_directions (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of beam_directions as text
%        str2double(get(hObject,'String')) returns contents of beam_directions as a double


% --- Executes during object creation, after setting all properties.
function beam_directions_CreateFcn(hObject, eventdata, handles)
% hObject    handle to beam_directions (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in multibeam_viz.
function multibeam_viz_Callback(hObject, eventdata, handles)
% hObject    handle to multibeam_viz (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of multibeam_viz


% --- Executes on button press in multi_viz.
function multi_viz_Callback(hObject, eventdata, handles)
% hObject    handle to multi_viz (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

[freq_bins, ~, beam_directions] = check_export_values(handles);

% loading bar
h = waitbar(0,sprintf('0/%d',length(beam_directions)),'Name','Computing multiple beams...',...
        'CreateCancelBtn','setappdata(gcbf,''canceling'',1)');
setappdata(h,'canceling',0)
handles.disable_weights_progress = true;

% compute weights
handles.export_freq_bins = freq_bins;
guidata(hObject, handles);
bfs = cell(length(beam_directions),1);
if handles.radio_button_bf1.Value
    
    prev_target = handles.angle_tar.String;
    
    for k = 1:length(beam_directions)
        
        % Check for Cancel button press
        if getappdata(h,'canceling')
            delete(h)
            handles.angle_tar.String = prev_target;
            return
        end

        fprintf('Computing weights for direction = %d degrees...\n', beam_directions(k))
        handles.angle_tar.String = num2str(beam_directions(k));
        handles = compute_weights_1(handles);
        bfs{k} = handles.beamformer_post;

        waitbar(k / length(beam_directions),h,sprintf('%d/%d',k,length(beam_directions)))
        
    end
    
    handles.angle_tar.String = prev_target;
    
elseif handles.radio_button_bf2.Value
    
    prev_target = handles.angle_tar_2.String;
    
    for k = 1:length(beam_directions)
        
        % Check for Cancel button press
        if getappdata(h,'canceling')
            delete(h)
            handles.angle_tar_2.String = prev_target;
            return
        end
        
        fprintf('Computing weights for direction = %d degrees...\n', beam_directions(k))
        handles.angle_tar_2.String = num2str(beam_directions(k));
        handles = compute_weights_2(handles);
        bfs{k} = handles.beamformer_post_2;

        waitbar(k / length(beam_directions),h,sprintf('%d/%d',k,length(beam_directions)))
        
    end
    
    handles.angle_tar_2.String = prev_target;
      
end

delete(h);
handles = rmfield(handles, 'disable_weights_progress');


% visualize
plt_compare.filter_responses = false;
plt_compare.frequency_responses = false;
ANGLE_TAR = str2double(handles.angle_tar.String);
plt_compare.frequency_responses_angles = [ANGLE_TAR, ANGLE_TAR+30, ANGLE_TAR+45, ...
    ANGLE_TAR+90, ANGLE_TAR+180];
plt_compare.heatmap_2d = false;
plt_compare.heatmap_3d = false;
plt_compare.beam_patterns = handles.plot_polar_plots.Value;
plt_compare.snr = false;
plt_compare.snr_gain = false;
plt_compare.directivity_idx = false;
plt_compare.beamwidth = false;
plt_compare.uncorrelated_noise_gain = false;
plt_compare.ambient_noise_gain = false;
plt_compare.total_noise_gain = false;
plt_compare.mic_arrays = false;

num_eval_angles = 360;
num_eval_freqs = 500;

fft_freqs = (0:(bfs{k}.nfft/2)) * (bfs{k}.mic_array.samp_freq/bfs{k}.nfft);
lower_freq = fft_freqs(min(freq_bins));
upper_freq = fft_freqs(max(freq_bins));
num_eval_freqs = [lower_freq, upper_freq, num_eval_freqs];

evals = cell(1, length(beam_directions));
figure_labels = cell(1, length(beam_directions));
for k = 1:length(beam_directions)
    figure_labels{k} = num2str(beam_directions(k));
    evals{k} = evaluate_beamformer( bfs{k}, num_eval_angles, ...
        num_eval_freqs, plt_compare, figure_labels{k}, 1);
end

compare_evals(bfs, evals, figure_labels, plt_compare);

% Update handles structure
handles = rmfield(handles,'export_freq_bins');
guidata(hObject, handles);


% --- Executes on button press in select_all_beam_indices.
function select_all_beam_indices_Callback(hObject, eventdata, handles)
% hObject    handle to select_all_beam_indices (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of select_all_beam_indices

if handles.select_all_beam_indices.Value
    handles.beam_indices.Enable = 'off';
    
    beam_indices = '[';
    for m = 1:handles.AW_NUMBEAMS
        if m < handles.AW_NUMBEAMS
            beam_indices = [beam_indices num2str(m-1) ','];
        else
            beam_indices = [beam_indices num2str(m-1) ']'];
        end
    end
    handles.beam_indices.String = beam_indices;
    
else
    handles.beam_indices.Enable = 'on';
end



function beam_indices_Callback(hObject, eventdata, handles)
% hObject    handle to beam_indices (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of beam_indices as text
%        str2double(get(hObject,'String')) returns contents of beam_indices as a double


% --- Executes during object creation, after setting all properties.
function beam_indices_CreateFcn(hObject, eventdata, handles)
% hObject    handle to beam_indices (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes when user attempts to close figure1.
function figure1_CloseRequestFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: delete(hObject) closes the figure
%delete(hObject);

% get up-to-date Module struct
GSYS_idx = handles.GSYS_index;
GSYS = get_gsys(GSYS_idx);
hierName = handles.M.hierarchyName;
M = get_module(GSYS.SYS, hierName);

% save all GUI variables
% previous Module arguments
M.inspectUserData.guiData.AW_NUMBEAMS = handles.AW_NUMBEAMS;
M.inspectUserData.guiData.AW_NUMBINS = handles.AW_NUMBINS;
M.inspectUserData.guiData.AW_NUMMICS = handles.AW_NUMMICS;
% eval strings since linspace type commands won't be saved within structs
M.inspectUserData.guiData.x_coord_1 = handles.x_coord_1.String;
M.inspectUserData.guiData.y_coord_1 = handles.y_coord_1.String;
M.inspectUserData.guiData.opt_angles_1 = handles.num_angles.String;
M.inspectUserData.guiData.opt_freqs_1 = handles.num_freqs.String;
M.inspectUserData.guiData.x_coord_2 = handles.x_coord_2.String;
M.inspectUserData.guiData.y_coord_2 = handles.y_coord_2.String;
M.inspectUserData.guiData.opt_angles_2 = handles.num_angles_2.String;
M.inspectUserData.guiData.opt_freqs_2 = handles.num_freqs_2.String;
% compare and copy mic array checkboxes 
M.inspectUserData.guiData.copy_array_2 = handles.same_array_as_2.Value;
M.inspectUserData.guiData.copy_array_1 = handles.same_arrays.Value;
M.inspectUserData.guiData.copy_beamformer_2 = handles.copy_beamformer_2.Value;
M.inspectUserData.guiData.copy_beamformer_1 = handles.copy_beamformer_1.Value;
M.inspectUserData.guiData.compare_button = handles.compare_checkbox.Value;
% beamformers + mic arrays + constants
M.inspectUserData.guiData.beamformer_1_label = handles.figure_label_1.String;
M.inspectUserData.guiData.beamformer_2_label = handles.figure_label_2.String;
mic_array_1 = save_array_1_struct(handles);
mic_array_2 = save_array_2_struct(handles);
M.inspectUserData.guiData.beamformer_1 = prepare_beamformer_1_struct(handles, ...
    mic_array_1);
M.inspectUserData.guiData.beamformer_2 = prepare_beamformer_2_struct(handles, ...
    mic_array_2);
% eval options
M.inspectUserData.guiData.eval_options.arrays = handles.plot_mic_arrays.Value;
M.inspectUserData.guiData.eval_options.filter_responses = handles.plot_filter_responses.Value;
M.inspectUserData.guiData.eval_options.heatmap = handles.plot_heatmap_2d.Value;
M.inspectUserData.guiData.eval_options.polar_plots = handles.plot_polar_plots.Value;
M.inspectUserData.guiData.eval_options.snr = handles.plot_snr.Value;
M.inspectUserData.guiData.eval_options.snr_gain = handles.plot_snr_gain.Value;
M.inspectUserData.guiData.eval_options.directivity_idx = handles.plot_directivity_idx.Value;
M.inspectUserData.guiData.eval_options.beam_width = handles.plot_beamwidth.Value;
M.inspectUserData.guiData.eval_options.uncorrelated_noise_gain = handles.plot_uncorrelated_noise_gain.Value;
M.inspectUserData.guiData.eval_options.ambient_noise_gain = handles.plot_ambient_noise_gain.Value;
M.inspectUserData.guiData.eval_options.total_noise_gain = handles.plot_total_noise_gain.Value;
% export options
M.inspectUserData.guiData.save_path = handles.save_path;
M.inspectUserData.guiData.export_options.b1 = handles.radio_button_bf1.Value;
M.inspectUserData.guiData.export_options.b2 = handles.radio_button_bf2.Value;
M.inspectUserData.guiData.export_options.all_freq_bins = handles.select_all_freq_bins.Value;
M.inspectUserData.guiData.export_options.freq_bins = handles.select_freq_bins.String;
M.inspectUserData.guiData.export_options.all_beam_idx = handles.select_all_beam_indices.Value;
M.inspectUserData.guiData.export_options.beam_idx = handles.beam_indices.String;
M.inspectUserData.guiData.export_options.beam_directions = handles.beam_directions.String;

% save new struct
handles.M = M;
GSYS.SYS.(hierName) = M;
set_gsys(GSYS, GSYS_idx);
guidata(hObject, handles);

% The user tries to close the inspector - need to handle this with an
% event.
% This will call inspector_exit function:
awe_event(['OnInspectorClose,' num2str(M.inspectUserData.designerInstanceID) ',' M.inspectUserData.sInspectorID ]);


[thisDir] = fileparts(mfilename('fullpath'));
addpath(fullfile(thisDir, 'weight_computation'));
addpath(fullfile(thisDir, 'utils'));
addpath(fullfile(thisDir, 'gui_utils'));


function select_freq_bins_Callback(hObject, eventdata, handles)
% hObject    handle to select_freq_bins (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of select_freq_bins as text
%        str2double(get(hObject,'String')) returns contents of select_freq_bins as a double


% --- Executes during object creation, after setting all properties.
function select_freq_bins_CreateFcn(hObject, eventdata, handles)
% hObject    handle to select_freq_bins (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in select_all_freq_bins.
function select_all_freq_bins_Callback(hObject, eventdata, handles)
% hObject    handle to select_all_freq_bins (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of select_all_freq_bins

if handles.select_all_freq_bins.Value
    handles.select_freq_bins.Enable = 'off';
    if handles.radio_button_bf1.Value
        handles.select_freq_bins.String = sprintf('[1:%d]',floor(str2double(handles.fft_length.String)/2+1));
    elseif handles.radio_button_bf2.Value
        handles.select_freq_bins.String = sprintf('[1:%d]',floor(str2double(handles.fft_length.String)/2+1));
    end
else
    handles.select_freq_bins.Enable = 'on';
end
    

function [freq_bins, beam_indices, beam_directions] = check_export_values(handles)
% check if valid values are inputed by user before exporting

try
    freq_bins = sort(eval(handles.select_freq_bins.String));
catch err
    rethrow(err)
end
try
    beam_directions = eval(handles.beam_directions.String);
catch err
    rethrow(err)
end
try
    beam_indices = eval(handles.beam_indices.String);
catch err
    rethrow(err)
end

if handles.radio_button_bf1.Value
    method = handles.method.String{handles.method.Value};
elseif handles.radio_button_bf2.Value
    method = handles.method_choice_2.String{handles.method_choice_2.Value};
end
if strcmp(method,'Import')
    % can only export one direction at a time since we don't have the other
    % parameters for beam-steering
    if length(beam_indices) > 1
        msgbox(sprintf('When exporting weights from the ''Import'' Method, only one beam can be exported at a time as beam-steering is not possible!'))
        error('When exporting weights from the ''Import'' Method, only one beam can be exported at a time as beam-steering is not possible!')
    end
end

if max(abs(round(freq_bins)-freq_bins)) > eps
    msgbox(sprintf('Frequency bins must be integers!'))
    error('Frequency bins must be integers!')
end

if length(unique(freq_bins)) < length(freq_bins)
    fprintf('Dropping duplicate frequency bins!')
    freq_bins = unique(freq_bins);
end

if handles.radio_button_bf1.Value
    nfft = str2double(handles.fft_length.String);
elseif handles.radio_button_bf2.Value
    nfft = str2double(handles.fft_length_2.String);
end

if max(freq_bins) > floor(nfft/2+1)
    msgbox(sprintf('Frequency bin cannot exceed %d due to selected FFT length!',floor(nfft/2+1)))
    error('Frequency bin cannot exceed %d due to selected FFT length!',floor(nfft/2+1))
end

if min(freq_bins) < 1
    msgbox(sprintf('Frequency bins must be larger than 1 due to MATLAB indexing.'))
    error('Frequency bins must be larger than 1 due to MATLAB indexing.')
end

if length(freq_bins) ~= handles.AW_NUMBINS
    msgbox(sprintf('Number of frequency bins must be equal to %d as set through the Module arguments!',handles.AW_NUMBINS))
    error('Number of frequency bins must be equal to %d as set through the Module arguments!',handles.AW_NUMBINS)
end

if max(abs(round(beam_indices)-beam_indices)) > eps
    msgbox(sprintf('Beam indices must be integers!'))
    error('Beam indices must be integers!')
end

if length(beam_indices) > handles.AW_NUMBEAMS
    msgbox(sprintf('Number of beams/directions must be less than or equal to %d!',handles.AW_NUMBEAMS))
    error('Number of beams/directions must be less than or equal to %d!',handles.AW_NUMBEAMS)
end

if max(beam_indices) > handles.AW_NUMBEAMS-1
    msgbox(sprintf('Largest beam index is %d!',handles.AW_NUMBEAMS-1))
    error('Largest beam index is %d!',handles.AW_NUMBEAMS-1)
end

if length(unique(beam_indices)) < length(beam_indices)
    msgbox(sprintf('Cannot map multiple beams to a single index!'))
    error('Cannot map multiple beams to a single index!')
end

if length(beam_indices) ~= length(beam_directions)
    msgbox(sprintf('Number of indices should match number of directions!'))
    error('Number of indices should match number of directions!')
end

