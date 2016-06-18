#ifndef LineSegment_h
#define LineSegment_h

#include "R3DPoint.h"

#include <iostream>

class R3DLineSegment {

public:
  // LineSegment is defined as   origin + dir * t, where 0<t<1
  //   t = 0 corresponds to the start, t=1 to the end point

     R3DPoint m_origin;
     R3DPoint m_direction; 

     R3DLineSegment(R3DPoint A, R3DPoint B)
     {
         m_origin = A;
         m_direction = B-A;
     }

};

std::ostream& operator<<(std::ostream &os,R3DLineSegment &line)
{
   R3DPoint end = line.m_origin + line.m_direction;
   os<<line.m_origin<<"-"<< end;
}


#endif
