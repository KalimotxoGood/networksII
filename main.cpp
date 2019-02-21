#include <iostream> 
#include <random>
#include <string>
#include <iomanip>
#include <map>
#include <limits.h>
//#include "link.hpp"
#include "manip_time.hpp"
#include "router.hpp"
#include "sourceDestinationPairs.hpp"
#include <array>
#include <vector>
int microseconds = 1;
//void DFS(int);

using namespace std;
//const int vertices = 5;
//int visited[vertices];
array<int,vertices> visited;
//vector<int> visited;
int visite =0;


void dijkstra(array<array<Link,vertices>, vertices> &, const int src, int *);
bool DFS(int, array<array<Link,vertices>,vertices> &,const int); 
//Matrix PASSED BY REFERENCE

int main()
{
    int seed = 12; // seed value for random number generators
//distribution(generator);
    default_random_engine generator(seed);
    uniform_real_distribution<double> distribution(0.0, 1.0);
    poisson_distribution<int> pdistribution(5);
    double num = distribution(generator);
    srand(seed);
// create the adjacency matrix of links. All initlized to '0'
    array<array<Link, vertices>, vertices> mylink;
    Router myrouters[vertices]; 
    /* While DFS returns an unconnected graph, connect hosts with links by (numberOfHosts/2).
   DFS takes an adjacency matrix (mylink) by reference. mylink edges are updated such that 
   the ingress/egress propagation/bandwidth numbers are symetrical as that is how we designed our network.
*/

    int k = 0;
    int l = 0;
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
/* At this point we have a connected graph. For each router in the graph we reference it via its
index as an "id" number in the myrouters[vertices] array. We call setHopTable for each router to set its routing table with the mylink matrix.
*/
    for(int id=0; id < vertices; id++) { 
        myrouters[id].setHopTable(mylink, id);
    }
/*
   Now we generate a list of src/dest pairs generate packets

--This is made by by choosing two end point ID's and creating packets accordingly to it.
Implemented via creating an array of size 20 of src/dest pair structures.
Packets are generated accordingly in a Poisson distribution by each of the source destination pairs(TODO: nlgn search if repeat.)
*/
    const int numberOfPairs = 20;
    array<SDpair, numberOfPairs> mySDpairs;
    for(int i = 0; i < numberOfPairs; i++) { // generate 20 src/dest pairs
        int src = 1;
        int dest = 1;
        while(src == dest){//randomly generated integers do not cause an SD pair to send to itself
        src = (rand()%vertices) + 1; //vertices are the number of nodes. Assumed to be 150
        dest = (rand()%vertices) + 1; 
        }
        //if(mySDpairs[i].getSource() == mySDpairs[i-1].getSource()) {--i; cout <<"YOOOOOOO";break;}
        mySDpairs[i].setSD(src,dest); // the structure holds the pairs
        cout << "set mySDpairs["<<i<<"] to : "<<mySDpairs[i].getSource() <<"/"<< mySDpairs[i].getDestination() << endl;
   
    }

/* Now that we Have Set Up The Network, it is time to run the simulation: 
*/  
 
    for(int seconds = 0; seconds < 10; seconds++) {     
    


/*
2. packets go into a min heap (priority queue) based on time to be calculated acordingly.

--While the packets are created, they get put into the min heap where they are then ordered in
such a way that they will be served in order of time through the iterations.
For the number of pairs, 
*/

int yes = 0;
int no = 0;
        for(int i =0; i<numberOfPairs; i++) {
            cout << "--------" << i << "------------" <<endl;
            int number = pdistribution(generator); // according to this poisson-number, an SD pair
                                                 // generates a packet.
            cout << "number is: " << number << endl;
            if(number <= 5) {// gen pkt
// 1. Get the location of source and its corresponding destination.
                int src = mySDpairs[i].getSource();
                int dest = mySDpairs[i].getDestination();
// 2. Create the packet and push it to the heap.
                
cout << src << " and " << dest << endl;
               
      yes++;}
            else{ // dont gen pkt
                
                
no++;       }
        }
cout << "yes is: " << yes << endl;

cout << "no is: " << no << endl;
       /*
// how many of these to generate per second??
        int number = pdistribution(generator);
        if(number < 3) {
cout << "3" << endl;
           
        }
        else if(number <= 5) {
cout << "5" << endl;
        }
        else if(number <= 7) {
cout << "7" << endl;
        } 
        else if(number <=9) {
cout << "9" << endl;
        }
        else if( number > 10) {
        cout << "10" << endl;
        }*/
    }// End For-Loop Outer Simulation
/*
3. handle each packet accordingly

	- heap.look() at type, whether it is in creation, processing, or propagation
		-if at creation, move to outputQ of rId
		-if at processing, move to outputq
		-if at outputq move to propagation
		-if at propagation move to input q
	- each time the packet is handled, we update its time until completion accordingly.
		
*/
cout << "end" << endl;
} // end main


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
