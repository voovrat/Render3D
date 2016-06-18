#ifndef read_triangles_h
#define read_triangles_h

#include "R3DTriangle.h"
#include "R3DColor.h"

#include <list>

//  Read triangles from file fname in 12 column format 
//   x1 y1 z1   x2 y2 z2  x3 y3 z3   r g b
//
// NOTE: 
//   You need to define global char error_str somewhere in your code: 
//char error_str_buffer[1024];
//char *error_str = error_str_buffer;


void read_triangles( const char *fname,
                     std::list<R3DTriangle> *triangles, 
                     std::list<R3DColor> *colors 
                    );

#endif

