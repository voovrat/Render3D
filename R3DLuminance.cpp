#include "R3DLuminance.h"

#include "R3DPoint.h"
#include "R3DLineSegment.h"

#include <math.h>

#include "buildPlanes.h"
#include "intersect.h"

#include "settings.h"

#include <iostream>

void R3DLuminance::init ( std::list<R3DTriangle> *triangles, 
                std::list<R3DLight> *lights, 
                int Ntheta ,//= 10,
                int Nphi, // = 20,
                int thetaMargin //= 1
              )
{
   m_triangles = triangles;
   m_lights = lights;

   m_Ntheta = Ntheta;
   m_Nphi = Nphi;
   m_thetaMargin = thetaMargin;

   m_dTheta = M_PI/( Ntheta - 1 + 2*thetaMargin);
   m_minTheta = thetaMargin * m_dTheta;
   m_dPhi = 2*M_PI/ Nphi;
    
   buildPlanes(
     triangles, //std::list<R3DTriangle> *triangles, //in
     &m_planes  //std::list<R3DPlane> *planes //out
   );

   m_triIndex.init(triangles);
   m_planeIndex.init(&m_planes);

}
 
// calculate spherical coordinated w.r.t. center of light
void R3DLuminance::calcThetaPhi( 
             R3DPoint &A,  //object position
             R3DPoint &L,  //light position
             double *theta, //out                     
             double *phi    //out
            )
{ R3DPoint LA = (A-L);

  double R = LA.norm();      
  *theta = acos(LA.z() / R);        
  *phi = atan2(LA.y(),LA.x() );
  if(*phi<0) *phi += 2*M_PI;                          
}

int R3DLuminance::getSegment( 
                   R3DPoint &A,  // object position
                   R3DPoint &L )
{
    double th,phi;
    calcThetaPhi(A,L,&th,&phi); 

    if(th<m_minTheta) return 0;  // 0 segment - "up"
    if(th>M_PI-m_minTheta) return 1; // 1 segment - "down"

    int line = (th - m_minTheta) / m_dTheta;
    int col = phi / m_dPhi;

    return 2 + line * m_Nphi + col;
 }

// returns all the segemtns in which there are points of the triangle
void R3DLuminance::getSegments( R3DTriangle &T,
                                R3DPoint &L, //light position 
                     std::set<int> *segment_set)
{
   int segmA = getSegment( T.A, L); 
   int segmB = getSegment( T.B, L);
   int segmC = getSegment( T.C, L);

   getSubSegments( T, //      R3DTriangle &T,
                   L, //      R3DPoint &L, //light position 
                   segmA,segmB,segmC,//int segmA, int segmB,int segmC,
                   segment_set //      std::set<int> *segment_set
                 );
}

   // auxilarly function for getSegments 
void R3DLuminance::getSubSegments ( 
                         R3DTriangle &T,
                         R3DPoint &L, //light position 
                         int segmA, int segmB,int segmC,
                         std::set<int> *segment_set)
{
   if(DEBUG)
   {
     std::cout<<"AB:"<<(T.A-T.B).norm()<<"  BC:"<<(T.B-T.C).norm()<<"  AC:"<<(T.A-T.C).norm()<<std::endl;
   }

   if( segmA == segmB && segmB == segmC ) //all in one segment
   {
      segment_set->insert(segmA);
      return;
   }
//         C
//         *
//        / \
//       /   \
//    B1*-----*A1
//     / \   / \
//    /   \ /   \
//   *-----*-----*
//  A      C1     B
//
   R3DPoint A1 = (T.B + T.C)/2;          
   R3DPoint B1 = (T.A + T.C)/2;         
   R3DPoint C1 = (T.A + T.B)/2;            
                                        
   int segmA1 = getSegment(A1,L);
   int segmB1 = getSegment(B1,L);
   int segmC1 = getSegment(C1,L);

   // if all segments are neigbouring 
   if ( ( segmA1 == segmB || segmA1 == segmC) &&
        ( segmB1 == segmA || segmB1 == segmC) &&
        ( segmC1 == segmA || segmC1 == segmB)
      )
   {
        segment_set->insert(segmA);
        segment_set->insert(segmB);
        segment_set->insert(segmC);
        return;
   }


    R3DTriangle AB1C1 ( T.A, B1, C1);
    R3DTriangle BA1C1 ( T.B, A1, C1);
    R3DTriangle CA1B1 ( T.C, A1, B1);
    R3DTriangle A1B1C1 ( A1, B1, C1);

    // call recoursively
    getSubSegments (  AB1C1, // R3DTriangle &T,
                      L,  //   R3DPoint &L, //light position 
                      segmA, segmB1, segmC1, //   int segmA, int segmB,int segmC,  
                      segment_set //   std::set<int> *segment_set
                    );
   
     getSubSegments (  BA1C1, // R3DTriangle &T,
                      L,  //   R3DPoint &L, //light position 
                      segmB, segmA1, segmC1, //   int segmA, int segmB,int segmC,  
                      segment_set //   std::set<int> *segment_set
                    );
   
     getSubSegments (  CA1B1, // R3DTriangle &T,
                      L,  //   R3DPoint &L, //light position 
                      segmC, segmA1, segmB1, //   int segmA, int segmB,int segmC,  
                      segment_set //   std::set<int> *segment_set
                    );

     getSubSegments (  A1B1C1, // R3DTriangle &T,
                      L,  //   R3DPoint &L, //light position 
                      segmA1, segmB1, segmC1, //   int segmA, int segmB,int segmC,  
                      segment_set //   std::set<int> *segment_set
                    );

   
}

void R3DLuminance::calculateLuminance(std::list<double> *luminance)
{

std::list<R3DLight>::iterator light_it;

int N = m_triangles->size();
int Nsegm = m_Ntheta * m_Nphi + 2;

std::list<int> *segments = new std::list<int>[ Nsegm ];
bool *isVisible = new bool[N];

//LineSegment *rayList = new LineSegment[N];
R3DPoint *midPoint = new R3DPoint[N];

// initialize with zeros
int i;
luminance->clear();
for(i=0;i<N;i++)
  luminance->push_back( 0 );


// calculate luminance: light by light 
for(light_it = m_lights->begin();
    light_it != m_lights->end();
    light_it ++) 
{
    R3DPoint L = (*light_it).position;
    double power = (*light_it).power;

    for(i=0;i<Nsegm;i++) segments[i].clear();
    for(i=0;i<N;i++) isVisible[i] = true;
     
    std::set<int> S; //segment of triangles
    std::set<int>::iterator set_it;
    std::list<R3DTriangle>::iterator tri_it;


    int tri_idx;
    // add triangles to appropriate segments
    for(tri_it = m_triangles->begin(),   tri_idx = 0;
        tri_it != m_triangles->end();
        tri_it++,                        tri_idx ++ )
    {
        S.clear();
        getSegments( *tri_it, //R3DTriangle &T,
                     L ,//  R3DPoint &L, //light position 
                     &S //std::set<int> *segment_set
                    );

         if(DEBUG) std::cout<<"Triangle "<<*tri_it<<" SEGMENTS:"<<std::endl;

        for( set_it = S.begin(); set_it!=S.end(); set_it ++ )
        {
            if(DEBUG)
            {
              std::cout<<*set_it;
            }
           
	    segments[ *set_it ].push_back( tri_idx  ); 
        }
   
    }// tri_it

if(DEBUG)
{
	for(i=0;i<Nsegm;i++)
        {
          std::list<int>::iterator idx_it;


          printf("SEGMENT %d:\n",i); 
          for( idx_it = segments[i].begin(); idx_it!=segments[i].end(); idx_it++)     
          {
              std::cout<<"Triangle "<<*idx_it<<" : "<< *m_triIndex[ *idx_it ]<<std::endl;
          }

        }


}


    // intersect triangles inside the segments
    int segm_id;
    for(segm_id = 0; segm_id < Nsegm; segm_id++)
    {
          // go through all the triangles in the segment 
          std::list<int>::iterator idx_it1,idx_it2;
          for( idx_it1 = segments[ segm_id].begin();
               idx_it1 != segments[ segm_id].end();
               idx_it1++)
          {
                 R3DTriangle T1 = *m_triIndex[ *idx_it1 ];
                 R3DPoint M = (T1.A + T1.B + T1.C)/3;
                 
                 R3DLineSegment ML(M,L);
                 midPoint[ *idx_it1 ] = M;

                 // check if ML croses one of triangles in this segment
                 for(idx_it2 = segments[segm_id].begin();
                     idx_it2 != segments[segm_id].end();
                     idx_it2 ++ )
                 {
                     if ( *idx_it1 == *idx_it2) continue; //triangle coinside
                     R3DPoint X; //cross of the plane with 
                     R3DPlane P2 = *m_planeIndex[ *idx_it2 ];
                  
                     if(! intersect( ML, P2, &X)) continue; // ML does not intersect wuth the plane of second triangle
                     

                     R3DTriangle T2 = *m_triIndex[ *idx_it2 ];

                     if( T2.isInside(X)) //croos point (X) is inside T2
                     {
                          isVisible[ *idx_it1 ] = false; // T2 covers T1
                          break;  
                     } 

                 }//idx_it2
          }// idx_it1

    } //segm_id
  
//    std::list<double>::iterator lum_it;
    std::list<double>::iterator lum_it;
    for( i=0, lum_it = luminance->begin(); 
         i<N; 
         i++, lum_it++)
    {
       if(!isVisible[i]) continue;

        R3DPlane P = *m_planeIndex[i];
       
       R3DLineSegment ML( midPoint[i], L);

     

       double normML = ML.m_direction.norm();
       double cos_phi = fabs( P.getNormal() * ML.m_direction )/normML;

      if(DEBUG)
         std::cout<<"M:"<<midPoint[i]<<" cos_phi="<<cos_phi<<"  normML="<<normML<<std::endl;
//       K = L.power / (normML * normML) * cos_phi;
       *lum_it += power / (normML * normML) * cos_phi;
    }
    



}// for light


delete [] segments;
delete [] isVisible;
delete [] midPoint;

}


