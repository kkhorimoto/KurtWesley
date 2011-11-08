#include <fstream> 
#include <iostream>
#include <stdbool.h>
#include "time.h"

void generateRandomGraph(int numNodes, int numEdges, int **nodeGrid) {
    for(int i = 0; i < numNodes; i++) {
        for(int j = 0; i < numNodes; i++) {
            if(i!=j && numEdges > 0) {
                nodeGrid[i][j] = rand() % 1;
                if(nodeGrid[i][j] == 1)
                    numEdges--;
            } else {
                nodeGrid[i][j] = 0;
            }
        }
    }
}


int main(int argc, char* argv[])
{
    //initialize seed using time
    srand ( time(NULL) );
    
    
    int numNodes, numEdges;
    sscanf(argv[1], "%d", &numNodes);
    sscanf(argv[2], "%d", &numEdges);
    char* outputfile = argv[3];

    
    int nodeGrid[numNodes][numNodes];
    generateRandomGraph(numNodes, numEdges, &nodeGrid);
	
    
    
    ofstream os;
    os.open(outputFile);

    os << numNodes << "\n" << numEdges;
    
    for(int i = 0; i < numNodes; i++) {
        for(int j = 0; j < numNodes; j++) {
            if(nodeGrid[i][j] == 1)
                os << i << " " << j; 
        }
    }
    
   
    os.close();
    return 0;
}
