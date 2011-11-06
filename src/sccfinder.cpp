#include <fstream> 
#include <iostream>
#include <vector>
#include <stack>
#include <stdbool.h>

using namespace std;

typedef struct node {
    int value;
    struct node *leader;
    std::vector<struct node * > outEdges, inEdges;
    bool visited, reverseVisited;
} Node;

int visitedCounter, numNodes;
Node *nodeArray, *baseNode;
std::stack<Node * > nodeStack;

void visitNode(Node *node, bool isReverse) {
    if (node) {
        bool *visitedBool = isReverse ? &(node->reverseVisited) : &(node->visited);
        *visitedBool = true;
    }
}

inline bool isNodeVisited(Node *node, bool isReverse) {
    return isReverse ? node->reverseVisited : node->visited;
}

// node index i is from 1 to numNodes, so we must correct it
// when accessing a zero-based array.
inline Node *getNode(int i, bool isReverse) {
    return isReverse ? &(nodeArray[i-1]) : nodeStack.top();
}

inline std::vector<Node * > getAccessibleNodes(Node *node, bool isReverse) {
    return isReverse ? node->inEdges : node->outEdges;
}

void DFS(Node *node, bool isReverse) {
    visitNode(node,isReverse);
    node->leader = baseNode;

    std::vector<Node * > accessibleNodes = getAccessibleNodes(node,isReverse);
    for (int i = 0; i < accessibleNodes.size(); i++) {
        if (!isNodeVisited(accessibleNodes[i],isReverse)) {
            DFS(accessibleNodes[i],isReverse);
        }
    }

    visitedCounter++;
    node->value = visitedCounter;
}

void DFSLoop(bool isReverse) {
    visitedCounter = 0;
    baseNode = NULL;
    for (int i = numNodes; i > 0; i--) {
        Node *node = getNode(i,isReverse);
        if (!isReverse) nodeStack.pop();
        if (!isNodeVisited(node,isReverse)) {
            baseNode = node;
            DFS(node, isReverse);
        }
    }
}

void readGraphIntoArray(char *inputFile) {

}

/**
 * Given an input file (inputFile) and an integer array (out) of size 5, fills
 * the 5 largest SCC sizes into (out) in decreasing order. In the case where
 * there are fewer than 5 components, you should fill in 0 for the remaining
 * values in (out). For example, if there are only 2 components of size 100 and
 * 50, you should fill:
 * out[0] = 100
 * out[1] = 50
 * out[2] = 0
 * out[3] = 0
 * out[4] = 0
 */
void findSccs(char* inputFile, int out[5])
{
    readGraphIntoArray(inputFile);

    DFSLoop(true);
    DFSLoop(false);

    // TODO: Implement this function.
    out[0] = 0;
    out[1] = 0;
    out[2] = 0;
    out[3] = 0;
    out[4] = 0;
}

/*
 * sccfinder should be your main class. If you decide to code in C, you can
 * rename this file to sccfinder.c. We only want your binary to be named
 * sccfinder and we want "make sccfinder" to build sccfinder.
 * Main takes two arguments: 1) input file and 2) output file.
 * You should fill in the findSccs function.
 * Warning: Don't change the part of main that outputs the result of findSccs.
 * It outputs in the correct format.
 */
int main(int argc, char* argv[])
{
    int sccSizes[5];
    char* inputFile = argv[1];
    char* outputFile = argv[2];

    findSccs(inputFile, sccSizes);
	
    // Output the first 5 sccs into a file.
    std::ofstream os;
    os.open(outputFile);
    os << sccSizes[0] << "\t" << sccSizes[1] << "\t" << sccSizes[2] <<
      "\t" << sccSizes[3] << "\t" << sccSizes[4];
    os.close();
    return 0;
}

