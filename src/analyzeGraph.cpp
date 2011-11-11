#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <stdbool.h>
#include <string.h>
#include <set>


using namespace std;
int numNodes;

//Calculataes highest node
int getHighestNodeInGraph (std::map<int, int>  &graph) {
    map<int,int>::iterator it;
   
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


int mapGraph (char *inputFile, std::map<int, int>  &frequencyMap) {
    ifstream file;
    file.open(inputFile);
    
    if(!file) {
        cout << endl << "Error opening file " << inputFile; 
        return 0;
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
                int updated = count+1;
                frequencyMap[curr] = updated;
                
            }
        }
        
        file.close();
    }
    return getHighestNodeInGraph(frequencyMap);
}

int findIsolatedNodes(char * inputFile) {
    set<int>uniqueNodes;
    
    ifstream file;
    file.open(inputFile);
    if(file.is_open()) {
        int curr, trash;
        file >> numNodes >> trash;
        while(!file.eof()) {
            file >> curr;
            uniqueNodes.insert(curr);
        }
    }
    return numNodes - uniqueNodes.size();
}

int main(int argc, char* argv[]) {
    char* inputFile = argv[1];
    char* outputFile = argv[2];
    
    map<int, int> frequencyMap;
    int highestDegreeNode =  mapGraph (inputFile, frequencyMap);
    
    
    int numIsolatedNodes = findIsolatedNodes(inputFile);
    
    
    ofstream os;
    os.open("./analyzeGraphResults");
    
    
    os << highestDegreeNode << "\n";
    os << numIsolatedNodes << "\n";
    
        
    os.close();
    return 0;
}


