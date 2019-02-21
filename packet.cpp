#ifndef LINK
#define LINK
#include "link.hpp"
#endif
#include <iostream>
#include <string>
#include <limits.h>



class Packet
{
    public:
    
    setTime(double t){
        time = t;
    }
   
    setType(int ty){
        type = ty;
    }

    setRID(int rid){
        routerId = rid;
    }

    setDest(int dest){
        destination = dest;
    }
       
    getTime(){
        return time;
    }
    
    getType(){
        return type;
    }
  
    getRID(){
        return routerId;
    }
   
    getDest(){
        return destination;
    }  
    
    
    private: 
    
    double time; // time used to determine when its current state will be finished.
    int type; // creation = 0, processing = 1, output queue = 2, propagation = 3, input queue = 5
    int routerId; // update current router id each time pkt moves 3->5
    int destination; // destination static


};
