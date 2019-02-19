// router.cpp
// router class
#ifndef LINK
#define LINK
#include "link.hpp"
#endif
#include <iostream>
#include <string>
#include <queue>
using namespace std;


class Router{


public:
    int* connections; // use the nextHopTable to determine interface to push the packet into
                      //E.G. for a destination 5,
                      // router1.connections[nextHopTable[5]] will reference the input queue
                      // for its interface towards destination 5.
/*
For each adjacent node, create an output/input queue.
*/
    char* id;
    //queue<sdPKT> input; // implement this using std::queue
    //queue<sdPKT> output; // queue of source-destination packets (not int's)
    
    int nextHopTable[150];
    double lastTimeToBeServiced;

};
