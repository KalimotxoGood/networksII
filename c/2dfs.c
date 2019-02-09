#include<stdio.h>
 
void DFS(int);
int G[10][10],visited[10],n;    //n is no of vertices and graph is sorted in array G[10][10]
 
void main()
{
    int i,j;
    printf("Enter number of vertices:");
    scanf("%d",&n);
/* 
    //read the adjecency matrix
    printf("\nEnter adjecency matrix of the graph:");
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d",&G[i][j]);
 */
int A[5][5] = {
    {0,1,0,1,0},
    {1,0,0,1,0},
    {0,0,0,0,0},
    {1,1,0,0,1},
    {0,0,0,1,0}
};
    //visited is initialized to zero
    for(i=0;i<n;i++)
        visited[i]=0;
    int k = 0;
    int l = 0;
    while(1){

        if(l==n&&A[k][l]==0) break;
        printf("%d\n", k);
        for(l=0;l<n;l++) {
            printf("for\n");
            if(!visited[l]&&A[k][l]==1) {
                k = l;
                visited[k] = 1; 
printf("break\n");
                break;
            }
            else { printf("else\n");break;}
printf("no break\n");
        }
       
    }
    printf("end\n");
 
 //   DFS(0);
}
 
void DFS(int i)
{
    int j;
    printf("\n%d",i);
    visited[i]=1;
    for(j=0;j<n;j++)
        if(!visited[j]&&G[i][j]==1)
            DFS(j);
}
