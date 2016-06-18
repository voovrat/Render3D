
#include "R3DPoint.h"
#include "R3DPlane.h"
#include "R3DLineSegment.h"

#include "settings.h"
#include <iostream>

bool intersect(  R3DLineSegment &line, 
                 R3DPlane &plane, 
                 R3DPoint *intersection_point // out
//                 double *t   // parameter t at intersection (out)
               )
{
// Plane: ax + by + cz + d =0
// Line:  x = x0 + dx*t,  y=y0+dy*t, z=z0+dz*t  
// -->  a(x0 + dx*t) + b(y0+dy*t) + c(z0+dz*t) + d = 0
// -->  (a*dx + b*dy + c*dz)*t = -a*x0 - b*y0 - c*z0 -d  
// In scalar products:
//  A*X + d =0       X = X0 + DX*t 
//  A(X0 + DX*t) + d = 0
//  (A*DX)*t =  -A*X0 - d
//  t = (-A*X0-d) / (A*DX)

// in our definitions:  a==plane.m_abc,   x0 == line.m_origin,  dx == line.m_direction

  double t =  (-plane.m_abc * line.m_origin - plane.m_d) / (plane.m_abc * line.m_direction);

  *intersection_point = line.m_origin + t * line.m_direction;

  return  !isnan(t) && (t> 0 ) && (t< 1 );  
 
  

}

bool intersect( R3DLineSegment &line1,
                R3DLineSegment &line2,
                R3DPoint *intersection_point )
{
//   Line1 : (x1,y1,z1) + (dx1,dy1,dz1)*t1
//   Line2 : (x2,y2,z2) + (dx2,dy2,dz2)*t2
//
//   x1 + dx1 * t1 = x2 + dx2 * t2   
//   y1 + dy1 * t1 = y2 + dy2 * t2
//
//  --> 
//   dx1 * t1 - dx2 * t2 = x2 - x1
//   dy1 * t1 - dy2 * t2 = y2 - y1
//
// for t2:
//   dx1 * dy1 * t1   -  dx2 * dy1 * t2 = (x2-x1)*dy1
//   dy1 * dx1 * t1   -  dy2 * dx1 * t2 = (y2-y1)*dx1
// 
//   (dy2 * dx1  - dx2 * dy1) * t2 = (x2-x1)*dy1 - (y2-y1)*dx1
//
//    t2 = ((x2 - x1) * dy1 -  (y2-y1)*dx1) / ( dy2 * dx1 - dx2 * dy1 );
//
// for t1:
//    dx1 * dy2 * t1 - dx2 * dy2 * t2 = (x2-x1)*dy2
//    dy1 * dx2 * t1 - dy2 * dx2 * t2 = (y2-y1)*dx2
//
//    ( dx1 * dy2 - dy1 * dx2) * t1 = (x2-x1)*dy2 - (y2-y1)*dx2
//
//    t1 = ( (x2-x1) * dy2 - (y2-y1)*dx2) / (dx1*dy2 - dy1*dx2);
//

if(DEBUG) std::cout<<"---";


  double x1 = line1.m_origin.x();
  double y1 = line1.m_origin.y();
  double z1 = line1.m_origin.z();

  double dx1 = line1.m_direction.x();
  double dy1 = line1.m_direction.y();
  double dz1 = line1.m_direction.z();
 
  double x2 = line2.m_origin.x();
  double y2 = line2.m_origin.y();
  double z2 = line2.m_origin.z();

  double dx2 = line2.m_direction.x();
  double dy2 = line2.m_direction.y();
  double dz2 = line2.m_direction.z();

// SPECIAL CASES:
  double eps = 1e-6;
  double t1=-1, t2=-1;


if(fabs(dx1)<eps && fabs(dx2)<eps ) 
{
    if(fabs(x1 - x2)>eps) return false;

    x1 = z1;  dx1 = dz1;
    x2 = z2;  dx2 = dz2;
} 

if(fabs(dy1)<eps && fabs(dy2)<eps ) 
{
    if(fabs(y1 - y2)>eps) return false;

    y1 = z1; dy1 = dz1;
    y2 = z2; dy2 = dz2;
}

if( fabs(dx1) < eps && fabs(dy1)<eps)
{
   if( fabs(dx2) > eps)
   {
       t2 = (x1-x2) / dx2;  // x1 + 0t1 = x2 + dx2 t2
   }
   else
   {
       t2 = (y1 - y2)/dy2;  // y1 + 0t1 = y2 + dy2 t2
   }

   // z1 + t1 dz1 = z2 + t2 dz2
   // t1 = (z2 + t2 dz2 - z1) / dz1
   t1 = (z2 + t2*dz2 - z1) / dz1;

   if(DEBUG) 
   {
     std::cout<<"t1:"<<t1<<"  t2:"<<t2<<std::endl;
   }

  *intersection_point = line1.m_origin + t1*line1.m_direction;

  if(DEBUG)
  {
    std::cout<<"intersection of"<<line1<<" and "<<line2<<"  is at "<<*intersection_point<<std::endl;

  }

 
   return ( t1>0 && t1<1 && t2>0 && t2<1); 

}

if( fabs(dx2) < eps && fabs(dy2)<eps)
{
   if( fabs(dx1) > eps)
   {
       t1 = (x2-x1) / dx1;  // x1 + dx1t1 = x2 + 0 t2
   }
   else
   {
       t2 = (y2 - y1)/dy1;  // y1 + dy1 t1 = y2 + 0 t2
   }

   // z1 + t1 dz1 = z2 + t2 dz2
   // t2 = (z1 + t1 dz1 - z2) / dz2
   t2 = (z1 + t1*dz1 - z2) / dz2;

   if(DEBUG) 
   {
     std::cout<<"t1:"<<t1<<"  t2:"<<t2<<std::endl;
   }
   
  *intersection_point = line1.m_origin + t1*line1.m_direction;

  if(DEBUG)
  {
    std::cout<<"intersection of"<<line1<<" and "<<line2<<"  is at "<<*intersection_point<<std::endl;

  }



   return ( t1>0 && t1<1 && t2>0 && t2<1); 

}

if( fabs(dy1/dx1 - dy2/dx2)<eps) ///xy projections are parrallel
{

     // Let dy1/dx1 = K , dy1 = Kdx1
     // we have 
     //   x1 + t1 * dx1  =  x2 + t2* dx2    
     //   y1 + t1 * K*dx1 = y2 + t2 * K*dx2
     // Multiply first by K:

     //   Kx1 + t1 * K*dx1 = K*x2 + t2 * K*dx2
     // Thus t1*Kdx1 - t2*Kdx2  == K ( x2 - x1 ) == y2 - y1
     //  thus if    dy1/dx1 *(x2-x1) == y2 - y1  projections coincide, otherwise - are parrallel
     //  
    
     if ( fabs( dy1 / dx1 * (x2-x1) - (y2-y1)) > eps) return false;

     // if coincide --> change y to z

     y1 = z1;    dy1 = dz1;
     y2 = z2;    dy2 = dz2;
}




   t2 = ((x2 - x1) * dy1 -  (y2-y1)*dx1) / ( dy2 * dx1 - dx2 * dy1 );
   t1 = ( (x2-x1) * dy2 - (y2-y1)*dx2) / (dx1*dy2 - dy1*dx2);

  
  *intersection_point = line1.m_origin + t1*line1.m_direction;

  if(DEBUG)
  {
    std::cout<<"intersection of"<<line1<<" and "<<line2<<"  is at "<<*intersection_point<<std::endl;

  }



  if(DEBUG) 
   {
     std::cout<<"t1:"<<t1<<"  t2:"<<t2<<std::endl;
   }
 

  if( t1<0 || t1>1 || t2<0 || t2>1 ) return false;

  if(fabs( z1 + t1*dz1  - z2 - t2*dz2)>eps) return false;

  return true;
}



