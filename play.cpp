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

    default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0, 1.0);

    double num = distribution(generator);//distribution(generator);

    cout << "uniform generator returns: " << num << endl;// uniform number generator
    link mylinks[9][9] ; //
    
    //cout << "mylinks[0][0]" << mylinks[0] << endl;
    Router myrouters[9];

    for(int j=0; j<=5; j++){
        
        myrouters[0].input.push(mylinks[0][j]); //pushing a link for fun. be a packet
    }
   
    while(myrouters[0].input.size() != 0 ){ // checking that the routers are created and pop works
                                            // for queue.
        cout << "myrouters[0]: " << myrouters[0].input.front().bandwidth << " popped. " << endl;
                                                  // pops a link's bandwidth.
        myrouters[0].input.pop();
        
    }
    

    for(int i = 0; i < 9; i++){ //will print garb if exceeds size
     cout << "link " << i << " has bandwidth: " << mylinks[0][i].bandwidth << endl;
    }

    int i=0; 
    int seconds=0;
 cout << microseconds << endl;   /*
    while(microseconds <= 1000000000) { //1000 seconds (16.6 mins)
        ms_to_sec(microseconds,seconds);
         
        
        
        microseconds++;
    }  */
}
