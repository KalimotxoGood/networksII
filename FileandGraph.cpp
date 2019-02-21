//Also remember to include these things :
#include <stdio.h>
#include <fstream>
#include <iostream>





int main(int argc , char *argv[])
{
    
    
    /*
     HELLO THIS IS WHERE THE GRAPH TO FILE FUNCTION IS. GRAPH7 IN THIS CASE IS 5X5 BUT CAN BE CHANGED
     YOU CAN CHANGE THE GRAPH/VERTICIES NUMBER AND THE REST OF THE CODE WILL STILL WORK. FOR EXAMPLE IF YOU WANT TO
     MAKE THE GRAPH BIGGER, JUST CHANGE GRAPH7 AND THE CODE WILL DETECT THAT AND WRITE IT TO A FILE
     */
    int links = 0;
    int graph[V][V] = { {0, 3, 0, 3, 0},
        {3, 0, 1, 2, 0},
        {0, 1, 0, 0, 1},
        {3, 2, 0, 0, 7},
        {0, 0, 1, 7, 0}
    };
    
    for(int x = 0; x < V; x++)
    {
        for(int y = 0; y < V; y++)
        {
            if (graph[x][y] > 0)    //if there is a connection add one to link count
            {
                links++;               //to put number of links in file
            }
        }
    }
    
    std::ofstream myfile;
    myfile.open("hi.txt");
    if(myfile.is_open())
    {
        myfile << V << " " << links << "  \n";
        for(int i = 0; i < V; i++)
        {
            for(int j = 0; j < V; j++)
            {
                if (graph[i][j] == 0)   //myLink.getDelay()()
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
    
    /*
     HELLO THIS IS THE END OF THE GRAPHTOFILE FUNCTION
     */
    
    
    
    
    
    /*
     THIS IS THE FILE TO GRAPH FUNCTION. IT TAKES IN A FILENAME (argv[2]) AND CREATES A GRAPH NAMES GRAPH7.
     YOU CAN USE THIS GRAPH7 FOR ANYTHING YOU WOULD BEFORE. THANKS LOLOLOLOL
     */
    int p = 2;
    int q = 3;
    int r = 0;
    int n = 0;
    int lines = 0;
    int arr[120];
    ifstream File;
    File.open(argv[2]);
    while(!File.eof())
    {
        File >> arr[n];             //puts each integer into an array
        n++;
    }
    File.close();
    
    for(int i=0;i<n-1;i++)
    {
        cout << arr[i] << " ";      //PLACES ALL NODES IN ARRAY FIRST
    }
    r = arr[0];
    lines = arr[1];
    
    cout << "done\n";
    cout << "Hello\n";
    cout << r << " \n";
    int graph7[r][r];     //initialize graph with size of first int given from file (r)
    for(int x = 0; x < r; x++)
    {
        for(int y = 0; y < r; y++)
        {
            graph7[x][y] = 0;           //set every part of matrix to 0 to simulate empty graph
        }
    }
    for(int i = 0; i < n; i++)
    {
        graph7[arr[p]][arr[q]] = 1;       //assign p and q connections from file
        if (p < n && q < n - 1)
        {
            p = p+2;           // getting seg fault here somewhere
            q = q+2;
        }
    }
    
}

