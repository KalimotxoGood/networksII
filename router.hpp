// router.cpp
// router class
#ifndef LINK
#define LINK
#include "link.hpp"
#endif
#include <iostream>
#include <string>
#include <queue>
#include <array>
#include <limits.h>
const int vertices = 150;
using namespace std;

void dijkstra(array<array<Link,vertices>, vertices> &, const int src, int *);

class Router{


public:
    int* connections; // use the nextHopTable to determine interface to push the packet into
                      //E.G. for a destination 5,
                      // router1.connections[nextHopTable[5]] will reference the input queue
                      // for its interface towards destination 5.
/*
For each adjacent node, create an output/input queue.
*/
    char* id;
    //queue<sdPKT> input; // implement this using std::queue
    //queue<sdPKT> output; // queue of source-destination packets (not int's)
    
    int nextHopTable[vertices];
    double lastTimeToBeServiced;
    
    void setHopTable(array<array<Link,vertices>,vertices> &mylinks,int id){
        dijkstra(mylinks, id, nextHopTable);
    }
};



int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < vertices; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}


void dijkstra(array<array<Link,vertices>,vertices> &mylinks, const int src, int *nextHop){
 
// distnace from src to dist[i]   
    int shortestPathTable[vertices]; //
// keeping track of parent nodes. this is the True routing Table
    int parent[vertices];
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
    //int nextHop[vertices];
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
        nextHop[currentNode] = previous;
        p = previous;
        if(parent[previous]==p) p = src; // parent[src]==INT_MAX will cause the break in loop.
    
        }
    currentNode++;
    } nextHop[src]=INT_MAX;
    cout << "nextHop list is: ";
    for(int i=0;i<vertices;i++) {
        cout << nextHop[i]<< ", ";
    }
    

}
