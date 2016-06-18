#include <Magick++.h> 
#include <iostream> 
using namespace std; 
using namespace Magick; 

int main(int argc,char **argv) 
{ 
  InitializeMagick(*argv);
  
   cout<<*argv<<endl;
 
  Image image( "100x100", "white" ); 
  image.pixelColor( 49, 49, ColorRGB(1,0,1 ) ); 
  image.write( "red_pixel.png" ); 
  return 0; 
}
/*
int main(int argc,char **argv) 
{ 
  InitializeMagick(*argv);

  // Construct the image object. Seperating image construction from the 
  // the read operation ensures that a failure to read the image file 
  // doesn't render the image object useless. 
  Image image;
  try { 
    // Read a file into image object 
    image.read( "a.png" );

    // Crop the image to specified size (width, height, xOffset, yOffset)
    image.crop( Geometry(100,100, 100, 100) );

    // Write the image to a file 
    image.write( "x.gif" ); 
  } 
  catch( Exception &error_ ) 
    { 
      cout << "Caught exception: " << error_.what() << endl; 
      return 1; 
    } 
  return 0; 
}
*/
