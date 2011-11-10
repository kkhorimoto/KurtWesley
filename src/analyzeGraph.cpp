#include <fstream>
#include <iostream>
#include <cstdio>
#include <stdbool.h>
#include <string.h>
#include <map>

using namespace std;

void mapGraph (char *inputFile, map<int, int> frequencyMap) {
    ifstream file;
    file.open(inputFile);

    if(!file) {
        cout << endl << "Error opening file " << inputFile; 
        return;
    }
    
    if(file.is_open()) {
        int curr, trash;
        int prev = 1; 
        int count = 0;
        int max = 0;
        file >> trash >> trash;
        
        while(!file.eof()) {
            file >> curr >> trash;
            int count = frequencyMap[curr];
            if(count == 0) {
                frequencyMap.insert(pair<int,int> (curr, 1));
            } else {
                frequencyMap.insert(pair<int,int> (curr, count+1));
            }
        }
    
    file.close();
    }
}

int getHighestNodeInGraph (map<int, int> graph) {
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
    return highestDegreeNode;
}
        
    
int main(int argc, char* argv[]) {
    char* inputFile = argv[1];
    char* outputFile = argv[2];
    
    int highestDegreeNode = 0;
    
    map<int, int> frequencyMap;
    
    mapGraph (inputFile, frequencyMap);
    highestDegreeNode = getHighestNodeInGraph(frequencyMap);
    

    ofstream os;
    os.open("./analyzeGraphResults");
    os << highestDegreeNode;
        
        
    os.close();
    return 0;
}

