
data_buffer = [0]
time_buffer = [0]


%  doc = labchart.getActiveDocument();
%  doc.registerOnNewSamplesCallback(@labchart.callbacks.newData)
 
    d = labchart.getActiveDocument();
  name = 'Channel 2';
  fs = 100;
  n_seconds_valid = 10;
  s1 = labchart.streaming.streamed_data1(fs,n_seconds_valid,name,...
      'h_axes',gca,'plot_options',{'Color','r'});
  fh = @(varargin)labchart.callbacks.newDataStreamingExample1(d,s1,varargin{:});
  d.registerOnNewSamplesCallback(fh);

 