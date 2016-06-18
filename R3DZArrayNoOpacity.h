#ifndef R3DZArrayNoOpacity_h
#define R3DZArrayNoOpacity_h

#include "R3DZArrayInterface.h"

class R3DZArrayNoOpacity : public R3DZArrayInterface 
{
protected:
 
  int m_ncols,m_nlines;
  R3DColor *m_color_matrix; // nlines*ncols, to be allocated
  double *m_z_matrix;       // nlines*ncols, to be allocated

  double m_focus; 

  // convert object coordinates to the pixel line and col
  // if out of range -> line=col=-1
  void getLineCol(double x,double y,int *line,int *col);
  
public:
 
   virtual double getPixelSize(double z);     
 
   R3DZArrayNoOpacity(R3DRect rect,double pixelSize,double Focus = 0);
   ~R3DZArrayNoOpacity();

   void addPixel(double x,double y,double z,R3DColor c,double opacity);
   R3DColor getPixel(double x,double y);

};

#endif
