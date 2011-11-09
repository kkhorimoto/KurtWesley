#include <fstream> 
#include <iostream>
#include <stdbool.h>
#include <set>
#include "time.h"

using namespace std;

struct nodePair {
    int start;
    int end;
};

//derived from c++ reference pages: http://www.cplusplus.com/reference/stl/set/set/
struct compFn 
{
    bool operator () (const nodePair &a, const nodePair &b) {
        if(a.start == b.start) {
            return (a.end < b.end);
        }
        else return (a.start < b.start);   
    }
};

void createRandomGraph(int numNodes, int numEdges, set<nodePair, compFn> &graphSet) {
    while (numEdges > 0) {
        nodePair n;
        n.start = rand() % numNodes + 1;
        n.end = rand() % numNodes + 1;
        
        if (n.start != n.end) {
            int prevSize = graphSet.size();
            graphSet.insert(n);
            if (graphSet.size() == prevSize + 1)
                numEdges--;
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
    char* outputFile = argv[3];

    set<nodePair, compFn> graphSet;
    createRandomGraph(numNodes, numEdges, graphSet);
    
    ofstream os;
    os.open(outputFile);
    os << numNodes << "\n" << numEdges << "\n";
    
    set<nodePair, compFn>:: iterator it;
    for (it = graphSet.begin();it != graphSet.end(); it++) {
        nodePair n = *it; 
        os << n.start << " " << n.end << "\n";
    }
    
    os.close();
    return 0;
}
