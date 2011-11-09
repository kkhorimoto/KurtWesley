#include <fstream>
#include <iostream>
#include <cstdio>
#include <stdbool.h>
#include <string.h>

using namespace std;

const char *basePath = "./basepath/";
const int numNodeArray[] = {100, 1000, 10000, 50000, 100000, 200000, 300000, 500000};
const int numEdgeCombinations = 5;
const int numTestsPerEdgeCombo = 100;


bool isGraphSingleSCC(int nodeTestNumber, int edgeTestNumber, int graphTestNumber) {
    char inputFilepath[strlen(basePath) + 9], buffer[5];
    strcpy (inputFilepath, basePath);
    sprintf(buffer, "%d/", nodeTestNumber);
    strcat (inputFilepath, buffer);
    sprintf(buffer, "%d/", edgeTestNumber);
    strcat (inputFilepath, buffer);
    sprintf(buffer, "%d",  graphTestNumber);

    ifstream file;
    file.open(inputFilepath);

    if (file.is_open()) {
        for (int i = 0; i < 5; i++) {
            int sccSize;
            file >> sccSize;

            if (i == 0 && sccSize == 0 || i != 0 && sccSize != 0) {
                file.close();
                return false;
            }
        }
    }

    file.close();
    return true;
}

void test(int nodeTestNumber, ofstream &os) {
    int numNodes = numNodeArray[nodeTestNumber-1];

    for (int j = 0; j < numEdgeCombinations; j++) {
        int frequencyOfSCC = 0;
        int numEdges = numNodes + j*(numNodes^2 - numNodes);
        for (int k = 0; k < numTestsPerEdgeCombo; k++) {
            if (isGraphSingleSCC(nodeTestNumber,j,k+1)) frequencyOfSCC++;
        }
        double percentage = (double)frequencyOfSCC / (double)numTestsPerEdgeCombo;

        os << "N = " << numNodes << "\n";
        os << "M = " << numEdges << "\n";
        os << "% = " << percentage << "\n\n";
    }
}

int testAll() {
    ofstream os;
    os.open("./RandomGraphTestResults");

    for (int i = 1; i < 9; i++) {
        test(i,os);
    }

    os.close();
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 1) return testAll();
    else {
       int testNumber = atoi(argv[1]);
       ofstream os;
       os.open("./RandomGraphTestResults");

       test(testNumber,os);

       os.close();
       return 0;
    }
}
