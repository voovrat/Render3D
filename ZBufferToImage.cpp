#include <Magick++.h> 
#include "R3DZArrayInterface.h"
//#include <iostream> 
//using namespace std; 

#include "R3DColor.h"
#include "R3DRect.h"

using namespace Magick; 


void ZBufferToImage( R3DZArrayInterface *zbuffer,
                     const char * image_name 
                   )
{
int xpixels,ypixels;
R3DRect rect = zbuffer->getRect();

double px = zbuffer->getPixelSize();

ypixels = rect.ysize / zbuffer->getPixelSize();
xpixels = rect.xsize / zbuffer->getPixelSize();

Image image(Geometry(xpixels,ypixels), ColorRGB(0,0,0) );

int i,j;
for(i=0;i<ypixels;i++)
for(j=0;j<xpixels;j++)
{
   R3DColor c = zbuffer->getPixel(rect.xmin + j*px,rect.ymin + i*px);
   double r,g,b;

   r = c.red()<1 ? c.red() : 1;
   g = c.green()<1 ? c.green() : 1;
   b = c.blue()<1 ? c.blue() : 1; 
    
   image.pixelColor( j, i, ColorRGB(r,g,b) );
}

image.write(image_name);

//  Image image( "100x100", "white" ); 
//  image.pixelColor( 49, 49, ColorRGB(1,0,1 ) ); 
//  image.write( "red_pixel.png" ); 
}
