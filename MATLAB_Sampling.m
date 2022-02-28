q%This script demonstrates live data streaming from LabChart to MATLAB.

%Instructions:
%1) Open a document in LabChart
%2) Run this script in MATLAB
%3) When LabChart starts sampling, the latest data from channels 1, 3 and 4 are 
%plotted in MATLAB (while sampling).
%4) If you stop sampling and make a selection in LabChart, then MATLAB will plot the
%selection.

global gLCApp;
global gLCDoc;
global gChans; %Array of channel numbers specifying channels to retrieve sampling data from
global gChansData;

%First a reference to a LabChart instance (gLCApp) is obtained, either by attaching to 
%an already running LabChart, or starting LabChart.
try
    gLCApp = actxGetRunningServer('ADIChart.Application');
catch err
    error('Please start LabChart before running this script.');
end
if (isempty(gLCApp.ActiveDocument))
    error('Please open a document in LabChart before running this script.');
end

gLCDoc = gLCApp.ActiveDocument;

gChans = [1 3 4]; % collect sampling data from channels 1, 3 and 4.

RegisterLCEvents(gLCDoc); % hook up the OnSelectionChange event and the sampling events such as OnNewSamples and OnBlockStart.

