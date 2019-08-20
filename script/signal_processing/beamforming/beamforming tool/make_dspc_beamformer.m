function [MM, NAME]=make_dspc_beamformer(GENDOC)
% make_mymodules(GENDOC)
% Generates the examples library that utilizes 32-bit floating-point values.
% this includes sources, header files, schema, and overall module
% list.  Arguments:
%    GENDOC - Boolean that specifies whether documentation (in Word)
%             format should be generated.  By default, GENDOC=0.
%
% Note, generating documentation slows down the process significantly.
%
% [MM, NAME]=make_mymodules(GENDOC)
% Optional output arguments return the cell array of modules that was
% used to build the library and the name of the library.  When an 
% output argument is requested, then the function DOES NOT GENERATE
% code.
%
% $Revision: 1.1 $

% ----------------------------------------------------------------------
% Set default input arguments
% ----------------------------------------------------------------------

if (nargin < 1)
    GENDOC=0;
end

% ----------------------------------------------------------------------
% Instantiate each module using default arguments
% ----------------------------------------------------------------------

NAME='DSPCBeamformer';
MM=cell(0,0);
MM{end+1} = sb_beamformer_module('temp');
MM{end+1} = sb_beamformer_v2_module('temp',[], [], [], [], 1);

if (nargout > 0)
    return;
end

% ----------------------------------------------------------------------
% Set the code generation directory relative to the directory in which
% this m-file is stored.
% ----------------------------------------------------------------------

MFILE=mfilename('fullpath');
%MFILE contains the name of the most recently invoked M-file
%with full path
[pathstr, fname]=fileparts(MFILE);
ind = find(pathstr == filesep);
DIR = pathstr(1:ind(end)-1);
add_module_path(DIR);

DOC_DIR = fullfile(DIR, 'Doc');
% ----------------------------------------------------------------------
% Generate the library.
% ----------------------------------------------------------------------

global AWE_INFO;
AWE_INFO.buildControl.combineSourceFiles=0;
AWE_INFO.buildControl.ignoreClassIDs=0;

USESLIB = cell(0, 0);

[DependMM, DependName] = make_standardmodulepack(0);
USESLIB{1}.MM=DependMM;
USESLIB{1}.str=DependName;

[DependMM, DependName] = make_advancedmodulepack(0);
USESLIB{2}.MM=DependMM;
USESLIB{2}.str=DependName;

[DependMM, DependName] = make_deprecatedmodulepack(0);
USESLIB{3}.MM=DependMM;
USESLIB{3}.str=DependName;

%awe_generate_library(MM, DIR, NAME, '', GENDOC);
awe_generate_library(MM, DIR, NAME, USESLIB, 0);

awe_generate_doc(MM, DOC_DIR, fullfile(DOC_DIR, '_DSPC_Beamformer.html'), 'DSPC Beamformer IP');
