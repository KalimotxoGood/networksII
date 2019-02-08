#include <iostream> 
#include <random>
//#include "link.hpp"
#include "manip_time.hpp"
#include "router.hpp"
int microseconds = 1;

int main()
{
    using namespace std;
//int microseconds = 0;
    int seed = 3; // get consistend use 'generations'
    default_random_engine generator(seed);
    uniform_real_distribution<double> distribution(0.0, 1.0);
    double num = distribution(generator);//distribution(generator);
    
    cout << "uniform generator returns: " << num << endl;// uniform number generator
    Link mylinks[9][9] ; // create the adjacency matrix of links. All initlized to '0'
    Router myrouters[9]; // create the routers corresponding to the links.
   
       
 
    //connectedLinks(&mylinks); // runs until we get a connected graph!

    for(int j=0; j<=5; j++){
        
        myrouters[0].input.push(mylinks[0][j]); //pushing a link for fun. be a packet
        cout << "link[0][" << j << "] pushed" << endl;
        cout << "it has bandwidth: " << myrouters[0].input.front().getBandwidth() << endl;
        
    }
   
}
