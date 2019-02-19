#include <iostream> 
#include <random>
#include <limits.h>
//#include "link.hpp"
#include "manip_time.hpp"
#include "router.hpp"
#include <array>
#include <vector>
int microseconds = 1;
//void DFS(int);

using namespace std;
const int vertices = 5;
//int visited[vertices];
array<int,vertices> visited;
//vector<int> visited;
int visite =0;


void dijkstra(array<array<Link,vertices>, vertices> &, const int src, int *);
bool DFS(int, array<array<Link,vertices>,vertices> &,const int); 
//Matrix PASSED BY REFERENCE

int main()
{
    int seed = 3; // get consistend use 'generations'
//distribution(generator);
    default_random_engine generator(seed);
    uniform_real_distribution<double> distribution(0.0, 1.0);
    double num = distribution(generator);
    
    cout << "uniform generator returns: " << num << endl;

// create the adjacency matrix of links. All initlized to '0'
    array<array<Link, vertices>, vertices> mylink;
    Router myrouters[vertices]; 
    //int visited[vertices]={0}; // used in DFS
    int k = 0;
    int l = 0;
/* While DFS returns an unconnected graph, connect hosts with links by (numberOfHosts/2).
   DFS takes an adjacency matrix (mylink) by reference. mylink edges are updated such that 
   the ingress/egress propagation/bandwidth numbers are symetrical as that is how we designed our network.
*/ 
    while( !DFS(0, mylink, vertices)) {
        cout << "unconnected" << endl;
        for(int newLinks = 0; newLinks<vertices/2; newLinks++){
            cout <<"....making new links" << endl;
            int j = (rand()%vertices);
            int k =(rand()%vertices) ;
            if (j==k) continue;
            mylink[j][k].setBD(1,1); //set Delay and then set BD
            mylink[k][j].setBD(mylink[j][k].getBandwidth(), mylink[j][k].getDelay());
       }
    }


/* To delete! this just prints out the vertices..
*/
    for (int i =0; i <vertices; i++){
        for(int j =0; j<vertices;j++) {

            //cout<< "["<<i<<"]"<<"["<<j<<"]"<< mylink[i][j].getBandwidth() << "\t";
            cout<< "["<<i<<"]"<<"["<<j<<"]"<< mylink[i][j].getDelay() << endl;
        }
   
    }
/* To delete! This is just a test to run dijkstras with node-0 in main(). 
We run dijkstra on every router to get its routing table.
*/  

    int sTable[vertices];
    dijkstra(mylink, 0,sTable);
    cout << "sTable in main is" << endl;
    for(int i =0; i< vertices; i++){
        cout<< sTable[i] << " ";
    } cout << "end" << endl;

/*  This section creates the sTables for the routers
    
*/
    
}

int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
        
    for (int v = 0; v < vertices; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
        
    return min_index;
}

void dijkstra(array<array<Link,vertices>,vertices> &mylinks, const int src, int *sTable){
    int parent[vertices]; // 2-19
// distnace from src to dist[i]   
    int shortestPathTable[vertices]; //
// keeping track of parent nodes. this is the True routing Table
    //int parent[vertices];
    bool visitedsta[vertices]; // visitedsta[i] will be true if vertex i is finalized as shortest distance to src
    
    for (int i=0; i<vertices; i++)
        shortestPathTable[i]= INT_MAX, visitedsta[i] = false;
    
// Distance of source vertex from itself is always 0.
    shortestPathTable[src] = 0;
   //!!! parent[src]= INT_MAX;
// Find shortest path for all vertices
    for (int count=0; count<vertices-1; count++)
    {
         // Pick the minimum distance vertex from the set of vertices not 
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(shortestPathTable, visitedsta);
        // Then, mark the picked vertex u as true;
        visitedsta[u]=true;
        
        
        // Update shortestPathTable value of the adjacent vertices of u.
        for (int v=0; v< vertices; v++){

            int val = mylinks[v][shortestPathTable[u]].getDelay();
            if(!visitedsta[v] && mylinks[u][v].getDelay()!=0 && shortestPathTable[u] != INT_MAX
                && (val + mylinks[u][v].getDelay()) < shortestPathTable[v]) {
cout << "Delay is: " << mylinks[u][v].getDelay()<< endl;
                
                shortestPathTable[v] = shortestPathTable[u] + mylinks[u][v].getDelay();
                if(u==src) parent[v] = v; // previous is the src then set the parent of current
                                          //index (u) to itself(v)b/c the src must only know about 
                                          // adjacent nodes to reach any node v
                else parent[v] = u; //setting parent of current index to its previous
                
            }
        }   
       
        
    }
    parent[src]=INT_MAX;
    for(int p = 0; p < vertices; p++) {
        cout << "This is the parent["<<p<<"]: " << parent[p] << " ";
        cout << endl;
    }
// At this point, parent[] holds the backtracking of nodes through their parents.
// Now, we use parent to generate nextHop[] which develops the "switching fabric" of
// each router (node). 
   // int nextHop[vertices];
    int currentNode=0;
    int previous=0;
    while(currentNode<vertices) {
        if(parent[currentNode]==INT_MAX) {
            currentNode++;
            continue;
        }
        int p = currentNode;
        while(parent[p] != INT_MAX) {
        
        previous = parent[p];
        sTable[currentNode] = previous;
        p = previous;
        if(parent[previous]==p) p = src; // parent[src]==INT_MAX will cause the break in loop.
    
        }
    currentNode++;
    } sTable[src]=INT_MAX;
    cout << "sTable list is: ";
    for(int i=0;i<vertices;i++) {
        cout << sTable[i]<< ", ";
    }
    

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
