%******************************************************************************\
%* Technische Universitaet Darmstadt, Institut fuer Nachrichtentechnik
%* Copyright (c) 2004
%*
%* Author:
%*	Volker Fischer
%*
%* Description:
%* 	Hilbert Filter for I / Q input
%*
%******************************************************************************
%*
%* This program is free software;
you can redistribute it and/or modify it under
%* the terms of the GNU General Public License as published by the Free Software
%* Foundation;
either version 2 of the License, or (at your option) any later
%* version.
%*
%* This program is distributed in the hope that it will be useful, but WITHOUT
%* ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS
%* FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
%* details.
%*
%* You should have received a copy of the GNU General Public License along with
%* this program;
if not, write to the Free Software Foundation, Inc.,
%* 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
%*
%******************************************************************************/

function [] = IQInputFilter()
                  PLOT = 1;

% Number of taps (should be odd)
nhil = 101;

% Other filter parameters
filterbw = 18000;
% Filter bandwidth

fs = 48000;
% Constant for all cases

% Generate filter coefficients
b = DesignFilter(filterbw, nhil, fs);

if (PLOT == 1)
    close all;
plot(b);
figure;
freqz(b);
end


% Export coefficiants to file ****************************************
fid = fopen('IQInputFilter.h', 'w');

fprintf(fid, '/* Automatically generated file with MATLAB */\n');
fprintf(fid, '/* File name: "IQInputFilter.m" */\n');
fprintf(fid, '/* Filter taps in time-domain */\n\n');

fprintf(fid, '#ifndef _IQINPUTFILTER_H_\n');
fprintf(fid, '#define _IQINPUTFILTER_H_\n\n');

fprintf(fid, '#define NUM_TAPS_IQ_INPUT_FILT        ');
fprintf(fid, int2str(nhil));
fprintf(fid, '\n');
fprintf(fid, '#define IQ_INP_HIL_FILT_DELAY         ');
fprintf(fid, int2str(floor(nhil / 2)));
fprintf(fid, '\n');
fprintf(fid, '\n\n');

% Write filter taps
fprintf(fid, '/* Low pass prototype for Hilbert-filter */\n');
fprintf(fid, ['static float fHilFiltIQ[NUM_TAPS_IQ_INPUT_FILT] =\n']);
fprintf(fid, '{\n');
fprintf(fid, '	%.20ff,\n', b(1:end - 1));
fprintf(fid, '	%.20ff\n', b(end));
fprintf(fid, '};\n\n');

fprintf(fid, '\n#endif /* _IQINPUTFILTER_H_ */\n');
fclose(fid);
return;


function [b] = DesignFilter(filterbw, nhil, fs)
               % Parks-McClellan optimal equiripple FIR filter design
               trans = (fs / 2 - filterbw) / 2 / (fs / 2);
f = [trans  1 - trans];
a = [1 1];
b = remez(nhil - 1, f, a,'Hilbert');
return;
