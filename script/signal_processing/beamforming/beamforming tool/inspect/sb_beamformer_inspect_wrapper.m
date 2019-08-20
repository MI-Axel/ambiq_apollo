function M = sb_beamformer_inspect_wrapper(action, M, varargin)
% Custom inspector for routers. This uses Matlab GUIDE to design the inspector 
% M is the router module to display
% action can either be 'new', 'change', 'close'. 'New' means creating a new
% inspector. 'Change' means the inspector updated and the module's
% inspectUserData needs to be updated. 'close' means the inspector is
% closed. 
% If action = 'new', the expected varargin are:
%    - inspectorID - a string of the GUI inspector ID
%    - nGSYSIndex - int that specifies which GUI instance this inspector
%    is for
%    - windowPosition - 2-element float array the position of the inspector window.
%     [xPosition, yPosition]. This will be used only if there was no
%     previous l
%    - windowSize - 2-element float array of the size of the inspector window:
%     [xSize, ySize]. (Default = uses previously stored size)
% If action = 'change', the expected varargin is the property change string
% If action = 'close', there is no other varargin.
% If action = 'updatePosition', 2 varargin is expected - the xPosition and
% yPosition. These are expected to be numbers, not strings
% If action = 'updateSize', 2 varargin is expected - the xSize and
% ySize. These are expected to be numbers, not strings 


if strcmpi(action, 'new')
    sInspectorUniqueID = varargin{1};
    nGSYSIndex = varargin{2};
    windowPosition = varargin{3};
    % Call the GUIDE inspector:
%     gui_handles = sb_beamformer_inspect('new', M, sInspectorUniqueID, nGSYSIndex, windowPosition);
%     M = gui_handles.M;
    
    M = sb_beamformer_inspect('new', M, sInspectorUniqueID, nGSYSIndex, windowPosition);
    
    
elseif any(strcmpi(action, {'change', 'update'}))
    % This should only be called from the property sheet
    % Changing a value from property sheet does not affect the GUI since we
    % refresh the stale M instance when we export.

    
elseif strcmpi(action, 'close')
    M = inspector_exit(M);
elseif strcmpi(action, 'updateposition')
    % Should not happen for this inspector
    %keyboard;
elseif strcmpi(action, 'updatesize')
    % Should not happen for  this inspector
    %keyboard;
else
    disp_console_msg(sprintf('Error: unknown action: %s', action));
end

return;

% Called by awe_event.
function M = inspector_exit(M)

fig = M.inspectUserData.figureHandle;

sInspectorUniqueID = M.inspectUserData.sInspectorID;
nDesignerInstanceID = M.inspectUserData.designerInstanceID;

M.inspectUserData.isInspectorOpen = 0;
M.inspectUserData.figureHandle = [];
M.inspectUserData.position = [];


% Call the close gui inspector function. This function will also remove 
% this inspector from the inspector list.
[success, message] = gui_close_inspector(nDesignerInstanceID, sInspectorUniqueID, fig);
if ~success
    disp_console_msg(message);
end

M.inspectUserData.sInspectorID = '';
M.inspectUserData.designerInstanceID = [];

return;




