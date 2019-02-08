#include <iostream>
#include <random>
using namespace std;

default_random_engine generator;
uniform_real_distribution<double> mbps(0,1000000);
uniform_real_distribution<double> ten_secs(0,10);

struct link
{
   // double bandwidth;
    //double delay;
    
    double bandwidth = 0;// = mbps(generator);
    double delay = 0; //= ten_secs(generator);
   
    // generate outside    

};



