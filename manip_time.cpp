// manip_time.cpp
// functions to manip time

#include <iostream>
#include "manip_time.hpp"
using namespace std;

bool ms_to_sec(int microseconds,int seconds) { // seconds counter
    
    if(microseconds%1000000==0){
        seconds++;
        cout << (double)microseconds/1000000 << " seconds" << endl;
    }
    
    return true;

}
