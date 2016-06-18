#include "R3DLight.h"
#include "R3DPoint.h"

#include "openOrDie.h"

#include <stdio.h>
#include <list>

extern char *error_str;

void read_lights( const char *lights_file,  std::list<R3DLight> *lights)
{
FILE *flight = openOrDie(lights_file,"r");

int current_line = 0;
double x1,y1,z1;
double power;
char str[1024];
int nscan;
while(!feof(flight))
{
    if(!fgets(str,1024,flight)) break; 
    current_line++;

    if(str[0] == '#') continue;

    nscan = sscanf(str,"%lf%lf%lf%lf",
                &x1,&y1,&z1,&power);
   
    
    if(nscan!=4 && nscan>0)
    {
         sprintf(error_str,"Incorrect number of arguments (%d) in file %s at line %d",nscan,lights_file,current_line);
         throw error_str;
    }

    if(nscan == 4)
    { R3DLight L(R3DPoint(x1,y1,z1),power);  
      lights->push_back(L);
    }
}// feof flight 

fclose(flight);

}

