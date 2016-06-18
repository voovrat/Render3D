#ifndef R3DTriangle_h
#define R3DTriangle_h

#include "R3DPoint.h"
#include <iostream>


class R3DZArrayInterface;

class R3DTriangle 
{
public:
  R3DPoint A,B,C;

  R3DTriangle() {}

  R3DTriangle(R3DPoint A,R3DPoint &B,R3DPoint &C)
  {
    this->A = A; 
    this->B = B;
    this->C = C;
  }

  //  checks whether M is inside the triangle
  //  Gives incorrect result if M is not in plane ABC ( check this before! )
  bool isInside(R3DPoint M); 

  //void draw(R3DZArrayInterface *zArray);

};

std::ostream& operator<<(std::ostream &os,R3DTriangle &T)
{
   os<<T.A<<"-"<<T.B<<"-"<<T.C;
}

#endif

