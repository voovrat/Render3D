#include "R3DTriangle.h"
#include "R3DPlane.h"

#include "settings.h"

#include <list>

#include <iostream>

using namespace std;

void buildPlanes(
     list<R3DTriangle> *triangles, //in
     list<R3DPlane> *planes //out
)
{
list<R3DTriangle>::iterator it;
planes->clear();

R3DTriangle T;

if(DEBUG) cout<<"PLANES:"<<endl;

for(it = triangles->begin();
    it != triangles->end(); 
    it++)
{   
    T = *it; 
    R3DPlane p(T.A,T.B,T.C);

    planes->push_back( p );
 
if(DEBUG)    cout<<p<<endl;
}


}            


