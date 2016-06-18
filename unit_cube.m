function [XYZ,col] = unit_cube( col )




A = [ -1 -1 ];
B = [  1 -1 ];
C = [  1  1 ];
D = [ -1  1 ];

ABCD = [A;B;C;D ];
ONE = ones(4,1);


[ F, C ] = rect3d( [ ABCD -ONE ],col);
[ B, C ] = rect3d( [ ABCD  ONE ],col);

[ L, C ] = rect3d([ -ONE ABCD ],col);
[ R, C ] = rect3d([  ONE ABCD ],col);

[ U, C ] = rect3d([ ABCD(:,1) -ONE ABCD(:,2) ],col);
[ D, C ] = rect3d([ ABCD(:,1) ONE ABCD(:,2)],col);



XYZ = [ F; B; L; R; U; D];
col = [ C; C ;C; C; C; C];

