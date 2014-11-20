%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%                                                                            %
%%  University of Kaiserslautern, Institute of Communications Engineering     %
%%  Copyright (C) 2005 Torsten Schorr                                         %
%%                                                                            %
%%  Author(s)    : Torsten Schorr (schorr@eit.uni-kl.de)                      %
%%  Project start: 15.04.2005                                                 %
%%  Last change  : 15.04.2005                                                 %
%%                                                                            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%                                                                            %
%%  This program is free software; you can redistribute it and/or modify      %
%%  it under the terms of the GNU General Public License as published by      %
%%  the Free Software Foundation; either version 2 of the License, or         %
%%  (at your option) any later version.                                       %
%%                                                                            %
%%  This program is distributed in the hope that it will be useful,           %
%%  but WITHOUT ANY WARRANTY; without even the implied warranty of            %
%%  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             %
%%  GNU General Public License for more details.                              %
%%                                                                            %
%%  You should have received a copy of the GNU General Public License         %
%%  along with this program; if not, write to the Free Software               %
%%  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA %
%%                                                                            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%                                                                            %
%%  plot_constellations.m                                                     %
%%                                                                            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function result = about( varargin )
% (-1) close figure and reset figure properties, result should be zero
% (0) close figure, result should be zero
% (1) create empty figure without data if not allready open, result==handle to figure
% (2, ...) update/create figure with data in the following arguments, result==handle to figure
%
% (10) put window into foreground
% (11) put window into background
% (12) put minimize figure
% (13, [xpos,ypos,xwidth,ywidth]) == set position of actual window or of position window will have if created
% (14) get position of actual window or last opened window, empty if not available

persistent position_this_figure ...		%position of figure
   hnd_this_figure ...
   is_in_use ...
   ...
   ...	%----------change from here------------------------------
   line_handles;
   settings_number = 24;   
   
    prog_name = 'Diorama';
    sub_title = 'Real-Time DRM Receiver for Matlab';
    authors = 'Andreas Dittrich, Torsten Schorr';
    uni = 'University of Kaiserslautern';
    lehrstuhl = 'Institute of Telecommunications';
    address = 'D-67663 Kaiserslautern, Germany';
    copyright = 'Copyright (C) 2004 - 2005';
    web_site = 'http://nt.eit.uni-kl.de/';
    description = 'Diorama is a complete open-source real-time software Digital Radio Mondiale (DRM) receiver written for Matlab. After plugging a modified short-wave receiver into your soundcard you can receive digital radio and discover how the decoder is working at each time. This program is free according to the GNU General Public License (GPL).';
    title_ack = 'Acknowledgment of used third party tools:';
    matlab_ack = 'MATLAB, (C) 1984 - 2002 The MathWorks, Inc., www.mathworks.com';
    faad_ack = 'FAAD2 AAC/HE-AAC/HE-AACv2/DRM decoder (c) Ahead Software, www.nero.com';
    journaline_ack = 'Features NewsService Journaline(R) decoder technology by Fraunhofer IIS, Erlangen, Germany. For more information visit http://www.iis.fhg.de/dab';
   
   %------------dont change begin ------------
TAG_NAME = mfilename;
FIGURE_PROCEDURE_NAME = mfilename;

result=-1;
%avoid reentrance 
if ( ~isempty(is_in_use) )
   return; %ignore this call
end

if (nargin == 0)
    
    message(authors,sprintf('\n'));
    message(uni,sprintf('\n'));
    message(lehrstuhl,sprintf('\n'));
    message(address,sprintf('\n'));
    message(copyright,sprintf('\n'));
    message(matlab_ack,sprintf('\n'));
    message(faad_ack,sprintf('\n'));
    message(journaline_ack,sprintf('\n'));
    message('flush');
    
    return;
end


is_in_use = varargin{1};

if( isempty(hnd_this_figure) )
   hnd_this_figure = findobj('Tag', TAG_NAME);
end

if( isempty(position_this_figure) )
   myScreenSize = get(0,'ScreenSize');
   position_this_figure = [1+floor(myScreenSize(3)/16)*4, 1+floor(myScreenSize(4)/12)*4, floor(myScreenSize(3)/8)*4, floor(myScreenSize(4)/8)*4];
end



switch varargin{1}
   
case -1,
   if ( ~isempty(hnd_this_figure) )
      delete( hnd_this_figure );
      settings_handler(7,settings_number,0);
      position_this_figure = [];
      hnd_this_figure = [];
   end
   hnd_this_axes = [];
   call_count = 0;
   result = 0;
   
case 0,
   if ( ~isempty(hnd_this_figure) )
      position_this_figure = get( hnd_this_figure, 'Position' );
      delete( hnd_this_figure );
      settings_handler(7,settings_number,0);
      hnd_this_figure = [];
   end
   hnd_this_axes = [];
   call_count = 0;
   result = 0;
   
case 1,
    %do we have a figure to plot?
    if ( isempty(hnd_this_figure) )
        hnd_this_figure = figure('Tag', TAG_NAME, ...
            'Position', position_this_figure, ...
            'CloseRequestFcn', [FIGURE_PROCEDURE_NAME,'(0);'], ...
            'Name', FIGURE_PROCEDURE_NAME, ...
            'MenuBar','none');
        result = hnd_this_figure;
      settings_handler(7,settings_number,1);
        
        h1 = uicontrol('Parent',hnd_this_figure, ...
            'Units','normalized', ...
            'BackgroundColor',[0.8 0.8 0.8], ...
            'FontName','Helvetica', ...
            'FontSize',28, ...
            'HorizontalAlignment','left', ...
            'ListboxTop',0, ...
            'Position',[0.0125 0.87 0.2589285714285714 0.09047619047619047], ...
            'String',prog_name, ...
            'Style','text', ...
            'Tag','StaticText1');
        h1 = uicontrol('Parent',hnd_this_figure, ...
            'Units','normalized', ...
            'BackgroundColor',[0.8 0.8 0.8], ...
            'FontName','Helvetica', ...
            'FontSize',12, ...
            'FontWeight','bold', ...
            'HorizontalAlignment','left', ...
            'ListboxTop',0, ...
            'Position',[0.2928571428571429 0.87 0.74 0.05952380952380953], ...
            'String',sub_title, ...
            'Style','text', ...
            'Tag','StaticText2');
        h1 = uicontrol('Parent',hnd_this_figure, ...
            'Units','normalized', ...
            'BackgroundColor',[0.8 0.8 0.8], ...
            'FontName','Helvetica', ...
            'FontSize',11, ...
            'HorizontalAlignment','left', ...
            'ListboxTop',0, ...
            'Position',[0.02321428571428571 0.77 0.95 0.05], ...
            'String',authors, ...
            'Style','text', ...
            'Tag','StaticText3');
        h1 = uicontrol('Parent',hnd_this_figure, ...
            'Units','normalized', ...
            'BackgroundColor',[0.8 0.8 0.8], ...
            'FontName','Helvetica', ...
            'FontSize',11, ...
            'HorizontalAlignment','left', ...
            'ListboxTop',0, ...
            'Position',[0.02321428571428571 0.72 0.95 0.05], ...
            'String',uni, ...
            'Style','text', ...
            'Tag','StaticText3');
        h1 = uicontrol('Parent',hnd_this_figure, ...
            'Units','normalized', ...
            'BackgroundColor',[0.8 0.8 0.8], ...
            'FontName','Helvetica', ...
            'FontSize',11, ...
            'HorizontalAlignment','left', ...
            'ListboxTop',0, ...
            'Position',[0.02321428571428571 0.67 0.95 0.05], ...
            'String',lehrstuhl, ...
            'Style','text', ...
            'Tag','StaticText3');
        h1 = uicontrol('Parent',hnd_this_figure, ...
            'Units','normalized', ...
            'BackgroundColor',[0.8 0.8 0.8], ...
            'FontName','Helvetica', ...
            'FontSize',11, ...
            'HorizontalAlignment','left', ...
            'ListboxTop',0, ...
            'Position',[0.02321428571428571 0.62 0.95 0.05], ...
            'String',address, ...
            'Style','text', ...
            'Tag','StaticText3');
        h1 = uicontrol('Parent',hnd_this_figure, ...
            'Units','normalized', ...
            'BackgroundColor',[0.8 0.8 0.8], ...
            'FontName','Helvetica', ...
            'FontSize',11, ...
            'HorizontalAlignment','left', ...
            'ListboxTop',0, ...
            'Position',[0.02321428571428571 0.57 0.95 0.05], ...
            'String',copyright, ...
            'Style','text', ...
            'Tag','StaticText3');
        h1 = uicontrol('Parent',hnd_this_figure, ...
            'Units','normalized', ...
            'BackgroundColor',[0.8 0.8 0.8], ...
            'FontName','Helvetica', ...
            'FontSize',11, ...
            'HorizontalAlignment','left', ...
            'ListboxTop',0, ...
            'Position',[0.02321428571428571 0.52 0.95 0.05], ...
            'String',web_site, ...
            'Style','text', ...
            'Tag','StaticText3');    
        h1 = uicontrol('Parent',hnd_this_figure, ...
            'Units','normalized', ...
            'BackgroundColor',[0.8 0.8 0.8], ...
            'FontName','Helvetica', ...
            'FontSize',10, ...
            'HorizontalAlignment','left', ...
            'ListboxTop',0, ...
            'Position',[0.02321428571428571 0.3 0.9339285714285712 0.1880952380952381], ...
            'String',description, ...
            'Style','text', ...
            'Tag','StaticText3');
        h1 = uicontrol('Parent',hnd_this_figure, ...
            'Units','normalized', ...
            'BackgroundColor',[0.8 0.8 0.8], ...
            'FontName','Helvetica', ...
            'FontSize',10, ...
            'FontWeight','bold', ...
            'HorizontalAlignment','left', ...
            'ListboxTop',0, ...
            'Position',[0.02321428571428571 0.25 0.95 0.04761904761904762], ...
            'String',title_ack, ...
            'Style','text', ...
            'Tag','StaticText3');
        h1 = uicontrol('Parent',hnd_this_figure, ...
            'Units','normalized', ...
            'BackgroundColor',[0.8 0.8 0.8], ...
            'FontName','Helvetica', ...
            'FontSize',10, ...
            'HorizontalAlignment','left', ...
            'ListboxTop',0, ...
            'Position',[0.02321428571428571 0.19 0.95 0.05], ...
            'String',matlab_ack, ...
            'Style','text', ...
            'Tag','StaticText3');
        h1 = uicontrol('Parent',hnd_this_figure, ...
            'Units','normalized', ...
            'BackgroundColor',[0.8 0.8 0.8], ...
            'FontName','Helvetica', ...
            'FontSize',10, ...
            'HorizontalAlignment','left', ...
            'ListboxTop',0, ...
            'Position',[0.02321428571428571 0.14 0.95 0.05], ...
            'String',faad_ack, ...
            'Style','text', ...
            'Tag','StaticText3');
        h1 = uicontrol('Parent',hnd_this_figure, ...
            'Units','normalized', ...
            'BackgroundColor',[0.8 0.8 0.8], ...
            'FontName','Helvetica', ...
            'FontSize',10, ...
            'HorizontalAlignment','left', ...
            'ListboxTop',0, ...
            'Position',[0.02321428571428571 0.04 0.95 0.1], ...
            'String',journaline_ack, ...
            'Style','text', ...
            'Tag','StaticText3');
    
    end
      
end

is_in_use = [];
