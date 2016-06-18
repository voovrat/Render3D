#ifndef R3DListIndex_h
#define R3DListIndex_h

// defines an object which allows one to indexate lists

#include <list>
//#include <stdlib.h>
#include <stdio.h>

template<typename T>
class R3DListIndex
{
protected:
  
   typename std::list<T>::iterator *m_index;

public:
   R3DListIndex() { m_index = NULL;  }

   
   R3DListIndex(std::list<T> * list)
   {
      init(list);
   }
   
   void init(std::list<T> * list)
   {
       m_index = 
         new typename std::list<T>::iterator[list->size()];

      typename std::list<T>::iterator it;
       int i;
       for(it=list->begin(), i=0; it!=list->end(); it++, i++) 
       { 
           m_index[i] = it;  
       }
     
   
   }

   ~R3DListIndex()
   {
      if(m_index) delete m_index;
   }

   typename std::list<T>::iterator operator[](int i)
   {
        return m_index[i];
   } 

};

#endif
