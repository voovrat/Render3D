#ifndef openOrDie_h
#define openOrDie_h

#include <stdio.h>

//open file or throws an const char * exception
// NOTE: 
//   You need to define global char *error_str  somewhere in your code: 
//  char error_str_buffer[1024];
// char *error_str = error_str_buffer;

FILE *openOrDie(const char *fname,const char *modifiers);

#endif

