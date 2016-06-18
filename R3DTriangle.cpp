#include "R3DTriangle.h"
#include "R3DPoint.h"

#include "R3DLineSegment.h"

#include "intersect.h"

//  checks whether M is inside the triangle
//  Gives incorrect result if M is not in plane ABC ( check this before! )
bool R3DTriangle::isInside(R3DPoint D)
{      

// if point M is in plane of triangle ABC
// and AM,BM,CM do not cross the sides

R3DPoint X;

R3DPoint M = (A+B+C)/3;

R3DLineSegment DM(D,M);

R3DLineSegment AB(A,B);
R3DLineSegment BC(B,C);
R3DLineSegment AC(A,C);

return !( intersect(DM,AB,&X)  ||
           intersect(DM,AC,&X)  ||
           intersect(DM,BC,&X) 
         );

}


