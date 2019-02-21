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
    Packet(double t){
        setTime(t);
    }   
    void setTime(double t){
        time = t;
    }
   
    void setType(int ty){
        type = ty;
    }

    void setRID(int rid){
        routerId = rid;
    }

    void setDest(int dest){
        destination = dest;
    }
       
    double getTime() const {
        return time;
    }
    
    int getType(){
        return type;
    }
  
    int getRID(){
        return routerId;
    }
   
    int getDest(){
        return destination;
    }  
    
    
    private: 
    
    double time; // time used to determine when its current state will be finished.
    int type; // creation = 0, processing = 1, output queue = 2, propagation = 3, input queue = 5
    int routerId; // update current router id each time pkt moves 3->5
    int destination; // destination static


};

class myComparator
{
    public:
        int operator() (const Packet& p1, const Packet& p2) {
            return p1.getTime() > p2.getTime();
        }
 
};
