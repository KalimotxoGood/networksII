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
    int* connections;
    char* id;
    queue<Link> input; // implement this using std::queue
    queue<int> output; // queue of packets (not int's)
    // table

};
