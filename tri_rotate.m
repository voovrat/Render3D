function tri_rot = tri_rotate(tri,angles)

phi = angles(1);
theta = angles(2);
psi = angles(3);

A = [ cos(phi) -sin(phi) 0; 
      sin(phi) cos(phi) 0;
      0         0       1];

B = [ cos(theta) 0   sin(theta);
      0          1     0
      -sin(theta) 0   cos(theta) ];

C = [ cos(psi)  -sin(psi) 0;
      sin(psi)   cos(psi) 0;
       0          0       1 ];

R = A*B*C;

points = tri2points(tri);

points_rot = (R * points')';

tri_rot = points2tri(points_rot);
