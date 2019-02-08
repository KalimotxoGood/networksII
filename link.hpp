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

    double bandwidth = mbps(generator);
    double delay = ten_secs(generator);
   
     
    

};



