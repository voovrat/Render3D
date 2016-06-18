#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>


#include "R3DColor.h"
#include "R3DTriangle.h"
#include "R3DPoint.h"

#include "R3DZArrayNoOpacity.h"
#include "drawTriangle.h"
#include "ZBufferToImage.h"

#include "read_triangles.h"
#include <Magick++.h> 
using namespace Magick; 
using namespace std;

char error_str_buffer[1024];
char *error_str = error_str_buffer;

// externs defined in getopt:
// extern char *optarg;   
// extern int optind, opterr, optopt;

#include <string>
#include <list>

static struct option long_options[] = {
         {"xsize",     required_argument, 0,  0 },
         {"ysize",     required_argument, 0,  0 },
         {"focus",     required_argument, 0,  0 },
         {"pixelSize", required_argument, 0,  0 },
         {"input",     required_argument, 0,  0 },
         {"output",    required_argument, 0,  0 },
         {"help",      no_argument,       0,  0 },
         {0,         0,                 0,  0 }
};

double xsize = 10,ysize =10, focus = 5 ,pixelSize = 0.01;

std::string input_file="/dev/stdin";
std::string output_file = "out.png";

void usage()
{
puts("usage:  render3d  [options] ");
puts("");
puts("OPTIONS:");
puts("--xsize=xsize");
puts("--ysize=ysize");
puts("--focus=focus");
puts("--input=input_file  (by default - stdin)");
puts("--output=output_file ( by default - out.png");
exit(1);
}


void *vals[] = { &xsize, &ysize, &focus, &pixelSize, &input_file, &output_file, (void *)&usage };
char types[]   = { 'd',    'd',    'd',    'd',         's',         's'        , 'f' };


void parse_options(int argc,char **argv)
{
    int c;
    int option_index;

    while (1) {
 
        c = getopt_long(argc, argv, "",
                 long_options, &option_index);

        if (c == -1)
            break;

        switch(types[option_index])
        { 
           case 'd':
 		     sscanf(optarg,"%lf",  (double *)vals[option_index]); 
                    
                     break;

           case 's': 
                     *(std::string *)vals[option_index] = optarg;
                     break;

           case  'f':
                     (( void (*)(void) )vals[option_index])();
 
                     break;

        };        
   } // while 1

}//parse options




int
main(int argc, char **argv)
{
try
{

parse_options(argc,argv);

printf("xsize=%lf\n ysize=%lf\n  focus=%lf\n pixelSize=%lf\n input=%s\n output=%s\n",
         xsize,ysize,focus,pixelSize,input_file.c_str(),output_file.c_str());

std::list<R3DTriangle> triangles;
std::list<R3DColor> colors;

read_triangles( input_file.c_str(),        //const char *fname,
                &triangles,                //std::list<R3DTriangle> *triangles, 
                &colors                    // std::list<R3DColor> *colors 
               );

InitializeMagick(*argv);
 
R3DRect rect ( -xsize/2, -ysize/2, xsize, ysize );

   
R3DZArrayNoOpacity zbuffer
(        rect,          //  R3DRect rect,
         pixelSize,		//double pixelSize,
         focus		//double Focus=0
);


std::list<R3DTriangle>::iterator tr_it;
std::list<R3DColor>::iterator col_it;
for( col_it = colors.begin(),  tr_it = triangles.begin();
     col_it != colors.end();
     col_it++, tr_it++)
{
   R3DTriangle T = *tr_it;

//   cout<<T<<endl;

   drawTriangle(  T.A, //R3DPoint &A,
                  T.B, //  R3DPoint &B,
                  T.C, //  R3DPoint &C,
                  *col_it,   //  R3DColor &color,
                  1,   //  double opacity,
                  &zbuffer  //R3DZArrayInterface *zArray
                  );
}

ZBufferToImage( &zbuffer, //R3DZArrayInterface *zbuffer,
                output_file.c_str()//     const char * image_name 
               );


} catch(const char *error)
{
   printf("EXCEPTION : %s. STOP AND EXIT.\n",error);
}

return 0;
}


