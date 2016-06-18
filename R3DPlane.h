#ifndef R3DPlane_h
#define R3DPlane_h

#include "R3DPoint.h"
#include <iostream>

class R3DPlane 
{
public:
    R3DPoint m_abc; // normal
    double m_d;

    R3DPlane(R3DPoint abc,double d); 
    R3DPlane(R3DPoint A,R3DPoint B,R3DPoint C); // plane trough 3 points

    R3DPoint getNormal()
    {
        return m_abc/m_abc.norm();
    }

};

std::ostream& operator<<(std::ostream &os,R3DPlane &plane)
{
   os<<plane.m_abc<<"*(x,y,z) + "<<plane.m_d;
}

#endif
