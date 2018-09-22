#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "FisherData.h"
using namespace std;

// ./fishstory [filename]
int main(int argc, char *argv[]) {
    //read the file argv1
    string line;
    ifstream inputFile;
    
    inputFile.open(argv[1]);
    
   // getline(inputFile, line);
   // FisherData fishdude(line);
    vector<FisherData> fishDudeFleet;
    while (getline(inputFile, line)) {
        
        fishDudeFleet.push_back(FisherData(line));
    }
    
    inputFile.close();
    
    for (int i = 0; i < fishDudeFleet.size(); i++) {
        fishDudeFleet.at(i).printStuff();
        cout << endl;
    }
    
    cout << "Who in the world has " << argv[2] << endl;
    for (int i = 0; i < fishDudeFleet.size(); i++) {
        if(fishDudeFleet.at(i).getFishType()==argv[2]){
            cout << fishDudeFleet.at(i).getName() << endl;
        }
    }
    return 0;
}
