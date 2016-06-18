

[UC_tri,UC_col] = unit_cube([0.8 1 0]);

UC2 = tri_rotate(UC_tri,[ 0  0  pi/4]);

UC3 = tri_translate(UC2,[3 3 2]);



%//UC_points = tri2points(UC_tri);

%//UC_points(:,3) = UC_points(:,3) +5;
%//UC_points(:,1) = UC_points(:,1) - 4;
%//UC_points(:,2) = UC_points(:,2) - 3;

%//UC2 = points2tri(UC_points);

%UC_all = [UC3 UC_col ];

%save -ascii cube.tri UC_all


[sp_tri,sp_col] = tri_sphere(20,[1 0 0]);

%//SP2 = tri_rotate(sp_tri,[0 pi/2 0]);
SP2 = tri_rotate(sp_tri,[0 0 0]);

SP3 = tri_translate(SP2,[5 -5 4]);



SP_all = [ UC3 UC_col; SP3 sp_col];

save -ascii sp.tri SP_all


%%%%%%%%%%%%%%%%%%%%%% LSD

f=fopen('LSD.tmp');
C=textscan(f,'%s%f%f%f');
fclose(f);

names = C{1};
XYZ = [ C{2} C{3} C{4} ];

XYZ(:,3) = XYZ(:,3) + 10;

N =length(names);

IH = find( strcmp(names,'H'));
IC = find( strcmp(names,'C'));
IN = find( strcmp(names,'N'));
IO = find( strcmp(names,'O'));

Colors = zeros(N,3);

Colors(IH,:) = ones(length(IH),1) * [1 1 1];
Colors(IC,:) = ones(length(IC),1) * [0.5 0.5 0.5];
Colors(IN,:) = ones(length(IN),1) * [0 0 1];
Colors(IO,:) = ones(length(IO),1) * [ 1 0 0];

Radii = zeros(N,1);

Radii(IH) = 0.7;
Radii(IC) = 1;
Radii(IN) = 0.8;
Radii(IO) = 0.9;

%tricol = zeros(0,12);

system('rm -f lsd.tricolor');

[SP0,col] = tri_sphere( 40, [1 1 1]);
Ntri = size(SP0,1);

for i=1:N

fprintf('%f of %f\n',i,N);

%[SP0,col] = tri_sphere( 40, Colors(i,:));
col = ones(Ntri,1) * Colors(i,:);

SP1 = tri_rotate(SP0,[0 0 0]);
SP2 = SP1 * Radii(i);
SP3 = tri_translate(SP2,XYZ(i,:));

SP_all = [SP3 col];

save -ascii tmp.tri SP_all 

system('./illuminate2 tmp.tri test.light >> lsd.tricolor');

end



% ---------

SP_all = zeros(0,12);

for i=1:N

fprintf('%f of %f\n',i,N);

[SP0,col] = tri_sphere( 40, Colors(i,:));
SP1 = tri_rotate(SP0,[0 0 0]);
SP2 = SP1 * Radii(i);
SP3 = tri_translate(SP2,XYZ(i,:));

SP_all = [SP_all; SP3 col];

%save -ascii tmp.tri SP_all 

%system('./illuminate tmp.tri test.light >> lsd.tricolor');

end

save -ascii lsd40.tri SP_all

















