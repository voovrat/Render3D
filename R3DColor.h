#ifndef R3DColor_h
#define R3DColor_h

class R3DColor {

public:
   double rgb[3];

   static R3DColor Black;
   static R3DColor White;

   R3DColor(double *rgb)
   {
        this->rgb[0] = rgb[0];
        this->rgb[1] = rgb[1]; 
        this->rgb[2] = rgb[2];
   }
   
   R3DColor(double r,double g,double b)
   {
        this->rgb[0] = r;
        this->rgb[1] = g; 
        this->rgb[2] = b;
   }
   
   inline double red() const { return rgb[0]; }
   inline void setRed(double r) { rgb[0] = r; }

   inline double green() const { return rgb[1]; }
   inline void setGreen(double g) { rgb[1] = g;}   

   inline double blue() const { return rgb[2]; }
   inline void setBlue(double b) { rgb[2] = b; }

   
   R3DColor operator*(double k)
   {
       return R3DColor(red()*k,green()*k,blue()*k);
   }

   R3DColor operator/(double k)
   {
       return R3DColor(red()/k,green()/k,blue()/k);
   }

};

inline R3DColor operator*(double k,R3DColor &col)
{
   return col.operator*(k);
}

#endif
