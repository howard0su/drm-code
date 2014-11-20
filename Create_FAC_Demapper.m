%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%                                                                            %
%%  University of Kaiserslautern, Institute of Communications Engineering     %
%%  Copyright (C) 2004 Torsten Schorr                                         %
%%                                                                            %
%%  Author(s)    : Torsten Schorr (schorr@eit.uni-kl.de)                      %
%%  Project start: 06.07.2004                                                 %
%%  Last change  : 06.07.2004                                                 %
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
%%  Create_FAC_Demapper.m                                                     %
%%                                                                            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%  Description:                                                              %
%%  Demapper for the FAC OFDM cells valid for all frames                      %
%%                                                                            %
%%  Usage:                                                                    %
%%  FAC_Demapper =                                                            %
%%           Create_FAC_Demapper(robustness_mode, K_dc)                       %
%%                                                                            %
%%  Invoked by channel_decoding.m                                             %
%%                                                                            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function FAC_Demapper = Create_FAC_Demapper(robustness_mode, K_dc, K_modulo)
%
%   ETSI ES 201980 / 8.5.2.1
%   FAC cells: Cell positions
%


% Tu_list = [288, 256, 176, 112];
% Tu = Tu_list(robustness_mode);

if (robustness_mode == 1)
    FAC_Demapper = K_dc +  [ 2*K_modulo+[26,46,66,86], ...
      		                 3*K_modulo+[10,30,50,70,90], ...
                             4*K_modulo+[14,22,34,62,74,94], ...
                             5*K_modulo+[26,38,58,66,78], ...
                             6*K_modulo+[22,30,42,62,70,82], ...
                             7*K_modulo+[26, 34, 46, 66, 74, 86], ...
                             8*K_modulo+[10, 30, 38, 50, 58, 70, 78, 90], ...
                             9*K_modulo+[14, 22, 34, 42, 62, 74, 82, 94], ...
                             10*K_modulo+[26, 38, 46, 66, 86], ...
                             11*K_modulo+[10, 30, 50, 70, 90], ...
                             12*K_modulo+[14, 34, 74, 94], ...
                             13*K_modulo+[38, 58, 78] ];
     return;
 elseif (robustness_mode == 2)
     FAC_Demapper = K_dc +  [ 2*K_modulo+[13,25,43,55,67], ...
      		                 3*K_modulo+[15,27,45,57,69], ...
                             4*K_modulo+[17,29,47,59,71], ...
                             5*K_modulo+[19,31,49,61,73], ...
                             6*K_modulo+[9,21,33,51,63,75], ...
                             7*K_modulo+[11,23,35,53,65,77], ...
                             8*K_modulo+[13,25,37,55,67,79], ...
                             9*K_modulo+[15,27,39,57,69,81], ...
                             10*K_modulo+[17,29,41,59,71,83], ...
                             11*K_modulo+[19,31,43,61,73], ...
                             12*K_modulo+[21,33,45,63,75], ...
                             13*K_modulo+[23,35,47,65,77] ];
     return;
 elseif (robustness_mode == 3)
      FAC_Demapper = K_dc +  [ 3*K_modulo+[9,21,45,57], ...
                             4*K_modulo+[23,35,47], ...
                             5*K_modulo+[13,25,37,49], ...
                             6*K_modulo+[15,27,39,51], ...
                             7*K_modulo+[5,17,29,41,53], ...
                             8*K_modulo+[7,19,31,43,55], ...
                             9*K_modulo+[9,21,45,57], ...
                             10*K_modulo+[23,35,47], ...
                             11*K_modulo+[13,25,37,49], ...
                             12*K_modulo+[15,27,39,51], ...
                             13*K_modulo+[5,17,29,41,53],...
                             14*K_modulo+[7,19,31,43,55], ...
                             15*K_modulo+[9,21,45,57], ...
                             16*K_modulo+[23,35,47], ...
                             17*K_modulo+[13,25,37,49], ...
                             18*K_modulo+[15,27,39,51]];
     return;
 elseif (robustness_mode == 4)
      FAC_Demapper = K_dc +  [ 3*K_modulo+[9,18,27], ...
                             4*K_modulo+[10,19], ...
                             5*K_modulo+[11,20,29], ...
                             6*K_modulo+[12,30], ...
                             7*K_modulo+[13,22,31], ...
                             8*K_modulo+[5,14,23,32], ...
                             9*K_modulo+[6,15,24,33], ...
                             10*K_modulo+[16,25,34], ...
                             11*K_modulo+[8,17,26,35], ...
                             12*K_modulo+[9,18,27,36], ...
                             13*K_modulo+[10,19,37],...
                             14*K_modulo+[11,20,29], ...
                             15*K_modulo+[12,30], ...
                             16*K_modulo+[13,22,31], ...
                             17*K_modulo+[5,14,23,32], ...
                             18*K_modulo+[6,15,24,33], ...
                             19*K_modulo+[16,25,34], ...
                             20*K_modulo+[8,17,26,35], ...
                             21*K_modulo+[9,18,27,36], ...
                             22*K_modulo+[10,19,37]];
     return;
 else 
     error ('Create_FAC_Demapper is called with invalid robustness_mode');
     return;
 end
 