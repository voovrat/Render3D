#include <stdio.h>

#include "R3DTriangle.h"
#include "R3DPlane.h"
#include "R3DLight.h"
#include "R3DPoint.h"
#include "R3DColor.h"

//#include "calculateLuminance.h"
#include "R3DLuminance.h"

#include <list>
#include <string>
#include <iostream>

#include "openOrDie.h"

#include "read_triangles.h"
#include "read_lights.h"

char error_str_buffer[1024];
char *error_str = error_str_buffer;


main(int argc,char *argv[])
{
try
{
const char *triangle_file;
const char *light_file;


if(argc<=2)
{
  puts("Usage: illuminate2 triangle_file light_file > output_file ");
  return 1;
}

triangle_file = argv[1];
light_file = argv[2];

std::list<R3DTriangle> triangles;
//std::list<R3DPlane> planes;
std::list<R3DLight> lights;
std::list<double> luminance;
std::list<R3DColor> colors;

//FILE *ftri = openOrDie(triangle_file,"r");
//FILE *flight = openOrDie(light_file,"r");

read_triangles(triangle_file,  &triangles, &colors);
read_lights(light_file, &lights);


R3DLuminance lumi(
         &triangles,   //  std::list<R3DTriangle> *triangles, 
         &lights,      //  std::list<R3DLight> *lights, 
         200,//       int Ntheta = 10,
         400//       int Nphi = 20,
         //       int thetaMargin = 1
 );

//buildPlanes(
//     &triangles, //std::list<R3DTriangle> *triangles, //in
//     &planes     //std::list<R3DPlane> *planes //out
//);


lumi.calculateLuminance(
   &luminance  //std::list<double> *luminance // out
);


std::list<double>::iterator lum_it;
std::list<R3DColor>::iterator col_it;
std::list<R3DTriangle>::iterator tri_it;
for(lum_it=luminance.begin(), col_it = colors.begin(), tri_it = triangles.begin();
     lum_it!=luminance.end(); 
    lum_it++,col_it++,tri_it++
   )
{
  R3DColor c = (*col_it) * (*lum_it);
  R3DTriangle T = *tri_it;
//    printf("!! %lf\n",*lum_it);
  printf("%lf %lf %lf       %lf %lf %lf       %lf %lf %lf      %lf %lf %lf\n",
          T.A.x(), T.A.y(), T.A.z(),
          T.B.x(), T.B.y(), T.B.z(),
          T.C.x(), T.C.y(), T.C.z(),
          c.red(), c.green(), c.blue()
       );

}

 return 0;
}catch(const char *error)
{
   
   printf("EXCEPTION : %s. STOP AND EXIT.\n",error);
   return 1;
}


}
