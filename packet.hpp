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
    
    Packet(double t, int rid, int dest, int type, double pktSize, int curr, double start){
        setTime(t);
        setRID(rid);
        setDest(dest);
        setType(type);
        setSize(pktSize);
        setPrev(curr);
        setStart(start);
    } 
    void setStart(double start) {
         startTime = start;
    }
    void setPrev(int curr){
         previous = curr;
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
    void setSize(double pktSize){
         size = pktSize;
    }   
    double getTime() const {
        return time;
    }
    
    int getType()const{
        return type;
    }
  
    int getRID()const{
        return routerId;
    }
   
    int getDest() const {
        return destination;
    }  
    double getSize() const { 
         return size;
    }
    int getPrev() const{
         return previous;
    }
    int getStart() const {
         return startTime;
    }
    private: 
    double startTime;
    double time; // time used to determine when its current state will be finished.
    int type; // creation = 0, processing = 1, output queue = 2, propagation = 3, input queue = 5
    int routerId; // update current router id each time pkt moves 3->5
    int destination; // destination static
    double size;
    int previous;

};

class myComparator
{
    public:
        int operator() (const Packet& p1, const Packet& p2) {
            return p1.getTime() > p2.getTime();
        }
 
};
