#ifndef intersect_h
#define intersect_h

// Define different intersections of planes, lines, triangles etc...

class R3DPoint;
class R3DPlane;
class R3DLineSegment;

bool intersect(  R3DLineSegment &line, 
                 R3DPlane &plane, 
                 R3DPoint *intersection_point // out
//                 double *t   // parameter t at intersection (out)
               );

bool intersect( R3DLineSegment &line1,
                R3DLineSegment &line2,
                R3DPoint *intersection_point );


#endif 
