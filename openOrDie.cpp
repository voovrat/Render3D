#include "openOrDie.h"

//char error_str[1024];

extern char *error_str;

FILE *openOrDie(const char *fname,const char *modifiers)
{  FILE *f=fopen(fname,modifiers);
  if(!f) 
   { 
     sprintf(error_str,"Cannot open file %s",fname);
     throw error_str;
   }
  return f;     
}
