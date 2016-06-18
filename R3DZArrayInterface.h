#ifndef R3DZArrayInterface_h
#define R3DZArrayInterface_h

class R3DColor; 


#include "R3DRect.h"


class R3DZArrayInterface {

protected:

   R3DRect m_rect;
   double m_pixelSize;

public:

   inline double getPixelSize() {  return m_pixelSize; }
  
   virtual double getPixelSize(double z)=0;

   inline R3DRect getRect() { return m_rect; }  

   virtual void addPixel(double x,double y,double z,R3DColor c,double opacity)=0;
   virtual R3DColor getPixel(double x,double y) = 0;

  

};

#endif
