#include <iostream> 
#include <random>
#include <fstream>
#include <string>
#include <iomanip>
#include <map>
#include <limits.h>
//#include "link.hpp"
#include "manip_time.hpp"
#include "packet.hpp"
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
int success = 0;

//void dijkstra(array<array<Link,vertices>, vertices> &, const int src, int *);
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
        for(int newLinks = 0; newLinks<(vertices/15); newLinks++){
            cout <<"....making new links" << endl;
            int j = (rand()%vertices);
            int k =(rand()%vertices) ;
            if (j==k) continue;
            mylink[j][k].setBD(1,1); //set Delay and then set BD
            mylink[k][j].setBD(mylink[j][k].getBandwidth(), mylink[j][k].getDelay());
       }
    }
    for(int i = 0; i < vertices; i++) {
        for(int j =0; j< vertices; j++) {
            cout << "mylink["<<i<<"]["<<j<<"] : "<<mylink[i][j].getDelay() << endl;
        }
     }
/*
Write the graph into the desired file format
*/
    int links = 0;
    for(int x = 0; x < vertices; x++)
    {
        for(int y = 0; y < vertices; y++)
        {
            if (mylink[x][y].getDelay() > 0)    //if there is a connection add one to link count
            {cout << links << endl;
             cout << "mylink["<<x<<"]["<<y<<"] : "<<mylink[x][y].getDelay() << endl;
                links++;               //to put number of links in file
            }
        }
    }
    links = links/2; // divide by two because the links are bidirectional
cout << links << "linkS" << endl;
//return 0;
//cout << "links: " << links << endl;
    std::ofstream myfile;
    myfile.open("graph.txt");
    if(myfile.is_open())
    {
        myfile << vertices << " " << links << "  \n";
        for(int i = 0; i < vertices; i++)
        {
            for(int j = 0; j < vertices; j++)
            {
                if (mylink[i][j].getDelay() == 0.0)   //myLink.getDelay()()
                {
                    continue;
                }

                else {
                    myfile << i << " " << j << "  \n";
                }
            }
        }
        myfile.close();
    }
    else
    {
        std::cerr << "didn't write" << std::endl;
    }
     
/* At this point we have a connected graph. For each router in the graph we reference it via its
index as an "id" number in the myrouters[vertices] array. We call setHopTable for each router to set its routing table with the mylink matrix.
In each call to setHopTable, Dijkstras is run!
*/
    for(int id=0; id < vertices; id++) { 
        myrouters[id].setHopTable(mylink, id);
    }
/* set the service rate for each router according to an exponential distribution at mu = 1.0
*/
    exponential_distribution<double> exdistribution(1.0);
    
    for(int id=0; id< vertices; id++){
        double rate = exdistribution(generator);
        myrouters[id].setServiceRate(rate);
//       cout << "myrouters["<<id<<"].serviceRate is: " << myrouters[id].serviceRate << endl;
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


// event handler priority queue to store the packets to be serviced
    
    priority_queue <Packet, vector<Packet>, myComparator> eventHeap;
/* Now that we Have Set Up The Network, it is time to run the simulation: 
Below is the outer loop of the simulation set for 1000 seconds.
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
        for(int i =0; i<numberOfPairs; i++) { // for all sources that gen packets follow a poisson distribution for generating packets.
            int number = pdistribution(generator); // according to this poisson-number, an SD pair
                                                 // generates a packet.
            if(number <= 5) { // mu is 5 so it is more than less often that a packet is generated.
// 1. Get the location of source and its corresponding destination.
                int rid = mySDpairs[i].getSource();
                int dest = mySDpairs[i].getDestination();
                int type = 0;
                double time = myrouters[rid].serviceRate + seconds;
               
                double pktSize = distribution(generator); // pktSize generated at uniform dist.

//cout << myrouters[rid].serviceRate << " + " << seconds << "= " << time << endl;
// 2. Create the packet via its constructor and push it to the heap.
                eventHeap.push(Packet(time, rid, dest, type, pktSize));
                //cout << "eventHeap.top().getTime();" << eventHeap.top().getTime()<<endl;
            }
            else{ // dont gen pkt
            }
        } //end generating packet loop
        
/*Handle the packets that have been added to the eventHeap until this current 'second'
*/
   cout << "-------------" << seconds <<"--------" << endl;
        while(eventHeap.top().getTime() < seconds){
            if(eventHeap.top().getType() == 0) {
cout <<"type 0 handling" << endl;
                int pktDest = eventHeap.top().getDest();
                int curr = eventHeap.top().getRID();
                int queue = myrouters[curr].getOutQueue(pktDest); //interface number is returned as queue
                if(queue == 0) { cout << "DROPPED" << endl;}
                else {
                    myrouters[curr].outputQueue[queue].push(1); //index at the interface number 'queue'
                }
                int time = seconds + myrouters[curr].serviceRate;
                int type = 2;
                double pktSize = eventHeap.top().getSize();
                eventHeap.pop();
                eventHeap.push(Packet(time, curr, pktDest, type,pktSize ));
                
                eventHeap.pop();
            } 
            if(eventHeap.top().getType() == 1) {

                eventHeap.pop();
            } 
            if(eventHeap.top().getType() == 2) {
cout <<"type 2" << endl;
                int pktDest = eventHeap.top().getDest(); // get pkt dest
                int curr = eventHeap.top().getRID(); // current router location
                int nextHop = myrouters[curr].nextHopTable[pktDest];//get nextHop for band/delay access
cout <<"source/dest is: " << curr<< "/" <<pktDest << endl;
                double pktSize = eventHeap.top().getSize();
//cout <<"pkt size is: " << pktSize << endl;
                double bandwidth = mylink[curr][nextHop].getBandwidth();
                double delay = mylink[curr][nextHop].getDelay();
//cout <<"mylink returns bandwidth: " << bandwidth << " and delay " << delay << endl;
                double time = pktSize/bandwidth + delay + seconds;
cout <<"time is : " << time << endl;
/* At this point the packet has left the output interface corresponding to its connected link and will now be popped out of the queue */
cout << "next hop" << nextHop << endl;
                myrouters[curr].outputQueue[nextHop].pop(); //popped out of queue
                eventHeap.pop(); // popped out of eventHeap handler
            } 
            if(eventHeap.top().getType() == 3) {
cout << "event 3" << endl;
                //double processTime = eventHeap.top().getTime();
                int pktDest = eventHeap.top().getDest(); // get pkt dest
                int curr = eventHeap.top().getRID(); // current router location
                int nR = myrouters[curr].nextHopTable[pktDest]; // get next hop router
               // check if input queue of next router is full. function will return 0 ifso
                int queue = myrouters[nR].getQueue(pktDest);
                if(queue == 0 ) { cout << "DROPPED" << endl;} 
                else if(queue == 777) {cout << "SUCCESS!" << success++;}
                else {cout << "else condition" << endl;
                    myrouters[nR].inputQueue[curr].push(1); // packet size does not need to be mentioned here since it's saved in the packet struct.
                }
                double time = seconds + myrouters[nR].inputQueue[curr].size() * myrouters[nR].serviceRate;
                int type = 4;
                double pktSize = eventHeap.top().getSize();

                eventHeap.pop();
                eventHeap.push(Packet(time, nR, pktDest, type, pktSize));

            } 
            if(eventHeap.top().getType() == 4) {
                eventHeap.pop();
            } 

   
        } 










        
    
 /*
3. handle each packet accordingly

	- heap.look() at type, whether it is in creation, processing, or propagation
		-if at creation, move to outputQ of rId 0
		-if at processing, move to outputq 1 // 0 and 1 might be same
		-if at outputq move to propagation 2
		-if at propagation move to input q 3
                -if at inputq move to processing 4
	- each time the packet is handled, we update its time until completion accordingly.
		
*/





    }// End For-Loop Outer Simulation
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
