#ifndef read_lights_h
#define read_lights_h

#include <list>
#include "R3DLight.h"

// read lights form file lights_file in 4 column format
//  x y z power
//  throws const char* exception if fails
// NOTE: 
//   You need to define global char *error_str somewhere in your code: 
//char error_str_buffer[1024];
//char *error_str = error_str_buffer;



void read_lights( const char *lights_file,  std::list<R3DLight> *lights);

#endif
