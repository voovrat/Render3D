#ifndef calculateLuminance_h
#define calculateLuminance_h

class R3DPoint;
class R3DTriangle;
class R3DPlane;
class R3DLight;

#include <list>

#include "buildPlanes.h"
//void buildPlanes(
//     std::list<R3DTriangle> *triangles, //in
//     std::list<R3DPlane> *planes //out
//);
     

void calculateLuminance
(  std::list<R3DTriangle> *triangles,
   std::list<R3DLight> *lights,
   std::list<R3DPlane> *planes, // planes of triangles. Use buildPlanes before 
   std::list<double> *luminance // out
);

#endif
