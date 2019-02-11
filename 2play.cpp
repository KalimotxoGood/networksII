#include <iostream> 
#include <random>
//#include "link.hpp"
#include "manip_time.hpp"
#include "router.hpp"
#include <array>
#include <vector>
int microseconds = 1;
//void DFS(int);
int visited[9];
int visite =0;
bool DFS(int, array<array<Link,5>,5>,const int);

int main()
{
    using namespace std;
//int microseconds = 0;
    int vertices = 5;
    int seed = 3; // get consistend use 'generations'
    default_random_engine generator(seed);
    uniform_real_distribution<double> distribution(0.0, 1.0);
    double num = distribution(generator);//distribution(generator);
    
    cout << "uniform generator returns: " << num << endl;// uniform number generator
// 9 vertices
    Link mylinks[vertices][vertices] ; // create the adjacency matrix of links. All initlized to '0'
    std:array<std::array<Link, 5>, 5> mylink;
    cout << mylink[0][1].getBandwidth() <<endl;
    mylink[0][1].setBD(1,1);
    mylink[1][0].setBD(1,1);
    mylink[1][3].setBD(1,1);
    mylink[2][4].setBD(1,1);
    mylink[3][0].setBD(1,1);
    mylink[3][1].setBD(1,1);
    mylink[3][4].setBD(1,1);
    mylink[4][2].setBD(1,1);
    mylink[4][3].setBD(1,1);
/* testing std:array of links */


    Router myrouters[vertices]; // create the routers corresponding to the links.
// so far we have initialized 0 edges in mylinks
    int visited[vertices]={0};
    int k = 0;
    int l = 0;

    if(DFS(0, mylink, 5) ){
        cout << "YESSS"  << endl;
     }
     else cout << "NOOO" << endl;

    //connectedLinks(&mylinks); // runs until we get a connected graph!

    for(int j=0; j<=5; j++){
        
        myrouters[0].input.push(mylink[0][j]); //pushing a link for fun. be a packet
        cout << "link[0][" << j << "] pushed" << endl;
        cout << "it has bandwidth: " << myrouters[0].input.front().getBandwidth() << endl;
        
    }
   
}

/*
Depth First Search
Takes as arguments: visited node index, adjacency matrix of links, and number of vertices (,respectively). 
Returns: true if connected, false otherwise.
Implementation technique: Used as a functor in while-loop that creates more edges while DFS returns false.

*/
// template to take size_t n in lieu of '5'
bool DFS(int i, array<array<Link,5>,5> mylinks,const int vertices){
    int j;
    visited[i]=1;
    visite++;
    cout << "-------visited: " << i << endl;
  
    for (int i =0; i <5; i++){
        for(int j =0; j<5;j++) {
            cout<< "["<<i<<"]"<<"["<<j<<"]"<< mylinks[i][j].getBandwidth() << endl;
   //         cout << "we out hee bih" <<endl;
        }
   
     }
    


     for(j=0;j<vertices;j++) 
         if(!visited[j]&&mylinks[i][j].getBandwidth()!=0)
         //cout <<"visited " << j << endl;
         {
             DFS(j, mylinks,5);
         
         }
     cout << "visite: " << visite <<endl;
    if(visite==vertices) return true;
    else return false;
/*
    nodes[i] = 1;"
    for(j=0;j<vertices;j++) DFS(j);*/
}
