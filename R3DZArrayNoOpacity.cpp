#include "R3DZArrayNoOpacity.h"    
 
#include <stdlib.h>
#include <limits>
#include "R3DColor.h"



R3DZArrayNoOpacity::R3DZArrayNoOpacity(R3DRect rect,double pixelSize,double Focus)
{
    int n_alloc;

    m_rect = rect;
    m_pixelSize = pixelSize;

    m_ncols = (int)(m_rect.getXsize() / m_pixelSize)+1;
    m_nlines = (int)(m_rect.getYsize() / m_pixelSize) + 1;

    n_alloc = m_nlines * m_ncols;

    m_color_matrix = (R3DColor *) malloc( n_alloc * sizeof(R3DColor) );
    m_z_matrix = (double *)malloc( n_alloc * sizeof(double));
    
    double *ptr = m_z_matrix; 
    double inf = std::numeric_limits<double>::infinity();
    int count;
    for(count=n_alloc; count>0; count--,ptr++) 
    {
       *ptr = inf;
    }
   
   m_focus = Focus;

}

R3DZArrayNoOpacity::~R3DZArrayNoOpacity()
{
   free(m_color_matrix);
   free(m_z_matrix);
}

// convert object coordinates to the pixel line and col
// if out of range -> line=col=-1
void R3DZArrayNoOpacity::getLineCol(double x,double y,int *line,int *col)
{
    if(!m_rect.isInRect(x,y))
    {
        *line = *col = -1;
         return;
    }

    *col = (x - m_rect.getXmin()) / m_pixelSize;
    *line = (y - m_rect.getYmin()) / m_pixelSize;
}

double R3DZArrayNoOpacity::getPixelSize( double z)
{
//                  px(z)
//                *------*
//                |     /          px(z) /(z+F) =  px /F  -> px(z) = (F+z) / F *px
//               z|    /
//                |px /
//          ---------*--
//                | /
//               F|/
//                *
//

  return (m_focus + z)/m_focus * R3DZArrayInterface::getPixelSize();


}


void R3DZArrayNoOpacity::addPixel(double x,double y,double z,R3DColor c,double opacity)
{
   int line,col;
   double x1,y1;

   if(m_focus<1e-8)
   {
       x1 = x; y1 = y;
   }
   else
   {
       x1 = m_focus / (m_focus + z) * x;
       y1 = m_focus / (m_focus + z) * y;
//                   x
//                *------*
//                |     /          x/(z+F) = x1/F  -> x1 = F/(F+z)*x 
//               z|    /
//                |x1 /
//          ---------*--
//                | /
//               F|/
//                *
//
  }

   getLineCol(x1,y1,&line,&col);

   if(line<0) return;  // point out of bounds

   int offset = line * m_ncols + col;
   double *current_z = m_z_matrix + offset;
   
   if(z > *current_z) return;

   *current_z = z;
   m_color_matrix[offset] = c;
}

R3DColor R3DZArrayNoOpacity::getPixel(double x,double y)
{
   int line,col;
   getLineCol(x,y,&line,&col);

   if(line<0) return R3DColor::Black;

   return m_color_matrix[line * m_ncols + col ];
}



