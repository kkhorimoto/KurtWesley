#include <fstream>
#include <iostream>
#include <stdbool.h>
#include <string.h>

using namespace std;

const char *basePath = "./basepath/";

bool isGraphSingleSCC(int nodeTestNumber, int edgeTestNumber, int graphTestNumber) {
    char inputFilepath[strlen(basePath) + 9];
    strcpy (inputFilepath, basePath);
    strcat (inputFilepath, itoa(nodeTestNumber));
    strcat (inputFilepath, "/");
    strcat (inputFilepath, itoa(edgeTestNumber));
    strcat (inputFilepath, "/");
    strcat (inputFilepath, itoa(graphTestNumber));

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

int main(int argc, char* argv[]) {
    int numNodeArray[] = {100, 1000, 10000, 50000, 100000, 200000, 300000, 500000};
    int numEdgeCombinations = 5;
    int numTestsPerEdgeCombo = 100;

    ofstream os;
    os.open("./RandomGraphTestResults");

    for (int i = 0; i < 8; i++) {
        int numNodes = numNodeArray[i];
        for (int j = 0; j < numEdgeCombinations; j++) {
            int frequencyOfSCC = 0;
            int numEdges = numNodes + j*(numNodes^2 - numNodes);
            for (int k = 0; k < numTestsPerEdgeCombo; k++) {
                if (isGraphSingleSCC(i+1,j,k+1)) frequencyOfSCC++;
            }
            double percentage = (double)frequencyOfSCC / (double)numTestsPerEdgeCombo;

            os << "N = " << numNodes << "\n";
            os << "M = " << numEdges << "\n";
            os << "% = " << percentage << "\n\n";
        }
    }

    os.close();
    return 0;
}
