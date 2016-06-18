function [tri,col] = tri_sphere(N,color)

dang = pi/N;

tri=zeros(0,9);
col=zeros(0,3);

for theta=dang:dang:pi-2*dang

   for phi = 0:dang:2*pi-dang

       x0 = cos(phi)*sin(theta);
       y0 = sin(phi)*sin(theta);
       z0 = cos(theta);

       x1 = cos(phi+dang)*sin(theta);
       y1 = sin(phi+dang)*sin(theta);
       z1 = z0;

       x2 = cos(phi+dang)*sin(theta+dang);
       y2 = sin(phi+dang)*sin(theta+dang);
       z2 = cos(theta+dang);

       x3 = cos(phi)*sin(theta+dang);
       y3 = sin(phi)*sin(theta+dang);
       z3 = z2;


       [T,C]=rect3d([x0 y0 z0; x1 y1 z1; x2 y2 z2; x3 y3 z3],color);

       tri = [tri; T];
       col = [ col; C];

   end

end

theta = dang;
for phi=0:dang:2*pi-dang
  
       x0 = cos(phi)*sin(theta);
       y0 = sin(phi)*sin(theta);
       z0 = cos(theta);

       x1 = cos(phi+dang)*sin(theta);
       y1 = sin(phi+dang)*sin(theta);
       z1 = z0;

%       x2 = cos(phi+dang)*sin(theta+dang);
%       y2 = sin(phi+dang)*sin(theta+dang);
%       z2 = cos(theta+dang);

        
%       x3 = cos(phi)*sin(theta+dang);
%       y3 = sin(phi)*sin(theta+dang);
%       z3 = z2;
       x2 = 0;
       y2 = 0;
       z2 = 1;

%       [T,C]=rect3d([x0 y0 z0; x1 y1 z1; x2 y2 z2; x3 y3 z3],color);
       T = [ x0 y0 z0 x1 y1 z1 x2 y2 z2];
       C = color;

       tri = [tri; T];
       col = [ col; C];

end


theta = pi-dang;
for phi=0:dang:2*pi-dang
  
       x0 = cos(phi)*sin(theta);
       y0 = sin(phi)*sin(theta);
       z0 = cos(theta);

       x1 = cos(phi+dang)*sin(theta);
       y1 = sin(phi+dang)*sin(theta);
       z1 = z0;

%       x2 = cos(phi+dang)*sin(theta+dang);
%       y2 = sin(phi+dang)*sin(theta+dang);
%       z2 = cos(theta+dang);

        
%       x3 = cos(phi)*sin(theta+dang);
%       y3 = sin(phi)*sin(theta+dang);
%       z3 = z2;
       x2 = 0;
       y2 = 0;
       z2 = -1;

%       [T,C]=rect3d([x0 y0 z0; x1 y1 z1; x2 y2 z2; x3 y3 z3],color);
       T = [ x0 y0 z0 x1 y1 z1 x2 y2 z2];
       C = color;

       tri = [tri; T];
       col = [ col; C];

end

