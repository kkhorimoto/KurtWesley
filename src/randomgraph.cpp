#include <fstream> 
#include <iostream>
#include <stdbool.h>
#include <string.h>
#include "time.h"

using namespace std;

int numNodes, numEdges;

inline int getRandomNodeNumber() {
    short int firstHalf = rand();
    short int secondHalf = rand();
    unsigned int nodeNumber;

    memcpy(&nodeNumber,&firstHalf,sizeof(firstHalf));
    memcpy((short int *)(&nodeNumber) + 1, &secondHalf, sizeof(secondHalf));

    return nodeNumber % numNodes + 1;
}

int main(int argc, char* argv[])
{
    //initialize seed using time
    srand ( time(NULL) );
    
    sscanf(argv[1], "%d", &numNodes);
    sscanf(argv[2], "%d", &numEdges);
    char* outputFile = argv[3];

    ofstream os;
    os.open(outputFile);
    os << numNodes << "\n" << numEdges << "\n";
    
    for (int i = 0; i < numEdges; i ++) {
        os << getRandomNodeNumber() << " " << getRandomNodeNumber() << "\n";
    }

    os.close();
    return 0;
}
