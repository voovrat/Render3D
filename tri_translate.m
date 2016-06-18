function tri = tri_translate(triangles,shift)

dx = shift(1);
dy = shift(2);
dz = shift(3);

points = tri2points(triangles);

points(:,1) = points(:,1) + dx;
points(:,2) = points(:,2) + dy;
points(:,3) = points(:,3) + dz;

tri = points2tri(points);
