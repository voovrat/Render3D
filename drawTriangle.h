#ifndef drawTriangle_h
#define drawTriangle_h

//#include "R3DLight.h"
class R3DZArrayInterface;
class R3DColor;

//#include <list>

void drawTriangle(  R3DPoint &A,
                    R3DPoint &B,
                    R3DPoint &C,
                    R3DColor &color,
                    double opacity,
            //        std::list<R3DLight> *lights,
                    R3DZArrayInterface *zArray,
		    int Nrecursion= -1 // auxilarly. -1 means "determine number of recursions"
                  );

#endif
