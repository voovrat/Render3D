function XYZ3 = points2tri(XYZ1)
%
%  XYZ1 - 3 column format ( all A, then all B, then all C)
%  XYZ3 - 9 column format

NNN = length(XYZ1);

N = round(NNN/3);

A = XYZ1(1:N,:);
B = XYZ1(N+1:2*N,:);
C = XYZ1(2*N+1:end,:);

XYZ3 = [ A B C];

