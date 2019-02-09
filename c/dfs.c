/* Implementation of DFS in C from https://www.quora.com/How-do-I-implement-DFS-traversal-using-adjacency-matrix-in-a-C-program

This type of implementation may be implemented in the network simulation to find adjacent routers
in the links adjacency matrix

*/


#include <stdbool.h>
#include<stdio.h>
 
void DFS(int);
int G[10][10],visited[10],n;    //n is no of vertices and graph is sorted in array G[10][10]
 
bool main()
{
    int i,j;
    printf("Enter number of vertices:");
    scanf("%d",&n);
 
    //read the adjecency matrix
    printf("\nEnter adjecency matrix of the graph:");
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d",&G[i][j]);
 
    //visited is initialized to zero
    for(i=0;i<n;i++)
        visited[i]=0;

//--------------------------------------------- 
    
    DFS(0); // Begin visited at node 0.
}
 
void DFS(int i)
{
    int j;
    printf("%d\n",i);
    visited[i]=1; // Visted needs to reach all nodes. 
/* Beginning at node 0, iterate
*/
    for(j=0;j<n;j++)
        
        if(!visited[j]&&G[i][j]==1)  
// If not visited and there is an edge from i to j
 			// outer to inner order of precedence

            DFS(j);
}

