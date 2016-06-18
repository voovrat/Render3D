#include <stdio.h>
#include <stdlib.h>

#include "R3DPoint.h"
#include "R3DPlane.h"
#include "R3DLineSegment.h"
#include "R3DTriangle.h"

#include "R3DLight.h"
#include "intersect.h"

#include "calculateLuminance.h"

#include "drawTriangle.h"

#include "R3DColor.h"
#include "R3DZArrayNoOpacity.h"
#include "ZBufferToImage.h"

#include <iostream>

#include <math.h>

#include <Magick++.h> 
using namespace Magick; 
using namespace std;

#include "R3DListIndex.h"

void testPoint()
{

 R3DPoint A(0,0,0),B(0,1,0),C(1,0,0);

 R3DPoint M = (A+B+C)/3;

 printf("%lf %lf %lf\n",M.x(),M.y(),M.z());

}

void testPlane()
{
R3DPoint A(0,0,1);
R3DPoint B(1,0,0);
R3DPoint C(0,1,0);

R3DPlane ABC(A,B,C);

R3DPoint M = ABC.m_abc;

 printf("%lf %lf %lf %lf\n",M.x(),M.y(),M.z(),ABC.m_d);


}

void testLinePlaneIntersect()
{
R3DPoint A(0,0,1);//(0,0,1);
R3DPoint B(1,0,1);//(1,0,0);
R3DPoint C(0,1,1);//(0,1,0);

R3DPlane ABC(A,B,C);

R3DPoint O(0,0,0);
R3DPoint M(2,0,2);

R3DLineSegment OM( O,M);

R3DPoint X;

bool r = intersect(OM,ABC,&X);

 printf("%d : %lf %lf %lf \n",r,X.x(),X.y(),X.z());

}

void testLineLineIntersect()
{
R3DLineSegment L1(R3DPoint(0,0,0),R3DPoint(1,1,1));
R3DLineSegment L2(R3DPoint(0,1,1),R3DPoint(1,0,0));

R3DPoint X;

bool r = intersect(L1,L2,&X);

 printf("%d : %lf %lf %lf \n",r,X.x(),X.y(),X.z());
}

void testTriangle()
{
R3DPoint A(0,0,0);
R3DPoint B(2,0,0);
R3DPoint C(1,1,0);

R3DTriangle ABC(A,B,C);

R3DPoint M(1,0.5,0);
R3DPoint N(0.5,0.4,0);
R3DPoint K(0.5,0.6,0);


 printf("%d %d %d\n",ABC.isInside(M),ABC.isInside(N),ABC.isInside(K));

}


void testLuminance()
{
std::list<R3DTriangle> triangles;
std::list<R3DPlane> planes;
std::list<R3DLight> lights;
std::list<double> luminance;

R3DPoint A(0,0,1);
R3DPoint B(1,1,2);
R3DPoint C(-1,1,2);

triangles.push_back( R3DTriangle(A,B,C) );

A = R3DPoint(0,0,1);
B = R3DPoint(-1,1,2);
C = R3DPoint(-1,-1,2);

triangles.push_back( R3DTriangle(A,B,C) );

A = R3DPoint(0,0,1);
B = R3DPoint(-1,-1,2);
C = R3DPoint(1,-1,2);

triangles.push_back( R3DTriangle(A,B,C));

A = R3DPoint(0,0,1);
B = R3DPoint(1,-1,2);
C = R3DPoint(1,1,2);

triangles.push_back( R3DTriangle(A,B,C));

cout<<A;

buildPlanes(
     &triangles, //std::list<R3DTriangle> *triangles, //in
     &planes     //std::list<R3DPlane> *planes //out
);
 
R3DLight L( R3DPoint(0,3,-8),100);

lights.push_back(L);

calculateLuminance
(  &triangles, //std::list<R3DTriangle> *triangles,
   &lights,    //std::list<R3DLight> *lights,
   &planes,    //std::list<R3DPlane> *planes, // planes of triangles. Use buildPlanes before 
   &luminance  //std::list<double> *luminance // out
);

std::list<double>::iterator lum_it;
for(lum_it=luminance.begin(); lum_it!=luminance.end(); lum_it++)
{
    printf("%lf\n",*lum_it);
}


R3DZArrayNoOpacity zbuffer
(        R3DRect(-2,-2,4,4), //  R3DRect rect,
         0.01,		//double pixelSize,
         5		//double Focus=0
);


std::list<R3DTriangle>::iterator tr_it;
for( lum_it = luminance.begin(),  tr_it = triangles.begin();
     lum_it != luminance.end();
     lum_it++, tr_it++)
{
   R3DColor c(*lum_it,*lum_it,*lum_it);
   R3DTriangle T = *tr_it;

   cout<<T<<endl;

   drawTriangle(  T.A, //R3DPoint &A,
                  T.B, //  R3DPoint &B,
                  T.C, //  R3DPoint &C,
                  c,   //  R3DColor &color,
                  1,   //  double opacity,
                  &zbuffer  //R3DZArrayInterface *zArray
                  );
}

ZBufferToImage( &zbuffer, //R3DZArrayInterface *zbuffer,
                "out.png" //     const char * image_name 
               );

}


void testInside()
{

//(6.41421,-4,2)-(5,-2.58579,2)-(5,-2.58579,4)  at (1.73544,0.678771,-3.91233)

R3DPoint A(6.41421,-4,2);
R3DPoint B(5,-2.58579,2);
R3DPoint C(5,-2.58579,4);

R3DPoint X(1.73544,0.678771,-3.91233);

R3DTriangle ABC(A,B,C);

int r = ABC.isInside(X);

printf(":::%d:::i\n",r);


}

int main(int argc,char *argv[])
{
//double x=0;
//double c=x/x;
  InitializeMagick(*argv);
 

//printf("%lf %d'\n",c,isnan(c));


//testPoint();
//testPlane();
//testLinePlaneIntersect();
//testLineLineIntersect();
//testTriangle();
//testLuminance();
//testInside();
//FILE *f = fopen("test.txt","r+");
//char s[256];
//double a,b;
//while(!feof(f))
//{
// fgets(s,255,f);

// if(sscanf(s,"%lf%lf",&a,&b)==2) 
//     printf("%lf %lf\n",a,b);
//}


//fclose(f);



//FILE *f = fopen("Проверка.txt","w+");
//fprintf(f,"Проверка:%s","Тест");
//fclose(f);

//printf("%s:",getenv("_"));

std::list<R3DTriangle> tri_list;
std::list<R3DLight> light_list;
std::list<R3DTriangle>::iterator tri_it;
std::list<R3DLight>::iterator light_it;

light_list.push_back(R3DLight(R3DPoint(0,0,0),1));
light_list.push_back(R3DLight(R3DPoint(2,0,2),2));

R3DListIndex<R3DLight> lightIndex(&light_list);


// Now random access is possible
 std::cout<<*lightIndex[1]<<endl;
 std::cout<<*lightIndex[0]<<endl;



printf("tri_list : %d \n"
       "light_list: %d \n "
       "tri_it: %d\n  "
       "light_it: %d\n",
        (int)sizeof(tri_list), 
        (int)sizeof(light_list),
        (int)sizeof(tri_it),
        (int)sizeof(light_it)
      );

double phi = atan2(1,1), psi = atan2(-1,-1);



printf("%lf %lf\n",phi/M_PI*180,(psi + 2*M_PI)/M_PI*180);


return 0;
}
