function [ XYZ , C ]= rect3d(ABCD,col)

A = ABCD(1,:);
B = ABCD(2,:);
C = ABCD(3,:);
D = ABCD(4,:);

XYZ = [ A B C; A C D];
C = [col; col];
