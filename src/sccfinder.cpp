#include <fstream> 
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <stdbool.h>

#define PRINT_INPUT_FILE 0
#define PRINT_NODE_ARRAY 0
#define PRINT_DFS_DETAILS 0

using namespace std;

/*
 * Node struct definition.
 */

typedef struct Node {
    vector<Node * > outEdges, inEdges;
    bool visited, reverseVisited, isMemberOfSCC, isMemberOfNodeStack;
    int label;
};

/*
 * Global Variables
 */

int numNodes;
Node *nodeArray;
stack<Node * > nodeStack;
priority_queue<int> sccSizes;

/*
 * Node visiting helper functions
 */

void visitNode(Node *node, bool isReverse) {
    if (node) {
        bool *visitedBool = isReverse ? &(node->reverseVisited) : &(node->visited);
        *visitedBool = true;
    }
}

inline bool isNodeVisited(Node *node, bool isReverse) {
    return isReverse ? node->reverseVisited : node->visited;
}

/*
 * Node Access functions.
 */

inline Node *getNode(int i, bool isReverse) {
    if (isReverse) {
        return &(nodeArray[i-1]);
    } else {
        Node *node = nodeStack.top();
        nodeStack.pop();
        return node;
    }
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

#if PRINT_DFS_DETAILS
    if (isReverse) {
        printf("Starting reverse DFS:\n");
    } else {
        printf("Starting second DFS:\n");
    }
#endif

    while (!dfsStack.empty()) {
        // Inspect the top node in the stack.
        Node *node = dfsStack.top();
        dfsStack.pop();
        visitNode(node,isReverse);
        
        vector<Node * > *childrenNodes = getChildrenNodes(node,isReverse);
        if ((*childrenNodes).empty()) {
            // If there are no accessible nodes, then it's either a
            // leaf node or a node that has already been visited.
            if (isReverse) {
                if (!node->isMemberOfNodeStack) {
                    node->isMemberOfNodeStack = true;
                    nodeStack.push(node);
                }
            } else {
		        if (!node->isMemberOfSCC) {
			        node->isMemberOfSCC = true;
			        sccSize++;
		        }
	        }

#if PRINT_DFS_DETAILS
            printf("\tNode %d explored.\n", node->label);
#endif

        } else {
            // If there are nodes, we want to do a DFS on all these
            // children nodes, so we add them to the DFS stack.
            dfsStack.push(node);
            for (int i = 0; i < (*accessibleNodes).size(); i++) {
                Node *childNode = (*accessibleNodes).back();
                if (!isNodeVisited(childNode,isReverse)) {
                    dfsStack.push(childNode);
                }
    		    (*accessibleNodes).pop_back();
            }
        }
    }
    
#if PRINT_DFS_DETAILS
    if (!isReverse) printf("\tSCC Size = %d",sccSize);
    printf("\n\n");
#endif

    if (!isReverse) sccSizes.push(sccSize);
}

void DFSLoop(bool isReverse) {
    for (int i = numNodes; i > 0; i--) {
        Node *node = getNode(i,isReverse);
        if (!isNodeVisited(node,isReverse)) {
            DFS(node,isReverse);
        }
    }
}

/*
 * File Reading
 */

void setNumberOfNodes(int numberOfNodes) {
    numNodes = numberOfNodes;
    nodeArray = (Node *)malloc(numberOfNodes * sizeof(Node));
    
    Node node;
    node.isMemberOfSCC = false;
    for (int i = 0; i < numberOfNodes; i++) {
        node.label = i+1;
        memcpy(&nodeArray[i],&node,sizeof(node));
    }
}

void setNumberOfEdges(int numberOfEdges) {
    // We don't use this data yet, but it might come in hand later.
}

//allocate memory for the vector? malloc each individual one? 

void addEdge(int srcNodeIndex, int dstNodeIndex) {
    Node *srcNode = &nodeArray[srcNodeIndex - 1];
    Node *dstNode = &nodeArray[dstNodeIndex - 1];
    (srcNode->outEdges).push_back(dstNode);
    (dstNode->inEdges).push_back(srcNode);
}

bool readGraphIntoArray(char *inputFile) {
    ifstream file;
    file.open(inputFile);
    char * buffer;
    
    if(!file) {
        cout << endl << "Error opening file " << inputFile; 
        return false;
    }
    
    if(file.is_open()) {
        int numNodes, numEdges;
        file >> numNodes >> numEdges;
        setNumberOfNodes(numNodes);
        setNumberOfEdges(numEdges); //doesnt do anything 
        
        while(!file.eof()) {
            int start,end;
            file >> start >> end;
            
            addEdge(start,end);

#if PRINT_INPUT_FILE
            printf("%d %d\n", start, end);
#endif

        }
    }
    
    file.close();
    return true;
}


/*
 * Extracting the largest scc size
 */

void populateOutArray(int out[5]) {
    int numberOfSCCs = sccSizes.size();
    for (int i = 0; i < numberOfSCCs && i < 5; i++) {
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

void printNodeArray() {
    for (int i = 0; i < numNodes; i++ ) {
        Node *node = &nodeArray[i];
        printf("node: %d\n", i+1); 
        printf("\tIncoming Edges:\n");
        for (int j = 0; j < node->inEdges.size(); j++) {
            printf("\t  %d\n",(node->inEdges)[j]->label);
        }
        printf("\tOutgoing Edges:\n");
        for (int j = 0; j < node->outEdges.size(); j++) {
            printf("\t  %d\n",(node->outEdges)[j]->label);
        }
    }
}

void findSccs(char* inputFile, int out[5])
{
    bool readSuccess = readGraphIntoArray(inputFile);

#if PRINT_NODE_ARRAY
    printNodeArray();
#endif

    if (readSuccess) {
        DFSLoop(true);
    	DFSLoop(false);
        populateOutArray(out);
    }
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
