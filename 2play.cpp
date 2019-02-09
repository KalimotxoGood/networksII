#include <iostream> 
#include <random>
//#include "link.hpp"
#include "manip_time.hpp"
#include "router.hpp"
#include <vector>
int microseconds = 1;

int main()
{
    using namespace std;
//int microseconds = 0;
    int vertices = 9;
    int seed = 3; // get consistend use 'generations'
    default_random_engine generator(seed);
    uniform_real_distribution<double> distribution(0.0, 1.0);
    double num = distribution(generator);//distribution(generator);
    
    cout << "uniform generator returns: " << num << endl;// uniform number generator
// 9 vertices
    Link mylinks[vertices][vertices] ; // create the adjacency matrix of links. All initlized to '0'
    Router myrouters[vertices]; // create the routers corresponding to the links.
// so far we have initialized 0 edges in mylinks
    int visited[vertices]={0};
    int k = 0;
    int l = 0;
    
    while(!visited[l]&&mylinks[k][l].getBandwidth()!=0){
        cout << k << endl;
        visited[k] = 1;
        for(l=0;l<vertices;l++) {
            if(!visited[l]&&mylinks[k][l].getBandwidth()!=0) {
                k = l;
                break;
            }
        } 
        break;
    }
     
    //connectedLinks(&mylinks); // runs until we get a connected graph!

    for(int j=0; j<=5; j++){
        
        myrouters[0].input.push(mylinks[0][j]); //pushing a link for fun. be a packet
        cout << "link[0][" << j << "] pushed" << endl;
        cout << "it has bandwidth: " << myrouters[0].input.front().getBandwidth() << endl;
        
    }
   
}
