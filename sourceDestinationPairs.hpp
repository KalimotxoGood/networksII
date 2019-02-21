#ifndef LINK
#define LINK
#include "link.hpp"
#endif
#include <iostream>
#include <string>
#include <limits.h>


class SDpair 
{

    public:
    
    SDpair(){
    
  //      setSD(src, dest);
    }
    
    bool setSD(int src, int dest){
        if (src==source) return false;
        source = src;
        destination = dest;
        return true;
    }
    
   int getDestination(){
       return destination;
   }
  
   int getSource(){
       return source;
   }
   private:
  
       int source;
       int destination;

};
