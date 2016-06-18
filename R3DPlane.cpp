#include "R3DPlane.h"

#include "R3DPoint.h"


R3DPlane::R3DPlane(R3DPoint abc,double d)
{
   m_abc = abc;
   m_d = d;
}

R3DPlane::R3DPlane(R3DPoint A,R3DPoint B,R3DPoint C) // plane trough 3 points
{
     // we need to find the normal vector to the triangle's plane
     // the plane's equation is 
     //       | x -x1  y -y1  z -z1|
     //   det | x2-x1  y2-y1  z2-z1|
     //       | x3-x1  y3-y1  z3-z1|

     // from this we find:   a(x-x1)+b(y-y1)+c(z-z1) = 0, where

     //  a = (y2-y1)*(z3-z1) - (y3-y1)*(z2-z1)
     //  b = -(x2-x1)*(z3-z1) + (x3-x1)*(z2-z1)
     //  c = (x2-x1)*(y3-y1) - (x2-x1)*(y2-y1)

     // d = -ax1 - by1 - cz1

      double x1 = A.x();
      double y1 = A.y();
      double z1 = A.z();

      double x2=  B.x();
      double y2 = B.y();
      double z2 = B.z();

      double x3 = C.x();
      double y3 = C.y();
      double z3 = C.z();

      double a = (y2-y1)*(z3-z1) - (y3-y1)*(z2-z1);
      double b = -(x2-x1)*(z3-z1) + (x3-x1)*(z2-z1);
      double c = (x2-x1)*(y3-y1) - (x3-x1)*(y2-y1);


      m_abc = R3DPoint(a,b,c);

      m_d = -a*x1 - b*y1 - c*z1; 

}

