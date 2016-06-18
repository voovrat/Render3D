
#include "drawTriangle.h"

#include "R3DPoint.h"
//#include "R3DLight.h"
#include "R3DZArrayInterface.h"
#include "R3DColor.h"

void drawTriangle(  R3DPoint &A,
                    R3DPoint &B,
                    R3DPoint &C,
                    R3DColor &color,
                    double opacity,
		   // std::list<R3DLight> *lights,
                    R3DZArrayInterface *zArray,
                    int Nrecursion // number of recursion
                 )
{
   if(Nrecursion<0)
   {
     double minZ = A.z() < B.z() ? A.z() : B.z();
            minZ = minZ < C.z() ? minZ : C.z();


     double pixelSize = zArray->getPixelSize(minZ);
     double pixelSize2 = pixelSize * pixelSize;  

     double AB2 = A.dist2(B);
     double AC2 = A.dist2(C);
     double BC2 = B.dist2(C);

     double R2 = AB2 > AC2 ? AB2 : AC2;
            R2 = R2 > BC2 ? R2 : BC2;

    // Nrec = log_2(R/pixelSize) = ln(R/pixelSize) / ln(2)
    //       ln(R/pixelSize) = 1/2 * ln( (R/pixelSize)^2)

     Nrecursion = 0.5 * log(R2 / pixelSize2 )/ M_LN2 ;//log_2(  R/pixelSize) 
     Nrecursion++;
   }

   if(Nrecursion==0)


//   if(A.dist2(B) < pixelSize2 && A.dist2(C) < pixelSize2 && B.dist2(C) < pixelSize2 )
   {
      R3DPoint M = (A+B+C)/3;

     // we need to find the normal vector to the triangle's plane
     // the plane's equation is 
     //       | x -x1  y -y1  z -z1|
     //   det | x2-x1  y2-y1  z2-z1|
     //       | x3-x1  y3-y1  z3-z1|

     // from this we find:   ax+by+cz+d = 0, where

     //  a = (y2-y1)*(z3-z1) - (y3-y1)*(z2-z1)
     //  b = -(x2-x1)*(z3-z1) + (x3-x1)*(z2-z1)
     //  c = (x2-x1)*(y3-y1) - (x2-x1)*(y2-y1)

/*      double x1 = A.x();
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
      double c = (x2-x1)*(y3-y1) - (x2-x1)*(y2-y1);

      
      R3DPoint abc(a,b,c);
     
      R3DPoint normal = abc/abc.norm();
    
      double k=0; //light coefficient
      std::list<R3DLight>::iterator it;
      for(it = lights->begin(); it != lights->end(); it++)
      {
         R3DLight &light = *it;

         R3DPoint ML = light.position - M;  // direction to light
     
         double normML = ML.norm();
 
         double cos_phi = ML * normal / normML; 
        
         k *= light.power / (normML*normML) * cos_phi; 
      }
*/

      zArray->addPixel(M.x(),M.y(),M.z(),color ,opacity);
       // zArray->addPixel(A.x(),A.y(),A.z(),color ,opacity);
      return;   
   }
  
   // divide sides into two equal parts
   R3DPoint C1 = (A+B)/2;
   R3DPoint B1 = (A+C)/2;
   R3DPoint A1 = (B+C)/2;

   //draw smaller triangles
   drawTriangle(A1,B1,C1,color,opacity,zArray,Nrecursion-1);
 
   drawTriangle(A,B1,C1,color,opacity,zArray,Nrecursion-1);
   drawTriangle(A1,B,C1,color,opacity,zArray,Nrecursion-1);
   drawTriangle(A1,B1,C,color,opacity,zArray,Nrecursion-1);
 
}

