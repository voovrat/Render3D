#ifndef R3DLuminance_h
#define R3DLuminance_h

// class calculate luminance of the triangles
// to accelerate the calculations, space around the lights is divided into segments

#include "R3DTriangle.h"
#include "R3DPlane.h"
#include "R3DLight.h"
#include "R3DListIndex.h"


#include <list>
#include <set>
class R3DLuminance 
{
public: // protected

   std::list<R3DTriangle> *m_triangles;
   std::list<R3DLight> *m_lights;
   std::list<R3DPlane> m_planes;  

   R3DListIndex<R3DTriangle> m_triIndex;
   R3DListIndex<R3DPlane> m_planeIndex;

   int m_Ntheta,m_Nphi, m_thetaMargin;
   // Theta margin: rigions at top and bottom belong to special segments 
   // (index 0 and 1)
   // The rigion size is defined as m_thetaMargin * m_dTheta
   double m_dTheta,m_dPhi,m_minTheta;
   //   m_dTheta = pi / ( Ntheta - 1 * m_thetaMargin * 2);
   // Ntheta-1 : number of distances between Ntheta points
   // m_thetaMargin*2 : number of distances in up and bottom regions together
  

public:

//  std::list<double> m_luminance;

  R3DLuminance( std::list<R3DTriangle> *triangles, 
                std::list<R3DLight> *lights, 
                int Ntheta = 10,
                int Nphi = 20,
                int thetaMargin = 1
              )
  {
     init(triangles,lights,Ntheta,Nphi,thetaMargin);
  }

  void init ( std::list<R3DTriangle> *triangles, 
                std::list<R3DLight> *lights, 
                int Ntheta = 10,
                int Nphi = 20,
                int thetaMargin = 1
              );
 
   
   void calculateLuminance(std::list<double> *luminance);


   // calculate spherical coordinated w.r.t. center of light
   void calcThetaPhi( R3DPoint &A,  //object position
                      R3DPoint &L,  //light position
                      double *theta, //out                     
                      double *phi    //out
                     );

   // get Segment index by position
   int getSegment( R3DPoint &A,  // object position
                   R3DPoint &L );
   
// returns all the segemtns in which there are points of the triangle
   void getSegments( R3DTriangle &T,
	             R3DPoint &L,//light pos 
                     std::set<int> *segment_set);

   // auxilarly function for getSegments 
   void getSubSegments ( R3DTriangle &T, 
                         R3DPoint &L, //light pos
                         int segmA, int segmB,int segmC,
                         std::set<int> *segment_set);


   


};

#endif
