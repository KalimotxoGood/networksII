#include <iostream> 
#include <random>
//#include "link.hpp"
#include "manip_time.hpp"
#include "router.hpp"
#include <array>
#include <vector>
int microseconds = 1;
//void DFS(int);

const int vertices = 150;
//int visited[vertices];
array<int,vertices> visited;
//vector<int> visited;
int visite =0;

bool DFS(int, array<array<Link,vertices>,vertices> &,const int); 
//Matrix PASSED BY REFERENCE

int main()
{
    using namespace std;
    int seed = 3; // get consistend use 'generations'
//distribution(generator);
    default_random_engine generator(seed);
    uniform_real_distribution<double> distribution(0.0, 1.0);
    double num = distribution(generator);
    
    cout << "uniform generator returns: " << num << endl;

// create the adjacency matrix of links. All initlized to '0'
    array<array<Link, vertices>, vertices> mylink;
    Router myrouters[vertices]; 
// create the routers corresponding to the links.
// so far we have initialized 0 edges in mylinks
    int visited[vertices]={0};
    int k = 0;
    int l = 0;

   // if(DFS(0, mylink, 5)) cout << "YESSS"  << endl;
   // else cout << "NOOO" << endl;
    while( !DFS(0, mylink, vertices)) {
        cout << "unconnected" << endl;
        for(int newLinks = 0; newLinks<vertices/2; newLinks++){
            cout <<"....making new links" << endl;
            int j = (rand()%vertices);
            int k =(rand()%vertices) ;
            if (j==k) continue;
            mylink[j][k].setBD(1,1);
            mylink[k][j].setBD(mylink[j][k].getBandwidth(), mylink[j][k].getDelay());
       }
    }


    for (int i =0; i <vertices; i++){
        for(int j =0; j<vertices;j++) {
            cout<< "["<<i<<"]"<<"["<<j<<"]"<< mylink[i][j].getBandwidth() << endl;
        }
   
     }

/*
    for(int j=0; j<=vertices; j++){
        
        myrouters[0].input.push(mylink[0][j]); //pushing a link for fun. be a packet
        cout << "link[0][" << j << "] pushed" << endl;
        cout << "it has bandwidth: " << myrouters[0].input.front().getBandwidth() << endl;
        
    }
*/
//cout <<"here"<<endl;
//    cout << DFS(0,mylink,5) << endl;
}

/*
Depth First Search
Takes as arguments: visited node index, adjacency matrix of links, and number of vertices (,respectively). 
Returns: true if connected, false otherwise.
Implementation technique: Used as a functor in while-loop that creates more edges while DFS returns false.

*/
// template to take size_t n in lieu of '5'
bool DFS(int i, array<array<Link,vertices>,vertices> &mylinks,const int vertices){
    int j;
//    cout << "visited.size(): "<<visited.size() << endl;
    visited[i]=1;

    for(j=0;j<vertices;j++)  {
         if(!visited[j]&&mylinks[i][j].getBandwidth()!=0)
             DFS(j, mylinks,vertices);
    }
    visite =0;
    for(int j = 0; j < vertices; j++)
        if(visited[j]!=0) visite++;

    if(visite==vertices){cout << "connected" <<endl; return true;}
    else return false;
}
