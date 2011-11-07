#include <fstream> 
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <stdbool.h>

using namespace std;

/*
 * Node struct definition.
 */

typedef struct node {
    struct node *leader;
    vector<struct node * > outEdges, inEdges;
    bool visited, reverseVisited;
} Node;

/*
 * Global Variables
 */

int visitedCounter, numNodes;
Node *nodeArray, *baseNode;
stack<Node * > nodeStack;
priority_queue<int> sccSizes;

/*
 * Node visiting helper functions
 */

void visitNode(Node *node, bool isReverse) {
    if (node) {
        bool *visitedBool = isReverse ? &(node->reverseVisited) : &(node->visited);
        *visitedBool = true;

        node->leader = baseNode;
    }
}

inline bool isNodeVisited(Node *node, bool isReverse) {
    return isReverse ? node->reverseVisited : node->visited;
}

/*
 * Node Access functions.
 */

inline Node *getNode(int i, bool isReverse) {
    return isReverse ? &(nodeArray[i-1]) : nodeStack.top();
}

inline vector<Node * > *getAccessibleNodes(Node *node, bool isReverse) {
    return isReverse ? &(node->inEdges) : &(node->outEdges);
}

inline void clearAccessibleNodes(Node *node, bool isReverse) {
    vector<Node *> *accessibleNodes = getAccessibleNodes(node,isReverse);
    (*accessibleNodes).clear();
}

/*
 * DFS functions.
 */

void DFS(Node *startNode, bool isReverse) {
    int sccSize = 0;

    stack<Node * >dfsStack;
    dfsStack.push(startNode);
    while (!dfsStack.empty()) {
        Node *node = dfsStack.top();
        dfsStack.pop();
        visitNode(node,isReverse);

        vector<Node * > *accessibleNodes = getAccessibleNodes(node,isReverse);
        if ((*accessibleNodes).empty()) {
            if (isReverse) nodeStack.push(node);
            else sccSize ++;
        } else {
            dfsStack.push(node);
            for (int i = 0; i < (*accessibleNodes).size(); i++) {
                Node *childNode = (*accessibleNodes)[i];
                if (!isNodeVisited(childNode,isReverse)) {
                    dfsStack.push(childNode);
                }
            }
            clearAccessibleNodes(node,isReverse);
        }
    }
    if (!isReverse) sccSizes.push(sccSize);
}

void DFSLoop(bool isReverse) {
    baseNode = NULL;
    for (int i = numNodes; i > 0; i--) {
        Node *node = getNode(i,isReverse);
        if (!isReverse) nodeStack.pop();
        if (!isNodeVisited(node,isReverse)) {
            baseNode = node;
            DFS(node,isReverse);
        }
    }
}

/*
 * File Reading
 */

void setNumberOfNodes(int numberOfNodes) {
    nodeArray = malloc(numberOfNodes * sizeof(Node));
}

void setNumberOfEdges(int numberOfEdges) {
    // We don't use this data yet, but it might come in hand later.
}

void addEdge(int srcNodeIndex, int dstNodeIndex) {
    Node *srcNode = &nodeArray[srcNodeIndex - 1];
    Node *dstNode = &nodeArray[dstNodeIndex - 1];
    (srcNode->outEdges).push_back(dstNode);
    (dstNode->inEdges).push_back(srcNode);
}

void readGraphIntoArray(char *inputFile) {
    //TODO: read the input file and populate the graph into the nodeArray global variable. 
}

/*
 * Extracting the largest scc size
 */

void populateOutArray(int out[5]) {
    int numberOfSCCs = sccSizes.size();
    for (int i = 0; i < numberOfSCCs; i++) {
        out[i] = sccSizes.top();
        sccSizes.pop();
    }
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

    populateOutArray(out);
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
    int sccSizes[] = {0, 0, 0, 0, 0};
    char* inputFile = argv[1];
    char* outputFile = argv[2];

    findSccs(inputFile, sccSizes);
	
    // Output the first 5 sccs into a file.
    ofstream os;
    os.open(outputFile);
    os << sccSizes[0] << "\t" << sccSizes[1] << "\t" << sccSizes[2] <<
      "\t" << sccSizes[3] << "\t" << sccSizes[4];
    os.close();
    return 0;
}

