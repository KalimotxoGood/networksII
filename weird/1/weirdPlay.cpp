#include <iostream> 
#include <random>
//#include "link.hpp"
#include "manip_time.hpp"
#include "router.hpp"
#include <array>
#include <vector>
int microseconds = 1;
//void DFS(int);


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
    std:array<std::array<Link, 9>, 9> mylink;
    cout << mylink[0][1].getBandwidth() << endl;
/* testing std:array of links */
    for (int i =0; i <8; i++){
        for(int j =0; j<8;j++) {
            cout<< "["<<i<<"]"<<"["<<j<<"]"<< mylink[i][j].getBandwidth() << endl;
        }
    }


    Router myrouters[vertices]; // create the routers corresponding to the links.
// so far we have initialized 0 edges in mylinks
    int visited[vertices]={0};
    int k = 0;
    int l = 0;

//    DFS(0);

    //connectedLinks(&mylinks); // runs until we get a connected graph!

    for(int j=0; j<=5; j++){
        
        myrouters[0].input.push(mylink[0][j]); //pushing a link for fun. be a packet
        cout << "link[0][" << j << "] pushed" << endl;
        cout << "it has bandwidth: " << myrouters[0].input.front().getBandwidth() << endl;
        
    }
   
}

/*
void DFS(int i, array nodes[], int vertices){
    int j;
    cout << i << endl;
    nodes[i] = 1;
    for(j=0;j<vertices;j++) DFS(j);
}
}
*/

