#include <iostream> 
#include <random>
#include <fstream>
#include <string>
#include <iomanip>
#include <map>
#include <limits.h>
//#include "link.hpp"
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
double success = 0;
double packetgen = 0;
double dropped[vertices]={-1.0}; // counter for drops for each router
double transmission = 0.0;
double totalTransmissions = 0.0;
double maxComplete = 0.0;
double minComplete = 100.0; // intialize minimum to large number to allow for condition to sink.
double totalComp = 0.0;
double averageComplete = 0.0;


//void dijkstra(array<array<Link,vertices>, vertices> &, const int src, int *);
bool DFS(int, array<array<Link,vertices>,vertices> &,const int); 
//Matrix PASSED BY REFERENCE

int main(int argc, char* argv[])
{
    
    int seed = atoi(argv[1]); // seed value for random number generators
    if(seed == 20) seed =19; //for some reason only seed of 20 causes unsuspected behavior...
    string filename = argv[2];
    
cout << filename <<endl;
   
    default_random_engine generator(seed);
    uniform_real_distribution<double> distribution(0.0, 1.0);
    poisson_distribution<int> pdistribution(5);
    double num = distribution(generator);
    srand(seed);
    array<array<Link, vertices>, vertices> mylink;
    Router myrouters[vertices]; 


    ifstream f(filename.c_str());
    if(f.good()){
       
       cout <<"Graph found will segfault if obscene size, however." <<endl;
       //return 0;
    
// create the adjacency matrix of links. All initlized to '0'

    int p = 2;
    int q = 3;
    int r = 0;
    int n = 0;
    int lines = 0;
    int arr[vertices];
    ifstream File;
    File.open(filename);
    while(!File.eof())
    {
        File >> arr[n];             //puts each integer into an array
        n++;
    }
    File.close();
    r = arr[0];
    lines = arr[1];
    
      //initialize graph with size of first int given from file (r)
    for(int x = 0; x < r; x++)
    {
        for(int y = 0; y < r; y++)
        {
            mylink[x][y].setBD(0,0);           //set every part of matrix to 0 to simulate empty graph
        }
    }
    for(int i = 0; i < n; i++)
    {
        mylink[arr[p]][arr[q]].setBD(1,1);       //assign p and q connections from file
        if (p < n && q < n - 1)
        {
            p = p+2;           
            q = q+2;
        }
    }

    for(int i=0; i < r; i++) {
        for(int j = 0; j < r; j++) {
            cout << "providedGraph[" <<i<<"]["<<j<<"]"<<endl;
        }
    }
    if(DFS(0,mylink,r)){
        cout << "\n-------------------------------------\n\n"<<endl;
        cout << "-----------RESULT of GRAPH------------" <<endl;
        cout<< "the graph provided is connected" << endl;

        cout << "\n-------------------------------------\n\n"<<endl;
    }
    else {
        cout << "the graph is not connected" << endl;
    }
    if(r<150) {
        cout << "The graph submitted is not of size 150 nodes. Please try again with a graph of 150 nodes"<<endl;

        cout << "\n-------------------------------------\n\n"<<endl;
        cout << "Exiting...." <<endl;
    }
    }
    /* While DFS returns an unconnected graph, connect hosts with links by (numberOfHosts/2).
   DFS takes an adjacency matrix (mylink) by reference. mylink edges are updated such that 
   the ingress/egress propagation/bandwidth numbers are symetrical as that is how we designed our network.
*/
    int k = 0;
    int l = 0;
   // if(
    //cout << "The graph inputted returns" << DFS(mylink2) << "that it is connected." << endl;*/
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
           // cout << "mylink["<<i<<"]["<<j<<"] : "<<mylink[i][j].getDelay() << endl;
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
            {//cout << links << endl;
           //  cout << "mylink["<<x<<"]["<<y<<"] : "<<mylink[x][y].getDelay() << endl;
                links++;               //to put number of links in file
            }
        }
    }
    links = links/2; // divide by two because the links are bidirectional
//return 0;
//cout << "links: " << links << endl;
    std::ofstream myfile;
    if(f.good()){
        myfile.open(filename);
    }
    else myfile.open("graph.txt");
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
        src = (rand()%vertices); //vertices are the number of nodes. Assumed to be 150
        dest = (rand()%vertices); 
        }
        //if(mySDpairs[i].getSource() == mySDpairs[i-1].getSource()) {--i; cout <<"YOOOOOOO";break;}
        mySDpairs[i].setSD(src,dest); // the structure holds the pairs
   
    }


// event handler priority queue to store the packets to be serviced
    
    priority_queue <Packet, vector<Packet>, myComparator> eventHeap;
/* Now that we Have Set Up The Network, it is time to run the simulation: 
Below is the outer loop of the simulation set for 1000 seconds.
*/  
    for(int seconds = 0; seconds < 1000; seconds++) {     
/*
packets go into a min heap (priority queue) based on time to be calculated acordingly.

--While the packets are created, they get put into the min heap where they are then ordered in
such a way that they will be served in order of time through the iterations.
For the number of pairs, 
*/

        for(int i =0; i<numberOfPairs; i++) { // for all sources that gen packets follow a poisson distribution for generating packets.
            int number = pdistribution(generator); // according to this poisson-number, an SD pair
                                                 // generates a packet.
            if(number <= 5) { // mu is 5 so it is more than less often that a packet is generated.
// 1. Get the location of source and its corresponding destination.
                int rid = mySDpairs[i].getSource();
                int dest = mySDpairs[i].getDestination();
                int type = 0;
                packetgen++;
                double pktSize = distribution(generator); // pktSize generated at uniform dist.
                double time = (pktSize/myrouters[rid].serviceRate) + seconds;
               

//cout << myrouters[rid].serviceRate << " + " << seconds << "= " << time << endl;
// 2. Create the packet via its constructor and push it to the heap.
                eventHeap.push(Packet(time, rid, dest, type, pktSize, rid, (double)seconds));
                //cout << "eventHeap.top().getTime();" << eventHeap.top().getTime()<<endl;
            }
            else{ // dont gen pkt
            }
        } //end generating packet loop
        
/*Handle the packets that have been added to the eventHeap until this current 'second'
*/
        while(eventHeap.top().getTime() < seconds){

            if(eventHeap.top().getType() == 0) {// if at creation, move to outputQ of rId 
                double start = eventHeap.top().getStart();
                int pktDest = eventHeap.top().getDest();
                int curr = eventHeap.top().getRID();
                int queue = myrouters[curr].getOutQueue(pktDest); //interface number is returned as queue

cout <<"Finished processing. at Router:  " << curr << ". Going to output queue interface towards: "<<pktDest << " via hop: " << queue<< endl;
                if(queue == 0) { 
                    cout << "DROPPED at output queue of router "<< curr << endl;
                    dropped[curr]++;
                    if(!eventHeap.empty()) eventHeap.pop();
                    continue;
                }
                else {
                    myrouters[curr].outputQueue[queue].push(1); //index at the interface number 'queue'/ pushed to output queue!
                }
                int time = seconds + myrouters[curr].serviceRate;
                int type = 2;
                double pktSize = eventHeap.top().getSize();
                if(!eventHeap.empty()) eventHeap.pop();
                eventHeap.push(Packet(time, curr, pktDest, type,pktSize,curr,start ));
                
               // eventHeap.pop();
            } 

            if(eventHeap.top().getType() == 1) {// if at processing, move to outputQ

                double start = eventHeap.top().getStart();
                int pktDest = eventHeap.top().getDest();
                int curr = eventHeap.top().getRID();

                if(curr==pktDest) {  // redundant accept handled
                     // cout << "SUCCESS!" << endl;
                      //success++;
                      double compTime = eventHeap.top().getTime()-eventHeap.top().getStart();
                      if(compTime > maxComplete) maxComplete = compTime;
		      if( (compTime!=0) && compTime < minComplete) minComplete = compTime;
                      totalComp += compTime; 
                      if(!eventHeap.empty()) eventHeap.pop();
                      continue;}

                int queue = myrouters[curr].getOutQueue(pktDest); //interface number is returned as queue
                
                cout <<"Finished processing. at Router:  " << curr << ". Going to output queue interface towards: "<<pktDest<< " via hop: " << queue<< endl;
                if(queue == 0) { 
                    cout << "DROPPED at output queue of router " << curr << endl;
                    dropped[curr]++;
                    if(!eventHeap.empty()) eventHeap.pop();
                    continue;
                }
                else if(queue == 777) {  //redundant accept logic handled
                   // cout<< "SUCCESS!" <<endl; 
                   // success ++;
                   double compTime = eventHeap.top().getTime()-eventHeap.top().getStart();
                     if(compTime > maxComplete) maxComplete = compTime;
                     if( (compTime!=0) && compTime < minComplete) minComplete = compTime;
                     totalComp += compTime; 
                }  //gaurd: if for some reason the propagation (scenario type 3) doesn't catch a success.
                else {
                    myrouters[curr].outputQueue[queue].push(1); //index at the interface number 'queue'/ pushed into output queue!
                }
                int time = seconds + myrouters[curr].serviceRate;
                int type = 2;
                double pktSize = eventHeap.top().getSize();
                if(!eventHeap.empty()) eventHeap.pop();
                eventHeap.push(Packet(time, curr, pktDest, type,pktSize,curr, start ));
            } 

            if(eventHeap.top().getType() == 2) {// if at outputq move to propagation 2
                totalTransmissions++;
                double start = eventHeap.top().getStart();
                int pktDest = eventHeap.top().getDest(); // get pkt dest
                int curr = eventHeap.top().getRID(); // current router location
                int nextHop = myrouters[curr].nextHopTable[pktDest];//get nextHop for band/delay access
                double pktSize = eventHeap.top().getSize();
//cout <<"pkt size is: " << pktSize << endl;
                double bandwidth = mylink[curr][nextHop].getBandwidth();
                double delay = mylink[curr][nextHop].getDelay();
//cout <<"mylink returns bandwidth: " << bandwidth << " and delay " << delay << endl;
                double time = pktSize/bandwidth + delay + seconds;
                int type = 3;
cout <<"curr is : " << curr << endl;
/* At this point the packet has left the output interface corresponding to its connected link and will now be popped out of the queue */
          /*     if(curr==149) { 
                   eventHeap.pop(); // popped out of eventHeap handler
                
                   myrouters[curr].outputQueue[nextHop].pop(); //popped out of queue
                   eventHeap.push(Packet(time, curr, pktDest, type, pktSize,curr));
 
                   continue;} */
               cout << "Moving from output queue of router: " <<curr<<" to propagation link towards: "<<nextHop << endl;
              if(!eventHeap.empty()) eventHeap.pop(); // popped out of eventHeap handler
                
                myrouters[curr].outputQueue[nextHop].pop(); //popped out of queue
                eventHeap.push(Packet(time, curr, pktDest, type, pktSize,curr,start));
                 
            } 
            if(eventHeap.top().getType() == 3) {// if at propagation move to inputQ 
                //double processTime = eventHeap.top().getTime();
                
                double start = eventHeap.top().getStart();
                int pktDest = eventHeap.top().getDest(); // get pkt dest
                int curr = eventHeap.top().getRID(); // current router location
                int nR = myrouters[curr].nextHopTable[pktDest]; // get next hop router
               // check if input queue of next router is full. function will return 0 ifso
                int queue = myrouters[nR].getQueue(pktDest);
cout<<"Moving from propagation from router: " << curr<< " to input queue of " << nR << endl;
                if(queue == 0 ) {
                    cout << "DROPPED at input Queue of router " << nR << endl; 
                    dropped[curr]++;
                    if(!eventHeap.empty()) eventHeap.pop();
                 }
                else if(queue == 777) {
                    cout << "********SUCCESS!" <<endl;
                    success++;
/*For each success, record the maxCompletion and minCompletion time if it is so.
  Then, add to the total of completion times where it is used for the average in results.
*/
                    double compTime = eventHeap.top().getTime()- eventHeap.top().getStart();
                     if(compTime > maxComplete) maxComplete = compTime;
                     if( (compTime!=0) && compTime < minComplete) minComplete = compTime;
                     totalComp += compTime; 
                }
                else { 
                     myrouters[nR].inputQueue[curr].push(1); // pushed into inputqueue!
                }
                transmission += seconds-eventHeap.top().getTime(); // get transmission time
                
                double pktSize = eventHeap.top().getSize();
                double time = seconds + myrouters[nR].inputQueue[curr].size() * pktSize/myrouters[nR].serviceRate;
                int type = 4;

              if(!eventHeap.empty())eventHeap.pop(); //popped out of eventHandler
                eventHeap.push(Packet(time, nR, pktDest, type, pktSize,curr,start));
            } 

            if(eventHeap.top().getType() == 4) { // if at inputq move to processing 4

                double start = eventHeap.top().getStart();
                int pktDest = eventHeap.top().getDest();
                int curr = eventHeap.top().getRID(); // current router location
                double pktSize = eventHeap.top().getSize();
                int previous = eventHeap.top().getPrev();
                
                double time = (pktSize/myrouters[curr].serviceRate) + seconds;
                int type = 1;
                cout << "moving from input queue of router: "<<curr<<" to processing. Packet destination is: " << pktDest<<endl;;
                if(!myrouters[curr].inputQueue[previous].empty()) myrouters[curr].inputQueue[previous].pop(); //popped from input queue! going to processing!
                eventHeap.push(Packet(time, curr, pktDest, type, pktSize,curr, start));
                if(!eventHeap.empty())eventHeap.pop();
            } 

   
        } 




 /*
3. handle each packet accordingly

	- heap.look() at type, whether it is in creation, processing, or propagation
	- each time the packet is handled, we update its time until completion accordingly.
		
*/





    }// End For-Loop Outer Simulation

int maxDropper;
double maxDrop = 0.0;
int minDropper; 
double minDrop = 100.0;
double minDrop2 = 100.0; //the second lowest since there seems to be lingering nodes which don't drop any packets. This may be due to the fact that no packets ever reach them via dijkstra's algorithm.

double totalDropped = 0.0;
for(int i=0; i<vertices; i++) {
   double current = dropped[i];
   if(current>maxDrop) {
       maxDrop = current;
       maxDropper = i;
   }
   if(( current!=-1 && current!=0) && current<minDrop) { 
       minDrop = current;
       minDropper = i;
   }
   if(( current!=-1) && current<minDrop) { 
       minDrop = current;
       minDropper = i;
   }
   totalDropped += current;
}
       
double fidelity = (1-(totalDropped+success)/packetgen)*100;
   

averageComplete = totalComp/success;
cout << "\n\n\n-------------------------------------"<<endl;
cout << "-------------RESULTS-----------------" <<endl;
cout << "number of generated packets: " << packetgen << endl;
cout << "number of successes: "<< success << endl;
cout << "Percentage of successfully received packets: " <<success/packetgen *100<<"%."<< endl;
cout << "Average transmission time for each transmission: " << transmission/totalTransmissions << " seconds."<<endl;
cout << "Maximum completion time is: " << maxComplete << " seconds." << endl;
cout << "Minimum completion time is: " << minComplete << " seconds."<< endl;
cout << "Average Completion time is: " << averageComplete << " seconds." << endl;

cout << "Router " <<maxDropper <<" droppped the most packets: " << maxDrop << "."<< endl;
cout << "Router " << minDropper << " dropped the least packets: " << minDrop << "." << endl;

cout << "Average number of drops per router " << totalDropped/150 << endl;
cout << "\n-------------------------------------\n\n"<<endl;
cout <<" note: if your filename was not found, the network topology will be printed to graph.txt" <<endl;
cout << "-------------MISC. RESULTS------------" <<endl;
cout << "Total Dropped: " << totalDropped << "." << endl;
cout << "Percent of \"lost\" packets or between processing/propagation/in queue \nbefore cutoff time: " << fidelity  <<"%." <<endl;
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

    if(visite==vertices){/*cout << "connected" <<endl;*/ return true;}
    else return false;
}
