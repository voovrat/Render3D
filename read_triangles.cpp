#include "R3DTriangle.h"
#include "R3DColor.h"
#include "R3DPoint.h"

#include <list>

#include "openOrDie.h"

#include <stdio.h>

extern char *error_str;


void read_triangles( const char *fname,
                     std::list<R3DTriangle> *triangles, 
                     std::list<R3DColor> *colors 
                    )
{
  FILE *ftri = openOrDie(fname,"r");
 
char str[1024];
int nscan;
double x1,y1,z1,x2,y2,z2,x3,y3,z3;
double r,g,b;
int current_line=0;

while(!feof(ftri))
{
    if(!fgets(str,1024,ftri)) break; 
    current_line++;

    if(str[0] == '#') continue;

    nscan = sscanf(str,"%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf",
                &x1,&y1,&z1,&x2,&y2,&z2,&x3,&y3,&z3,&r,&g,&b);
   
    
    if(nscan!=12 && nscan>0)
    {    //static char error_str[1024];
         sprintf(error_str,"Incorrect number of arguments (%d) in file %s at line %d",nscan,fname,current_line);
         throw error_str;
    }

    if(nscan==12)
    {    R3DPoint A(x1,y1,z1);
         R3DPoint B(x2,y2,z2);
         R3DPoint C(x3,y3,z3);
  
         R3DTriangle T(A,B,C);

       // std::cout<<T<<std::endl;    
 
        triangles->push_back(T);
        colors->push_back(R3DColor(r,g,b));
     }
}// feof ftri

fclose(ftri);

}
