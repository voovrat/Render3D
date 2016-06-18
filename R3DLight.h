#ifndef R3DLight_h
#define R3DLight_h

#include "R3DPoint.h"

#include <iostream>


struct R3DLight 
{
  R3DPoint position;
  double power;  // at distance 1 and power 1 the koefficient will be 1

  R3DLight() {}

  R3DLight(R3DPoint position,double power)
  {
    this->position = position;
    this->power = power;
  }
};

std::ostream & operator<<(std::ostream &os,R3DLight &L)
{
   os<<L.position<<"*"<<L.power;
}

#endif
