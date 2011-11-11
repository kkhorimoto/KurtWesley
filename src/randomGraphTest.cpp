#include <fstream>
#include <iostream>
#include <cstdio>
#include <stdbool.h>
#include <string.h>

using namespace std;

const char *basePath = "./part2out/";
const int numNodeArray[] = {100, 1000, 10000, 50000, 100000, 200000, 300000, 500000};
const int numEdgeCombinations = 100;
const int numTestsPerEdgeCombo = 100;


bool isGraphSingleSCC(int nodeTestNumber, int edgeTestNumber, int graphTestNumber) {
    char inputFilepath[strlen(basePath) + 9], buffer[5];
    strcpy (inputFilepath, basePath);
    sprintf(buffer, "%d/", nodeTestNumber);
    strcat (inputFilepath, buffer);
    sprintf(buffer, "%d/", edgeTestNumber);
    strcat (inputFilepath, buffer);
    sprintf(buffer, "%d",  graphTestNumber);
    strcat(inputFilepath, buffer);

    printf("inputFilepath: %s\n",inputFilepath);
  
    ifstream file;
    file.open(inputFilepath);

    int sccSize;
    if (file.is_open()) {
        for (int i = 0; i < 2; i++) {
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

    for (int j = 1; j <= numEdgeCombinations; j++) {
        int frequencyOfSCC = 0;
    	int multiplier = (numNodes * (numNodes -1)) / (numEdgeCombinations);
        int numEdges = numNodes + j*multiplier;
        for (int k = 0; k < numTestsPerEdgeCombo; k++) {
            if (isGraphSingleSCC(nodeTestNumber,j,k+1)) {
		        frequencyOfSCC++;
            }	
        }
        double percentage = 100.0 * (double)frequencyOfSCC / (double)numTestsPerEdgeCombo;

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
