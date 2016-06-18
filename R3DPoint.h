#ifndef R3DPoint_h
#define R3DPoint_h

#include <math.h>

#include <iostream>

class R3DPoint
{
public:
   double xyz[3];

   R3DPoint()
   {
     xyz[0] = xyz[1] = xyz[2] = 0;
   }

   R3DPoint(double x,double y,double z)
   {
       xyz[0] = x;
       xyz[1] = y;
       xyz[2] = z;
   }

   inline double x() const {return xyz[0];}
   inline double y() const {return xyz[1];}
   inline double z() const {return xyz[2];}

   double norm2()
   {
      return x()*x() + y()*y() + z()*z();
   }
 
   double norm()
   {
       return sqrt(norm2());
   }


   double dist2(R3DPoint &p)
   {
      return ( *this - p ).norm2();
   }

   double dist(R3DPoint &p)
   {
      return ( *this - p ).norm();
   }

 

   R3DPoint operator+(R3DPoint p)
   {
    return R3DPoint(x() + p.x(), y() + p.y(), z() + p.z() );
   }  
   
   R3DPoint operator-(R3DPoint p)
   {
     return R3DPoint(x() - p.x(), y() - p.y(), z() - p.z() );
   }  
  
   R3DPoint operator-()
   {
     return R3DPoint(-x(), -y(), - z() );
   }  

   R3DPoint operator*(double k)
   {
     return R3DPoint(k*x(), k*y(), k*z() );
   }  

   double operator*(R3DPoint p)
   {
      return   x() * p.x() +
               y() * p.y() +
               z() * p.z();
                     
   }

   R3DPoint operator/(double k)
   {
     return R3DPoint(x()/k, y()/k, z()/k );
   }  

  
};

inline R3DPoint operator*(double k,R3DPoint p)
{
  return p.operator*(k);
}


std::ostream& operator<<(std::ostream &os,R3DPoint &p)
{
  os<<"("<<p.x()<<","<<p.y()<<","<<p.z()<<")";
  return os;
}

#endif
