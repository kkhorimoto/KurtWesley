#include <fstream>
#include <iostream>
#include <cstdio>
#include <stdbool.h>
#include <string.h>
#include <map>

using namespace std;
int numNodes;

void mapGraph (char *inputFile, map<int, int> &frequencyMap) {
    ifstream file;
    file.open(inputFile);

    if(!file) {
        cout << endl << "Error opening file " << inputFile; 
        return;
    }
    
    if(file.is_open()) {
        int curr, trash;
        file >> numNodes >> trash;
        
        while(!file.eof()) {
            file >> curr >> trash;
            int count = frequencyMap[curr];
            if(count == 0) {
                frequencyMap[curr] = 1;
            } else {
                int value = count + 1;
                frequencyMap[curr] = value;
            }
        }
    file.close();
    }
}

int getHighestNodeInGraph (map<int, int> &graph) {
    map<int, int>::iterator it;
   
    int highestDegreeNode;
    int curr;
    int max, count;
    for(it = graph.begin(); it != graph.end(); ++it){
        curr = (*it).first;
        count = (*it).second;
        if(count > max) {
            max = count;
            highestDegreeNode = curr; 
        }
    }
    return max;
}
        
    
int main(int argc, char* argv[]) {
    char* inputFile = argv[1];
    char* outputFile = argv[2];

    
    map<int, int> frequencyMap;
    
    mapGraph (inputFile, frequencyMap);
    highestDegreeNode = getHighestNodeInGraph(frequencyMap);
    

    ofstream os;
    os.open("./analyzeGraphResults");
    os << highestDegreeNode;
        
        
    os.close();
    return 0;
}

