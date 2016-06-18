#include "R3DPoint.h"
#include "R3DTriangle.h"
#include "R3DPlane.h"
#include "R3DLight.h"
#include "R3DLineSegment.h"

#include "settings.h"

#include "intersect.h"

#include <math.h>

#include <list>

#include <iostream>

using namespace std;

/*  --- NOW in buildPlanes.cpp ---


void buildPlanes(
     list<R3DTriangle> *triangles, //in
     list<R3DPlane> *planes //out
)
{
list<R3DTriangle>::iterator it;
planes->clear();

R3DTriangle T;

if(DEBUG) cout<<"PLANES:"<<endl;

for(it = triangles->begin();
    it != triangles->end(); 
    it++)
{   
    T = *it; 
    R3DPlane p(T.A,T.B,T.C);

    planes->push_back( p );
 
if(DEBUG)    cout<<p<<endl;
}


}            
*/

void calculateLuminance
(  list<R3DTriangle> *triangles,
   list<R3DLight> *lights,
   list<R3DPlane> *planes, // planes of triangles. Use buildPlanes before 
   list<double> *luminance // out
)
{

list<R3DTriangle>::iterator it1,it2;
list<R3DPlane>::iterator plane_it1,plane_it2;
list<R3DLight>::iterator light_iterator;

double K; // luminance of the current triangle
R3DPoint X;
luminance->clear();

R3DTriangle T1; 
R3DPoint M,normal; // center of the triangle

for( it1 = triangles->begin(),  plane_it1 = planes->begin();
     it1 != triangles->end();
     it1++, plane_it1++)
{
    T1 = *it1;
    M = (T1.A + T1.B + T1.C)/3;
    normal = (*plane_it1).getNormal();

    K = 0;

if(DEBUG)
{    cout<<"Triangle 1:"<<T1<<endl;
    cout<<"Normal:"<<normal<<endl;
}
    

    for( light_iterator = lights->begin();
         light_iterator != lights->end();
         light_iterator++)
    {
         R3DLight L = *light_iterator;
         R3DLineSegment ML(M,L.position);

if(DEBUG)       cout<<"ML:"<<ML<<endl;

    
        for( it2 = triangles->begin(), plane_it2 = planes->begin();
              it2 != triangles->end();
              it2++, plane_it2++)
         {
             if(it1 == it2 ) continue;
            
             if( intersect( ML, *plane_it2, &X) &&
                 (*it2).isInside(X) 
               ) 
           {  
   if(DEBUG)      cout<<"Intersect with Triangle 2: "<<*it2<<"  at "<<X<<endl;
 
              break;
           } // break;  // ray intersects the triangle, light is invisible

         }//triangle 2

         if( it2 == triangles->end() )  //there were no intersections
         {
              double normML = ML.m_direction.norm();
              double cos_phi = fabs( normal * ML.m_direction )/normML;
              K += L.power / (normML * normML) * cos_phi;

     if(DEBUG)   
      cout<<"normal"<<normal<<"DIR:"<<ML.m_direction<<"normML:"<<normML<<"  cos_phi"<<cos_phi<<endl;
         }
    }//light
         
    luminance->push_back(K);
    
}// triangle 1




}

