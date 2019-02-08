#include <iostream> 
#include <random>
#include "link.hpp"
#include "manip_time.hpp"
int microseconds = 1;

int main()
{
    using namespace std;


//int microseconds = 0;

    default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0, 1.0);

    double num = distribution(generator);//distribution(generator);

    cout << "uniform generator returns: " << num << endl;// uniform number generator
    link mylinks[150];
/*
    for(int i = 0; i< 150; i++){
     cout << "link " << i << " has bandwidth: " << mylinks[i].bandwidth << endl;
    }*/
    int i=0; 
    int seconds=0;
 cout << microseconds << endl;   
    while(microseconds <= 1000000000) { //1000 seconds (16.6 mins)
        ms_to_sec(microseconds,seconds);
         
        
        
        microseconds++;
    }  
}
