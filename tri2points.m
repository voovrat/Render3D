function XYZ1 = tri2points(XYZ3)
%
%  XYZ3  - 9 column format
%  XYZ1  - 3 column format

XYZ1 = [ XYZ3(:,[ 1 2 3]); XYZ3(:,[4 5 6]); XYZ3(:,[7 8 9]) ];
