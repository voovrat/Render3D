#ifndef R3DRect_h
#define R3DRect_h

class R3DRect 
{
public:
   double xmin,ymin,xsize,ysize;

   R3DRect()
   {
      xmin = 0;
      ymin = 0;
      xsize = 0;
      ysize = 0;
   }

   R3DRect(double xmin,double ymin,double xsize,double ysize)
   {
       this->xmin = xmin;
       this->ymin = ymin;
       this->xsize = xsize;
       this->ysize = ysize;
   }

   inline double getXmin() {return xmin;}
   inline double getYmin() {return ymin;}
   inline double getXmax() {return xmin+xsize;}
   inline double getYmax() {return ymin+ysize;}
   
   inline double getXsize() {return xsize;}
   inline double getYsize() {return ysize;}

   inline bool isInRect(double x,double y)
   { 
      return (x>xmin) && (y>ymin) && (x<xmin+xsize) && (y<ymin+ysize);
   }

};

#endif
