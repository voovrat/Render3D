#ifndef buildPlanes_h
#define buildPlanes_h

class R3DTriangle;
class R3DPlane;

#include <list>


void buildPlanes(
     std::list<R3DTriangle> *triangles, //in
     std::list<R3DPlane> *planes //out
);
 
#endif
